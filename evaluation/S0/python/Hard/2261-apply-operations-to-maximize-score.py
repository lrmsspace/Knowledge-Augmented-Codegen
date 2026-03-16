# Source: https://leetcode.com/problems/apply-operations-to-maximize-score/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums of n positive integers and an integer k.
#
# Initially, you start with a score of 1. You have to maximize your score by applying the following operation at most k times:
#
#
# 	Choose any non-empty subarray nums[l, ..., r] that you haven't chosen previously.
# 	Choose an element x of nums[l, ..., r] with the highest prime score. If multiple such elements exist, choose the one with the smallest index.
# 	Multiply your score by x.
#
#
# Here, nums[l, ..., r] denotes the subarray of nums starting at index l and ending at the index r, both ends being inclusive.
#
# The prime score of an integer x is equal to the number of distinct prime factors of x. For example, the prime score of 300 is 3 since 300 = 2 * 2 * 3 * 5 * 5.
#
# Return the maximum possible score after applying at most k operations.
#
# Since the answer may be large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [8,3,9,3,8], k = 2
# Output: 81
# Explanation: To get a score of 81, we can apply the following operations:
# - Choose subarray nums[2, ..., 2]. nums[2] is the only element in this subarray. Hence, we multiply the score by nums[2]. The score becomes 1 * 9 = 9.
# - Choose subarray nums[2, ..., 3]. Both nums[2] and nums[3] have a prime score of 1, but nums[2] has the smaller index. Hence, we multiply the score by nums[2]. The score becomes 9 * 9 = 81.
# It can be proven that 81 is the highest score one can obtain.
#
# Constraints:
# 1 <= nums.length == n <= 105
# 	1 <= nums[i] <= 105
# 	1 <= k <= min(n * (n + 1) / 2, 109)
#

class Solution(object):
    def maximumScore(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        max_num = max(nums)
        
        # Step 1: Sieve to find the number of distinct prime factors for each number
        prime_count = [0] * (max_num + 1)
        for i in range(2, max_num + 1):
            if prime_count[i] == 0:  # i is prime
                for multiple in range(i, max_num + 1, i):
                    prime_count[multiple] += 1
        
        # Step 2: Create a list of (num, prime_score, index) and sort it
        indexed_nums = [(num, prime_count[num], idx) for idx, num in enumerate(nums)]
        indexed_nums.sort(key=lambda x: (-x[1], x[2]))  # Sort by prime score desc, index asc
        
        # Step 3: Use a stack to find the next greater element on both sides
        n = len(nums)
        left = [-1] * n
        right = [n] * n
        
        stack = []
        for i in range(n):
            while stack and nums[stack[-1]] < nums[i]:
                right[stack.pop()] = i
            stack.append(i)
        
        stack.clear()
        for i in range(n - 1, -1, -1):
            while stack and nums[stack[-1]] <= nums[i]:
                left[stack.pop()] = i
            stack.append(i)
        
        # Step 4: Calculate the maximum score
        score = 1
        for num, prime_score, idx in indexed_nums:
            if k <= 0:
                break
            
            total_subarrays = (idx - left[idx]) * (right[idx] - idx)
            use_count = min(k, total_subarrays)
            
            score = (score * pow(num, use_count, MOD)) % MOD
            k -= use_count
        
        return score