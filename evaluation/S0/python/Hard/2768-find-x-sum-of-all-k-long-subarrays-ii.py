# Source: https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums of n integers and two integers k and x.
#
# The x-sum of an array is calculated by the following procedure:
#
#
# 	Count the occurrences of all elements in the array.
# 	Keep only the occurrences of the top x most frequent elements. If two elements have the same number of occurrences, the element with the bigger value is considered more frequent.
# 	Calculate the sum of the resulting array.
#
#
# Note that if an array has less than x distinct elements, its x-sum is the sum of the array.
#
# Return an integer array answer of length n - k + 1 where answer[i] is the x-sum of the subarray nums[i..i + k - 1].
#
# Example:
# Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
#
# Output: [6,10,12]
#
# Explanation:
#
#
# 	For subarray [1, 1, 2, 2, 3, 4], only elements 1 and 2 will be kept in the resulting array. Hence, answer[0] = 1 + 1 + 2 + 2.
# 	For subarray [1, 2, 2, 3, 4, 2], only elements 2 and 4 will be kept in the resulting array. Hence, answer[1] = 2 + 2 + 2 + 4. Note that 4 is kept in the array since it is bigger than 3 and 1 which occur the same number of times.
# 	For subarray [2, 2, 3, 4, 2, 3], only elements 2 and 3 are kept in the resulting array. Hence, answer[2] = 2 + 2 + 2 + 3 + 3.
#
# Constraints:
# nums.length == n
# 	1 <= n <= 105
# 	1 <= nums[i] <= 109
# 	1 <= x <= k <= nums.length
#

class Solution(object):
    def findXSum(self, nums, k, x):
        """
        :type nums: List[int]
        :type k: int
        :type x: int
        :rtype: List[int]
        """
        from collections import defaultdict
        import heapq

        n = len(nums)
        if k > n:
            return []

        freq = defaultdict(int)
        for i in range(k):
            freq[nums[i]] += 1

        def calculate_x_sum(freq_map):
            max_heap = [(-count, num) for num, count in freq_map.items()]
            heapq.heapify(max_heap)

            x_sum = 0
            for _ in range(min(x, len(max_heap))):
                count, num = heapq.heappop(max_heap)
                x_sum += -count * num
            return x_sum

        result = []
        result.append(calculate_x_sum(freq))

        for i in range(k, n):
            freq[nums[i]] += 1
            freq[nums[i - k]] -= 1
            if freq[nums[i - k]] == 0:
                del freq[nums[i - k]]

            result.append(calculate_x_sum(freq))

        return result