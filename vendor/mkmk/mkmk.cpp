/*...scopyright:0:*/
/*
 MKMK: Makefile maker.
 By Luis Crespo, lcrespo@ergos.es
 Please read MKMK.TXT for a program description.

 Define "WATCOM_MAKE" for Watcom C/C++ oriented makefiles.
 Define "UNIX" for unix orieted makefiles
 Define "OSX" for Mac OS X oriented makefiles
*/
/*...e*/
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.114.2.5 $
 * $Name:  $
 * $Id: mkmk.cpp,v 1.114.2.5 2014/10/11 10:29:39 lollisoft Exp $
 *
 * $Log: mkmk.cpp,v $
 * Revision 1.114.2.5  2014/10/11 10:29:39  lollisoft
 * Some remaining -WL in unix targets.
 *
 * Revision 1.114.2.4  2014/10/11 06:46:46  lollisoft
 * Fixed issues with soname parameter.
 *
 * Revision 1.114.2.3  2013/10/26 04:39:12  lollisoft
 * Fixes on Linux related to socket and transfer classes.
 *
 * Revision 1.114.2.2  2012/10/03 21:03:30  lollisoft
 * Recursive include bugfix.
 *
 * Revision 1.114.2.1  2012/06/16 10:19:43  lollisoft
 * Added commands to reference libraries within the application bundle.
 *
 * Revision 1.114  2011/06/18 17:29:55  lollisoft
 * Changed all char* to const char* where a corresponding warning was generated.
 *
 * Revision 1.113  2011/02/20 09:31:09  lollisoft
 * Added cleaning up *.o files.
 *
 * Revision 1.112  2010/08/29 21:09:30  lollisoft
 * Changes to get more modules compiled with MinGW.
 * Also changed my adress in some files as I have a new
 * home. Others will follow.
 *
 * Revision 1.111  2010/06/03 16:58:07  lollisoft
 * Most requriered modules are now compilable with MinGW and the main application runs.
 * There are some problems with unit tests but they pass. Also the code generator seems to
 * not work properly.
 *
 * Revision 1.110  2010/06/02 07:05:19  lollisoft
 * Changes to get more targets compiled with MinGW.
 *
 * Revision 1.109  2010/04/03 00:13:17  lollisoft
 * Added more MinGW support. The UnitTests now are working properly.
 *
 * Revision 1.108  2010/03/20 22:58:07  lollisoft
 * Added support for mingw mixed mode (with Open Watcom).
 * This is tested with the Basetypes sample application that uses
 * lbHook.dll (mingw), lbModule.dll (OW) and lbclasses.dll (OW).
 *
 * Revision 1.107  2009/11/22 16:38:36  lollisoft
 * Compile Mac OS X on Snow Leopard only for i386. Add ppc on demand to the OSX_ARCH flag in make/STD_MAKE. Probgrid seems to not correctly initialize a variable that causes a division with zero (hack).
 *
 * Revision 1.106  2009/11/20 11:18:11  lollisoft
 * Corrected bin directory to put executables into.
 *
 * Revision 1.105  2009/11/08 11:49:32  lollisoft
 * Implemented 'unit test' like capabilities. The TestPlugin in the Plugins directory demonstrates the usage. Yet missing is a real test listener and stuff to display results. But it shows a working unit test mechanism using plugins.
 *
 * Corrected mkmk to find also include files in <> brackets.
 *
 * Corrected make system to work correctly with the new mkmk version. There may be a performance problem when compiling tvision code, thus that target is deactivated.
 *
 * Fixed some warnings.
 *
 * Revision 1.104  2009/10/24 21:01:35  lollisoft
 * Added new partial stuff to handle idl files.
 *
 * Revision 1.103  2009/05/29 13:42:52  lollisoft
 * Deactivated calling Rez.
 *
 * Revision 1.102  2009/05/28 16:12:27  lollisoft
 * Added option to enable libraries located in bundle.
 *
 * Revision 1.101  2009/03/12 18:54:08  lollisoft
 * Added a failsave postlink step to enable copying of some files into the Mac type application bundle.
 *
 * Revision 1.100  2009/01/14 15:01:02  lollisoft
 * Fixed build system for solaris. Now basically the application works with sqlite.
 *
 * Revision 1.99  2008/09/06 15:54:55  lollisoft
 * Changed copying sym files for dll and plugins into the same directory as the plugins and dlls are copied.
 *
 * Open Watcom seems to have changed some search algorythms for the sym files.
 *
 * Revision 1.98  2008/08/29 16:52:38  lollisoft
 * Bugfix for crashes when the execution path was long. (Buffer overflow)
 *
 * Revision 1.97  2008/08/12 08:38:59  lollisoft
 * Bugfix for an array overflow. To be fixed in a better way later.
 *
 * Revision 1.96  2008/07/24 20:53:36  lollisoft
 * These changes let the application run on Mac OS X 10.5 (Leopard). But crashes at exit, propably due to changed cleanup logic or changed default variable values (not correctly initialized).
 *
 * Revision 1.95  2008/06/07 10:11:34  lollisoft
 * Beautified some code.
 *
 * Revision 1.94  2008/06/07 07:45:24  lollisoft
 * Moving Open Watcom crosscompiling attempts to my other Linux box.
 *
 * Revision 1.93  2008/06/05 19:36:32  lollisoft
 * Added crosscompiling stuff. Really beta !
 *
 * Revision 1.92  2008/05/31 12:19:23  lollisoft
 * Removed dependency to non existing makefile. (LEX and YACC targets)
 *
 * Revision 1.91  2008/05/03 07:00:37  lollisoft
 * Changed path to frameworks.
 *
 * Revision 1.90  2008/01/18 21:44:30  lollisoft
 * Added lex and yacc target.
 *
 * Revision 1.89  2007/11/17 09:44:31  lollisoft
 * Bugfix for false #include statements (codegenertaion string literals may heve them).
 *
 * Revision 1.88  2007/11/14 20:45:57  lollisoft
 * Some changes for mkmk to compile c files in subdirectories well under Windows.
 * Added xsltc target and some other changes.
 *
 * Revision 1.87  2007/11/14 17:16:37  lollisoft
 * Try to correctly write c compile rule with path's in it.
 *
 * Revision 1.86  2007/10/28 16:56:45  lollisoft
 * Corrected object file name determination problem when having path in the name.
 *
 * Revision 1.85  2007/07/05 16:40:32  lollisoft
 * Corrected Mac icon copy rule.
 *
 * Revision 1.84  2006/12/10 17:05:24  lollisoft
 * Other changes under Mac OS X.
 *
 * Revision 1.83  2006/07/17 17:58:42  lollisoft
 * Faster cleanup.
 *
 * Revision 1.82  2006/06/24 06:19:54  lollisoft
 * Commit due to travel to Duesseldorf.
 *
 * Revision 1.81  2006/04/20 13:13:40  lollisoft
 * Copy application bundle instead of plain application.
 *
 * Revision 1.80  2006/04/20 12:46:00  lollisoft
 * Copy application bundle instead of plain application.
 *
 * Revision 1.79  2006/04/16 10:03:06  lollisoft
 * Added copying wxPropgrid framework. (Todo: Move that to a post make copy list rule)
 *
 * Revision 1.78  2006/03/04 22:18:18  lollisoft
 * Corrected library dependencies and build names
 *
 * Revision 1.77  2006/03/03 16:16:41  lollisoft
 * Changes in shared library naming and linking against.
 *
 * Revision 1.76  2006/03/02 16:39:29  lollisoft
 * Use prefix for libraries.
 *
 * Revision 1.75  2006/03/02 12:37:12  lollisoft
 * Modified or added make install (strip) process
 *
 * Revision 1.74  2006/02/26 23:46:19  lollisoft
 * Changed build method for shared libraries under Mac OS X
 * to be frameworks. These would be embedable into the
 * application bundle - thus enables better install method.
 *
 * Revision 1.73  2006/02/24 14:27:32  lollisoft
 * Fix absolute path for symbolic links of shared libraries.
 * Linux not yet tested.
 *
 * Revision 1.72  2006/01/29 09:45:39  lollisoft
 * Added new target.
 *
 * Revision 1.71  2006/01/20 01:00:39  lollisoft
 * Bugfix in absolutely depend on wxMac version 2.6.1.
 *
 * Revision 1.70  2005/11/26 18:59:11  lollisoft
 * Minor changes to compile and run under Linux
 *
 * Revision 1.69  2005/11/06 19:25:34  lollisoft
 * All bugs of unloading shared libraries removed.\nUsing dlopen more than once per shared library leads into unability to unload that library.\nMac OS X seems to not properly handle the reference counting, thus unloading of twice loaded shared libs fails.\n\nI have implemented a workaround to handle this properly.\n\nThere is one exeption: lbModule.so is needed by UAP macros, thus this shared library is left loaded and the system can unload it for me.
 *
 * Revision 1.68  2005/09/09 18:00:16  lollisoft
 * Added printout of given commandline in help mode.
 * Added -o option in bundle target to put object file
 * in same directory as the source file is.
 *
 * Revision 1.67  2005/08/22 16:31:33  lollisoft
 * Write L_OPS in wxWidgets so target for OSX.
 *
 * Revision 1.66  2005/08/04 18:06:45  lollisoft
 * Added creating bundle target on Mac OS X.
 *
 * Revision 1.65  2005/06/24 23:10:02  lollisoft
 * Changes to build with new wxWidgets version 2.6.1.
 * Added fallback to hardcoded settings, if no environment
 * variables are found. Logging changed to reside in a
 * $(HOME)/log directory.
 *
 * GUI application build process enhanced to also make the
 * bundle. App runs from clicking on the desktop icon.
 *
 * Revision 1.64  2005/05/16 00:00:46  lollisoft
 * Added lines to report building a source file.
 *
 * Revision 1.63  2005/05/13 10:58:56  lollisoft
 * Better creation proccess for watcom link information file.
 * It was a bug in the old one, if there were a partly build, so that
 * the link info file would be incorrect or at least incomplete.
 *
 * Revision 1.62  2005/05/10 21:09:43  lollisoft
 * Removed unneeded mkmk message
 *
 * Revision 1.61  2005/05/09 21:14:24  lollisoft
 * Adaptions to compile C code with C compiler. Not with CPP compiler.
 * This let's the tvision library built correctly and also some pieces of OW it self.
 *
 * Revision 1.60  2005/05/07 08:49:14  lollisoft
 * Better handling of much object files (for DLL's now)
 *
 * Revision 1.59  2005/04/28 09:46:37  lollisoft
 * Some changes under Linux to built correctly
 *
 * Revision 1.58  2005/04/27 12:58:02  lollisoft
 * Linking with L_OPS options instead of LIBS
 *
 * Revision 1.57  2005/04/26 20:51:14  lollisoft
 * Changes for OSX
 *
 * Revision 1.56  2005/04/26 17:18:04  lollisoft
 * Much changes to include correct libraries, preparements for memory debugging, tests changed and more
 *
 * Revision 1.55  2005/04/23 10:49:56  lollisoft
 * Try to include tvision built. Added copying sym file to a place where wdw find it.
 *
 * Revision 1.54  2005/04/17 14:04:29  lollisoft
 * Changed target path for linux
 *
 * Revision 1.53  2005/03/16 01:56:25  lollisoft
 * Added wxplugin make rules. Suddenly reformatted the code.
 *
 * Revision 1.52  2005/03/16 00:27:53  lollisoft
 * Last changes to full automatic compiling under OSX.
 *
 * Revision 1.51  2005/03/15 22:17:52  lollisoft
 * mkmk and make process under linux improoved
 *
 * Revision 1.50  2005/03/15 14:43:53  lollisoft
 * Changes for linux to build and let GUI running with plugins
 *
 * Revision 1.49  2005/03/05 23:13:34  lollisoft
 * More changes to build source tree under Mac OS X
 *
 * Revision 1.48  2005/02/10 17:04:16  lollisoft
 * Changes for Mac OS X
 *
 * Revision 1.47  2005/01/27 13:01:07  lollisoft
 * Added POST_PROCESS functionality
 *
 * Revision 1.46  2005/01/23 11:35:00  lollisoft
 * Now the code compiles under SuSE Linux 9.1 except wx. It has link problems
 *
 * Revision 1.45  2005/01/22 11:37:43  lollisoft
 * Changed the about text
 *
 * Revision 1.44  2005/01/22 05:55:31  lollisoft
 * Minor code changes
 *
 * Revision 1.43  2004/11/02 19:02:06  lollisoft
 * Replated del with rm
 *
 * Revision 1.42  2004/10/16 12:01:05  lollisoft
 * Adopted new make system to linux
 *
 * Revision 1.41  2004/10/16 09:47:38  lollisoft
 * New make system works nearly perfect. It does not longer build unnessesary.
 *
 * Revision 1.40  2004/10/09 18:00:24  lollisoft
 * Added distclean feature
 *
 * Revision 1.39  2004/10/09 16:16:44  lollisoft
 * Added clean feature for linux
 *
 * Revision 1.38  2004/06/07 20:09:17  lollisoft
 * Added support for plugins
 *
 * Revision 1.37  2003/09/10 19:39:03  lollisoft
 * Watcom lnk file cration problem solved
 *
 * Revision 1.36  2003/09/05 15:46:22  lollisoft
 * Last changes to try to make setup distribution and before moving to Düsseldorf
 *
 * Revision 1.35  2003/07/15 22:00:44  lollisoft
 * Use libr define for system libraries
 *
 * Revision 1.34  2003/05/29 08:41:19  lollisoft
 * Corrected makefile generation for watcom
 *
 * Revision 1.33  2003/04/28 20:42:15  lollisoft
 * Moved back to watcom
 *
 * Revision 1.32  2003/03/15 01:01:57  lollisoft
 * Removed the problem with _chkesp() failure. But still crash in my GUI app
 *
 * Revision 1.31  2003/02/17 21:34:44  lollisoft
 * Much problems with compilation solved, bu wy came this ??
 *
 * Revision 1.30  2003/01/15 22:44:30  lothar
 * Added handling of MSC compiler
 *
 * Revision 1.29  2002/12/29 16:09:30  lothar
 * Intent to go public
 *
 * Revision 1.28  2002/11/29 19:50:27  lothar
 * Compiles again under linux, but some problems at runtime with DOMString
 *
 * Revision 1.27  2002/11/23 09:47:19  lothar
 * Added copy so file to libdev/lib
 *
 * Revision 1.26  2002/05/29 19:09:06  lothar
 * Changes due to hiding much informal compile messages
 *
 * Revision 1.25  2002/04/15 18:25:16  lothar
 * Huge changes - works good
 *
 * Revision 1.24  2001/12/16 17:41:43  lothar
 * Added VENDORLIBS
 *
 * Revision 1.23  2001/12/15 18:15:48  lothar
 * More support for different compilers im one makefile.
 * Separated compiler and linker options for different
 * targets.
 *
 * Revision 1.22  2001/12/12 17:20:20  lothar
 * Works on elf now
 *
 * Revision 1.21  2001/11/21 22:30:01  lothar
 * Much changes to make lib makefiles working
 *
 * Revision 1.20  2001/11/20 20:05:15  lothar
 * Changed linking object files
 *
 * Revision 1.19  2001/11/10 07:22:32  lothar
 * Building so targets works now
 *
 * Revision 1.18  2001/11/09 19:28:49  lothar
 * Added first attempt of building so targets
 *
 * Revision 1.17  2001/11/08 20:47:13  lothar
 * Added writing dll targets (tested on lbmodule)
 *
 * Revision 1.16  2001/11/06 21:38:30  lothar
 * Added writeExeTarget function to be able building my self under windows
 *
 * Revision 1.15  2001/11/04 19:28:47  lothar
 * Uninitalized variable bug solved
 *
 * Revision 1.14  2001/11/04 19:07:49  lothar
 * Produces it's own makefile that work's (using templates)
 *
 * Revision 1.13  2001/10/23 20:23:16  lothar
 * What is that ???
 *
 * Revision 1.12  2001/10/23 20:17:56  lothar
 * Changed hardcoded path seperator
 *
 * Revision 1.11  2001/10/22 21:28:51  lothar
 * It may work now with include directory paths, but not in the
 * case if there are #ifdefs ...
 *
 * Revision 1.10  2001/10/21 13:08:45  lothar
 * Added includepath parameter
 *
 * Revision 1.9  2001/10/21 12:32:06  lothar
 * Little changes
 *
 * Revision 1.8  2001/10/20 20:20:12  lothar
 * Changed file output to stdout
 *
 * Revision 1.7  2001/10/20 19:52:53  lothar
 * Moved some messages to VERBOSE only
 *
 * Revision 1.6  2001/10/20 19:48:45  lothar
 * Moved some messages to VERBOSE only
 *
 * Revision 1.5  2001/10/20 19:45:43  lothar
 * Added revision history
 *
 **************************************************************/

/*...e*/
/*...sincludes:0:*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "DEFS.H"
#include "contain.h"

#ifdef __WATCOMC__
#include <malloc.h>
#endif
/*...e*/
/*...sdefs:0:*/
#ifdef __WATCOMC__

  #include <dos.h>
  #define dd_findfirst(x,y,z) _dos_findfirst(x,z,y)
  #define dd_findnext _dos_findnext
  #define dd_ffblk find_t
  #define dd_name name

#else

  #include <limits.h>

  #include <dosdir.h>
#endif
/*...e*/
/*...sdefs:0:*/
//#define WATCOM_MAKE

#ifdef LINUX
#define UNIX
#undef WATCOM_MAKE
#endif

#ifdef OSX
#define UNIX
#undef WATCOM_MAKE
#endif

/*...e*/
/*...sdefs:0:*/
#ifdef UNIX
  #define PathChar '/'
#else
  #define PathChar '/'
#endif

#ifdef UNIX
  #define ffblk dd_ffblk;

#endif

#ifdef WATCOM_MAKE
  #define MoreChar '&'
#else
  #define MoreChar '\\'
#endif
/*...e*/
/*...starget defs:0:*/
#define EXE_TARGET 1
#define DLL_TARGET 2
#define LIB_TARGET 3

#define ELF_TARGET 4
#define WXELF_TARGET 5

#define SO_TARGET  6
#define WXSO_TARGET  7

#define PLUGIN_TARGET 8
#define WXPLUGIN_TARGET 9

#define SOPLUGIN_TARGET 10
#define WXSOPLUGIN_TARGET 11
#define TVISION_DLL 12
#define TVISION_EXE 13
#define ELF_BUNDLE_TARGET 15
#define SO_BUNDLE_TARGET 16
#define WXSHARED_TARGET  17
#define FRAMEWORK_TARGET  18
#define WXFRAMEWORK_TARGET  19

// Separate mkmk invoke to build the pice of make rule for generating the sources.
// Generating an extra makefile for this would be callable before the real makefile would be build.
#define LEX_TARGET 20
#define YACC_TARGET 21

#define IDL_TARGET 22

// These are the new cross compiling targets
// This is absolutely beta !

#define EXE_TARGET_CROSS 200
#define DLL_TARGET_CROSS 201
#define LIB_TARGET_CROSS 202


// Using mingw as a compiler
#define EXE_TARGET_MINGW      400
#define DLL_TARGET_MINGW      401
#define LIB_TARGET_MINGW      402
#define PLUGIN_TARGET_MINGW   403
#define WXPLUGIN_TARGET_MINGW 404

/*...e*/

int targettype=EXE_TARGET;

char** IncPathList;

char* targetname = NULL;

/*...sint split\40\const char split_char\44\ char \42\string\44\ char \42\\42\\42\array\41\:0:*/
int split(const char split_char, char *string, char ***array)
{
        char *block;            /* current item block */
        int index;              /* position in array */
        int count;              /* number of items in array */
        char split_string[2];   /* string to hold split character */

        /* generate string for strtok() from split_char */
        sprintf(split_string, "%c", split_char);

        /* count number of blocks; if only one, return it as sole item */
        count = 0;
        block = strchr(string, split_char);
        if ( block == NULL) count = 1;
        while ( block != NULL )
        {
                block = strchr(block + 1, split_char);
                count++;
        }

        /* allocate enough memory to hold pointers to copies of all items */

        *array = (char**) malloc(sizeof(char *) * count);

        if ( *array == NULL )
        {
                /* can't allocate memory, so fail */
                return 0;
        }

        /* find each item, copy, and insert pointer to item in array */
        index = 0;
        for ( block = strtok(string, split_string); block != NULL;
              block = strtok(NULL, split_string) )
              {
                (*array)[index] = strdup(block);
                index++;
              }

        /* returnt the number of items in the array */
        return index;
}
/*...e*/

/*...shelpers:0:*/
/*...sclass TDepList:0:*/
//------------------------- Dependency list -------------------------

struct TDepItem {
  char Name[PATH_MAX];
  char Path[PATH_MAX];
};

class TDepList:public TDynArray {
  public:
    TDepList():TDynArray(20,10,sizeof(TDepItem)){}
    bool Search(char *s);
    void Insert(char *n, char *p);
    void AddMask(char *Mask);
};
/*...e*/
/*...svoid GetPath\40\char \42\s\44\ char \42\p\44\ int Len\41\:0:*/
void GetPath(char *s, char *p, int Len)
{
  int l;

  memset(p,0,Len);
  l=strlen(s)-1;
  if (l<1) return;
  while (l>=0 && s[l]!=PathChar) l--;
  if (l>=0 && l<Len) memcpy(p,s,l+1);
}
/*...e*/
/*...svoid FSplit\40\char \42\s\44\ char \42\p\44\ char \42\n\41\:0:*/
void FSplit(char *s, char *p, char *n)
{
  int l;

  l=strlen(s)-1;
  if (l<1) return;
  while (l>=0 && s[l]!=PathChar) l--;
#ifdef WINDOWS
//  while (l>=0 && s[l]!='\\') l--;
#endif
  memcpy(p,s,l+1); p[l+1]=0;
  strcpy(n,&s[l+1]);
}
/*...e*/


/*...sbool TDepList\58\\58\Search\40\char \42\s\41\:0:*/
bool TDepList::Search(char *s)
{
  int i;
  bool Found;
  TDepItem *d;

  i=0;
  Found=false;
  while (i<Count && !Found)
  {
    d=(TDepItem*)(*this)[i];
    //Found = strcmpi(d->Name,s)==0;
    Found = strcmp(d->Name,s)==0;
    i++;
  }
  return Found;
}
/*...e*/
/*...svoid TDepList\58\\58\Insert\40\char \42\n\44\ char \42\p\41\:0:*/
void TDepList::Insert(char *n, char *p)
{
  TDepItem i;

  memset(&i,0,sizeof(i));
  strncpy(i.Name,n,sizeof(i.Name)-1);
  strncpy(i.Path,p,sizeof(i.Path)-1);
  TDynArray::Insert(&i);
}
/*...e*/
/*...svoid TDepList\58\\58\AddMask\40\char \42\Mask\41\:0:*/
void TDepList::AddMask(char *Mask)
{
  TDepItem i;
  dd_ffblk _ffblk;
  bool Done;
  char Path[PATH_MAX] = "";
  char Name[PATH_MAX] = "";

  memset(&i,0,sizeof(i));

  FSplit(Mask,Path,Name);

  strcpy(i.Name,Name);
  strcpy(i.Path,Path);

  if (strchr(Mask,'*') || strchr(Mask,'?'))
  {
    Done = 0;
    Done = dd_findfirst(Mask,&_ffblk,0);
    while (!Done)
    {
      strcpy(i.Name,_ffblk.dd_name);
      TDynArray::Insert(&i);
      Done=dd_findnext(&_ffblk);
    }
  }
  else TDynArray::Insert(&i);
}
/*...e*/
/*...sInclude file parsing:0:*/
//------------------------- Include file parsing -------------------------

/*...sclass TIncludeParser:0:*/
class TIncludeParser {
  public:
    bool Parse(char *FileName, bool CPP=true);
    void setIncludes(char** iPathList, int _count);
    TDepList l;
  private:
    char FilePath[PATH_MAX];
    bool Comment,bCPP;
    char** InclPathList;
    int count;
    char* BasicParse(char *FileName);
    void ParseComments(char *s);
    void ParseCLine(char *s);
    void AddInclude(char *IncName);
};
/*...e*/
void TIncludeParser::setIncludes(char** iPathList, int _count) {
        InclPathList = iPathList;
        count = _count;
}
/*...svoid TIncludeParser\58\\58\AddInclude\40\char \42\IncName\41\:0:*/
void TIncludeParser::AddInclude(char *IncName)
{
  char s[160];
  char* Found;
  char Path[PATH_MAX] = "";
  char realfile[1000] = "";

/*...sSearch the real place:0:*/
  // Search on std include path's (First occurence fits)
  int foundStdPath = 0;

  for (int i = 0; i < count; i++) {
        FILE* f;
        strcpy(s, InclPathList[i]);
        strcat(s, IncName);

        f = fopen(s, "rt");

        if (f != NULL) {
                strcpy(realfile, s);
                fclose(f);
                foundStdPath = 1;
                break;
        }
  }

  if (foundStdPath == 0) {
        FILE* f;

        f = fopen(IncName, "rt");

        if (f != NULL) {
                strcpy(realfile, IncName);
                fclose(f);
        } else {
                        //fprintf(stderr, "Error: No standard path has this file, and this rule does not match for %s\n", IncName);
                }
  }
/*...e*/

  if (l.Search(IncName)) {
      //printf("File %s has already been added!\n", realfile);
        return;
  }

  if (strcmp(realfile,"") != 0)  {
    FSplit(realfile, Path, IncName);
    l.Insert(IncName,Path);
  }

/*...sVERBOSE:0:*/
#ifdef VERBOSE
  printf("    '%s'\n",IncName);
#endif
/*...e*/

  Found=BasicParse(IncName);
/*...sbla:0:*/
/*
  if (Found) {
        FSplit(Found, Path, IncName);
        printf("Insert include file %s%s\n", Path, IncName);
        l.Insert(IncName,Path);
  }
  else if (FilePath[0]!=0)
  {
    strcpy(s,FilePath);
    strcat(s,IncName);
    Found=BasicParse(s);
    FSplit(Found, Path, IncName);
    printf("Insert include file %s%s\n", Path, IncName);
    l.Insert(IncName,Path);
  }
*/
/*...e*/
/*...sVERBOSE:0:*/
#ifdef VERBOSE
  if (!Found)
    fprintf(stderr,"AddInclude: WARNING: %s could not be opened\n",IncName);
#endif
/*...e*/
}
/*...e*/
/*...svoid TIncludeParser\58\\58\ParseCLine\40\char \42\s\41\:0:*/
void TIncludeParser::ParseCLine(char *s)
{
  char *t,*p1,*p2;

  t=strstr(s,"#include");

  if (t)
  {
    p1=strchr(t,'"');
    if (p1)
    {
      p1++;
      p2=strchr(p1,'"');
      if (p2)
      {
        *p2=0;
/*...sVERBOSE:0:*/
#ifdef VERBOSE
        fprintf(stderr, "Add the include '%s' for line '%s'\n", p1, s);
#endif
/*...e*/
/// \todo Find a better way to skip wrong include detections.
        if (strcmp(p1, "") != 0) {
            AddInclude(p1);
        }
/*...sVERBOSE:0:*/
#ifdef VERBOSE
        printf("Added\n");
#endif
/*...e*/
      }
    }
    p1=strchr(t,'<');
    if (p1)
          {
                  p1++;
                  p2=strchr(p1,'>');
                  if (p2)
                  {
                          *p2=0;
                          /*...sVERBOSE:0:*/
#ifdef VERBOSE
                          fprintf(stderr, "Add the include '%s' for line '%s'\n", p1, s);
#endif
                          /*...e*/
                          /// \todo Find a better way to skip wrong include detections.
                          if (strcmp(p1, "") != 0) {
                                  AddInclude(p1);
                          }
                          /*...sVERBOSE:0:*/
#ifdef VERBOSE
                          printf("Added\n");
#endif
                          /*...e*/
                  }
          }
  }
}
/*...e*/
/*...svoid TIncludeParser\58\\58\ParseComments\40\char \42\s\41\:0:*/
void TIncludeParser::ParseComments(char *s)
{
  int i;

  i=0;
  do {
  #ifdef VERBOSE
    if (i == 20) printf("Char at %d, strlen is %d\n", i, strlen(s));
  #endif
    if (Comment)
    {
    #ifdef VERBOSE
      if (i == 20) printf("Comment state\n");
    #endif
      if (strlen(s)-1 < i) return;
      if (strlen(s)-1 < i+1) return;
      if (s[i]=='*' && s[i+1]=='/')
      {
        Comment=false;
        i++;
      }
      else {
        if (strlen(s)-1 < i) return;
        (s[i]='*');
      }
    }
    else {
      #ifdef VERBOSE
      if (i >= 20) printf("No comment state at %d\n", i);
      #endif
      if (strlen(s)-1 <= i) {
        #ifdef VERBOSE
        if (i >= 20) printf("Return 1\n");
        #endif
        return;
      }
      if (strlen(s)-1 <= i+1) {
        #ifdef VERBOSE
        if (i >= 20) printf("Return 2\n");
        #endif
        return;
      }
      #ifdef VERBOSE
      if (i >= 20) printf("Check for /\n");
      #endif
      if (s[i]=='/')
      {
      #ifdef VERBOSE
        if (i >= 20) printf("Do switch\n");
      #endif
       if (strlen(s) == i+1) {
         printf("Buffer overflow\n");
         return;
       }
        switch (s[i+1])
        {
          case '*': Comment=true; i++; break;
          case '/':
       #ifdef VERBOSE
                if (i >= 20) printf("Switch (/)\n");
       #endif
                s[i]=0;
                i--;
                break;
        }
      }
    }
    i++;
    if (strlen(s)-1 == i) return;
#ifdef VERBOSE
    if (i >= 20) printf("Do the while now\n");
#endif
  } while (s[i]);
}
/*...e*/
/*...sbool TIncludeParser\58\\58\Parse\40\char \42\FileName\44\ bool CPP\41\:0:*/
bool TIncludeParser::Parse(char *FileName, bool CPP)
{
  Comment=false;
  bCPP=CPP;
  GetPath(FileName,FilePath,sizeof(FilePath));

  if (!BasicParse(FileName))
  {
    //fprintf(stderr,"TIncludeParser::Parser() WARNING: %s could not be opened\n",FileName);
    return false;
  } else {
          return true;
  }
}
/*...e*/
/*...sbool TIncludeParser\58\\58\BasicParse\40\char \42\FileName\41\:0:*/
char* TIncludeParser::BasicParse(char *FileName)
{
  FILE *f;
  char Line[256];
  static char realfile[1000] = "";
  int success = 0;

/*...sfind file in standard include path:0:*/
  for (int i = 0; i < count; i++) {
    char file[1000] = "";
    strcat(file, InclPathList[i]);
    strcat(file, FileName);
    f=fopen(file,"rt");
    //printf("Open %s\n", file);
    if (f != NULL) {
        success = 1;
        strcpy(realfile, file);
        break;
    }
  }
/*...e*/

  if (success == 0) {
        f=fopen(FileName, "rt");
        if (f == NULL) return NULL;
        strcpy(realfile, FileName);
  }

  do {
    fgets(Line,sizeof(Line)-1,f);
    if (Line[0]!=0)
    {
      //printf("Parse %s\n", Line);
      ParseComments(Line);
      ParseCLine(Line);
    }
  } while (!feof(f));
  fclose(f);

  return realfile;
}
/*...e*/
/*...e*/

/*...svoid ObjExt\40\char \42\s\44\ char \42\ObjName\44\ int Len\41\:0:*/
void ObjExt(char *s, char *ObjName, int Len)
{
        // Copy max Len characters
        ObjName[0] = 0;
        strcpy(ObjName, s);

        // Strip extension.
        int len = strlen(ObjName);
        for (int i = len; i >= 0; i--) {
                if (ObjName[i] == '.') {
                        ObjName[i] = 0;
                        break;
                }
        }

        if ((targettype != IDL_TARGET) && (targettype != LEX_TARGET) && (targettype != YACC_TARGET))
        strcat(ObjName,".$(OBJ)");
}
/*...e*/

// Changes the install name to use included versions or locally installed versions (/usr/lib/...)
void change_install_names(bool included) {
        //printf("\t\tINSTALLNAMETOOL_WX_PREFIX=`wx-config --prefix`\n");
        //printf("\t\tINSTALLNAMETOOL_WX_BASENAME=`wx-config --basename`\n");
        //printf("\t\tINSTALLNAMETOOL_WX_VERSION=`wx-config --version`\n");
        if (included) {
                printf("\t\tinstall_name_tool `wx-config --prefix`/lib/lib`wx-config --basename`-`wx-config --release`.dylib -id @executable_path/../lib/lib`wx-config --basename`-`wx-config --release`.dylib\n");     
        } else {
                printf("\t\tinstall_name_tool `wx-config --prefix`/lib/lib`wx-config --basename`-`wx-config --release`.dylib -id `wx-config --prefix`/lib/lib`wx-config --basename`-`wx-config --release`.dylib\n");    
        }
}

/*...swriteExeTarget\40\char\42\ modulename\41\:0:*/
void writeBundleTarget(char* modulename) {
#ifdef OSX
#undef UNIX
        fprintf(stderr, "Writing osx executable target\n");
        printf("PROGRAM=%s\n", modulename);
        printf("MKMK_WX_VERSION=`wx-config --version`\n");
        printf("\n%s: $(OBJS)\n", modulename);
        
        change_install_names(true);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
        printf("\t\t$(CC) $(LDFLAGS) -o %s $(OBJS) $(OBJDEP) $(LIBS) -bind_at_load -lc $(VENDORLIBS)\n",modulename);
        
        // Write Mac OS X Bundle
        printf("\t\t#/Developer/Tools/Rez -d __DARWIN__ -t APPL -d __WXMAC__ -i . -d WXUSINGDLL -i $(HOME)/wxMac-$(MKMK_WX_VERSION)/samples -i $(HOME)/wxMac-$(MKMK_WX_VERSION)/include -o %s Carbon.r sample.r\n", modulename);
        printf("\t\t/Developer/Tools/SetFile -a C %s\n", modulename);
        printf("\t\t-$(HOME)/develop/wxMac-$(MKMK_WX_VERSION)/change-install-names $(HOME)/develop/wxMac-$(MKMK_WX_VERSION)/lib /usr/local %s\n", modulename);
        printf("\t\trm -Rf %s.app\n", modulename);
        printf("\t\tmkdir -p %s.app\n", modulename);
        printf("\t\tmkdir -p %s.app/Contents\n", modulename);
        printf("\t\tmkdir -p %s.app/Contents/MacOS\n", modulename);
        printf("\t\tmkdir -p %s.app/Contents/Frameworks\n", modulename);
        
        /// \todo Create module specific framework list to be copied instead.
        
        printf("\t\trm -Rf %s.app/Contents/Frameworks/lbHook.framework\n", modulename);
        printf("\t\trm -Rf %s.app/Contents/Frameworks/wxWrapperDLL.framework\n", modulename);
#ifdef OSNAME_Panther
        printf("\t\t-rm -Rf %s.app/Contents/Frameworks/wxAUI.framework\n", modulename);
#endif
        printf("\t\trm -Rf %s.app/Contents/Frameworks/wxPropgrid.framework\n", modulename);
        
        printf("\t\tcp -R $(prefix)/Library/Frameworks/lbHook.framework %s.app/Contents/Frameworks\n", modulename);
        printf("\t\tcp -R $(prefix)/Library/Frameworks/wxWrapperDLL.framework %s.app/Contents/Frameworks\n", modulename);
#ifdef OSNAME_Panther
        printf("\t\t-cp -R $(prefix)/Library/Frameworks/wxAUI.framework %s.app/Contents/Frameworks\n", modulename);
#endif
        printf("\t\tcp -R $(prefix)/Library/Frameworks/wxPropgrid.framework %s.app/Contents/Frameworks\n", modulename);
        printf("\t\tmkdir -p %s.app/Contents/Resources\n", modulename);
        printf("\t\tcp wxmac.icns %s.app/Contents/Resources/wxmac.icns\n", modulename, modulename);
        printf("\t\tsed -e \"s/IDENTIFIER/`echo . | sed -e 's,\\.\\./,,g' | sed -e 's,/,.,g'`/\" -e \"s/EXECUTABLE/%s/\" -e \"s/VERSION/$(MKMK_WX_VERSION)/\" $(HOME)/develop/wxMac-$(MKMK_WX_VERSION)/src/mac/carbon/Info.plist.in >%s.app/Contents/Info.plist\n", modulename, modulename);
        printf("\t\techo -n \"APPL????\" >%s.app/Contents/PkgInfo\n", modulename);
        printf("\t\tln -f %s %s.app/Contents/MacOS/%s\n", modulename, modulename, modulename);

        change_install_names(false);

        printf("\t\t-./postlink-mac.sh\n");
        //  printf("\t\t\n", modulename);
#endif
        
#ifdef UNIX
        fprintf(stderr, "Writing linux executable target\n");
        printf("PROGRAM=%s\n", modulename);
        printf("\n%s: $(OBJS)\n", modulename);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).       
        printf("\t\t$(CC) $(LDFLAGS) -o %s $(OBJS) $(OBJDEP) $(LIBS) -lc $(VENDORLIBS)\n",modulename);
#endif
        
#ifdef OSX
#define UNIX
#endif
        
#ifdef UNIX
        printf("install:\n");
        printf("\t\t$(CP) -Rf $(PROGRAM).app $(bindir)\n");
        
        printf("install-strip: install\n");
        printf("\t\t$(STRIP) $(PROGRAM)\n");
        //printf("\t\t$(INSTALL_PROGRAM) $(PROGRAM).app $(bindir)\n");
#endif
        
#ifdef __WATCOMC__
        char* ModName = strdup(modulename);
        char** array;
        int count = split('.', ModName, &array);
        
        printf("FILE = FIL\n");
        printf("FILE += $(foreach s, $(OBJS),$s, )\n");
        printf("LNK=%s.lnk\n", ModName);
        printf("ifeq ($(COMPILER), WATCOM)\n");
        printf("COMPILERFLAGS=@$(LNK)\n");
        printf("endif\n");
        printf("PROGRAM=%s\n", ModName);
        
        printf("\n%s.exe: $(OBJS)\n", ModName);
        printf("\t\t@echo Link %s.exe\n", ModName);
        printf("\t\t@echo NAME $(PROGRAM).exe > $(LNK)\n");
        printf("\t\t@echo $(FILE) $(LIBS) >> $(LNK)\n");
        printf("\t\t-@cmd /C \"attrib -r *.bak\"\n");
        printf("\t\t@$(LINK) $(LINKFLAGS) $(LIBRS) $(COMPILERFLAGS)\n");
        printf("\t\t@$(CP) $(PROGRAM).exe $(EXEDIR) > null\n");
        printf("\t\t@$(CP) $(PROGRAM).sym $(EXEDIR) > null\n");
#endif
}
/*...e*/


