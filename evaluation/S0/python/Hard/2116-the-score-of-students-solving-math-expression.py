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

class Solution(object):
    def scoreOfStudents(self, s, answers):
        """
        :type s: str
        :type answers: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7

        def compute_all_results(nums, ops):
            n = len(nums)
            dp = [[set() for _ in range(n)] for _ in range(n)]

            for i in range(n):
                dp[i][i].add(nums[i])

            for length in range(2, n + 1):
                for i in range(n - length + 1):
                    j = i + length - 1
                    for k in range(i, j):
                        for left in dp[i][k]:
                            for right in dp[k + 1][j]:
                                if ops[k] == '+':
                                    dp[i][j].add(left + right)
                                else:
                                    dp[i][j].add(left * right)

            return dp[0][n - 1]

        def evaluate_expression(s):
            nums, ops = [], []
            num = 0
            for char in s:
                if char.isdigit():
                    num = num * 10 + int(char)
                else:
                    nums.append(num)
                    ops.append(char)
                    num = 0
            nums.append(num)

            # Compute correct answer with standard precedence
            stack = []
            i = 0
            while i < len(ops):
                if ops[i] == '*':
                    last_num = stack.pop() if stack else nums[i]
                    stack.append(last_num * nums[i + 1])
                else:
                    stack.append(nums[i])
                i += 1
            correct_answer = sum(stack)

            return nums, ops, correct_answer

        nums, ops, correct_answer = evaluate_expression(s)
        all_possible_results = compute_all_results(nums, ops)

        score = 0
        for ans in answers:
            if ans == correct_answer:
                score += 5
            elif ans in all_possible_results:
                score += 2

        return score