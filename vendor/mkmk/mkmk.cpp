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
 * $Revision: 1.5 $
 * $Name:  $
 * $Id: mkmk.cpp,v 1.5 2001/10/20 19:45:43 lothar Exp $
 *
 * $Log: mkmk.cpp,v $
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
/*...e*/
/*...sdefs:0:*/
#ifdef __WATCOMC__
  #include <dos.h>
  #define findfirst(x,y,z) _dos_findfirst(x,z,y)
  #define findnext _dos_findnext
  #define ffblk find_t
  #define ff_name name
#else
  #include <dosdir.h>
#endif
/*...e*/

#define WATCOM_MAKE
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

int targettype=EXE_TARGET;

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
    TDepList l;
  private:
    char FilePath[80];
    bool Comment,bCPP;
    bool BasicParse(char *FileName);
    void ParseComments(char *s);
    void ParseCLine(char *s);
    void AddInclude(char *IncName);
};
/*...e*/
/*...svoid TIncludeParser\58\\58\AddInclude\40\char \42\IncName\41\:0:*/
void TIncludeParser::AddInclude(char *IncName)
{
  char s[160];
  bool Found;

  if (l.Search(IncName)) return;
  printf("    '%s'\n",IncName);
  Found=BasicParse(IncName);
  if (Found) l.Insert(IncName,"");
  else if (FilePath[0]!=0)
  {
    strcpy(s,FilePath);
    strcat(s,IncName);
    Found=BasicParse(s);
    l.Insert(IncName,FilePath);
  }
  if (!Found)
    fprintf(stderr,"WARNING: %s could not be opened\n",IncName);
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
        AddInclude(p1);
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
    if (Comment)
    {
      if (s[i]=='*' && s[i+1]=='/')
      {
        Comment=false;
        i++;
      }
      else (s[i]='*');
    }
    else if (s[i]=='/')
    {
      switch (s[i+1])
      {
        case '*': Comment=true; i++; break;
        case '/': s[i]=0; i--; break;
      }
    }
    i++;
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
    fprintf(stderr,"WARNING: %s could not be opened\n",FileName);
    return false;
  }
  else return true;
}
/*...e*/
/*...sbool TIncludeParser\58\\58\BasicParse\40\char \42\FileName\41\:0:*/
bool TIncludeParser::BasicParse(char *FileName)
{
  FILE *f;
  char Line[256];

  f=fopen(FileName,"rt");
  if (!f) return false;
  do {
    fgets(Line,sizeof(Line)-1,f);
    if (Line[0]!=0)
    {
      ParseComments(Line);
      ParseCLine(Line);
    }
  } while (!feof(f));
  fclose(f);
  return true;
}
/*...e*/
/*...e*/
//------------------------------ Main code ------------------------------
/*...svoid ShowHelp\40\\41\:0:*/
void ShowHelp()
{
  puts("MKMK: makefile generator");
  puts("Usage: MKMK lib|exe|dll modulname file1 [file2 file3...]\n");
}
/*...e*/
/*...svoid WriteHeader\40\FILE \42\f\44\ char \42\ExeName\41\:0:*/
void WriteHeader(FILE *f, char *ExeName)
{
  fprintf(f,"#Make file automatically generated by MKMK\n\n");

  fprintf(f,"!include $(%%DEVROOT)\\projects\\cpp\\make\\STD_MAKE\n");
  fprintf(f,"!include STD_MAKE\n");

  fprintf(f,".BEFORE\n");
  fprintf(f,"!include MAKE_BEFORE\n");


  fprintf(f,"main: %s\n\n",ExeName);
  fprintf(f,"clean: .SYMBOLIC\n");
  fprintf(f,"  del *.err\n");
  fprintf(f,"  del *.obj\n");
  fprintf(f,"  del %s\n\n",ExeName);
  fprintf(f,"#Compiler and linker definitions (suggestion):\n");
#ifdef WATCOM_MAKE
  fprintf(f,"CC       = WPP386\n");
  fprintf(f,"C_OPS    = $(STD_C_OPS) /Oneatx /zp4 /5 /fp5 /D1 /D3 /W1 /MF /SG /HW /ZQ\n");

/*...sbla:0:*/
#ifdef bla  
  fprintf(f,"STD_INCL = -i=.;Q:\\develop\\Tools\\WATCOM\\h;&\n");
  fprintf(f,"Q:\\develop\\Tools\\WATCOM\\h\\nt;&\n");
  fprintf(f,"Q:\\develop\\projects\\cpp\\interfaces;&\n");
  fprintf(f,"Q:\\develop\\projects\\cpp\\include;&\n");
  fprintf(f,"Q:\\develop\\projects\\dll\\include;&\n");
  fprintf(f,"Q:\\develop\\projects\\lib\\include\n");
#endif
/*...e*/
  
  fprintf(f,"LINK     = WLINK\n");
  fprintf(f,"WLIB     = WLIB\n");
  fprintf(f,"LIB_OPS  = -b -c -n -q -p=512\n");
  fprintf(f,"L_OPS_EXE    = D all SYS nt op m op maxe=25 op q\n\n");
  fprintf(f,"L_OPS_DLL    = D all SYS nt_dll op m op maxe=25 op q\n\n");
  fprintf(f,"L_OPS_LIB    = D all SYS nt_lib op m op maxe=25 op q\n\n");
#else
  fprintf(f,"CC       = your favorite C/CPP compiler\n");
  fprintf(f,"C_OPS    = your compiler options\n");
  fprintf(f,"LINK     = your favorite linker\n");
  fprintf(f,"L_OPS    = your linker options\n\n");
#endif
  fprintf(f,"#File dependencies:\n\n");
}
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
  strcat(ObjName,"OBJ");
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
      fprintf(f,"%s, %c\n",Line,MoreChar);
      sprintf(Line," %s",s);
    }
    else {
	if (i!=0) strcat(Line,", ");
    	strcat(Line,s);
    }
  }
  fprintf(f,"%s\n",Line);
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
  fprintf(f,"  $(CC) $(C_OPS) $(STD_INCL) %s\n\n",Name);
}
/*...e*/
/*...svoid WriteEnding\40\FILE \42\f\44\ char \42\ExeName\44\ TDepList \42\l\41\:0:*/
void WriteEnding(FILE *f, char *ModuleName, TDepList *l)
{
  char Line[120];

  fprintf(f,"OBJS =");
  ListFiles(f,Line,l,true);
  fprintf(f,"LIBS = $(%%DEVROOT)\\projects\\dll\\libs\\lbHook.lib \n\n");
#ifdef WATCOM_MAKE

  switch (targettype) {
  	case DLL_TARGET:
  		printf("Making a dll target\n");
		fprintf(f,"%s: $(OBJS) $(LIBS)\n",ModuleName);
		fprintf(f,"  *$(LINK) $(L_OPS_DLL) name %s file $(OBJS) library $(LIBS)\n",ModuleName);
  		break;
  	case LIB_TARGET:
  		printf("Making a lib target\n");
  		fprintf(f,"%s: $(OBJS) $(LIBS)\n",ModuleName);
  		fprintf(f,"  *$(WLIB) $(LIB_OPS_LIB) %s &\n", ModuleName);
  		fprintf(f,"	$(OBJS)\n");
  		break;
  	case EXE_TARGET:
  		printf("Making a exe target\n");
  		fprintf(f,"%s: $(OBJS) $(LIBS)\n",ModuleName);
  		fprintf(f,"  *$(LINK) $(L_OPS_EXE) name %s ",ModuleName);
  		fprintf(f,"file {$(OBJS)} library {$(LIBS)}\n");
  		    
  		break;
  	default:
  		break;
  }

  fprintf(f,".AFTER\n");
  fprintf(f,"!include MAKE_AFTER\n");

#else
  fprintf(f,"  $(LINK) $(L_OPS) %s $(OBJS) $(LIBS)\n",ModuleName);
#endif
}
/*...e*/
/*...svoid DoDep\40\FILE \42\f\44\ TDepItem \42\d\41\:0:*/
void DoDep(FILE *f, TDepItem *d)
{
  TIncludeParser p;
  char FileName[256];

  strcpy(FileName,d->Path);
  strcat(FileName,d->Name);
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
    return 0;
  }
  f=fopen("makefile","wt");
  if (!f)
  {
	  fputs("ERROR: could not create makefile",stderr);
    return 0;
  }
  
/*...sdetermine target type:0:*/
  char *target = strdup(argv[1]);
  char *targetname = strdup(argv[2]);
  char *target_ext = NULL;
  
  for(int c = 0; c < strlen(target); c++) target[c] = toupper(target[c]);
  
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
  
  WriteHeader(f,targetname);
  for (i=3; i<argc; i++) Sources.AddMask(argv[i]);
  for (i=0; i<Sources.Count; i++) DoDep(f,(TDepItem*)Sources[i]);
  WriteEnding(f,targetname,&Sources);
  fclose(f);
}
/*...e*/