/*...swriteExeTarget\40\char\42\ modulename\41\:0:*/
void writeExeTarget(char* modulename) {
#ifdef OSX
#undef UNIX
  fprintf(stderr, "Writing osx executable target\n");
  printf("PROGRAM=%s\n", modulename);
  printf("\n%s: $(OBJS)\n", modulename);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -o %s $(OBJS) $(OBJDEP) $(LIBS) -bind_at_load -lc $(VENDORLIBS)\n",modulename);
#endif

#ifdef UNIX
  fprintf(stderr, "Writing linux executable target\n");
  printf("PROGRAM=%s\n", modulename);
  printf("\n%s: $(OBJS)\n", modulename);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -o %s $(OBJS) $(OBJDEP) $(LIBS) $(VENDORLIBS)\n",modulename);
  printf("\t\t$(CP) $(PROGRAM) $(prefix)/bin\n");
#endif



#ifdef OSX
#define UNIX
#endif

#ifdef UNIX
  printf("install:\n");
  printf("\t\t$(CP) $(PROGRAM) $(bindir)\n");

  printf("install-strip:\n");
  printf("\t\t$(STRIP) $(PROGRAM)\n");
  printf("\t\t$(INSTALL_PROGRAM) $(PROGRAM) $(bindir)\n");
#endif

#ifdef __WATCOMC__
  char* ModName = strdup(modulename);
  char** array;
  int count = split('.', ModName, &array);

  printf("FILE = FIL\n");
  printf("FILE += $(foreach s, $(OBJS),$s, )\n");
  printf("LNK=%s.lnk\n", ModName);
  printf("ifeq ($(COMPILER), WATCOM)\n");
  printf("COMPILERFLAGS=@$(LNK)\n");
  printf("endif\n");
  printf("PROGRAM=%s\n", ModName);

  printf("\n%s.exe: $(OBJS)\n", ModName);
  printf("\t\t@echo Link %s.exe\n", ModName);
  printf("\t\t@echo NAME $(PROGRAM).exe > $(LNK)\n");
  printf("\t\t@echo $(FILE) $(LIBS) >> $(LNK)\n");
  printf("\t\t-@cmd /C \"attrib -r *.bak\"\n");
  printf("\t\t@$(LINK) $(LINKFLAGS) $(LIBRS) $(COMPILERFLAGS)\n");
  printf("\t\t@$(CP) $(PROGRAM).exe $(EXEDIR) > null\n");
  printf("\t\t@$(CP) $(PROGRAM).sym $(EXEDIR) > null\n");
#endif
}
/*...e*/
/*...swriteExeTarget\40\char\42\ modulename\41\:0:*/
void writeMinGWExeTarget(char* modulename) {
#ifdef OSX
#undef UNIX
  fprintf(stderr, "Writing osx executable target\n");
  printf("PROGRAM=%s\n", modulename);
  printf("\n%s: $(OBJS)\n", modulename);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -o %s $(OBJS) $(OBJDEP) $(LIBS) -bind_at_load -lc $(VENDORLIBS)\n",modulename);
#endif

#ifdef UNIX
  fprintf(stderr, "Writing linux executable target\n");
  printf("PROGRAM=%s\n", modulename);
  printf("\n%s: $(OBJS)\n", modulename);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -o %s $(OBJS) $(OBJDEP) $(LIBS) $(VENDORLIBS)\n",modulename);
  printf("\t\t$(CP) $(PROGRAM) $(prefix)/bin\n");
#endif



#ifdef OSX
#define UNIX
#endif

#ifdef UNIX
  printf("install:\n");
  printf("\t\t$(CP) $(PROGRAM) $(bindir)\n");

  printf("install-strip:\n");
  printf("\t\t$(STRIP) $(PROGRAM)\n");
  printf("\t\t$(INSTALL_PROGRAM) $(PROGRAM) $(bindir)\n");
#endif

#ifdef __WATCOMC__
  char* ModName = strdup(modulename);
  char** array;
  int count = split('.', ModName, &array);
#ifdef muster
testmingw.exe: test.o
                rm testdll.lib
                g++ -o testmingw.exe test.o -L. -ltestdll
#endif

  printf("PROGRAM=%s\n", ModName);

  printf("\n%s.exe: $(OBJS)\n", ModName);

  printf("\t\t@g++ -Wl,--enable-auto-import -o $(PROGRAM).exe $(OBJS) $(MINGWLIBS)\n");
  printf("\t\t@$(CP) $(PROGRAM).exe $(EXEDIR) > null\n");
#endif
}
/*...e*/
/*...svoid writeLexTarget\40\char\42\ modulename\41\:0:*/
void writeLexTarget(char* modulename) {
#ifdef UNIX
  //printf("\n%s.yy.c: $(OBJS)\n", modulename);
  //printf("\t\techo Dummy target for lex files.\n");
#endif
#ifdef __WATCOMC__
#endif

#ifdef UNIX
  printf("install:\n");
  printf("\n", modulename);

  printf("install-strip:\n");
  printf("\n", modulename);
#endif
}
/*...e*/
/*...svoid writeYaccTarget\40\char\42\ modulename\41\:0:*/
void writeYaccTarget(char* modulename) {
#ifdef UNIX
  //printf("\n%s.output: $(OBJS)\n", modulename);
  //printf("\t\techo Dummy target for yacc files.\n");
#endif
#ifdef __WATCOMC__
#endif

#ifdef UNIX
  printf("install:\n");
  printf("\n", modulename);

  printf("install-strip:\n");
  printf("\n", modulename);
#endif
}
/*...e*/

