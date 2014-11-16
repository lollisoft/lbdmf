; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=lbDMF XSLT Patch Distribution
AppVerName=lbDMF XSLT Patch Distribution 1.0.4-final-patch_1
OutputBaseFilename=lbDMF-XSLTPatchDistribution-1.0.4-final-patch_1
AppPublisher=Lothar Behrens
AppPublisherURL=http://www.lollisoft.de
AppSupportURL=http://www.sourceforge.net/projects/lbdmf
AppUpdatesURL=http://www.sourceforge.net/projects/lbdmf
DefaultDirName={sd}\lbDMF
DefaultGroupName=lbDMF
LicenseFile=license-templatedist.txt
; uncomment the following line if you want your installation to run on NT 3.51 too.
; MinVersion=4,3.51

[Tasks]
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; MinVersion: 4,4

[Files]
Source: "AppDevelopmentDemo\DynamicApp\XSLT_Templates\*.*"; DestDir: "{app}\XSLT"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;
; --- My current binary only file

[Icons]

[Run]
;Filename: "{app}\installODBC.bat"; Description: "Install ODBC driver settings"; Flags: shellexec postinstall

