#include <algorithm>
#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <map>

namespace calculator
{
	class Math
	{
	public:
		constexpr static double e  = 2.718281828459045;
		constexpr static double pi = 3.141592653589793;

		template<typename T>
		static T factorial(T const& n)
		{
			int res = 1;
			for (int i = 2; i <= n; ++i)
				res *= i;
			return res;
		}

		template<typename T>
		static T log(T const& expression, double const& base)
		{
			return std::log(expression) / std::log(base);
		}

		template<typename T>
		static T root(T const& expression, double const& power)
		{
			return std::pow(expression, static_cast<T>(-1) / power);
		}
	};

	template<typename T = double>
	class Calculator
	{
	public:
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
			FACTORIAL		// !
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
				return (a / b);
			case OperationType::EXTENT:
				return std::pow(a, b);
			case OperationType::FACTORIAL:
				return Math::factorial(a);
			case OperationType::NULL_OP:
				return b;
			}
			throw std::runtime_error("Bad Operation (compute function)");
		}

		T compute(T const& expression, std::string const& operation, double const& base = 0) const
		{
			if (operation == "sin")
				return std::sin(expression);
			if (operation == "cos")
				return std::cos(expression);
			if (operation == "tg")
				return (std::sin(expression) / std::cos(expression));
			if (operation == "ctg")
				return (std::cos(expression) / std::sin(expression));
			if (operation == "sec")
				return (1. / std::cos(expression));
			if (operation == "csc")
				return (1. / std::sin(expression));
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
			throw std::runtime_error("Bad Operation (trigonometric compute function)");
		}

		T parseExpression()
		{
			_operations.push(OperationValue(Operation(OperationType::NULL_OP, 0), 0));

			auto value = parseToken();

			while (!_operations.empty())
			{
				auto oper = parseOperator();

				while (oper.priority <= _operations.top().operation.priority &&
					oper.isRightside == false)
				{
					if(_operations.top().isNullOperation())
					{
						_operations.pop();
						return value;
					}

					value = compute(_operations.top().value, value, _operations.top().operation);
					_operations.pop();
				}

				_operations.push(OperationValue(oper, value));
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

			const std::map<std::string, double> constants {
				{ "e",  Math::e  },
				{ "pi", Math::pi } };
			for (auto const& constant : constants)
			{
				if (std::strncmp(&_expr[_index], constant.first.c_str(), constant.first.length()) == 0)
				{
					_index += constant.first.length();
					return constant.second;
				}
			}

			const std::string funcWithBase[]{ "log", "root" };
			for (auto const& func : funcWithBase)
			{
				if (std::strncmp(&_expr[_index], func.c_str(), func.length()) == 0)
				{
					_index += func.length();
					std::string base;
					while (isdigit(_expr[_index]))
					{
						base += _expr[_index++];
					}
					if (base.empty())
						base = (func == "log") ? "10" : "2";
					++_index;
					return compute(parseExpression(), func, std::stod(base));
				}
			}

			const std::string functions[]{ "sin", "cos", "tg", "ctg", "sec", "csc", "ln", "sqrt", "exp" };
			for (auto const& func : functions)
			{
				if (std::strncmp(&_expr[_index], func.c_str(), func.length()) == 0)
				{
					_index += func.length() + 1; // +1 for open bracket '('
					return compute(parseExpression(), func);
				}
			}

			throw std::runtime_error("Invalid token (parseToken function)");
		}
	};

	template<typename T = double>
	T eval(std::string const& expression)
	{
		Calculator<T> calc;
		return calc.eval(expression);
	}
}

int main()
{
	const std::string expression { "|e^pi| - (-1)" };

	try
	{
		std::cout << std::fixed << calculator::eval<double>(expression) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