/*...swriteMinGWDllTarget\40\char\42\ modulename\41\:0:*/
void writeMinGWDllTarget(char* modulename) {
#ifdef UNIX
  printf("\n%s: $(OBJS)\n", modulename);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(MINGWCC) $(LDFLAGS) -o %s $(OBJS) $(OBJDEP)\n",modulename);
#endif
#ifdef __WATCOMC__
  char* ModName = strdup(modulename);
  char** array;
  int count = split('.', ModName, &array);

  printf("FILE = FIL\n");
  printf("FILE += $(OBJLIST)\n");
  printf("LNK=%s.lnk\n", ModName);
  printf("ifeq ($(COMPILER), WATCOM)\n");
  printf("LINKFLAGS=@%s.lnk\n", targetname);
  printf("endif\n");
  printf("ifeq ($(COMPILER), MICROSOFT)\n");
  printf("LINKFLAGS=$(OBJS) $(VENDORLIBS) $(LIBS)\n");
  printf("endif\n");
  printf("PROGRAM=%s\n", ModName);

  printf("ifeq ($(COMPILER), WATCOM)\n");

  printf("\n%s.dll: $(OBJS) %s.dll.lnk\n", ModName, ModName);
  printf("\t\t@echo Link %s.dll\n", ModName);

  printf("\t\t@cmd /C if NOT \"$(LIBS)\" == \"\" echo LIBR $(LIBS) >> $@.lnk\n");

  //printf("\t\t@$(CPPMINGW) -Wl,--kill-at,--output-def=$(PROGRAM).def -shared -o $(PROGRAM).dll $(OBJS) $(MINGWLIBS)\n");
  printf("\t\t@$(CPPMINGW) -fPIC -shared -Wl,--enable-auto-import -Wl,--subsystem,windows -mthreads -mwindows -Wl,--out-implib=$(PROGRAM).a -o $(PROGRAM).dll $(OBJS) $(MINGWLIBS)\n");
  //printf("\t\t@wlib -q -n -b $(PROGRAM).lib +$(PROGRAM).dll\n");
  printf("\t\t@$(CP) $(PROGRAM).dll $(DLLDIR) > null\n");
  printf("\t\t@$(CP) $(PROGRAM).a $(DLLLIBDIR) > null\n");
  printf("\t\t@$(POST_PROCESS) \n");

/*
  printf("\t\t\n");

  printf("%s.dll.lnk: makefile\n", ModName);

  printf("\t\t@echo NAME $(PROGRAM).dll > $(LNK)\n");
  printf("\t\t@echo FIL { $(OBJS) } >> $@\n");

  printf("\t\t@cmd /C \"doit >> %s.lnk\"\n", targetname);
  printf("\t\t@cmd /C \"rm doit.bat\"\n");
  printf("\t\t-@cmd /C \"attrib -r *.bak\"\n");

  printf("\t\t@echo @rem Nothing > doit.bat\n");
  printf("\t\t@echo @if NOT \\\"$(LIBS)\\\" == \\\"\\\" echo LIBR $(LIBS) > doit.bat\n");
*/

  printf("endif\n");

  printf("ifeq ($(COMPILER), MICROSOFT)\n");
  printf("\n%s.dll: $(OBJS)\n", ModName);
  printf("\t\t@echo Link %s.dll\n", ModName);
  printf("\t\t@echo NAME $(PROGRAM).dll > $(LNK)\n");
  printf("\t\t@echo $(FILE) $(LIBS) >> $(LNK)\n");
// Don know, why this doesn't work now ??
//  printf("\t\t@;if NOT \"$(LIBS)\" == \"\" echo LIBR $(LIBS) >> $(LNK)\n");
  printf("\t\t@$(LINK) $(LNKDLLOPS) $(LINKFLAGS)\n");
// Hack for copy not found ??
  printf("\t\t$(CP) $(PROGRAM).dll $(DLLDIR) > null\n");
  printf("\t\t$(CP) $(PROGRAM).lib $(DLLLIBDIR) > null\n");
  printf("\t\t@$(POST_PROCESS) \n");
  printf("endif\n");
#endif

#ifdef UNIX
  printf("install:\n");
  printf("\t\t$(INSTALL_PROGRAM) %s $(libdir)\n", modulename);

  printf("install-strip:\n");
  printf("\t\t$(STRIP) $(PROGRAM)\n");
  printf("\t\t$(INSTALL_PROGRAM) %s $(libdir)\n", modulename);
#endif

}
/*...e*/
/*...swriteMinGWPluginTarget\40\char\42\ modulename\41\:0:*/
void writeMinGWPluginTarget(char* modulename) {
#ifdef UNIX
  printf("\n%s: $(OBJS)\n", modulename);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -o %s $(OBJS) $(OBJDEP)\n",modulename);
#endif
#ifdef __WATCOMC__
  char* ModName = strdup(modulename);
  char** array;
  int count = split('.', ModName, &array);

  printf("FILE = FIL\n");
//  printf("FILE += $(foreach s, $(OBJS),$s, )\n");
  printf("FILE += $(OBJLIST)\n");
  printf("LNK=%s.lnk\n", ModName);
  printf("ifeq ($(COMPILER), WATCOM)\n");
  printf("LINKFLAGS=@$(LNK)\n");
  printf("endif\n");
  printf("ifeq ($(COMPILER), MICROSOFT)\n");
  printf("LINKFLAGS=$(OBJS) $(VENDORLIBS) $(LIBS)\n");
  printf("endif\n");
  printf("PROGRAM=%s\n", ModName);

  printf("ifeq ($(COMPILER), WATCOM)\n");
  printf("\n%s.dll: $(OBJS)\n", ModName);

//  printf("\t\t@$(CPPMINGW) -Wl,--kill-at,--output-def=$(PROGRAM).def -shared -o $(PROGRAM).dll $(OBJS) $(MINGWLIBS)\n");
  printf("\t\t@$(CPPMINGW) -fPIC -shared -Wl,--enable-auto-import -Wl,--subsystem,windows -mthreads -mwindows -Wl,--out-implib=$(PROGRAM).a -o $(PROGRAM).dll $(OBJS) $(MINGWLIBS)\n");
  //printf("\t\t@wlib -q -n -b $(PROGRAM).lib +$(PROGRAM).dll\n");
  printf("\t\t@$(CP) $(PROGRAM).dll $(PLUGINDIR) > null\n");
  printf("\t\t@$(CP) $(PROGRAM).a $(PLUGINLIBDIR) > null\n");
  printf("\t\t@$(POST_PROCESS) \n\n");

/*
  printf("\t\t@cmd /C \"doit >> $(LNK)\"\n");
  printf("\t\trm doit.bat\n");
//  printf("\t\t@;if NOT \"$(LIBS)\" == \"\" echo LIBR $(LIBS) >> $(LNK)\n");
  printf("\t\t-@cmd /C \"attrib -r *.bak\"\n");
  printf("\t\t@$(LINK) $(LNKDLLOPS) $(LINKFLAGS)\n");
  printf("\t\t@wlib -q -n -b $(PROGRAM).lib +$(PROGRAM).dll\n");
  printf("\t\t@$(CP) $(PROGRAM).sym $(PLUGINDIR) > null\n");
  printf("\t\t@$(CP) $(PROGRAM).dll $(PLUGINDIR) > null\n");
  printf("\t\t@$(CP) $(PROGRAM).lib $(PLUGINLIBDIR) > null\n");
*/

  printf("endif\n");

  printf("ifeq ($(COMPILER), MICROSOFT)\n");
  printf("\n%s.dll: $(OBJS)\n", ModName);
  printf("\t\t@echo Link %s.dll\n", ModName);
  printf("\t\t@echo NAME $(PROGRAM).dll > $(LNK)\n");
  printf("\t\t@echo $(FILE) $(LIBS) >> $(LNK)\n");
// Don know, why this doesn't work now ??
//  printf("\t\t@;if NOT \"$(LIBS)\" == \"\" echo LIBR $(LIBS) >> $(LNK)\n");
  printf("\t\t@$(LINK) $(LNKDLLOPS) $(LINKFLAGS)\n");
// Hack for copy not found ??
  printf("\t\t$(CP) $(PROGRAM).dll $(PLUGINDIR) > null\n");
  printf("\t\t$(CP) $(PROGRAM).lib $(PLUGINLIBDIR) > null\n");
  printf("endif\n");
#endif
}
/*...e*/


