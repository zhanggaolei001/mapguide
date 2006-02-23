# Microsoft Developer Studio Project File - Name="dbxml_query_runner" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=dbxml_query_runner - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dbxml_query_runner.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dbxml_query_runner.mak" CFG="dbxml_query_runner - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dbxml_query_runner - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "dbxml_query_runner - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dbxml_query_runner - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release\dbxml_query_runner"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release\dbxml_query_runner"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I "../include" /I "../src/dbxml" /I "../../xquery-1.2.0/include"  /I "../../pathan/include" /I "../../db-4.3.29/include" /I "../../db-4.3.29/build_win32" /I "../../db-4.3.29/dbinc" /I "../../xerces-c-src/include" /I "../../xerces-c-src/src" /I "../../include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 /libpath:../../lib /libpath:Release libdbxml22.lib libdb43.lib xerces-c_2.lib libxquery12.lib Pathan.lib /libpath:../../xquery-1.2.0/build_win32/Release /libpath:../../db-4.3.29/build_win32/Release /nologo /subsystem:console /machine:I386 /nodefaultlib:"libcmt" /libpath:../../pathan/lib /libpath:../../xerces-c-src/lib /libpath:../../xerces-c-src/build/win32/vc6/release

!ELSEIF  "$(CFG)" == "dbxml_query_runner - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".Debug\dbxml_query_runner"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".Debug\dbxml_query_runner"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MDd /W3 /GX /Zi /Od /I "." /I "../include" /I "../src/dbxml" /I "../../xquery-1.2.0/include" /I "../../pathan/include" /I "../../db-4.3.29/include" /I "../../db-4.3.29/build_win32" /I "../../db-4.3.29/dbinc" /I "../../xerces-c-src/include"  /I "../../xerces-c-src/src" /I "../../include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /libpath:../../lib /libpath:Debug libdbxml22d.lib libdb43d.lib xerces-c_2d.lib libxquery12d.lib PathanD.lib /libpath:../../pathan/lib /libpath:../../xquery-1.2.0/build_win32/Debug /libpath:../../db-4.3.29/build_win32/Debug /nologo /subsystem:console /pdb:./Debug/dbxml_query_runner.pdb /debug /machine:I386 /nodefaultlib:"libcmtd" /fixed:no /libpath:../../xerces-c-src/lib /libpath:../../xerces-c-src/build/win32/vc6/debug

!ENDIF 

# Begin Target

# Name "dbxml_query_runner - Win32 Release"
# Name "dbxml_query_runner - Win32 Debug"
# Begin Source File

SOURCE=..\src\utils\query_runner\QueryRunner.cpp
# End Source File
# End Target
# End Project
