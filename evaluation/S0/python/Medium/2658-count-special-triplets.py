# Source: https://leetcode.com/problems/count-special-triplets/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
#
# A special triplet is defined as a triplet of indices (i, j, k) such that:
#
#
# 	0 <= i < j < k < n, where n = nums.length
# 	nums[i] == nums[j] * 2
# 	nums[k] == nums[j] * 2
#
#
# Return the total number of special triplets in the array.
#
# Since the answer may be large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [6,3,6]
#
# Output: 1
#
# Explanation:
#
# The only special triplet is (i, j, k) = (0, 1, 2), where:
#
#
# 	nums[0] = 6, nums[1] = 3, nums[2] = 6
# 	nums[0] = nums[1] * 2 = 3 * 2 = 6
# 	nums[2] = nums[1] * 2 = 3 * 2 = 6
#
# Constraints:
# 3 <= n == nums.length <= 105
# 	0 <= nums[i] <= 105
#

class Solution(object):
    def specialTriplets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        count = 0
        n = len(nums)
        
        # Create a frequency map to store occurrences of each number
        freq = {}
        for num in nums:
            freq[num] = freq.get(num, 0) + 1
        
        # Iterate through each number to find valid triplets
        for j in range(n):
            num_j = nums[j]
            num_i = num_j * 2
            num_k = num_j * 2
            
            if num_i in freq and num_k in freq:
                count += (freq[num_i] * freq[num_k])
                count %= MOD
            
            # Decrease the frequency of nums[j] as we move forward
            freq[num_j] -= 1
        
        return count % MOD