/*...swriteDllTarget\40\char\42\ modulename\41\:0:*/
void writeDllTarget(char* modulename) {
#ifdef UNIX
  printf("\n%s: $(OBJS)\n", modulename);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -o %s $(OBJS) $(OBJDEP)\n",modulename);
#endif
#ifdef __WATCOMC__
  char* ModName = strdup(modulename);
  char** array;
  int count = split('.', ModName, &array);

  printf("FILE = FIL\n");
//  printf("FILE += $(foreach s, $(OBJS),$s, )\n");
  printf("FILE += $(OBJLIST)\n");
  printf("LNK=%s.lnk\n", ModName);
  printf("ifeq ($(COMPILER), WATCOM)\n");
  printf("LINKFLAGS=@%s.lnk\n", targetname);
  printf("endif\n");
  printf("ifeq ($(COMPILER), MICROSOFT)\n");
  printf("LINKFLAGS=$(OBJS) $(VENDORLIBS) $(LIBS)\n");
  printf("endif\n");
  printf("PROGRAM=%s\n", ModName);

  printf("ifeq ($(COMPILER), WATCOM)\n");

  printf("\n%s.dll: $(OBJS) %s.dll.lnk\n", ModName, ModName);
  printf("\t\t@echo Link %s.dll\n", ModName);
//  printf("\t\t@echo $(FILE) >> $(LNK)\n");

  printf("\t\t@cmd /C if NOT \"$(LIBS)\" == \"\" echo LIBR $(LIBS) >> $@.lnk\n");

  printf("\t\t@$(LINK) $(LNKDLLOPS) $(LINKFLAGS)\n");
  printf("\t\t@wlib -q -n -b $(PROGRAM).lib +$(PROGRAM).dll\n");
  printf("\t\t@$(CP) $(PROGRAM).dll $(DLLDIR) > null\n");
  printf("\t\t@$(CP) $(PROGRAM).sym $(DLLDIR) > null\n");
  printf("\t\t@$(CP) $(PROGRAM).lib $(DLLLIBDIR) > null\n");
  printf("\t\t@$(POST_PROCESS) \n");

/*
  printf("\t\t\n");

  printf("%s.dll.lnk: makefile\n", ModName);

  printf("\t\t@echo NAME $(PROGRAM).dll > $(LNK)\n");
  printf("\t\t@echo FIL { $(OBJS) } >> $@\n");

  printf("\t\t@cmd /C \"doit >> %s.lnk\"\n", targetname);
  printf("\t\t@cmd /C \"rm doit.bat\"\n");
  printf("\t\t-@cmd /C \"attrib -r *.bak\"\n");

  printf("\t\t@echo @rem Nothing > doit.bat\n");
  printf("\t\t@echo @if NOT \\\"$(LIBS)\\\" == \\\"\\\" echo LIBR $(LIBS) > doit.bat\n");
*/

  printf("endif\n");

  printf("ifeq ($(COMPILER), MICROSOFT)\n");
  printf("\n%s.dll: $(OBJS)\n", ModName);
  printf("\t\t@echo Link %s.dll\n", ModName);
  printf("\t\t@echo NAME $(PROGRAM).dll > $(LNK)\n");
  printf("\t\t@echo $(FILE) $(LIBS) >> $(LNK)\n");
// Don know, why this doesn't work now ??
//  printf("\t\t@;if NOT \"$(LIBS)\" == \"\" echo LIBR $(LIBS) >> $(LNK)\n");
  printf("\t\t@$(LINK) $(LNKDLLOPS) $(LINKFLAGS)\n");
// Hack for copy not found ??
  printf("\t\t$(CP) $(PROGRAM).dll $(DLLDIR) > null\n");
  printf("\t\t$(CP) $(PROGRAM).lib $(DLLLIBDIR) > null\n");
  printf("\t\t@$(POST_PROCESS) \n");
  printf("endif\n");
#endif

#ifdef UNIX
  printf("install:\n");
  printf("\t\t$(INSTALL_PROGRAM) %s $(libdir)\n", modulename);

  printf("install-strip:\n");
  printf("\t\t$(STRIP) $(PROGRAM)\n");
  printf("\t\t$(INSTALL_PROGRAM) %s $(libdir)\n", modulename);
#endif

}
/*...e*/
/*...swritePluginTarget\40\char\42\ modulename\41\:0:*/
void writePluginTarget(char* modulename) {
#ifdef UNIX
  printf("\n%s: $(OBJS)\n", modulename);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -o %s $(OBJS) $(OBJDEP)\n",modulename);
#endif
#ifdef __WATCOMC__
  char* ModName = strdup(modulename);
  char** array;
  int count = split('.', ModName, &array);

  printf("FILE = FIL\n");
//  printf("FILE += $(foreach s, $(OBJS),$s, )\n");
  printf("FILE += $(OBJLIST)\n");
  printf("LNK=%s.lnk\n", ModName);
  printf("ifeq ($(COMPILER), WATCOM)\n");
  printf("LINKFLAGS=@$(LNK)\n");
  printf("endif\n");
  printf("ifeq ($(COMPILER), MICROSOFT)\n");
  printf("LINKFLAGS=$(OBJS) $(VENDORLIBS) $(LIBS)\n");
  printf("endif\n");
  printf("PROGRAM=%s\n", ModName);

  printf("ifeq ($(COMPILER), WATCOM)\n");
  printf("\n%s.dll: $(OBJS)\n", ModName);
  printf("\t\t@echo Link %s.dll\n", ModName);
  printf("\t\t@echo NAME $(PROGRAM).dll > $(LNK)\n");
  printf("\t\t@echo $(FILE) >> $(LNK)\n");

  printf("\t\t@echo @rem Nothing > doit.bat\n");
  printf("\t\t@echo @if NOT \\\"$(LIBS)\\\" == \\\"\\\" echo LIBR $(LIBS) > doit.bat\n");

  printf("\t\t@cmd /C \"doit >> $(LNK)\"\n");
  printf("\t\trm doit.bat\n");
//  printf("\t\t@;if NOT \"$(LIBS)\" == \"\" echo LIBR $(LIBS) >> $(LNK)\n");
  printf("\t\t-@cmd /C \"attrib -r *.bak\"\n");
  printf("\t\t@$(LINK) $(LNKDLLOPS) $(LINKFLAGS)\n");
  printf("\t\t@wlib -q -n -b $(PROGRAM).lib +$(PROGRAM).dll\n");
  printf("\t\t@$(CP) $(PROGRAM).sym $(PLUGINDIR) > null\n");
  printf("\t\t@$(CP) $(PROGRAM).dll $(PLUGINDIR) > null\n");
  printf("\t\t@$(CP) $(PROGRAM).lib $(PLUGINLIBDIR) > null\n");
  printf("endif\n");

  printf("ifeq ($(COMPILER), MICROSOFT)\n");
  printf("\n%s.dll: $(OBJS)\n", ModName);
  printf("\t\t@echo Link %s.dll\n", ModName);
  printf("\t\t@echo NAME $(PROGRAM).dll > $(LNK)\n");
  printf("\t\t@echo $(FILE) $(LIBS) >> $(LNK)\n");
// Don know, why this doesn't work now ??
//  printf("\t\t@;if NOT \"$(LIBS)\" == \"\" echo LIBR $(LIBS) >> $(LNK)\n");
  printf("\t\t@$(LINK) $(LNKDLLOPS) $(LINKFLAGS)\n");
// Hack for copy not found ??
  printf("\t\t$(CP) $(PROGRAM).dll $(PLUGINDIR) > null\n");
  printf("\t\t$(CP) $(PROGRAM).lib $(PLUGINLIBDIR) > null\n");
  printf("endif\n");
#endif
}
/*...e*/
/*...swriteLibTarget\40\char\42\ modulename\44\ TDepList\42\ l\41\:0:*/
void writeLibTarget(char* modulename, TDepList* l) {
#ifdef __WATCOMC__
  char* ModName = strdup(modulename);
  char** array;
  int count = split('.', ModName, &array);

  printf("FILE = FIL\n");
  printf("FILE += $(foreach s, $(OBJS),$s, )\n");
  printf("LNK=%s.lnk\n", ModName);
  printf("PROGRAM=%s\n", ModName);

  printf("\n%s.lib: $(OBJS)\n", ModName);
  printf("\t\t@echo Link %s.lib\n", ModName);

  TDepItem *d;
  char FName[80] = "";

  printf("\t\t$(RM) $(LNK)\n");

  for (int i=0; i<l->Count; i++)
  {
    d=(TDepItem*)(*l)[i];

    ObjExt(d->Name,FName,sizeof(FName));

    printf("\t\t@echo +%s >> $(LNK)\n", FName);
  }

  printf("\t\t@wlib -b -c -n -q -p=512 $(PROGRAM).lib @$(LNK)\n");
  printf("\t\t@cmd /C \"$(CP) $(PROGRAM).lib $(LIBDIR) > null\"\n");
#endif
}
/*...e*/
/*...svoid write_lex_clean\40\char\42\ modulename \61\ NULL\41\:0:*/
/// \todo Implement cleanup routine
void write_lex_clean(char* modulename = NULL) {
#ifdef __WATCOMC__
    // Write the normal clean rule
    printf("clean:\n");

    // Write the distclean rule
    printf("distclean:\n");
#endif //__WATCOMC__
#ifdef UNIX
    // Write the normal clean rule
    printf("clean:\n");

    // Write the distclean rule
    printf("distclean:\n");
#endif //UNIX
}
/*...e*/
/*...svoid write_yacc_clean\40\char\42\ modulename \61\ NULL\41\:0:*/
/// \todo Implement cleanup routine
void write_yacc_clean(char* modulename = NULL) {
#ifdef __WATCOMC__
    // Write the normal clean rule
    printf("clean:\n");

    // Write the distclean rule
    printf("distclean:\n");
#endif //__WATCOMC__
#ifdef UNIX
    // Write the normal clean rule
    printf("clean:\n");

    // Write the distclean rule
    printf("distclean:\n");
#endif //UNIX
}
/*...e*/

