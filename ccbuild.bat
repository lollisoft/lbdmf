
@REM Simulate first startup

echo --------------------------------------------------------------------------------- > readme.txt
echo * JENKINS                                                                       * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 

call Projects\CPP\watcomenv.bat none JENKINS

if "%1" == "release" (

cd Projects\CPP
make_src_dist.bat

)
