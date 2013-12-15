/*
 * Copyright (C) 2011-2013 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program. If not,
 * see <http://www.gnu.org/licenses/>.
 */
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <stack>
#include <vector>
#include <POLDER/evaluate.h>
#include <POLDER/string.h>
#include <POLDER/stype.h>
#include <POLDER/math/factorial.h>


namespace polder
{

namespace
{

    ////////////////////////////////////////////////////////////
    // Constants
    ////////////////////////////////////////////////////////////

    // Supported operators
    enum op_t: int
    {
        ERROR = -1,

        // Supported binary operators
        EQ = 0,     // ==
        NE,         // !=, <>
        GE,         // >=
        LE,         // <=
        AND,        // &&
        OR,         // ||
        XOR,        // ^
        POW,        // **
        SPACE,      // <=>
        LSHIFT,     // <<
        RSHIFT,     // >>
        ADD,        // +
        SUB,        // -
        MUL,        // *
        DIV,        // /
        MOD,        // %
        BAND,       // &
        BOR,        // |
        GT,         // >
        LT,         // <
        BXOR,       // ^^
        IDIV,       // //
        ASSIGN,     // =
        NB_BINARY_OPERATORS,

        // Supported prefix unary operators
        USUB,       // - (Unary minus)
        NOT,        // ! (Logical NOT)
        BNOT,       // ~ (Bitwise NOT)

        // Supported postfix unary operators
        FAC         // ! (Factorial)
    };

    // Binary operators priority
    // The priority of unary operators is
    // determined by their position
    constexpr unsigned int _priority[NB_BINARY_OPERATORS] = {
        7,   // ==
        7,   // !=, <>
        8,   // >=
        8,   // <=
        3,   // &&
        1,   // ||
        2,   // ^
        12,  // **
        7,   // <=>
        9,   // <<
        9,   // >>
        10,  // +
        10,  // -
        11,  // *
        11,  // /
        11,  // %
        6,   // &
        4,   // |
        8,   // >
        8,   // <
        5,   // ^^
        11,  // //
        0,   // =
    };


    // Element types
    enum struct elem_t
    {
        NONE,
        OPERAND,
        OPERATOR,
        PREFIX,
        POSTFIX,
        PARENTHESIS
    };

