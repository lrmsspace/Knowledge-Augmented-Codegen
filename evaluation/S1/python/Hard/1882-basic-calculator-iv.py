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
# Helpful references (internal KB):
# - Operations on polynomials and series (array, recursion)
#   • When to use: When problems involve manipulating algebraic polynomials or power series, especially when their properties or coefficients are defined recursively. It is also useful for problems involving generating functions to represent sequences.
#   • Idea: This card describes recursive approaches to perform common operations on polynomials and power series, often represented by their coefficients. The complexity varies depending on the specific operation, but many are O(N^2) or O(N log N) with optimized techniques.
#   • Invariants: For a polynomial represented by P[0...N-1], P[i] always stores the coefficient of x^i.; When performing an operation recursively, the result of subproblems correctly represents the corresponding sub-polynomial or sub-series.
#   • Tips: Represent polynomials as arrays of coefficients.; Base cases for recursion are crucial (e.g., constant polynomial, empty series).
#   • Pitfalls: Incorrectly handling polynomial degrees or series truncation.; Off-by-one errors in coefficient indexing.
# - Expression parsing (stack, simulation)
#   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
#   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
#   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
#   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
#   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
# - String Hashing (string, number, hashing, prefix-sum)
#   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
#   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
#   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
#   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
#   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def basicCalculatorIV(self, expression, evalvars, evalints):
        """
        :type expression: str
        :type evalvars: List[str]
        :type evalints: List[int]
        :rtype: List[str]
        """
        from collections import defaultdict
        import re

        # Map variable evaluations
        eval_map = dict(zip(evalvars, evalints))

        def parse_expression(expr):
            tokens = re.findall(r'\w+|[()+\-*]', expr)
            return tokens

        def precedence(op):
            if op in ('+', '-'):
                return 1
            if op == '*':
                return 2
            return 0

        def apply_operator(operators, values):
            right = values.pop()
            left = values.pop()
            op = operators.pop()

            if op == '+':
                values.append(add_polynomials(left, right))
            elif op == '-':
                values.append(subtract_polynomials(left, right))
            elif op == '*':
                values.append(multiply_polynomials(left, right))

        def add_polynomials(p1, p2):
            result = defaultdict(int)
            for k, v in p1.items():
                result[k] += v
            for k, v in p2.items():
                result[k] += v
            return {k: v for k, v in result.items() if v != 0}

        def subtract_polynomials(p1, p2):
            result = defaultdict(int)
            for k, v in p1.items():
                result[k] += v
            for k, v in p2.items():
                result[k] -= v
            return {k: v for k, v in result.items() if v != 0}

        def multiply_polynomials(p1, p2):
            result = defaultdict(int)
            for k1, v1 in p1.items():
                for k2, v2 in p2.items():
                    new_key = tuple(sorted(k1 + k2))
                    result[new_key] += v1 * v2
            return {k: v for k, v in result.items() if v != 0}

        def evaluate(tokens):
            values = []
            operators = []

            i = 0
            while i < len(tokens):
                token = tokens[i]

                if token == ' ':
                    i += 1
                    continue

                if token == '(':
                    operators.append(token)
                elif token == ')':
                    while operators and operators[-1] != '(':
                        apply_operator(operators, values)
                    operators.pop()
                elif token in '+-*':
                    while (operators and precedence(operators[-1]) >= precedence(token)):
                        apply_operator(operators, values)

                    operators.append(token)
                else:
                    if token.isdigit() or (token[0] == '-' and token[1:].isdigit()):
                        values.append({(): int(token)})
                    else:
                        if token in eval_map:
                            values.append({(): eval_map[token]})
                        else:
                            values.append({(token,): 1})
                i += 1
            while operators:
                apply_operator(operators, values)
            return values[0]
        tokens = parse_expression(expression)
        poly = evaluate(tokens)
        sorted_terms = sorted(poly.items(), key=lambda x: (-len(x[0]), x[0]))
        result = []
        for vars_tuple, coeff in sorted_terms:
            if coeff == 0:
                continue
            term = str(coeff)
            if vars_tuple:
                term += '*' + '*'.join(vars_tuple)
            result.append(term)
        return result   
            