/*...scopyright:0:*/
/*
 MKMK: Makefile maker.
 By Luis Crespo, lcrespo@ergos.es
 Please read MKMK.TXT for a program description.

 Define "WATCOM_MAKE" for Watcom C/C++ oriented makefiles.
 Define "UNIX" for unix orieted makefiles
*/
/*...e*/
/*...sRevision history:0:*/
/**************************************************************
 * $Locker:  $
 * $Revision: 1.22 $
 * $Name:  $
 * $Id: mkmk.cpp,v 1.22 2001/12/12 17:20:20 lothar Exp $
 *
 * $Log: mkmk.cpp,v $
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

  #include "dosdir.h"

#endif
/*...e*/

//#define WATCOM_MAKE

#ifdef LINUX
#define UNIX
#undef WATCOM_MAKE
#endif

/*...sdefs:0:*/
#ifdef UNIX
  #define PathChar '/'
#else
  #define PathChar '\\'
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

#define EXE_TARGET 1
#define DLL_TARGET 2
#define LIB_TARGET 3
#define ELF_TARGET 4
#define SO_TARGET  5

int targettype=EXE_TARGET;

char** IncPathList;

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
	  	(*array)[index] = block;
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
  char Path[80],Name[80];

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
	} else { printf("Error: No standard path has this file, and this rule does not match for %s\n", IncName); }
  }
