
/*  conio.h - Einfache Nachbildung der wichtigsten
              Semigraphik-Funktionen von Borland-C unter DOS 
              (aus conio.h und dos.h)                              */

#include   <conio.h>

/*------ tty_cbreak --- Terminal in cbreak-Modus umschalten ----------*/
int tty_cbreak(int fd, int echo)
{
   struct termios  terminal;

   if (tcgetattr(fd, &alt_terminal) < 0)
      return(-1);
   terminal = alt_terminal;
   terminal.c_lflag &= (echo==0) ? (~(ECHO | ICANON)) : (~ICANON); 
   terminal.c_cc[VMIN] = 1; /* Fall 2: Immer nur 1 Byte; kein Timer */
   terminal.c_cc[VTIME] = 0;
  
   if (tcsetattr(fd, TCSANOW, &terminal) < 0)
      return(-1);
   tty_modus = CBREAK;
   alt_ttyfd = fd;
   return(0);
}

/*------ tty_reset --- Terminal in alten Modus zuruecksetzen ---------*/
int tty_reset(int fd)
{
   if (tty_modus != CBREAK)
      return(-1);
   if (tcsetattr(fd, TCSANOW, &alt_terminal) < 0)
      return(-1);
   return(0);
}

/*------ wherexy --- Aktuellen Cursorkoordinaten ermitteln ----------*/
void wherexy(int *x, int *y)
{
   char *term_name = ttyname(0), vcsa_name[100] = "/dev/vcsaX";
   FILE *vcsa;

   vcsa_name[strlen(vcsa_name)-1] = term_name[strlen(term_name)-1];
   if ( (vcsa = fopen(vcsa_name, "r")) == NULL) {
      fprintf(stderr, "kann `%s' nicht oeffnen\n", vcsa_name);
      return;
   }
   fgetc(vcsa); fgetc(vcsa);
   *x = fgetc(vcsa);
   *y = fgetc(vcsa);
   fclose(vcsa);
}

/*====================================================================*/
/*=================== conio-Teil =====================================*/
/*====================================================================*/
void clreol(void)         { printf("\033[80X");          fflush(stdout); }
void gotoxy(int x, int y) { printf("\033[%d;%dH", y, x); fflush(stdout); }
void clrscr(void)         { printf("\033[H\033[J");      fflush(stdout); }
void delline(void)        { printf("\033[1M");           fflush(stdout); }
void insline(void)        { printf("\033[1L");           fflush(stdout); }
void normvideo(void)      { printf("\033[0m");           fflush(stdout); }
void highvideo(void)      { printf("\033[1m");           fflush(stdout); }
void lowvideo(void)       { printf("\033[2m");           fflush(stdout); }
int  wherex(void)         { int  x, y; wherexy(&x,&y);   return(x+1);    }
int  wherey(void)         { int  x, y; wherexy(&x,&y);   return(y+1);    }
int  putch(int zeich)     { printf("%c", zeich);         fflush(stdout); }
int  cputs(char *string)  { printf("%s", string);        fflush(stdout); }

void textcolor(int farbe) { printf("\033[2m\033[2;%d]", farbe & 0x7f);
                            printf("\033[%dm", (farbe & 0x80) ? 5 : 25);
                            fflush(stdout);                              }

void textbackground(int farbe) { printf("\033[%dm", 40+farbe%8);
                                 fflush(stdout);                         }

void textattr(int attr)        { textcolor( attr & 0x0f );
                                 textbackground( (attr >> 4) & 0x0f );   }

void sound(unsigned frequenz)  { printf("\033[10;%d]", frequenz);
                                 printf("\007");         fflush(stdout); }

void nosound(void)             { printf("\033[10;0]");   fflush(stdout); }

/*---------------------------------------------- cprintf ------------*/
void cprintf(const char *format, ...)
{
   char puffer[5000];
   va_list     az;
   
   va_start(az, format);
   
   vsprintf(puffer, format, az);
   fprintf(stdout, "%s", puffer);
   fflush(stdout);

   va_end(az);
}

