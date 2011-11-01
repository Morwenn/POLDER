////////////////////////////////////////////////////////////
///
/// POLDER Evaluate - POLDER library evaluating mathematical expressions
/// Written by Morwenn Edrahir, 2011
///
////////////////////////////////////////////////////////////

#ifndef _POLDER_EVALUATE_H
#define _POLDER_EVALUATE_H

////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <vector>
#include "math.h"
#include "ptype.h"
#include "string.h"


////////////////////////////////////////////////////////////
/// Aliases
////////////////////////////////////////////////////////////
#ifndef _eval
    #define _eval polder::evaluate
#endif
#ifndef eval
    #define eval polder::evaluate
#endif


////////////////////////////////////////////////////////////
/// Constants
////////////////////////////////////////////////////////////

#define OP_ERROR 0

// Supported binary operators
#define OP_EQ 1      // ==
#define OP_NE 2      // !=, <>
#define OP_GE 3      // >=
#define OP_LE 4      // <=
#define OP_AND 5     // &&
#define OP_OR 6      // ||
#define OP_XOR 7     // ^
#define OP_POW 8     // **
#define OP_SPACE 9   // <=>
#define OP_LSHIFT 10 // <<
#define OP_RSHIFT 11 // >>
#define OP_ADD 12    // +
#define OP_SUB 13    // -
#define OP_MUL 14    // *
#define OP_DIV 15    // /
#define OP_MOD 16    // %
#define OP_BAND 17   // &
#define OP_BOR 18    // |
#define OP_GT 19     // >
#define OP_LT 20     // <
#define OP_BXOR 21   // ^^
#define OP_IDIV 22   // //

// Supported unary operators
#define UOP_SUB -1   // - (Unary minus, prefix)
#define UOP_NOT -2   // ! (Logical NOT, prefix)
#define UOP_BNOT -3  // ~ (Bitwise NOT, prefix)
#define UOP_FAC -101 // ! (Factorial, postfix)


namespace polder
{

////////////////////////////////////////////////////////////
/// Elements
////////////////////////////////////////////////////////////

// Error types
enum class eval_error
{
    UNKNOWN = 0,
    UNKNOWN_OPERATOR,
    UNEXPECTED_CHAR,
    LAST_CHARACTER,
    INVALID_NUMBER,
    MISSING_CHAR,
    SYNTAX
};

// Element types
enum class elem_t
{
    NONE = 0,
    OPERAND,
    OPERATOR,
    PREFIX,
    POSTFIX,
    PARENTHESIS
};

// Element structure
typedef struct Elem
{
    double data;
    elem_t type;
    //Elem* prev;
} Elem;
//typedef Elem* Stack;


////////////////////////////////////////////////////////////
/// Functions
////////////////////////////////////////////////////////////

// Evaluation function
double evaluate(const char* expr);


} // namespace polder


#endif
