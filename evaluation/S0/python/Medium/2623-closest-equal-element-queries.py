# Source: https://leetcode.com/problems/closest-equal-element-queries/   |   Difficulty: Medium
#
# Problem Description:
# You are given a circular array nums and an array queries.
#
# For each query i, you have to find the following:
#
#
# 	The minimum distance between the element at index queries[i] and any other index j in the circular array, where nums[j] == nums[queries[i]]. If no such index exists, the answer for that query should be -1.
#
#
# Return an array answer of the same size as queries, where answer[i] represents the result for query i.
#
# Example:
# Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]
#
# Output: [2,-1,3]
#
# Explanation:
#
#
# 	Query 0: The element at queries[0] = 0 is nums[0] = 1. The nearest index with the same value is 2, and the distance between them is 2.
# 	Query 1: The element at queries[1] = 3 is nums[3] = 4. No other index contains 4, so the result is -1.
# 	Query 2: The element at queries[2] = 5 is nums[5] = 3. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).
#
# Constraints:
# 1 <= queries.length <= nums.length <= 105
# 	1 <= nums[i] <= 106
# 	0 <= queries[i] < nums.length
#

class Solution(object):
    def solveQueries(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[int]
        :rtype: List[int]
        """
        from collections import defaultdict
        import bisect

        index_map = defaultdict(list)
        n = len(nums)

        # Build a map from number to its indices
        for i, num in enumerate(nums):
            index_map[num].append(i)

        result = []

        for q in queries:
            target = nums[q]
            indices = index_map[target]

            if len(indices) == 1:
                result.append(-1)
                continue

            pos = bisect.bisect_left(indices, q)

            # Find the closest index in the circular manner
            left_index = indices[pos - 1] if pos > 0 else indices[-1]
            right_index = indices[pos] if pos < len(indices) else indices[0]

            left_distance = (q - left_index) % n
            right_distance = (right_index - q) % n

            result.append(min(left_distance, right_distance))

        return result