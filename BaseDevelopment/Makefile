# Global makefile to build all sub modules
# **************************************************************
# * $Locker:  $
# * $Revision: 1.229.2.60 $
# * $Name:  $
# * $Id: Makefile,v 1.229.2.60 2016/02/21 18:02:51 lollisoft Exp $
# *
# * $Log: Makefile,v $
# * Revision 1.229.2.60  2016/02/21 18:02:51  lollisoft
# * Corrected path.
# *
# * Revision 1.229.2.59  2016/02/21 17:40:33  lollisoft
# * Corrected path.
# *
# * Revision 1.229.2.58  2016/02/21 16:25:42  lollisoft
# * Removing downloading dependencies.
# *
# * Revision 1.229.2.57  2016/02/20 18:20:47  lollisoft
# * Fixed missing cacert parameter.
# *
# * Revision 1.229.2.56  2016/02/20 17:21:52  lollisoft
# * Changed wget to curl.
# *
# * Revision 1.229.2.55  2016/02/20 16:53:25  lollisoft
# * Chenged wget to curl.
# *
# * Revision 1.229.2.54  2015/06/27 05:06:21  lollisoft
# * Deactivated goldparser engine stuff.
# *
# * Revision 1.229.2.53  2015/03/27 04:23:11  lollisoft
# * Added new plugins to start developing domain languages.
# *
# * Revision 1.229.2.52  2015/01/15 18:54:15  lollisoft
# * Changed version information.
# *
# * Revision 1.229.2.51  2015/01/10 12:27:02  lollisoft
# * Added separate install rules for Jenkins build versus manual build. The manual build fails at missing AppDevelopment install step, but that could be ignored. In Jenkins build this should be excluded.
# *
# * Revision 1.229.2.50  2015/01/10 05:07:08  lollisoft
# * Added required parameter.
# *
# * Revision 1.229.2.49  2015/01/03 10:38:51  lollisoft
# * Added enhanced update mechanism with a silent recheck to create download toolbar and menu entries.
# *
# * Revision 1.229.2.48  2015/01/02 07:38:31  lollisoft
# * Separated JSON target per platform due to build type selection.
# *
# * Revision 1.229.2.47  2015/01/02 06:48:37  lollisoft
# * Moved JSON target to another location.
# *
# * Revision 1.229.2.46  2015/01/01 23:10:13  lollisoft
# * Added wxJSON target for all platforms.
# *
# * Revision 1.229.2.45  2015/01/01 19:06:50  lollisoft
# * Added initial json based update check plugin.
# *
# * Revision 1.229.2.44  2014/12/14 11:43:13  lollisoft
# * Added a comment to test jenkins join plugin.
# *
# * Revision 1.229.2.43  2014/12/13 09:15:53  lollisoft
# * Made installation of AppDevelopment folder optional.
# *
# * Revision 1.229.2.42  2014/11/22 08:54:16  lollisoft
# * Changed OSType to OSName.
# *
# * Revision 1.229.2.41  2014/11/22 08:11:07  lollisoft
# * No longer use foreign key Lex&Yacc code on Windows, because I create the semantic in XSLT instead.
# *
# * Revision 1.229.2.40  2014/10/24 05:05:40  lollisoft
# * Added Mac OSX jenkins build script and corrected first set of makefiles for it.
# *
# * Revision 1.229.2.39  2014/10/19 11:47:35  lollisoft
# * Preparing config.h file.
# *
# * Revision 1.229.2.38  2014/10/19 10:02:58  lollisoft
# * Fixed typo.
# *
# * Revision 1.229.2.37  2014/10/19 09:44:02  lollisoft
# * Added new rule to download libxslt and prepare makefile.module for it.
# *
# * Revision 1.229.2.36  2014/10/19 09:12:26  lollisoft
# * Adding semicolons.
# *
# * Revision 1.229.2.35  2014/10/19 07:57:18  lollisoft
# * Splitted cd command
# *
# * Revision 1.229.2.34  2014/10/19 07:40:33  lollisoft
# * Try using shell
# *
# * Revision 1.229.2.33  2014/10/19 07:10:27  lollisoft
# * Using pathsep creation with stip.
# *
# * Revision 1.229.2.32  2014/10/19 06:35:44  lollisoft
# * Switched to forward slashes.
# *
# * Revision 1.229.2.31  2014/10/19 06:08:40  lollisoft
# * Changed how to build libxml.
# *
# * Revision 1.229.2.30  2014/10/18 10:11:45  lollisoft
# * Tell me where tar is.
# *
# * Revision 1.229.2.29  2014/10/18 07:45:08  lollisoft
# * Adding z to tar command parameter.
# *
# * Revision 1.229.2.28  2014/10/18 06:55:33  lollisoft
# * Specifying directory corrected.
# *
# * Revision 1.229.2.27  2014/10/18 06:30:23  lollisoft
# * Moved definitions for wget and tar
# *
# * Revision 1.229.2.26  2014/10/18 05:11:03  lollisoft
# * Added rule to download libxml in the currently used version.
# *
# * Revision 1.229.2.25  2014/10/18 03:45:08  lollisoft
# * Added bin rule and dependency
# *
# * Revision 1.229.2.24  2014/10/18 02:53:02  lollisoft
# * Added rule to copy bison.simple file. This is not ideal.
# *
# * Revision 1.229.2.23  2014/10/14 06:17:05  lollisoft
# * Added dependency
# *
# * Revision 1.229.2.22  2014/10/14 06:04:43  lollisoft
# * Added rule to first create dll directory.
# *
# * Revision 1.229.2.21  2014/10/14 05:01:58  lollisoft
# * Corrected RELPATH for Windows.
# *
# * Revision 1.229.2.20  2014/03/15 06:30:31  lollisoft
# * Some new features.
# *
# * Revision 1.229.2.19  2013/11/29 06:25:47  lollisoft
# * Added copy commands for rpm deployment to prepare XMISettings.xsl based on XMISettingsTemplate.xsl.
# *
# * Revision 1.229.2.18  2013/11/17 09:26:38  lollisoft
# * Changed L_OPS flags to be LDFLAGS.
# *
# * Revision 1.229.2.17  2013/10/20 10:33:55  lollisoft
# * Removed some char[] arrays due to buffer overflow danger.
# *
# * Revision 1.229.2.16  2013/10/15 04:51:26  lollisoft
# * Added lbtracsfer and lbcs to the target lists.
# *
# * Revision 1.229.2.15  2013/09/22 10:29:14  lollisoft
# * Differences for MkBs.
# *
# * Revision 1.229.2.14  2013/09/16 09:23:07  lollisoft
# * Changed implementation of makefile bootstrapping for Mac OS X. Added relevant code for it and other changes.
# *
# * Revision 1.229.2.13  2013/09/15 07:24:50  lollisoft
# * Target distclean using touch makefile.
# *
# * Revision 1.229.2.12  2013/01/30 04:50:50  lollisoft
# * Corrected rpm istallation.
# *
# * Revision 1.229.2.11  2013/01/27 15:53:00  lollisoft
# * Moved target to be build earlyer.
# *
# * Revision 1.229.2.10  2012/12/07 05:09:49  lollisoft
# * Activated building UnitTests on solaris, linux and ppc linux.
# *
# * Revision 1.229.2.9  2012/11/25 09:03:49  lollisoft
# * Missed the wsShapeFramework targets on Linux.
# *
# * Revision 1.229.2.8  2012/11/25 08:37:30  lollisoft
# * Moved wxShapeFramework build before plugins.
# *
# * Revision 1.229.2.7  2012/11/19 13:31:55  lollisoft
# * Fixed Windows based issues and replaced wxAUI library with built in wxWidgets AUI version.
# *
# * Revision 1.229.2.6  2012/10/05 07:08:51  lollisoft
# * Moved deployment specific stuff to environment file.
# *
# * Revision 1.229.2.5  2012/10/03 20:56:38  lollisoft
# * Modified make system to work with current cygwin make and with MinGW compilers together.
# *
# * Revision 1.229.2.4  2012/07/22 07:44:31  lollisoft
# * Any changes before CVS backup
# *
# * Revision 1.229.2.3  2012/06/09 17:56:39  lollisoft
# * Integrated new version of libxml2 and it's build task. Modified other build tasks.
# *
# * Revision 1.229.2.2  2012/06/08 17:51:30  lollisoft
# * Building libxml2 with gcc, no longer with OW. Need to add support switching compiler when required.
# *
# * Revision 1.229.2.1  2012/05/19 05:47:32  lollisoft
# * New workflow module integrated into the build. SQL scripts tewaked.
# *
# * Revision 1.229  2011/10/15 06:36:11  lollisoft
# * All current changes including interfaces (starting mass changes).
# *
# * Revision 1.228  2011/09/24 11:37:31  lollisoft
# * Deactivated databaselayer for ODBC variant.
# *
# * Revision 1.227  2011/06/12 18:51:55  lollisoft
# * Hack for the RPM space in file issue.
# *
# * Revision 1.226  2011/04/21 11:33:39  lollisoft
# * Added wxSF demo target on Mac OS X.
# *
# * Revision 1.225  2011/04/20 20:35:36  lollisoft
# * Activated optional wxShapeFramework compile task.
# *
# * Revision 1.224  2011/04/02 10:44:17  lollisoft
# * Now the UML based activities are reworked and they work while testing it against postbooks database.
# *
# * Revision 1.223  2010/12/18 09:38:38  lollisoft
# * Some changes on my macbook.
# *
# * Revision 1.222  2010/11/09 08:11:57  lollisoft
# * Added unit tests target on debian ppc. Not all tests are passing yet.
# *
# * Revision 1.221  2010/08/29 21:09:30  lollisoft
# * Changes to get more modules compiled with MinGW.
# * Also changed my adress in some files as I have a new
# * home. Others will follow.
# *
# * Revision 1.220  2010/06/03 16:58:07  lollisoft
# * Most requriered modules are now compilable with MinGW and the main application runs.
# * There are some problems with unit tests but they pass. Also the code generator seems to
# * not work properly.
# *
# * Revision 1.219  2010/06/02 07:11:29  lollisoft
# * Executable targets now compile with MinGW. Tested with wxWrapper yet.
# *
# * Revision 1.218  2010/05/29 18:07:18  lollisoft
# * Changes to compile code with MinGW.
# *
# * Revision 1.217  2010/04/26 06:49:01  lollisoft
# * Moved lbCryptoStream plugin to activate building it on Windows.
# *
# * Revision 1.216  2010/04/03 00:15:56  lollisoft
# * Changes to properly mix up compilers (OW and MinGW). Tested in UnitTests with is actually testing some functions of the lbString class.
# *
# * Revision 1.215  2010/03/28 19:23:02  lollisoft
# * Added new subdirectory target UnitTests.
# *
# * Revision 1.214  2010/03/20 22:33:38  lollisoft
# * Added support for mingw mixed mode (with Open Watcom).
# * This is tested with the Basetypes sample application that uses
# * lbHook.dll (mingw), lbModule.dll (OW) and lbclasses.dll (OW).
# *
# * Revision 1.213  2010/02/04 21:10:51  lollisoft
# * Added support for Mac OSX 10.2.0.
# *
# * Revision 1.212  2010/01/16 00:04:27  lollisoft
# * Deactivated cryptstrm. Not yet ready to compile on all platforms.
# *
# * Revision 1.211  2010/01/12 19:45:41  lollisoft
# * Mostly completed plugin based interceptor functionality for events.
# *
# * Revision 1.210  2009/12/18 13:13:16  lollisoft
# * Added compile support for OS X 10.5.6
# *
# * Revision 1.209  2009/12/17 12:49:04  lollisoft
# * Added deploying missing XSLT templates.
# *
# * Revision 1.208  2009/11/22 16:38:36  lollisoft
# * Compile Mac OS X on Snow Leopard only for i386. Add ppc on demand to the OSX_ARCH flag in make/STD_MAKE. Probgrid seems to not correctly initialize a variable that causes a division with zero (hack).
# *
# * Revision 1.207  2009/11/20 19:32:53  lollisoft
# * Corrected HOME path usage to become prefix.
# *
# * Revision 1.206  2009/11/19 16:14:16  lollisoft
# * Optimized CC build to write mkmk into /bin.
# *
# * Revision 1.205  2009/11/14 10:00:27  lollisoft
# * Corrected build system to support OSX 10.5.8
# *
# * Revision 1.204  2009/11/08 11:49:32  lollisoft
# * Implemented 'unit test' like capabilities. The TestPlugin in the Plugins directory demonstrates the usage. Yet missing is a real test listener and stuff to display results. But it shows a working unit test mechanism using plugins.
# *
# * Corrected mkmk to find also include files in <> brackets.
# *
# * Corrected make system to work correctly with the new mkmk version. There may be a performance problem when compiling tvision code, thus that target is deactivated.
# *
# * Fixed some warnings.
# *
# * Revision 1.203  2009/09/11 10:58:16  lollisoft
# * Corrected UML sample file directory.
# *
# * Revision 1.202  2009/06/18 17:38:33  lollisoft
# * Changes to compile on OSX 10.5.4
# *
# * Revision 1.201  2009/06/10 11:40:17  lollisoft
# * Changed order of targets to enable application bundle packaging including wxWidgets library.
# *
# * Revision 1.200  2009/06/03 09:33:53  lollisoft
# * Added support for creating debug rpm packages.
# *
# * Revision 1.199  2009/06/02 10:27:15  lollisoft
# * Changed source path for copying XSLT templates.
# *
# * Revision 1.198  2009/05/26 09:15:02  lollisoft
# * Added creating include directory.
# *
# * Revision 1.197  2009/05/25 17:03:01  lollisoft
# * Corrected file extensions.
# *
# * Revision 1.196  2009/05/25 08:16:04  lollisoft
# * Added include directory.
# *
# * Revision 1.195  2009/05/21 14:57:10  lollisoft
# * Added packaging of DMFToXMI files.
# *
# * Revision 1.194  2009/03/12 19:14:00  lollisoft
# * Added code to copy SQL files into correct place on Linux.
# *
# * Revision 1.193  2009/03/09 23:14:56  lollisoft
# * Changes to fix RPM build issue with databaselayer_sqlite and sqlite library.
# *
# * Revision 1.192  2009/03/09 20:29:22  lollisoft
# * Corrected PDF filename problem in RPM built.
# *
# * Revision 1.191  2009/03/09 19:08:53  lollisoft
# * Try fix for files with spaces.
# *
# * Revision 1.190  2009/03/09 18:43:08  lollisoft
# * Try fix for files with spaces.
# *
# * Revision 1.189  2009/03/09 17:10:13  lollisoft
# * Removed target in RPM build.
# *
# * Revision 1.188  2009/01/14 15:01:02  lollisoft
# * Fixed build system for solaris. Now basically the application works with sqlite.
# *
# * Revision 1.187  2008/10/03 14:35:14  lollisoft
# * Added unit test target for the database layer modul.
# *
# * Revision 1.186  2008/08/13 06:53:32  lollisoft
# * Changes to get code again compiled under Mac OS X 10.3.9. But there is an issue with wxWrapper target and Rez.
# *
# * Revision 1.185  2008/08/08 11:30:30  lollisoft
# * Tries on Linux
# *
# * Revision 1.184  2008/07/24 20:53:36  lollisoft
# * These changes let the application run on Mac OS X 10.5 (Leopard). But crashes at exit, propably due to changed cleanup logic or changed default variable values (not correctly initialized).
# *
# * Revision 1.183  2008/07/16 10:04:40  lollisoft
# * Deactivated AppDevelopment target in cruisecontrol build.
# *
# * Revision 1.182  2008/07/13 08:02:15  lollisoft
# * Builds before update to Mac OS X 10.5
# *
# * Revision 1.181  2008/06/08 22:08:47  lollisoft
# * Avoid failures if tvision is not available.
# *
# * Revision 1.180  2008/06/07 07:45:23  lollisoft
# * Moving Open Watcom crosscompiling attempts to my other Linux box.
# *
# * Revision 1.179  2008/06/02 12:27:21  lollisoft
# * Testing failure works with jabber notification. Error removed.
# *
# * Revision 1.178  2008/06/02 12:21:30  lollisoft
# * Test failure 2
# *
# * Revision 1.177  2008/06/02 12:10:06  lollisoft
# * Test failure
# *
# * Revision 1.176  2008/06/02 11:51:58  lollisoft
# * Corrected failure test.
# *
# * Revision 1.175  2008/06/02 11:47:31  lollisoft
# * Test failure
# *
# * Revision 1.174  2008/06/02 07:54:47  lollisoft
# * Added some code for crosscompiling with OW on Linux.
# *
# * Revision 1.173  2008/06/01 19:08:23  lollisoft
# * Removed installing instructions for Windows databaselayer and sqlite3 targets.
# *
# * Revision 1.172  2008/06/01 18:24:20  lollisoft
# * Try ifneq for sqlite special install.
# *
# * Revision 1.171  2008/06/01 12:30:30  lollisoft
# * Last changes to let compile under Linux to be prepared for cruise control.
# *
# * Revision 1.170  2008/06/01 09:12:12  lollisoft
# * Changed order of building lex and yacc files. This builds from freshly checked out project.
# *
# * Revision 1.169  2008/06/01 08:32:51  lollisoft
# * Try to install sqlite3 and databaselayer_sqllite while building it to resolve missing those libraries.
# *
# * This should be done better.
# *
# * Revision 1.168  2008/05/10 17:42:06  lollisoft
# * Activated and deactivated some targets.
# *
# * Revision 1.167  2008/05/09 06:38:22  lollisoft
# * More porting changes for debian-ppc.
# *
# * Revision 1.166  2008/02/02 08:22:52  lollisoft
# * Some improvements in sqlite database stuff, but also some problems in parser syntax.
# *
# * Revision 1.165  2008/01/26 20:24:43  lollisoft
# * Implemented more functions regarding to meta data for sqlite database gateway. Some interface functions have
# * been changed to get proper working test application.
# *
# * These are getTableName and getColumnName in lb_I_Query interface.
# *
# * Revision 1.164  2008/01/19 21:51:42  lollisoft
# * Go to Mac for further development.
# *
# * Revision 1.163  2008/01/18 22:38:34  lollisoft
# * Small problems with new lex and yacc make defines.
# *
# * Revision 1.162  2008/01/18 21:36:25  lollisoft
# * Added build steps for sqlite fk implementation.
# *
# * Revision 1.161  2007/12/28 17:08:40  lollisoft
# * Removed some targets from the build target list.
# *
# * Revision 1.160  2007/11/26 17:25:12  lollisoft
# * Removed databaselayer test target.
# *
# * Revision 1.159  2007/11/26 16:54:14  lollisoft
# * Changing build order of some modules.
# *
# * Revision 1.158  2007/11/17 09:35:30  lollisoft
# * Added new xsltc target for linux.
# *
# * Revision 1.157  2007/11/14 20:45:57  lollisoft
# * Some changes for mkmk to compile c files in subdirectories well under Windows.
# * Added xsltc target and some other changes.
# *
# * Revision 1.156  2007/11/10 23:24:46  lollisoft
# * Added databaselayer test application.
# *
# * Revision 1.155  2007/11/09 22:49:36  lollisoft
# * Modifications to build databaselayer on Linux.
# *
# * Revision 1.154  2007/11/09 17:29:08  lollisoft
# * Added missing target definitions. This reduces conditionals.
# *
# * Revision 1.153  2007/11/08 08:49:34  lollisoft
# * Moved around some targets (buildorder) and added targets
# * to windows build.
# *
# * Revision 1.152  2007/11/07 09:25:20  lollisoft
# * Added sqlite target.
# *
# * Revision 1.151  2007/11/03 08:20:49  lollisoft
# * Fix CRUISECONTROL detection.
# *
# * Revision 1.150  2007/11/02 22:12:50  lollisoft
# * Deactivated some targets that fail building.
# *
# * Revision 1.149  2007/11/02 11:56:48  lollisoft
# * Changes that propably enable Cruise Control builds.
# *
# * Revision 1.148  2007/10/29 19:59:17  lollisoft
# * Added xsl templates and made bugfixes that now let
# * the designer create code for any application. Not only
# * 'lbDMF Manager'. The problem is the container class.
# * It allows multible entries per key.
# *
# * Revision 1.147  2007/10/28 23:22:39  lollisoft
# * Small changes to correctly compile generated code.
# *
# * Revision 1.146  2007/10/28 16:59:53  lollisoft
# * Added databaselayer as vendor target.
# *
# * Revision 1.145  2007/10/21 21:30:30  lollisoft
# * Added mpatrol support that partly works on small test apps. wxWidgets gets very slow.
# *
# * Revision 1.144  2007/10/16 10:33:27  lollisoft
# * Moved desktop menu icon creation to spec file.
# *
# * Revision 1.143  2007/10/15 12:48:17  lollisoft
# * Corrected path to icon file.
# *
# * Revision 1.142  2007/10/15 12:10:58  lollisoft
# * Missing applications directory :-)
# *
# * Revision 1.141  2007/10/15 11:38:26  lollisoft
# * Using simple echo commands to create desktop menu entry.
# *
# * Revision 1.140  2007/10/13 20:20:32  lollisoft
# * Added pdf document to the rpm build.
# *
# * Revision 1.139  2007/10/13 18:32:24  lollisoft
# * Try to add xsl, xmi and UML sample files.
# *
# * Revision 1.138  2007/09/28 18:26:34  lollisoft
# * Some bugfixes on Windows regarding xslt processing.
# *
# * Revision 1.137  2007/09/18 12:22:42  lollisoft
# * Added splash screen image to the correct install location.
# *
# * Revision 1.136  2007/09/18 09:02:53  lollisoft
# * Try again from SuSE specification. (http://forgeftp.novell.com//library/SUSE%20Package%20Conventions/spc.pdf)
# *
# * Revision 1.135  2007/09/18 06:49:26  lollisoft
# * Added desktop file to /share/applications.
# *
# * Revision 1.134  2007/09/17 11:07:56  lollisoft
# * Added desktop symbol to Linux installation. Small correction.
# *
# * Revision 1.133  2007/09/17 11:06:24  lollisoft
# * Added desktop symbol to Linux installation.
# *
# * Revision 1.132  2007/09/16 23:02:50  lollisoft
# * Corrected toolbar image path creation.
# *
# * Revision 1.131  2007/09/16 21:40:02  lollisoft
# * Other place for toolbar images.
# *
# * Revision 1.130  2007/09/16 16:18:47  lollisoft
# * Using copy script without creating it. (Added to repo)
# *
# * Revision 1.129  2007/09/16 13:51:51  lollisoft
# * Try to echo into o script.
# *
# * Revision 1.128  2007/09/16 12:25:35  lollisoft
# * Trouble with special characters.
# *
# * Revision 1.127  2007/09/16 09:44:05  lollisoft
# * Try to use tested ldd command to include required wxWidgets libraries.
# *
# * Revision 1.126  2007/09/12 08:11:11  lollisoft
# * Deacivated copying wx library.
# *
# * Revision 1.125  2007/08/06 19:10:29  lollisoft
# * Improved installation process on Windows.
# *
# * Revision 1.124  2007/07/08 16:50:27  lollisoft
# * Removed some targets. Last removal failed ??
# *
# * Revision 1.123  2007/07/08 16:30:29  lollisoft
# * Removed some targets in rpmbuild verion.
# *
# * Revision 1.122  2007/07/07 16:37:32  lollisoft
# * Changes to let xslt code work.
# *
# * Revision 1.121  2007/06/16 10:26:51  lollisoft
# * This changes let the application successfully run under Solaris. Also a bug is fixed that caused a crash at application exit.
# *
# * Revision 1.120  2007/05/14 19:19:14  lollisoft
# * Unfinished changes. Go to Linux.
# *
# * Revision 1.119  2007/04/22 14:05:20  lollisoft
# * Many changes due to client/server redesign.
# *
# * Revision 1.118  2007/02/28 19:24:29  lollisoft
# * New plugin compiles under Mac OS X.
# *
# * Revision 1.117  2007/02/27 21:40:34  lollisoft
# * Added new plugin
# *
# * Revision 1.116  2006/12/10 17:05:24  lollisoft
# * Other changes under Mac OS X.
# *
# * Revision 1.115  2006/10/22 18:34:36  lollisoft
# * Many memory leaks resolved, but they were caused by small errors :-(
# * This is also a sync.
# *
# * Revision 1.114  2006/07/17 17:37:45  lollisoft
# * Changes dueto bugfix in plugin manager. Repeadable iterator problem.
# * Not correctly finished the iteration, thus plugins in the same DLL wouldn't
# * be found any more after first query.
# *
# * Code works well with improved trmem library, but there is still a crash in
# * database classes (pgODBC library).
# *
# * Revision 1.113  2006/04/20 12:20:31  lollisoft
# * Changed make order to catch up all targets before propably non existing directories.
# *
# * Revision 1.112  2006/04/20 11:40:32  lollisoft
# * Added creation rules for ~/bin ~/lib and ~/plugins into the Mac OS X target list.
# *
# * Revision 1.111  2006/04/16 12:01:19  lollisoft
# * Missed addition of propgrid target.
# *
# * Revision 1.110  2006/04/16 10:10:43  lollisoft
# * Added wxPropgrid framework rule.
# *
# * Revision 1.109  2006/04/11 13:40:05  lollisoft
# * Added making propgrid module.
# *
# * Revision 1.108  2006/03/15 07:24:14  lollisoft
# * Moved Windows module make ordering.
# *
# * Revision 1.107  2006/03/09 09:03:10  lollisoft
# * Missing ALLDIRS.
# *
# * Revision 1.106  2006/03/07 09:40:28  lollisoft
# * Removed some targets in rpm build
# *
# * Revision 1.105  2006/03/06 13:10:31  lollisoft
# * Use local libdir for pulling wx library
# *
# * Revision 1.104  2006/03/06 09:17:18  lollisoft
# * Again wrong name
# *
# * Revision 1.103  2006/03/06 08:58:45  lollisoft
# * Wrong module name in installation
# *
# * Revision 1.102  2006/03/05 10:09:57  lollisoft
# * Wrong wx library name
# *
# * Revision 1.101  2006/03/04 22:18:17  lollisoft
# * Corrected library dependencies and build names
# *
# * Revision 1.100  2006/03/04 17:18:55  lollisoft
# * Bugfix
# *
# * Revision 1.99  2006/03/04 17:03:17  lollisoft
# * Symlinks do not simply appear in rpm's
# *
# * Revision 1.98  2006/03/04 16:41:23  lollisoft
# * Bugfix
# *
# * Revision 1.97  2006/03/04 16:24:20  lollisoft
# * Added creation of symlinks while installation.
# *
# * Revision 1.96  2006/03/04 12:18:18  lollisoft
# * Try to include wx libraries
# *
# * Revision 1.95  2006/03/03 16:16:40  lollisoft
# * Changes in shared library naming and linking against.
# *
# * Revision 1.94  2006/03/02 20:32:28  lollisoft
# * Minor changes under Windows
# *
# * Revision 1.93  2006/03/02 16:39:29  lollisoft
# * Use prefix for libraries.
# *
# * Revision 1.92  2006/03/02 13:10:40  lollisoft
# * Missing -p
# *
# * Revision 1.91  2006/03/02 13:06:58  lollisoft
# * Corrected creation of target directories
# *
# * Revision 1.90  2006/03/02 13:01:18  lollisoft
# * Added creation of target directories
# *
# * Revision 1.89  2006/03/02 12:35:22  lollisoft
# * Modified existing clean target and added install-strip target
# *
# * Revision 1.88  2006/03/01 11:34:46  lollisoft
# * Activated RPMBUILD section
# *
# * Revision 1.87  2006/03/01 11:30:51  lollisoft
# * Test RPMBUILD failure
# *
# * Revision 1.86  2006/02/28 23:11:59  lollisoft
# * Try -k
# *
# * Revision 1.85  2006/02/28 20:23:04  lollisoft
# * Test existence of ../AppDevelopment
# *
# * Revision 1.84  2006/02/28 19:40:04  lollisoft
# * Removed unused vendor targets
# *
# * Revision 1.83  2006/02/28 11:26:58  lollisoft
# * Set TARGETFRAMEWORK to so for Linux
# *
# * Revision 1.82  2006/02/26 23:46:18  lollisoft
# * Changed build method for shared libraries under Mac OS X
# * to be frameworks. These would be embedable into the
# * application bundle - thus enables better install method.
# *
# * Revision 1.81  2006/02/24 14:25:23  lollisoft
# * Fix wrong path
# *
# * Revision 1.80  2006/02/21 19:35:50  lollisoft
# * Implemented autoload mechanism of last loaded application.
# * It demonstrates the new capabilities operating with files.
# *
# * Revision 1.79  2006/02/16 22:48:38  lollisoft
# * Tested last wxAUI layout changes under Linux. It builds and runs.
# *
# * Revision 1.78  2006/02/15 12:47:12  lollisoft
# * Added wxAUI target.
# *
# * Revision 1.77  2006/01/29 09:36:33  lollisoft
# * Don't build TVision. It should completely be in my private makefile.
# *
# * Revision 1.76  2006/01/20 00:58:24  lollisoft
# * Changed order to enable building AppDevelopment tree.
# * This is a hook for users of lbDMF framework.
# *
# * Revision 1.75  2006/01/10 23:37:42  lollisoft
# * Added Goldparser for usability testing.
# *
# * Revision 1.74  2005/12/06 17:04:25  lollisoft
# * Last make problems under Linux
# *
# * Revision 1.73  2005/12/06 15:54:56  lollisoft
# * Changes let the GUI work properly in debug mode. But there is a NULL
# * pointer exeption in release mode near opening a database form.
# *
# * Testing on Mac OS X and Linux.
# *
# * Revision 1.72  2005/11/11 22:51:30  lollisoft
# * Memory leaks removed. There are currently only 4 chunks leaky.
# * These may be false positives, because one of them is an allocated
# * wxMenu instance, I have not to delete after adding it to a wxMenuBar.
# * wxMenuBar gets an owner (see wxWidgets documentation).
# *
# * Revision 1.71  2005/11/07 10:08:54  lollisoft
# * Windows was missing the new TARGETSHARED definition.
# *
# * Revision 1.70  2005/11/06 19:25:32  lollisoft
# * All bugs of unloading shared libraries removed.\nUsing dlopen more than once per shared library leads into unability to unload that library.\nMac OS X seems to not properly handle the reference counting, thus unloading of twice loaded shared libs fails.\n\nI have implemented a workaround to handle this properly.\n\nThere is one exeption: lbModule.so is needed by UAP macros, thus this shared library is left loaded and the system can unload it for me.
# *
# * Revision 1.69  2005/10/28 17:28:42  lollisoft
# * Fixed memory leaks in database classes. Using it in console is tested.
# * There now are only three objects leaked.
# *
# * Revision 1.68  2005/10/05 10:02:50  lollisoft
# * Creating help files was sensitive for errors and stops further making.
# *
# * Revision 1.67  2005/10/03 17:15:14  lollisoft
# * Latest changes for release 0.5.1 under Linux
# *
# * Revision 1.66  2005/09/24 21:41:32  lollisoft
# * Deactivated building tvision stuff. Not yet part of an usable sample.
# *
# * Revision 1.65  2005/09/11 06:33:11  lollisoft
# * Using stdandard make for wx sample app. Added wxWrapperDLL target.
# *
# * Revision 1.64  2005/09/09 18:06:18  lollisoft
# * Commented out libxml2.
# *
# * Revision 1.63  2005/09/07 20:49:46  lollisoft
# * Minor changes due to wxWidgets 2.6.1 usage under Windows.
# *
# * Revision 1.62  2005/08/22 16:33:03  lollisoft
# * Added wxWrapperDLL target for OSX.
# *
# * Revision 1.61  2005/08/21 23:25:50  lollisoft
# * Moving code to wxWrapper DLL/so module.
# *
# * Revision 1.60  2005/08/08 19:18:44  lollisoft
# * Minor changes.
# *
# * Revision 1.59  2005/07/14 19:36:50  lollisoft
# * Compiling SET's version of my tvision test application.
# *
# * Revision 1.58  2005/07/13 20:12:54  lollisoft
# * Changed wxWidgets built to bundle type.
# *
# * Revision 1.57  2005/06/30 07:30:33  lollisoft
# * Added building of login wizard plugin under Mac OS X.
# *
# * Revision 1.56  2005/06/24 23:09:47  lollisoft
# * Changes to build with new wxWidgets version 2.6.1.
# * Added fallback to hardcoded settings, if no environment
# * variables are found. Logging changed to reside in a
# * $(HOME)/log directory.
# *
# * GUI application build process enhanced to also make the
# * bundle. App runs from clicking on the desktop icon.
# *
# * Revision 1.55  2005/06/21 15:15:00  lollisoft
# * Added login wizard plugin under Linux
# *
# * Revision 1.54  2005/06/03 12:34:43  lollisoft
# * Compile tvision-set instead of my version. Better to work together.
# *
# * Revision 1.53  2005/05/15 19:24:40  lollisoft
# * Added new target under osx.
# *
# * Revision 1.52  2005/05/11 08:58:27  lollisoft
# * Little changes to get compiled tvision sample. Compiler switch changes.
# *
# * Revision 1.51  2005/05/10 22:37:47  lollisoft
# * Removed unused code.
# *
# * Revision 1.50  2005/05/10 15:03:23  lollisoft
# * Made Linux make more silent
# *
# * Revision 1.49  2005/05/09 22:20:34  lollisoft
# * Changes to also compile C source code.
# *
# * Revision 1.48  2005/05/03 21:07:18  lollisoft
# * More dependency to doxygen
# *
# * Revision 1.47  2005/04/29 20:49:41  lollisoft
# * Added more files in dependency to help generation
# *
# * Revision 1.46  2005/04/24 19:26:42  lollisoft
# * Moved making of help files to the end of make process
# *
# * Revision 1.45  2005/04/24 18:46:31  lollisoft
# * New modules
# *
# * Revision 1.44  2005/04/23 10:52:07  lollisoft
# * Try to add tvision target
# *
# * Revision 1.43  2005/04/13 21:32:37  lollisoft
# * Restructuring making of subdirectories.
# *
# * Revision 1.42  2005/03/16 23:38:07  lollisoft
# * Missing define to build wx so plugins
# *
# * Revision 1.41  2005/03/16 23:01:25  lollisoft
# * Automatically creating target directories for plugins
# *
# * Revision 1.40  2005/03/16 22:01:57  lollisoft
# * Added creating dll/libs dir under windows
# *
# * Revision 1.39  2005/03/16 20:31:55  lollisoft
# * DEVROOT / DEVROOT_MAKE and DEVROOT_MAKE_INTERNAL clashes
# * and cleanup.
# *
# * Revision 1.38  2005/03/16 00:27:36  lollisoft
# * Last changes to full automatic compiling under OSX.
# *
# * Revision 1.37  2005/03/15 22:26:39  lollisoft
# * More changes on OSX to compile plugins
# *
# * Revision 1.36  2005/03/15 22:17:52  lollisoft
# * mkmk and make process under linux improoved
# *
# * Revision 1.35  2005/03/15 14:43:51  lollisoft
# * Changes for linux to build and let GUI running with plugins
# *
# * Revision 1.34  2005/03/06 12:02:45  lollisoft
# * Added touching lbkey.h in include directory to avoid build failures (osx)
# *
# * Revision 1.33  2005/03/06 11:53:46  lollisoft
# * Changes to automatically make dosdir
# *
# * Revision 1.32  2005/03/06 00:43:56  lollisoft
# * Minor changes to auto compile mkmk as bootstrap
# *
# * Revision 1.31  2005/03/05 23:28:05  lollisoft
# * Initial wx plugin attempt
# *
# * Revision 1.30  2005/03/05 23:13:33  lollisoft
# * More changes to build source tree under Mac OS X
# *
# * Revision 1.29  2005/03/03 08:33:56  lollisoft
# * Added plugins to compile
# *
# * Revision 1.28  2005/03/02 20:05:57  lollisoft
# * Added new module lbLoginWizard and bugfixes
# *
# * Revision 1.27  2005/02/10 19:14:11  lollisoft
# * Why ?
# *
# * Revision 1.26  2005/02/10 16:59:05  lollisoft
# * Changes for Mac OS X
# *
# * Revision 1.25  2005/02/10 12:48:25  lollisoft
# * Changes for Mac OS X
# *
# * Revision 1.24  2005/02/03 19:56:41  lollisoft
# * Samples and more dependencies in documentation
# *
# * Revision 1.23  2005/02/02 13:30:15  lollisoft
# * Latest changes for version 0.4.1
# *
# * Revision 1.22  2005/01/27 12:47:21  lollisoft
# * Minor bugfixes
# *
# * Revision 1.21  2005/01/25 14:05:50  lollisoft
# * Minor changes
# *
# * Revision 1.20  2005/01/25 12:28:34  lollisoft
# * Changes for linux due to several reasons. The GUI sample has still problems with database access. Crash in lbDB.cpp while creating bound columns. Console works
# *
# * Revision 1.19  2005/01/24 22:21:01  lollisoft
# * Changes on Linux to get database access running. Login and selecting / loading an application works. But the application would not load
# *
# * Revision 1.18  2005/01/23 15:23:43  lollisoft
# * Last changes before release 0.4.0
# *
# * Revision 1.17  2005/01/22 15:01:25  lollisoft
# * Commented out lbhook
# *
# * Revision 1.16  2005/01/22 11:59:42  lollisoft
# * Restructuring
# *
# * Revision 1.15  2005/01/05 13:41:36  lollisoft
# * New dynamic application implementation works
# *
# * Revision 1.14  2004/12/14 16:15:06  lollisoft
# * Also make wxWrapper with mkmk and the like.
# *
# * Revision 1.13  2004/10/16 11:59:30  lollisoft
# * Adopted new make system to linux
# *
# * Revision 1.12  2004/10/16 10:10:38  lollisoft
# * Added the doxygen rule depending on lbInterfaces.h
# *
# * Revision 1.11  2004/10/16 09:47:37  lollisoft
# * New make system works nearly perfect. It does not longer build unnessesary.
# *
# * Revision 1.10  2004/10/09 18:01:27  lollisoft
# * Added distclean feature
# *
# * Revision 1.9  2004/10/09 17:22:51  lollisoft
# * Changed make process for wx based apps
# *
# * Revision 1.8  2004/10/09 16:52:46  lollisoft
# * Enhancements for cleaning up
# *
# * Revision 1.7  2004/08/17 20:04:02  lollisoft
# * Deactivated parts, that do not compile under Linux and added demo app module including sample apps
# *
# * Revision 1.6  2004/07/18 07:28:25  lollisoft
# * Now the database sample works also under linux. Some bugs solved and minor changes
# *
# * Revision 1.5  2004/06/06 12:55:58  lollisoft
# * Added new module lbPluginManager
# *
# * Revision 1.4  2003/05/24 02:09:44  lollisoft
# * Added lbDB module
# *
# * Revision 1.3  2003/02/17 21:34:33  lollisoft
# * Much problems with compilation solved, bu wy came this ??
# *
# * Revision 1.2  2002/11/29 19:50:26  lothar
# * Compiles again under linux, but some problems at runtime with DOMString
# *
# * Revision 1.1  2001/10/14 10:25:56  lothar
# * Initial
# *
# **************************************************************

