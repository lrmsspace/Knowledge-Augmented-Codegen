# Source: https://leetcode.com/problems/count-of-interesting-subarrays/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums, an integer modulo, and an integer k.
#
# Your task is to find the count of subarrays that are interesting.
#
# A subarray nums[l..r] is interesting if the following condition holds:
#
#
# 	Let cnt be the number of indices i in the range [l, r] such that nums[i] % modulo == k. Then, cnt % modulo == k.
#
#
# Return an integer denoting the count of interesting subarrays. 
#
# Note: A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [3,2,4], modulo = 2, k = 1
# Output: 3
# Explanation: In this example the interesting subarrays are: 
# The subarray nums[0..0] which is [3]. 
# - There is only one index, i = 0, in the range [0, 0] that satisfies nums[i] % modulo == k. 
# - Hence, cnt = 1 and cnt % modulo == k.  
# The subarray nums[0..1] which is [3,2].
# - There is only one index, i = 0, in the range [0, 1] that satisfies nums[i] % modulo == k.  
# - Hence, cnt = 1 and cnt % modulo == k.
# The subarray nums[0..2] which is [3,2,4]. 
# - There is only one index, i = 0, in the range [0, 2] that satisfies nums[i] % modulo == k. 
# - Hence, cnt = 1 and cnt % modulo == k. 
# It can be shown that there are no other interesting subarrays. So, the answer is 3.
#
# Constraints:
# 1 <= nums.length <= 105 
# 	1 <= nums[i] <= 109
# 	1 <= modulo <= 109
# 	0 <= k < modulo
#

class Solution(object):
    def countInterestingSubarrays(self, nums, modulo, k):
        """
        :type nums: List[int]
        :type modulo: int
        :type k: int
        :rtype: int
        """
        prefix_count = {0: 1}
        current_count = 0
        result = 0

        for num in nums:
            if num % modulo == k:
                current_count += 1
            current_mod = current_count % modulo
            target_mod = (current_mod - k + modulo) % modulo

            if target_mod in prefix_count:
                result += prefix_count[target_mod]

            prefix_count[current_mod] = prefix_count.get(current_mod, 0) + 1

        return result