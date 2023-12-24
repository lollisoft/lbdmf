; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=lbDMF Binary Build Tools
AppVerName=lbDMF Binary Build Tools 1.3.3-vc
OutputBaseFilename=lbDMF-BinbuildTools-1.3.3-vc
AppPublisher=Lothar Behrens
AppPublisherURL=http://www.lollisoft.de
AppSupportURL=http://www.sourceforge.net/projects/lbdmf
AppUpdatesURL=http://www.sourceforge.net/projects/lbdmf
DefaultDirName={sd}\lbDMF
DefaultGroupName=lbDMF
LicenseFile=license.txt
; uncomment the following line if you want your installation to run on NT 3.51 too.
; MinVersion=4,3.51

[Tasks]
;Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; MinVersion: 4,4

[Files]
Source: "dist\dist_iss_BinBuildTools\test.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\flex.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\bison.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\bison.simple"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\gawk.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\sh.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\ssh.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\cp.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\cat.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\echo.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\rm.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\mkdir.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\unixfind.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\grep.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\cygcrypto-1.0.0.dll"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\cygintl-8.dll"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\cygpcre-0.dll"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\cygwin1.dll"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\cygz.dll"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\cygiconv-2.dll"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\cygreadline7.dll"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\make.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\cygncursesw-10.dll"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\cyggcc_s-1.dll"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
;Source: "Q:\Develop\Projects\dll\mspdb60.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;

Source: "dist\dist_iss_BinBuildTools\cygattr-1.dll"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\ls.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "dist\dist_iss_BinBuildTools\pwd.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite

Source: "dist\dist_iss_BinBuildTools\Graphviz2.26.3\*.*"; DestDir: "{app}\Develop\Tools\Graphviz2.26.3"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;
Source: "dist\dist_iss_BinBuildTools\doxygen\*.*"; DestDir: "{app}\Develop\Tools\doxygen"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;


;Dependency (VC Build)
Source: "dist\dist_iss_MkMk\mkmk.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite


[Icons]
;Name: "{group}\lbDMF Develop"; Filename: "{app}\watcomenv.bat"; WorkingDir: "{app}\develop\projects\cpp\BaseDevelopment"
;Name: "{userdesktop}\lbDMF Develop"; Filename: "{app}\watcomenv.bat"; MinVersion: 4,4; Tasks: desktopicon; WorkingDir: "{app}\develop\projects\cpp\BaseDevelopment"
;Name: "{userdesktop}\lbDMF Help"; Filename: "{app}\develop\projects\cpp\Doc\html\index.html"; MinVersion: 4,4; Tasks: desktopicon; WorkingDir: "{app}\develop\projects\cpp\BaseDevelopment"

[Run]
;Filename: "{app}\watcomenv.bat"; Description: "Launch My Program"; Flags: shellexec postinstall skipifsilent