/*------------------------------------------------ getch ------------*/
int  getch(void)
{
   int zeich;

   if (tty_cbreak(STDIN_FILENO, 0) < 0) {
      fprintf(stderr, "kann nicht in cbreak-Modus umschalten\n");
      return(EOF);
   }
   if (read(STDIN_FILENO, &zeich, 1) == 1)
      zeich &= 0xff;
   tty_reset(STDIN_FILENO);
   return(zeich);
}

/*----------------------------------------------- getche ------------*/
int  getche(void)
{
   int zeich;

   if (tty_cbreak(STDIN_FILENO, 1) < 0) {
      fprintf(stderr, "kann nicht in cbreak-Modus umschalten\n");
      return(EOF);
   }
   if (read(STDIN_FILENO, &zeich, 1) == 1)
      zeich &= 0xff;
   tty_reset(STDIN_FILENO);
   return(zeich);
}

/*------------------------------------------------ kbhit ------------*/
int  kbhit(void)
{
   fd_set          lese_menge;
   struct timeval  timeout;
   struct termios  terminal;
   int             taste;
   
   if (tcgetattr(0, &alt_terminal) < 0)
      return(-1);
   terminal = alt_terminal;
   terminal.c_lflag &= ~ICANON;  /* kanonischen Modus ausschalten */
   terminal.c_cc[VMIN] = 1; /* Immer nur 1 Byte; kein Timer */
   terminal.c_cc[VTIME] = 0;
  
   if (tcsetattr(0, TCSANOW, &terminal) < 0)
      return(-1);
   tty_modus = CBREAK;
   alt_ttyfd = 0;

   FD_ZERO(&lese_menge);
   FD_SET(0, &lese_menge);
   timeout.tv_sec  = 0;
   timeout.tv_usec = 100;
   taste = select(1, &lese_menge, NULL, NULL, &timeout);

   tty_reset(STDIN_FILENO);
   return(taste);
}

/*------------------------------------------------ delay ------------*/
void delay(long millisek)
{
   int mikrosek = millisek*1000;
   struct timeval  timeout;
   
   timeout.tv_sec  = mikrosek / 1000000L;
   timeout.tv_usec = mikrosek % 1000000L;
   select(0, NULL, NULL, NULL, &timeout);
}

/*---------------------------------------------- gettext ------------*/
#ifdef bla
int gettext(int left, int top, int right, int bottom, char *puffer)
{
   char *term_name = ttyname(0), vcsa_name[100] = "/dev/vcsaX";
   FILE *vcsa;
   int  i, j, z=0,
        offset = 4 + ((top-1)*80+left-1)*2,
        pro_zeile = (right-left+1)*2,
        zeil_zahl = (bottom-top+1);

   vcsa_name[strlen(vcsa_name)-1] = term_name[strlen(term_name)-1];

   if ( (vcsa = fopen(vcsa_name, "r")) == NULL) {
      fprintf(stderr, "kann `%s' nicht oeffnen\n", vcsa_name);
      return -1;
   }
   fseek(vcsa, offset, SEEK_SET);
   for (i=1; i<=zeil_zahl; i++) {
      for (j=1; j<=pro_zeile; j++)
         puffer[z++] = fgetc(vcsa);
      fseek(vcsa, 80*2L-pro_zeile, SEEK_CUR);
   }
   fclose(vcsa);
}
#endif
/*---------------------------------------------- puttext ------------*/
int puttext(int left, int top, int right, int bottom, char *puffer)
{
   char *term_name = ttyname(0), vcsa_name[100] = "/dev/vcsaX";
   FILE *vcsa;
   int  i, j, z=0,
        offset = 4 + ((top-1)*80+left-1)*2,
        pro_zeile = (right-left+1)*2,
        zeil_zahl = (bottom-top+1);

   vcsa_name[strlen(vcsa_name)-1] = term_name[strlen(term_name)-1];
   if ( (vcsa = fopen(vcsa_name, "w")) == NULL) {
      fprintf(stderr, "kann `%s' nicht oeffnen\n", vcsa_name);
      return -1;
   }
   fseek(vcsa, offset, SEEK_SET);
   for (i=1; i<=zeil_zahl; i++) {
      for (j=1; j<=pro_zeile; j++)
         fputc(puffer[z++], vcsa);
      fseek(vcsa, 80*2L-pro_zeile, SEEK_CUR);
   }
   fclose(vcsa);
}

