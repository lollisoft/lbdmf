
@REM Simulate first startup

echo --------------------------------------------------------------------------------- > readme.txt
echo * JENKINS                                                                       * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 

call Projects\lbdmf\watcomenv.bat none JENKINS

if "%1" == "release" (

cd ..
make_src_dist.bat

)
