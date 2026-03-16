# Source: https://leetcode.com/problems/combination-sum-iii/   |   Difficulty: Medium
#
# Problem Description:
# Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
#
#
# 	Only numbers 1 through 9 are used.
# 	Each number is used at most once.
#
#
# Return a list of all possible valid combinations. The list must not contain the same combination twice, and the combinations may be returned in any order.
#
# Example:
# Input: k = 3, n = 7
# Output: [[1,2,4]]
# Explanation:
# 1 + 2 + 4 = 7
# There are no other valid combinations.
#
# Constraints:
# 2 <= k <= 9
# 	1 <= n <= 60
#

class Solution(object):
    def combinationSum3(self, k, n):
        """
        :type k: int
        :type n: int
        :rtype: List[List[int]]
        """
        res = []
        
        def backtrack(start, path, remaining_k, remaining_n):
            if remaining_k == 0 and remaining_n == 0:
                res.append(path)
                return
            if remaining_k < 0 or remaining_n < 0:
                return
            
            for i in range(start, 10):
                backtrack(i + 1, path + [i], remaining_k - 1, remaining_n - i)
        
        backtrack(1, [], k, n)
        return res