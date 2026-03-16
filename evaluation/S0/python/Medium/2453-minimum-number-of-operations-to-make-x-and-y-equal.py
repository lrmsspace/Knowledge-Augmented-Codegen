# Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-x-and-y-equal/   |   Difficulty: Medium
#
# Problem Description:
# You are given two positive integers x and y.
#
# In one operation, you can do one of the four following operations:
#
#
# 	Divide x by 11 if x is a multiple of 11.
# 	Divide x by 5 if x is a multiple of 5.
# 	Decrement x by 1.
# 	Increment x by 1.
#
#
# Return the minimum number of operations required to make  x and y equal.
#
# Example:
# Input: x = 26, y = 1
# Output: 3
# Explanation: We can make 26 equal to 1 by applying the following operations: 
# 1. Decrement x by 1
# 2. Divide x by 5
# 3. Divide x by 5
# It can be shown that 3 is the minimum number of operations required to make 26 equal to 1.
#
# Constraints:
# 1 <= x, y <= 104
#

class Solution(object):
    def minimumOperationsToMakeEqual(self, x, y):
        """
        :type x: int
        :type y: int
        :rtype: int
        """
        from collections import deque

        if x == y:
            return 0

        queue = deque([(x, 0)])  # (current value, operations count)
        visited = set([x])

        while queue:
            current, ops = queue.popleft()

            for next_val in [current - 1, current + 1] + ([current // 11] if current % 11 == 0 else []) + ([current // 5] if current % 5 == 0 else []):
                if next_val == y:
                    return ops + 1
                if 0 < next_val <= 20000 and next_val not in visited:
                    visited.add(next_val)
                    queue.append((next_val, ops + 1))

        return -1  # This line should never be reached