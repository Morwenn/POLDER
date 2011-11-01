/*
 * Copyright (C) 2011 Morwenn
 *
 * POLDER is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * POLDER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "evaluate.h"

namespace polder
{


// Expression handling
static void expr_norm(char* str);
static std::vector<Elem> vec_from_expr(const char* expr);
static std::stack<Elem> postfix(std::vector<Elem> vec);
static double eval_postfix(std::stack<Elem>& S);

// Miscellaneous
static int op_value(const char* op);
static Elem operation(double a, double op);
static Elem operation(double a, double b, double op);
static int priority(Elem E);

// Type checking
static bool is_operand(Elem E);
static bool is_operator(Elem E);
static bool is_prefix(Elem E);
static bool is_postfix(Elem E);

// Error function
static void report_error(eval_error error);
static void report_error(eval_error error, double info);
static void report_error(eval_error error, const char* info);

using namespace std;

////////////////////////////////////////////////////////////
/// Evaluation function
///
////////////////////////////////////////////////////////////

double evaluate(const char* expr)
{
    char* expr_copy = new char[2*strlen(expr)+1];
    strcpy(expr_copy, expr);
    expr_norm(expr_copy);
    vector<Elem> vec = vec_from_expr(expr_copy); // Split the string into elements
    delete[] expr_copy;
    stack<Elem> P = postfix(vec);                // Order the elements
    return eval_postfix(P);                      // Evaluate the expression
}


////////////////////////////////////////////////////////////
/// Expression handling functions
///
////////////////////////////////////////////////////////////

/* Add/remove spaces in the expression so that it will be easier to split it
   Also returns an error when reading an unexpected character. */
