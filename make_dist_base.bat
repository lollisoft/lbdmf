
xcopy /exclude:XCopyIgnores.txt /E /I /Y %1 %DEVROOT%\%1
cd %DEVROOT%\%1
del /S *.o
del /S *.a
del /S *.mbr
del /S *.err
del /S *.bsc
del /S *.sbr
del /S wxwrapper.exe
del /S test.exe
del /S *.obj
del /S *.bak
del /S .#*
del /S *.ilk
del /S *.pch
del /S *.pdb
del /S *.lib
del /S *.dll
del /S *.mak
del /S *.opt
del /S *.lnk
del /S *.lb1
del /S *.lk1
del /S *.mk1
del /S *.sym
del /S *.map
del /S *.exp
del /S *.idb
del /S *.$$$
del /S null
cd %PACKAGINGROOT%
