# Source: https://leetcode.com/problems/minimum-sum-of-squared-difference/   |   Difficulty: Medium
#
# Problem Description:
# You are given two positive 0-indexed integer arrays nums1 and nums2, both of length n.
#
# The sum of squared difference of arrays nums1 and nums2 is defined as the sum of (nums1[i] - nums2[i])2 for each 0 <= i < n.
#
# You are also given two positive integers k1 and k2. You can modify any of the elements of nums1 by +1 or -1 at most k1 times. Similarly, you can modify any of the elements of nums2 by +1 or -1 at most k2 times.
#
# Return the minimum sum of squared difference after modifying array nums1 at most k1 times and modifying array nums2 at most k2 times.
#
# Note: You are allowed to modify the array elements to become negative integers.
#
# Example:
# Input: nums1 = [1,2,3,4], nums2 = [2,10,20,19], k1 = 0, k2 = 0
# Output: 579
# Explanation: The elements in nums1 and nums2 cannot be modified because k1 = 0 and k2 = 0. 
# The sum of square difference will be: (1 - 2)2 + (2 - 10)2 + (3 - 20)2 + (4 - 19)2 = 579.
#
# Constraints:
# n == nums1.length == nums2.length
# 	1 <= n <= 105
# 	0 <= nums1[i], nums2[i] <= 105
# 	0 <= k1, k2 <= 109
#

class Solution(object):
    def minSumSquareDiff(self, nums1, nums2, k1, k2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k1: int
        :type k2: int
        :rtype: int
        """
        import heapq

        n = len(nums1)
        diffs = [abs(nums1[i] - nums2[i]) for i in range(n)]
        max_heap = [-diff for diff in diffs]
        heapq.heapify(max_heap)

        total_k = k1 + k2

        while total_k > 0 and max_heap:
            largest_diff = -heapq.heappop(max_heap)
            if largest_diff == 0:
                heapq.heappush(max_heap, -largest_diff)
                break
            largest_diff -= 1
            heapq.heappush(max_heap, -largest_diff)
            total_k -= 1

        result = sum(((-diff) ** 2) for diff in max_heap)
        return result