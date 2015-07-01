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
auto evaluator<Number>::evaluate(const std::string& expression) const
    -> Number
{
    auto tokens = tokenize<Number>(expression);
    return eval_postfix(to_postfix(tokens));
}

template<typename Number>
auto evaluator<Number>::operator()(const std::string& expression) const
    -> Number
{
    return evaluate(expression);
}

template<typename Number>
template<typename Func>
auto evaluator<Number>::connect(const std::string& name, Func&& function)
    -> void
{
    callbacks.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(name),
        std::forward_as_tuple(function)
    );
}

template<typename Number>
auto evaluator<Number>::disconnect(const std::string& name)
    -> void
{
    callbacks.erase(name);
}

template<typename Number>
auto evaluator<Number>::eval_postfix(std::stack<token<Number>>&& tokens) const
    -> Number
{
    std::stack<Number> operands;

    while (not tokens.empty())
    {
        token<Number> tok = std::move(tokens.top());
        tokens.pop();

        switch (tok.type)
        {
            case token_t::operand:
            {
                operands.push(tok.data);
                break;
            }

            case token_t::name:
            {
                auto&& func = callbacks.at(tok.name);

                if (operands.size() < func.arity)
                {
                    std::stringstream sstr;
                    sstr << "not enough operands for function "
                         << tok.name
                         << ": expected "
                         << func.arity
                         << ", got "
                         << operands.size();

                    throw error(error_type::not_enough_operands, sstr.str());
                }

                // Only 16 parameters for now
                // This function would benefit from variable size arrays
                Number params[16];

                for (std::size_t i = func.arity ; i > 0u ; --i)
                {
                    params[i-1u] = std::move(operands.top());
                    operands.pop();
                }
                operands.push(func(params));
                break;
            }

            case token_t::infix:
            {
                if (operands.size() < 2)
                {
                    std::stringstream sstr;
                    sstr << "not enough operands for infix operator "
                         << to_string(tok.infix)
                         << ": expected 2, got "
                         << operands.size();

                    throw error(error_type::not_enough_operands, sstr.str());
                }
                Number rhs = std::move(operands.top());
                operands.pop();
                Number lhs = std::move(operands.top());
                operands.pop();
                operands.push(operation(tok.infix, lhs, rhs));
                break;
            }

            case token_t::prefix:
            {
                if (operands.empty())
                {
                    std::stringstream sstr;
                    sstr << "not enough operands for prefix operator "
                         << to_string(tok.prefix)
                         << ": expected 1, got "
                         << operands.size();

                    throw error(error_type::not_enough_operands, sstr.str());
                }
                Number arg = std::move(operands.top());
                operands.pop();
                operands.push(operation(tok.prefix, arg));
                break;
            }

            case token_t::postfix:
            {
                if (operands.empty())
                {
                    std::stringstream sstr;
                    sstr << "not enough operands for postfix operator "
                         << to_string(tok.postfix)
                         << ": expected 1, got "
                         << operands.size();

                    throw error(error_type::not_enough_operands, sstr.str());
                }
                Number arg = std::move(operands.top());
                operands.pop();
                operands.push(operation(tok.postfix, arg));
                break;
            }

            default:
            {
                std::stringstream sstr;
                sstr << "unexpected token in postfix evaluation: "
                     << to_string(tok);

                throw error(error_type::unexpected_token, sstr.str());
            }
        }
    }
    return operands.top();
}