/*--------------------------------------------- movetext ------------*/
int movetext(int left, int top, int right, int bottom,
             int zielleft, int zieltop)
{
   char *term_name = ttyname(0), vcsa_name[100] = "/dev/vcsaX", puffer[5000];
   FILE *vcsa;
   int  i, j, z=0,
        offset = 4 + ((top-1)*80+left)*2,
        pro_zeile = (right-left+1)*2,
        zeil_zahl = (bottom-top+1),
        ziel_offset = 4 + ((zieltop-1)*80+zielleft)*2;

   vcsa_name[strlen(vcsa_name)-1] = term_name[strlen(term_name)-1];
   if ( (vcsa = fopen(vcsa_name, "w+")) == NULL) {
      fprintf(stderr, "kann `%s' nicht oeffnen\n", vcsa_name);
      return -1;
   }

   fseek(vcsa, offset, SEEK_SET);
   for (i=1; i<=zeil_zahl; i++) {
      for (j=1; j<=pro_zeile; j++)
         puffer[z++] = fgetc(vcsa);
      fseek(vcsa, 80*2L-pro_zeile-2, SEEK_CUR);
   }

   fseek(vcsa, ziel_offset, SEEK_SET);
   z = 0;
   for (i=1; i<=zeil_zahl; i++) {
      for (j=1; j<=pro_zeile; j++)
         fputc(puffer[z++], vcsa);
      fseek(vcsa, 80*2L-pro_zeile-2, SEEK_CUR);
   }
   fclose(vcsa);
}

/*--------------------------------------- _setcursortype ------------*/
void _setcursortype(int cursor)
{
   if (cursor == _NOCURSOR) {
      printf("\033[?25l");
      printf("\033[?1000l");
   } else 
      printf("\033[?25h");
   fflush(stdout);
}

/*---------------------------------------------- getpass ------------*/
char *getpass(const char *prompt)
{
   static char      puffer[MAX_PASSWORT + 1];
   char             *zgr;
   sigset_t         sig_maske, sig_alt;
   struct termios   terminal, terminal_alt;
   FILE             *fz;
   int              zeich;

   if ( (fz = fopen(ctermid(NULL), "r+")) == NULL)
      return(NULL);
   setbuf(fz, NULL);

    /* Blockieren der Signale SIGINT u. SIGTSTP */
   sigemptyset(&sig_maske);
   sigaddset(&sig_maske, SIGINT);
   sigaddset(&sig_maske, SIGTSTP);
   sigprocmask(SIG_BLOCK, &sig_maske, &sig_alt);

   tcgetattr(fileno(fz), &terminal_alt);
   terminal = terminal_alt;
   terminal.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
   tcsetattr(fileno(fz), TCSAFLUSH, &terminal);

   fputs(prompt, fz);

   zgr = puffer;
   while ( (zeich = getc(fz)) != EOF && zeich != '\n')
      if (zgr < &puffer[MAX_PASSWORT])
         *zgr++ = zeich;
   *zgr = '\0';
   putc('\n', fz);  /* Echo fuer NL */

    /* Terminal in alten Zustand zuruecksetzen */ 
   tcsetattr(fileno(fz), TCSAFLUSH, &terminal_alt); 

    /* Alte Signalmaske wieder herstellen */
   sigprocmask(SIG_SETMASK, &sig_alt, NULL);
   fclose(fz);

   return(puffer);
}

