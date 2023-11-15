@REM Simulate first startup

echo --------------------------------------------------------------------------------- > readme.txt
echo * Appveyor                                                                      * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 

call watcomenv.bat none JENKINS

if "%1" == "release" (

make_src_dist.bat

)
