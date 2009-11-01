REM !/bin/sh

SET MICORC=NUL
SET IADDR=inet:localhost:12123SET UADDR=unix:/tmp/foo$$SET LADDR=local:start .\server -ORBIIOPAddr %UADDR% -ORBNoCodeSets 
start .\server -ORBIIOPAddr %IADDR% -ORBNoCodeSets 

pause 1


echo "### same process:" 
.\client %LADDR% -ORBNoCodeSets

echo "### same machine (pipe):"
.\client %UADDR% -ORBNoCodeSets

echo "### same machine (TCP):"
.\client %IADDR% -ORBNoCodeSets
