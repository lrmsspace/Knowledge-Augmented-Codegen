# Source: https://leetcode.com/problems/minimum-cost-to-equalize-array/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and two integers cost1 and cost2. You are allowed to perform either of the following operations any number of times:
#
#
# 	Choose an index i from nums and increase nums[i] by 1 for a cost of cost1.
# 	Choose two different indices i, j, from nums and increase nums[i] and nums[j] by 1 for a cost of cost2.
#
#
# Return the minimum cost required to make all elements in the array equal. 
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [4,1], cost1 = 5, cost2 = 2
#
# Output: 15
#
# Explanation: 
#
# The following operations can be performed to make the values equal:
#
#
# 	Increase nums[1] by 1 for a cost of 5. nums becomes [4,2].
# 	Increase nums[1] by 1 for a cost of 5. nums becomes [4,3].
# 	Increase nums[1] by 1 for a cost of 5. nums becomes [4,4].
#
#
# The total cost is 15.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 106
# 	1 <= cost1 <= 106
# 	1 <= cost2 <= 106
#

class Solution(object):
    def minCostToEqualizeArray(self, nums, cost1, cost2):
        """
        :type nums: List[int]
        :type cost1: int
        :type cost2: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        max_num = max(nums)
        
        # Precompute prefix sums for nums
        prefix_sum = [0] * (max_num + 2)
        count = [0] * (max_num + 2)
        
        for num in nums:
            count[num] += 1
        
        for i in range(1, max_num + 2):
            prefix_sum[i] = prefix_sum[i - 1] + count[i - 1]
        
        def cost_to_equalize(target):
            total_cost = 0
            for num in nums:
                diff = target - num
                if diff > 0:
                    pairs = diff // 2
                    singles = diff % 2
                    total_cost += pairs * min(cost2, 2 * cost1) + singles * cost1
            return total_cost % MOD
        
        left, right = min(nums), max(nums)
        answer = float('inf')
        
        while left <= right:
            mid = (left + right) // 2
            cost_mid = cost_to_equalize(mid)
            cost_mid_plus_1 = cost_to_equalize(mid + 1)
            
            answer = min(answer, cost_mid, cost_mid_plus_1)
            
            if cost_mid < cost_mid_plus_1:
                right = mid - 1
            else:
                left = mid + 1
        
        return answer % MOD