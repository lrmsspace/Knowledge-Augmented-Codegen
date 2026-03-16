# Source: https://leetcode.com/problems/find-the-k-beauty-of-a-number/   |   Difficulty: Easy
#
# Problem Description:
# The k-beauty of an integer num is defined as the number of substrings of num when it is read as a string that meet the following conditions:
#
#
# 	It has a length of k.
# 	It is a divisor of num.
#
#
# Given integers num and k, return the k-beauty of num.
#
# Note:
#
#
# 	Leading zeros are allowed.
# 	0 is not a divisor of any value.
#
#
# A substring is a contiguous sequence of characters in a string.
#
# Example:
# Input: num = 240, k = 2
# Output: 2
# Explanation: The following are the substrings of num of length k:
# - "24" from "240": 24 is a divisor of 240.
# - "40" from "240": 40 is a divisor of 240.
# Therefore, the k-beauty is 2.
#
# Constraints:
# 1 <= num <= 109
# 	1 <= k <= num.length (taking num as a string)
#

class Solution(object):
    def divisorSubstrings(self, num, k):
        """
        :type num: int
        :type k: int
        :rtype: int
        """
        num_str = str(num)
        count = 0
        
        for i in range(len(num_str) - k + 1):
            substring = num_str[i:i+k]
            substring_value = int(substring)
            
            if substring_value != 0 and num % substring_value == 0:
                count += 1
                
        return count