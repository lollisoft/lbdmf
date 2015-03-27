/** \file
 *  This C source file was generated by $ANTLR version 3.5
 *
 *     -  From the grammar source file : /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g
 *     -                            On : 2015-03-22 11:46:15
 *     -                 for the lexer : uiLexerLexer
 *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
*/
// [The "BSD license"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


/* =============================================================================
 * This is what the grammar programmer asked us to put at the top of every file.
 */

#define Hidden 99

/* End of Header action.
 * =============================================================================
 */

/* -----------------------------------------
 * Include the ANTLR3 generated header file.
 */
#include    "uiLexer.h"
/* ----------------------------------------- */





/* MACROS that hide the C interface implementations from the
 * generated code, which makes it a little more understandable to the human eye.
 * I am very much against using C pre-processor macros for function calls and bits
 * of code as you cannot see what is happening when single stepping in debuggers
 * and so on. The exception (in my book at least) is for generated code, where you are
 * not maintaining it, but may wish to read and understand it. If you single step it, you know that input()
 * hides some indirect calls, but is always referring to the input stream. This is
 * probably more readable than ctx->input->istream->input(snarfle0->blarg) and allows me to rejig
 * the runtime interfaces without changing the generated code too often, without
 * confusing the reader of the generated output, who may not wish to know the gory
 * details of the interface inheritance.
 */

#define		CTX	ctx

/* Aids in accessing scopes for grammar programmers
 */
#undef	SCOPE_TYPE
#undef	SCOPE_STACK
#undef	SCOPE_TOP
#define	SCOPE_TYPE(scope)   puiLexer_##scope##_SCOPE
#define SCOPE_STACK(scope)  puiLexer_##scope##Stack
#define	SCOPE_TOP(scope)    ctx->puiLexer_##scope##Top
#define	SCOPE_SIZE(scope)		ctx->puiLexer_##scope##Stack_limit
#define SCOPE_INSTANCE(scope, i)	(ctx->SCOPE_STACK(scope)->get(ctx->SCOPE_STACK(scope),i))


/* Macros for accessing things in a lexer
 */
#undef	    LEXER
#undef	    RECOGNIZER
#undef	    RULEMEMO
#undef	    GETCHARINDEX
#undef	    GETLINE
#undef	    GETCHARPOSITIONINLINE
#undef	    EMIT
#undef	    EMITNEW
#undef	    MATCHC
#undef	    MATCHS
#undef	    MATCHRANGE
#undef	    LTOKEN
#undef	    HASFAILED
#undef	    FAILEDFLAG
#undef	    INPUT
#undef	    STRSTREAM
#undef	    LA
#undef	    HASEXCEPTION
#undef	    EXCEPTION
#undef	    CONSTRUCTEX
#undef	    CONSUME
#undef	    LRECOVER
#undef	    MARK
#undef	    REWIND
#undef	    REWINDLAST
#undef	    BACKTRACKING
#undef		MATCHANY
#undef		MEMOIZE
#undef		HAVEPARSEDRULE
#undef		GETTEXT
#undef		INDEX
#undef		SEEK
#undef		PUSHSTREAM
#undef		POPSTREAM
#undef		SETTEXT
#undef		SETTEXT8

