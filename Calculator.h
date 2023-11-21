#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stack>
#include <cmath>
#include <map>

namespace calculator
{
	/** \class Math
	 * \brief Provides math functions and math constants \n
	 * Class is used to protect from divide by zero, small numbers and provides helpful functions
	 */
	class Math
	{
	public:
		constexpr static double e  = 2.718281828459045;
		constexpr static double pi = 3.141592653589793;

		/**
		 * \brief Calculates the factorial
		 * \details For example: \n
		 * \code auto answer = calculator::Math::factorial<std::int64_t>(5); // = 120 \endcode
		 * \tparam T the type of evaluated variable 
		 * \param number the number for which the factorial will be found
		 * \return Factorial of a 'number'
		 */
		template<class T>
		static constexpr T factorial(T const& number)
		{
			int result = 1;
			for (int i = 2; i <= number; ++i)
				result *= i;
			return result;
		}

		/**
		 * \brief Calculates the logarithm of any base
		 * \details For example: \n
		 * \code auto answer = calculator::Math::log<std::int64_t>(100, 10); // = 2 \endcode
		 * \tparam T the type of evaluated variable
		 * \param expression the number for which the logarithm will be found
		 * \param base the base of the logarithm
		 * \return Logarithm by 'base' of the 'expression'
		 */
		template<class T>
		static T log(T const& expression, double const& base)
		{
			return std::log10(expression) / std::log10(base);
		}

		/**
		 * \brief Calculates the root of any power
		 * \details For example: \n
		 * \code auto answer = calculator::Math::root<std::int64_t>(100, 10); // = 2 \endcode
		 * \tparam T the type of evaluated variable
		 * \param expression the number for which the root will be found
		 * \param power the power of the root
		 * \return Root by 'power' of the 'expression'
		 */
		template<class T>
		static T root(T const& expression, double const& power)
		{
			return std::pow(expression, static_cast<T>(1) / power);
		}

		/**
		 * \brief Calculates the sine of expression
		 * \details For example: \n
		 * \code auto answer = calculator::Math::sin<std::int64_t>(90); // = 0 \endcode
		 * \tparam T the type of evaluated variable
		 * \param expression the number for which the sine will be found
		 * \return Sine of the 'expression' or zero if answer is especially small number
		 */
		template<class T>
		static T sin(T const& expression)
		{
			T a = static_cast<T>(std::sin(expression));
			if (std::abs(a) < (1e-15))
				return 0;
			return a;
		}

		/**
		 * \brief Calculates the cosine of expression
		 * \details For example: \n
		 * \code auto answer = calculator::Math::cos<std::int64_t>(0); // = 1 \endcode
		 * \tparam T the type of evaluated variable
		 * \param expression the number for which the cosine will be found
		 * \return Cosine of the 'expression' or zero if answer is especially small number
		 */
		template<class T>
		static T cos(T const& expression)
		{
			T a = static_cast<T>(std::cos(expression));
			if (std::abs(a) < (1e-15))
				return 0;
			return a;
		}

		/**
		 * \brief Divide two number
		 * \details For example: \n
		 * \code auto answer = calculator::Math::divide<std::int64_t>(10, 2); // = 5 \endcode
		 * \tparam T the type of evaluated variable
		 * \param divisible the number which will be divided
		 * \param divider the number which will divide
		 * \throw std::range_error if divider is especially small number 
		 * \return Division result of the two numbers
		 */
		template<class T>
		static T divide(T const& divisible, T const& divider)
		{
			if (static_cast<double>(std::abs(divider)) < (1e-15))
				throw std::range_error("Division by zero exception");
			return divisible / divider;
		}
	};

	/** \class Calculator
	 * \brief Provides 'eval' function for calculate expression
	 */
	template<class T = double>
	class Calculator
	{
	public:
		/**
		 * \brief Calculate string mathematical expression
		 * \details For example: \n
		 * \code calculator::Calculator<double> calculator;
		 * calculator.eval("5 + 5"); \endcode
		 * \param expression mathematic expression to be evaluated
		 * \throw std::runtime_error if expression has incorrect format
		 * \throw std::range_error for division by zero
		 * \return The answer of the calculated expression
		 */
		T eval(std::string const& expression)
		{
			if (expression.empty())
				return 0;

			_index = 0;
			_expr = expression;

			_expr.erase(std::remove_if(_expr.begin(), _expr.end(), isspace), _expr.end());

			std::transform(_expr.begin(), _expr.end(), _expr.begin(),
				[](unsigned char const& c) { return std::tolower(c); });
			
			return parseExpression();
		}

	private:
		enum class OperationType
		{
			NULL_OP = 0,
			ADDITION,       // +
			SUBTRACTION,    // -
			MULTIPLICATION, // *
			DIVISION,		// /
			EXTENT,			// ^
			FACTORIAL,		// !
			PERCENT,		// %
		};

		class Operation
		{
		public:
			Operation(OperationType const& type,
				int const& priority,
				bool const& isRightside = false)
				: type(type), priority(priority), isRightside(isRightside)
			{}

			OperationType type;
			int priority;
			bool isRightside;
		};

		class OperationValue
		{
		public:
			OperationValue(Operation const& op, T const& value)
				: operation(op), value(value)
			{}

			bool isNullOperation() const
			{
				return (operation.type == OperationType::NULL_OP);
			}

			Operation operation;
			T value;
		};

	private:
		std::string _expr;
		std::size_t _index{};
		std::stack<OperationValue> _operations;

		const std::map<std::string, std::string> _funcWithBase{
		{ "log",  "10" },
		{ "root", "2"  } };

		const std::vector<std::string> _functions{
		"sin", "cos", "tg", "ctg", "sec", "csc", "ln", "sqrt", "exp" };
		
