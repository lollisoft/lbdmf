all: testdllow.dll testdll.dll testdllmingw.dll testow.exe testmingw.exe

CALL=-5s

testdll.o: testdll.cpp testdll.h
		g++ -c testdll.cpp

test.obj: test.cpp testdll.h
		wpp386 -DWINDOWS -w3 -e25 -zq -otexan $(CALL) -of+ -xr /DLBDMF_PRE test.cpp

testdllmingw.o: testdll.cpp testdll.h
		g++ -c testdll.cpp -o testdllmingw.o

testdllmingw.dll: testdllmingw.o
		g++ -shared -o testdllmingw.dll testdllmingw.o
		wlib -q -n -b testdllmingw.lib +testdllmingw.dll
		wlib -m testdllmingw.dll > exportsmingw.txt


testdllow.obj: testdllow.cpp testdll.h
		wpp386 -DWINDOWS -bd -hd -w3 -e25 -zq -otexan $(CALL) -of+ -xr /DLBDMF_PRE testdllow.cpp

testdllow.dll.lnk: makefile testdllow.obj
		echo NAME testdllow.dll > $@
		echo FIL testdllow.obj >> $@


testdllow.dll: testdllow.obj testdllow.dll.lnk
		@echo Link testdllow.dll
		wlink op q op symf d dwarf SYS nt_dll op m op maxe=25 @testdllow.dll.lnk
		@wlib -q -n -b testdllow.lib +testdllow.dll


test.o: test.cpp testdll.h
		g++ -c test.cpp

testdll.dll: testdll.o
		g++ -shared -o testdll.dll testdll.o
		wlib -q -n -b testdll.lib +testdll.dll
		wlib -m testdll.dll > exports.txt

testow.exe: test.obj
		echo Link testow.exe
		echo NAME testow.exe > test.lnk
		echo FIL test.obj,testdll.lib >> test.lnk
		cmd /C "attrib -r *.bak"
		wlink op q op symf d dwarf   @test.lnk

testmingw.exe: test.o
		rm testdll.lib
		g++ -o testmingw.exe test.o -L. -ltestdll


clean:
		-del *.err *.exe *.obj *.o *.dll *.bak *.sym *.lnk *.map *.lib exports.txt exportsmingw.txt
		-rm *.err *.exe *.obj *.o *.dll *.bak *.sym *.lnk *.map *.lib exports.txt exportsmingw.txt
