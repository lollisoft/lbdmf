
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "parser.h"
#include "parseconst.h"

//
// This function is called when the scanner matches a token
//
// Our implementation handles the "Comment Start" symbol, and scans through
// the input until the token closure is found
//
// All other tokens are refered to the default match function
//
char cbmatchtoken(_parser* parser, void* user, short type, char* name, short symbol)
{
	short c;
	switch(type) {
	case SymbolTypeCommentStart: // /* */
		while((c = scanner_get_char(parser)) != EEOF) {
			if (c == '*') {
				scanner_next_char(parser);
				c = scanner_get_char(parser);
				if (c != EEOF) {
					if (c == '/') {
						scanner_next_char(parser);
						return 0;
					}
				}
			}
			scanner_next_char(parser);
		}
		parser->symbol = 0; // eof
		return 0;
	default:
		return scanner_def_matchtoken(parser,user,type,name,symbol);
	}
}

//
// This function is called when the scanner needs more data
//
// If the pinput->bpreserve flag is set(because the scanner may need
// to backtrack), then the data in the current input buffer must be
// preserved.  This is done by increasing the buffer size and copying
// the old data to the new buffer.
// If the pinput->bpreserve flag is not set, the new data can be copied
// over the existing buffer.
//
// If the input buffer is empty after this callback returns(because no
// more data was added), the scanner function will return either:
//   1] the last accepted token
//   2] an eof, if no token has been accepted yet
//
void cbgetinput(_parse_input* pinput)
{
	int nr;
	if (!feof((FILE*)pinput->user)) {
		if (pinput->bpreserve) {
			// copy the existing buffer to a new, larger one
			char* p = (char*)malloc(2048 + pinput->ncount);
			pinput->nbufsize += 2048;
			memcpy(p, pinput->buf, pinput->ncount);
			free(pinput->buf);
			pinput->buf = p;
			nr = (int)fread(pinput->buf, 1, 2048, (FILE*)pinput->user);
			pinput->ncount += nr; // increase the character count
		} else {
			nr = (int)fread(pinput->buf, 1, pinput->nbufsize, (FILE*)pinput->user);
			pinput->nofs = 0;    // reset the offset
			pinput->ncount = nr; // set the character count
		}
	}
}

int main(int argc, char** argv)
{
	const char* lexeme;
	_parse_input* input;
	FILE*		fin = 0;
	Parser		p("test.cgt");

	if (!p.isopen()) return 0;

	// open input file
	fin = fopen("input.txt", "rb");
	if (!fin) {
		printf("input file not found");
		return 0;
	}

	// set match callback
	p.m_parser->cbmatchtoken = cbmatchtoken;

	// set the input
	input = &p.m_parser->input;
	input->buf = (char*)malloc(2048);
	input->nbufsize = 2048;
	input->cbneedinput = cbgetinput;
	input->user = fin;

	printf("starting parse of file 'input.txt'\n");

	bool run = true;
	while(run)
	{
		lexeme = 0;
		switch(p.parse())
		{
		case PS_NUMBER: // Symbol Number
			lexeme = p.get_child_lexeme(0);
			p.set_lexeme(lexeme,0);
			printf("Number: %s\n", lexeme);
			break;
		case PS_WORD: // Symbol Word
			lexeme = p.get_child_lexeme(0);
			p.set_lexeme(lexeme,0);
			printf("Word: %s\n", lexeme);
			break;
		case PS_RNUMBER: // Rule <Number>
			lexeme = p.get_child_lexeme(0);
			p.set_lexeme(lexeme,0);
			printf("<Number>: %s\n", lexeme);
			break;
		case PS_RWORD: // Rule <Word>
			lexeme = p.get_child_lexeme(0);
			p.set_lexeme(lexeme,0);
			printf("<Word>: %s\n", lexeme);
			break;
		case PS_VALUE: // Rule <Value>
			lexeme = p.get_child_lexeme(0);
			p.set_lexeme(lexeme,0);
			printf("<Value>: %s\n", lexeme);
			break;
		case PS_MAIN:  // Rule <Main>
			lexeme = p.get_child_lexeme(0);
			p.set_lexeme(lexeme,0);
			printf("<Main>: %s\n", lexeme);
			break;
		case PS_EOF: // Eof
			run = false;
			break;
		case -1: // Parse error
			run = false;
			break;
		default:
			break;
		}
	}

	if (fin) fclose(fin);
	free(input->buf);
	return 0;
}
