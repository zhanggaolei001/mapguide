# Microsoft Developer Studio Project File - Name="PathanDll" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=PathanDll - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PathanDll.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PathanDll.mak" CFG="PathanDll - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PathanDll - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "PathanDll - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PathanDll - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "../../../bin"
# PROP BASE Intermediate_Dir "ReleaseDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../bin"
# PROP Intermediate_Dir "ReleaseDLL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PATHANDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../../xerces-c-src/src" /I "../../include" /I "../../src" /D "NDEBUG" /D "PROJ_PATHAN" /D "_WINDOWS" /D "_USRDLL" /D "WIN32" /D "_UNICODE" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 xerces-c_2.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"../../../bin/Pathan.dll" /implib:"../../../lib/Pathan.lib" /libpath:"../../../xerces-c-src/Build/Win32/VC6/Release" /libpath:"../../../lib"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "PathanDll - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "../../../bin/debug"
# PROP BASE Intermediate_Dir "DebugDLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../bin/debug"
# PROP Intermediate_Dir "DebugDLL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PATHANDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /I "../../../xerces-c-src/src" /I "../../include" /I "../../src" /D "_DEBUG" /D "PROJ_PATHAN" /D "_WINDOWS" /D "_USRDLL" /D "WIN32" /D "_UNICODE" /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 xerces-c_2d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"../../../bin/debug/PathanD.dll" /implib:"../../../lib/PathanD.lib" /pdbtype:sept /libpath:"../../../xerces-c-src/Build/Win32/VC6/Debug" /libpath:"../../../lib"

!ENDIF 

# Begin Target

# Name "PathanDll - Win32 Release"
# Name "PathanDll - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "context"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\include\pathan\DocumentCache.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\context\DocumentCacheImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal\context\DocumentCacheImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\DynamicContext.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\context\DynamicContextImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal\context\DynamicContextImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\StaticContext.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\context\XPath2ContextImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/context\XPath2ContextImpl.hpp
# End Source File
# End Group
# Begin Group "utils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\utils\ContextUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal\utils\ContextUtils.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\Date.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\Date.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\DateUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\DateUtils.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\NumUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\NumUtils.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\PathanPlatformUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\PathanPlatformUtils.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\PrintDataItemTree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal\utils\PrintDataItemTree.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\URIResolver.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\XPath2NSUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\XPath2NSUtils.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\utils\XPath2Utils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\XPath2Utils.hpp
# End Source File
# End Group
# Begin Group "dataItem"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\dataItem\AtomizeResult.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\AtomizeResult.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItem.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemCastableAs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemCastableAs.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemCastAs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemCastAs.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemContextItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemContextItem.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemFor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemFor.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemFunction.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemIf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemIf.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemInstanceOf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemInstanceOf.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemLiteral.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemLiteral.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemNav.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemNav.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemOperator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemOperator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemParenthesizedExpr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemParenthesizedExpr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemQuantifiedExpr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemQuantifiedExpr.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemSequence.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemSequence.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemStep.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemStep.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemTreatAs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemTreatAs.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\DataItemVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\DataItemVariable.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\EmptyResult.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\EmptyResult.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\LazySequenceResult.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\LazySequenceResult.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\Result.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\Result.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\ResultBuffer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\ResultBuffer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\ResultBufferImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\ResultBufferImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\ResultImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\ResultImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\SequenceResult.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\SequenceResult.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\SingleResult.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\SingleResult.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\SortIntoDocumentOrderResult.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\SortIntoDocumentOrderResult.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\dataItem\StaticResolutionContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\dataItem\StaticResolutionContext.hpp
# End Source File
# End Group
# Begin Group "DOMutils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\DOMutils\UTF8Str.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal\utils\UTF8Str.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\DOMutils\XMLChCompare.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/DOMutils\XMLChCompare.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\DOMutils\XStr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/DOMutils\XStr.hpp
# End Source File
# End Group
# Begin Group "exceptions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\exceptions\CannotHappenException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\ContextException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\DataItemException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\exceptions\DSLException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\DSLException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\FunctionException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\IllegalArgumentException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\exceptions\InvalidLexicalSpaceException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\ItemException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\exceptions\MiscException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\NamespaceLookupException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\NavigationException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\exceptions\SequenceException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\StaticAnalysisException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\TypeNotFoundException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\VariableStoreException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\XMLParseException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\exceptions\XPath2ErrorException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\exceptions\XPath2TypeCastException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\exceptions\XPath2TypeMatchException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\exceptions\XPathLexerException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\exceptions\XPathParseException.hpp
# End Source File
# End Group
# Begin Group "factory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\factory\DatatypeFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\factory\PathanFactoryImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/factory\DatatypeFactory.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\factory\DatatypeFactoryTemplate.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\factory\FuncFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/factory\FuncFactory.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\factory\FuncFactoryTemplate.hpp
# End Source File
# End Group
# Begin Group "functionAPI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\functionAPI\AggregateFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functionAPI\AggregateFunction.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functionAPI\ConstantFoldingFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functionAPI\ConstantFoldingFunction.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functionAPI\DatatypeLookup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functionAPI\DatatypeLookup.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functionAPI\FunctionLookup.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functionAPI\FunctionLookupImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functionAPI\FunctionLookupImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functionAPI\NumericFunction.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functionAPI\NumericFunction.hpp
# End Source File
# End Group
# Begin Group "lexer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\lexer\FlexLexer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\lexer\LexerDOMStringStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\lexer\LexerDOMStringStream.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\lexer\XPath2Lexer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\lexer\XPath2Lexer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\lexer\XPath2Lexer.lex
# End Source File
# Begin Source File

