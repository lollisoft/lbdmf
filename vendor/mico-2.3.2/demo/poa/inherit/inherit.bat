REM !/bin/sh

SET ADDR=inet:localhost:12456
SET MICORC=NUL
REM  run Server
start .\server -ORBIIOPAddr %ADDR% 
pause 1


REM  run client
.\client -ORBBindAddr %ADDR%

