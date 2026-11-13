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

echo [INFO] Starte frischen Tumbleweed-Container und installiere lbdmf ...
podman run --rm -it ^
  -e WAYLAND_DISPLAY=wayland-0 ^
  -e XDG_RUNTIME_DIR=/mnt/wslg/runtime-dir ^
  -v /mnt/wslg:/mnt/wslg ^
  registry.opensuse.org/opensuse/tumbleweed bash -c ^
  "zypper addrepo -f https://download.opensuse.org/repositories/home:/lollisoft/openSUSE_Tumbleweed lbdmf-obs && zypper --gpg-auto-import-keys refresh && zypper install -y fontconfig liberation-fonts dejavu-fonts && fc-cache -f -v && zypper install -y lbdmf && exec bash"