SOURCE=..\..\src\lexer\XPathFlexLexer.hpp
# End Source File
# End Group
# Begin Group "items"

# PROP Default_Filter ""
# Begin Group "impl"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\items\impl\ATAnySimpleTypeImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATAnySimpleTypeImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATAnyURIOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATAnyURIOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATBase64BinaryOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATBase64BinaryOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATBooleanOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATBooleanOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATDateOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATDateOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATDateTimeOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATDateTimeOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATDecimalOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATDecimalOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATDoubleOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATDoubleOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATDurationOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATDurationOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATFloatOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATFloatOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATGDayOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATGDayOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATGMonthDayOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATGMonthDayOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATGMonthOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATGMonthOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATGYearMonthOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATGYearMonthOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATGYearOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATGYearOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATHexBinaryOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATHexBinaryOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATNotationOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATNotationOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATQNameOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATQNameOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATStringOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATStringOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATTimeOrDerivedImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATTimeOrDerivedImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATUntypedAtomicImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\ATUntypedAtomicImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\NodeImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\impl\NodeImpl.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src\items\AnyAtomicType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\AnyAtomicType.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\AnyAtomicTypeConstructor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\AnyAtomicTypeConstructor.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATAnySimpleType.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATAnyURIOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATBase64BinaryOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATBooleanOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATDateOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATDateTimeOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATDecimalOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATDoubleOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\ATDurationOrDerived.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATDurationOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATFloatOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATGDayOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATGMonthDayOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATGMonthOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATGYearMonthOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATGYearOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATHexBinaryOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATNotationOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\ATQNameConstructor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATQNameConstructor.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATQNameOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATStringOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATTimeOrDerived.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\ATUntypedAtomic.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ATUntypedAtomic.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\DateOrTimeType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\DateOrTimeType.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\Item.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\Item.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\ItemConstructor.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\Node.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\Node.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\Numeric.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\Numeric.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\items\Timezone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\Timezone.hpp
# End Source File
# End Group
# Begin Group "navigation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\navigation\NodeTest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\AncestorAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\AncestorAxis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\AncestorOrSelfAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\AncestorOrSelfAxis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\AttributeAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\AttributeAxis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\Axis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\ChildAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\ChildAxis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\DescendantAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\DescendantAxis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\DescendantOrSelfAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\DescendantOrSelfAxis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\FollowingAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\FollowingAxis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\FollowingSiblingAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\FollowingSiblingAxis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\NamespaceAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\NamespaceAxis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\ParentAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\ParentAxis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\PrecedingAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\PrecedingAxis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\PrecedingSiblingAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\PrecedingSiblingAxis.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\navigation\SelfAxis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/navigation\SelfAxis.hpp
# End Source File
# End Group
# Begin Group "parser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\parser\QName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/parser\QName.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\parser\VariableBinding.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal/parser\VariableBinding.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\parser\XPath2Parser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\parser\XPath2Parser.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\parser\XPath2Parser.y
# End Source File
# Begin Source File

