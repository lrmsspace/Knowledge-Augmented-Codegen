# Source: https://leetcode.com/problems/sliding-window-maximum/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
#
# Return the max sliding window.
#
# Example:
# Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
# Output: [3,3,5,5,6,7]
# Explanation: 
# Window position                Max
# ---------------               -----
# [1  3  -1] -3  5  3  6  7       3
#  1 [3  -1  -3] 5  3  6  7       3
#  1  3 [-1  -3  5] 3  6  7       5
#  1  3  -1 [-3  5  3] 6  7       5
#  1  3  -1  -3 [5  3  6] 7       6
#  1  3  -1  -3  5 [3  6  7]      7
#
# Constraints:
# 1 <= nums.length <= 105
# 	-104 <= nums[i] <= 104
# 	1 <= k <= nums.length
#

class Solution(object):
    def maxSlidingWindow(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        from collections import deque

        if not nums or k == 0:
            return []

        result = []
        dq = deque()

        for i in range(len(nums)):
            # Remove elements not in the current window
            if dq and dq[0] < i - k + 1:
                dq.popleft()

            # Remove elements smaller than the current element from the deque
            while dq and nums[dq[-1]] < nums[i]:
                dq.pop()

            dq.append(i)

            # Append the maximum for the current window to the result
            if i >= k - 1:
                result.append(nums[dq[0]])

        return result