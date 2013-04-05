@rem This batch will download and install MinGW by mingw-get

Develop\Tools\MinGW\bin\mingw-get install mingw
Develop\Tools\MinGW\bin\mingw-get install g++

@rem Required to compile ACE
Develop\Tools\MinGW\bin\mingw-get install msys
