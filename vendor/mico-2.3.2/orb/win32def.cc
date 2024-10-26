// (W) 1998 Martin Sander
// maybe there is a "Microsoft way" to do this

#ifndef BUILD_MICO_DLL

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int main(int argc,char** argv)
{
  if (argc != 4) {
    fprintf(stderr,"Usage: %s <dll name> <dll description> <dumpbin file>\n",argv[0]);
    return 10;
  }

  fprintf(stdout,"LIBRARY\t\t%s\n",argv[1]);
  fprintf(stdout,"DESCRIPTION\t%s\n",argv[2]);
  fprintf(stdout,"EXPORTS\n");

  FILE* dumpbin = fopen(argv[3],"r");

  if (!dumpbin) {
    fprintf(stderr,"cannot read \042%s\042\n",argv[3]);
    return 20;
  }

  int i = 0;

  while (!feof(dumpbin)) {

    char Line[3000];

    memset(Line,0,sizeof(Line));
    fgets(Line,sizeof(Line)-1,dumpbin);

    int dummy1,dummy2;
    char dummy3[3000];
    char name[3000];

    int s = sscanf(Line,"%x %x %s notype () External | %s",&dummy1,&dummy2,&dummy3,name);
    if (s != 4) {
      s = sscanf(Line,"%x %x %s notype External | %s",&dummy1,&dummy2,&dummy3,name);
    }

#if 0
    //necessary if compiling with static runtime library
    // Quite a hack
    // ignore std members because redefinitions
    if(strstr(name,"@std@")!=NULL && NULL==strstr(name,"@CORBA@") && NULL==strstr(name,"MICO")
        && NULL==strstr(name,"FixedBase"))
        continue;
#endif    
    if ((s == 4) &&
	(name[0] == '?') &&
	(strncmp(name,"??_G",4)) &&
	(strncmp(name,"??_E",4)) &&
	(strncmp(name,"??_D",4)) &&
	(strncmp(name,"??_C",4)) &&
	(!strstr(name,"@?$"))
	) {
      fprintf(stdout,"\t\t%s\n",name);
      i++;
      if(i%10 ==0)
          fprintf(stderr,"\r%d symbols",i);
    }
    // sander begin
    if ((s == 4) &&
	(!strncmp(name,"_CORBA",6)) &&
	(stricmp(dummy3,"UNDEF"))
	) {

      fprintf(stdout,"\t\t%s\n",name+1);
      fprintf(stderr,"\r%d symbols",i++);

    }
    // sander end
  }

  fprintf(stderr,"\n");

  fclose(dumpbin);

  return 0;
}

#endif