SOURCE=..\..\src\parser\XPath2ParserControl.hpp
# End Source File
# End Group
# Begin Group "simpleVariables"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\include\pathan\simpleVariables\Scope.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\simpleVariables\VarHashEntry.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\simpleVariables\VarHashEntryImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal\simpleVariables\VarHashEntryImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\VariableStore.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\simpleVariables\VariableStoreTemplate.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\simpleVariables\VariableTypeStore.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\simpleVariables\VarStoreImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\simpleVariables\VarStoreImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\simpleVariables\VarTypeStoreImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\simpleVariables\VarTypeStoreImpl.hpp
# End Source File
# End Group
# Begin Group "Sequence"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\include\pathan\ReferenceCounted.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\sequence\Sequence.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\Sequence.hpp
# End Source File
# End Group
# Begin Group "schema"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\schema\SequenceType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\SequenceType.hpp
# End Source File
# End Group
# Begin Group "collations"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\collations\CodepointCollation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal\collations\CodepointCollation.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\Collation.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\collations\CollationImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal\collations\CollationImpl.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\collations\UCANormalizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\collations\UCANormalizer.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\collations\UCANormalizer1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\collations\UCANormalizer2.cpp
# End Source File
# End Group
# Begin Group "mapm"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\include\pathan\internal\m_apm.h
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\m_apm.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\m_apm_lc.h
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm5sin.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_add.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_cpi.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_div.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_exp.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_fam.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_fft.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_flr.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_fpf.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_gcd.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_lg2.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_lg3.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_log.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_mt.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_mul.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_pow.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_rcp.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_rnd.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_set.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapm_sin.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmasin.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmasn0.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmcbrt.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmcnst.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmfact.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmfmul.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmgues.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmhasn.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmhsin.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmipwr.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmistr.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmpwr2.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmrsin.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmsqrt.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmstck.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmutil.c
# End Source File
# Begin Source File

SOURCE=..\..\src\mapm\mapmutl2.c
# End Source File
# End Group
# Begin Group "operators"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\operators\And.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\And.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\ArithmeticOperator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\ArithmeticOperator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\ComparisonOperator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\ComparisonOperator.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\Divide.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\Divide.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\Equals.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\Equals.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\Except.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\Except.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\GeneralComp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\GeneralComp.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\GreaterThan.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\GreaterThan.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\GreaterThanEqual.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\GreaterThanEqual.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\IntegerDivide.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\IntegerDivide.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\Intersect.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\Intersect.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\LessThan.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\LessThan.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\LessThanEqual.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\LessThanEqual.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\Minus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\Minus.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\Mod.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\Mod.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\Multiply.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\Multiply.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\NodeComparison.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\NodeComparison.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\NotEquals.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\NotEquals.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\Or.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\Or.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\OrderComparison.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\OrderComparison.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\Plus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\Plus.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\Range.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\Range.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\TotalOrderComparison.cpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\TotalOrderComparison.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\UnaryMinus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\UnaryMinus.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\operators\Union.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\operators\Union.hpp
# End Source File
# End Group
# Begin Group "functions"