# Change to see join triggers are working as expected.

#
# False targets
#
#.PHONY: dummy

ifeq ($(CRUISECONTROL), yes)
RELPATH=/Projects/CPP
else
RELPATH=/Projects/CPP
endif



ifeq ($(OSTYPE), solaris)
DEVROOT_MAKE=$(DEVROOT)

ifndef prefix
prefix=$(HOME)
endif

endif

ifeq ($(OSTYPE), linux-debian-ppc)
DEVROOT_MAKE=$(DEVROOT)

ifndef prefix
prefix=$(HOME)
endif

endif

ifeq ($(OSTYPE), linux)
DEVROOT_MAKE=$(DEVROOT)

ifndef prefix
prefix=$(HOME)
endif

endif

ifeq ($(OSTYPE), osx)
DEVROOT_MAKE=$(DEVROOT)

ifndef prefix
prefix=$(HOME)
endif

OSVERSION_=$(OSVERSION)
OSPLATFORM_=$(OSPLATFORM)

#OSVERSION=9.0.0
#OSPLATFORM=ppc

OSNAME=Panther

ifeq ($(OSVERSION_), 9.0.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 9.1.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 9.6.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 9.8.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 10.0.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 10.2.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 10.4.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 10.5.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 10.7.0)
OSNAME=Leopard
endif

