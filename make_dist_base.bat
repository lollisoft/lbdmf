
xcopy /I /Y %1 %DEVROOT%\%1
cd %DEVROOT%\%1
del *.exe
del *.obj
del *.bak
del .#*
del *.ilk
del *.pch
del *.pdb
del *.lib
del *.dll
del *.mak
del *.opt
del *.lnk
del *.lb1
del *.lk1
del *.mk1
del *.sym
del *.map
del *.exp
del *.idb
del *.$$$
del null
cd Q:\develop\Projects\CPP
