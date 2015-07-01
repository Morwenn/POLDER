/*
 * Copyright (C) 2011-2015 Morwenn
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

template<typename Number>
auto operation(infix_t oper, Number lhs, Number rhs)
    -> Number
{
    static const std::unordered_map<infix_t, Number(*)(Number, Number), enum_hash<infix_t>> operations = {
        { infix_t::ADD,    [](Number a, Number b) -> Number { return a + b; } },
        { infix_t::SUB,    [](Number a, Number b) -> Number { return a - b; } },
        { infix_t::MUL,    [](Number a, Number b) -> Number { return a * b; } },
        { infix_t::LT,     [](Number a, Number b) -> Number { return a < b; } },
        { infix_t::GT,     [](Number a, Number b) -> Number { return a > b; } },
        { infix_t::DIV,    [](Number a, Number b) -> Number { return a / b; } },
        { infix_t::IDIV,   [](Number a, Number b) -> Number { return (long long) a / (long long) b; } },
        { infix_t::MOD,    [](Number a, Number b) -> Number { return (long long) a % (long long) b; } },
        { infix_t::BAND,   [](Number a, Number b) -> Number { return (long long) a & (long long) b; } },
        { infix_t::BXOR,   [](Number a, Number b) -> Number { return (long long) a ^ (long long) b; } },
        { infix_t::BOR,    [](Number a, Number b) -> Number { return (long long) a | (long long) b; } },
        { infix_t::EQ,     [](Number a, Number b) -> Number { return a == b; } },
        { infix_t::NE,     [](Number a, Number b) -> Number { return a != b; } },
        { infix_t::GE,     [](Number a, Number b) -> Number { return a >= b; } },
        { infix_t::LE,     [](Number a, Number b) -> Number { return a <= b; } },
        { infix_t::AND,    [](Number a, Number b) -> Number { return a && b; } },
        { infix_t::XOR,    [](Number a, Number b) -> Number { return (a && !b) || (b && !a); } },
        { infix_t::OR,     [](Number a, Number b) -> Number { return a || b; } },
        { infix_t::POW,    [](Number a, Number b) -> Number { return std::pow(a, b); } },
        { infix_t::SPACE,  [](Number a, Number b) -> Number { return (a < b) ? -1 : (a != b); } },
        { infix_t::LSHIFT, [](Number a, Number b) -> Number { return (long long) a << (long long) b; } },
        { infix_t::RSHIFT, [](Number a, Number b) -> Number { return (long long) a >> (long long) b; } }
    };

    auto it = operations.find(oper);
    if (it == operations.end())
    {
        std::stringstream sstr;
        sstr << "unknown operator in the expression: "
             << to_string(oper);

        throw error(error_type::unknown_operator, sstr.str());
    }
    return it->second(lhs, rhs);
}

template<typename Number>
auto operation(prefix_t oper, Number arg)
    -> Number
{
    static const std::unordered_map<prefix_t, Number(*)(Number), enum_hash<prefix_t>> operations = {
        { prefix_t::USUB,  [](Number a) -> Number { return -a; } },
        { prefix_t::NOT,   [](Number a) -> Number { return !a; } },
        { prefix_t::BNOT,  [](Number a) -> Number { return ~ (long long) a; } }
    };

    auto it = operations.find(oper);
    if (it == operations.end())
    {
        std::stringstream sstr;
        sstr << "unknown operator in the expression: "
             << to_string(oper);

        throw error(error_type::unknown_operator, sstr.str());
    }
    return it->second(arg);
}

template<typename Number>
auto operation(postfix_t oper, Number arg)
    -> Number
{
    static const std::unordered_map<postfix_t, Number(*)(Number), enum_hash<postfix_t>> operations = {
        { postfix_t::FAC,    [](Number a) -> Number { return math::factorial((unsigned long long) a); } }
    };

    auto it = operations.find(oper);
    if (it == operations.end())
    {
        std::stringstream sstr;
        sstr << "unknown operator in the expression: "
             << to_string(oper);

        throw error(error_type::unknown_operator, sstr.str());
    }
    return it->second(arg);
}