ifeq ($(OSVERSION_), 10.8.0)
OSNAME=Leopard
endif

endif

ifeq ($(OSTYPE), Windows_NT)
DEVROOT_MAKE=$(DEVROOT_MAKE_BASE)
WGET=wget
CURL=curl --cacert $(DEVROOT_MAKE)/Tools/curl/ca-bundle.crt
TAR=tar
endif

ifeq ($(OSTYPE), Cross_OW)
DEVROOT_MAKE=$(DEVROOT)
endif

Path=$(PATH)


#
# The BASEDIRECTORIES is intended to hook in other projects into the directory structure.
# This means, that these directories are for general intent. I would create some modules,
# plugins or even different applications.
#
# To enable one build process, these directories are predefined or checked for it's existence.

MAKE_CONFIG_FILE=$(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure

ifndef RPMBUILD
ifeq ($(OSTYPE), linux-debian-ppc)
BASEDIRECTORIES= \
	../Plugins \
	../Modules \
	../RegressionTests \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../UnitTests \
	../AppDevelopment
endif
endif

ifdef RPMBUILD
ifeq ($(OSTYPE), linux-debian-ppc)
BASEDIRECTORIES= \
	../Plugins \
	../UnitTests \
	../Modules
endif
endif


ifndef RPMBUILD
ifeq ($(OSTYPE), solaris)
BASEDIRECTORIES= \
	../Plugins \
	../Modules \
	../RegressionTests \
	../UnitTests \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../AppDevelopment
endif

ifeq ($(OSTYPE), linux)
ifndef CRUISECONTROL
BASEDIRECTORIES= \
	../Plugins \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../Modules \
	../UnitTests \
	../RegressionTests \
	../AppDevelopment
endif

ifdef CRUISECONTROL
BASEDIRECTORIES= \
	../Plugins \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../Modules \
	../UnitTests \
	../RegressionTests
endif


#	../ServerPlugins \
#	../ClientPlugins
#

#	../vendor/tvision-set \
#	../vendor/tvision-set/examples/lbDMF
#	../../open-watcom
endif
endif

ifdef RPMBUILD
ifeq ($(OSTYPE), solaris)
BASEDIRECTORIES= \
	../Plugins \
	../UnitTests \
	../Modules
endif
ifeq ($(OSTYPE), linux)
BASEDIRECTORIES= \
	../Plugins \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../UnitTests \
	../Modules
endif
endif


ifeq ($(OSTYPE), Windows_NT)
BASEDIRECTORIES= \
	../Plugins \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../Modules \
	../RegressionTests \
	../AppDevelopment \
	../UnitTests

# Don't compile these every time.
#	../vendor/propgrid \
#	../vendor/wxaui-0.9.1/sample \
#	../vendor/tvision \
#	../vendor/tvision/examples/lbDMF \
#	../vendor/tvision/examples/dlgdsn \
#	../vendor/tvision/examples/listvi \
#	../vendor/wxReportWriter \

endif

ifeq ($(OSTYPE), Cross_OW)
BASEDIRECTORIES= \
	../Plugins \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../Modules \
	../RegressionTests \
	../vendor/wxaui-0.9.1/sample \
	../AppDevelopment

endif


ifeq ($(OSTYPE), osx)

BASEDIRECTORIES= \
	../Plugins \
	../AppDevelopmentDemo/DynamicApp/Plugins \
	../Modules \
	../RegressionTests \
	../vendor/wxaui-0.9.1/sample \
	../AppDevelopment \
	../ServerPlugins \
	../ClientPlugins \
	../UnitTests

#	../vendor/tvision \
#	../vendor/tvision/examples/lbDMF

TARGETDLL=sobundle
TARGETSHARED=so
TARGETEXE=elf
TARGETWXEXE=bundle
TARGET_TV_DLL=tvision_dll
TARGET_TV_EXE=tvision_elf
TARGETPLUGIN=soplugin
TARGETSOBUNDLE=sobundle
TARGETWXSO=wxso
TARGETWXSHARED=wxshared
TARGETWXPLUGIN=wxsoplugin
TARGETFRAMEWORK=framework
TARGETWXFRAMEWORK=wxframework
TARGETYACC=yacc
TARGETLEX=lex

ALLTARGETS = \
	$(prefix)/bin \
	$(prefix)/Library \
	$(prefix)/Library/Frameworks \
	$(prefix)/lib \
	$(prefix)/plugins \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbModule \
	lbMetaApplication \
	lbclasses \
	lbWorkflowEngine \
	lbDB \
	lbPluginManager \
	lbcs \
	lbtransfer \
	../vendor/propgrid \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxJSON-1.2.1/src \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxPlugins/lbCryptoStream \
	../vendor/sqlite \
	../vendor/databaselayer/src/Implementations/Sqllite \
	../vendor/databaselayer/tests \
	../vendor/antlr3/src \
	../Test/Console/XML \
	../vendor/wxShapeFramework/src \
	$(BASEDIRECTORIES) \
	../Test/GUI/wxWrapper \
	../AppDevelopmentDemo/MkBs \
	../vendor/wxShapeFramework/samples/wxSFDemo

#	../vendor/goldparserengine/src \
#	../vendor/goldparserengine/samples/engine \
#	../vendor/goldparserengine/samples/gptest \
#	../vendor/wxARG/src \
#	../vendor/databaselayer/src/Implementations/ODBC \
#	../vendor/cryptostream/src/crypstrm \
#	../vendor/dbwrapcontrols \
#	../vendor/databaselayer/tests \


ALLDIRS = \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbWorkflowEngine \
	lbMetaApplication \
	lbPluginManager \
	lbcs \
	lbtransfer \
	../vendor/propgrid \
	../vendor/databaselayer/src/Implementations/Sqllite \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxaui-0.9.1/sample \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxPlugins/lbCryptoStream \
	$(BASEDIRECTORIES)

#	../vendor/cryptostream/src/crypstrm \

endif

ifeq ($(OSTYPE), linux-debian-ppc)

TARGETDLL=so
TARGETFRAMEWORK=so
TARGETEXE=elf
TARGETSHARED=so
TARGETWXEXE=elf
TARGETWXSO=wxso
TARGET_TV_DLL=tvision_dll
TARGET_TV_EXE=tvision_elf
TARGETPLUGIN=soplugin
TARGETWXPLUGIN=wxsoplugin
TARGETWXSHARED=so
TARGETYACC=yacc
TARGETLEX=lex

ifdef RPMBUILD
ALLDIRS = \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbWorkflowEngine \
	lbMetaApplication \
	lbPluginManager \
	lbcs \
	lbtransfer \
	../vendor/propgrid \
	../vendor/sqlite \
	../vendor/antlr3/src \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxJSON-1.2.1/src \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxPlugins/lbCryptoStream \
	$(BASEDIRECTORIES)

#	../vendor/cryptostream/src/crypstrm \


endif

ifndef RPMBUILD
ALLDIRS = \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbWorkflowEngine \
	lbMetaApplication \
	lbPluginManager \
	lbcs \
	lbtransfer \
	../vendor/propgrid \
	../vendor/sqlite \
	../vendor/antlr3/src \
	../vendor/databaselayer/src/Implementations/Sqllite \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxJSON-1.2.1/src \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxPlugins/lbCryptoStream \
	$(BASEDIRECTORIES)

#	../vendor/cryptostream/src/crypstrm \


endif

ALLTARGETS = \
	$(prefix)/bin \
	$(prefix)/lib \
	$(prefix)/plugins \
	$(ALLDIRS)

endif

ifeq ($(OSTYPE), solaris)

TARGETDLL=so
TARGETFRAMEWORK=so
TARGETEXE=elf
TARGETSHARED=so
TARGETWXSHARED=so
TARGETWXEXE=elf
TARGETWXSO=wxso
TARGET_TV_DLL=tvision_dll
TARGET_TV_EXE=tvision_elf
TARGETPLUGIN=soplugin
TARGETWXPLUGIN=wxsoplugin
TARGETYACC=yacc
TARGETLEX=lex

ifdef RPMBUILD
ALLDIRS = \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbWorkflowEngine \
	lbMetaApplication \
	lbPluginManager \
	lbcs \
	lbtransfer \
	../vendor/propgrid \
	../vendor/sqlite \
	../vendor/antlr3/src \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxJSON-1.2.1/src \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxPlugins/lbCryptoStream \
	$(BASEDIRECTORIES)

#	../vendor/cryptostream/src/crypstrm \


endif

ifndef RPMBUILD
ALLDIRS = \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbWorkflowEngine \
	lbMetaApplication \
	lbPluginManager \
	lbcs \
	lbtransfer \
	../vendor/propgrid \
	../vendor/sqlite \
	../vendor/antlr3/src \
	../vendor/databaselayer/src/Implementations/Sqllite \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxJSON-1.2.1/src \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxPlugins/lbCryptoStream \
	$(BASEDIRECTORIES)

#	../vendor/cryptostream/src/crypstrm \

endif

ALLTARGETS = \
	$(prefix)/bin \
	$(prefix)/lib \
	$(prefix)/plugins \
	$(ALLDIRS)

endif

ifeq ($(OSTYPE), linux)

TARGETDLL=so
TARGETFRAMEWORK=so
TARGETEXE=elf
TARGETSHARED=so
TARGETWXSHARED=so
TARGETWXEXE=elf
TARGETWXSO=wxso
TARGET_TV_DLL=tvision_dll
TARGET_TV_EXE=tvision_elf
TARGETPLUGIN=soplugin
TARGETWXPLUGIN=wxsoplugin
TARGETYACC=yacc
TARGETLEX=lex

ifdef RPMBUILD
ALLDIRS = \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbWorkflowEngine \
	lbMetaApplication \
	lbPluginManager \
	lbcs \
	lbtransfer \
	../vendor/propgrid \
	../vendor/sqlite \
	../vendor/antlr3/src \
	../vendor/databaselayer/src/Implementations/Sqllite \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxJSON-1.2.1/src \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../AppDevelopmentDemo/MkBs \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxPlugins/lbCryptoStream \
	../vendor/wxShapeFramework/src \
	$(BASEDIRECTORIES)

#	../vendor/cryptostream/src/crypstrm \
#	../vendor/databaselayer/src/Implementations/ODBC \
#	../vendor/dbwrapcontrols
endif

ifndef RPMBUILD
ALLDIRS = \
	../vendor/dosdir \
	../vendor/mkmk \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbWorkflowEngine \
	lbMetaApplication \
	lbPluginManager \
	lbcs \
	lbtransfer \
	../vendor/propgrid \
	../vendor/sqlite \
	../vendor/antlr3/src \
	../vendor/databaselayer/src/Implementations/Sqllite \
	../vendor/dbwrapcontrols \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxJSON-1.2.1/src \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../AppDevelopmentDemo/MkBs \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxPlugins/lbCryptoStream \
	../vendor/wxShapeFramework/src \
	$(BASEDIRECTORIES)

#	../vendor/cryptostream/src/crypstrm \
#	../vendor/databaselayer/src/Implementations/ODBC \

endif

ALLTARGETS = \
	$(prefix)/bin \
	$(prefix)/lib \
	$(prefix)/plugins \
	$(ALLDIRS)

endif

ifeq ($(OSTYPE), Windows_NT)


TARGET_SELECTOR=_target_mingw
#TARGET_SELECTOR=

TARGETEXE=exe$(TARGET_SELECTOR)
TARGETWXEXE=exe$(TARGET_SELECTOR)
TARGETDLL=dll$(TARGET_SELECTOR)
TARGETFRAMEWORK=dll$(TARGET_SELECTOR)
TARGETSHARED=dll$(TARGET_SELECTOR)
TARGETWXSHARED=dll$(TARGET_SELECTOR)
TARGETXSLTDLL=xsltdll$(TARGET_SELECTOR)
TARGETPLUGIN=plugin$(TARGET_SELECTOR)
TARGETWXPLUGIN=wxplugin$(TARGET_SELECTOR)

TARGET_TV_DLL=tvision_dll$(TARGET_SELECTOR)
TARGET_TV_EXE=tvision_exe$(TARGET_SELECTOR)
TARGETYACC=yacc
TARGETLEX=lex

bla = \
	../../open-watcom

ALLTARGETS = \
	../../lib \
	../../dll/libs \
	../../plugins/libs \
	lbHook \
	lbtransfer \
	lbDB \
	lbModule \
	lbclasses \
	lbWorkflowEngine \
	lbMetaApplication \
	lbPluginManager \
	lbcs \
	lbtransfer \
	../vendor/propgrid \
	../Test/GUI/wxWrapperDLL \
	../vendor/sqlite \
	../vendor/antlr3/src \
	../vendor/databaselayer/src/Implementations/Sqllite \
	../vendor/libxml2-2.8.0/win32/bin.mingw/libxml2.dll \
	../vendor/libxslt-1.1.21/libxslt \
	../vendor/wxJSON-1.2.1/src \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxPlugins/lbCryptoStream \
	../Samples/HelloWorld \
	../vendor/wxShapeFramework/src \
	$(BASEDIRECTORIES) \
	../Doc/html \
	../AppDevelopmentDemo/MkBs \
	../vendor/wxShapeFramework/samples/wxSFDemo

#	lbcs \
#	../vendor/databaselayer/src/Implementations/ODBC \
#	../vendor/cryptostream/src/crypstrm \
#	../vendor/wxaui-0.9.1/src \
#	../vendor/dbwrapcontrols
# sqlitefk is included in Sqllite target, but may be used separately including this target.
# When including this target, the include path for sql.h must pount to ./sqlite/src
#	../vendor/databaselayer/src/Implementations/Sqllite/sqlitefk/build/mkmk

ALLDIRS = \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbWorkflowEngine \
	lbMetaApplication \
	lbPluginManager \
	lbcs \
	lbtransfer \
	../vendor/propgrid \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxaui-0.9.1/sample \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxPlugins/lbCryptoStream \
	$(BASEDIRECTORIES)


#	../vendor/cryptostream/src/crypstrm \
#$(DEVROOT_MAKE)/wxwin/wx/samples/report \
#tvision: ../vendor/tvision
#	Q:/develop/wxwin/wx/contrib/wxCode/components/wxxml2/thirdparty/libxml2 \

endif

ifeq ($(OSTYPE), Cross_OW)

TARGETDLL=dll_cross
TARGETXSLTDLL=xsltdll
TARGETFRAMEWORK=dll
TARGETSHARED=dll
TARGETWXSHARED=dll
TARGETEXE=exe
TARGETWXEXE=exe
TARGETPLUGIN=plugin
TARGETWXPLUGIN=wxplugin
TARGET_TV_DLL=tvision_dll
TARGET_TV_EXE=tvision_exe
TARGETYACC=yacc
TARGETLEX=lex

bla = \
	../../open-watcom

ALLTARGETS = \
	../../lib \
	../../dll/libs \
	../../plugins/libs \
	lbHook \
	lbtransfer \
	lbcs \
	lbDB \
	lbModule \
	lbclasses \
	lbWorkflowEngine \
	lbMetaApplication \
	lbPluginManager \
	lbcs \
	lbtransfer \
	../vendor/propgrid \
	../vendor/sqlite \
	../vendor/antlr3/src \
	../vendor/databaselayer/src/Implementations/Sqllite \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxJSON-1.2.1/src \
	../vendor/libxml2-2.8.0/win32/bin.mingw/libxml2.dll \
	../vendor/libxslt-1.1.21/libxslt \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxPlugins/lbCryptoStream \
	../Samples/HelloWorld \
	../Doc/html \
	$(BASEDIRECTORIES)

#	../vendor/cryptostream/src/crypstrm \
#	../vendor/databaselayer/src/Implementations/ODBC \
#	../vendor/dbwrapcontrols
# sqlitefk is included in Sqllite target, but may be used separately including this target.
# When including this target, the include path for sql.h must pount to ./sqlite/src
#	../vendor/databaselayer/src/Implementations/Sqllite/sqlitefk/build/mkmk

ALLDIRS = \
	lbHook \
	lbDB \
	lbModule \
	lbclasses \
	lbWorkflowEngine \
	lbMetaApplication \
	lbPluginManager \
	lbcs \
	lbtransfer \
	../vendor/propgrid \
	../vendor/wxaui-0.9.1/src \
	../vendor/wxaui-0.9.1/sample \
	../AppDevelopmentDemo/App \
	../AppDevelopmentDemo/DynamicApp/App \
	../Test/Console/XML \
	../Test/GUI/wxWrapperDLL \
	../Test/GUI/wxWrapper \
	../Test/GUI/wxPlugins/lbLoginWizard \
	../Test/GUI/wxPlugins/lbCryptoStream \
	$(BASEDIRECTORIES)


#	../vendor/cryptostream/src/crypstrm \
#$(DEVROOT_MAKE)/wxwin/wx/samples/report \
#tvision: ../vendor/tvision
#	Q:/develop/wxwin/wx/contrib/wxCode/components/wxxml2/thirdparty/libxml2 \

endif


all_targets: $(ALLTARGETS)

ifndef RPMBUILD

ifeq ($(CRUISECONTROL), yes)

install:
	for sub_target in $(ALLDIRS); do \
		echo Install CRUISECONTROL $$sub_target; \
		$(MAKE) -C $$sub_target install; \
	done

else

install:
	for sub_target in $(ALLDIRS); do \
		echo Install $$sub_target; \
		$(MAKE) -C $$sub_target install; \
	done
	-$(MAKE) -C ../AppDevelopment install

endif

install-strip:
	for sub_target in $(ALLDIRS); do \
		$(MAKE) -C $$sub_target install-strip; \
	done
	echo mkdir -p $(prefix)/lib
	mkdir -p $(prefix)/share
	mkdir -p $(prefix)/share/lbdmf
	mkdir -p $(prefix)/share/lbdmf/toolbarimages
	cp $(DEVROOT_MAKE)$(RELPATH)/Test/GUI/wxWrapper/toolbarimages/*.png $(prefix)/share/lbdmf/toolbarimages
	cp $(DEVROOT_MAKE)$(RELPATH)/Test/GUI/wxWrapper/toolbarimages/*.xpm $(prefix)/share/lbdmf/toolbarimages

endif

ifdef RPMBUILD

install:
	for sub_target in $(ALLDIRS); do \
		$(MAKE) -C $$sub_target install; \
	done
	echo mkdir -p $(prefix)/lib
	mkdir -p $(prefix)/share
	mkdir -p $(prefix)/share/lbdmf
	mkdir -p $(prefix)/share/applications
	mkdir -p $(prefix)/share/lbdmf/toolbarimages
	mkdir -p $(prefix)/share/lbdmf/UMLSamples
	mkdir -p $(prefix)/share/lbdmf/Doc
	mkdir -p $(prefix)/share/lbdmf/include
	mkdir -p $(prefix)/share/lbdmf/XMIToDMF
	mkdir -p $(prefix)/share/lbdmf/DMFToXMI
	mkdir -p $(prefix)/share/lbdmf/database
	mkdir -p $(prefix)/share/lbdmf/TurboVision
	mkdir -p $(prefix)/share/lbdmf/wxLua
	mkdir -p $(prefix)/share/lbdmf/wxActiveRecords
	mkdir -p $(prefix)/share/lbdmf/lbDMFDataViewModel
	mkdir -p $(prefix)/share/lbdmf/lbDMFFixedFormular
	cp $(DEVROOT_MAKE)$(RELPATH)/Database/*.sql $(prefix)/share/lbdmf/database
	cp $(DEVROOT_MAKE)$(RELPATH)/Test/GUI/wxWrapper/toolbarimages/*.png $(prefix)/share/lbdmf/toolbarimages
	cp $(DEVROOT_MAKE)$(RELPATH)/Test/GUI/wxWrapper/toolbarimages/*.xpm $(prefix)/share/lbdmf/toolbarimages
	cp $(DEVROOT_MAKE)$(RELPATH)/Test/GUI/wxWrapper/splash.png $(prefix)/share/lbdmf
	cp $(DEVROOT_MAKE)$(RELPATH)/Test/GUI/wxWrapper/lbdmf.png $(prefix)/share/lbdmf
	cp $(DEVROOT_MAKE)$(RELPATH)/Test/GUI/wxWrapper/wxWrapper.desktop $(prefix)/share/lbdmf
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/include/*.xml $(prefix)/share/lbdmf/include
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/include/*.xsl $(prefix)/share/lbdmf/include
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/include/XMISettingsTemplate.xsl $(prefix)/share/lbdmf/XMIToDMF/XMISettings.xsl
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/XMIToDMF/*.xsl $(prefix)/share/lbdmf/XMIToDMF
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/DMFToXMI/*.xsl $(prefix)/share/lbdmf/DMFToXMI
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/lbDMFDataViewModel/*.xsl $(prefix)/share/lbdmf/lbDMFDataViewModel
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/lbDMFFixedFormular/*.xsl $(prefix)/share/lbdmf/lbDMFFixedFormular
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/TurboVision/*.xsl $(prefix)/share/lbdmf/TurboVision
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/wxActiveRecords/*.xsl $(prefix)/share/lbdmf/wxActiveRecords
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/wxLua/*.xsl $(prefix)/share/lbdmf/wxLua
	cp -R $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/UMLSamples $(prefix)/share/lbdmf
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/Doc/*.pdf $(prefix)/share/lbdmf/Doc
	./copy-wxGTK-libs.sh $(prefix)

install-strip:
	for sub_target in $(ALLDIRS); do \
		$(MAKE) -C $$sub_target install-strip; \
	done
	echo mkdir -p $(prefix)/lib
	mkdir -p $(prefix)/share
	mkdir -p $(prefix)/share/lbdmf
	mkdir -p $(prefix)/share/applications
	mkdir -p $(prefix)/share/lbdmf/toolbarimages
	mkdir -p $(prefix)/share/lbdmf/UMLSamples
	mkdir -p $(prefix)/share/lbdmf/Doc
	mkdir -p $(prefix)/share/lbdmf/include
	mkdir -p $(prefix)/share/lbdmf/XMIToDMF
	mkdir -p $(prefix)/share/lbdmf/DMFToXMI
	mkdir -p $(prefix)/share/lbdmf/database
	mkdir -p $(prefix)/share/lbdmf/TurboVision
	mkdir -p $(prefix)/share/lbdmf/wxLua
	mkdir -p $(prefix)/share/lbdmf/wxActiveRecords
	mkdir -p $(prefix)/share/lbdmf/lbDMFDataViewModel
	mkdir -p $(prefix)/share/lbdmf/lbDMFFixedFormular
	cp $(DEVROOT_MAKE)$(RELPATH)/Database/*.sql $(prefix)/share/lbdmf/database
	cp $(DEVROOT_MAKE)$(RELPATH)/Test/GUI/wxWrapper/toolbarimages/*.png $(prefix)/share/lbdmf/toolbarimages
	cp $(DEVROOT_MAKE)$(RELPATH)/Test/GUI/wxWrapper/toolbarimages/*.xpm $(prefix)/share/lbdmf/toolbarimages
	cp $(DEVROOT_MAKE)$(RELPATH)/Test/GUI/wxWrapper/splash.png $(prefix)/share/lbdmf
	cp $(DEVROOT_MAKE)$(RELPATH)/Test/GUI/wxWrapper/lbdmf.png $(prefix)/share/lbdmf
	cp $(DEVROOT_MAKE)$(RELPATH)/Test/GUI/wxWrapper/wxWrapper.desktop $(prefix)/share/lbdmf
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/include/*.xml $(prefix)/share/lbdmf/include
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/include/*.xsl $(prefix)/share/lbdmf/include
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/XMIToDMF/*.xmi $(prefix)/share/lbdmf/XMIToDMF
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/XMIToDMF/*.xsl $(prefix)/share/lbdmf/XMIToDMF
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/include/XMISettingsTemplate.xsl $(prefix)/share/lbdmf/XMIToDMF/XMISettings.xsl
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/DMFToXMI/*.xsl $(prefix)/share/lbdmf/DMFToXMI
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/lbDMFDataViewModel/*.xsl $(prefix)/share/lbdmf/lbDMFDataViewModel
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/lbDMFFixedFormular/*.xsl $(prefix)/share/lbdmf/lbDMFFixedFormular
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/TurboVision/*.xsl $(prefix)/share/lbdmf/TurboVision
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/wxActiveRecords/*.xsl $(prefix)/share/lbdmf/wxActiveRecords
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/XSLT_Templates/wxLua/*.xsl $(prefix)/share/lbdmf/wxLua
	cp -R $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/UMLSamples $(prefix)/share/lbdmf
	mv "$(prefix)/share/lbdmf/UMLSamples/SecondStageModels/lbDMF Manager.xmi" "$(prefix)/share/lbdmf/UMLSamples/SecondStageModels/lbDMFManager.xmi"
	cp $(DEVROOT_MAKE)$(RELPATH)/AppDevelopmentDemo/DynamicApp/Doc/*.pdf $(prefix)/share/lbdmf/Doc
	./copy-wxGTK-libs.sh $(prefix)

endif

test-ldd:
	./copy-wxGTK-libs.sh $(prefix)

../../bin:
	-mkdir ../../bin
	
../../lib:
	-mkdir ../../lib

../../dll:
	-mkdir ../../dll

../../dll/libs: ../../dll
	-mkdir ../../dll/libs

../../plugins:
	-mkdir ../../plugins

../../plugins/libs: ../../plugins
	-mkdir ../../plugins/libs

$(prefix)/Library:
	-mkdir -p $@

$(prefix)/Library/Frameworks:
	-mkdir -p $@

$(prefix)/bin:
	-mkdir -p $@

$(prefix)/lib:
	-mkdir -p $@

$(prefix)/plugins:
	-mkdir -p $@

clean:
	@for d in $(ALLDIRS); do \
	  $(MAKE) -C $$d clean; \
	done

distclean:
	touch Makefile
#	@for d in $(ALLDIRS); do \
#	    echo $$d ; \
#	    cp $$d/makefile $$d/makefile.clean; \
#	    $(MAKE) -C $$d distclean -f makefile.clean || exit $? ; \
#	    rm $$d/makefile.clean; \
#	done

mkrelease:
	@for d in $(ALLDIRS); do \
	    $(MAKE) -C $$d clean || exit $? ; \
	done
	cd ../..; tar cvzf lbDMF-0.3.2.3.tgz CPP; cd CPP/BaseDevelopment

#	Doesn't compile yet under linux
#	lbPluginManager \
#	Doesn't compile if XML dependend module XML4C (alphaworks) is not installed
#	lbXMLConfig/lbDOMConfig \

dummy:

../vendor/databaselayer/src/Implementations/ODBC: dummy
	$(MAKE) -s -C $@ -e MODULE=databaselayer_odbc -e TARGET=$(TARGETWXSHARED) -e CUSTOM_FILES=../../*.cpp -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../../bin/bison.simple: ../../bin
	-cp ../vendor/databaselayer/src/Implementations/Sqllite/sqlitefk/src/bison.simple ../../bin/bison.simple
	
ifneq ($(OSTYPE), Windows_NT)
../vendor/databaselayer/src/Implementations/Sqllite: dummy
	@echo Build Grammar makefile
	$(MAKE) -s -C $@/sqlitefk/src -e MODULE=gram -e TARGET=$(TARGETYACC) -e CUSTOM_FILES='*.y' -f $(MAKE_CONFIG_FILE)
	@echo Build Lexer makefile
	$(MAKE) -s -C $@/sqlitefk/src -e MODULE=lex -e TARGET=$(TARGETLEX) -e CUSTOM_FILES='*.l' -f $(MAKE_CONFIG_FILE)
	@echo Build Grammar file
	$(MAKE) -s -C $@/sqlitefk/src -f makefile.yacc
	@echo Build Lexer make
	$(MAKE) -s -C $@/sqlitefk/src -f makefile.lex
	@echo Build Main makefile
	$(MAKE) -s -C $@ -e MODULE=liblbdatabaselayer_sqllite -e TARGET=$(TARGETWXSHARED) -e CUSTOM_FILES='../../*.cpp sqlitefk/src/*.c' -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install
endif

ifeq ($(OSTYPE), Windows_NT)
../vendor/databaselayer/src/Implementations/Sqllite: ../../bin/bison.simple
	$(MAKE) -s -C $@/sqlitefk/src -e MODULE=gram -e TARGET=$(TARGETYACC) -e CUSTOM_FILES='*.y' -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@/sqlitefk/src -e MODULE=lex -e TARGET=$(TARGETLEX) -e CUSTOM_FILES='*.l' -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@/sqlitefk/src -f makefile.yacc
	$(MAKE) -s -C $@/sqlitefk/src -f makefile.lex
	$(MAKE) -s -C $@ -e MODULE=databaselayer_sqllite -e TARGET=$(TARGETWXSHARED) -e CUSTOM_FILES='../../*.cpp sqlitefk/src/*.c' -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

../vendor/databaselayer/tests: dummy
	$(MAKE) -s -C $@ -e MODULE=databaselayer_sqllite_tests -e TARGET=$(TARGETWXEXE) -e CUSTOM_FILES='*.cxx' -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/databaselayer/src/Implementations/Sqllite/sqlitefk/build/mkmk: dummy
	$(MAKE) -s -C $@ -e MODULE=sqllitefk -e TARGET=$(TARGETDLL) -e CUSTOM_FILES=../../src/*.c -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@


../vendor/databaselayer/test: dummy
	$(MAKE) -s -C $@ -e MODULE=databaselayer_test -e TARGET=$(TARGETWXEXE) -e CUSTOM_FILES=../../*.cpp -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/xsltc: dummy
	$(MAKE) -s -C $@ -e MODULE=xsltc -e TARGET=$(TARGETEXE) -e CUSTOM_FILES='src/*.cpp src/main/*.cpp src/compiler/*.cpp src/base/*.cpp src/xml/*.cpp src/net/*.cpp src/util/*.cpp src/xml/dom/standalone/*.cpp src/xpath/*.cpp src/xslt/*.cpp src/xslt/functions/*.cpp src/xslt/util/*.cpp src/xml/printer/*.cpp src/xml/util/*.cpp src/xml/parser/*.cpp src/xml/parser/expat/xmltok/*.c src/xml/parser/expat/xmlparse/*.c' -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/dbwrapcontrols: dummy
	$(MAKE) -s -C $@ -e MODULE=dbwrapcontrols -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/c-goldparser: dummy
	$(MAKE) -s -C $@ -e MODULE=gold -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

ifeq ($(OSTYPE), Windows_NT)
../vendor/libxml2-2.8.0:
	$(TAR) -zxf ../libxml2-2.8.0.tar.gz --directory ../vendor
endif

ifeq ($(OSTYPE), Windows_NT)
PATHSEP2=\\
PATHSEP=$(strip $(PATHSEP2))

../vendor/libxml2-2.8.0/win32/makefile.mingw: ../vendor/libxml2-2.8.0
	cd ..; \
	cd vendor; \
	cd libxml2-2.8.0; \
	cd win32; \
	cscript configure.js compiler=mingw prefix=$(DEVROOT_MAKE)$(RELPATH)/vendor/libxml2-2.8.0 include=$(DEVROOT_MAKE)$(RELPATH)/vendor/libxml2-2.8.0/include lib=$(DEVROOT_MAKE)$(RELPATH)/vendor/libxml2-2.8.0/lib debug=no include=$(DEVROOT_MAKE)$(RELPATH)/vendor/libiconv-1.9.1/include iconv=no

endif

../vendor/libxml2-2.8.0/win32/bin.mingw/libxml2.dll: dummy ../vendor/libxml2-2.8.0/win32/makefile.mingw
	$(MAKE) -s -C ../vendor/libxml2-2.8.0/win32 -f makefile.mingw dep libxml
	cp ../vendor/libxml2-2.8.0/win32/bin.mingw/libxml2.dll ../../dll
	cp ../vendor/libxml2-2.8.0/win32/bin.mingw/libxml2.lib ../../dll/libs

ifneq ($(OSTYPE), Windows_NT)
../vendor/sqlite: dummy
	$(MAKE) -s -C $@ -e MODULE=liblbsqlite3 -e TARGET=$(TARGETSHARED) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install

# My own antlr3 due to using my build system. (Should be thought of for my other vendor stuff)
../vendor/antlr3/src: dummy
	$(MAKE) -s -C $@ -e MODULE=liblbantlr3 -e TARGET=$(TARGETSHARED) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install
endif

ifeq ($(OSTYPE), Windows_NT)
../vendor/sqlite: dummy
	$(MAKE) -s -C $@ -e MODULE=sqlite3 -e TARGET=$(TARGETSHARED) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

# My own antlr3 due to using my build system.
../vendor/antlr3/src: dummy
	$(MAKE) -s -C $@ -e MODULE=liblbantlr3 -e TARGET=$(TARGETSHARED) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

ifeq ($(OSTYPE), Windows_NT)
../vendor/libxslt-1.1.21:
	$(TAR) -zxf libxslt-1.1.21.tar.gz --directory ../vendor
	cp ../vendor/makefile.module.libxslt ../vendor/libxslt-1.1.21/libxslt/makefile.module
	cp ../vendor/libxslt-1.1.21/libxslt/win32config.h ../vendor/libxslt-1.1.21/config.h
endif


../vendor/libxslt-1.1.21/libxslt: ../vendor/libxslt-1.1.21
	$(MAKE) -s -C $@ -e MODULE=lbxslt -e TARGET=$(TARGETXSLTDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/tvision: dummy
	-$(MAKE) -s -C $@ -e MODULE=librhtv -e TARGET=$(TARGET_TV_DLL) -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@

../vendor/tvision-set: dummy
	$(MAKE) -s -C $@ -e MODULE=librhtv -e TARGET=$(TARGET_TV_DLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/tvision/examples/lbDMF: dummy
	-$(MAKE) -s -C $@ -e MODULE=demo -e TARGET=$(TARGET_TV_EXE) -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@

../vendor/tvision/examples/listvi: dummy
	$(MAKE) -s -C $@ -e MODULE=tvlistvi -e TARGET=$(TARGET_TV_EXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/tvision/examples/tcombo: dummy
	$(MAKE) -s -C $@ -e MODULE=tvcombo -e TARGET=$(TARGET_TV_EXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/tvision/examples/dlgdsn: dummy
	$(MAKE) -s -C $@ -e MODULE=dlgdsn -e TARGET=$(TARGET_TV_EXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxReportWriter: dummy
	$(MAKE) -s -C $@

../Test/Console/XML: dummy
	$(MAKE) -s -C $@ -e MODULE=console-test -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../Test/GUI/wxPlugins/lbCryptoStream: dummy
	$(MAKE) -s -C $@ -e MODULE=lbCryptoStream -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

ifeq ($(OSTYPE), Windows_NT)
../AppDevelopmentDemo/MkBs: dummy
	$(MAKE) -s -C $@ -e MODULE=MkBs -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

ifneq ($(OSTYPE), Windows_NT)
../AppDevelopmentDemo/MkBs: dummy
	$(MAKE) -s -C $@ -e MODULE=MkBs -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install
endif

ifeq ($(OSTYPE), solaris)
../vendor/dosdir: dummy
	$@/make.sh $@
	cd ../BaseDevelopment

../vendor/mkmk: dummy
	$@/make.sh $@
	cp $@/mkmk $(prefix)/bin
	cd ../BaseDevelopment
endif

ifeq ($(OSTYPE), linux-debian-ppc)
../vendor/dosdir: dummy
	$@/make.sh $@
	cd ../BaseDevelopment

../vendor/mkmk: dummy
	$@/make.sh $@
	cp $@/mkmk $(prefix)/bin
	cd ../BaseDevelopment
endif

ifeq ($(OSTYPE), linux)
../vendor/dosdir: dummy
	$@/make.sh $@
	cd ../BaseDevelopment

../vendor/mkmk: dummy
	$@/make.sh $@
	cp $@/mkmk $(prefix)/bin
	cd ../BaseDevelopment
endif

ifeq ($(OSTYPE), osx)
../vendor/dosdir: dummy
	$@/make-osx.sh $@
	cd ../BaseDevelopment

../vendor/mkmk: dummy
	$@/make-osx.sh $@
	cp $@/mkmk $(prefix)/bin
	cd ../BaseDevelopment

../vendor/propgrid: dummy
	$(MAKE) -s -C $@ -e MODULE=wxPropgrid -e TARGET=$(TARGETWXFRAMEWORK) -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@

../Test/GUI/wxPlugins/lbLoginWizard: dummy
	$(MAKE) -s -C $@ -e MODULE=lbLoginWizard -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/cryptostream/src/crypstrm: dummy
	$(MAKE) -s -C $@ -e MODULE=wxCryptoStream -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxaui-0.9.1/src: dummy
ifeq ($(OSNAME), Panther)
	$(MAKE) -s -C $@ -e MODULE=wxAUI -e TARGET=$(TARGETWXFRAMEWORK) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

../vendor/wxShapeFramework/samples/wxSFDemo: dummy
	-$(MAKE) -s -C $@ -e MODULE=wxSFDemo -e TARGET=$(TARGETWXEXE) -e CUSTOM_FILES=wxxmlserializer/*.cpp -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@

../vendor/wxaui-0.9.1/sample: dummy
ifeq ($(OSNAME), Panther)
	$(MAKE) -s -C $@ -e MODULE=wxAUISample -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

../Test/GUI/wxWrapper: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapper -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@ -e prefix=$(prefix)
	cp ../Test/GUI/wxWrapper/wxWrapper $(prefix)/bin

../vendor/wxARG/src: dummy
	$(MAKE) -s -C $@ -e MODULE=wxActiveRecordGenerator -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	cp ../vendor/wxARG/src/wxActiveRecordGenerator $(prefix)/bin

../vendor/wxShapeFramework/src: dummy
	-$(MAKE) -s -C $@ -e MODULE=wxShapeFramework -e TARGET=$(TARGETWXFRAMEWORK) -e CUSTOM_FILES=wxxmlserializer/*.cpp -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@

../vendor/wxShapeFramework/example: dummy
	-$(MAKE) -s -C $@ -e MODULE=wxShapeFrameworkExample -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@

../vendor/wxJSON-1.2.1/src: dummy
	-$(MAKE) -s -C $@ -e MODULE=wxJson -e TARGET=$(TARGETWXFRAMEWORK) -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@
	-$(MAKE) -s -C $@ install

../Test/GUI/wxWrapperDLL: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapperDLL -e TARGET=$(TARGETWXFRAMEWORK) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	
../vendor/goldparserengine/src: dummy
	$(MAKE) -s -C $@ -e MODULE=wxGoldParser -e TARGET=$(TARGETWXFRAMEWORK) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/goldparserengine/samples/engine: dummy
	$(MAKE) -s -C $@ -e MODULE=wxGoldParserEngineTest -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@ -e prefix=$(prefix)
	cp ../vendor/goldparserengine/samples/engine/wxGoldParserEngineTest $(prefix)/bin

../vendor/goldparserengine/samples/gptest: dummy
	$(MAKE) -s -C $@ -e MODULE=wxGoldParserGPTest -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@ -e prefix=$(prefix)
	cp ../vendor/goldparserengine/samples/engine/wxGoldParserGPTest $(prefix)/bin


endif

ifeq ($(OSTYPE), solaris)
../vendor/wxaui-0.9.1/src: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxAUI -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../vendor/propgrid: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxPropgrid -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../vendor/wxaui-0.9.1/sample: dummy
	$(MAKE) -s -C $@ -e MODULE=wxAUISample -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxJSON-1.2.1/src: dummy
	-$(MAKE) -s -C $@ -e MODULE=libwxJson -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@
	-$(MAKE) -s -C $@ install

../Test/GUI/wxWrapperDLL: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxWrapperDLL -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../Test/GUI/wxWrapper: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapper -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	cp ../Test/GUI/wxWrapper/wxWrapper $(prefix)/bin

#../Test/GUI/wxWrapper: dummy
#	$(MAKE) -s -C $@ -f makefile.wx-sample

../Test/GUI/wxPlugins/lbLoginWizard: dummy
	$(MAKE) -s -C $@ -e MODULE=lbLoginWizard -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

ifeq ($(OSTYPE), linux)
../vendor/wxaui-0.9.1/src: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxAUI -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../vendor/propgrid: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxPropgrid -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../vendor/mpatrol/src: dummy
	$(MAKE) -s -C $@ -e MODULE=libmpatrol -e TARGET=$(TARGETSHARED) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../vendor/wxShapeFramework/src: dummy
	-$(MAKE) -s -C $@ -e MODULE=wxShapeFramework -e TARGET=$(TARGETWXSO) -e CUSTOM_FILES=wxxmlserializer/*.cpp -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@

../vendor/wxShapeFramework/example: dummy
	-$(MAKE) -s -C $@ -e MODULE=wxShapeFrameworkExample -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@

../vendor/wxaui-0.9.1/sample: dummy
	$(MAKE) -s -C $@ -e MODULE=wxAUISample -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxJSON-1.2.1/src: dummy
	-$(MAKE) -s -C $@ -e MODULE=libwxJson -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@
	-$(MAKE) -s -C $@ install

../Test/GUI/wxWrapperDLL: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxWrapperDLL -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../Test/GUI/wxWrapper: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapper -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	cp ../Test/GUI/wxWrapper/wxWrapper $(prefix)/bin

#../Test/GUI/wxWrapper: dummy
#	$(MAKE) -s -C $@ -f makefile.wx-sample

../Test/GUI/wxPlugins/lbLoginWizard: dummy
	$(MAKE) -s -C $@ -e MODULE=lbLoginWizard -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

ifeq ($(OSTYPE), linux-debian-ppc)
../vendor/wxaui-0.9.1/src: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxAUI -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../vendor/propgrid: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxPropgrid -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../vendor/mpatrol/src: dummy
	$(MAKE) -s -C $@ -e MODULE=libmpatrol -e TARGET=$(TARGETSHARED) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../vendor/wxaui-0.9.1/sample: dummy
	$(MAKE) -s -C $@ -e MODULE=wxAUISample -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxJSON-1.2.1/src: dummy
	-$(MAKE) -s -C $@ -e MODULE=libwxJson -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@
	-$(MAKE) -s -C $@ install

../Test/GUI/wxWrapperDLL: dummy
	$(MAKE) -s -C $@ -e MODULE=libwxWrapperDLL -e TARGET=$(TARGETWXSO) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	$(MAKE) -s -C $@ install-strip

../Test/GUI/wxWrapper: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapper -e TARGET=$(TARGETWXEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	cp ../Test/GUI/wxWrapper/wxWrapper $(prefix)/bin

#../Test/GUI/wxWrapper: dummy
#	$(MAKE) -s -C $@ -f makefile.wx-sample

../Test/GUI/wxPlugins/lbLoginWizard: dummy
	$(MAKE) -s -C $@ -e MODULE=lbLoginWizard -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
endif

ifeq ($(OSTYPE), Windows_NT)
../Test/GUI/wxWrapper: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapper -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

$(DEVROOT_MAKE)/wxwin/wx/samples/report: dummy
	$(MAKE) -s -C $@ -e MODULE=report -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/propgrid: dummy
	$(MAKE) -s -C $@ -e MODULE=wxPropgrid -e TARGET=$(TARGETSHARED) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxaui-0.9.1/src: dummy
	$(MAKE) -s -C $@ -e MODULE=wxAUI -e TARGET=$(TARGETSHARED) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxaui-0.9.1/sample: dummy
	$(MAKE) -s -C $@ -e MODULE=wxAUISample -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxJSON-1.2.1/src: dummy
	-$(MAKE) -s -C $@ -e MODULE=wxJson -e TARGET=$(TARGETWXSHARED) -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@

../Test/GUI/wxWrapperDLL: dummy
	$(MAKE) -s -C $@ -e MODULE=wxWrapperDLL -e TARGET=$(TARGETSHARED) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../Test/GUI/wxPlugins/lbLoginWizard: dummy
	$(MAKE) -s -C $@ -e MODULE=lbLoginWizard -e TARGET=$(TARGETWXPLUGIN) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../vendor/wxShapeFramework/src: dummy
	-$(MAKE) -s -C $@ -e MODULE=wxShapeFramework -e TARGET=$(TARGETWXSHARED) -e CUSTOM_FILES=wxxmlserializer/*.cpp -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@

../vendor/wxShapeFramework/samples/wxSFDemo: dummy
	-$(MAKE) -s -C $@ -e MODULE=wxSFDemo -e TARGET=$(TARGETWXEXE) -e CUSTOM_FILES=wxxmlserializer/*.cpp -f $(MAKE_CONFIG_FILE)
	-$(MAKE) -s -C $@

endif

../../open-watcom: dummy
	$(MAKE) -C $@

../AppDevelopment: dummy
	-$(MAKE) -k -s -C $@

../Plugins: dummy
	$(MAKE) -s -C $@

../ServerPlugins: dummy
	-$(MAKE) -s -C $@

../ClientPlugins: dummy
	-$(MAKE) -s -C $@

../UnitTests: dummy
	-$(MAKE) -s -C $@

../AppDevelopmentDemo/DynamicApp/Plugins: dummy
	$(MAKE) -s -C $@

../Modules: dummy
	$(MAKE) -s -C $@

../AppDevelopmentDemo: dummy
	$(MAKE) -s -C $@

../RegressionTests: dummy
	$(MAKE) -s -C $@ -e CRUISECONTROL=$(CRUISECONTROL)

../AppDevelopmentDemo/App: dummy
	$(MAKE) -s -C $@ -e MODULE=Application -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

../AppDevelopmentDemo/DynamicApp/App: dummy
	$(MAKE) -s -C $@ -e MODULE=lbDynApp -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbWorkflowEngine: dummy
	$(MAKE) -s -C $@ -e MODULE=lbWorkflowEngine -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
	
#../Plugins/DatabaseForm: dummy
#	$(MAKE) -s -C $@ -e MODULE=lbDatabaseForm -e TARGET=$(TARGETWXPLUGIN) -f $(DEVROOT_MAKE)$(RELPATH)/make/makefile.configure
#	$(MAKE) -s -C $@

lbHook: dummy
	@echo prefix='$(prefix)' OSNAME=$(OSNAME)
ifeq ($(OSTYPE), linux)
	$(MAKE) -s -C $@ -e MODULE=lib$@ -e TARGET=$(TARGETFRAMEWORK) -f $(MAKE_CONFIG_FILE)
else
ifeq ($(OSTYPE), solaris)
	$(MAKE) -s -C $@ -e MODULE=lib$@ -e TARGET=$(TARGETFRAMEWORK) -f $(MAKE_CONFIG_FILE)
else
ifeq ($(OSTYPE), linux-debian-ppc)
	$(MAKE) -s -C $@ -e MODULE=lib$@ -e TARGET=$(TARGETFRAMEWORK) -f $(MAKE_CONFIG_FILE)
else
ifeq ($(OSTYPE), Windows_NT)
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETFRAMEWORK) -f $(MAKE_CONFIG_FILE)
else
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETFRAMEWORK) -f $(MAKE_CONFIG_FILE)
endif
endif
endif
endif
	echo $(MAKE) -s -C $@
	$(MAKE) -s -C $@
ifeq ($(OSTYPE), solaris)
	$(MAKE) -s -C $@ install-strip
endif
ifeq ($(OSTYPE), linux)
	$(MAKE) -s -C $@ install-strip
endif

lbDB: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbPluginManager: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbModule: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbclasses: dummy
	$(MAKE) -s -C lbclasses -e MODULE=lbClasses -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C lbclasses

lbMetaApplication: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbtransfer: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbcs: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

lbXMLConfig/lbDOMConfig: dummy
	$(MAKE) -s -C $@ -e MODULE=$@ -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@

#Q:/develop/wxwin/wx/contrib/wxCode/components/wxxml2/thirdparty/libxml2: dummy
#	$(MAKE) -s -C $@ -e MODULE=libxml2 -e TARGET=$(TARGETDLL) -f $(MAKE_CONFIG_FILE)
#	$(MAKE) -s -C $@

../Doc/html: ../doxygen.conf \
	../interfaces/lbInterfaces.h \
	../include/lbConfigHook.h \
	../Samples/HelloWorld/helloworld.cpp \
	../RegressionTests/Basetypes/Basetypes.cpp \
	../RegressionTests/Memory/memTest.cpp
	-@doxygen ../doxygen.conf



#	../RegressionTests/Database/dbTest.cpp \

../Samples/HelloWorld: dummy
	$(MAKE) -s -C $@ -e MODULE=HelloWorld -e TARGET=$(TARGETEXE) -f $(MAKE_CONFIG_FILE)
	$(MAKE) -s -C $@
