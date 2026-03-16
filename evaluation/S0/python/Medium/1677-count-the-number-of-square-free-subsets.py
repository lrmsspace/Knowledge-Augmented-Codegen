# Source: https://leetcode.com/problems/count-the-number-of-square-free-subsets/   |   Difficulty: Medium
#
# Problem Description:
# You are given a positive integer 0-indexed array nums.
#
# A subset of the array nums is square-free if the product of its elements is a square-free integer.
#
# A square-free integer is an integer that is divisible by no square number other than 1.
#
# Return the number of square-free non-empty subsets of the array nums. Since the answer may be too large, return it modulo 109 + 7.
#
# A non-empty subset of nums is an array that can be obtained by deleting some (possibly none but not all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
#
# Example:
# Input: nums = [3,4,4,5]
# Output: 3
# Explanation: There are 3 square-free subsets in this example:
# - The subset consisting of the 0th element [3]. The product of its elements is 3, which is a square-free integer.
# - The subset consisting of the 3rd element [5]. The product of its elements is 5, which is a square-free integer.
# - The subset consisting of 0th and 3rd elements [3,5]. The product of its elements is 15, which is a square-free integer.
# It can be proven that there are no more than 3 square-free subsets in the given array.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= 30
#

class Solution(object):
    def squareFreeSubsets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
        prime_to_bit = {p: i for i, p in enumerate(primes)}
        
        count = [0] * (1 << len(primes))
        count[0] = 1
        
        for num in nums:
            mask = 0
            temp = num
            is_square_free = True
            
            for p in primes:
                if temp % (p * p) == 0:
                    is_square_free = False
                    break
                if temp % p == 0:
                    mask |= (1 << prime_to_bit[p])
                    temp //= p
            
            if not is_square_free:
                continue
            
            for prev_mask in range((1 << len(primes)) - 1, -1, -1):
                if (prev_mask & mask) == 0:
                    count[prev_mask | mask] = (count[prev_mask | mask] + count[prev_mask]) % MOD
        
        return (sum(count) - 1) % MOD