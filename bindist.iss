; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=lbDMF Binary Samples
AppVerName=lbDMF Binary Samples 1.0.4-stable-rc2
OutputBaseFilename=lbDMF-BinSamples-1.0.4-stable-rc2
AppPublisher=Lothar Behrens
AppPublisherURL=http://www.lollisoft.de
AppSupportURL=http://www.sourceforge.net/projects/lbdmf
AppUpdatesURL=http://www.sourceforge.net/projects/lbdmf
DefaultDirName={sd}\lbDMF
DefaultGroupName=lbDMF
LicenseFile=license-bindist.txt
; uncomment the following line if you want your installation to run on NT 3.51 too.
; MinVersion=4,3.51

[Tasks]
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; MinVersion: 4,4

[Files]
Source: "Q:\Develop\Projects\CPP\installODBC.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "Q:\Develop\Projects\bin\wxwrapper.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "Q:\Develop\Projects\bin\xsltproc.exe"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "Q:\Develop\Projects\CPP\Test\GUI\wxWrapper\splash.png"; DestDir: "{app}\Develop\Projects\bin"; CopyMode: alwaysoverwrite
Source: "Q:\Develop\Projects\CPP\Test\GUI\wxWrapper\splash.png"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "Q:\Develop\Projects\CPP\watcomenv.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "Q:\Develop\Projects\CPP\binsample.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "Q:\Develop\Projects\dll\mspdb60.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\psqlodbc.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\CPP\Database\*.*"; DestDir: "{app}\Database"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;
Source: "Q:\develop\Projects\CPP\Test\GUI\wxWrapper\toolbarimages\*.xpm"; DestDir: "{app}\toolbarimages"; CopyMode: alwaysoverwrite;
Source: "Q:\develop\Projects\CPP\Test\GUI\wxWrapper\toolbarimages\*.png"; DestDir: "{app}\toolbarimages"; CopyMode: alwaysoverwrite;
;Source: "Q:\develop\Projects\CPP\BaseDevelopment\MetaApp-Bindist.mad"; DestDir: "{app}"; DestName: "MetaApp.mad"; CopyMode: alwaysoverwrite;
Source: "Q:\develop\Projects\CPP\AppDevelopmentDemo\DynamicApp\XSLT_Templates\*.*"; DestDir: "{app}\XSLT"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;
Source: "Q:\develop\Projects\CPP\AppDevelopmentDemo\DynamicApp\UMLSamples\*.*"; DestDir: "{app}\UMLSamples\"; CopyMode: alwaysoverwrite; Flags: recursesubdirs;
Source: "Q:\develop\Projects\CPP\AppDevelopmentDemo\DynamicApp\Doc\ApplicationprototypingDokumentation.pdf"; DestDir: "{app}\"; CopyMode: alwaysoverwrite;
; --- My current binary only file

Source: "Q:\Develop\Projects\plugins\lbCryptoStream.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\plugins\lbDMFBasicActionSteps.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\plugins\lbFileOperationsPlugin.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\plugins\lbXSLTTransformer.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;

Source: "Q:\Develop\Projects\dll\lbClasses.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\lbDB.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\lbModule.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\lbHook.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\lbDynApp.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\lbPluginManager.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\lbMetaApplication.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\wxWrapperDLL.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\wxmsw28_gcc_custom.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
;Source: "Q:\Develop\Projects\dll\wxmsw28_wat_custom.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
;Source: "Q:\Develop\Projects\dll\wxmsw26d_wat_custom.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\wxAUI.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\wxPropgrid.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\lbxslt.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\plugins\lbDatabaseForm.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\plugins\lbDatabaseReport.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\plugins\lbDMFDataModel.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\plugins\lbDynamicAppStorage.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\plugins\lbLoginWizard.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\plugins\lbVisitorOperations.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\plugins\UserFeedback.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;

; Also now add the code generation plugin.
Source: "Q:\Develop\Projects\plugins\lbDMFXslt.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;

; --- wxLua Runtime to demonstrate code generation for it.
Source: "Q:\develop\Projects\CPP\vendor\wxLua-dist\*.bat"; DestDir: "{app}"; CopyMode: alwaysoverwrite;
Source: "Q:\develop\Projects\CPP\vendor\wxLua-dist\*.exe"; DestDir: "{app}"; CopyMode: alwaysoverwrite;
Source: "Q:\develop\Projects\CPP\vendor\wxLua-dist\*.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;

; --- MinGW Library needed to run my applications.
Source: "Q:\develop\Tools\mingw\bin\mingwm10.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;

; Stuff for Sqlite based databases
Source: "Q:\Develop\Projects\dll\sqlite3.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\databaselayer_sqllite.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\plugins\DatabaseLayerGateway.dll"; DestDir: "{app}\Develop\Projects\plugins"; CopyMode: alwaysoverwrite;


; --- Some files needed from OW's BinNT directory
Source: "Q:\develop\Tools\watcom\binnt\mt7r17.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\develop\Tools\watcom\binnt\clbr17.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\develop\Tools\watcom\binnt\plbr17.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
; --- Some files needed from libxml and libxslt
Source: "Q:\Develop\Projects\dll\iconv.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\zlib1.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\libexslt.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\libxml2.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;
Source: "Q:\Develop\Projects\dll\libxslt.dll"; DestDir: "{app}\Develop\Projects\dll"; CopyMode: alwaysoverwrite;

Source: "Q:\develop\Projects\CPP\Test\GUI\wxWrapper\lbdmf.ico"; DestDir: "{app}"; CopyMode: alwaysoverwrite;

[Icons]
Name: "{group}\lbDMF"; IconFilename: "{app}\lbdmf.ico"; Filename: "{app}\binsample.bat"; WorkingDir: "{app}"
Name: "{group}\Applicationprototyping Dokumentation"; IconFilename: "{app}\lbdmf.ico"; Filename: "{app}\ApplicationprototypingDokumentation.pdf"; WorkingDir: "{app}"
Name: "{userdesktop}\lbDMF"; IconFilename: "{app}\lbdmf.ico"; Filename: "{app}\binsample.bat"; MinVersion: 4,4; Tasks: desktopicon; WorkingDir: "{app}"
;Name: "{userdesktop}\lbDMF Help"; Filename: "{app}\Doc\html\index.html"; MinVersion: 4,4; Tasks: desktopicon; WorkingDir: "{app}\develop\projects\cpp\BaseDevelopment"

[Run]
Filename: "{app}\installODBC.bat"; Description: "Install ODBC driver settings"; Flags: shellexec postinstall