#define	    LEXER					ctx->pLexer
#define	    RECOGNIZER			    LEXER->rec
#define		LEXSTATE				RECOGNIZER->state
#define		TOKSOURCE				LEXSTATE->tokSource
#define	    GETCHARINDEX()			LEXER->getCharIndex(LEXER)
#define	    GETLINE()				LEXER->getLine(LEXER)
#define	    GETTEXT()				LEXER->getText(LEXER)
#define	    GETCHARPOSITIONINLINE() LEXER->getCharPositionInLine(LEXER)
#define	    EMIT()					LEXSTATE->type = _type; LEXER->emit(LEXER)
#define	    EMITNEW(t)				LEXER->emitNew(LEXER, t)
#define	    MATCHC(c)				LEXER->matchc(LEXER, c)
#define	    MATCHS(s)				LEXER->matchs(LEXER, s)
#define	    MATCHRANGE(c1,c2)	    LEXER->matchRange(LEXER, c1, c2)
#define	    MATCHANY()				LEXER->matchAny(LEXER)
#define	    LTOKEN  				LEXSTATE->token
#define	    HASFAILED()				(LEXSTATE->failed == ANTLR3_TRUE)
#define	    BACKTRACKING			LEXSTATE->backtracking
#define	    FAILEDFLAG				LEXSTATE->failed
#define	    INPUT					LEXER->input
#define	    STRSTREAM				INPUT
#define		ISTREAM					INPUT->istream
#define		INDEX()					ISTREAM->index(ISTREAM)
#define		SEEK(n)					ISTREAM->seek(ISTREAM, n)
#define	    EOF_TOKEN				&(LEXSTATE->tokSource->eofToken)
#define	    HASEXCEPTION()			(LEXSTATE->error == ANTLR3_TRUE)
#define	    EXCEPTION				LEXSTATE->exception
#define	    CONSTRUCTEX()			RECOGNIZER->exConstruct(RECOGNIZER)
#define	    LRECOVER()				LEXER->recover(LEXER)
#define	    MARK()					ISTREAM->mark(ISTREAM)
#define	    REWIND(m)				ISTREAM->rewind(ISTREAM, m)
#define	    REWINDLAST()			ISTREAM->rewindLast(ISTREAM)
#define		MEMOIZE(ri,si)			RECOGNIZER->memoize(RECOGNIZER, ri, si)
#define		HAVEPARSEDRULE(r)		RECOGNIZER->alreadyParsedRule(RECOGNIZER, r)
#define		PUSHSTREAM(str)			LEXER->pushCharStream(LEXER, str)
#define		POPSTREAM()				LEXER->popCharStream(LEXER)
#define		SETTEXT(str)			LEXSTATE->text = str
#define		SKIP()					LEXSTATE->token = &(TOKSOURCE->skipToken)
#define		USER1					LEXSTATE->user1
#define		USER2					LEXSTATE->user2
#define		USER3					LEXSTATE->user3
#define		CUSTOM					LEXSTATE->custom
#define		RULEMEMO				LEXSTATE->ruleMemo
#define		DBG						RECOGNIZER->debugger

/* If we have been told we can rely on the standard 8 bit or UTF16 input
 * stream, then we can define our macros to use the direct pointers
 * in the input object, which is much faster than indirect calls. This
 * is really only significant to lexers with a lot of fragment rules (which
 * do not place LA(1) in a temporary at the moment) and even then
 * only if there is a lot of input (order of say 1M or so).
 */
#if	defined(ANTLR3_INLINE_INPUT_8BIT) || defined(ANTLR3_INLINE_INPUT_UTF16)

# ifdef	ANTLR3_INLINE_INPUT_8BIT

/* 8 bit character set */

#  define	    NEXTCHAR	((pANTLR3_UINT8)(INPUT->nextChar))
#  define	    DATAP	((pANTLR3_UINT8)(INPUT->data))

# else

#  define	    NEXTCHAR	((pANTLR3_UINT16)(INPUT->nextChar))
#  define	    DATAP	((pANTLR3_UINT16)(INPUT->data))

# endif

# define	    LA(n) ((NEXTCHAR + n) > (DATAP + INPUT->sizeBuf) ? ANTLR3_CHARSTREAM_EOF : (ANTLR3_UCHAR)(*(NEXTCHAR + n - 1)))
# define            CONSUME()                                           \
{                                                                       \
    if        (NEXTCHAR < (DATAP + INPUT->sizeBuf))                     \
    {                                                                   \
        INPUT->charPositionInLine++;                                    \
        if  ((ANTLR3_UCHAR)(*NEXTCHAR) == INPUT->newlineChar)           \
        {                                                               \
            INPUT->line++;                                              \
            INPUT->charPositionInLine        = 0;                       \
            INPUT->currentLine                = (void *)(NEXTCHAR + 1); \
        }                                                               \
        INPUT->nextChar = (void *)(NEXTCHAR + 1);                       \
    }                                                                   \
}

