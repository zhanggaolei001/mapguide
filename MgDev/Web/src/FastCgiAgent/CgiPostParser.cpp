//
//  Copyright (C) 2004-2006  Autodesk, Inc.
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of version 2.1 of the GNU Lesser
//  General Public License as published by the Free Software Foundation.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//

#include "AceCommon.h"
#include "HttpHandler.h"
#include "CgiPostParser.h"
#include "CgiGetParser.h"
#include "CgiStrings.h"
#ifdef WIN32
#include "fcgi_config_x86.h"
#else
#include "fcgi_config.h"
#endif
#include "fcgi_stdio.h"

extern void DumpMessage(const char* format, ...);
extern void DumpMessage2(const char* msg);

// Is the thing pointed to an XML processing instruction?
bool IsXmlPi(char* buf)
{
    return buf[0] == '<' &&
           buf[1] == '?' &&
           buf[2] == 'x' &&
           buf[3] == 'm' &&
           buf[4] == 'l';
}

CgiPostParser::CgiPostParser(void)
{
}

CgiPostParser::~CgiPostParser(void)
{
}

void CgiPostParser::Parse(MgHttpRequestParam* params)
{
    MG_TRY()
    //TODO: Make MAXPOSTSIZE a webconfig parameter
    static size_t MAXPOSTSIZE = 1000000000; // Limit to 1Gig
    static size_t bufSize = 0;
    static char* buf = NULL;
    size_t bufPos = 0;

    // TODO: Use a memory mapped file here
    char* contentLength = getenv(CgiStrings::ContentLength);

    size_t nBytes = 0;
    if (NULL != contentLength)
    {
        DumpMessage("Content length %s", contentLength);
        nBytes = atoi(contentLength);
        if (nBytes < 0 || nBytes > MAXPOSTSIZE)
        {
            throw new MgStreamIoException(L"CgiPostParser.Parse", __LINE__, __WFILE__, NULL, L"", NULL);
        }

        // Attempt to reuse the existing buffer, if it's
        // big enough; if not, we need to reallocate a bigger
        // one.  Note: to avoid a null pointer, even when a first
        // pass has Content-Length == 0 (an thus not > the virgin
        // bufSize,) we ALWAYS come through this branch if the
        // buffer is still null.
        if (nBytes > bufSize || buf == NULL)
        {
            if (buf != NULL)
            {
                free(buf);
                buf = NULL;
            }
            // Add extra byte for url encoded null termination
            buf = (char*) malloc(nBytes+1);

            if (NULL == buf)
            {
                throw new MgOutOfMemoryException(L"CgiPostParser.Parse", __LINE__, __WFILE__, NULL, L"", NULL);
            }

            bufSize = nBytes;
        }
    }

    DumpMessage("Attempting to read %d bytes", nBytes);

    size_t readBytes = 0;

    if (nBytes > 0)
    {
        readBytes = fread(buf, 1, nBytes, stdin);
    }

    DumpMessage("Read %d bytes", readBytes);
    DumpMessage2(buf);


    if (readBytes != nBytes)
    {
        //TODO:  Better exception message?
        throw new MgStreamIoException(L"CgiPostParser.Parse", __LINE__, __WFILE__, NULL, L"", NULL);
    }

    char* contentType = getenv(CgiStrings::ContentType);
    if (NULL != contentType)
    {
        string content = contentType;
        DumpMessage("Content type: %s", content.c_str());

        if (content == CgiStrings::UrlEncoded)
        {
            buf[nBytes] = '\0';
            // Here's another case of interoperability "Forgiveness
            // and Tolerance": deegree, among other clients, sends along
            // a POST with xml contents, but fails to correctly set the
            // mime type.  You guessed it: it says it's url-encoded.
            // ----------------
            // If we got here, but determine that the contents look
            // and feel like XML, it's a safe bet that it should
            // be treated like XML.  Otherwise, we assume the
            // content-type is probably correct.  (Note that
            // the IsXmlPi should conveniently fail if it really IS
            // url-encoded, since the question mark in <?xml...?>
            // should itself be url-encoded: <%3Fxml... )
            if(IsXmlPi(buf))
                params->SetXmlPostData(buf);
            else
                CgiGetParser::Parse(buf,params);
        }
        else if (content.find(CgiStrings::MultiPartForm) != content.npos)
        {
            // TODO: Factor this block into a descriptively-named method;
            // this one is waaaaaaaay too long.
            // Delegation code (if then else if then else if ...) shouldn't
            // mingle with actual "work" code.
            const char* boundary = CgiStrings::PostBoundary;
            string::size_type tagIdx = content.find(boundary);
            if (tagIdx != content.npos)
            {
                string partTag = "--";
                partTag.append(content.substr(tagIdx+strlen(boundary)));
                string dataEndTag = "\r\n";
                dataEndTag.append(partTag);
                char* endBuf = &buf[nBytes];
                char* curBuf = buf;
                while (curBuf < endBuf && NULL != curBuf)
                {
                    // Isolate multipart header
                    bool bOk = true;
                    char* partHdrStart = NULL;
                    char* partHdrEnd = NULL;
                    bOk = (NULL != (partHdrStart = strstr(curBuf, partTag.c_str())));
                    if (bOk) bOk = (NULL != (partHdrEnd = strstr(partHdrStart, "\r\n\r\n")));

                    STRING paramName;
                    STRING paramType;
                    bool bIsFile = false;

                    // Scan headers
                    if (bOk)
                    {
                        *partHdrEnd = '\0';
                        string hdr = partHdrStart;

                        string nameTag = CgiStrings::PostName;
                        string::size_type idx = hdr.find(nameTag);
                        if (idx != hdr.npos)
                        {
                            string::size_type i = idx+nameTag.length();
                            string::size_type j = hdr.find("\"", i);
                            paramName = MgUtil::MultiByteToWideChar(hdr.substr(i, j-i));
                        }

                        string typeTag = CgiStrings::PostContent;
                        idx = hdr.find(typeTag);
                        if (idx != hdr.npos)
                        {
                            string::size_type i = idx+typeTag.length();
                            string::size_type j = hdr.find(" ", i);
                            paramType = MgUtil::MultiByteToWideChar(hdr.substr(i, j-i));
                        }

                        string fileTag = CgiStrings::PostFile;
                        if (hdr.find(fileTag) != hdr.npos)
                        {
                            bIsFile = true;
                        }
                    }

                    // And populate the data
                    if (paramName.length() > 0)
                    {
                        // Note:  dataEnd tag always start with "\r\n--" (see above)
                        char* dataStart = partHdrEnd + 4;
                        char* dataEnd = dataStart;
                        char match0 = dataEndTag[0];
                        char match1 = dataEndTag[1];
                        char match2 = dataEndTag[2];
                        char match3 = dataEndTag[3];
                        while (dataEnd < endBuf)
                        {
                            // This multi-and should virtually guarantee that the strstr
                            // is only called once on the correct data.  It matches against
                            // the constant part of the end tag.
                            if (dataEnd[0] == match0 && dataEnd[1] == match1 &&
                                dataEnd[2] == match2 && dataEnd[3] == match3)
                            {
                                if (strstr(dataEnd, dataEndTag.c_str()) == dataEnd)
                                {
                                    break;
                                }
                            }
                            dataEnd++;
                        }

                        if (dataEnd > dataStart && dataEnd < endBuf)
                        {
                            if (bIsFile)
                            {
                                //TODO: Change infrastructure so byte reader can
                                // be passed directly into HTTP call.  Possibly an
                                // overload on AddParameter that takes a reader
                                STRING fileName = MgFileUtil::GenerateTempFileName();
                                Ptr<MgByte> bytes = new MgByte((BYTE_ARRAY_IN)dataStart, (INT32)(dataEnd-dataStart), MgByte::None);
                                Ptr<MgByteSource> source = new MgByteSource(bytes);
                                Ptr<MgByteSink> sink = new MgByteSink(source->GetReader());
                                sink->ToFile(fileName);

                                params->AddParameter(paramName, fileName);
                                params->SetParameterType(paramName, paramType);
                            }
                            else
                            {
                                *dataEnd = '\0';
                                string paramVal = dataStart;
                                *dataEnd = '\r';
                                wstring paramValue;
                                MgUtil::MultiByteToWideChar(paramVal, paramValue);
                                params->AddParameter(paramName, paramValue);
                             }
                        }

                        curBuf = dataEnd-1;
                    }
                    else
                    {
                        curBuf = NULL;
                    }
                }
            }
        }
        // The check for text/xml is not always sufficient.  CarbonTools, for example,
        // fails to set Content-Type: text/xml and just sends Content-Type: utf-8.
        // A better check might be looking into the buffer to find "<?xml" at the beginning.
        else if (content.find(CgiStrings::TextXml) != content.npos || IsXmlPi(buf))
        {
            buf[nBytes] = '\0';
            params->SetXmlPostData(buf);
        }
        else
        {
            //TODO: throw a better exception here
            throw new MgStreamIoException(L"CgiPostParser.Parse", __LINE__, __WFILE__, NULL, L"", NULL);
        }
    }
    MG_CATCH_AND_THROW(L"CgiPostParser.Parse");
}

