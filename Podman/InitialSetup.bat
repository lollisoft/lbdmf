@REM Setup a place where I want to have my files for Podman machine environment
@REM That is as of my current setting a drive D: and the folder where they should
@REM reside is D:\PodmanMachine. This script assumes a preconfigured software but
@REM nothing has yet been initialized and no machine exists or is running.
@REM IT DOES NO CHECKS AGAINST REPEATED RUNS

SET PATH=%PATH%;"C:\Program Files\RedHat\Podman"

SET DRIVE=D:
SET PODMANSPACE=PodmanMachine

if not exist "%DRIVE%\%PODMANSPACE%" mkdir "%DRIVE%\%PODMANSPACE%"

podman machine init
wsl --export podman-machine-default %DRIVE%\%PODMANSPACE%\podman.tar
wsl --unregister podman-machine-default
wsl --import podman-machine-default %DRIVE%\%PODMANSPACE% %DRIVE%\%PODMANSPACE%\podman.tar --version 2
del %DRIVE%\%PODMANSPACE%\podman.tar
podman machine start
@REM podman run --rm -it registry.opensuse.org/opensuse/tumbleweed bash