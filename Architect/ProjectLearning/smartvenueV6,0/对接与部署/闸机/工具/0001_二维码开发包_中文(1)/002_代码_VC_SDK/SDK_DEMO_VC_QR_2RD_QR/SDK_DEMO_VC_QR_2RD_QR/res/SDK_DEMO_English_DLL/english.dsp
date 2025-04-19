# Microsoft Developer Studio Project File - Name="english" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=english - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "english.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "english.mak" CFG="english - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "english - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "english - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "english - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "d:\Compile\ENGLISHRelease"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "english - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "d:\Compile\ENGLISHDEBUG"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\bin_VR\english.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "english - Win32 Release"
# Name "english - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\english.cpp
# End Source File
# Begin Source File

SOURCE=.\english.def
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Vcard.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\english.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\akregator.ico
# End Source File
# Begin Source File

SOURCE=".\res\Application Starting.cur"
# End Source File
# Begin Source File

SOURCE=.\res\applixware.ico
# End Source File
# Begin Source File

SOURCE=.\res\back.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_l.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_TREE.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\build.bmp
# End Source File
# Begin Source File

SOURCE=.\res\camera.ico
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\default.bmp
# End Source File
# Begin Source File

SOURCE=.\res\edit.bmp
# End Source File
# Begin Source File

SOURCE=.\res\english.rc2
# End Source File
# Begin Source File

SOURCE=".\res\exclamation mark.ico"
# End Source File
# Begin Source File

SOURCE=.\res\HTML.ico
# End Source File
# Begin Source File

SOURCE=.\res\I.ico
# End Source File
# Begin Source File

SOURCE=.\res\I1.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon8.ico
# End Source File
# Begin Source File

SOURCE=.\res\imageList.bmp
# End Source File
# Begin Source File

SOURCE=.\res\images.bmp
# End Source File
# Begin Source File

SOURCE=.\res\keys.ico
# End Source File
# Begin Source File

SOURCE=.\res\PAUSE_ENABLE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\PLAY_DISABLE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\PLAY_ENABLE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\safer.ico
# End Source File
# Begin Source File

SOURCE=.\res\SDK_DEMO_VC.ico
# End Source File
# Begin Source File

SOURCE=.\res\ShutDown.ico
# End Source File
# Begin Source File

SOURCE=.\res\step_disable.ico
# End Source File
# Begin Source File

SOURCE=.\res\STOP.ICO
# End Source File
# Begin Source File

SOURCE=.\res\STOP_DISABLE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\sysset_image.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolBar_CAI.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolBar_new.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_res.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbox_hc.ico
# End Source File
# Begin Source File

SOURCE=.\res\ToolBoxDemoDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\tools_page1hc_01.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page1hc_02.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page1hc_03.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page1hc_04.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page1hc_05.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page1hc_06.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page1hc_07.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page1hc_08.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page1hc_09.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tools_page1hc_10.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Torch.ico
# End Source File
# Begin Source File

SOURCE=.\res\Vcard.ico
# End Source File
# Begin Source File

SOURCE=.\res\VcardDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
