!ifdef MAXCOMPRESSION

SetCompressor /FINAL /SOLID lzma
SetCompressorDictSize 64

FileBufSize 256

!endif

VIProductVersion "${MG_VERSION}"
VIAddVersionKey "FileVersion" "1.0.0.0"
VIAddVersionKey "CompanyName" "Open Source Geospatial Foundation"
VIAddVersionKey "FileDescription" "Installer Bootstrapper package for MapGuide Open Source"
VIAddVersionKey "LegalCopyright" "2010 Open Source Geospatial Foundation"

!ifndef CULTURE
!define CULTURE "en-us"
!endif

!define INSTALLER_OUTPUT "${INSTALLER_ROOT}\Output\${CULTURE}"

OutFile "${INSTALLER_OUTPUT}\${OUTNAME}.exe"

SilentInstall silent

Icon "${INSTALLER_ROOT}\Support\Graphics\OSGeo.ico"

Function .onInit
	System::Call 'kernel32::CreateMutexA(i 0, i 0, t "myMutex") i .r1 ?e'
	Pop $R0
	
	StrCmp $R0 0 +3
		MessageBox MB_OK|MB_ICONEXCLAMATION "The installer is already running."
		Abort
FunctionEnd

Section Main
	Banner::show /NOUNLOAD "Extracting files. Please Wait"
	Banner::getWindow /NOUNLOAD
	
	SetOutPath $TEMP
	SetOverwrite On
	File "${INSTALLER_OUTPUT}\${OUTNAME}.msi"
	File "${INSTALLER_OUTPUT}\setup.exe"
!if ${CPU} = "x64"
	File /r "${INSTALLER_OUTPUT}\vcredist_x64"
!else
	File /r "${INSTALLER_OUTPUT}\vcredist_x86"
!endif
	Banner::destroy
	ExecWait '"$OUTDIR\setup.exe"'
SectionEnd