void expr_norm(char* str)
{
    char* new_str = new char[2*strlen(str)+1];

    unsigned int count = 0;
    for (unsigned int i = 0 ; str[i] ; ++i)
    {
        switch (str[i])
        {
            // Characters always used alone
            case '(':
            case ')':
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
            case '+': // Can be unary or not
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
                        report_error(eval_error::SYNTAX);
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
                    report_error(eval_error::UNEXPECTED_CHAR, str[i]);
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
        report_error(eval_error::LAST_CHARACTER, new_str[count]);
    }

    strcpy(str, new_str);
    delete[] new_str;
}

// Create a vector of elements with the expression
vector<Elem> vec_from_expr(const char* expr)
{
    vector<Elem> vec;
    char* word = new char[128];
    Elem e;

    strcpy(word, string::read_word_first(expr));
    while (word[0])
    {
        if (word[0] == '(' || word[0] == ')')
        {
            e.type = elem_t::PARENTHESIS;
            e.data = word[0];
        }
        else if (isdigit(word[0]) || word[0] == '.'
            || (word[0] == '-' && (isdigit(word[1]) || word[1] == '.')))
        {
            e.type = elem_t::OPERAND;
            if (ptype::is_unumber(word))
            {
                e.data = atof(word);
            }
            else
            {
                report_error(eval_error::INVALID_NUMBER);
            }
        }
        else
        {
            e.data = op_value(word);
            if (e.data < -100)
            {
                e.type = elem_t::POSTFIX;
            }
            else if (e.data < 0)
            {
                e.type = elem_t::PREFIX;
            }
            else
            {
                e.type = elem_t::OPERATOR;
            }
        }
        vec.push_back(e);
        strcpy(word, string::read_word_next());
    }
    delete[] word;
    return vec;
}

// Create the postfix expression from a vector of elements
stack<Elem> postfix(vector<Elem> vec)
{
    stack<Elem> R, P;

    for (auto it = vec.begin() ; it != vec.end() ; ++it)
    {
        if (is_operand(*it))
        {
            R.push(*it);
            while (!P.empty() && is_prefix(P.top()))
            {
                R.push(P.top());
                P.pop();
            }
        }
        else if (is_postfix(*it))
        {
            R.push(*it);
        }
        else if (is_operator(*it))
        {
            while(!P.empty() && is_operator(P.top()) && (priority(*it) <= priority(P.top())))
            {
                R.push(P.top());
                P.pop();
            }
            P.push(*it);
        }
        else if (it->data == '(' || is_prefix(*it))
        {
            P.push(*it);
        }
        else // if it->data == ')'
        {
            while (!P.empty() && P.top().data != '(')
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
double eval_postfix(stack<Elem>& S)
{
    Elem x, y, e;
    stack<Elem> R;

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
            R.push(operation(y.data, x.data, e.data));
        }
        else // if (is_prefix(e) || is_postfix(e))
        {
            x = R.top();
            R.pop();
            R.push(operation(x.data, e.data));
        }
    }
    return R.top().data;
}


////////////////////////////////////////////////////////////
/// Miscellaneous functions
///
////////////////////////////////////////////////////////////

// Returns the value corresponding to an operator
int op_value(const char* op)
{
    if (op[1] == '\0')
    {
        switch (op[0])
        {
            case '+': return OP_ADD;
            case '-': return OP_SUB;
            case '*': return OP_MUL;
            case '<': return OP_LT;
            case '>': return OP_GT;
            case '/': return OP_DIV;
            case '%': return OP_MOD;
            case '&': return OP_BAND;
            case '^': return OP_BXOR;
            case '|': return OP_BOR;
            case '!': return UOP_NOT;
            case '~': return UOP_BNOT;
            default: report_error(eval_error::UNKNOWN_OPERATOR, op);
        }
    }
    else // If op has several characters
    {
        if (!strcmp(op, "=="))
            return OP_EQ;
        else if (!strcmp(op, "!=") || !strcmp(op, "<>"))
            return OP_NE;
        else if (!strcmp(op, ">="))
            return OP_GE;
        else if (!strcmp(op, "<="))
            return OP_LE;
        else if (!strcmp(op, "&&"))
            return OP_AND;
        else if (!strcmp(op, "||"))
            return OP_OR;
        else if (!strcmp(op, "**"))
            return OP_POW;
        else if (!strcmp(op, "//"))
            return OP_IDIV;
        else if (!strcmp(op, "<=>"))
            return OP_SPACE;
        else if (!strcmp(op, "<<"))
            return OP_LSHIFT;
        else if (!strcmp(op, ">>"))
            return OP_RSHIFT;
        else if (!strcmp(op, "^^"))
            return OP_XOR;
        else if (!strcmp(op, "$-"))
            return UOP_SUB;
        else if (!strcmp(op, "$!"))
            return UOP_FAC;
        else
            report_error(eval_error::UNKNOWN_OPERATOR, op);
    }
    // Should never be executed
    return OP_ERROR;
}

// Returns the priority of an operator
int priority(Elem E)
{
    switch ((int) E.data)
    {
        // The greater the faster
        case OP_POW: return 12;
        case OP_MUL:
        case OP_DIV:
        case OP_IDIV:
        case OP_MOD: return 11;
        case OP_ADD:
        case OP_SUB: return 10;
        case OP_LSHIFT:
        case OP_RSHIFT: return 9;
        case OP_LT:
        case OP_LE:
        case OP_GT:
        case OP_GE: return 8;
        case OP_EQ:
        case OP_NE:
        case OP_SPACE: return 7;
        case OP_BAND: return 6;
        case OP_BXOR: return 5;
        case OP_BOR: return 4;
        case OP_AND: return 3;
        case OP_XOR: return 2;
        case OP_OR: return 1;

        // Error
        default: report_error(eval_error::UNKNOWN_OPERATOR, E.data);
    }
    // Should never be executed
    return -1;
}

// Does the operation between two operands
Elem operation(double a, double b, double op)
{
    Elem res;
    res.type = elem_t::OPERAND;

    switch ((int) op)
    {
        case OP_ADD: res.data = a + b; break;                     // +
        case OP_SUB: res.data = a - b; break;                     // -
        case OP_MUL: res.data = a * b; break;                     // *
        case OP_LT: res.data = a < b; break;                      // <
        case OP_GT: res.data = a > b; break;                      // >
        case OP_DIV: res.data = a / b; break;                     // /
        case OP_IDIV: res.data = (int) a / (int) b; break;        // //
        case OP_MOD: res.data = (int) a % (int) b; break;         // %
        case OP_BAND: res.data = (int) a & (int) b; break;        // &
        case OP_BXOR: res.data = (int) a ^ (int) b; break;         // ^
        case OP_BOR: res.data = (int) a | (int) b; break;         // |
        case OP_EQ: res.data = (a == b); break;                   // ==
        case OP_NE: res.data = (a != b); break;                   // != or <>
        case OP_GE: res.data = (a >= b); break;                   // >=
        case OP_LE: res.data = (a <= b); break;                   // <=
        case OP_AND: res.data = (a && b); break;                  // &&
        case OP_XOR: res.data = (a && !b) || (b && !a); break;    // ^^
        case OP_OR: res.data = (a || b); break;                   // ||
        case OP_POW: res.data = pow(a, b); break;                 // **
        case OP_SPACE: res.data = (a < b) ? -1 : (a != b); break; // <=>
        case OP_LSHIFT: res.data = (int) a << (int) b; break;     // <<
        case OP_RSHIFT: res.data = (int) a >> (int) b; break;     // >>
        default: report_error(eval_error::UNKNOWN_OPERATOR, op);
    }

    // Returns an operand corresponding to the result of the operation
    return res;
}

// Does an unary operation
Elem operation(double a, double op)
{
    Elem res;
    res.type = elem_t::OPERAND;

    switch ((int) op)
    {
        case UOP_SUB: res.data = -a; break;                 // -
        case UOP_NOT: res.data = !a; break;                 // ! (prefix)
        case UOP_BNOT: res.data = ~ (int) a; break;         // ~
        case UOP_FAC: res.data = math::factorial((unsigned int) a); break; // ! (postfix)
        default: report_error(eval_error::UNKNOWN_OPERATOR, op);
    }

    // Returns an operand corresponding to the result of the operation
    return res;
}


////////////////////////////////////////////////////////////
/// Type checking functions
///
////////////////////////////////////////////////////////////

bool is_operand(Elem E)
{
    return E.type == elem_t::OPERAND;
}

bool is_operator(Elem E)
{
    return E.type == elem_t::OPERATOR;
}

bool is_prefix(Elem E)
{
    return E.type == elem_t::PREFIX;
}

bool is_postfix(Elem E)
{
    return E.type == elem_t::POSTFIX;
}


////////////////////////////////////////////////////////////
/// Error functions
///
////////////////////////////////////////////////////////////

void report_error(eval_error error)
{
    FILE* f = fopen("eval_errors.log", "a");
    switch (error)
    {
        case eval_error::UNKNOWN: fprintf(f, "An unknowed error occurred during the evaluation.\n");
        break;
        case eval_error::SYNTAX: fprintf(f, "Syntax error in the expression.\n");
        break;
        default: fprintf(f, "This sentence should not have appeared...\n");
        break;
    }
    fclose(f);

    // Exit gracefully
    exit(1);
}

// Report errors and exit gracefully
void report_error(eval_error error, double info)
{
    FILE* f = fopen("eval_errors.log", "a");
    switch (error)
    {
        case eval_error::UNEXPECTED_CHAR: fprintf(f, "Unexpected character '%c' in the expression.\n", (char) info);
        break;
        case eval_error::LAST_CHARACTER: fprintf(f, "Character '%c' is not allowed at the end of the expression.\n", (char) info);
        break;
        case eval_error::MISSING_CHAR: fprintf(f, "Expected character '%c' in the expression.\n", (char) info);
        break;
        case eval_error::UNKNOWN_OPERATOR: fprintf(f, "Unknown operator code '%f' in the expression.\n", info);
        break;
        default: fprintf(f, "This sentence should not have appeared...\n");
        break;
    }
    fclose(f);

    // Exit gracefully
    exit(1);
}

void report_error(eval_error error, const char* info)
{
    FILE* f = fopen("eval_errors.log", "a");
    switch (error)
    {
        case eval_error::UNKNOWN_OPERATOR: fprintf(f, "Unknown operator '%s' in the expression.\n", info);
        break;
        case eval_error::INVALID_NUMBER: fprintf(f, "Invalid number '%s' in the expression.\n", info);
        break;
        default: fprintf(f, "This sentence should not have appeared...\n");
        break;
    }
    fclose(f);

    // Exit gracefully
    exit(1);
}


} // namespace polder
