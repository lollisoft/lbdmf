REM !/bin/sh

SET MICORC=NUL
SET ADDR=inet:localhost:12456
REM  run BOA daemon
start micod -ORBIIOPAddr %ADDR% --forward 
pause 1


REM  register server1
imr create Account1 shared server IDL:Account:1.0   -ORBImplRepoAddr %ADDR%

REM  register server2
imr create Account2 shared server IDL:Account:1.0   -ORBImplRepoAddr %ADDR%

REM  run client
.\client %ADDR%