#else

// Pick up the input character by calling the input stream implementation.
//
#define	    CONSUME()   INPUT->istream->consume(INPUT->istream)
#define	    LA(n)       INPUT->istream->_LA(INPUT->istream, n)

#endif

#define		TOKTEXT(tok, txt)				tok, (pANTLR3_UINT8)txt

/* The 4 tokens defined below may well clash with your own #defines or token types. If so
 * then for the present you must use different names for your defines as these are hard coded
 * in the code generator. It would be better not to use such names internally, and maybe
 * we can change this in a forthcoming release. I deliberately do not #undef these
 * here as this will at least give you a redefined error somewhere if they clash.
 */
#define	    UP	    ANTLR3_TOKEN_UP
#define	    DOWN    ANTLR3_TOKEN_DOWN
#define	    EOR	    ANTLR3_TOKEN_EOR
#define	    INVALID ANTLR3_TOKEN_INVALID


/* =============================================================================
 * Functions to create and destroy scopes. First come the rule scopes, followed
 * by the global declared scopes.
 */



/* ============================================================================= */

/* =============================================================================
 * Start of recognizer
 */

/* Forward declare the locally static matching functions we have generated and any predicate functions.
 */
static ANTLR3_INLINE 
 void
	mDIV    (puiLexer ctx);
static ANTLR3_INLINE 
 void
	mMINUS    (puiLexer ctx);
static ANTLR3_INLINE 
 void
	mMULT    (puiLexer ctx);
static ANTLR3_INLINE 
 void
	mPLUS    (puiLexer ctx);
static ANTLR3_INLINE 
 void
	mNUMBER    (puiLexer ctx);
static ANTLR3_INLINE 
 void
	mWHITESPACE    (puiLexer ctx);
static ANTLR3_INLINE 
 void
	mDIGIT    (puiLexer ctx);
static ANTLR3_INLINE 
 void
	mTokens    (puiLexer ctx);
static void	uiLexerFree(puiLexer ctx);

/* =========================================================================
 * Lexer matching rules end.
 * =========================================================================
 */



static void
uiLexerFree  (puiLexer ctx)
{
    LEXER->free(LEXER);

    ANTLR3_FREE(ctx);
}

static void
uiLexerReset (puiLexer ctx)
{
    RECOGNIZER->reset(RECOGNIZER);
}

/** \brief Name of the grammar file that generated this code
 */
static const char fileName[] = "/Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g";

/** \brief Return the name of the grammar file that generated this code.
 */
static const char * getGrammarFileName()
{
	return fileName;
}

/** \brief Create a new lexer called uiLexer
 *
 * \param[in]    instream Pointer to an initialized input stream
 * \return
 *     - Success puiLexer initialized for the lex start
 *     - Fail NULL
 */
ANTLR3_API puiLexer uiLexerNew
(
pANTLR3_INPUT_STREAM
 instream)
{
	// See if we can create a new lexer with the standard constructor
	//
	return uiLexerNewSSD(instream, NULL);
}

/** \brief Create a new lexer called uiLexer
 *
 * \param[in]    instream Pointer to an initialized input stream
 * \param[state] state Previously created shared recognizer stat
 * \return
 *     - Success puiLexer initialized for the lex start
 *     - Fail NULL
 */
