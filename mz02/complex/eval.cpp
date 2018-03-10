#include "complex.h"
#include "complex_stack.h"
#include "eval.h"

namespace numbers {

complex eval(char **args, const complex &z)
{
    complex_stack stack;
    while (*args != nullptr) {
        switch (**args) {
            case '(':
                stack = std::move(stack) << complex(*args);
                break;
            case 'z':
                stack = std::move(stack) << z;
                break;
            case '+': case '-': case '*': case '/':
                PerformBinOp(stack, **args);
                break;
            default:
                PerformUnaryOp(stack, **args);
                break;
        }
        ++args;
    }
    return +stack;
}

void PerformBinOp(complex_stack &stack, char op)
{
    complex c2 = +stack;
    stack = ~std::move(stack);
    complex c1 = +stack;
    stack = ~std::move(stack);
    complex res;
    switch (op) {
        case '+':
            res = c1 + c2;
            break;
        case '-':
            res = c1 - c2;
            break;
        case '*':
            res = c1 * c2;
            break;
        case '/':
            res = c1 / c2;
            break;
    }
    stack = std::move(stack) << res;
}

void PerformUnaryOp(complex_stack &stack, char op)
{
    complex &top_elem = +stack;
    complex c;
    switch (op) {
        case '!':
            stack = std::move(stack) << top_elem;
            break;
        case ';':
            stack = ~std::move(stack);
            break;
        case '~':
            c = ~top_elem;
            stack = (~std::move(stack)) << c;
            break;
        case '#':
            c = -top_elem;
            stack = (~std::move(stack)) << c;
            break;
    }
}

}
