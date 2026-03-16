# Source: https://leetcode.com/problems/find-the-maximum-divisibility-score/   |   Difficulty: Easy
#
# Problem Description:
# You are given two integer arrays nums and divisors.
#
# The divisibility score of divisors[i] is the number of indices j such that nums[j] is divisible by divisors[i].
#
# Return the integer divisors[i] with the maximum divisibility score. If multiple integers have the maximum score, return the smallest one.
#
# Example:
# Input: nums = [2,9,15,50], divisors = [5,3,7,2]
#
# Output: 2
#
# Explanation:
#
# The divisibility score of divisors[0] is 2 since nums[2] and nums[3] are divisible by 5.
#
# The divisibility score of divisors[1] is 2 since nums[1] and nums[2] are divisible by 3.
#
# The divisibility score of divisors[2] is 0 since none of the numbers in nums is divisible by 7.
#
# The divisibility score of divisors[3] is 2 since nums[0] and nums[3] are divisible by 2.
#
# As divisors[0], divisors[1], and divisors[3] have the same divisibility score, we return the smaller one which is divisors[3].
#
# Constraints:
# 1 <= nums.length, divisors.length <= 1000
# 	1 <= nums[i], divisors[i] <= 109
#

class Solution(object):
    def maxDivScore(self, nums, divisors):
        """
        :type nums: List[int]
        :type divisors: List[int]
        :rtype: int
        """
        max_score = -1
        result_divisor = None
        
        for divisor in divisors:
            score = sum(1 for num in nums if num % divisor == 0)
            
            if score > max_score or (score == max_score and (result_divisor is None or divisor < result_divisor)):
                max_score = score
                result_divisor = divisor
                
        return result_divisor