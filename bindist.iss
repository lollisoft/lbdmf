; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=lbDMF Binary Samples
AppVerName=lbDMF Binary Samples 0.4.0
AppPublisher=Lothar Behrens
AppPublisherURL=http://www.lollisoft.de
AppSupportURL=http://www.sourceforge.net/projects/lbdmf
AppUpdatesURL=http://www.sourceforge.net/projects/lbdmf
DefaultDirName={sd}\lbDMF
DefaultGroupName=lbDMF
; uncomment the following line if you want your installation to run on NT 3.51 too.
; MinVersion=4,3.51

[Tasks]
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; MinVersion: 4,4

[Files]
Source: "Q:\Develop\Projects\bin\wxwrapper.exe"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "Q:\Develop\Projects\CPP\watcomenv.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "Q:\Develop\Projects\CPP\binsample.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "Q:\Develop\Projects\dll\mspdb60.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\CPP\Doc\*.*"; DestDir: "{app}\Doc"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;
; --- My current binary only file
Source: "Q:\Develop\Projects\dll\lb*.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\plugins\*.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;

[Icons]
Name: "{group}\lbDMF"; Filename: "{app}\binsample.bat"; WorkingDir: "{app}"
Name: "{userdesktop}\lbDMF"; Filename: "{app}\binsample.bat"; MinVersion: 4,4; Tasks: desktopicon; WorkingDir: "{app}"
Name: "{userdesktop}\lbDMF Help"; Filename: "{app}\Doc\html\index.html"; MinVersion: 4,4; Tasks: desktopicon; WorkingDir: "{app}\develop\projects\cpp\BaseDevelopment"

[Run]
;Filename: "{app}\watcomenv.bat"; Description: "Launch My Program"; Flags: shellexec postinstall skipifsilent

