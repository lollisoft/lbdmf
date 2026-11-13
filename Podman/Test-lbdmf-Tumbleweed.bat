@REM Setup a place where I want to have my files for Podman machine environment
@REM That is as of my current setting a drive D: and the folder where they should
@REM reside is D:\PodmanMachine. This script assumes a preconfigured software but
@REM nothing has yet been initialized and no machine exists or is running.
@REM IT DOES NO CHECKS AGAINST REPEATED RUNS. TO REPEAT, FIRST CALL DropSetup.bat

SET PATH=%PATH%;"C:\Program Files\RedHat\Podman"

SET DRIVE=D:
SET PODMANSPACE=PodmanMachine

if not exist "%DRIVE%\%PODMANSPACE%" mkdir "%DRIVE%\%PODMANSPACE%"

podman machine init
wsl --export podman-machine-default %DRIVE%\%PODMANSPACE%\podman.tar
wsl --unregister podman-machine-default
wsl --import podman-machine-default %DRIVE%\%PODMANSPACE% %DRIVE%\%PODMANSPACE%\podman.tar --version 2
del %DRIVE%\%PODMANSPACE%\podman.tar

echo [INFO] Stelle sicher, dass die Podman-Maschine laeuft ...
podman machine start 2>nul

start "" /MAX "C:\Program Files\VcXsrv\vcxsrv.exe" :2 -ac -wgl -noreset

echo [INFO] Starte frischen Tumbleweed-Container und installiere lbdmf ...
SET CMD=zypper addrepo -f https://download.opensuse.org/repositories/home:/lollisoft/openSUSE_Tumbleweed lbdmf-obs ^&^& ^
zypper --gpg-auto-import-keys refresh ^&^& ^
zypper install -y icewm fontconfig liberation-fonts dejavu-fonts lbdmf ^&^& ^
gw=$(grep -m1 $'\t00000000\t' /proc/net/route ^| cut -f3) ^&^& ^
export DISPLAY=$(printf '%%d.%%d.%%d.%%d:2.0' 0x${gw:6:2} 0x${gw:4:2} 0x${gw:2:2} 0x${gw:0:2}) ^&^& ^
export GDK_BACKEND=x11 ^&^& ^
(icewm ^&) ^&^& sleep 1 ^&^& wxWrapper; exec bash

podman run --rm -it registry.opensuse.org/opensuse/tumbleweed bash -c "%CMD%"
