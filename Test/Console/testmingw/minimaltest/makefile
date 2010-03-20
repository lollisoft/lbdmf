all: testdll.dll testow.exe testmingw.exe


testdll.o: testdll.cpp testdll.h
		g++ -c testdll.cpp

test.obj: test.cpp testdll.h
		wpp386 -DWINDOWS -w3 -e25 -zq -otexan -5r -of+ -xr /DLBDMF_PRE test.cpp

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
		rm *.exe *.obj *.o *.dll *.bak *.sym *.lnk
