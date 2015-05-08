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

////////////////////////////////////////////////////////////
// Construction and destruction

template<typename Number>
token<Number>::token(const token& other):
    type(other.type)
{
    switch (type)
    {
        case token_t::operand:
            data = other.data;
            break;
        case token_t::name:
            new (&name) std::string;
            name = other.name;
            break;
        case token_t::infix:
            infix = other.infix;
            break;
        case token_t::prefix:
            prefix = other.prefix;
            break;
        case token_t::postfix:
            postfix = other.postfix;
            break;

        default:
            // Do fucking nothing and shut the compiler warning
            break;
    }
}

template<typename Number>
token<Number>::token(token_t type):
    type(type)
{
    if (type == token_t::name)
    {
        new (&name) std::string;
    }
}

template<typename Number>
token<Number>::token(Number num):
    type(token_t::operand),
    data(num)
{}

template<typename Number>
token<Number>::token(std::string name):
    type(token_t::name)
{
    new (&this->name) std::string;
    this->name = std::move(name);
}

template<typename Number>
token<Number>::token(infix_t oper):
    type(token_t::infix),
    infix(oper)
{}

template<typename Number>
token<Number>::token(prefix_t oper):
    type(token_t::prefix),
    prefix(oper)
{}

template<typename Number>
token<Number>::token(postfix_t oper):
    type(token_t::postfix),
    postfix(oper)
{}

template<typename Number>
token<Number>::~token()
{
    if (type == token_t::name)
    {
        name.~basic_string();
    }
}

////////////////////////////////////////////////////////////
// Helper functions

template<typename Number>
auto token<Number>::is_operand() const
    -> bool
{
    return type == token_t::operand;
}

template<typename Number>
auto token<Number>::is_name() const
    -> bool
{
    return type == token_t::name;
}

template<typename Number>
auto token<Number>::is_infix() const
    -> bool
{
    return type == token_t::infix;
}

template<typename Number>
auto token<Number>::is_prefix() const
    -> bool
{
    return type == token_t::prefix;
}

template<typename Number>
auto token<Number>::is_postfix() const
    -> bool
{
    return type == token_t::postfix;
}

template<typename Number>
auto token<Number>::is_left_brace() const
    -> bool
{
    return type == token_t::left_brace;
}

template<typename Number>
auto token<Number>::is_right_brace() const
    -> bool
{
    return type == token_t::right_brace;
}

template<typename Number>
auto token<Number>::is_comma() const
    -> bool
{
    return type == token_t::comma;
}

////////////////////////////////////////////////////////////
// Display functions

template<typename Number>
auto to_string(const token<Number>& tok)
    -> std::string
{
    switch (tok.type)
    {
        case token_t::operand:
            return std::to_string(tok.data);
        case token_t::name:
            return tok.name;
        case token_t::infix:
            return to_string(tok.infix);
        case token_t::prefix:
            return to_string(tok.prefix);
        case token_t::postfix:
            return to_string(tok.postfix);
        case token_t::left_brace:
            return "(";
        case token_t::right_brace:
            return ")";
        case token_t::comma:
            return ",";
    }

    // Should never be reached
    return "";
}

template<typename Number>
auto operator<<(std::ostream& stream, const token<Number>& tok)
    -> std::ostream&
{
    switch (tok.type)
    {
        case token_t::operand:
            stream << tok.data;
            break;
        case token_t::name:
            stream << tok.name;
            break;
        case token_t::infix:
            stream << to_string(tok.infix);
            break;
        case token_t::prefix:
            stream << to_string(tok.prefix);
            break;
        case token_t::postfix:
            stream << to_string(tok.postfix);
            break;
        case token_t::left_brace:
            stream << '(';
            break;
        case token_t::right_brace:
            stream << ')';
            break;
        case token_t::comma:
            stream << ',';
            break;
    }
    return stream;
}