/*...swrite_clean\40\char\42\ modulename \61\ NULL\41\:0:*/
void write_clean(char* modulename = NULL) {
#ifdef __WATCOMC__
    // Write the normal clean rule
    printf("clean:\n");
    printf("\t\t-@rm *.exp *.err *.ilk *.lib *.lk1 *.mk1 *.map *.mk *.mk1 *.sym *.obj *.o *.idb *.pch *.pdb\n");
    printf("\t\t-@rm -f *.bak\n");
#ifdef bla
    printf("\t\t-@rm *.err\n");
    printf("\t\t-@rm *.ilk\n");
    printf("\t\t-@rm *.lib\n");
    printf("\t\t-@rm *.lk1\n");
    printf("\t\t-@rm *.mk1\n");
    printf("\t\t-@rm *.map\n");
    printf("\t\t-@rm *.mk\n");
    printf("\t\t-@rm *.mk1\n");
    printf("\t\t-@rm *.sym\n");
    printf("\t\t-@rm *.obj\n");
    printf("\t\t-@rm *.o\n");
    printf("\t\t-@rm -f *.bak\n");
    printf("\t\t-@rm *.idb\n");
    printf("\t\t-@rm *.pch\n");
    printf("\t\t-@rm *.pdb\n");
#endif
    if (modulename == NULL) {
        printf("\t\t-@rm *.dll\n");
    } else {
        printf("\t\t-@rm %s.exe\n", modulename);
    }

    // Write the distclean rule
    printf("distclean:\n");
    printf("\t\t-@rm *.o\n");
    printf("\t\t-@rm makefile\n");
    printf("\t\t-@rm *.log\n");
    if (modulename == NULL) {
        printf("\t\t-@rm *.so.*\n");
    } else {
        printf("\t\t-@rm %s\n", modulename);
    }
#endif //__WATCOMC__
#ifdef UNIX
    // Write the normal clean rule
    printf("clean:\n");
    printf("\t\t-rm *.o\n");
    if (modulename == NULL) {
        printf("\t\t-rm *.so.*\n");
        printf("\t\t-rm *.so\n");
    } else {
        printf("\t\t-rm %s\n", modulename);
    }

    // Write the distclean rule
    printf("distclean:\n");
    printf("\t\t-rm *.o\n");
    printf("\t\t-rm makefile\n");
    printf("\t\t-rm *.log\n");
    if (modulename == NULL) {
        printf("\t\t-rm *.so.*\n");
    } else {
        printf("\t\t-rm %s\n", modulename);
    }
#endif //UNIX
}
/*...e*/

/*...swrite_so_Target\40\char\42\ modulename\41\ create a UNIX shared library:0:*/
void write_so_Target(char* modulename) {
#ifdef UNIX
  printf("PROGRAM=%s\n", modulename);
  printf("MAJOR=0\n");
  printf("MINOR=0\n");
  printf("MICRO=1\n");
  printf("\n%s: $(OBJS)\n", modulename);

// Patch to create dynamic libraries under Mac OS X
#ifdef OSX
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -dynamiclib -WL,soname,$(PROGRAM).$(MAJOR) -install_name \"@executable_path/../lib/$(PROGRAM)\" -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) $(VENDORLIBS)\n");
#undef UNIX
#endif
#ifdef UNIX
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -shared -Wl,-soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) $(VENDORLIBS)\n");
#endif

#ifdef OSX
#define UNIX
#endif

  printf("\n");
  printf("install:\n");
  printf("\t\t$(INSTALL) $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(libdir)\n");
  printf("\t\techo cd $(libdir) >mklink.sh\n");
  printf("\t\techo ln -sf $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(PROGRAM).$(MAJOR) >>mklink.sh\n");
  printf("\t\techo ln -sf $(PROGRAM).$(MAJOR) $(PROGRAM) >>mklink.sh\n");
  printf("\t\tchmod +x mklink.sh\n");
  printf("\t\t./mklink.sh\n");
  printf("\t\trm mklink.sh\n");

  printf("\n");
  printf("install-strip: install\n");
  printf("\t\t$(STRIP) $(libdir)/$(PROGRAM).$(MAJOR).$(MINOR).$(MICRO)\n");

#endif
#ifdef __WATCOMC__
  fprintf(stderr, "Warning: Creating a so library under Windows is not possible with Watcom !!\n");
#endif
}
/*...e*/
/*...swrite_so_bundleTarget\40\char\42\ modulename\41\ create a UNIX shared library:0:*/
void write_so_bundleTarget(char* modulename) {
#ifdef UNIX
  printf("PROGRAM=%s\n", modulename);
  printf("MAJOR=0\n");
  printf("MINOR=0\n");
  printf("MICRO=1\n");
  printf("\n%s: $(OBJS)\n", modulename);

        // Patch to create dynamic libraries under Mac OS X
#ifdef OSX
        
  change_install_names(true);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).        
  printf("\t\t$(CC) $(LDFLAGS) -dynamic -bundle -WL,soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) $(VENDORLIBS)\n");
        
  change_install_names(false);
        
#undef UNIX
#endif
#ifdef UNIX
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -shared -Wl,-soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) $(VENDORLIBS)\n");
#endif

#ifdef OSX
#define UNIX
#endif

  printf("\n");
  printf("install:\n");
  printf("\t\t$(INSTALL) $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(libdir)\n");
  printf("\t\techo cd $(libdir) >mklink.sh\n");
  printf("\t\techo ln -sf $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(PROGRAM).$(MAJOR) >>mklink.sh\n");
  printf("\t\techo ln -sf $(PROGRAM).$(MAJOR) $(PROGRAM) >>mklink.sh\n");
  printf("\t\tchmod +x mklink.sh\n");
  printf("\t\t./mklink.sh\n");
  printf("\t\trm mklink.sh\n");

  printf("\n");
  printf("install-strip: install\n");
  printf("\t\t$(STRIP) $(libdir)/$(PROGRAM).$(MAJOR).$(MINOR).$(MICRO)\n");

#endif
#ifdef __WATCOMC__
  fprintf(stderr, "Warning: Creating a so library under Windows is not possible with Watcom !!\n");
#endif
}
/*...e*/
/*...swrite_wx_so_Target\40\char\42\ modulename\41\ create a UNIX shared library:0:*/
void write_wx_so_Target(char* modulename) {
#ifdef UNIX
  printf("PROGRAM=%s\n", modulename);
  printf("MAJOR=0\n");
  printf("MINOR=0\n");
  printf("MICRO=1\n");
  printf("\n%s: $(OBJS)\n", modulename);

// Patch to create dynamic libraries under Mac OS X
#ifdef OSX
        
        change_install_names(true);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).        
        printf("\t\t$(CC) $(LDFLAGS) -dynamic -bundle -WL,soname,$(PROGRAM).$(MAJOR) -install_name \"@executable_path/../lib/$(PROGRAM)\" -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) `wx-config --libs` $(OBJS) $(OBJDEP) $(VENDORLIBS)\n");
        
        change_install_names(false);
        
#undef UNIX
#endif
#ifdef UNIX
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -shared -Wl,-soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) $(VENDORLIBS)\n");
#endif
#ifdef OSX
#define UNIX
#endif

  printf("\n");
  printf("install:\n");
  printf("\t\t$(INSTALL) $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(libdir)\n");
  printf("\t\techo cd $(libdir) >mklink.sh\n");
  printf("\t\techo ln -sf $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(PROGRAM).$(MAJOR) >>mklink.sh\n");
  printf("\t\techo ln -sf $(PROGRAM).$(MAJOR) $(PROGRAM) >>mklink.sh\n");
  printf("\t\tchmod +x mklink.sh\n");
  printf("\t\t./mklink.sh\n");
  printf("\t\trm mklink.sh\n");

  printf("\n");
  printf("install-strip: install\n");
  printf("\t\t$(STRIP) $(libdir)/$(PROGRAM).$(MAJOR).$(MINOR).$(MICRO)\n");

#endif
#ifdef __WATCOMC__
  fprintf(stderr, "Warning: Creating a so library under Windows is not possible with Watcom !!\n");
#endif
}
/*...e*/
/*...swrite_wx_shared_Target\40\char\42\ modulename\41\ create a UNIX shared library:0:*/
void write_wx_shared_Target(char* modulename) {
#ifdef UNIX
  printf("PROGRAM=%s\n", modulename);
  printf("MAJOR=0\n");
  printf("MINOR=0\n");
  printf("MICRO=1\n");
  printf("\n%s: $(OBJS)\n", modulename);

// Patch to create dynamic libraries under Mac OS X
#ifdef OSX
        
        change_install_names(true);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).        
        printf("\t\t$(CC) $(LDFLAGS) -dynamiclib -WL,soname,$(PROGRAM).$(MAJOR) -install_name \"@executable_path/../lib/$(PROGRAM)\" -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) `wx-config --libs` $(OBJS) $(OBJDEP) $(VENDORLIBS)\n");
        
        change_install_names(false);
        
