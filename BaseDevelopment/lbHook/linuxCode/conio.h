#ifndef  __CONIO_H
#define  __CONIO_H

/*  conio.h - Einfache Nachbildung der wichtigsten
              Semigraphik-Funktionen von Borland-C unter DOS 
              (aus conio.h und dos.h)                              */

#include   <stdio.h>
#include   <signal.h>
#include   <string.h>
#include   <stdarg.h>
#include   <ctype.h>
#include   <sys/time.h>
#include   <time.h>
#include   <sys/types.h>
#include   <termios.h>
#include   <unistd.h>
#include   <stdlib.h>

/*================ Hilfsroutinen =====================================*/
/*====================================================================*/

static struct termios   alt_terminal;
static int              alt_ttyfd = -1;
static enum { RESET, CBREAK } tty_modus = RESET;

/*------ tty_cbreak --- Terminal in cbreak-Modus umschalten ----------*/
int tty_cbreak(int fd, int echo);
/*------ tty_reset --- Terminal in alten Modus zuruecksetzen ---------*/
int tty_reset(int fd);
/*------ wherexy --- Aktuellen Cursorkoordinaten ermitteln ----------*/
void wherexy(int *x, int *y);
/*====================================================================*/
/*=================== conio-Teil =====================================*/
/*====================================================================*/
# define  BLACK         0
# define  RED           1
# define  GREEN         2
# define  BROWN         3
# define  BLUE          4
# define  MAGENTA       5
# define  CYAN          6
# define  LIGHTGRAY     7
# define  DARKGRAY      8
# define  LIGHTRED      9
# define  LIGHTGREEN   10
# define  YELLOW       11
# define  LIGHTBLUE    12
# define  LIGHTMAGENTA 13
# define  LIGHTCYAN    14
# define  WHITE        15

# define BLINK       0x80

#define  cscanf   scanf
#define  cgets    gets

void clreol(void);
void gotoxy(int x, int y);
void clrscr(void);
void delline(void);
void insline(void);
void normvideo(void);
void highvideo(void);
void lowvideo(void);
int  wherex(void);
int  wherey(void);
int  putch(int zeich);
int  cputs(char *string);

void textcolor(int farbe);
void textbackground(int farbe);

void textattr(int attr);
void sound(unsigned frequenz);
void nosound(void);
void cprintf(const char *format, ...);
int  getch(void);
int  getche(void);
int  kbhit(void);
void delay(long millisek);
int gettext(int left, int top, int right, int bottom, char *puffer);
int puttext(int left, int top, int right, int bottom, char *puffer);
int movetext(int left, int top, int right, int bottom,
             int zielleft, int zieltop);
#define _NOCURSOR      0
#define _SOLIDCURSOR   1
#define _NORMALCURSOR  2

void _setcursortype(int cursor);
#define  MAX_PASSWORT   8  /* Maximal 8 Zeichen fuer ein Passwort */
char *getpass(const char *prompt);
#endif  /* __CONIO_H */
