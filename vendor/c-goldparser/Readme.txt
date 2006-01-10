Description: ANSI C GOLD Parser engine implementation
Date:        1/2004
Updated:     1/2005
Author:      Justin Holmes
Email:       justin@holmeweb.net

Updates:
  -  Made the example program print the tokens and rules as it matches them.
     Before, it would just happily run over the input and exit with no feedback(not very
     informative).

Fixes:
  -  Fixed a bug which could cause a crash when loading certain grammars.
  -  Removed some Windows(TM) dependencies which were inadvertantly left in the code.

NOTES:
  -  It doesn't have UNICODE support at the moment, because my project didn't
     need it, but it would be trivial to add, and will be added at some point.
  -  For speed, the "Comment End" terminal is not supported internally by the
     scanner, but is easily implemented.  The example program shows how.
  -  This engine was built and tested with Microsoft Visual C++ versions 6.0 and .NET,
     but doesn't use any extensions, and should be portable.

Files:
 main.cpp         example program for testing the engine
                  - this contains a well-commented example program
 parseconst.h     auto-generated header file(from c-defines.pgt)
 parser.c         the parser implementation
 parser.h         the parser include file
 c - defines.pgt  Gold Parser builder template file for creating c defines
 test.grm         test grammar file
 test.cgt         compiled grammar file
 input.txt        sample grammar input file
 readme.txt       the file you are reading 
