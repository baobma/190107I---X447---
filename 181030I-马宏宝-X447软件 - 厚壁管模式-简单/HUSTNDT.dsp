# Microsoft Developer Studio Project File - Name="HUSTNDT" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=HUSTNDT - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HUSTNDT.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HUSTNDT.mak" CFG="HUSTNDT - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HUSTNDT - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HUSTNDT - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HUSTNDT - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 libjpeg.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "HUSTNDT - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libjpeg.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "HUSTNDT - Win32 Release"
# Name "HUSTNDT - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ARDSET.cpp
# End Source File
# Begin Source File

SOURCE=.\DataBuf.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSaveFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSaveStyle.cpp
# End Source File
# Begin Source File

SOURCE=.\DataSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GobalData.cpp
# End Source File
# Begin Source File

SOURCE=.\hooseFileDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HUSTNDT.cpp
# End Source File
# Begin Source File

SOURCE=.\HUSTNDT.rc
# End Source File
# Begin Source File

SOURCE=.\HUSTNDTDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\HUSTNDTView.cpp
# End Source File
# Begin Source File

SOURCE=.\IntialSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\IOStatusDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MParDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PARSET.cpp
# End Source File
# Begin Source File

SOURCE=.\PlyData.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintReportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RbhUsb20.cpp
# End Source File
# Begin Source File

SOURCE=.\ReportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SampleCard.cpp
# End Source File
# Begin Source File

SOURCE=.\ScarData.cpp
# End Source File
# Begin Source File

SOURCE=.\ShowSet.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleCompressData.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleDataSave.cpp
# End Source File
# Begin Source File

SOURCE=.\SRoomSample.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticPIC.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StrParDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StyleForFloordata.cpp
# End Source File
# Begin Source File

SOURCE=.\TestFuc.cpp
# End Source File
# Begin Source File

SOURCE=.\TestSampleControl.cpp
# End Source File
# Begin Source File

SOURCE=.\TLine78data.cpp
# End Source File
# Begin Source File

SOURCE=.\TlineSv3.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveShow.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ADCARD.H
# End Source File
# Begin Source File

SOURCE=.\ADCARD1.H
# End Source File
# Begin Source File

SOURCE=.\ARDSET.h
# End Source File
# Begin Source File

SOURCE=.\DataBuf.h
# End Source File
# Begin Source File

SOURCE=.\DataSaveFactory.h
# End Source File
# Begin Source File

SOURCE=.\DataSaveStyle.h
# End Source File
# Begin Source File

SOURCE=.\DataSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\enmuHead.h
# End Source File
# Begin Source File

SOURCE=.\GobalData.h
# End Source File
# Begin Source File

SOURCE=.\hooseFileDlg.h
# End Source File
# Begin Source File

SOURCE=.\HUSTNDT.h
# End Source File
# Begin Source File

SOURCE=.\HUSTNDTDoc.h
# End Source File
# Begin Source File

SOURCE=.\HUSTNDTView.h
# End Source File
# Begin Source File

SOURCE=.\IntialSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\IOStatusDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MParDlg.h
# End Source File
# Begin Source File

SOURCE=.\MsgDlg.h
# End Source File
# Begin Source File

SOURCE=.\PARSET.h
# End Source File
# Begin Source File

SOURCE=.\PlyData.h
# End Source File
# Begin Source File

SOURCE=.\PrintReportDlg.h
# End Source File
# Begin Source File

SOURCE=.\RbhUsb20.h
# End Source File
# Begin Source File

SOURCE=.\ReportDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SampleCard.h
# End Source File
# Begin Source File

SOURCE=.\ScarData.h
# End Source File
# Begin Source File

SOURCE=.\ShowSet.h
# End Source File
# Begin Source File

SOURCE=.\SimpleCompressData.h
# End Source File
# Begin Source File

SOURCE=.\SimpleDataSave.h
# End Source File
# Begin Source File

SOURCE=.\SRoomSample.h
# End Source File
# Begin Source File

SOURCE=.\StaticPIC.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StrParDlg.h
# End Source File
# Begin Source File

SOURCE=.\StyleForFloordata.h
# End Source File
# Begin Source File

SOURCE=.\TestFuc.h
# End Source File
# Begin Source File

SOURCE=.\TestSampleControl.h
# End Source File
# Begin Source File

SOURCE=.\TLine78data.h
# End Source File
# Begin Source File

SOURCE=.\TlineSv3.h
# End Source File
# Begin Source File

SOURCE=.\WaveShow.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BKGRD.bmp
# End Source File
# Begin Source File

SOURCE=.\res\HUSTNDT.ico
# End Source File
# Begin Source File

SOURCE=.\res\HUSTNDT.rc2
# End Source File
# Begin Source File

SOURCE=.\res\HUSTNDTDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\Adcard.lib
# End Source File
# Begin Source File

SOURCE=.\Adcard1.lib
# End Source File
# End Target
# End Project