ANTLR3_API puiLexer uiLexerNewSSD
(pANTLR3_INPUT_STREAM instream, pANTLR3_RECOGNIZER_SHARED_STATE state)
{
    puiLexer ctx; // Context structure we will build and return

    ctx = (puiLexer) ANTLR3_CALLOC(1, sizeof(uiLexer));

    if  (ctx == NULL)
    {
        // Failed to allocate memory for lexer context
        return  NULL;
    }

    /* -------------------------------------------------------------------
     * Memory for basic structure is allocated, now to fill in
     * in base ANTLR3 structures. We initialize the function pointers
     * for the standard ANTLR3 lexer function set, but upon return
     * from here, the programmer may set the pointers to provide custom
     * implementations of each function.
     *
     * We don't use the macros defined in uiLexer.h here so you can get a sense
     * of what goes where.
     */

    /* Create a base lexer, using the supplied input stream
     */
    ctx->pLexer	= antlr3LexerNewStream(ANTLR3_SIZE_HINT, instream, state);

    /* Check that we allocated the memory correctly
     */
    if	(ctx->pLexer == NULL)
    {
		ANTLR3_FREE(ctx);
		return  NULL;
    }
    /* Install the implementation of our uiLexer interface
     */
    ctx->mDIV	= mDIV;
    ctx->mMINUS	= mMINUS;
    ctx->mMULT	= mMULT;
    ctx->mPLUS	= mPLUS;
    ctx->mNUMBER	= mNUMBER;
    ctx->mWHITESPACE	= mWHITESPACE;
    ctx->mDIGIT	= mDIGIT;
    ctx->mTokens	= mTokens;

    /** When the nextToken() call is made to this lexer's pANTLR3_TOKEN_SOURCE
     *  it will call mTokens() in this generated code, and will pass it the ctx
     * pointer of this lexer, not the context of the base lexer, so store that now.
     */
    ctx->pLexer->ctx	    = ctx;

    /**Install the token matching function
     */
    ctx->pLexer->mTokens = (void (*) (void *))(mTokens);

    ctx->getGrammarFileName	= getGrammarFileName;
    ctx->free		= uiLexerFree;
    ctx->reset          = uiLexerReset;


    /* Return the newly built lexer to the caller
     */
    return  ctx;
}
/* =========================================================================
 * Functions to match the lexer grammar defined tokens from the input stream
 */

//   Comes from: 11:5: ( '/' )
/** \brief Lexer rule generated by ANTLR3
 *
 * $ANTLR start DIV
 *
 * Looks to match the characters the constitute the token DIV
 * from the attached input stream.
 *
 *
 * \remark
 *  - lexer->error == ANTLR3_TRUE if an exception was thrown.
 */
static ANTLR3_INLINE
void mDIV(puiLexer ctx)
{
	ANTLR3_UINT32	_type;

    _type	    = DIV;


    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:11:5: ( '/' )
    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:11:7: '/'
    {
        MATCHC('/');
        if  (HASEXCEPTION())
        {
            goto ruleDIVEx;
        }


    }

	LEXSTATE->type = _type;
    // This is where rules clean up and exit
    //
    goto ruleDIVEx; /* Prevent compiler warnings */
    ruleDIVEx: ;

}
// $ANTLR end DIV

//   Comes from: 12:7: ( '-' )
/** \brief Lexer rule generated by ANTLR3
 *
 * $ANTLR start MINUS
 *
 * Looks to match the characters the constitute the token MINUS
 * from the attached input stream.
 *
 *
 * \remark
 *  - lexer->error == ANTLR3_TRUE if an exception was thrown.
 */
static ANTLR3_INLINE
void mMINUS(puiLexer ctx)
{
	ANTLR3_UINT32	_type;

    _type	    = MINUS;


    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:12:7: ( '-' )
    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:12:9: '-'
    {
        MATCHC('-');
        if  (HASEXCEPTION())
        {
            goto ruleMINUSEx;
        }


    }

	LEXSTATE->type = _type;
    // This is where rules clean up and exit
    //
    goto ruleMINUSEx; /* Prevent compiler warnings */
    ruleMINUSEx: ;

}
// $ANTLR end MINUS

