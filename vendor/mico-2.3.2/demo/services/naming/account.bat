
set ADDR=inet:127.0.0.1:12456
SET MICORC=NUL
set RC=-ORBImplRepoAddr %ADDR% -ORBNamingAddr %ADDR%
set path=..\..\win32-bin\;%path% 
REM run BOA daemon
echo "starting BOA daemon ..."
start micod -ORBIIOPAddr %ADDR% 


REM register server
echo "register name service ..."
imr create NameService poa nsd.exe "IDL:omg.org/CosNaming/NamingContext:1.0#NameService" %RC%

echo "register account service ..."
imr create Account shared "server %RC%"  IDL:Account:1.0 %RC%


REM activate the account server to make itself register with the
REM name service so the client can find it ...
echo "activating Account implementation"
imr activate Account %RC%
pause
REM run client
echo "and run client ..."
./client %RC%

