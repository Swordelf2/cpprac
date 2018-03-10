#ifndef _EVAL_H
#define _EVAL_H

#include "complex.h"
#include "complex_stack.h"

namespace numbers {

complex eval(char **args, const complex &z);

void PerformBinOp(complex_stack &stack, char op);
void PerformUnaryOp(complex_stack &stack, char op);

}

#endif
