﻿using SqliteDotNet;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace OSGeo.MapGuide.Test.Common
{
    /// <summary>
    /// Extension methods for SqliteVm
    /// </summary>
    public static class SqliteDbExtensions
    {
        public static int Prepare(this SqliteVm vm, string sql, params object[] args)
        {
            string formattedSql = string.Format(sql, args);
            return vm.Prepare(formattedSql);
        }

        public static int Execute(this SqliteVm vm, string sql, params object[] args)
        {
            string formattedSql = string.Format(sql, args);
            return vm.Execute(formattedSql);
        }

        public static bool ReadParameterValue(this SqliteVm vm, int paramSetId, string paramName, NameValueCollection result, bool bIsPath = false)
        {
            int stat = vm.Execute("Select ParamValue from Params WHERE ParamSet={0} AND ParamName=\"{1}\"", paramSetId, paramName);
            if (stat == Sqlite.Row)
            {
                string str = vm.GetString("ParamValue");
                if (bIsPath)
                {
                    str = CommonUtility.GetPath(str);
                }
                result.Add(paramName, str);
                return true;
            }
            return false;
        }

        public static bool ReadParameterValue(this SqliteVm vm, string paramName, NameValueCollection result)
        {
            int stat = vm.Execute("Select ParamValue from Params WHERE ParamName=\"{0}\"", paramName);
            if (stat == Sqlite.Row)
            {
                result.Add(paramName, vm.GetString("ParamValue"));
                return true;
            }
            return false;
        }

        public static bool ReadCommonParameterValue(this SqliteVm vm, string paramName, NameValueCollection result)
        {
            int stat = vm.Execute("Select ParamValue from CommonParams WHERE ParamName=\"{0}\"", paramName);
            if (stat == Sqlite.Row)
            {
                result.Add(paramName, vm.GetString("ParamValue"));
                return true;
            }
            return false;
        }
    }

    /// <summary>
    /// Common utility methods
    /// </summary>
    public class CommonUtility
    {
        public static NameValueCollection SetCommonParams(int paramSet, SqliteDb db)
        {
            NameValueCollection result = null;
            var vm = new SqliteVm(db, false);
            try
            {
                result = new NameValueCollection();

                vm.ReadParameterValue(paramSet, "OPERATION", result);
                vm.ReadCommonParameterValue("VERSION", result);
                vm.ReadCommonParameterValue("CREDENTIALS", result);
                vm.ReadCommonParameterValue("LOCALE", result);

                vm = null;
            }
            catch (MgException ex)
            {
                throw new UnitTestException(string.Format("Exception from MapGuide:\n{0}", ex.GetDetails()));
            }
            catch (Exception ex)
            {
                try
                {
                    vm = null;
                    vm = new SqliteVm(db, true);
                    vm.ReadParameterValue("VERSION", result);
                    vm.ReadParameterValue("CREDENTIALS", result);
                    vm.ReadParameterValue("LOCALE", result);
                }
                catch (Exception ex2)
                {

                }
            }
            return result;
        }

        public static MgByteReader GetByteReaderFromPath(string path, bool bCheck = true)
        {
            if (bCheck)
            {
                if (File.Exists(path))
                {
                    MgByteSource source = new MgByteSource(path);
                    MgByteReader reader = source.GetReader();
                    return reader;
                }
                return null;
            }
            else
            {
                MgByteSource source = new MgByteSource(path);
                MgByteReader reader = source.GetReader();
                return reader;
            }
        }

        public static string GetDbPath(string dumpFileName)
        {
            var db = new SqliteDb();
            var dbPath = dumpFileName.Replace(".dump", ".db");
            var dbName = CommonUtility.GetPath(dbPath);

            if (!File.Exists(dumpFileName) && !File.Exists(dbName))
            {
                throw new UnitTestException(string.Format("Error: Dump file {0} not found. Unable to create database file", dumpFileName));
            }
            else if (!File.Exists(dbName))
            {
                db.GenerateDatabase(dumpFileName, dbName);
            }
            else if (File.Exists(dumpFileName) && File.GetLastWriteTimeUtc(dumpFileName) > File.GetLastWriteTimeUtc(dbName))
            {
                try
                {
                    File.Delete(dbName);
                    db.GenerateDatabase(dumpFileName, dbName);
                }
                catch
                {
                    throw new UnitTestException(string.Format("Unable to delete database file {0}. The file is either in use or is read-only. The database has not been updated", dbName));
                }
            }

            return dbPath;
        }

        public static string GetPath(string dbPath)
        {
            return dbPath.Replace("\\", "/");
        }

        public static MgStringCollection StringToMgStringCollection(string str)
        {
            try
            {
                MgStringCollection coll = new MgStringCollection();
                string[] tokens = str.Split(',');
                foreach (var token in tokens)
                {
                    coll.Add(token);
                }
                return coll;
            }
            catch (MgException ex)
            {
                throw new UnitTestException(string.Format("Exception from MapGuide:\n{0}", ex.GetDetails()));
            }
        }

        public static string MgStringCollectionToString(MgStringCollection coll)
        {
            try
            {
                List<string> items = new List<string>();
                for (int i = 0; i < coll.GetCount(); i++)
                {
                    items.Add(coll.GetItem(i));
                }
                return string.Join(",", items.ToArray());
            }
            catch (MgException ex)
            {
                throw new UnitTestException(string.Format("Exception from MapGuide:\n{0}", ex.GetDetails()));
            }
        }

        public static string BooleanToString(bool b)
        {
            return b ? "True" : "False";
        }

        public static string MgEnvelopeToString(MgEnvelope env)
        {
            try
            {
                var ll = env.GetLowerLeftCoordinate();
                var ur = env.GetUpperRightCoordinate();
                return string.Format(CultureInfo.InvariantCulture,
                    "({0}:{1})-({2}:{3})", 
                    ll.GetX(), 
                    ll.GetY(), 
                    ur.GetX(), 
                    ur.GetY());
            }
            catch (MgException ex)
            {
                throw new UnitTestException(string.Format("Exception from MapGuide:\n{0}", ex.GetDetails()));
            }
        }

        public static string MgPointToString(MgPoint pt)
        {
            try
            {
                var coord = pt.GetCoordinate();
                return string.Format(CultureInfo.InvariantCulture,
                    "({0}:{1})",
                    coord.GetX(),
                    coord.GetY());
            }
            catch (MgException ex)
            {
                throw new UnitTestException(string.Format("Exception from MapGuide:\n{0}", ex.GetDetails()));
            }
        }

        public static string GetExtension(string name)
        {
            if (name.LastIndexOf(".") >= 0)
            {
                return name.Substring(name.LastIndexOf(".") + 1);
            }
            else
            {
                if (name == "MG_USER_CREDENTIALS")
                    return "txt";
                else
                    return "bin";
            }
        }

        public static string GetMimeType(string extension)
        {
            switch (extension)
            {
                case "agf":
                    return "application/agf";
                case "bin":
                    return "application/octet-stream";
                case "dwf":
                    return "model/vnd.dwf";
                case "jpg":
                case "jpeg":
                    return "image/jpeg";
                case "png":
                    return "image/png";
                case "tif":
                case "tiff":
                    return "image/tiff";
                case "html":
                    return "text/html";
                case "txt":
                    return "text/plain";
                case "xml":
                    return "text/xml";
                default:
                    return "application/octet-stream";
            }
        }

        public static string SpecialDataHandling(string operation, string resultData, string mimeType)
        {
            string res = resultData;
            switch (operation)
            {
                case "ENUMERATERESOURCES":
                    res = RemoveTimeStamp(resultData);
                    break;
                case "GETDRAWINGLAYER":
                    res = RemoveDwfSectionName(resultData);
                    break;
                case "GETDRAWINGSECTION":
                    res = RemoveDwfSectionName(resultData);
                    break;
                case "GETLOG":
                    res = RemoveLogEntryTimeStamp(resultData);
                    break;
                case "GETMAP":
                    res = GetMapHeader(resultData);
                    break;
                case "GETLONGTRANSACTIONS":
                    res = RemoveCreationDate(resultData);
                    break;
            }

            if (res != null && mimeType == "text/xml")
            {
                var doc = new XmlDocument();
                doc.LoadXml(res);
                res = SortElement(doc, "");
            }
            return res;
        }

        private static string SortElement(XmlNode elem, string preText)
        {
            var elemArray = new List<string>();
            string elemString = "";
            if (elem.ChildNodes.Count > 0)
            {
                foreach (XmlNode child in elem.ChildNodes)
                {
                    if (child.NodeType == XmlNodeType.Element)
                    {
                        var elemValue = SortElement(child, preText + "  ");
                        if (!string.IsNullOrEmpty(elemValue))
                            elemArray.Add(elemValue);
                    }
                    else if (child.NodeType == XmlNodeType.Text)
                    {
                        string content = child.InnerText.Trim();
                        if (!string.IsNullOrEmpty(content))
                            elemArray.Add(content);
                    }
                }
                elemArray.Sort();
                foreach (string str in elemArray)
                {
                    elemString += str;
                }
            }

            string endTag = "";
            if (elemArray.Count > 1 && elemString.Length > 0)
            {
                endTag = "\n" + preText;
            }
            string tagName = "";
            if (!(elem is XmlDocument))
            {
                tagName = elem.Name;
            }
            endTag += "</" + tagName + ">";

            if ("" != tagName)
            {
                elemString = "\n" + preText + "<" + tagName + ">" + elemString + endTag;
            }

            return elemString;
        }

        private static string RemoveTimeStamp(string resultData)
        {
            string result = resultData;
            string newResult = result;
            while (result.IndexOf("<CreatedDate>") >= 0)
            {
                newResult = result.Substring(0, result.IndexOf("<CreatedDate>"));
                newResult += result.Substring(result.IndexOf("</ModifiedDate>") + "</ModifiedDate>".Length);
                result = newResult;
            }
            return newResult;
        }

        private static string RemoveDwfSectionName(string resultData)
        {
            string newResult = resultData.Substring(resultData.IndexOf(".w2d"));
            if (0 != newResult.IndexOf("EndOfDWF"))
            {
                newResult = newResult.Substring(0, newResult.IndexOf("EndOfDWF"));
            }
            return newResult;
        }

        private static string RemoveLogEntryTimeStamp(string resultData)
        {
            string result = resultData;
            string newResult = result;
            while (result.IndexOf("<") >= 0)
            {
                newResult = result.Substring(0, result.IndexOf("<"));
                newResult += result.Substring(result.IndexOf(">") + 1);
                result = newResult;
            }
            return newResult;
        }

        private static string GetMapHeader(string resultData)
        {
            if (resultData.IndexOf("(DWF V06.01)") >= 0)
                resultData = "(DWF V06.01)";
            return resultData;
        }

        private static string RemoveCreationDate(string resultData)
        {
            string newResult = resultData;
            while (resultData.IndexOf("<CreationDate>") >= 0)
            {
                newResult = resultData.Substring(0, resultData.IndexOf("<CreationDate>"));
                newResult += resultData.Substring(resultData.IndexOf("</CreationDate>") + "</CreationDate>".Length);
                resultData = newResult;
            }
            return newResult;
        }

        public static string ProcessExceptionMessage(string resultData)
        {
            string text = "exception occurred";
            if (resultData.Contains(text))
            {
                resultData = resultData.Substring(0, resultData.IndexOf(text) + text.Length); 
            }
            return resultData;
        }

        public static bool SpecialValidation(string operation, string resultData, string expectedResult)
        {
            if (operation == "GETFEATUREPROVIDERS")
            {
                return GetFeatureProvidersValidation(resultData, expectedResult);
            }
            return false;
        }

        private static bool GetFeatureProvidersValidation(string resultData, string expectedResult)
        {
            throw new NotImplementedException();
        }

        public static string RemoveStackTraceFromResult(string result)
        {
            //TODO: Clean out stack trace
            return result;
        }

        public static string GetExtensionFromMimeType(string mimeType)
        {
            string extension = "xml";
            if (mimeType.Contains("ePlot"))
                return "dwf";
            if (mimeType.Contains("text/plain"))
                return "txt";
            if (mimeType.Contains("text/html"))
                return "html";

            switch (mimeType)
            { 
                case "application/agf":
                    return "agf";
                case "application/octet-stream":
                    return "bin";
                case "model/vnd.dwf":
                    return "dwf";
                case "image/jpeg":
                    return "jpg";
                case "image/png":
                    return "png";
                case "image/tiff":
                    return "tiff";
                case "application/x-w2d":
                    return "dwf";
            }

            return extension;
        }
    }
}