//   Comes from: 13:6: ( '*' )
/** \brief Lexer rule generated by ANTLR3
 *
 * $ANTLR start MULT
 *
 * Looks to match the characters the constitute the token MULT
 * from the attached input stream.
 *
 *
 * \remark
 *  - lexer->error == ANTLR3_TRUE if an exception was thrown.
 */
static ANTLR3_INLINE
void mMULT(puiLexer ctx)
{
	ANTLR3_UINT32	_type;

    _type	    = MULT;


    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:13:6: ( '*' )
    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:13:8: '*'
    {
        MATCHC('*');
        if  (HASEXCEPTION())
        {
            goto ruleMULTEx;
        }


    }

	LEXSTATE->type = _type;
    // This is where rules clean up and exit
    //
    goto ruleMULTEx; /* Prevent compiler warnings */
    ruleMULTEx: ;

}
// $ANTLR end MULT

//   Comes from: 14:6: ( '+' )
/** \brief Lexer rule generated by ANTLR3
 *
 * $ANTLR start PLUS
 *
 * Looks to match the characters the constitute the token PLUS
 * from the attached input stream.
 *
 *
 * \remark
 *  - lexer->error == ANTLR3_TRUE if an exception was thrown.
 */
static ANTLR3_INLINE
void mPLUS(puiLexer ctx)
{
	ANTLR3_UINT32	_type;

    _type	    = PLUS;


    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:14:6: ( '+' )
    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:14:8: '+'
    {
        MATCHC('+');
        if  (HASEXCEPTION())
        {
            goto rulePLUSEx;
        }


    }

	LEXSTATE->type = _type;
    // This is where rules clean up and exit
    //
    goto rulePLUSEx; /* Prevent compiler warnings */
    rulePLUSEx: ;

}
// $ANTLR end PLUS

//   Comes from: 39:9: ( ( DIGIT )+ )
/** \brief Lexer rule generated by ANTLR3
 *
 * $ANTLR start NUMBER
 *
 * Looks to match the characters the constitute the token NUMBER
 * from the attached input stream.
 *
 *
 * \remark
 *  - lexer->error == ANTLR3_TRUE if an exception was thrown.
 */
static ANTLR3_INLINE
void mNUMBER(puiLexer ctx)
{
	ANTLR3_UINT32	_type;

    _type	    = NUMBER;


    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:39:9: ( ( DIGIT )+ )
    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:39:11: ( DIGIT )+
    {
        // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:39:11: ( DIGIT )+
        {
            int cnt1=0;

            for (;;)
            {
                int alt1=2;
        	switch ( LA(1) )
        	{
        	case '0':
        	case '1':
        	case '2':
        	case '3':
        	case '4':
        	case '5':
        	case '6':
        	case '7':
        	case '8':
        	case '9':
        		{
        			alt1=1;
        		}
        	    break;

        	}

        	switch (alt1)
        	{
        	    case 1:
        	        // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:
        	        {
        	            if ( ((LA(1) >= '0') && (LA(1) <= '9')) )
        	            {
        	                CONSUME();
        	            }
        	            else
        	            {
        	                CONSTRUCTEX();
        	                EXCEPTION->type         = ANTLR3_MISMATCHED_SET_EXCEPTION;
        	                EXCEPTION->name         = (void *)ANTLR3_MISMATCHED_SET_NAME;

        	                LRECOVER();
        	                goto ruleNUMBEREx;
        	            }


        	        }
        	        break;

        	    default:

        		if ( cnt1 >= 1 )
        		{
        		    goto loop1;
        		}
        		/* mismatchedSetEx()
        		 */
        		CONSTRUCTEX();
        		EXCEPTION->type = ANTLR3_EARLY_EXIT_EXCEPTION;
        		EXCEPTION->name = (void *)ANTLR3_EARLY_EXIT_NAME;


        		goto ruleNUMBEREx;
        	}
        	cnt1++;
            }
            loop1: ;	/* Jump to here if this rule does not match */
        }

    }

	LEXSTATE->type = _type;
    // This is where rules clean up and exit
    //
    goto ruleNUMBEREx; /* Prevent compiler warnings */
    ruleNUMBEREx: ;

}
// $ANTLR end NUMBER

