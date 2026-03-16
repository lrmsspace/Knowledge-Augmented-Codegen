# Source: https://leetcode.com/problems/combination-sum-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.
#
# Each number in candidates may only be used once in the combination.
#
# Note: The solution set must not contain duplicate combinations.
#
# Example:
# Input: candidates = [10,1,2,7,6,1,5], target = 8
# Output: 
# [
# [1,1,6],
# [1,2,5],
# [1,7],
# [2,6]
# ]
#
# Constraints:
# 1 <= candidates.length <= 100
# 	1 <= candidates[i] <= 50
# 	1 <= target <= 30
#

class Solution(object):
    def combinationSum2(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        candidates.sort()
        res = []
        
        def backtrack(start, path, target):
            if target == 0:
                res.append(path)
                return
            if target < 0:
                return
            
            for i in range(start, len(candidates)):
                if i > start and candidates[i] == candidates[i - 1]:
                    continue
                backtrack(i + 1, path + [candidates[i]], target - candidates[i])
        
        backtrack(0, [], target)
        return res