#undef UNIX
#endif
#ifdef UNIX
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -shared -Wl,-soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) `wx-config --libs` $(OBJS) $(OBJDEP) $(LIBS) $(VENDORLIBS)\n");
#endif
#ifdef OSX
#define UNIX
#endif

  printf("\n");
  printf("install:\n");
  printf("\t\t$(INSTALL) $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(libdir)\n");
  printf("\t\techo cd $(libdir) >mklink.sh\n");
  printf("\t\techo ln -sf $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(PROGRAM).$(MAJOR) >>mklink.sh\n");
  printf("\t\techo ln -sf $(PROGRAM).$(MAJOR) $(PROGRAM) >>mklink.sh\n");
  printf("\t\tchmod +x mklink.sh\n");
  printf("\t\t./mklink.sh\n");
  printf("\t\trm mklink.sh\n");

  printf("\n");
  printf("install-strip: install\n");
  printf("\t\t$(STRIP) $(libdir)/$(PROGRAM).$(MAJOR).$(MINOR).$(MICRO)\n");

#endif
#ifdef __WATCOMC__
  fprintf(stderr, "Warning: Creating a so library under Windows is not possible with Watcom !!\n");
#endif
}
/*...e*/
/*...svoid write_wx_framework_Target\40\char\42\ modulename\41\:0:*/
void write_wx_framework_Target(char* modulename) {
#ifdef UNIX
  printf("PROGRAM=%s\n", modulename);
  printf("MAJOR=0\n");
  printf("MINOR=0\n");
  printf("MICRO=1\n");
  printf("\n%s.framework: $(OBJS)\n", modulename);

// Create the  directory structure

  printf("\t\t-rm -R %s.framework\n", modulename);
  printf("\t\tmkdir -p %s.framework/Versions/A/Resources\n", modulename);

  printf("\t\techo \\<?xml version=\"1.0\" encoding=\"UTF-8\"?\\> > Info.plist\n");
  printf("\t\techo \\<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\"\\> >> Info.plist\n");
  printf("\t\techo \\<plist version=\"1.0\"\\> >> Info.plist\n");
  printf("\t\techo \\<dict\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>CFBundleDevelopmentRegion\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>English\\</string\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>CFBundleExecutable\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>%s\\</string\\> >> Info.plist\n", modulename);
  printf("\t\techo      \\<key\\>CFBundleIconFile\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>\\</string\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>CFBundleIdentifier\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>com.apple.%sframework\\</string\\> >> Info.plist\n", modulename);
  printf("\t\techo      \\<key\\>CFBundleInfoDictionaryVersion\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>6.0\\</string\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>CFBundlePackageType\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>FMWK\\</string\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>CFBundleSignature\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>????\\</string\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>CFBundleVersion\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>1.0\\</string\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>NSPrincipalClass\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>\\</string\\> >> Info.plist\n");
  printf("\t\techo \\</dict\\> >> Info.plist\n");
  printf("\t\techo \\</plist\\> >> Info.plist\n");

  printf("\t\tcp Info.plist %s.framework/Versions/A/Resources\n", modulename);

  printf("\t\tmkdir -p %s.framework/Versions/A/Resources/English.lproj\n", modulename);

/* Localized versions of Info.plist keys */

  printf("\t\techo CFBundleName = \"%s\"; > InfoPlist.strings\n", modulename);
  printf("\t\techo CFBundleShortVersionString = \"1.0\"; >> InfoPlist.strings\n");
  printf("\t\techo CFBundleGetInfoString = \"%s version 1.0, Copyright (c) 2004 __MyCompanyName__.\"; >> InfoPlist.strings\n", modulename);
  printf("\t\techo NSHumanReadableCopyright = \"Copyright (c) 2004 __MyCompanyName__.\"; >> InfoPlist.strings\n");

  printf("\t\tcp InfoPlist.strings %s.framework/Versions/A/Resources/English.lproj\n", modulename);



// Patch to create dynamic libraries under Mac OS X
#ifdef OSX
        
        change_install_names(true);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).        
        printf("\t\t$(CC) $(LDFLAGS) -dynamiclib -W1,-single_module -compatibility_version 1 -current_version 1 -install_name \"@executable_path/../Frameworks/%s.framework/Versions/A/%s\" -seg1addr 0xb0000000 $(OBJS) $(OBJDEP) `wx-config --libs` -o $(PROGRAM).framework/Versions/A/$(PROGRAM) $(VENDORLIBS)\n", modulename, modulename);
        
        change_install_names(false);
        
        
  printf("\t\techo \\#!/bin/sh > mkLinks.sh\n");
  printf("\t\techo cd %s.framework/Versions >> mkLinks.sh\n", modulename);
  printf("\t\techo ln -sf A Current >> mkLinks.sh\n");
  printf("\t\techo cd .. >> mkLinks.sh\n");
  printf("\t\techo ln -sf Versions/Current/Resources Resources >> mkLinks.sh\n");
  printf("\t\techo ln -sf Versions/Current/%s %s >> mkLinks.sh\n", modulename, modulename);
  printf("\t\tchmod +x mkLinks.sh\n");
  printf("\t\t./mkLinks.sh");
  printf("\t\trm mkLinks.sh\n");


#undef UNIX
#endif
#ifdef UNIX
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -shared -Wl,-soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) $(VENDORLIBS)\n");
#endif
#ifdef OSX
#define UNIX
#endif

  printf("\t\t-rm -R $(prefix)/Library/Frameworks/%s.framework\n", modulename);
  printf("\t\tcp -Rf $(PROGRAM).framework $(prefix)/Library/Frameworks\n");
#endif
#ifdef __WATCOMC__
  fprintf(stderr, "Warning: Creating a so library under Windows is not possible with Watcom !!\n");
#endif
}
/*...e*/

/*...svoid write_framework_Target\40\char\42\ modulename\41\:0:*/
void write_framework_Target(char* modulename) {
#ifdef UNIX
  printf("PROGRAM=%s\n", modulename);
  printf("MAJOR=0\n");
  printf("MINOR=0\n");
  printf("MICRO=1\n");
  printf("\n%s.framework: $(OBJS)\n", modulename);

// Create the  directory structure

  printf("\t\t-rm -R %s.framework\n", modulename);
  printf("\t\tmkdir -p %s.framework/Versions/A/Resources\n", modulename);

  printf("\t\techo \\<?xml version=\"1.0\" encoding=\"UTF-8\"?\\> > Info.plist\n");
  printf("\t\techo \\<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\"\\> >> Info.plist\n");
  printf("\t\techo \\<plist version=\"1.0\"\\> >> Info.plist\n");
  printf("\t\techo \\<dict\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>CFBundleDevelopmentRegion\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>English\\</string\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>CFBundleExecutable\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>%s\\</string\\> >> Info.plist\n", modulename);
  printf("\t\techo      \\<key\\>CFBundleIconFile\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>\\</string\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>CFBundleIdentifier\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>com.apple.%sframework\\</string\\> >> Info.plist\n", modulename);
  printf("\t\techo      \\<key\\>CFBundleInfoDictionaryVersion\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>6.0\\</string\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>CFBundlePackageType\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>FMWK\\</string\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>CFBundleSignature\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>????\\</string\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>CFBundleVersion\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>1.0\\</string\\> >> Info.plist\n");
  printf("\t\techo      \\<key\\>NSPrincipalClass\\</key\\> >> Info.plist\n");
  printf("\t\techo      \\<string\\>\\</string\\> >> Info.plist\n");
  printf("\t\techo \\</dict\\> >> Info.plist\n");
  printf("\t\techo \\</plist\\> >> Info.plist\n");

  printf("\t\tcp Info.plist %s.framework/Versions/A/Resources\n", modulename);

  printf("\t\tmkdir -p %s.framework/Versions/A/Resources/English.lproj\n", modulename);

/* Localized versions of Info.plist keys */

  printf("\t\techo CFBundleName = \"%s\"; > InfoPlist.strings\n", modulename);
  printf("\t\techo CFBundleShortVersionString = \"1.0\"; >> InfoPlist.strings\n");
  printf("\t\techo CFBundleGetInfoString = \"%s version 1.0, Copyright (c) 2004 __MyCompanyName__.\"; >> InfoPlist.strings\n", modulename);
  printf("\t\techo NSHumanReadableCopyright = \"Copyright (c) 2004 __MyCompanyName__.\"; >> InfoPlist.strings\n");

  printf("\t\tcp InfoPlist.strings %s.framework/Versions/A/Resources/English.lproj\n", modulename);



// Patch to create dynamic libraries under Mac OS X
#ifdef OSX
        
        change_install_names(true);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).        
        printf("\t\t$(CC) $(LDFLAGS) -dynamiclib -W1,-single_module -compatibility_version 1 -current_version 1 -install_name \"@executable_path/../Frameworks/%s.framework/Versions/A/%s\" -seg1addr 0xb0000000 $(OBJS) $(OBJDEP) -o $(PROGRAM).framework/Versions/A/$(PROGRAM) $(VENDORLIBS)\n", modulename, modulename);
        
        change_install_names(false);
        
        
  printf("\t\techo \\#!/bin/sh > mkLinks.sh\n");
  printf("\t\techo cd %s.framework/Versions >> mkLinks.sh\n", modulename);
  printf("\t\techo ln -sf A Current >> mkLinks.sh\n");
  printf("\t\techo cd .. >> mkLinks.sh\n");
  printf("\t\techo ln -sf Versions/Current/Resources Resources >> mkLinks.sh\n");
  printf("\t\techo ln -sf Versions/Current/%s %s >> mkLinks.sh\n", modulename, modulename);
  printf("\t\tchmod +x mkLinks.sh\n");
  printf("\t\t./mkLinks.sh");
  printf("\t\trm mkLinks.sh\n");


#undef UNIX
#endif
#ifdef UNIX
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -shared -Wl,-soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) $(VENDORLIBS)\n");
#endif
#ifdef OSX
#define UNIX
#endif

  printf("\t\t-rm -R $(prefix)/Library/Frameworks/%s.framework\n", modulename);
  printf("\t\tcp -Rf $(PROGRAM).framework $(prefix)/Library/Frameworks\n");
#endif
#ifdef __WATCOMC__
  fprintf(stderr, "Warning: Creating a so library under Windows is not possible with Watcom !!\n");
#endif
}
/*...e*/

/*...swrite_soPlugin_Target\40\char\42\ modulename\41\ create a UNIX shared library:0:*/
void write_soPlugin_Target(char* modulename) {
#ifdef UNIX
  printf("PROGRAM=%s\n", modulename);
  printf("MAJOR=0\n");
  printf("MINOR=0\n");
  printf("MICRO=1\n");
  printf("\n%s: $(OBJS)\n", modulename);

#ifdef OSX
        
        change_install_names(true);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
        printf("\t\t$(CC) $(LDFLAGS) -dynamic -bundle -WL,soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) $(VENDORLIBS)\n");
        
        change_install_names(false);
        
#endif

#ifndef OSX
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -shared -Wl,-soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) $(VENDORLIBS)\n");
#endif

  printf("\n");
  printf("install:\n");
  printf("\t\t$(INSTALL) $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(plugindir)\n");
  printf("\t\techo cd $(plugindir) >mklink.sh\n");
  printf("\t\techo ln -sf $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(PROGRAM).$(MAJOR) >>mklink.sh\n");
  printf("\t\techo ln -sf $(PROGRAM).$(MAJOR) $(PROGRAM) >>mklink.sh\n");
  printf("\t\tchmod +x mklink.sh\n");
  printf("\t\t./mklink.sh\n");
  printf("\t\trm mklink.sh\n");

  printf("\n");
  printf("install-strip: install\n");
  printf("\t\t$(STRIP) $(plugindir)/$(PROGRAM).$(MAJOR).$(MINOR).$(MICRO)\n");
#endif
#ifdef __WATCOMC__
  fprintf(stderr, "Warning: Creating a so library under Windows is not possible with Watcom !!\n");
#endif
}
/*...e*/

/*...swrite_wx_soPlugin_Target\40\char\42\ modulename\41\ create a UNIX shared library:0:*/
void write_wx_soPlugin_Target(char* modulename) {
#ifdef UNIX
  printf("PROGRAM=%s\n", modulename);
  printf("MAJOR=0\n");
  printf("MINOR=0\n");
  printf("MICRO=1\n");
  printf("\n%s: $(OBJS)\n", modulename);

#ifdef OSX
        
        change_install_names(true);
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
        printf("\t\t$(CC) $(LDFLAGS) -dynamic -bundle -WL,soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(VENDORLIBS)\n");
        
        change_install_names(false);
        
#endif

#ifndef OSX
//\todo Rewrite to be more convient to make system (begun with LDFLAGS).
  printf("\t\t$(CC) $(LDFLAGS) -shared -Wl,-soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(VENDORLIBS)\n");
#endif

  printf("\n");
  printf("install:\n");
  printf("\t\t$(INSTALL) $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(plugindir)\n");
  printf("\t\techo cd $(plugindir) >mklink.sh\n");
  printf("\t\techo ln -sf $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(PROGRAM).$(MAJOR) >>mklink.sh\n");
  printf("\t\techo ln -sf $(PROGRAM).$(MAJOR) $(PROGRAM) >>mklink.sh\n");
  printf("\t\tchmod +x mklink.sh\n");
  printf("\t\t./mklink.sh\n");
  printf("\t\trm mklink.sh\n");

  printf("\n");
  printf("install-strip: install\n");
  printf("\t\t$(STRIP) $(plugindir)/$(PROGRAM).$(MAJOR).$(MINOR).$(MICRO)\n");

#endif
#ifdef __WATCOMC__
  fprintf(stderr, "Warning: Creating a so library under Windows is not possible with Watcom !!\n");
#endif
}
/*...e*/

