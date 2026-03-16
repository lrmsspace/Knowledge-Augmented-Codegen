# Source: https://leetcode.com/problems/count-number-of-distinct-integers-after-reverse-operations/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums consisting of positive integers.
#
# You have to take each integer in the array, reverse its digits, and add it to the end of the array. You should apply this operation to the original integers in nums.
#
# Return the number of distinct integers in the final array.
#
# Example:
# Input: nums = [1,13,10,12,31]
# Output: 6
# Explanation: After including the reverse of each number, the resulting array is [1,13,10,12,31,1,31,1,21,13].
# The reversed integers that were added to the end of the array are underlined. Note that for the integer 10, after reversing it, it becomes 01 which is just 1.
# The number of distinct integers in this array is 6 (The numbers 1, 10, 12, 13, 21, and 31).
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 106
#

class Solution(object):
    def countDistinctIntegers(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        distinct_numbers = set(nums)  # 使用集合存储原始整数，自动去重
        
        for num in nums:
            reversed_num = int(str(num)[::-1])  # 反转整数的数字并转换回整数
            distinct_numbers.add(reversed_num)  # 将反转后的整数加入集合
        
        return len(distinct_numbers)  # 返回集合中不同整数的数量