    // Element structure
    struct Token
    {
        // The element can be
        union
        {
            char par;       // A parenthesis
            op_t op;        // A binary operator
            double data;    // A real value
        };
        elem_t type;
    };
}


// Expression handling
static void expr_norm(char* str);
static std::vector<Token> tokenize(const char* expr);
static std::stack<Token> postfix(const std::vector<Token>& vec);
static double eval_postfix(std::stack<Token>&& S);

// Miscellaneous
static Token op_value(const char* op);
static Token operation(double a, op_t op);
static Token operation(double a, double b, op_t op);
static int priority(const Token& E);

// Type checking
static bool is_operand(const Token& E);
static bool is_operator(const Token& E);
static bool is_prefix(const Token& E);
static bool is_postfix(const Token& E);


using namespace std;

////////////////////////////////////////////////////////////
// Evaluation function
////////////////////////////////////////////////////////////

double evaluate(const char* expr)
{
    char* expr_copy = new char[2*strlen(expr)+1];
    strcpy(expr_copy, expr);
    expr_norm(expr_copy);
    const vector<Token> vec = tokenize(expr_copy); // Split the string into elements
    delete[] expr_copy;
    return eval_postfix(postfix(vec));            // Order the elements and evaluate the expression
}


////////////////////////////////////////////////////////////
// Expression handling functions
////////////////////////////////////////////////////////////

/* Add/remove spaces in the expression so that it will be easier to split it
   Also returns an error when reading an unexpected character. */
void expr_norm(char* str)
{
    char* new_str = new char[2*strlen(str)+1];

    // Number of parenthesis
    int nmb_parenthesis = 0;

    std::size_t count = 0;
    for (std::size_t i = 0 ; str[i] ; ++i)
    {
        switch (str[i])
        {
            // Characters always used alone
            case ')':
            {
                if (nmb_parenthesis == 0)
                {
                    throw evaluation_error("trying to close a non-opened parenthesis");
                }
                // Substract 2 so that it compenses that addition done after
                nmb_parenthesis -= 2;
            }
            case '(': ++nmb_parenthesis;
            case '%':
            case '~':
            {
                if (!isspace(new_str[count-1]) && count > 0)
                {
                    new_str[count++] = ' ';
                }
                new_str[count++] = str[i];
                new_str[count++] = ' ';
                break;
            }
            // Characters used alone or with an equivalent
            case '*': // "*" or "**"
            case '&': // "&" or "&&"
            case '|': // "|" or "||"
            case '^': // "^" or "^^"
            case '/': // "/" or "//"
            {
                if (!isspace(new_str[count-1]) && new_str[count-1] != str[i])
                {
                    new_str[count++] = ' ';
                }
                new_str[count++] = str[i];
                if (str[i+1] != str[i])
                {
                    new_str[count++] = ' ';
                }
                break;
            }
            case '+': // Can be unary or binary
            {
                // Check whether the '+' is unary or not
                int j = count;
                while (--j >= 0 && isspace(new_str[j])); // Previous character
                if (j >= 0 && (isdigit(new_str[j]) || new_str[j] == '.' || new_str[j] == '!' || new_str[j] == ')'))
                {
                    // If '+' is not unary
                    if (!isspace(new_str[count-1]) && count > 0)
                    {
                        new_str[count++] = ' ';
                    }
                    new_str[count++] = '+';
                    new_str[count++] = ' ';
                }
                // else it is ignored
                break;
            }
            case '-': // Can be unary or not
            {
                if (!isspace(new_str[count-1]) && i > 0)
                {
                    new_str[count++] = ' ';
                }

                // Check whether the '-' is unary or not
                int j = i; int k = i;
                while (--j >= 0 && isspace(str[j])); // Previous character
                if (j < 0 || str[j] == '(')
                {
                    // This '-' is unary
                    while (isspace(str[++k])); // Following character
                    if (str[k] == '(')
                    {
                        // We add '$' before the symbol to tell it is an unary symbol
                        new_str[count++] = '$';
                        new_str[count++] = '-';
                        new_str[count++] = ' ';
                    }
                    else if (!isdigit(str[k]) && str[k] != '.')
                    {
                        throw evaluation_error();
                    }
                    else
                    {
                        new_str[count++] = '-';
                    }
                }
                else
                {
                    new_str[count++] = '-';
                    new_str[count++] = ' ';
                }
                break;
            }
            case '=': // Used in "==", "!=", ">=", "<=" and "<=>"
            {
                if (!isspace(new_str[count-1]) && str[i+1] == '=')
                {
                    new_str[count++] = ' ';
                }
                new_str[count++] = '=';
                if (str[i+1] != '>' && str[i+1] != '=')
                {
                    new_str[count++] = ' ';
                }
                break;
            }
            case '<': // Used alone and in "<=", "<=>", "<<" and "<>"
            {
                if (!isspace(new_str[count-1]) && new_str[count-1] != '<')
                {
                    new_str[count++] = ' ';
                }
                new_str[count++] = '<';
                if (str[i+1] != '<' && str[i+1] != '>' && str[i+1] != '=')
                {
                    new_str[count++] = ' ';
                }
                break;
            }
            case '>': // Used alone and in ">=", "<=>", ">>" and "<>"
            {
                if (!isspace(new_str[count-1]) && new_str[count-1] != '<' && new_str[count-1] != '>' && new_str[count-1] != '=')
                {
                    new_str[count++] = ' ';
                }
                new_str[count++] = '>';
                if (str[i+1] != '=' && str[i+1] != '>')
                {
                    new_str[count++] = ' ';
                }
                break;
            }
            case '!': // Used alone (as prefix or postfix) and in "!="
            {
                if (!isspace(new_str[count-1]) && count > 0)
                {
                    new_str[count++] = ' ';
                }
                int j = i;
                while (--j >= 0 && (isspace(str[j]) || str[j] == '!')); // Previous character
                if ((isdigit(str[j]) || str[j] == '.' || str[j] == ')') && count > 0)
                {
                    // Can be "!=" or factorial
                    if (str[i+1] == '=' && str[i+2] != '=')
                    {
                        // "!=" symbol
                        new_str[count++] = '!';
                    }
                    else // Factorial, represented by "$!"
                    {
                        new_str[count++] = '$';
                        new_str[count++] = '!';
                        new_str[count++] = ' ';
                    }
                }
                else // Can just be the logical NOT
                {
                    new_str[count++] = '!';
                    new_str[count++] = ' ';
                }
                break;
            }
            case '.':
            {
                if (!isdigit(new_str[count-1]) && !isspace(new_str[count-1]))
                {
                    new_str[count++] = ' ';
                }
                new_str[count++] = '.';
                if (!isdigit(str[i+1]))
                {
                    new_str[count++] = ' ';
                }
                break;
            }
            default:
            {
                if (isdigit(str[i]))
                {
                    new_str[count++] = str[i];
                }
                else if (!isspace(str[i]))
                {
                    throw evaluation_error(_eval_error::UNEXPECTED_CHARACTER, str[i]);
                }
            }
        }
    }

    // Add the ending character
    if (isspace(new_str[count-1]))
    {
        new_str[--count] = '\0';
    }
    else
    {
        new_str[count] = '\0';
    }

    // Check for errors
    if (!isdigit(new_str[--count]) && new_str[count] != '.' && new_str[count] != ')' && new_str[count] != '!')
    {
        throw evaluation_error(_eval_error::LAST_CHARACTER, new_str[count]);
    }

    // Check whether all the parenthesis are closed
    if (nmb_parenthesis)
    {
        throw evaluation_error("there are unclosed parenthesis in the expression");
    }

    strcpy(str, new_str);
    delete[] new_str;
}

// Create a vector of elements with the expression
vector<Token> tokenize(const char* expr)
{
    vector<Token> vec;
    char* word = new char[128];
    Token e;

    strcpy(word, string::read_word_first(expr));
    while (word[0])
    {
        if (word[0] == '(' || word[0] == ')')
        {
            e.type = elem_t::PARENTHESIS;
            e.par = word[0];
        }
        else if (isdigit(word[0]) || word[0] == '.'
            || (word[0] == '-' && (isdigit(word[1]) || word[1] == '.')))
        {
            e.type = elem_t::OPERAND;
            if (stype::is_unumber(word))
            {
                e.data = std::atof(word);
            }
            else
            {
                throw evaluation_error(_eval_error::INVALID_NUMBER, word);
            }
        }
        else
        {
            e = op_value(word);
        }
        vec.push_back(e);
        strcpy(word, string::read_word_next());
    }
    delete[] word;
    return vec;
}

// Create the postfix expression from a vector of elements
stack<Token> postfix(const vector<Token>& vec)
{
    stack<Token> R, P;

    for (const Token& e: vec)
    {
        if (is_operand(e))
        {
            R.push(e);
            while (!P.empty() && is_prefix(P.top()))
            {
                R.push(P.top());
                P.pop();
            }
        }
        else if (is_postfix(e))
        {
            R.push(e);
        }
        else if (is_operator(e))
        {
            while(!P.empty() && is_operator(P.top()) && (priority(e) <= priority(P.top())))
            {
                R.push(P.top());
                P.pop();
            }
            P.push(e);
        }
        else if (e.par == '(' || is_prefix(e))
        {
            P.push(e);
        }
        else // if e.par == ')'
        {
            while (!P.empty() && P.top().par != '(')
            {
                R.push(P.top());
                P.pop();
            }
            P.pop();
            while (!P.empty() && is_prefix(P.top()))
            {
                R.push(P.top());
                P.pop();
            }
        }
    }

    while(!R.empty())
    {
        P.push(R.top());
        R.pop();
    }
    return P;
}

// Evaluate the result with the postfix expression
double eval_postfix(stack<Token>&& S)
{
    Token x, y, e;
    stack<Token> R;

    while (!S.empty())
    {
        e = S.top();
        S.pop();
        if (is_operand(e))
        {
            R.push(e);
        }
        else if (is_operator(e))
        {
            x = R.top();
            R.pop();
            y = R.top();
            R.pop();
            R.push(operation(y.data, x.data, e.op));
        }
        else // if (is_prefix(e) || is_postfix(e))
        {
            x = R.top();
            R.pop();
            R.push(operation(x.data, e.op));
        }
    }
    return R.top().data;
}


////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

// Returns the value corresponding to an operator
Token op_value(const char* op)
{
    Token res;

    if (op[1] == '\0')
    {
        switch (op[0])
        {
            case '+': res.op = op_t::ADD; break;
            case '-': res.op = op_t::SUB; break;
            case '*': res.op = op_t::MUL; break;
            case '<': res.op = op_t::LT; break;
            case '>': res.op = op_t::GT; break;
            case '/': res.op = op_t::DIV; break;
            case '%': res.op = op_t::MOD; break;
            case '&': res.op = op_t::BAND; break;
            case '^': res.op = op_t::BXOR; break;
            case '|': res.op = op_t::BOR; break;
            case '!':
                res.op = op_t::NOT;
                res.type = elem_t::PREFIX;
                return res;
            case '~':
                res.op = op_t::BNOT;
                res.type = elem_t::PREFIX;
                return res;
            default: throw evaluation_error(_eval_error::UNKNOWN_OPERATOR, op);
        }
    }
    else // If op has several characters
    {
        if (!strcmp(op, "=="))
            res.op = op_t::EQ;
        else if (!strcmp(op, "!=") || !strcmp(op, "<>"))
            res.op = op_t::NE;
        else if (!strcmp(op, ">="))
            res.op = op_t::GE;
        else if (!strcmp(op, "<="))
            res.op = op_t::LE;
        else if (!strcmp(op, "&&"))
            res.op = op_t::AND;
        else if (!strcmp(op, "||"))
            res.op = op_t::OR;
        else if (!strcmp(op, "**"))
            res.op = op_t::POW;
        else if (!strcmp(op, "//"))
            res.op = op_t::IDIV;
        else if (!strcmp(op, "<=>"))
            res.op = op_t::SPACE;
        else if (!strcmp(op, "<<"))
            res.op = op_t::LSHIFT;
        else if (!strcmp(op, ">>"))
            res.op = op_t::RSHIFT;
        else if (!strcmp(op, "^^"))
            res.op = op_t::XOR;
        else if (!strcmp(op, "$-"))
        {
            res.op = op_t::USUB;
            res.type = elem_t::PREFIX;
            return res;
        }
        else if (!strcmp(op, "$!"))
        {
            res.op = op_t::FAC;
            res.type = elem_t::POSTFIX;
            return res;
        }
        else
            throw evaluation_error(_eval_error::UNKNOWN_OPERATOR, op);
    }

    // Executed if an element is a binary operator
    res.type = elem_t::OPERATOR;
    return res;
}

// Returns the priority of an operator
int priority(const Token& E)
{
    if (E.op >= 0 && E.op < op_t::NB_BINARY_OPERATORS)
    {
        return _priority[E.op];
    }

    // Should never be executed
    return -1;
}

// Does the operation between two operands
Token operation(double a, double b, op_t op)
{
    Token res;
    res.type = elem_t::OPERAND;

    switch (op)
    {
        case op_t::ADD: res.data = a + b; break;                     // +
        case op_t::SUB: res.data = a - b; break;                     // -
        case op_t::MUL: res.data = a * b; break;                     // *
        case op_t::LT: res.data = a < b; break;                      // <
        case op_t::GT: res.data = a > b; break;                      // >
        case op_t::DIV: res.data = a / b; break;                     // /
        case op_t::IDIV: res.data = (int) a / (int) b; break;        // //
        case op_t::MOD: res.data = (int) a % (int) b; break;         // %
        case op_t::BAND: res.data = (int) a & (int) b; break;        // &
        case op_t::BXOR: res.data = (int) a ^ (int) b; break;        // ^
        case op_t::BOR: res.data = (int) a | (int) b; break;         // |
        case op_t::EQ: res.data = (a == b); break;                   // ==
        case op_t::NE: res.data = (a != b); break;                   // != or <>
        case op_t::GE: res.data = (a >= b); break;                   // >=
        case op_t::LE: res.data = (a <= b); break;                   // <=
        case op_t::AND: res.data = (a && b); break;                  // &&
        case op_t::XOR: res.data = (a && !b) || (b && !a); break;    // ^^
        case op_t::OR: res.data = (a || b); break;                   // ||
        case op_t::POW: res.data = pow(a, b); break;                 // **
        case op_t::SPACE: res.data = (a < b) ? -1 : (a != b); break; // <=>
        case op_t::LSHIFT: res.data = (int) a << (int) b; break;     // <<
        case op_t::RSHIFT: res.data = (int) a >> (int) b; break;     // >>

        // Shoulf never happen
        default: throw evaluation_error();
    }

    // Returns an operand corresponding to the result of the operation
    return res;
}

// Does an unary operation
Token operation(double a, op_t op)
{
    Token res;
    res.type = elem_t::OPERAND;

    switch (op)
    {
        case op_t::USUB: res.data = -a; break;                                  // -
        case op_t::NOT: res.data = !a; break;                                   // ! (prefix)
        case op_t::BNOT: res.data = ~ (int) a; break;                           // ~
        case op_t::FAC: res.data = math::factorial((unsigned int) a); break;    // ! (postfix)

        // Should never happen
        default: throw evaluation_error();
    }

    // Returns an operand corresponding to the result of the operation
    return res;
}


////////////////////////////////////////////////////////////
// Type checking functions
////////////////////////////////////////////////////////////

bool is_operand(const Token& E)
{
    return E.type == elem_t::OPERAND;
}

bool is_operator(const Token& E)
{
    return E.type == elem_t::OPERATOR;
}

bool is_prefix(const Token& E)
{
    return E.type == elem_t::PREFIX;
}

bool is_postfix(const Token& E)
{
    return E.type == elem_t::POSTFIX;
}


////////////////////////////////////////////////////////////
// Exceptions handling
////////////////////////////////////////////////////////////

// Create a new exception
evaluation_error::evaluation_error():
    msg("polder::evaluation_error: undocumented error")
{}

// Create a new exception
evaluation_error::evaluation_error(const std::string& arg):
    msg(std::string("polder::evaluation_error: ") + arg)
{}

// Create a new exception
evaluation_error::evaluation_error(_eval_error e, char c)
{
    ostringstream oss;
    oss << "polder::evaluation_error: ";

    switch (e)
    {
        case _eval_error::UNEXPECTED_CHARACTER:
            oss << "unexpected character '" << c <<"' in the expression";
            break;
        case _eval_error::EXPECTED_CHARACTER:
            oss << "expected character '" << c <<"' in the expression";
            break;
        case _eval_error::LAST_CHARACTER:
            oss << "unexpected character '" << c <<"' at the end of the expression";
            break;
        default:
            oss << "unknown error in the expression";
            break;
    }

    msg = oss.str();
}

// Creation a new exception
evaluation_error::evaluation_error(_eval_error e, const std::string& arg)
{
    ostringstream oss;
    oss << "polder::evaluation_error: ";

    switch (e)
    {
        case _eval_error::UNKNOWN_OPERATOR:
            oss << "unknown operator '" << arg << "' in the expression";
            break;

        case _eval_error::INVALID_NUMBER:
            oss << "'" << arg << "' is not valid number";
            break;
        default:
            oss << "unknown error in the expression";
            break;
    }

    msg = oss.str();
}

// Destructor, does nothing
evaluation_error::~evaluation_error() noexcept {}

// Returns what the error is
const char* evaluation_error::what() const noexcept
{
    return msg.c_str();
}


} // namespace polder
