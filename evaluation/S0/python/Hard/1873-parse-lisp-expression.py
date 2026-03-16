# Source: https://leetcode.com/problems/parse-lisp-expression/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string expression representing a Lisp-like expression to return the integer value of.
#
# The syntax for these expressions is given as follows.
#
#
# 	An expression is either an integer, let expression, add expression, mult expression, or an assigned variable. Expressions always evaluate to a single integer.
# 	(An integer could be positive or negative.)
# 	A let expression takes the form "(let v1 e1 v2 e2 ... vn en expr)", where let is always the string "let", then there are one or more pairs of alternating variables and expressions, meaning that the first variable v1 is assigned the value of the expression e1, the second variable v2 is assigned the value of the expression e2, and so on sequentially; and then the value of this let expression is the value of the expression expr.
# 	An add expression takes the form "(add e1 e2)" where add is always the string "add", there are always two expressions e1, e2 and the result is the addition of the evaluation of e1 and the evaluation of e2.
# 	A mult expression takes the form "(mult e1 e2)" where mult is always the string "mult", there are always two expressions e1, e2 and the result is the multiplication of the evaluation of e1 and the evaluation of e2.
# 	For this question, we will use a smaller subset of variable names. A variable starts with a lowercase letter, then zero or more lowercase letters or digits. Additionally, for your convenience, the names "add", "let", and "mult" are protected and will never be used as variable names.
# 	Finally, there is the concept of scope. When an expression of a variable name is evaluated, within the context of that evaluation, the innermost scope (in terms of parentheses) is checked first for the value of that variable, and then outer scopes are checked sequentially. It is guaranteed that every expression is legal. Please see the examples for more details on the scope.
#
# Example:
# Input: expression = "(let x 2 (mult x (let x 3 y 4 (add x y))))"
# Output: 14
# Explanation: In the expression (add x y), when checking for the value of the variable x,
# we check from the innermost scope to the outermost in the context of the variable we are trying to evaluate.
# Since x = 3 is found first, the value of x is 3.
#
# Constraints:
# 1 <= expression.length <= 2000
# 	There are no leading or trailing spaces in expression.
# 	All tokens are separated by a single space in expression.
# 	The answer and all intermediate calculations of that answer are guaranteed to fit in a 32-bit integer.
# 	The expression is guaranteed to be legal and evaluate to an integer.
#

class Solution(object):
    def evaluate(self, expression):
        """
        :type expression: str
        :rtype: int
        """
        def helper(expr, scope):
            if expr[0] != '(':
                if expr.lstrip('-').isdigit():
                    return int(expr)
                return scope[expr][-1]

            tokens = []
            balance = 0
            current = ''
            for char in expr[1:-1]:
                if char == ' ' and balance == 0:
                    if current:
                        tokens.append(current)
                        current = ''
                else:
                    if char == '(':
                        balance += 1
                    elif char == ')':
                        balance -= 1
                    current += char
            if current:
                tokens.append(current)

            if tokens[0] == 'let':
                new_scope = {k: v[:] for k, v in scope.items()}
                i = 1
                while i < len(tokens) - 1:
                    var = tokens[i]
                    val = helper(tokens[i + 1], new_scope)
                    if var not in new_scope:
                        new_scope[var] = []
                    new_scope[var].append(val)
                    i += 2
                return helper(tokens[-1], new_scope)

            elif tokens[0] == 'add':
                return helper(tokens[1], scope) + helper(tokens[2], scope)

            elif tokens[0] == 'mult':
                return helper(tokens[1], scope) * helper(tokens[2], scope)

        return helper(expression, {})