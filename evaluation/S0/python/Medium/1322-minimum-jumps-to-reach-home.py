# Source: https://leetcode.com/problems/minimum-jumps-to-reach-home/   |   Difficulty: Medium
#
# Problem Description:
# A certain bug's home is on the x-axis at position x. Help them get there from position 0.
#
# The bug jumps according to the following rules:
#
#
# 	It can jump exactly a positions forward (to the right).
# 	It can jump exactly b positions backward (to the left).
# 	It cannot jump backward twice in a row.
# 	It cannot jump to any forbidden positions.
#
#
# The bug may jump forward beyond its home, but it cannot jump to positions numbered with negative integers.
#
# Given an array of integers forbidden, where forbidden[i] means that the bug cannot jump to the position forbidden[i], and integers a, b, and x, return the minimum number of jumps needed for the bug to reach its home. If there is no possible sequence of jumps that lands the bug on position x, return -1.
#
# Example:
# Input: forbidden = [14,4,18,1,15], a = 3, b = 15, x = 9
# Output: 3
# Explanation: 3 jumps forward (0 -> 3 -> 6 -> 9) will get the bug home.
#
# Constraints:
# 1 <= forbidden.length <= 1000
# 	1 <= a, b, forbidden[i] <= 2000
# 	0 <= x <= 2000
# 	All the elements in forbidden are distinct.
# 	Position x is not forbidden.
#

class Solution(object):
    def minimumJumps(self, forbidden, a, b, x):
        """
        :type forbidden: List[int]
        :type a: int
        :type b: int
        :type x: int
        :rtype: int
        """
        from collections import deque

        forbidden_set = set(forbidden)
        visited = set()
        queue = deque([(0, 0, False)])  # (position, jumps, last_was_backward)
        max_limit = max(forbidden + [x]) + a + b

        while queue:
            position, jumps, last_was_backward = queue.popleft()

            if position == x:
                return jumps

            # Jump forward
            next_forward = position + a
            if (0 <= next_forward <= max_limit and
                next_forward not in forbidden_set and
                (next_forward, False) not in visited):
                visited.add((next_forward, False))
                queue.append((next_forward, jumps + 1, False))

            # Jump backward
            if not last_was_backward:
                next_backward = position - b
                if (0 <= next_backward and
                    next_backward not in forbidden_set and
                    (next_backward, True) not in visited):
                    visited.add((next_backward, True))
                    queue.append((next_backward, jumps + 1, True))

        return -1