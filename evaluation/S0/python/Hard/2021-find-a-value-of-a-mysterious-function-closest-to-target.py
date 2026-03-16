# Source: https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/   |   Difficulty: Hard
#
# Problem Description:
# Winston was given the above mysterious function func. He has an integer array arr and an integer target and he wants to find the values l and r that make the value |func(arr, l, r) - target| minimum possible.
#
# Return the minimum possible value of |func(arr, l, r) - target|.
#
# Notice that func should be called with the values l and r where 0 <= l, r < arr.length.
#
# Example:
# Input: arr = [9,12,3,7,15], target = 5
# Output: 2
# Explanation: Calling func with all the pairs of [l,r] = [[0,0],[1,1],[2,2],[3,3],[4,4],[0,1],[1,2],[2,3],[3,4],[0,2],[1,3],[2,4],[0,3],[1,4],[0,4]], Winston got the following results [9,12,3,7,15,8,0,3,7,0,0,3,0,0,0]. The value closest to 5 is 7 and 3, thus the minimum difference is 2.
#
# Constraints:
# 1 <= arr.length <= 105
# 	1 <= arr[i] <= 106
# 	0 <= target <= 107
#

class Solution(object):
    def closestToTarget(self, arr, target):
        """
        :type arr: List[int]
        :type target: int
        :rtype: int
        """
        possible_ands = set()
        result = float('inf')

        for num in arr:
            new_ands = {num}
            for prev_and in possible_ands:
                new_ands.add(prev_and & num)
            possible_ands = new_ands

            for val in possible_ands:
                result = min(result, abs(val - target))

        return result