//------------------------------ Main code ------------------------------
/*...svoid ShowHelp\40\\41\:0:*/
void ShowHelp(int argc, char *argv[])
{
  fprintf(stderr, "MKMK by Luis Crespo (lcrespo@ergos.es or lcrespo@dccp.dret.ub.es).\n");
  fprintf(stderr, "Published at http://www.cubic.org/~submissive/sourcerer/mkmk.htm\n\n");

  fprintf(stderr, "Enhanced by Lothar Behrens (lothar.behrens@lollisoft.de)\n\n");

  fprintf(stderr, "MKMK: makefile generator $Revision: 1.114.2.5 $\n");
  fprintf(stderr, "Usage: MKMK lib|exe|dll|so modulname includepath,[includepath,...] file1 [file2 file3...]\n");

  fprintf(stderr, "Your parameters are: ");
  for (int i = 0; i < argc-1; i++) fprintf(stderr, "%s ", argv[i]);
  fprintf(stderr, "%s\n", argv[argc-1]);
}
/*...e*/
/*...svoid WriteHeader\40\FILE \42\f\44\ char \42\ExeName\41\:0:*/
void WriteHeader(FILE *f, char *ExeName)
{
#ifdef WATCOM_MAKE
  printf("#Make file automatically generated by MKMK\n\n");

  printf("!include $(%%DEVROOT)\\projects\\cpp\\make\\STD_MAKE\n");
  printf("!include STD_MAKE\n");

  printf(".BEFORE\n");
  printf("!include MAKE_BEFORE\n");


  printf("main: %s\n\n",ExeName);
  printf("clean: .SYMBOLIC\n");
  printf("  del *.err\n");
  printf("  del *.obj\n");
  printf("  del %s\n\n",ExeName);
  printf("#Compiler and linker definitions (suggestion):\n");
#endif
#ifdef UNIX
  printf("#Make file automatically generated by MKMK\n\n");

  printf("!include $(%%DEVROOT)/Projects/CPP/make/STD_MAKE\n");

  printf("main: %s\n\n",ExeName);
  printf("clean:\n");
  printf("\t\tdel *.err\n");
  printf("\t\tdel *.obj\n");
  printf("\t\tdel %s\n\n",ExeName);
  printf("#Compiler and linker definitions (suggestion):\n");
#endif
#ifdef WATCOM_MAKE
  printf("CC       = WPP386\n");
  printf("C_OPS    = $(STD_C_OPS) /Oneatx /zp4 /5 /fp5 /D1 /D3 /W1 /MF /SG /HW /ZQ\n");

/*...sbla:0:*/
#ifdef bla
  printf("STD_INCL = -i=.;Q:\\develop\\Tools\\WATCOM\\h;&\n");
  printf("Q:\\develop\\Tools\\WATCOM\\h\\nt;&\n");
  printf("Q:\\develop\\projects\\cpp\\interfaces;&\n");
  printf("Q:\\develop\\projects\\cpp\\include;&\n");
  printf("Q:\\develop\\projects\\dll\\include;&\n");
  printf("Q:\\develop\\projects\\lib\\include\n");
#endif
/*...e*/

  printf("LINK     = WLINK\n");
  printf("WLIB     = WLIB\n");
  printf("LIB_OPS  = -b -c -n -q -p=512\n");
  printf("L_OPS_EXE    = D all SYS nt op m op maxe=25 op q\n\n");
  printf("L_OPS_DLL    = D all SYS nt_dll op m op maxe=25 op q\n\n");

  printf("L_OPS_LIB    = D all SYS nt_lib op m op maxe=25 op q\n\n");
#else
  printf("CC       = your favorite C/CPP compiler\n");
  printf("C_OPS    = your compiler options\n");
  printf("LINK     = your favorite linker\n");
  printf("L_OPS    = your linker options\n\n");
#endif
  printf("#File dependencies:\n\n");
}
/*...e*/
/*...svoid ListFiles\40\FILE \42\f\44\ char \42\Line\44\ TDepList \42\l\44\ bool IsObj\61\false\41\:0:*/
void ListFiles(FILE *f, char *Line, TDepList *l, bool IsObj=false)
{
  char s[120],FName[PATH_MAX];
  int i;
  TDepItem *d;

  for (i=0; i<l->Count; i++)
  {
    d=(TDepItem*)(*l)[i];
    strcpy(s," ");
    strcat(s,d->Path);
    if (IsObj) ObjExt(d->Name,FName,sizeof(FName));
    else strcpy(FName,d->Name);
    strcat(s,FName);

    if (strlen(s)+strlen(Line)>74)
    {
      printf("%s %c\n",Line,MoreChar);
      sprintf(Line,"\t\t%s",s);
    }
    else {
//      if (i!=0) strcat(Line,", ");
        strcat(Line,s);
    }
  }
  printf("%s\n",Line);
}
/*...e*/
/*...svoid ListFilesWithComma\40\FILE \42\f\44\ char \42\Line\44\ TDepList \42\l\44\ bool IsObj\61\false\41\:0:*/
void ListFilesWithComma(FILE *f, char *Line, TDepList *l, bool IsObj=false)
{
  char s[120],FName[PATH_MAX];
  int i;
  TDepItem *d;

  for (i=0; i<l->Count; i++)
  {
    d=(TDepItem*)(*l)[i];
    strcpy(s," ");
    strcat(s,d->Path);
    if (IsObj) ObjExt(d->Name,FName,sizeof(FName));
    else strcpy(FName,d->Name);
    strcat(s,FName);

    /* Append ',' if i is less than l->Count */
    /* Because of problems in watcom linking */

    if (i < l->Count-1) strcat(s, ",");

    if (strlen(s)+strlen(Line)>74)
    {
      printf("%s %c\n",Line,MoreChar);
      sprintf(Line,"\t\t%s",s);
    }
    else {
//      if (i!=0) strcat(Line,", ");
        strcat(Line,s);
    }
  }
  printf("%s\n",Line);
}
/*...e*/
/*...svoid WriteDep\40\FILE \42\f\44\ char \42\Name\44\ TIncludeParser \42\p\41\:0:*/
int depCount = 0;

/*...svoid replace\40\char\42\ to\44\ char\42\ match\44\ char\42\ replace\41\:0:*/
void replace(char* to, const char* match, const char* replace) {
        char rep[800] = "";
        char repl[800] = "";
        char* t;
        strcpy(rep, to);

        t = strtok(rep, match);

        while (t != NULL) {
                strcat(repl, t);
                strcat(repl, replace);

                t = strtok(NULL, match);
        }

        repl[strlen(repl)-2] = 0;

        to[0] = 0;

        strcpy(to, repl);
}
/*...e*/

void WriteDep(FILE *f, char *Name, TIncludeParser *p)
{
/// Todo: Reimplement without hardcoded sizes. There was a buffer overflow !
  char ObjName[800] = "";
  char ObjNameC[800] = "";
  char NameC[800] = "";
  char SExt[100] = "";
  char Line[800] = "";

  int  CPPFlag = 0;

  char Compiler[100] = "";

  int pos = strlen(Name);

  strcpy(NameC, Name);

  replace(NameC, "/", "\\\\");

  while ((pos > 0) && (Name[pos] != '.')) pos--;
  strcpy(SExt, &Name[pos]);

  for(int c = 0; c < strlen(SExt); c++) SExt[c] = toupper(SExt[c]);

  // Lex and yacc files are a pre step before creating the makefile. At the time mkmk scans for C and CPP files, it doesn't find
  // these files generated from LEX and YACC. Thus these *.Y and *.L files must be passed before all other source files.
  // Also usable would be setting new target types for these files.
  //
  // Either calling mkmk with a separate set of files for lex and yacc files specifying the correct tardet or implementing the suggested
  // two pass mechanism are workable. I choose the first to get a solution for this earlier.

  if (strcmp(SExt, ".L") == 0) {
        CPPFlag = 0;
        strcpy(Compiler, "$(LEX)");
  }

  if (strcmp(SExt, ".Y") == 0) {
        CPPFlag = 0;
        strcpy(Compiler, "$(YACC)");
  }

  if (strcmp(SExt, ".C") == 0) {
        CPPFlag = 0;
        strcpy(Compiler, "$(CC)");
  }

  if (strcmp(SExt, ".CPP") == 0) {
        CPPFlag = 1;
        strcpy(Compiler, "$(CPP)");
  }

  if (strcmp(SExt, ".CC") == 0) {
        CPPFlag = 1;
        strcpy(Compiler, "$(CPP)");
  }

  if ((targettype == IDL_TARGET) || (targettype == LEX_TARGET) || (targettype == YACC_TARGET)) {
        ObjExt(Name,ObjName,sizeof(ObjName));
        if (targettype == LEX_TARGET) {
                sprintf(Line, "lex.yy.c: %s",Name);
        } else if (targettype == IDL_TARGET) {
                sprintf(Line, "%s.hh: %s",ObjName,Name);
          } else {
                sprintf(Line, "%s.output: %s",ObjName,Name);
        }
  } else {
      ObjExt(Name,ObjName,sizeof(ObjName));
      sprintf(Line, "%s: makefile %s",ObjName,Name);
  }
/*
  fprintf(stderr, "Name is       '%s'.\n", Name);
  fprintf(stderr, "Objectname is '%s'.\n", ObjName);
*/
  strcpy(ObjNameC, ObjName);

  replace(ObjNameC, "/", "\\\\");

  ListFiles(f,Line,&p->l);
  int len;

  switch (targettype) {
        case IDL_TARGET:
                printf("\t\t@(dir=omniORB4; $(CreateDir))\n", Compiler, Name);
                printf("\t\t$(OMNIORB_IDL) -v -ComniORB4 $<\n", Compiler, Name);
                break;
        case LEX_TARGET:
                printf("\t\t@%s -i %s\n\n", Compiler, Name);
                break;
        case YACC_TARGET:
                printf("\t\t@%s -d -v %s\n\n", Compiler, Name);
                break;
        case LIB_TARGET:
                printf("\t\t@%s $(C_LIBOPS) $(MOD_INCL) %s\n\n", Compiler, Name);
                break;
        case DLL_TARGET:
        case DLL_TARGET_CROSS:
        case PLUGIN_TARGET:
        case WXPLUGIN_TARGET:
        case TVISION_DLL:
                printf("\t\t@echo Build %s\n", NameC);

                if (CPPFlag == 0) printf("\t\t%s $(C_DLLOPS) $(MOD_INCL) -Fo=%s %s\n", Compiler, ObjNameC, NameC);
                if (CPPFlag == 1) printf("\t\t%s $(CPP_DLLOPS) $(MOD_INCL_CPP) -Fo=%s %s\n", Compiler, ObjName, Name);
                break;
        case EXE_TARGET_MINGW:
                len = strlen(ObjName);
                for (int i = len; i >= 0; i--) {
                    if (ObjName[i] == '.') {
                        ObjName[i] = 0;
                        break;
                    }
                }

                if (strcmp(SExt, ".C") == 0) {
                      CPPFlag = 0;
                      strcpy(Compiler, "$(CCMINGW)");
                }

                if (strcmp(SExt, ".CPP") == 0) {
                      CPPFlag = 1;
                      strcpy(Compiler, "$(CPPMINGW)");
                }

                if (strcmp(SExt, ".CC") == 0) {
                      CPPFlag = 1;
                      strcpy(Compiler, "$(CPPMINGW)");
                }

                                printf("\t\t@echo Build %s\n", NameC);
                if (CPPFlag == 0) printf("\t\t%s -c $(C_MINGW_EXEOPS) $(MOD_INCL_MINGW) -o%s %s\n\n", Compiler, ObjNameC, NameC);
                if (CPPFlag == 1) printf("\t\t%s -c $(CPP_MINGW_EXEOPS) $(MOD_INCL_MINGW_CPP) -o%s.$(OBJ) %s\n\n", Compiler, ObjName, Name);
                break;
        case DLL_TARGET_MINGW:
        case PLUGIN_TARGET_MINGW:
        case WXPLUGIN_TARGET_MINGW:

                if (strcmp(SExt, ".C") == 0) {
                      CPPFlag = 0;
                      strcpy(Compiler, "$(CCMINGW)");
                }

                if (strcmp(SExt, ".CPP") == 0) {
                      CPPFlag = 1;
                      strcpy(Compiler, "$(CPPMINGW)");
                }

                if (strcmp(SExt, ".CC") == 0) {
                      CPPFlag = 1;
                      strcpy(Compiler, "$(CPPMINGW)");
                }


                printf("\t\t@echo Build %s\n", NameC);

                if (CPPFlag == 0) printf("\t\t%s -c $(C_MINGW_DLLOPS) $(MOD_INCL_MINGW) -o%s %s\n", Compiler, ObjNameC, NameC);
                if (CPPFlag == 1) printf("\t\t%s  -c $(CPP_MINGW_DLLOPS) $(MOD_INCL_MINGW_CPP) -o%s %s\n", Compiler, ObjName, Name);
                break;
        case EXE_TARGET:
                len = strlen(ObjName);
                for (int i = len; i >= 0; i--) {
                    if (ObjName[i] == '.') {
                        ObjName[i] = 0;
                        break;
                    }
                }

                printf("\t\t@echo Build %s\n", NameC);
                if (CPPFlag == 0) printf("\t\t%s $(C_EXEOPS) $(MOD_INCL) -Fo=%s %s\n\n", Compiler, ObjNameC, NameC);
                if (CPPFlag == 1) printf("\t\t%s $(CPP_EXEOPS) $(MOD_INCL_CPP) -Fo=%s.$(OBJ) %s\n\n", Compiler, ObjName, Name);
                break;
        case ELF_TARGET:
        case ELF_BUNDLE_TARGET:
                len = strlen(ObjName);
                for (int i = len; i >= 0; i--) {
                    if (ObjName[i] == '.') {
                        ObjName[i] = 0;
                        break;
                    }
                }
                printf("\t\t@echo Build %s\n", NameC);
                printf("\t\t@%s $(C_ELFOPS) $(MOD_INCL) %s -o %s.o\n\n", Compiler, Name, ObjName);
                break;
        case SO_BUNDLE_TARGET:
                len = strlen(ObjName);
                for (int i = len; i >= 0; i--) {
                    if (ObjName[i] == '.') {
                        ObjName[i] = 0;
                        break;
                    }
                }
                printf("\t\t@echo Build %s\n", NameC);
                printf("\t\t@%s -c -fPIC $(C_SOOPS) $(MOD_INCL) %s -o %s.o\n\n", Compiler, Name, ObjName);
                break;
        case SO_TARGET:
        case SOPLUGIN_TARGET:
                {
                                len = strlen(ObjName);
                for (int i = len; i >= 0; i--) {
                    if (ObjName[i] == '.') {
                        ObjName[i] = 0;
                        break;
                    }
                }
                printf("\t\t@echo Build %s\n", NameC);
                printf("\t\t@%s -c -fPIC $(C_SOOPS) $(MOD_INCL) %s -o %s.o\n\n", Compiler, Name, ObjName);
                }
                break;
        case WXSO_TARGET:
        case WXSHARED_TARGET:
        case WXSOPLUGIN_TARGET:
                {
                len = strlen(ObjName);
                for (int i = len; i >= 0; i--) {
                    if (ObjName[i] == '.') {
                        ObjName[i] = 0;
                        break;
                    }
                }
                printf("\t\t@echo Build %s\n", NameC);
                printf("\t\t@%s -c -fPIC $(C_SOOPS) $(MOD_INCL) %s -o %s.o\n\n", Compiler, Name, ObjName);
                }
                break;
    case FRAMEWORK_TARGET:
    case WXFRAMEWORK_TARGET:
                {
                len = strlen(ObjName);
                for (int i = len; i >= 0; i--) {
                    if (ObjName[i] == '.') {
                        ObjName[i] = 0;
                        break;
                    }
                }
                printf("\t\t@echo Build %s\n", NameC);
                printf("\t\t@%s -c $(C_SOOPS) $(MOD_INCL) %s -o %s.o\n\n", Compiler, Name, ObjName);
                }
                break;
    default:
                break;
  }
}
/*...e*/
/*...svoid WriteEnding\40\FILE \42\f\44\ char \42\ExeName\44\ TDepList \42\l\41\:0:*/
void WriteEnding(FILE *f, char *ModuleName, TDepList *l)
{
  char Line[120] = "";

        if ((targettype != LEX_TARGET) && (targettype != YACC_TARGET)) {
                printf("OBJS =");

                ListFiles(f,Line,l,true);
                Line[0] = 0;

                printf("OBJLIST =");
                ListFilesWithComma(f,Line,l,true);
        }
#ifndef UNIX
//  printf("LIBS = $(DEVROOT)\\projects\\lib\\lbhook.lib \n");
#endif

#ifdef WATCOM_MAKE
/*...swrite a wmake makefile:0:*/
  switch (targettype) {
        case DLL_TARGET:
        case DLL_TARGET_CROSS:
                #ifdef VERBOSE
                printf("Making a dll target\n");
                #endif
                printf("%s: $(OBJS) $(LIBS)\n",ModuleName);
                printf("\t\t*$(LINK) $(L_OPS_DLL) name %s file $(OBJS) library $(LIBS)\n",ModuleName);
                break;
        case LIB_TARGET:
                #ifdef VERBOSE
                printf("Making a lib target\n");
                #endif
                printf("%s: $(OBJS) $(LIBS)\n",ModuleName);
                printf("\t\t*$(WLIB) $(LIB_OPS_LIB) %s &\n", ModuleName);
                printf("        $(OBJS)\n");
                break;
        case EXE_TARGET:
                #ifdef VERBOSE
                printf("Making a exe target\n");
                #endif
                printf("%s: $(OBJS) $(LIBS)\n",ModuleName);
                printf("\t\t*$(LINK) $(L_OPS_EXE) name %s ",ModuleName);
                printf("file {$(OBJS)} library {$(LIBS)}\n");

                break;
        default:
                break;
  }
#ifndef UNIX
  printf(".AFTER\n");
  printf("!include MAKE_AFTER\n");
#endif

/*...e*/
#else

  switch (targettype) {
        case LEX_TARGET:
                writeLexTarget(ModuleName);
                write_lex_clean();
                break;
        case YACC_TARGET:
                writeYaccTarget(ModuleName);
                write_yacc_clean();
                break;
        case DLL_TARGET:
        case DLL_TARGET_CROSS:
                writeDllTarget(ModuleName);
                write_clean();
                break;
        case DLL_TARGET_MINGW:
                writeMinGWDllTarget(ModuleName);
                write_clean();
                break;
        case PLUGIN_TARGET_MINGW:
        case WXPLUGIN_TARGET_MINGW:
                writeMinGWPluginTarget(ModuleName);
                write_clean();
                break;
        case TVISION_DLL:
                writeDllTarget(ModuleName);
                write_clean();
                break;
        case TVISION_EXE:
                writeExeTarget(ModuleName);
                write_clean();
                break;
        case PLUGIN_TARGET:
                writePluginTarget(ModuleName);
                write_clean();
                break;
        case WXPLUGIN_TARGET:
                writePluginTarget(ModuleName);
                write_clean();
                break;
        case LIB_TARGET:
                writeLibTarget(ModuleName, l);
                write_clean();
                break;
        case EXE_TARGET:
                writeExeTarget(ModuleName);
                write_clean(ModuleName);
                break;
        case EXE_TARGET_MINGW:
                writeMinGWExeTarget(ModuleName);
                write_clean();
                break;
        case WXELF_TARGET:
                writeExeTarget(ModuleName);
                write_clean(ModuleName);
                break;
        case ELF_TARGET:
                writeExeTarget(ModuleName);
                write_clean(ModuleName);
                break;
        case ELF_BUNDLE_TARGET:
                writeBundleTarget(ModuleName);
                write_clean(ModuleName);
                break;
        case SO_TARGET:
                write_so_Target(ModuleName);
                write_clean();
                break;
        case SO_BUNDLE_TARGET:
                write_so_bundleTarget(ModuleName);
                write_clean();
                break;
        case WXSHARED_TARGET:
                write_wx_shared_Target(ModuleName);
                write_clean();
                break;
        case FRAMEWORK_TARGET:
                write_framework_Target(ModuleName);
                write_clean();
                break;
        case WXFRAMEWORK_TARGET:
                write_wx_framework_Target(ModuleName);
                write_clean();
                break;
        case WXSO_TARGET:
                write_wx_so_Target(ModuleName);
                write_clean();
                break;
        case SOPLUGIN_TARGET:
                write_soPlugin_Target(ModuleName);
                write_clean();
                break;
        case WXSOPLUGIN_TARGET:
                write_wx_soPlugin_Target(ModuleName);
                write_clean();
                break;
        default:
                break;
  }

#endif
}
/*...e*/
/*...svoid DoDep\40\FILE \42\f\44\ TDepItem \42\d\41\:0:*/
void DoDep(FILE *f, TDepItem *d, char** iPathList, int count)
{
  TIncludeParser p;
  char FileName[256];

  strcpy(FileName,d->Path);
  strcat(FileName,d->Name);

  p.setIncludes(iPathList, count);

  p.Parse(FileName);

  char fullName[1000] = "";

  strcpy(fullName, d->Path);
  strcat(fullName, d->Name);
  WriteDep(f,fullName,&p);
#ifdef VERBOSE
  printf("Warning: Using hardcoded char array.\n");
#endif
//  delete[] fullName;
}
/*...e*/
/*...e*/

