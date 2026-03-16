# Source: https://leetcode.com/problems/basic-calculator-iv/   |   Difficulty: Hard
#
# Problem Description:
# Given an expression such as expression = "e + 8 - a + 5" and an evaluation map such as {"e": 1} (given in terms of evalvars = ["e"] and evalints = [1]), return a list of tokens representing the simplified expression, such as ["-1*a","14"]
#
#
# 	An expression alternates chunks and symbols, with a space separating each chunk and symbol.
# 	A chunk is either an expression in parentheses, a variable, or a non-negative integer.
# 	A variable is a string of lowercase letters (not including digits.) Note that variables can be multiple letters, and note that variables never have a leading coefficient or unary operator like "2x" or "-x".
#
#
# Expressions are evaluated in the usual order: brackets first, then multiplication, then addition and subtraction.
#
#
# 	For example, expression = "1 + 2 * 3" has an answer of ["7"].
#
#
# The format of the output is as follows:
#
#
# 	For each term of free variables with a non-zero coefficient, we write the free variables within a term in sorted order lexicographically.
# 	
# 		For example, we would never write a term like "b*a*c", only "a*b*c".
# 	
# 	
# 	Terms have degrees equal to the number of free variables being multiplied, counting multiplicity. We write the largest degree terms of our answer first, breaking ties by lexicographic order ignoring the leading coefficient of the term.
# 	
# 		For example, "a*a*b*c" has degree 4.
# 	
# 	
# 	The leading coefficient of the term is placed directly to the left with an asterisk separating it from the variables (if they exist.) A leading coefficient of 1 is still printed.
# 	An example of a well-formatted answer is ["-2*a*a*a", "3*a*a*b", "3*b*b", "4*a", "5*c", "-6"].
# 	Terms (including constant terms) with coefficient 0 are not included.
# 	
# 		For example, an expression of "0" has an output of [].
# 	
# 	
#
#
# Note: You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].
#
# Example:
# Input: expression = "e + 8 - a + 5", evalvars = ["e"], evalints = [1]
# Output: ["-1*a","14"]
#
# Constraints:
# 1 <= expression.length <= 250
# 	expression consists of lowercase English letters, digits, '+', '-', '*', '(', ')', ' '.
# 	expression does not contain any leading or trailing spaces.
# 	All the tokens in expression are separated by a single space.
# 	0 <= evalvars.length <= 100
# 	1 <= evalvars[i].length <= 20
# 	evalvars[i] consists of lowercase English letters.
# 	evalints.length == evalvars.length
# 	-100 <= evalints[i] <= 100
#

class Solution(object):
    def basicCalculatorIV(self, expression, evalvars, evalints):
        """
        :type expression: str
        :type evalvars: List[str]
        :type evalints: List[int]
        :rtype: List[str]
        """
        import re
        from collections import defaultdict

        eval_map = {var: val for var, val in zip(evalvars, evalints)}

        def parse(expr):
            tokens = re.findall(r'\d+|[a-z]+|[()+\-*]', expr)
            return tokens

        def to_postfix(tokens):
            precedence = {'+': 1, '-': 1, '*': 2}
            output = []
            stack = []

            for token in tokens:
                if token.isalnum():
                    output.append(token)
                elif token == '(':
                    stack.append(token)
                elif token == ')':
                    while stack and stack[-1] != '(':
                        output.append(stack.pop())
                    stack.pop()
                else:
                    while (stack and stack[-1] != '(' and
                           precedence[stack[-1]] >= precedence[token]):
                        output.append(stack.pop())
                    stack.append(token)

            while stack:
                output.append(stack.pop())

            return output

        def eval_postfix(postfix):
            stack = []

            for token in postfix:
                if token.isalnum():
                    if token.isdigit():
                        stack.append({(): int(token)})
                    else:
                        if token in eval_map:
                            stack.append({(): eval_map[token]})
                        else:
                            stack.append({(token,): 1})
                else:
                    b = stack.pop()
                    a = stack.pop()
                    if token == '+':
                        res = defaultdict(int)
                        for k, v in a.items():
                            res[k] += v
                        for k, v in b.items():
                            res[k] += v
                        stack.append(dict(res))
                    elif token == '-':
                        res = defaultdict(int)
                        for k, v in a.items():
                            res[k] += v
                        for k, v in b.items():
                            res[k] -= v
                        stack.append(dict(res))
                    elif token == '*':
                        res = defaultdict(int)
                        for ka, va in a.items():
                            for kb, vb in b.items():
                                new_key = tuple(sorted(ka + kb))
                                res[new_key] += va * vb
                        stack.append(dict(res))

            return stack[0]

        tokens = parse(expression)
        postfix = to_postfix(tokens)
        result_map = eval_postfix(postfix)

        result_terms = []
        for k, v in result_map.items():
            if v != 0:
                term = '*'.join([str(v)] + list(k)) if k else [str(v)]
                result_terms.append((len(k), k, term))
        result_terms.sort(key=lambda x: (-x[0], x[1]))
        return ['*'.join(term) for _, _, term in result_terms]