# Source: https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers arr and an integer k. Find the least number of unique integers after removing exactly k elements.
#
# Example:
# Input: arr = [5,5,4], k = 1
# Output: 1
# Explanation: Remove the single 4, only 5 is left.
#
# Constraints:
# 1 <= arr.length <= 10^5
# 	1 <= arr[i] <= 10^9
# 	0 <= k <= arr.length
#

class Solution(object):

    def findLeastNumOfUniqueInts(self, arr, k):

        """

        :type arr: List[int]

        :type k: int

        :rtype: int

        """
        from collections import Counter
        import heapq

        freq = Counter(arr)
        min_heap = list(freq.values())
        heapq.heapify(min_heap)

        while k > 0 and min_heap:
            smallest_freq = heapq.heappop(min_heap)
            if k >= smallest_freq:
                k -= smallest_freq
            else:
                heapq.heappush(min_heap, smallest_freq)
                break

        return len(min_heap)