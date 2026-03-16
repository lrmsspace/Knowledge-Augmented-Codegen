# Source: https://leetcode.com/problems/longest-increasing-subsequence-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and an integer k.
#
# Find the longest subsequence of nums that meets the following requirements:
#
#
# 	The subsequence is strictly increasing and
# 	The difference between adjacent elements in the subsequence is at most k.
#
#
# Return the length of the longest subsequence that meets the requirements.
#
# A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
#
# Example:
# Input: nums = [4,2,1,4,3,4,5,8,15], k = 3
# Output: 5
# Explanation:
# The longest subsequence that meets the requirements is [1,3,4,5,8].
# The subsequence has a length of 5, so we return 5.
# Note that the subsequence [1,3,4,5,8,15] does not meet the requirements because 15 - 8 = 7 is larger than 3.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i], k <= 105
#

class Solution(object):
    def lengthOfLIS(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        class SegmentTree:
            def __init__(self, size):
                self.size = size
                self.tree = [0] * (4 * size)

            def update(self, index, value, node, node_left, node_right):
                if node_left == node_right:
                    self.tree[node] = max(self.tree[node], value)
                    return
                mid = (node_left + node_right) // 2
                if index <= mid:
                    self.update(index, value, 2 * node + 1, node_left, mid)
                else:
                    self.update(index, value, 2 * node + 2, mid + 1, node_right)
                self.tree[node] = max(self.tree[2 * node + 1], self.tree[2 * node + 2])

            def query(self, left, right, node, node_left, node_right):
                if right < node_left or left > node_right:
                    return 0
                if left <= node_left and node_right <= right:
                    return self.tree[node]
                mid = (node_left + node_right) // 2
                return max(
                    self.query(left, right, 2 * node + 1, node_left, mid),
                    self.query(left, right, 2 * node + 2, mid + 1, node_right)
                )

        max_num = max(nums)
        seg_tree = SegmentTree(max_num)
        max_length = 0

        for num in nums:
            left_bound = max(1, num - k)
            best_length = seg_tree.query(left_bound, num - 1, 0, 1, max_num)
            current_length = best_length + 1
            seg_tree.update(num, current_length, 0, 1, max_num)
            max_length = max(max_length, current_length)

        return max_length   