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
 * $Revision: 1.66 $
 * $Name:  $
 * $Id: mkmk.cpp,v 1.66 2005/08/04 18:06:45 lollisoft Exp $
 *
 * $Log: mkmk.cpp,v $
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
  char Name[80];
  char Path[80];
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
  char Path[80] = "";
  char Name[80] = "";

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
    char FilePath[80];
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
  char Path[255] = "";
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
        } else { fprintf(stderr, "Error: No standard path has this file, and this rule does not match for %s\n", IncName); }
  }
/*...e*/

  if (l.Search(realfile)) {
//      printf("File %s has already been added!\n", realfile);
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
        printf("Add the include %s\n", p1);
        #endif
/*...e*/
        AddInclude(p1);
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
    fprintf(stderr,"TIncludeParser::Parser() WARNING: %s could not be opened\n",FileName);
    return false;
  }
  else return true;
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
  int l;

  memset(ObjName,0,Len);
  l=strlen(s)-1;
  if (l<1) return;
  while (l>=0 && s[l]!='.') l--;
  if (l>=0 && l<Len) memcpy(ObjName,s,l+1);
  strcat(ObjName,"$(OBJ)");
}
/*...e*/

/*...swriteExeTarget\40\char\42\ modulename\41\:0:*/
void writeBundleTarget(char* modulename) {
#ifdef OSX
#undef UNIX
  fprintf(stderr, "Writing osx executable target\n");
  printf("PROGRAM=%s\n", modulename);
  printf("\n%s: $(OBJS)\n", modulename);
  printf("\t\t$(CC) $(L_OPS) %s $(OBJS) $(OBJDEP) $(LIBS) -bind_at_load -lc $(VENDORLIBS)\n",modulename);
  printf("\t\t$(CP) $(PROGRAM) $(HOME)/bin\n");

  // Write Mac OS X Bundle
  printf("\t\t/Developer/Tools/Rez -d __DARWIN__ -t APPL -d __WXMAC__ -i . -d WXUSINGDLL -i $(HOME)/wxMac-2.6.1/samples -i $(HOME)/wxMac-2.6.1/include -o %s Carbon.r sample.r\n", modulename);
  printf("\t\t/Developer/Tools/SetFile -a C %s\n", modulename);
  printf("\t\t-$(HOME)/wxMac-2.6.1/change-install-names $(HOME)/wxMac-2.6.1/lib /usr/local %s\n", modulename);
  printf("\t\trm -Rf %s.app\n", modulename);
  printf("\t\tmkdir -p %s.app\n", modulename);
  printf("\t\tmkdir -p %s.app/Contents\n", modulename);
  printf("\t\tmkdir -p %s.app/Contents/MacOS\n", modulename);
  printf("\t\tmkdir -p %s.app/Contents/Resources\n", modulename);
  printf("\t\tset -e \"s/IDENTIFIER/`echo . | sed -e 's,\\.\\./,,g' | sed -e 's,/,.,g'`/\" -e \"s/EXECUTABLE/%s/\" -e \"s/VERSION/2.6.1/\" $(HOME)/wxMac-2.6.1/src/mac/carbon/wxmac.icns %s.app/Contents/Resources/wxmac.icns\n", modulename, modulename);
  printf("\t\tsed -e \"s/IDENTIFIER/`echo . | sed -e 's,\\.\\./,,g' | sed -e 's,/,.,g'`/\" -e \"s/EXECUTABLE/%s/\" -e \"s/VERSION/2.6.1/\" $(HOME)/wxMac-2.6.1/src/mac/carbon/Info.plist.in >%s.app/Contents/Info.plist\n", modulename, modulename);
  printf("\t\techo -n \"APPL????\" >%s.app/Contents/PkgInfo\n", modulename);
  printf("\t\tln -f %s %s.app/Contents/MacOS/%s\n", modulename, modulename, modulename);
//  printf("\t\t\n", modulename);
#endif

#ifdef UNIX
  fprintf(stderr, "Writing linux executable target\n");
  printf("PROGRAM=%s\n", modulename);
  printf("\n%s: $(OBJS)\n", modulename);
  printf("\t\t$(CC) $(L_OPS) %s $(OBJS) $(OBJDEP) $(LIBS) -lc $(VENDORLIBS)\n",modulename);
  printf("\t\t$(CP) $(PROGRAM) $(HOME)/bin\n");
#endif

#ifdef OSX
#define UNIX
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
  printf("\t\t$(CC) $(L_OPS) %s $(OBJS) $(OBJDEP) $(LIBS) -bind_at_load -lc $(VENDORLIBS)\n",modulename);
  printf("\t\t$(CP) $(PROGRAM) $(HOME)/bin\n");
#endif

#ifdef UNIX
  fprintf(stderr, "Writing linux executable target\n");
  printf("PROGRAM=%s\n", modulename);
  printf("\n%s: $(OBJS)\n", modulename);
  printf("\t\t$(CC) $(L_OPS) %s $(OBJS) $(OBJDEP) $(LIBS) -lc $(VENDORLIBS)\n",modulename);
  printf("\t\t$(CP) $(PROGRAM) $(HOME)/bin\n");
#endif

#ifdef OSX
#define UNIX
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
/*...swriteDllTarget\40\char\42\ modulename\41\:0:*/
void writeDllTarget(char* modulename) {
#ifdef UNIX
  printf("\n%s: $(OBJS)\n", modulename);
  printf("\t\t$(CC) $(L_OPS) %s $(OBJS) $(OBJDEP)\n",modulename);
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
  printf("\t\t@$(CP) $(PROGRAM).sym $(EXEDIR) > null\n");
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
}
/*...e*/
/*...swritePluginTarget\40\char\42\ modulename\41\:0:*/
void writePluginTarget(char* modulename) {
#ifdef UNIX
  printf("\n%s: $(OBJS)\n", modulename);
  printf("\t\t$(CC) $(L_OPS) %s $(OBJS) $(OBJDEP)\n",modulename);
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
  printf("\t\t@$(CP) $(PROGRAM).sym $(EXEDIR) > null\n");
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
#ifdef UNIX
//  printf("\n%s: $(OBJS)\n", modulename);
//  printf("\t\t$(CC) $(L_OPS) %s $(OBJS) $(OBJDEP)\n",modulename);
#endif
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

/*...swrite_clean\40\char\42\ modulename \61\ NULL\41\:0:*/
void write_clean(char* modulename = NULL) {
#ifdef __WATCOMC__
    // Write the normal clean rule
    printf("clean:\n");
    printf("\t\t-@rm *.exp\n");
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
    printf("\t\t-@rm *.bak\n");
    printf("\t\t-@rm *.idb\n");
    printf("\t\t-@rm *.pch\n");
    printf("\t\t-@rm *.pdb\n");
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
  printf("\t\t$(CC) -dynamiclib -WL,soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) -lc $(VENDORLIBS)\n");
#undef UNIX  
#endif
#ifdef UNIX
  printf("\t\t$(CC) -shared -WL,soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) -lc $(VENDORLIBS)\n");
#endif

#ifdef OSX
#define UNIX
#endif

  printf("\t\tcp $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(HOME)/lib\n");
  printf("\t\tln -sf $(HOME)/lib/$(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(HOME)/lib/$(PROGRAM).$(MAJOR)\n");
  printf("\t\tln -sf $(HOME)/lib/$(PROGRAM).$(MAJOR) $(HOME)/lib/$(PROGRAM)\n");
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
  printf("\t\t$(CC) -dynamiclib -WL,soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) `wx-config --libs` $(OBJS) $(OBJDEP) $(LIBS) -lc $(VENDORLIBS)\n");
#undef UNIX  
#endif
#ifdef UNIX
  printf("\t\t$(CC) -shared -WL,soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) `wx-config --libs` $(OBJS) $(OBJDEP) $(LIBS) -lc $(VENDORLIBS)\n");
#endif
#ifdef OSX
#define UNIX
#endif

  printf("\t\tcp $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(HOME)/lib\n");
  printf("\t\tln -sf $(HOME)/lib/$(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(HOME)/lib/$(PROGRAM).$(MAJOR)\n");
  printf("\t\tln -sf $(HOME)/lib/$(PROGRAM).$(MAJOR) $(HOME)/lib/$(PROGRAM)\n");
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
  printf("\t\t$(CC) -dynamiclib -WL,soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) -lc $(VENDORLIBS)\n");
#endif

#ifndef OSX
  printf("\t\t$(CC) -shared -WL,soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(LIBS) -lc $(VENDORLIBS)\n");
#endif

  printf("\t\tcp $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(HOME)/plugins\n");
  printf("\t\tln -sf $(HOME)/plugins/$(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(HOME)/plugins/$(PROGRAM).$(MAJOR)\n");
  printf("\t\tln -sf $(HOME)/plugins/$(PROGRAM).$(MAJOR) $(HOME)/plugins/$(PROGRAM)\n");
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
  printf("\t\t$(CC) -dynamiclib -WL,soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(L_OPS) -lc $(VENDORLIBS)\n");
#endif

#ifndef OSX
  printf("\t\t$(CC) -shared -WL,soname,$(PROGRAM).$(MAJOR) -o $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) $(L_OPS) -lc $(VENDORLIBS)\n");
#endif

  printf("\t\tcp $(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(HOME)/plugins\n");
  printf("\t\tln -sf $(HOME)/plugins/$(PROGRAM).$(MAJOR).$(MINOR).$(MICRO) $(HOME)/plugins/$(PROGRAM).$(MAJOR)\n");
  printf("\t\tln -sf $(HOME)/plugins/$(PROGRAM).$(MAJOR) $(HOME)/plugins/$(PROGRAM)\n");

#endif
#ifdef __WATCOMC__
  fprintf(stderr, "Warning: Creating a so library under Windows is not possible with Watcom !!\n");
#endif
}
/*...e*/

//------------------------------ Main code ------------------------------
/*...svoid ShowHelp\40\\41\:0:*/
void ShowHelp()
{
  fprintf(stderr, "MKMK by Luis Crespo (lcrespo@ergos.es or lcrespo@dccp.dret.ub.es).\n");
  fprintf(stderr, "Published at http://www.cubic.org/~submissive/sourcerer/mkmk.htm\n\n");

  fprintf(stderr, "Enhanced by Lothar Behrens (lothar.behrens@lollisoft.de)\n\n");

  fprintf(stderr, "MKMK: makefile generator $Revision: 1.66 $\n");
  fprintf(stderr, "Usage: MKMK lib|exe|dll|so modulname includepath,[includepath,...] file1 [file2 file3...]\n");
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
  char s[120],FName[80];
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
  char s[120],FName[80];
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

void replace(char* to, char* match, char* replace) {
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

void WriteDep(FILE *f, char *Name, TIncludeParser *p)
{
  char ObjName[800] = "";
  char ObjNameC[800] = "";
  char NameC[800] = "";
  char SExt[100] = "";
  char Line[120] = "";

  int  CPPFlag = 0;

  char Compiler[100] = "";

  int pos = strlen(Name);

  strcpy(NameC, Name);

  replace(NameC, "/", "\\\\");

  while ((pos > 0) && (Name[pos] != '.')) pos--;
  strcpy(SExt, &Name[pos]);

  for(int c = 0; c < strlen(SExt); c++) SExt[c] = toupper(SExt[c]);

  if (strcmp(SExt, ".CPP") == 0) {
  	CPPFlag = 1;
  	strcpy(Compiler, "$(CPP)");
  }
  
  if (strcmp(SExt, ".CC") == 0) {
  	CPPFlag = 1;
  	strcpy(Compiler, "$(CPP)");
  }
  
  if (strcmp(SExt, ".C") == 0) {
  	CPPFlag = 0;
  	strcpy(Compiler, "$(CC)");
  }
  
  ObjExt(Name,ObjName,sizeof(ObjName));
  sprintf(Line,"%s: makefile %s",ObjName,Name);
  
  strcpy(ObjNameC, ObjName);
  
  replace(ObjNameC, "/", "\\\\");
  
  ListFiles(f,Line,&p->l);

  switch (targettype) {
        case LIB_TARGET:
                printf("\t\t@%s $(C_LIBOPS) $(MOD_INCL) %s\n\n", Compiler, Name);
                break;
        case DLL_TARGET:
        case PLUGIN_TARGET:
        case WXPLUGIN_TARGET:
        case TVISION_DLL:
        	printf("\t\t@echo Build %s\n", NameC);
        	
        	if (CPPFlag == 0) printf("\t\t%s $(C_DLLOPS) $(MOD_INCL) -Fo=%s %s\n", Compiler, ObjNameC, NameC);
        	if (CPPFlag == 1) printf("\t\t%s $(CPP_DLLOPS) $(MOD_INCL_CPP) -Fo=%s %s\n", Compiler, ObjName, Name);
/*
                if (depCount == 0) {
                	printf("\t\t@echo NAME %s > %s.lnk\n", targetname, targetname);
                }
               	printf("\t\t@echo FIL %s >> %s.lnk\n", ObjName, targetname);
               	depCount++;
*/
                break;
        case EXE_TARGET:
        	printf("\t\t@echo Build %s\n", NameC);
        	if (CPPFlag == 0) printf("\t\t%s $(C_EXEOPS) $(MOD_INCL) -Fo=%s %s\n\n", Compiler, ObjNameC, Name);
        	if (CPPFlag == 1) printf("\t\t%s $(CPP_EXEOPS) $(MOD_INCL_CPP) -Fo=%s %s\n\n", Compiler, ObjName, Name);
//                printf("\t\t%s $(C_EXEOPS) $(MOD_INCL) %s\n\n", Compiler, Name);
                break;
        case ELF_TARGET:
		case ELF_BUNDLE_TARGET:
				printf("\t\t@echo Build %s\n", NameC);
                printf("\t\t@%s $(C_ELFOPS) $(MOD_INCL) %s\n\n", Compiler, Name);
                break;
        case SO_TARGET:
        case SOPLUGIN_TARGET:
                {
                int pos = 0;
                for (int i = 0; i < strlen(ObjName); i++) {
                    if (ObjName[i] == '.') {
                        ObjName[i] = 0;
                        break;
                    }
                }
	        	printf("\t\t@echo Build %s\n", NameC);
                printf("\t\t@%s -c -fPIC -g $(C_SOOPS) $(MOD_INCL) %s -o %s.o\n\n", Compiler, Name, ObjName);
                }
                break;
        case WXSO_TARGET:
        case WXSOPLUGIN_TARGET:
                {
                int pos = 0;
                for (int i = 0; i < strlen(ObjName); i++) {
                    if (ObjName[i] == '.') {
                        ObjName[i] = 0;
                        break;
                    }
                }
	        	printf("\t\t@echo Build %s\n", NameC);
                printf("\t\t@%s -c -fPIC -g $(C_SOOPS) $(MOD_INCL) %s -o %s.o\n\n", Compiler, Name, ObjName);
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

  printf("OBJS =");
  
  ListFiles(f,Line,l,true);
  Line[0] = 0;
  
  printf("OBJLIST =");
  ListFilesWithComma(f,Line,l,true);

#ifndef UNIX
//  printf("LIBS = $(DEVROOT)\\projects\\lib\\lbhook.lib \n");
#endif

#ifdef WATCOM_MAKE
/*...swrite a wmake makefile:0:*/
  switch (targettype) {
        case DLL_TARGET:
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
        case DLL_TARGET:
                writeDllTarget(ModuleName);
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
    ShowHelp();
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
  
  if (strcmp(target, "WXSOPLUGIN") == 0) {
        targettype = WXSOPLUGIN_TARGET;
        target_ext = strdup(".so");
  }
  
  if (strcmp(target, "EXE") == 0) {
        targettype = EXE_TARGET;
        target_ext = strdup(".exe");
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

#ifdef __WATCOMC__  
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
#endif  
  for (i=0; i<Sources.Count; i++) DoDep(f,(TDepItem*)Sources[i], copyIPathList, count);
  WriteEnding(f,targetname,&Sources);
//  fclose(f);
  return 0;
}
/*...e*/