//   Comes from: 41:12: ( ( '\\t' | ' ' | '\\r' | '\\n' | '\\u000C' )+ )
/** \brief Lexer rule generated by ANTLR3
 *
 * $ANTLR start WHITESPACE
 *
 * Looks to match the characters the constitute the token WHITESPACE
 * from the attached input stream.
 *
 *
 * \remark
 *  - lexer->error == ANTLR3_TRUE if an exception was thrown.
 */
static ANTLR3_INLINE
void mWHITESPACE(puiLexer ctx)
{
	ANTLR3_UINT32	_type;

    _type	    = WHITESPACE;


    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:41:12: ( ( '\\t' | ' ' | '\\r' | '\\n' | '\\u000C' )+ )
    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:41:14: ( '\\t' | ' ' | '\\r' | '\\n' | '\\u000C' )+
    {
        // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:41:14: ( '\\t' | ' ' | '\\r' | '\\n' | '\\u000C' )+
        {
            int cnt2=0;

            for (;;)
            {
                int alt2=2;
        	switch ( LA(1) )
        	{
        	case '\t':
        	case '\n':
        	case '\f':
        	case '\r':
        	case ' ':
        		{
        			alt2=1;
        		}
        	    break;

        	}

        	switch (alt2)
        	{
        	    case 1:
        	        // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:
        	        {
        	            if ( ((LA(1) >= '\t') && (LA(1) <= '\n')) || ((LA(1) >= '\f') && (LA(1) <= '\r')) || LA(1) == ' ' )
        	            {
        	                CONSUME();
        	            }
        	            else
        	            {
        	                CONSTRUCTEX();
        	                EXCEPTION->type         = ANTLR3_MISMATCHED_SET_EXCEPTION;
        	                EXCEPTION->name         = (void *)ANTLR3_MISMATCHED_SET_NAME;

        	                LRECOVER();
        	                goto ruleWHITESPACEEx;
        	            }


        	        }
        	        break;

        	    default:

        		if ( cnt2 >= 1 )
        		{
        		    goto loop2;
        		}
        		/* mismatchedSetEx()
        		 */
        		CONSTRUCTEX();
        		EXCEPTION->type = ANTLR3_EARLY_EXIT_EXCEPTION;
        		EXCEPTION->name = (void *)ANTLR3_EARLY_EXIT_NAME;


        		goto ruleWHITESPACEEx;
        	}
        	cnt2++;
            }
            loop2: ;	/* Jump to here if this rule does not match */
        }

        {
             LEXSTATE->channel = Hidden; 
        }


    }

	LEXSTATE->type = _type;
    // This is where rules clean up and exit
    //
    goto ruleWHITESPACEEx; /* Prevent compiler warnings */
    ruleWHITESPACEEx: ;

}
// $ANTLR end WHITESPACE

//   Comes from: 43:17: ( '0' .. '9' )
/** \brief Lexer rule generated by ANTLR3
 *
 * $ANTLR start DIGIT
 *
 * Looks to match the characters the constitute the token DIGIT
 * from the attached input stream.
 *
 *
 * \remark
 *  - lexer->error == ANTLR3_TRUE if an exception was thrown.
 */
