# Source: https://leetcode.com/problems/minimum-absolute-difference-queries/   |   Difficulty: Medium
#
# Problem Description:
# The minimum absolute difference of an array a is defined as the minimum value of |a[i] - a[j]|, where 0 <= i < j < a.length and a[i] != a[j]. If all elements of a are the same, the minimum absolute difference is -1.
#
#
# 	For example, the minimum absolute difference of the array [5,2,3,7,2] is |2 - 3| = 1. Note that it is not 0 because a[i] and a[j] must be different.
#
#
# You are given an integer array nums and the array queries where queries[i] = [li, ri]. For each query i, compute the minimum absolute difference of the subarray nums[li...ri] containing the elements of nums between the 0-based indices li and ri (inclusive).
#
# Return an array ans where ans[i] is the answer to the ith query.
#
# A subarray is a contiguous sequence of elements in an array.
#
# The value of |x| is defined as:
#
#
# 	x if x >= 0.
# 	-x if x < 0.
#
# Example:
# Input: nums = [1,3,4,8], queries = [[0,1],[1,2],[2,3],[0,3]]
# Output: [2,1,4,1]
# Explanation: The queries are processed as follows:
# - queries[0] = [0,1]: The subarray is [1,3] and the minimum absolute difference is |1-3| = 2.
# - queries[1] = [1,2]: The subarray is [3,4] and the minimum absolute difference is |3-4| = 1.
# - queries[2] = [2,3]: The subarray is [4,8] and the minimum absolute difference is |4-8| = 4.
# - queries[3] = [0,3]: The subarray is [1,3,4,8] and the minimum absolute difference is |3-4| = 1.
#
# Constraints:
# 2 <= nums.length <= 105
# 	1 <= nums[i] <= 100
# 	1 <= queries.length <= 2 * 104
# 	0 <= li < ri < nums.length
#

class Solution(object):
    def minDifference(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        n = len(nums)
        prefix = [[0] * 101 for _ in range(n + 1)]
        
        for i in range(n):
            for j in range(1, 101):
                prefix[i + 1][j] = prefix[i][j]
            prefix[i + 1][nums[i]] += 1
        
        result = []
        
        for l, r in queries:
            prev = -1
            min_diff = float('inf')
            for num in range(1, 101):
                count = prefix[r + 1][num] - prefix[l][num]
                if count > 0:
                    if prev != -1:
                        min_diff = min(min_diff, num - prev)
                    prev = num
            if min_diff == float('inf'):
                result.append(-1)
            else:
                result.append(min_diff)
        
        return result