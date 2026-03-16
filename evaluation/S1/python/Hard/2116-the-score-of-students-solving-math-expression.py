# Source: https://leetcode.com/problems/the-score-of-students-solving-math-expression/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s that contains digits 0-9, addition symbols '+', and multiplication symbols '*' only, representing a valid math expression of single digit numbers (e.g., 3+5*2). This expression was given to n elementary school students. The students were instructed to get the answer of the expression by following this order of operations:
#
#
# 	Compute multiplication, reading from left to right; Then,
# 	Compute addition, reading from left to right.
#
#
# You are given an integer array answers of length n, which are the submitted answers of the students in no particular order. You are asked to grade the answers, by following these rules:
#
#
# 	If an answer equals the correct answer of the expression, this student will be rewarded 5 points;
# 	Otherwise, if the answer could be interpreted as if the student applied the operators in the wrong order but had correct arithmetic, this student will be rewarded 2 points;
# 	Otherwise, this student will be rewarded 0 points.
#
#
# Return the sum of the points of the students.
#
# Example:
# Input: s = "7+3*1*2", answers = [20,13,42]
# Output: 7
# Explanation: As illustrated above, the correct answer of the expression is 13, therefore one student is rewarded 5 points: [20,13,42]
# A student might have applied the operators in this wrong order: ((7+3)*1)*2 = 20. Therefore one student is rewarded 2 points: [20,13,42]
# The points for the students are: [2,5,0]. The sum of the points is 2+5+0=7.
#
# Constraints:
# 3 <= s.length <= 31
# 	s represents a valid expression that contains only digits 0-9, '+', and '*' only.
# 	All the integer operands in the expression are in the inclusive range [0, 9].
# 	1 <= The count of all operators ('+' and '*') in the math expression <= 15
# 	Test data are generated such that the correct answer of the expression is in the range of [0, 1000].
# 	Test data are generated such that value never exceeds 109 in intermediate steps of multiplication.
# 	n == answers.length
# 	1 <= n <= 104
# 	0 <= answers[i] <= 1000
#
# Helpful references (internal KB):
# - Expression parsing (stack, simulation)
#   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
#   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
#   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
#   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
#   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
# - Knapsack Problem (array, knapsack, dp-1d, enumeration)
#   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
#   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
#   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
#   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
#   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def scoreOfStudents(self, s, answers):
        """
        :type s: str
        :type answers: List[int]
        :rtype: int
        """
        # 1. 计算正确答案
        def evaluate(expr):
            # 这里我们直接使用 Python 的 eval 来计算表达式的值
            return eval(expr)
        correct_answer = evaluate(s)

        # 2. 计算所有可能的错误答案
        from collections import defaultdict
        def compute_all_results(expr):
            n = len(expr)
            dp = defaultdict(set)

            # 初始化 dp 表
            for i in range(0, n, 2):
                dp[(i, i)].add(int(expr[i]))

            # 枚举子表达式长度
            for length in range(3, n + 1, 2):
                for i in range(0, n - length + 1, 2):
                    j = i + length - 1
                    for k in range(i + 1, j, 2):
                        op = expr[k]
                        for left in dp[(i, k - 1)]:
                            for right in dp[(k + 1, j)]:
                                if op == '+':
                                    dp[(i, j)].add(left + right)
                                elif op == '*':
                                    dp[(i, j)].add(left * right)
            return dp[(0, n - 1)]
        possible_answers = compute_all_results(s)

        # 3. 评分
        score = 0
        for ans in answers:
            if ans == correct_answer:
                score += 5
            elif ans in possible_answers:
                score += 2
        return score    