; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=lbDMF Development Environment
AppVerName=lbDMF Development Environment 1.1.1
OutputBaseFilename=lbDMF-Source-1.1.1
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
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; MinVersion: 4,4

[Files]
; Source code
Source: "dist\dist_iss_src\*.*"; DestDir: "{app}"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;

; WGet tool
Source: "dist\dist_iss\*.*"; DestDir: "{app}"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;

; MinGW Get tool
Source: "dist\dist_iss_MinGW_Get\*.*"; DestDir: "{app}\Develop\Tools\MinGW"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;

; wxWidgets configuration update
Source: "wxWidgets-config.gcc"; DestDir: "{app}"; CopyMode: alwaysoverwrite;

; Special binary files
Source: "dist\dist_iss_psqlodbc\psqlodbc.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "dist\dist_iss_BinBuildTools\test.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite

Source: "Database\*.*"; DestDir: "{app}\Database"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;
Source: "watcomenv.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "buildwxWidgets_MinGW.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite;
Source: "installODBC.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite;
Source: "installMinGW.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite;
Source: "Test\GUI\wxWrapper\splash.png"; DestDir: "{app}\Develop\Projects\CPP\BaseDevelopment"; CopyMode: alwaysoverwrite;
Source: "Test\GUI\wxWrapper\toolbarimages\*.*"; DestDir: "{app}\Develop\Projects\CPP\BaseDevelopment\toolbarimages"; CopyMode: alwaysoverwrite;

Source: "Test\GUI\wxWrapper\lbdmf.ico"; DestDir: "{app}"; CopyMode: alwaysoverwrite;

Source: "activateACE.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite;
Source: "InstallACE.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite;

; Patches
Source: "TAO.GNUmakefile"; DestDir: "{app}"; CopyMode: alwaysoverwrite;
Source: "TAO.orbsvcs.orbsvcs.GNUmakefile"; DestDir: "{app}"; CopyMode: alwaysoverwrite;
; MinGW patches
;Source: "commctrl-wxWidgets-patch.h"; DestDir: "{app}"; CopyMode: alwaysoverwrite;
Source: "w32api-Wcpp-patch.h"; DestDir: "{app}"; CopyMode: alwaysoverwrite;

[Icons]
Name: "{group}\lbDMF Develop"; IconFilename: "{app}\lbdmf.ico"; Filename: "{app}\watcomenv.bat"; WorkingDir: "{app}\develop\projects\cpp\BaseDevelopment"
Name: "{userdesktop}\lbDMF Develop"; IconFilename: "{app}\lbdmf.ico"; Filename: "{app}\watcomenv.bat"; MinVersion: 4,4; Tasks: desktopicon; WorkingDir: "{app}\develop\projects\cpp\BaseDevelopment"
;Name: "{userdesktop}\lbDMF Help"; Filename: "{app}\develop\projects\cpp\Doc\html\index.html"; MinVersion: 4,4; Tasks: desktopicon; WorkingDir: "{app}\develop\projects\cpp\BaseDevelopment"

[Run]
;Filename: "{app}\watcomenv.bat"; Description: "Launch My Program"; Flags: shellexec postinstall skipifsilent
Filename: "http://www.lollisoft.de/index.php?module=xarpages&func=display&pid=24"; Flags: shellexec
Filename: "{app}\installODBC.bat"; Description: "Install ODBC driver settings"; Flags: shellexec postinstall unchecked
Filename: "{app}\activateACE.bat"; Description: "Get and build ACE framework (ca. 2.4GByte disk usage!)"; Flags: shellexec postinstall unchecked
Filename: "{app}\buildwxWidgets_MinGW.bat"; Description: "Get MinGW, wxWidgets (and ACE when flagged) and build it"; Flags: shellexec postinstall
