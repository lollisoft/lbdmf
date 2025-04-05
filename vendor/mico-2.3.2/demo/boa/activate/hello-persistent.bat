REM !/bin/sh

SET MICORC=NUL
SET ADDR=inet:localhost:12456
REM  run BOA daemon
start micod -ORBIIOPAddr %ADDR% --forward
pause 1


REM  register server
imr create Hello persistent "server1" IDL:Hello:1.0   -ORBImplRepoAddr %ADDR%

REM  run server
start /b .\server1 -ORBImplRepoAddr %ADDR% -OARemoteAddr %ADDR% -OAImplName Hello 
pause 1

REM  run client
.\client1 %ADDR%

REM  wait a bit to make sure we do not bind to the old object
pause 1

REM  rerun server (exits after one invocation)
start /b .\server1 -ORBImplRepoAddr %ADDR% -OARemoteAddr %ADDR% -OAImplName Hello 
pause 1

REM  run client
.\client1 %ADDR%
pause 3
