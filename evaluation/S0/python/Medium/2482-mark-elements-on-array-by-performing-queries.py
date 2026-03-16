# Source: https://leetcode.com/problems/mark-elements-on-array-by-performing-queries/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array nums of size n consisting of positive integers.
#
# You are also given a 2D array queries of size m where queries[i] = [indexi, ki].
#
# Initially all elements of the array are unmarked.
#
# You need to apply m queries on the array in order, where on the ith query you do the following:
#
#
# 	Mark the element at index indexi if it is not already marked.
# 	Then mark ki unmarked elements in the array with the smallest values. If multiple such elements exist, mark the ones with the smallest indices. And if less than ki unmarked elements exist, then mark all of them.
#
#
# Return an array answer of size m where answer[i] is the sum of unmarked elements in the array after the ith query.
#
# Example:
# Input: nums = [1,2,2,1,2,3,1], queries = [[1,2],[3,3],[4,2]]
#
# Output: [8,3,0]
#
# Explanation:
#
# We do the following queries on the array:
#
#
# 	Mark the element at index 1, and 2 of the smallest unmarked elements with the smallest indices if they exist, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 2 + 2 + 3 + 1 = 8.
# 	Mark the element at index 3, since it is already marked we skip it. Then we mark 3 of the smallest unmarked elements with the smallest indices, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 3.
# 	Mark the element at index 4, since it is already marked we skip it. Then we mark 2 of the smallest unmarked elements with the smallest indices if they exist, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 0.
#
# Constraints:
# n == nums.length
# 	m == queries.length
# 	1 <= m <= n <= 105
# 	1 <= nums[i] <= 105
# 	queries[i].length == 2
# 	0 <= indexi, ki <= n - 1
#

class Solution(object):
    def unmarkedSumArray(self, nums, queries):
        """
        :type nums: List[int]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        n = len(nums)
        marked = [False] * n
        result = []
        total_sum = sum(nums)

        # Create a list of (value, index) pairs and sort it
        value_index_pairs = sorted((val, idx) for idx, val in enumerate(nums))
        current_mark_index = 0

        for index, k in queries:
            # Mark the specified index if not already marked
            if not marked[index]:
                marked[index] = True
                total_sum -= nums[index]

            # Mark k smallest unmarked elements
            marked_count = 0
            while marked_count < k and current_mark_index < n:
                value, idx = value_index_pairs[current_mark_index]
                if not marked[idx]:
                    marked[idx] = True
                    total_sum -= value
                    marked_count += 1
                current_mark_index += 1

            result.append(total_sum)

        return result