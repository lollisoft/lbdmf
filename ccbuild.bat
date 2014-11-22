
@REM Simulate first startup

echo --------------------------------------------------------------------------------- > readme.txt
echo * JENKINS                                                                       * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 

call Projects\CPP\watcomenv.bat none JENKINS

@rem Get an explicite version that always ensures to build the code
set MINGW_STICKON_VERSION=4.7.*
set MINGW_STICKON_WIN32_VERSION=4.0.3-*

IF NOT EXIST %DEVLW%\lbDMF\Tools\MinGW\bin\gcc.exe (
call Projects\CPP\installMinGW.bat %MINGW_STICKON_VERSION% %MINGW_STICKON_WIN32_VERSION% 
)

if "%1" == "release" (

cd ..
make_src_dist.bat

)
