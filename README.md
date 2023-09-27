<h1 align="center">
  Calculator
</h1>

<p align="center">
  An Awesome Calculator To Use It In Your Project
  <br/>
</p>

## Table Of Contents
* [About the Project](#about-the-project)
* [Getting Started](#getting-started)
  * [Installation](#installation)
* [Usage](#usage)
  * [Supported Operations And Functions](#supported-operations-and-functions)
  * [Example](#example)
* [License](#license)
* [Authors](#authors)

## About The Project

Calculator is an expression parser that takes a string expression and returns an answer

```C++
double eval(std::string const& expression);
```

## Getting Started

Here is a way how you can use the Calculator in your project

### Installation

1. Get ```Calculator.hpp``` on your project folder
2. Connect ```Calculator.hpp``` to project file

```C++
#include "Calculator.hpp"
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
    <td> (+10) <br/> 10 + 5 </td>
    <td> 10 <br/> 15 </td>
  </tr>
  <tr align="center">
    <td>-</td>
    <td> Unary/Binary Minus Operation </td>
    <td> (-10) <br/> 10 - 4.5 </td>
    <td> -10 <br/> 5.5 </td>
  </tr>
  <tr align="center">
    <td> * </td>
    <td> Binary Multiplication Operation </td>
    <td> 100 * 0.75 </td>
    <td> 75 </td>
  </tr>
  <tr align="center">
    <td> / </td>
    <td> Binary Division Operation </td>
    <td> 1024 / 256 </td>
    <td> 4 </td>
  </tr>
  <tr align="center">
    <td> ^ </td>
    <td> Exponentiation </td>
    <td> 5 ^ 5 </td>
    <td> 3125 </td>
  </tr>
  <tr align="center">
    <td> ! </td>
    <td> Factorial </td>
    <td> 5! </td>
    <td> 120 </td>
  </tr>
  <tr align="center">
    <td> log </td>
    <td> Logarithm With Any Base </td>
    <td> ln(2.718281) <br/> log6(36) </td>
    <td> 1 <br/> 2 </td>
  </tr>
  <tr align="center">
    <td> root </td>
    <td> Any Root Extent </td>
    <td> sqrt(100) <br/> root10(1024) </td>
    <td> 10 <br/> 2 </td>
  </tr>
  <tr align="center">
    <td> sin </td>
    <td> Sine Function </td>
    <td> sin(120) </td>
    <td> 0.580611 </td>
  </tr>
  <tr align="center">
    <td> cos </td>
    <td> Cosine Function </td>
    <td> cos(120) </td>
    <td> 0.814181 </td>
  </tr>
  <tr align="center">
    <td> tg </td>
    <td> Tangent Function </td>
    <td> tg(120) </td>
    <td> 0.713123 </td>
  </tr>
  <tr align="center">
    <td> ctg </td>
    <td> Cotangent Function </td>
    <td> ctg(120) </td>
    <td> 1.40228 </td>
  </tr>
  <tr align="center">
    <td> sec </td>
    <td> Secant Function </td>
    <td> sec(120) </td>
    <td> 1.22823 </td>
  </tr>
  <tr align="center">
    <td> csc </td>
    <td> Cosecant Function </td>
    <td> csc(120) </td>
    <td> 1.72232 </td>
  </tr>
</table>

### Example
Here is examples how to use it
```C++
const std::string expressions[]{ "(sin(120) - cos(360)) * tg(90)",
    "(-4) * 5.5 + 3.2 * sec(90)^2",
    "(((((((10))))))) - (((((((5)))))))" };
try
{
    calculator::Calculator calculator;
    for (const auto& expression : expressions)
    {
        std::cout << calculator.eval(expression) << std::endl;
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
