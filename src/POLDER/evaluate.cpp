/*
 * Copyright (C) 2011-2014 Morwenn
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
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <POLDER/evaluate.h>
#include <POLDER/math/factorial.h>
#include <POLDER/utility.h>


namespace polder
{
namespace
{
    ////////////////////////////////////////////////////////////
    // Constants
    ////////////////////////////////////////////////////////////

    // Handled operators
    enum op_t: int
    {
        // Handled binary operators
        EQ = 0,     // =
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
        NB_BINARY_OPERATORS,

        // Handled prefix unary operators
        USUB,       // - (Unary minus)
        NOT,        // ! (Logical NOT)
        BNOT,       // ~ (Bitwise NOT)

        // Handled postfix unary operators
        FAC         // ! (Factorial)
    };

    constexpr const char* op_str[] = {
        "=",
        "!=",
        ">=",
        "<=",
        "&&",
        "||",
        "^^",
        "**",
        "<=>",
        "<<",
        ">>",
        "+",
        "-",
        "*",
        "/",
        "%",
        "&",
        "|",
        ">",
        "<",
        "^",
        "//",
        "-",
        "!",
        "~",
        "!"
    };

    // Binary operators priority
    // The priority of unary operators is
    // determined by their position
    constexpr unsigned int _priority[] = {
        7,   // =
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
    };

    // Operations corresponding to the operators
    const std::unordered_map<op_t, double(*)(double, double), enum_hash_t<op_t>> _operation = {
        { op_t::ADD,    [](double a, double b) -> double { return a + b; } },
        { op_t::SUB,    [](double a, double b) -> double { return a - b; } },
        { op_t::MUL,    [](double a, double b) -> double { return a * b; } },
        { op_t::LT,     [](double a, double b) -> double { return a < b; } },
        { op_t::GT,     [](double a, double b) -> double { return a > b; } },
        { op_t::DIV,    [](double a, double b) -> double { return a / b; } },
        { op_t::IDIV,   [](double a, double b) -> double { return (int) a / (int) b; } },
        { op_t::MOD,    [](double a, double b) -> double { return (int) a % (int) b; } },
        { op_t::BAND,   [](double a, double b) -> double { return (int) a & (int) b; } },
        { op_t::BXOR,   [](double a, double b) -> double { return (int) a ^ (int) b; } },
        { op_t::BOR,    [](double a, double b) -> double { return (int) a | (int) b; } },
        { op_t::EQ,     [](double a, double b) -> double { return a == b; } },
        { op_t::NE,     [](double a, double b) -> double { return a != b; } },
        { op_t::GE,     [](double a, double b) -> double { return a >= b; } },
        { op_t::LE,     [](double a, double b) -> double { return a <= b; } },
        { op_t::AND,    [](double a, double b) -> double { return a && b; } },
        { op_t::XOR,    [](double a, double b) -> double { return (a && !b) || (b && !a); } },
        { op_t::OR,     [](double a, double b) -> double { return a || b; } },
        { op_t::POW,    [](double a, double b) -> double { return std::pow(a, b); } },
        { op_t::SPACE,  [](double a, double b) -> double { return (a < b) ? -1 : (a != b); } },
        { op_t::LSHIFT, [](double a, double b) -> double { return (int) a << (int) b; } },
        { op_t::RSHIFT, [](double a, double b) -> double { return (int) a >> (int) b; } }
    };

    // Element types
    enum struct elem_t
    {
        OPERAND,
        OPERATOR,
        PREFIX,
        POSTFIX,
        PARENTHESIS
    };

    struct Token
    {
        elem_t type;
        union
        {
            char par;       // parenthesis
            op_t op;        // operator
            double data;    // real value
        };

        Token():
            type(elem_t::OPERAND),
            data(0.0)
        {}

        Token(char p):
            type(elem_t::PARENTHESIS),
            par(p)
        {}

        Token(double d):
            type(elem_t::OPERAND),
            data(d)
        {}

        Token(op_t o):
            type(elem_t::OPERATOR),
            op(o)
        {
            if (o == op_t::USUB
                || o == op_t::NOT
                || o == op_t::BNOT)
            {
                type = elem_t::PREFIX;
            }
            else if (o == op_t::FAC)
            {
                type = elem_t::POSTFIX;
            }
        }
    };
}

// Error codes
enum struct eval_error_code
{
    UNKNOWN_OPERATOR,
    UNEXPECTED_CHARACTER,
    NOT_ENOUGH_OPERANDS
};

// Lexer and parser
auto tokenize(const std::string& expr)
    -> std::vector<Token>;
auto postfix(const std::vector<Token>& vec)
    -> std::stack<Token>;
auto eval_postfix(std::stack<Token>&& S)
    -> double;

// Miscellaneous
auto operation(double a, op_t op)
    -> Token;
auto operation(double a, double b, op_t op)
    -> Token;
auto priority(const Token& token)
    -> int;

// Type checking
auto is_operand(const Token& token)
    -> bool;
auto is_operator(const Token& token)
    -> bool;
auto is_prefix(const Token& token)
    -> bool;
auto is_postfix(const Token& token)
    -> bool;

////////////////////////////////////////////////////////////
// Evaluation function
////////////////////////////////////////////////////////////

auto evaluate(const std::string& expr)
    -> double
{
    auto tokens = tokenize(expr);
    return eval_postfix(postfix(tokens));
}

////////////////////////////////////////////////////////////
// Lexer and Parser
////////////////////////////////////////////////////////////

auto tokenize(const std::string& expr)
    -> std::vector<Token>
{
    std::vector<Token> res;

    // Number of parenthesis
    int nmb_parenthesis = 0;

    for (auto it = expr.cbegin() ; it != expr.cend() ; ++it)
    {
        // Skip all kinds of spaces
        while (std::isspace(*it))
        {
            ++it;
        }
        if (*it == '\0')
        {
            break;
        }

        if (std::isdigit(*it))
        {
            // Found a number
            auto tmp = it;
            bool has_dot = false;
            while (std::isdigit(*it) || *it == '.')
            {
                if (*it == '.')
                {
                    if (has_dot)
                    {
                        // Two dots in the same number: error
                        throw evaluation_error(eval_error_code::UNEXPECTED_CHARACTER, '.');
                    }
                    else
                    {
                        // We just confirmed we found a real number
                        has_dot = true;
                    }
                }
                ++it;
            }
            auto tmp_str = std::string(tmp, it);
            res.emplace_back(std::stod(tmp_str));
            --it; // Iteration is pushed one step too far
            continue;
        }

        switch (*it)
        {
            case ')':
                if (nmb_parenthesis == 0)
                {
                    throw evaluation_error("trying to close a non-opened parenthesis");
                }
                --nmb_parenthesis;
                res.emplace_back(')');
                break;

            case '(':
                ++nmb_parenthesis;
                res.emplace_back('(');
                break;

            case '+':
                res.emplace_back(op_t::ADD);
                break;
            case '%':
                res.emplace_back(op_t::MOD);
                break;
            case '~':
                res.emplace_back(op_t::BNOT);
                break;
            case '=':
                res.emplace_back(op_t::EQ);
                break;

            case '*': // * or **
                if (it[1] == '*')
                {
                    res.emplace_back(op_t::POW);
                    ++it;
                }
                else
                {
                    res.emplace_back(op_t::MUL);
                }
                break;

            case '&': // & or &&
                if (it[1] == '&')
                {
                    res.emplace_back(op_t::AND);
                    ++it;
                }
                else
                {
                    res.emplace_back(op_t::BAND);
                }
                break;

            case '|': // | or ||
                if (it[1] == '*')
                {
                    res.emplace_back(op_t::OR);
                    ++it;
                }
                else
                {
                    res.emplace_back(op_t::BOR);
                }
                break;

            case '^': // ^ or ^^
                if (it[1] == '^')
                {
                    res.emplace_back(op_t::XOR);
                    ++it;
                }
                else
                {
                    res.emplace_back(op_t::BXOR);
                }
                break;

            case '/': // / or //
                if (it[1] == '/')
                {
                    res.emplace_back(op_t::IDIV);
                    ++it;
                }
                else
                {
                    res.emplace_back(op_t::DIV);
                }
                break;

            case '-': // - (unary or binary)
                if (res.empty())
                {
                    res.emplace_back(op_t::USUB);
                    break;
                }
                else
                {
                    const Token& t = res.back();
                    if (is_operand(t)
                        || is_postfix(t)
                        || (t.type == elem_t::PARENTHESIS && t.par == ')'))
                    {
                        res.emplace_back(op_t::SUB);
                    }
                    else
                    {
                        res.emplace_back(op_t::USUB);
                    }
                    break;
                }

            case '<': // <, <=, <=>, << and <>
                if (it[1] == '<')
                {
                    res.emplace_back(op_t::LSHIFT);
                    ++it;
                    break;
                }
                else if (it[1] == '>')
                {
                    res.emplace_back(op_t::NE);
                    ++it;
                    break;
                }
                else if (it[1] == '=')
                {
                    if (it[2] == '>')
                    {
                        res.emplace_back(op_t::SPACE);
                        it += 2;
                        break;
                    }
                    res.emplace_back(op_t::LE);
                    ++it;
                    break;
                }
                res.emplace_back(op_t::LT);
                break;

            case '>': // >, >= and >>
                if (it[1] == '>')
                {
                    res.emplace_back(op_t::RSHIFT);
                    ++it;
                    break;
                }
                else if (it[1] == '=')
                {
                    res.emplace_back(op_t::GE);
                    ++it;
                    break;
                }
                res.emplace_back(op_t::GT);
                break;

            case '!': // ! (prefix or postfix) and !=
                if (it[1] == '=' && it[1] != '=')
                {
                    res.emplace_back(op_t::NE);
                    break;
                }
                else
                {
                    const Token& t = res.back();
                    if (is_operand(t)
                        || is_postfix(t)
                        || (t.type == elem_t::PARENTHESIS && t.par == ')'))
                    {
                        res.emplace_back(op_t::FAC);
                        break;
                    }
                    res.emplace_back(op_t::NOT);
                    break;
                }

            default:
                throw evaluation_error(eval_error_code::UNKNOWN_OPERATOR, *it);
        }
    }

    if (nmb_parenthesis)
    {
        throw evaluation_error("mismatched parenthesis in the expression");
    }

    return res;
}

auto postfix(const std::vector<Token>& vec)
    -> std::stack<Token>
{
    std::stack<Token> r, p;

    for (const Token& token: vec)
    {
        if (is_operand(token))
        {
            r.push(token);
            while (not p.empty() && is_prefix(p.top()))
            {
                r.push(p.top());
                p.pop();
            }
        }
        else if (is_postfix(token))
        {
            r.push(token);
        }
        else if (is_operator(token))
        {
            while (not p.empty() && is_operator(p.top())
                  && (priority(token) <= priority(p.top())))
            {
                r.push(p.top());
                p.pop();
            }
            p.push(token);
        }
        else if (is_prefix(token) || token.par == '(')
        {
            p.push(token);
        }
        else // if token.par == ')'
        {
            while (not p.empty() && p.top().par != '(')
            {
                r.push(p.top());
                p.pop();
            }
            p.pop();
            while (not p.empty() && is_prefix(p.top()))
            {
                r.push(p.top());
                p.pop();
            }
        }
    }

    while (not r.empty())
    {
        p.push(r.top());
        r.pop();
    }
    return p;
}

auto eval_postfix(std::stack<Token>&& st)
    -> double
{
    Token x, y, e;
    std::stack<Token> operands;

    while (not st.empty())
    {
        e = st.top();
        st.pop();
        if (is_operand(e))
        {
            operands.push(e);
        }
        else if (is_operator(e))
        {
            if (operands.size() < 2)
            {
                throw evaluation_error(eval_error_code::NOT_ENOUGH_OPERANDS, op_str[e.op]);
            }
            x = operands.top();
            operands.pop();
            y = operands.top();
            operands.pop();
            operands.push(operation(y.data, x.data, e.op));
        }
        else // if (is_prefix(token) || is_postfix(token))
        {
            if (operands.empty())
            {
                throw evaluation_error(eval_error_code::NOT_ENOUGH_OPERANDS, op_str[e.op]);
            }
            x = operands.top();
            operands.pop();
            operands.push(operation(x.data, e.op));
        }
    }
    return operands.top().data;
}

////////////////////////////////////////////////////////////
// Miscellaneous functions
////////////////////////////////////////////////////////////

auto priority(const Token& token)
    -> int
{
    return _priority[token.op];
}

auto operation(double a, double b, op_t op)
    -> Token
{
    Token res;
    res.type = elem_t::OPERAND;

    auto it = _operation.find(op);
    if (it == _operation.end())
    {
        throw evaluation_error(eval_error_code::UNKNOWN_OPERATOR, op);
    }
    return it->second(a, b);
}

auto operation(double a, op_t op)
    -> Token
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
        default:
            throw evaluation_error();
    }
    return res;
}

////////////////////////////////////////////////////////////
// Type checking functions
////////////////////////////////////////////////////////////

auto is_operand(const Token& token)
    -> bool
{
    return token.type == elem_t::OPERAND;
}

auto is_operator(const Token& token)
    -> bool
{
    return token.type == elem_t::OPERATOR;
}

auto is_prefix(const Token& token)
    -> bool
{
    return token.type == elem_t::PREFIX;
}

auto is_postfix(const Token& token)
    -> bool
{
    return token.type == elem_t::POSTFIX;
}

////////////////////////////////////////////////////////////
// Exceptions handling
////////////////////////////////////////////////////////////

evaluation_error::evaluation_error():
    msg("polder::evaluation_error: undocumented error")
{}

evaluation_error::evaluation_error(const std::string& arg):
    msg(std::string("polder::evaluation_error: ") + arg)
{}

evaluation_error::evaluation_error(eval_error_code e, char c)
{
    std::ostringstream oss;
    oss << "polder::evaluation_error: ";

    switch (e)
    {
        case eval_error_code::UNKNOWN_OPERATOR:
            oss << "unknown operator '" << c << "' in the expression";
            break;
        case eval_error_code::UNEXPECTED_CHARACTER:
            oss << "unexpected character '" << c <<"' in the expression";
            break;
        default:
            oss << "unknown error in the expression";
            break;
    }

    msg = oss.str();
}

evaluation_error::evaluation_error(eval_error_code e, const std::string& arg)
{
    std::ostringstream oss;
    oss << "polder::evaluation_error: ";

    switch (e)
    {
        case eval_error_code::UNKNOWN_OPERATOR:
            oss << "unknown operator '" << arg << "' in the expression";
            break;
        case eval_error_code::NOT_ENOUGH_OPERANDS:
            oss << "not enough operands for operator '" << arg << "'.";
            break;
        default:
            oss << "unknown error in the expression";
            break;
    }

    msg = oss.str();
}

evaluation_error::~evaluation_error() noexcept
    = default;

auto evaluation_error::what() const noexcept
    -> const char*
{
    return msg.c_str();
}

} // namespace polder
