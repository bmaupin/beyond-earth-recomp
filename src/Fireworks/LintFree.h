#ifndef _INCLUDED_LintFree_H
#define _INCLUDED_LintFree_H
//------------------------------------------------------------------------------------------------
//
//  *****************   FIRAXIS GAME ENGINE   ********************
//
//  FILE:    LintFree.h
//
//  AUTHOR:  Justin Randall  --  2010 August 16
//
//  PURPOSE: Upgrade warnings to errors for files that claim to be lint-free to prevent new errors
//           from creeping back into the code.
//
//  USAGE:   Add lint checks to either LINT_WARNINGS or LINT_CODE_ANALYSIS to eliminate problem
//           code. Include this header file in de-linted files to ensure they stay lint-free. In
//           the rare case a warning needs to be supressed, do it inline in the file with an
//           explaination describing why supression was the only option:
//             const T& operator []( uint i ) const
//             {
//             	   assert( i < ARRAY_SIZE );
//                 #ifdef _MSC_VER
//                     // It is the caller's responsibility to ensure
//                     // the index is valid.
//                     #pragma warning ( suppress : 6385 )
//                 #endif
//             	   return ( m_akItems[ i ] );
//             }
//
//------------------------------------------------------------------------------------------------
//  Copyright (c) 2003-2006 Firaxis Games, Inc. All rights reserved.
//------------------------------------------------------------------------------------------------

#ifdef _MSC_VER

#define LINT_WARNINGS \
	4100 /* unreferenced formal parameter */ \
	4130 /* logical operation on address of a string constant */ \
	4189 /* local variable is initialized but not referenced */ \
	4239 /* nonstandard extension used */ \
	4238 /* nonstandard extension used : class rvalue used as lvalue */ \
	4505 /* unreferenced local function has been removed */ \
	4512 /* assignment operator could not be generated */ \
	4702 /* unreachable code */ \
	4706 /* assignment within conditional expression */

#define LINT_CODE_ANALYSIS \
	6001 /* Using uninitialized memory */ \
	6011 /* dereferencing NULL pointer.  */ \
	6246 /* Local declaration of 'variable' hides declaration of the same name in outer scope. Consider using the previous declaration. */ \
	6262 /* Function uses excessive stack. Consider moving some data to heap. */ \
	6302 /* Format string mismatch */ \
	6385 /* Invalid buffer access */ \
	6386 /* Buffer overrun */

#define LINT_SUPPRESSIONS \
	6255 /* _alloca indicates failure by raising a stack overflow exception. Consider using _malloca instead */ \
	6326 /* Potential comparison of a constant with another constant */

#	pragma warning ( 1 : LINT_WARNINGS )
#	ifndef FINAL_RELEASE
#		ifndef LINT_WARNINGS_ONLY
#			pragma warning ( error : LINT_WARNINGS LINT_CODE_ANALYSIS )
#		endif//LINT_WARNINGS_ONLY
#	endif//FINAL_RELEASE
#	pragma warning ( disable : LINT_SUPPRESSIONS )
#	ifdef LINT_EXTRA_SUPPRESSIONS
#		pragma warning ( disable : LINT_EXTRA_SUPPRESSIONS )
#	endif//LINT_EXTRA_SUPPRESSIONS
#endif

#endif//_INCLUDED_LintFree_H
