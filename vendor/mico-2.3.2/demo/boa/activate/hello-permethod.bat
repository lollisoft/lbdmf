REM !/bin/sh

SET MICORC=NUL
SET ADDR=inet:localhost:12456
REM  run BOA daemon
start micod -ORBIIOPAddr %ADDR% --forward
pause 1


REM  register server
imr create Hello permethod server2 IDL:Hello:1.0   -ORBImplRepoAddr %ADDR%

REM  run client
.\client2 %ADDR%
REM  wait a bit to make sure we do not bind to the old object
pause 1
.\client2 %ADDR%
pause 3
