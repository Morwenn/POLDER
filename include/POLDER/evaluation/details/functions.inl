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
auto tokenize(const std::string& expr)
    -> std::vector<token<Number>>
{
    std::vector<token<Number>> res;

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
                        throw error(error_type::several_dots);
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

        if (std::isalpha(*it) || *it == '_')
        {
            // Found a function name
            auto tmp = it;
            while (std::isalnum(*it) || *it == '_')
            {
                ++it;
            }
            res.emplace_back(std::string(tmp, it));
            --it; // Iteration is pushed one step too far
            continue;
        }

        switch (*it)
        {
            case ',':
                if (nmb_parenthesis == 0)
                {
                    throw error(error_type::stray_comma);
                }
                res.emplace_back(token_t::comma);
                break;

            case ')':
                if (nmb_parenthesis == 0)
                {
                    throw error(error_type::closed_parenthesis);
                }
                --nmb_parenthesis;
                res.emplace_back(token_t::right_brace);
                break;

            case '(':
                ++nmb_parenthesis;
                res.emplace_back(token_t::left_brace);
                break;

            case '+':
                res.emplace_back(infix_t::ADD);
                break;
            case '%':
                res.emplace_back(infix_t::MOD);
                break;
            case '~':
                res.emplace_back(prefix_t::BNOT);
                break;
            case '=':
                res.emplace_back(infix_t::EQ);
                break;

            case '*': // * or **
                if (it[1] == '*')
                {
                    res.emplace_back(infix_t::POW);
                    ++it;
                }
                else
                {
                    res.emplace_back(infix_t::MUL);
                }
                break;

            case '&': // & or &&
                if (it[1] == '&')
                {
                    res.emplace_back(infix_t::AND);
                    ++it;
                }
                else
                {
                    res.emplace_back(infix_t::BAND);
                }
                break;

            case '|': // | or ||
                if (it[1] == '|')
                {
                    res.emplace_back(infix_t::OR);
                    ++it;
                }
                else
                {
                    res.emplace_back(infix_t::BOR);
                }
                break;

            case '^': // ^ or ^^
                if (it[1] == '^')
                {
                    res.emplace_back(infix_t::XOR);
                    ++it;
                }
                else
                {
                    res.emplace_back(infix_t::BXOR);
                }
                break;

            case '/': // / or //
                if (it[1] == '/')
                {
                    res.emplace_back(infix_t::IDIV);
                    ++it;
                }
                else
                {
                    res.emplace_back(infix_t::DIV);
                }
                break;

            case '-': // - (unary or binary)
                if (res.empty())
                {
                    res.emplace_back(prefix_t::USUB);
                }
                else
                {
                    const token<Number>& tok = res.back();
                    if (tok.is_operand()
                        || tok.is_postfix()
                        || tok.is_right_brace())
                    {
                        res.emplace_back(infix_t::SUB);
                    }
                    else
                    {
                        res.emplace_back(prefix_t::USUB);
                    }
                }
                break;

            case '<': // <, <=, <=>, << and <>
                if (it[1] == '<')
                {
                    res.emplace_back(infix_t::LSHIFT);
                    ++it;
                    break;
                }
                else if (it[1] == '>')
                {
                    res.emplace_back(infix_t::NE);
                    ++it;
                    break;
                }
                else if (it[1] == '=')
                {
                    if (it[2] == '>')
                    {
                        res.emplace_back(infix_t::SPACE);
                        it += 2;
                        break;
                    }
                    res.emplace_back(infix_t::LE);
                    ++it;
                    break;
                }
                res.emplace_back(infix_t::LT);
                break;

            case '>': // >, >= and >>
                if (it[1] == '>')
                {
                    res.emplace_back(infix_t::RSHIFT);
                    ++it;
                    break;
                }
                else if (it[1] == '=')
                {
                    res.emplace_back(infix_t::GE);
                    ++it;
                    break;
                }
                res.emplace_back(infix_t::GT);
                break;

            case '!': // ! (prefix or postfix) and !=
                if (it[1] == '=' && it[1] != '=')
                {
                    res.emplace_back(infix_t::NE);
                }
                else
                {
                    const token<Number>& tok = res.back();
                    if (tok.is_operand()
                        || tok.is_postfix()
                        || tok.is_right_brace())
                    {
                        res.emplace_back(postfix_t::FAC);
                        break;
                    }
                    res.emplace_back(prefix_t::NOT);
                }
                break;

            default:
            {
                std::stringstream sstr;
                sstr << "unknown operator in the expression: "
                     << *it;

                throw error(error_type::unknown_operator, sstr.str());
            }
        }
    }

    if (nmb_parenthesis)
    {
        throw error(error_type::mismatched_parenthesis);
    }

    return res;
}

template<typename Number>
auto to_postfix(const std::vector<token<Number>>& tokens)
    -> std::stack<token<Number>>
{
    // This function implements a Shunting-Yard algorithm
    // to handle the priority of infix operators

    std::stack<token<Number>> output;
    std::stack<token<Number>> operations;

    for (const token<Number>& tok: tokens)
    {
        switch (tok.type)
        {
            case token_t::operand:
            {
                output.push(tok);
                while (not operations.empty() && operations.top().is_prefix())
                {
                    output.push(std::move(operations.top()));
                    operations.pop();
                }
                break;
            }

            case token_t::postfix:
            {
                output.push(tok);
                break;
            }

            case token_t::infix:
            {
                while (not operations.empty()
                       && operations.top().is_infix()
                       && (priority(tok.infix) <= priority(operations.top().infix)))
                {
                    output.push(std::move(operations.top()));
                    operations.pop();
                }
                operations.push(tok);
                break;
            }

            case token_t::prefix:
            case token_t::name:
            case token_t::left_brace:
            {
                operations.push(tok);
                break;
            }

            case token_t::right_brace:
            {
                while (not operations.empty() &&
                       not operations.top().is_left_brace())
                {
                    output.push(std::move(operations.top()));
                    operations.pop();
                }
                operations.pop();
                while (not operations.empty()
                       && (operations.top().is_prefix() || operations.top().is_name()))
                {
                    output.push(std::move(operations.top()));
                    operations.pop();
                }
                break;
            }

            case token_t::comma:
            {
                while (not operations.empty() &&
                       not operations.top().is_left_brace())
                {
                    output.push(std::move(operations.top()));
                    operations.pop();
                }
                break;
            }
        }
    }

    while (not output.empty())
    {
        operations.push(std::move(output.top()));
        output.pop();
    }
    return operations;
}