		const std::map<std::string, double> _constants{
		{ "e",  Math::e  },
		{ "pi", Math::pi } };

	private:
		T compute(T const& a, T const& b, Operation const& op) const
		{
			switch (op.type)
			{
			case OperationType::ADDITION:
				return (a + b);
			case OperationType::SUBTRACTION:
				return (a - b);
			case OperationType::MULTIPLICATION:
				return (a * b);
			case OperationType::DIVISION:
				return Math::divide(a, b);
			case OperationType::EXTENT:
				return std::pow(a, b);
			case OperationType::FACTORIAL:
				return Math::factorial(a);
			case OperationType::PERCENT:
				return (a / static_cast<T>(100));
			case OperationType::NULL_OP:
				return b;
			}
		}

		T compute(T const& expression, std::string const& operation, double const& base = 0) const
		{
			if (operation == "sin")
				return Math::sin(expression);
			if (operation == "cos")
				return Math::cos(expression);
			if (operation == "tg")
				return Math::divide(Math::sin(expression), Math::cos(expression));
			if (operation == "ctg")
				return Math::divide(Math::cos(expression), Math::sin(expression));
			if (operation == "sec")
				return Math::divide(static_cast<T>(1), Math::cos(expression));
			if (operation == "csc")
				return Math::divide(static_cast<T>(1), Math::sin(expression));
			if (operation == "ln")
				return std::log(expression);
			if (operation == "sqrt")
				return std::sqrt(expression);
			if (operation == "log")
				return Math::log(expression, base);
			if (operation == "root")
				return Math::root(expression, base);
			if (operation == "exp")
				return std::exp(expression);
		}

		T parseExpression()
		{
			_operations.push(OperationValue(Operation(OperationType::NULL_OP, 0), 0));

			auto value = parseToken();

			while (!_operations.empty())
			{
				auto operation = parseOperator();

				while (operation.priority <= _operations.top().operation.priority &&
					operation.isRightside == false)
				{
					if(_operations.top().isNullOperation())
					{
						_operations.pop();
						return value;
					}

					value = compute(_operations.top().value, value, _operations.top().operation);
					_operations.pop();
				}
				
				if (operation.type == OperationType::PERCENT &&
					(_operations.top().operation.type == OperationType::ADDITION ||
					_operations.top().operation.type == OperationType::SUBTRACTION))
				{
					value *= _operations.top().value;
				}

				_operations.push(OperationValue(operation, value));
				if (!_operations.top().operation.isRightside)
					value = parseToken();
			}

			return value;
		}

		Operation parseOperator()
		{
			if (_expr.size() == _index)
				return Operation{ OperationType::NULL_OP, 0 };

			switch (_expr[_index++])
			{
			case '+':
				return Operation{ OperationType::ADDITION, 1 };
			case '-':
				return Operation{ OperationType::SUBTRACTION, 1 };
			case '*':
				return Operation{ OperationType::MULTIPLICATION, 2 };
			case '/':
				return Operation{ OperationType::DIVISION, 2 };
			case '^':
				return Operation{ OperationType::EXTENT, 3 };
			case '!':
				return Operation{ OperationType::FACTORIAL, 4, true };
			case '%':
				return Operation{ OperationType::PERCENT, 5, true };
			default:
				return Operation{ OperationType::NULL_OP, 0 };
			}
		}

		T parseToken()
		{
			if (_expr.size() == _index)
				return 0;

			if (isdigit(_expr[_index]))
			{
				std::string	value;
				while (isdigit(_expr[_index]) || _expr[_index] == '.')
				{
					value += _expr[_index++];
				}
				return std::stod(value);
			}
			if (_expr[_index] == '(') //expression in parentheses
			{
				++_index;
				return parseExpression();
			}
			if (_expr[_index] == '|') //expression in module
			{
				++_index;
				return std::abs(parseExpression());
			}
			if (_expr[_index] == '-') //unary minus
			{
				++_index;
				return static_cast<T>(-1) * parseToken();
			}
			if (_expr[_index] == '+') //unary plus
			{
				++_index;
				return parseToken();
			}

			for (auto const& func : _funcWithBase)
			{
				if (std::strncmp(&_expr[_index], func.first.c_str(), func.first.length()) == 0)
				{
					_index += func.first.length();
					std::string base;
					while (isdigit(_expr[_index]))
					{
						base += _expr[_index++];
					}
					if (base.empty())
						base = func.second;
					++_index;
					return compute(parseExpression(), func.first, std::stod(base));
				}
			}

			for (auto const& func : _functions)
			{
				if (std::strncmp(&_expr[_index], func.c_str(), func.length()) == 0)
				{
					_index += func.length() + 1; // +1 for open bracket '('
					return compute(parseExpression(), func);
				}
			}

			for (auto const& constant : _constants)
			{
				if (std::strncmp(&_expr[_index], constant.first.c_str(), constant.first.length()) == 0)
				{
					_index += constant.first.length();
					return constant.second;
				}
			}

			throw std::runtime_error("Invalid token");
		}
	};

	/**
	 * \brief Calculate string mathematical expression
	 * \details For example: \n
	 * \code auto answer = calculator::eval<std::int64_t>("5 + 5"); \endcode
	 * \tparam T the type of evaluated variable 
	 * \param expression mathematic expression to be evaluated
	 * \throw std::runtime_error if expression has incorrect format
	 * \throw std::range_error for division by zero
	 * \return The answer of the calculated expression
	 */
	template<class T = double>
	T eval(std::string const& expression)
	{
		auto calc = std::make_unique<Calculator<T>>();
		return calc->eval(expression);
	}
}
