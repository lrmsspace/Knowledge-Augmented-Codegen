# Source: https://leetcode.com/problems/minimum-swaps-to-sort-by-digit-sum/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums of distinct positive integers. You need to sort the array in increasing order based on the sum of the digits of each number. If two numbers have the same digit sum, the smaller number appears first in the sorted order.
#
# Return the minimum number of swaps required to rearrange nums into this sorted order.
#
# A swap is defined as exchanging the values at two distinct positions in the array.
#
# Example:
# Input: nums = [37,100]
#
# Output: 1
#
# Explanation:
#
#
# 	Compute the digit sum for each integer: [3 + 7 = 10, 1 + 0 + 0 = 1] → [10, 1]
# 	Sort the integers based on digit sum: [100, 37]. Swap 37 with 100 to obtain the sorted order.
# 	Thus, the minimum number of swaps required to rearrange nums is 1.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	nums consists of distinct positive integers.
#

class Solution(object):
    def minSwaps(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def digit_sum(n):
            return sum(int(d) for d in str(n))
        
        n = len(nums)
        arrpos = [(digit_sum(nums[i]), nums[i], i) for i in range(n)]
        arrpos.sort()
        
        visited = [False] * n
        ans = 0
        
        for i in range(n):
            if visited[i] or arrpos[i][2] == i:
                continue
            
            cycle_size = 0
            j = i
            
            while not visited[j]:
                visited[j] = True
                j = arrpos[j][2]
                cycle_size += 1
            
            if cycle_size > 0:
                ans += (cycle_size - 1)
        
        return ans