static ANTLR3_INLINE
void mDIGIT(puiLexer ctx)
{
	ANTLR3_UINT32	_type;


    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:43:17: ( '0' .. '9' )
    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:
    {
        if ( ((LA(1) >= '0') && (LA(1) <= '9')) )
        {
            CONSUME();
        }
        else
        {
            CONSTRUCTEX();
            EXCEPTION->type         = ANTLR3_MISMATCHED_SET_EXCEPTION;
            EXCEPTION->name         = (void *)ANTLR3_MISMATCHED_SET_NAME;

            LRECOVER();
            goto ruleDIGITEx;
        }


    }


    // This is where rules clean up and exit
    //
    goto ruleDIGITEx; /* Prevent compiler warnings */
    ruleDIGITEx: ;

}
// $ANTLR end DIGIT

/** This is the entry point in to the lexer from an object that
 *  wants to generate the next token, such as a pCOMMON_TOKEN_STREAM
 */
static void
mTokens(puiLexer ctx)
{
    {
        //  /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:1:8: ( DIV | MINUS | MULT | PLUS | NUMBER | WHITESPACE )

        ANTLR3_UINT32 alt3;

        alt3=6;

        switch ( LA(1) )
        {
        case '/':
        	{
        		alt3=1;
        	}
            break;
        case '-':
        	{
        		alt3=2;
        	}
            break;
        case '*':
        	{
        		alt3=3;
        	}
            break;
        case '+':
        	{
        		alt3=4;
        	}
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        	{
        		alt3=5;
        	}
            break;
        case '\t':
        case '\n':
        case '\f':
        case '\r':
        case ' ':
        	{
        		alt3=6;
        	}
            break;

        default:
            CONSTRUCTEX();
            EXCEPTION->type         = ANTLR3_NO_VIABLE_ALT_EXCEPTION;
            EXCEPTION->message      = (void *)"";
            EXCEPTION->decisionNum  = 3;
            EXCEPTION->state        = 0;


            goto ruleTokensEx;

        }

        switch (alt3)
        {
    	case 1:
    	    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:1:10: DIV
    	    {
    	        /* 1:10: DIV */
    	        mDIV(ctx );
    	        if  (HASEXCEPTION())
    	        {
    	            goto ruleTokensEx;
    	        }



    	    }
    	    break;
    	case 2:
    	    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:1:14: MINUS
    	    {
    	        /* 1:14: MINUS */
    	        mMINUS(ctx );
    	        if  (HASEXCEPTION())
    	        {
    	            goto ruleTokensEx;
    	        }



    	    }
    	    break;
    	case 3:
    	    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:1:20: MULT
    	    {
    	        /* 1:20: MULT */
    	        mMULT(ctx );
    	        if  (HASEXCEPTION())
    	        {
    	            goto ruleTokensEx;
    	        }



    	    }
    	    break;
    	case 4:
    	    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:1:25: PLUS
    	    {
    	        /* 1:25: PLUS */
    	        mPLUS(ctx );
    	        if  (HASEXCEPTION())
    	        {
    	            goto ruleTokensEx;
    	        }



    	    }
    	    break;
    	case 5:
    	    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:1:30: NUMBER
    	    {
    	        /* 1:30: NUMBER */
    	        mNUMBER(ctx );
    	        if  (HASEXCEPTION())
    	        {
    	            goto ruleTokensEx;
    	        }



    	    }
    	    break;
    	case 6:
    	    // /Users/lothar/develop/Projects/CPP/Plugins/DomainLanguages/lbUILanguage/ui.g:1:37: WHITESPACE
    	    {
    	        /* 1:37: WHITESPACE */
    	        mWHITESPACE(ctx );
    	        if  (HASEXCEPTION())
    	        {
    	            goto ruleTokensEx;
    	        }



    	    }
    	    break;

        }
    }


    goto ruleTokensEx; /* Prevent compiler warnings */
ruleTokensEx: ;
}

/* =========================================================================
 * Lexer matching rules end.
 * =========================================================================
 */
/* End of Lexer code
 * ================================================
 * ================================================
 */


/* End of code
 * =============================================================================
 */
