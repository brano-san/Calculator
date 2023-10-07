<h1 align="center">
  Calculator
</h1>
  
<p align="center">
  An Awesome Open Source Calculator To Use It In Your Project
  <br/>
</p>

## Table Of Contents
* [About the Project](#about-the-project)
* [Getting Started](#getting-started)
  * [Installation](#installation)
* [Usage](#usage)
  * [Supported Operations And Functions](#supported-operations-and-functions)
  * [Supported Constants](#supported-constants)
  * [Example](#example)
* [License](#license)
* [Authors](#authors)

## About The Project

A Сalculator is a template expression parser that accepts a string expression and returns an answer

```C++
template<class T = double>
T eval(std::string const& expression);
```

## Getting Started

### Installation

1. Get ```Calculator.h``` on your project folder
2. Connect ```Calculator.h``` to project file

```C++
#include "Calculator.h"
```

## Usage

### Supported Operations And Functions

<table>
  <tr align="center">
    <td><b> Operation/Function </b></td>
    <td><b> Description </b></td>
    <td><b> Example </b></td>
    <td><b> Result </b></td>
  </tr>
  <tr align="center">
    <td> + </td>
    <td> Unary/Binary Plus Operation </td>
    <td> "+10" <br/> "10 + 5" </td>
    <td> 10 <br/> 15 </td>
  </tr>
  <tr align="center">
    <td>-</td>
    <td> Unary/Binary Minus Operation </td>
    <td> "-10" <br/> "10 - 4.5" </td>
    <td> -10 <br/> 5.5 </td>
  </tr>
  <tr align="center">
    <td> * </td>
    <td> Binary Multiplication Operation </td>
    <td> "100 * 0.75" </td>
    <td> 75 </td>
  </tr>
  <tr align="center">
    <td> / </td>
    <td> Binary Division Operation </td>
    <td> "1024 / 256" </td>
    <td> 4 </td>
  </tr>
  <tr align="center">
    <td> ^ </td>
    <td> Exponentiation </td>
    <td> "2 ^ 10" </td>
    <td> 1024 </td>
  </tr>
  <tr align="center">
    <td> ! </td>
    <td> Factorial </td>
    <td> "5!" </td>
    <td> 120 </td>
  </tr>
  <tr align="center">
    <td> % </td>
    <td> Percent </td>
    <td> "1000 * 50%" <br/> "1000 + 50%" </td>
    <td> 500 <br/> 1500 </td>
  </tr>
  <tr align="center">
    <td> ln <br /> log </td>
    <td> Natural Logarithm <br /> Logarithm With Any Base </td>
    <td> "ln(2.718281)" <br/> "log6(36)" </td>
    <td> 1 <br/> 2 </td>
  </tr>
  <tr align="center">
    <td> sqrt <br /> root </td>
    <td> Square Root <br /> Root Of Any Degree </td>
    <td> "sqrt(100)" <br /> "root10(1024)" </td>
    <td> 10 <br /> 2 </td>
  </tr>
  <tr align="center">
    <td> exp </td>
    <td> Exponential Function </td>
    <td> "exp(2)" </td>
    <td> 7.389056 </td>
  </tr>
  <tr align="center">
    <td> sin </td>
    <td> Sine Function </td>
    <td> "sin(120)" </td>
    <td> 0.580611 </td>
  </tr>
  <tr align="center">
    <td> cos </td>
    <td> Cosine Function </td>
    <td> "cos(120)" </td>
    <td> 0.814181 </td>
  </tr>
  <tr align="center">
    <td> tg </td>
    <td> Tangent Function </td>
    <td> "tg(120)" </td>
    <td> 0.713123 </td>
  </tr>
  <tr align="center">
    <td> ctg </td>
    <td> Cotangent Function </td>
    <td> "ctg(120)" </td>
    <td> 1.40228 </td>
  </tr>
  <tr align="center">
    <td> sec </td>
    <td> Secant Function </td>
    <td> "sec(120)" </td>
    <td> 1.22823 </td>
  </tr>
  <tr align="center">
    <td> csc </td>
    <td> Cosecant Function </td>
    <td> "csc(120)" </td>
    <td> 1.72232 </td>
  </tr>
  <tr align="center">
    <td> (expr) </td>
    <td> Expression In Parentheses </td>
    <td> "10 - (4 + 1)" </td>
    <td> 5 </td>
  </tr>
  <tr align="center">
    <td> |expr| </td>
    <td> Module </td>
    <td> "|-5|" </td>
    <td> 5 </td>
  </tr>
</table>

### Supported Constants

<table>
  <tr align="center">
    <td><b> Constant </b></td>
    <td><b> Description </b></td>
    <td><b> Example </b></td>
    <td><b> Result </b></td>
  </tr>
  <tr align="center">
    <td> pi </td>
    <td> Mathematical Constant Pi </td>
    <td> "sin(pi / 2)" </td>
    <td> 1 </td>
  </tr>
  <tr align="center">
    <td> e </td>
    <td> Mathematical Constant Exponent </td>
    <td> "ln(e)" </td>
    <td> 1 </td>
  </tr>
</table>

### Example
Here the way to use Calculator via ```calculator::eval<double>(expression)``` function
```C++
const std::string expressions[]{ "(log10(10) - cos(pi)) * sin(pi / 2)",
    "(-4) * 5.5 + 3.2 * sec(90)^2",
    "root5(3125) / |ln(e^e) * exp(2.5)|",
    "300 * 50%" };
try
{
    for (const auto& expression : expressions)
    {
        std::cout << calculator::eval<double>(expression) << std::endl;
    }
}
catch (std::exception& e)
{
    std::cout << e.what() << std::endl;
}
```

## License

Distributed under the MIT License. See [LICENSE](https://github.com/brano-san/Calculator/blob/master/LICENSE.md) for more information.

## Authors

* **Andrey** - *Student* - [brano-san](https://github.com/brano-san) - *All work*

[![Contributors](https://img.shields.io/github/contributors/brano-san/Calculator?color=dark-green)](https://github.com/brano-san/Calculator/graphs/contributors)
[![License](https://img.shields.io/github/license/brano-san/Calculator)](https://github.com/brano-san/Calculator/blob/master/LICENSE.md) 
