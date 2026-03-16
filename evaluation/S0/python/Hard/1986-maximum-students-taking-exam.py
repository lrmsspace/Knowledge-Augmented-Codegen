# Source: https://leetcode.com/problems/maximum-students-taking-exam/   |   Difficulty: Hard
#
# Problem Description:
# Given a m * n matrix seats  that represent seats distributions in a classroom. If a seat is broken, it is denoted by '#' character otherwise it is denoted by a '.' character.
#
# Students can see the answers of those sitting next to the left, right, upper left and upper right, but he cannot see the answers of the student sitting directly in front or behind him. Return the maximum number of students that can take the exam together without any cheating being possible.
#
# Students must be placed in seats in good condition.
#
# Example:
# Input: seats = [["#",".","#","#",".","#"],
#                 [".","#","#","#","#","."],
#                 ["#",".","#","#",".","#"]]
# Output: 4
# Explanation: Teacher can place 4 students in available seats so they don't cheat on the exam.
#
# Constraints:
# seats contains only characters '.' and'#'.
# 	m == seats.length
# 	n == seats[i].length
# 	1 <= m <= 8
# 	1 <= n <= 8
#

class Solution(object):
    def maxStudents(self, seats):
        """
        :type seats: List[List[str]]
        :rtype: int
        """
        m, n = len(seats), len(seats[0])
        valid = []
        for row in seats:
            mask = 0
            for c in row:
                mask = (mask << 1) + (c == '.')
            valid.append(mask)

        dp = [[0] * (1 << n) for _ in range(m + 1)]
        for i in range(1, m + 1):
            for state in range(1 << n):
                if (state & valid[i - 1]) != state or (state & (state >> 1)) != 0:
                    continue
                for prev in range(1 << n):
                    if (state & (prev >> 1)) != 0 or (state & (prev << 1)) != 0:
                        continue
                    dp[i][state] = max(dp[i][state], dp[i - 1][prev] + bin(state).count('1'))
        return max(dp[m])