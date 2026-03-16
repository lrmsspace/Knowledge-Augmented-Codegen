# Source: https://leetcode.com/problems/pyramid-transition-matrix/   |   Difficulty: Medium
#
# Problem Description:
# You are stacking blocks to form a pyramid. Each block has a color, which is represented by a single letter. Each row of blocks contains one less block than the row beneath it and is centered on top.
#
# To make the pyramid aesthetically pleasing, there are only specific triangular patterns that are allowed. A triangular pattern consists of a single block stacked on top of two blocks. The patterns are given as a list of three-letter strings allowed, where the first two characters of a pattern represent the left and right bottom blocks respectively, and the third character is the top block.
#
#
# 	For example, "ABC" represents a triangular pattern with a 'C' block stacked on top of an 'A' (left) and 'B' (right) block. Note that this is different from "BAC" where 'B' is on the left bottom and 'A' is on the right bottom.
#
#
# You start with a bottom row of blocks bottom, given as a single string, that you must use as the base of the pyramid.
#
# Given bottom and allowed, return true if you can build the pyramid all the way to the top such that every triangular pattern in the pyramid is in allowed, or false otherwise.
#
# Example:
# Input: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
# Output: true
# Explanation: The allowed triangular patterns are shown on the right.
# Starting from the bottom (level 3), we can build "CE" on level 2 and then build "A" on level 1.
# There are three triangular patterns in the pyramid, which are "BCC", "CDE", and "CEA". All are allowed.
#
# Constraints:
# 2 <= bottom.length <= 6
# 	0 <= allowed.length <= 216
# 	allowed[i].length == 3
# 	The letters in all input strings are from the set {'A', 'B', 'C', 'D', 'E', 'F'}.
# 	All the values of allowed are unique.
#

class Solution(object):
    def pyramidTransition(self, bottom, allowed):
        """
        :type bottom: str
        :type allowed: List[str]
        :rtype: bool
        """
        from collections import defaultdict

        allowed_map = defaultdict(list)
        for triple in allowed:
            allowed_map[triple[:2]].append(triple[2])

        def can_build(current_level):
            if len(current_level) == 1:
                return True

            next_level_options = []

            for i in range(len(current_level) - 1):
                pair = current_level[i:i+2]
                if pair not in allowed_map:
                    return False
                next_level_options.append(allowed_map[pair])

            def backtrack(index, next_level):
                if index == len(next_level_options):
                    return can_build(''.join(next_level))

                for block in next_level_options[index]:
                    next_level.append(block)
                    if backtrack(index + 1, next_level):
                        return True
                    next_level.pop()

                return False

            return backtrack(0, [])

        return can_build(bottom)