# PROP Default_Filter ""
# Begin Group "dateTimeFunctions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionAdjustDateTimeToTimezone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionAdjustDateTimeToTimezone.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionAdjustDateToTimezone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionAdjustDateToTimezone.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionAdjustTimeToTimezone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionAdjustTimeToTimezone.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionDayFromDate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionDayFromDate.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionDayFromDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionDayFromDateTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionDaysFromDuration.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionDaysFromDuration.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionHoursFromDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionHoursFromDateTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionHoursFromDuration.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionHoursFromDuration.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionHoursFromTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionHoursFromTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionMinutesFromDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionMinutesFromDateTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionMinutesFromDuration.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionMinutesFromDuration.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionMinutesFromTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionMinutesFromTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionMonthFromDate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionMonthFromDate.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionMonthFromDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionMonthFromDateTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionMonthsFromDuration.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionMonthsFromDuration.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionSecondsFromDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionSecondsFromDateTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionSecondsFromDuration.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionSecondsFromDuration.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionSecondsFromTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionSecondsFromTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionTimezoneFromDate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionTimezoneFromDate.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionTimezoneFromDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionTimezoneFromDateTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionTimezoneFromTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionTimezoneFromTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionYearFromDate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionYearFromDate.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionYearFromDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionYearFromDateTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\dateTimeFunctions\FunctionYearsFromDuration.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionYearsFromDuration.hpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src\functions\FunctionAbs.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionAbs.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionAvg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionAvg.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionBaseURI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionBaseURI.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionBoolean.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionBoolean.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionCeiling.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionCeiling.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionCodepointEqual.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionCodepointEqual.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionCodepointsToString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionCodepointsToString.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionCollection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionCollection.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionCompare.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionCompare.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionConcat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionConcat.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionConstructor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionConstructor.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionContains.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionContains.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionCount.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionCount.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionCurrentDate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionCurrentDate.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionCurrentDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionCurrentDateTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionCurrentTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionCurrentTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionData.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionDateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionDateTime.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionDeepEqual.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionDeepEqual.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionDefaultCollation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionDefaultCollation.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionDistinctValues.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionDistinctValues.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionDoc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionDoc.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionDocAvailable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionDocAvailable.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionDocumentURI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionDocumentURI.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionEmpty.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionEmpty.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionEndsWith.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionEndsWith.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionError.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionError.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionEscapeURI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionEscapeURI.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionExactlyOne.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionExactlyOne.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionExists.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionExists.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionFalse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionFalse.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionFloor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionFloor.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionId.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionId.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionIdref.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionIdref.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionImplicitTimezone.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionImplicitTimezone.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionIndexOf.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionIndexOf.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionInScopePrefixes.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionInScopePrefixes.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionInsertBefore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionInsertBefore.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionLang.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionLang.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionLast.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionLast.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionLocalname.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionLocalname.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionLocalNameFromQName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionLocalNameFromQName.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionLowerCase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionLowerCase.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionMatches.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionMatches.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionMax.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionMax.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionMin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionMin.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionName.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionNamespaceUri.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionNamespaceUri.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionNamespaceURIForPrefix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionNamespaceURIForPrefix.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionNamespaceURIFromQName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionNamespaceURIFromQName.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionNilled.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionNilled.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionNodeName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionNodeName.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionNormalizeSpace.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionNormalizeSpace.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionNormalizeUnicode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionNormalizeUnicode.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionNot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionNot.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionNumber.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionNumber.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionOneOrMore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionOneOrMore.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionPosition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionPosition.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionPrefixFromQName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionPrefixFromQName.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionQName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionQName.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionRemove.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionRemove.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionReplace.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionReplace.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionResolveQName.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionResolveQName.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionResolveURI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionResolveURI.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionReverse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionReverse.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionRoot.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionRoot.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionRound.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionRound.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionRoundHalfToEven.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionRoundHalfToEven.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionStartsWith.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionStartsWith.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionStaticBaseURI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionStaticBaseURI.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionString.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionStringJoin.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionStringJoin.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionStringLength.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionStringLength.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionStringToCodepoints.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionStringToCodepoints.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionSubsequence.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionSubsequence.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionSubstring.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionSubstring.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionSubstringAfter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionSubstringAfter.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionSubstringBefore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionSubstringBefore.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionSum.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionSum.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionTokenize.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionTokenize.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionTrace.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionTrace.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionTranslate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionTranslate.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionTrue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionTrue.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionUnordered.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionUnordered.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionUpperCase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionUpperCase.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\functions\FunctionZeroOrOne.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\functions\FunctionZeroOrOne.hpp
# End Source File
# End Group
# Begin Group "validators"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\validators\AnyAtomicTypeDatatypeValidator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal\AnyAtomicTypeDatatypeValidator.hpp
# End Source File
# End Group
# Begin Group "dom-extensions"

# PROP Default_Filter ""
# Begin Group "impl No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\src\dom-extensions\impl\PathanBuilderImpl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\impl\PathanBuilderImpl.hpp"
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\impl\PathanDocumentImpl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\impl\PathanDocumentImpl.hpp"
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\impl\PathanExpressionImpl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\include\pathan\internal/dom-extensions\PathanExpressionImpl.hpp"
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\impl\PathanNSResolverImpl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\include\pathan\internal/dom-extensions\PathanNSResolverImpl.hpp"
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\impl\PathanXMLGrammarPoolImpl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\impl\PathanXMLGrammarPoolImpl.hpp"
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\impl\XPathNamespaceImpl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\impl\XPathNamespaceImpl.hpp"
# End Source File
# End Group
# Begin Source File

SOURCE="..\..\src\dom-extensions\PathanEngine.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\PathanEngine.hpp
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\PathanException.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\PathanException.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\PathanExpression.hpp
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\PathanImplementation.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\PathanImplementation.hpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\PathanNSResolver.hpp
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\XPath2NodeSerializer.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\XPath2NodeSerializer.hpp
# End Source File
# Begin Source File

SOURCE="..\..\src\dom-extensions\XPath2Result.cpp"
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\XPath2Result.hpp
# End Source File
# End Group
# Begin Group "memoryManager"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\memoryManager\BaseMemoryManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal\BaseMemoryManager.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\memoryManager\ProxyMemoryManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal\ProxyMemoryManager.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\memoryManager\StringPool.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\XPath2MemoryManager.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\memoryManager\XPath2MemoryManagerImpl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\include\pathan\internal\XPath2MemoryManagerImpl.hpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\pathan\Pathan.hpp
# End Source File
# Begin Source File

SOURCE=..\..\src\config\pathan_config.h
# End Source File
# Begin Source File

SOURCE=..\..\src\config\pathan_config_win32.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
