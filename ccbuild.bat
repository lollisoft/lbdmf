
@REM Simulate first startup

echo --------------------------------------------------------------------------------- > readme.txt
echo *                        Basic development settings                             * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt
echo * You have started lbDMF Develop the first time. Wait until wxWidgets           * >> readme.txt
echo * got built if you opted for a build. If that is finished, reopen               * >> readme.txt
echo * lbDMF Develop and type make.                                                  * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 
echo * If you don't have opted for building wxWigets, the library and MinGW must     * >> readme.txt
echo * be installed manually. Folders for that look respectively like this:          * >> readme.txt
echo * C:\lbDMF\Develop\wxwin\wx (wx is the base folder for wxWidgets)               * >> readme.txt
echo * C:\lbDMF\Develop\Tools\MinGW (MinGW is the base for the compiler stuff)       * >> readme.txt
echo *                                                                               * >> readme.txt
echo * Also install the lbDMF Build tools at the same place as the source code.      * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 
echo * If installation and building is finished, type wxWrapper and enjoy running    * >> readme.txt
echo * the lbDMF Manager prototype (default login: user, password: TestUser)         * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 
echo * Important note: If you have chosen to install in another location,            * >> readme.txt
echo * update the watcomenv.bat file environment variables DEVLW, BASE, BASE_MAKE    * >> readme.txt
echo * and DEVROOT_MAKE_BASE respectively                                            * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 
echo * Download the latest documentation and follow the modeling quickstart.         * >> readme.txt 
echo --------------------------------------------------------------------------------- >> readme.txt
echo * KNOWN ISSUES: The prototype doesn't cope with empty tables when using         * >> readme.txt
echo * Sqlite. To overcome this, use a Sqlite database browser to setup sample data. * >> readme.txt
echo * Using a properly set up ODBC database (tested is PostgreSQL), no problems are * >> readme.txt
echo * known.                                                                        * >> readme.txt
echo --------------------------------------------------------------------------------- >> readme.txt 

call Projects\CPP\watcomenv.bat none JENKINS
