@echo off
@REM Tear down the Podman machine environment completely so the init script
@REM can be executed again from a clean state.

SET PATH=%PATH%;"C:\Program Files\RedHat\Podman"

SET DRIVE=D:
SET PODMANSPACE=PodmanMachine

echo [INFO] Stoppe Podman-Maschine ...
podman machine stop

echo [INFO] Entferne Podman-Maschine aus Podman ...
podman machine rm -f

echo [INFO] Deregistriere WSL-Instanz (falls noch vorhanden) ...
wsl --unregister podman-machine-default 2>nul

echo [INFO] Bereinige Speicherverzeichnis %DRIVE%\%PODMANSPACE% ...
if exist "%DRIVE%\%PODMANSPACE%" rmdir /s /q "%DRIVE%\%PODMANSPACE%"

echo [OK] Umgebung ist wieder sauber zurueckgesetzt.