/*...svoid main\40\int argc\44\ char \42\argv\91\\93\\41\:0:*/
int main(int argc, char *argv[])
{
  FILE *f;
  TDepList Sources;
  int i;
  if (argc<4)
  {
    ShowHelp(argc, argv);
#ifdef UNIX
    return 0;
#endif
#ifdef __WATCOMC__
    return 0;
#endif
  }
/*...sbla:0:*/
/*  f=fopen("makefile","wt");
  if (!f)
  {
          fputs("ERROR: could not create makefile",stderr);
    return;
  }
*/
/*...e*/
/*...sdetermine target type:0:*/
  char *target = strdup(argv[1]);
  targetname = strdup(argv[2]);
  char *target_ext = NULL;

  for(int c = 0; c < strlen(target); c++) target[c] = toupper(target[c]);

  if (strcmp(target, "-") == 0) {
        targettype = ELF_TARGET;
        target_ext = strdup("");
  }

  if (strcmp(target, "TVISION_DLL") == 0) {
        targettype = TVISION_DLL;
        target_ext = strdup(".dll");
  }

  if (strcmp(target, "TVISION_USR_DLL") == 0) {
        targettype = TVISION_DLL;
        target_ext = strdup(".dll");
  }

  if (strcmp(target, "TVISION_EXE") == 0) {
        targettype = TVISION_EXE;
        target_ext = strdup(".exe");
  }

  if (strcmp(target, "ELF") == 0) {
        targettype = ELF_TARGET;
        target_ext = strdup("");
  }

  if (strcmp(target, "BUNDLE") == 0) {
        targettype = ELF_BUNDLE_TARGET;
        target_ext = strdup("");
  }

  if (strcmp(target, "SO") == 0) {
        targettype = SO_TARGET;
        target_ext = strdup(".so");
  }

  if (strcmp(target, "WXSO") == 0) {
        targettype = WXSO_TARGET;
        target_ext = strdup(".so");
  }

  if (strcmp(target, "WXSHARED") == 0) {
        targettype = WXSHARED_TARGET;
        target_ext = strdup(".so");
  }

  if (strcmp(target, "FRAMEWORK") == 0) {
        targettype = FRAMEWORK_TARGET;
        target_ext = strdup("");
  }

  if (strcmp(target, "WXFRAMEWORK") == 0) {
        targettype = WXFRAMEWORK_TARGET;
        target_ext = strdup("");
  }

  if (strcmp(target, "LIB") == 0) {
        targettype = LIB_TARGET;
        target_ext = strdup(".lib");
  }

  if (strcmp(target, "DLL") == 0) {
        targettype = DLL_TARGET;
        target_ext = strdup(".dll");
  }

  if (strcmp(target, "PLUGIN") == 0) {
        targettype = PLUGIN_TARGET;
        target_ext = strdup(".dll");
  }

  if (strcmp(target, "WXPLUGIN") == 0) {
        targettype = WXPLUGIN_TARGET;
        target_ext = strdup(".dll");
  }

  if (strcmp(target, "SOPLUGIN") == 0) {
        targettype = SOPLUGIN_TARGET;
        target_ext = strdup(".so");
  }

  if (strcmp(target, "SOBUNDLE") == 0) {
        targettype = SO_BUNDLE_TARGET;
        target_ext = strdup(".so");
  }

  if (strcmp(target, "WXSOPLUGIN") == 0) {
        targettype = WXSOPLUGIN_TARGET;
        target_ext = strdup(".so");
  }

  if (strcmp(target, "EXE") == 0) {
        targettype = EXE_TARGET;
        target_ext = strdup(".exe");
  }

  if (strcmp(target, "LEX") == 0) {
        targettype = LEX_TARGET;
        target_ext = strdup("");
  }

  if (strcmp(target, "YACC") == 0) {
        targettype = YACC_TARGET;
        target_ext = strdup("");
  }

// These are the new cross compiling targets
// This is absolutely beta !

  if (strcmp(target, "DLL_CROSS") == 0) {
        targettype = DLL_TARGET_CROSS;
        target_ext = strdup(".dll");
  }

// The new support for mingw compiler

  if (strcmp(target, "EXE_TARGET_MINGW") == 0) {
        targettype = EXE_TARGET_MINGW;
        target_ext = strdup(".exe");
  }

  if (strcmp(target, "DLL_TARGET_MINGW") == 0) {
        targettype = DLL_TARGET_MINGW;
        target_ext = strdup(".dll");
  }

  if (strcmp(target, "PLUGIN_TARGET_MINGW") == 0) {
        targettype = PLUGIN_TARGET_MINGW;
        target_ext = strdup(".dll");
  }

  if (strcmp(target, "WXPLUGIN_TARGET_MINGW") == 0) {
        targettype = WXPLUGIN_TARGET_MINGW;
        target_ext = strdup(".dll");
  }



  if (strchr(targetname, '.') == NULL) targetname = strcat(targetname, target_ext);
/*...e*/

  //  WriteHeader(f,targetname);
  char *inclPaths = strdup(argv[3]);

  //const char split_char, char *string, char ***array
  int count = split(',', inclPaths, &IncPathList);

/*...sVERBOSE:0:*/
#ifdef VERBOSE
  for (i = 0; i < count; i++) {
        printf("Path: %s\n", IncPathList[i]);
  }
#endif
/*...e*/
  char** copyIPathList = NULL;

  copyIPathList = new char*[count];


  for (i = 0; i < count; i++) {
        char temp[1000] = "";
        char pc[2] = "";
        sprintf(pc, "%c", PathChar);

        strcpy(temp, IncPathList[i]);
        if(temp[strlen(temp)] != PathChar) strcat(temp, pc);

        //printf("Prepared include directory %s\n", temp);
        copyIPathList[i] = strdup(temp);
  }
/*...sVERBOSE:0:*/
#ifdef VERBOSE
  for (i = 0; i < count; i++) {
        printf("Have copied this entry: %s\n", copyIPathList[i]);
  }
#endif
/*...e*/

  for (i=4; i<argc; i++) Sources.AddMask(argv[i]);

  if (Sources.Count == 0) fprintf(stderr, "ERROR: No source files to write!\n");

  // Here the link information file should be created



  switch (targettype) {
    case EXE_TARGET_MINGW:
    case DLL_TARGET_MINGW:
    case PLUGIN_TARGET_MINGW:
    case WXPLUGIN_TARGET_MINGW:
    case DLL_TARGET:
    case DLL_TARGET_CROSS:
    case LIB_TARGET:
    case WXPLUGIN_TARGET:
    case PLUGIN_TARGET:
    case EXE_TARGET:
    case TVISION_EXE:
    case TVISION_DLL:
      printf("%s.lnk: makefile $(OBJS)\n", targetname);
      printf("\t\techo NAME %s > $@\n", targetname);

      for (i=0; i<Sources.Count; i++) {

        char FileName[256];
        char ObjName[256];

        strcpy(FileName, ((TDepItem*)Sources[i])->Path);
        strcat(FileName, ((TDepItem*)Sources[i])->Name);

        ObjExt(FileName,ObjName,sizeof(ObjName));

        printf("\t\techo FIL %s >> $@\n", ObjName);

      }
      break;
    default:
      break;
  }

  fprintf(stderr, "Creating dependency list.\n");
  for (i=0; i<Sources.Count; i++) DoDep(f,(TDepItem*)Sources[i], copyIPathList, count);
  WriteEnding(f,targetname,&Sources);
//  fclose(f);
  return 0;
}
/*...e*/