/*...e*/

  if (l.Search(realfile)) {
//	printf("File %s has already been added!\n", realfile);
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
void writeExeTarget(char* modulename) {
#ifdef UNIX
  fprintf(stderr, "Writing exe target\n");
  printf("PROGRAM=%s\n", modulename);
  printf("\n%s: $(OBJS)\n", modulename);
  printf("\t\t$(CC) $(L_OPS) %s $(OBJS) $(OBJDEP) $(LIBS)\n",modulename);
  printf("\t\t$(CP) $(PROGRAM) $(HOME)/bin\n");
  fprintf(stderr, "Written exe target\n");
#endif
#ifdef __WATCOMC__
  char* ModName = strdup(modulename);
  char** array;
  int count = split('.', ModName, &array);

  printf("FILE = FIL\n");
  printf("FILE += $(foreach s, $(OBJS),$s, )\n");
  printf("LNK=%s.lnk\n", ModName);
  printf("PROGRAM=%s\n", ModName);
  
  printf("\n%s.exe: $(OBJS)\n", ModName);
  printf("\t\techo NAME $(PROGRAM).exe > $(LNK)\n");
  printf("\t\techo $(FILE) $(LIBS) >> $(LNK)\n");
  printf("\t\t$(LINK) @$(LNK)\n");
  printf("\t\t$(CP) $(PROGRAM).exe $(EXEDIR)\n");
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
  printf("FILE += $(foreach s, $(OBJS),$s, )\n");
  printf("LNK=%s.lnk\n", ModName);
  printf("PROGRAM=%s\n", ModName);
  
  printf("\n%s.dll: $(OBJS)\n", ModName);
  printf("\t\techo NAME $(PROGRAM).dll > $(LNK)\n");
  printf("\t\techo $(FILE) $(LIBS) >> $(LNK)\n");
  printf("\t\techo LIBR $(LIBS) >> $(LNK)\n");
  printf("\t\t$(LINK) $(LNKDLLOPS) @$(LNK)\n");
  printf("\t\t$(CP) $(PROGRAM).dll $(DLLDIR)\n");
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
//  printf("\t\techo $(PROGRAM).$(OBJ) > $(LNK)\n");
//  printf("\t\techo $(FILE) $(LIBS) >> $(LNK)\n");
//  printf("\t\techo LIBR $(LIBS) >> $(LNK)\n");


//  printf("\t\twlib -b -c -n -q -p=512 lbhook.lib @lbhook.lb1

  TDepItem *d;
  char FName[80] = "";

  printf("\t\t$(RM) $(LNK)\n");

  for (int i=0; i<l->Count; i++)
  {
    d=(TDepItem*)(*l)[i];
    
    ObjExt(d->Name,FName,sizeof(FName));

    printf("\t\techo +%s >> $(LNK)\n", FName);
  }
  
  printf("\t\twlib -b -c -n -q -p=512 $(PROGRAM).lib @$(LNK)\n");
//  printf("\t\t$(LINK) $(LNKDLLOPS) @$(LNK)\n");
  printf("\t\t$(CP) $(PROGRAM).lib $(LIBDIR)\n");
#endif
}
/*...e*/
#ifdef bla
/*...swriteLibTarget\40\char\42\ modulename\41\:0:*/
void writeLibTarget(char* modulename) {
#ifdef UNIX
  printf("\n%s: $(OBJS)\n", modulename);
  printf("\t\t$(CC) $(L_OPS) %s $(OBJS) $(OBJDEP)\n",modulename);
#endif
#ifdef __WATCOMC__
  #ifdef VERBOSE
  printf("Making a lib target\n");
  #endif
  printf("%s: $(OBJS) $(LIBS)\n",modulename);
  printf("\t\t*$(WLIB) $(LIB_OPS_LIB) %s \\\n", modulename);
  printf("\t\t$(OBJS)\n");
#endif
}
/*...e*/
#endif
/*...swrite_so_Target\40\char\42\ modulename\41\ create a UNIX shared library:0:*/
void write_so_Target(char* modulename) {
#ifdef UNIX
  printf("PROGRAM=%s\n", modulename);
  printf("MAJOR=0\n");
  printf("MINOR=0\n");
  printf("MICRO=1\n");
  printf("\n%s: $(OBJS)\n", modulename);
  printf("\t\t$(CC) -shared -WL,soname,$(PROGRAM).so.$(MAJOR) -o $(PROGRAM).so.$(MAJOR).$(MINOR).$(MICRO) $(OBJS) $(OBJDEP) -lc\n",modulename);
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
  fprintf(stderr, "MKMK: makefile generator");
  fprintf(stderr, "Usage: MKMK lib|exe|dll modulname includepath,[includepath,...] file1 [file2 file3...]\n");
}
/*...e*/
/*...svoid WriteHeader\40\FILE \42\f\44\ char \42\ExeName\41\:0:*/
void WriteHeader(FILE *f, char *ExeName)
{
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
//	if (i!=0) strcat(Line,", ");
    	strcat(Line,s);
    }
  }
  printf("%s\n",Line);
}
/*...e*/
/*...svoid WriteDep\40\FILE \42\f\44\ char \42\Name\44\ TIncludeParser \42\p\41\:0:*/
void WriteDep(FILE *f, char *Name, TIncludeParser *p)
{
  char ObjName[800];
  char Line[120];

  ObjExt(Name,ObjName,sizeof(ObjName));
  sprintf(Line,"%s: makefile %s",ObjName,Name);
  ListFiles(f,Line,&p->l);

  switch (targettype) {
  	case LIB_TARGET:
		printf("\t\t$(CC) $(C_OPS) $(MOD_INCL) %s\n\n",Name);
		break;
  	case DLL_TARGET:
		printf("\t\t$(CC) $(C_OPS) $(MOD_INCL) %s\n\n",Name);
		break;
	case EXE_TARGET:
		printf("\t\t$(CC) $(C_OPS) $(MOD_INCL) %s\n\n",Name);
		break;
	case ELF_TARGET:
	    	printf("\t\t$(CC) $(C_OPS) $(MOD_INCL) %s\n\n",Name);
		break;
	case SO_TARGET:
		printf("\t\t$(CC) -fPIC -g $(C_OPS) $(MOD_INCL) %s\n\n",Name);
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

#ifndef UNIX
  printf("LIBS = $(DEVROOT)\\projects\\lib\\lbhook.lib \n");
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
  		printf("	$(OBJS)\n");
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
		break;
  	case LIB_TARGET:
		writeLibTarget(ModuleName, l);
		break;
	case EXE_TARGET:
		writeExeTarget(ModuleName);
		break;
	case ELF_TARGET:
		writeExeTarget(ModuleName);
		break;
	case SO_TARGET:
		write_so_Target(ModuleName);
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
void main(int argc, char *argv[])
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
    return;
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
  char *targetname = strdup(argv[2]);
  char *target_ext = NULL;
  
  for(int c = 0; c < strlen(target); c++) target[c] = toupper(target[c]);
  
  if (strcmp(target, "-") == 0) {
  	targettype = ELF_TARGET;
  	target_ext = strdup("");
  }
  
  if (strcmp(target, "ELF") == 0) {
  	targettype = ELF_TARGET;
  	target_ext = strdup("");
  }
  
  if (strcmp(target, "SO") == 0) {
  	targettype = SO_TARGET;
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
  for (i=0; i<Sources.Count; i++) DoDep(f,(TDepItem*)Sources[i], copyIPathList, count);
  WriteEnding(f,targetname,&Sources);
//  fclose(f);
}
/*...e*/
