@echo This module makes your application modules if the main directory
@echo appdevelopment exists.

if not exist ..\appdevelopment goto next1:
cd ..\appdevelopment
call make.bat
cd ..\BaseDevelopment
@echo Compiled
goto end:
:next1
@echo No custom application modules available. Not compiled.
:end


