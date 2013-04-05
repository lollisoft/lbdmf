@rem ACE Delete Problem: del \\?\C:\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\ace\nul

@rem This batch will flag the installation and building of ACE.

call watcomenv.bat exit

if NOT EXIST C:\lbDMF\Develop\Projects\CPP\vendor\ACE+TAO+CIAO-6.1.0.tar (
	cd C:\lbDMF\Develop\Projects\CPP\vendor
	C:\lbDMF\wget http://download.dre.vanderbilt.edu/previous_versions/ACE+TAO+CIAO-6.1.0.tar.bz2
	C:\lbDMF\Develop\Tools\MinGW\msys\1.0\bin\bunzip2 ACE+TAO+CIAO-6.1.0.tar.bz2
	C:\lbDMF\Develop\Tools\MinGW\msys\1.0\bin\tar xvf ACE+TAO+CIAO-6.1.0.tar
)

@rem Post prepare
@rem Use mingw32-make to compile (multiple targets error will be shown by make)

copy %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\ace\config-win32.h %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\ace\config.h
copy %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\include\makeinclude\platform_mingw32.GNU %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\include\makeinclude\platform_macros.GNU
copy %DEVLW%\lbDMF\Develop\Projects\bin\gawk.exe %DEVLW%\lbDMF\Develop\Projects\bin\awk.exe
cd %DEVLW%\lbDMF\Develop\Projects\CPP\vendor\ACE_wrappers\
mingw32-make