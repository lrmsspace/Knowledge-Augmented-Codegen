# Source: https://leetcode.com/problems/find-k-pairs-with-smallest-sums/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integer arrays nums1 and nums2 sorted in non-decreasing order and an integer k.
#
# Define a pair (u, v) which consists of one element from the first array and one element from the second array.
#
# Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest sums.
#
# Example:
# Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
# Output: [[1,2],[1,4],[1,6]]
# Explanation: The first 3 pairs are returned from the sequence: [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
#
# Constraints:
# 1 <= nums1.length, nums2.length <= 105
# 	-109 <= nums1[i], nums2[i] <= 109
# 	nums1 and nums2 both are sorted in non-decreasing order.
# 	1 <= k <= 104
# 	k <= nums1.length * nums2.length
#

class Solution(object):
    def kSmallestPairs(self, nums1, nums2, k):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :type k: int
        :rtype: List[List[int]]
        """
        import heapq
        if not nums1 or not nums2 or k <= 0:
            return []
        
        min_heap = []
        for i in range(min(k, len(nums1))):
            heapq.heappush(min_heap, (nums1[i] + nums2[0], i, 0))
        
        result = []
        while min_heap and len(result) < k:
            current_sum, i, j = heapq.heappop(min_heap)
            result.append([nums1[i], nums2[j]])
            
            if j + 1 < len(nums2):
                heapq.heappush(min_heap, (nums1[i] + nums2[j + 1], i, j + 1))
        
        return result