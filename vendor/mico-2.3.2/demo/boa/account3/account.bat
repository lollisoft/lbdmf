REM !/bin/sh

SET MICORC=NUL
SET ADDR=inet:localhost:12456
REM  run BOA daemon
start micod -ORBIIOPAddr %ADDR% --forward 
pause 1


REM  register server
imr create Banking unshared server   IDL:Account:1.0 IDL:Bank:1.0 -ORBImplRepoAddr %ADDR%

REM imr create Banking unshared "rsh zirkon `pwd`/server" #  IDL:Account:1.0 IDL:Bank:1.0 -ORBImplRepoAddr $ADDR

REM  run client
.\client %ADDR%
