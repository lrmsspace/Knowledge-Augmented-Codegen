# Source: https://leetcode.com/problems/find-valid-pair-of-adjacent-digits-in-string/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s consisting only of digits. A valid pair is defined as two adjacent digits in s such that:
#
#
# 	The first digit is not equal to the second.
# 	Each digit in the pair appears in s exactly as many times as its numeric value.
#
#
# Return the first valid pair found in the string s when traversing from left to right. If no valid pair exists, return an empty string.
#
# Example:
# Input: s = "2523533"
#
# Output: "23"
#
# Explanation:
#
# Digit '2' appears 2 times and digit '3' appears 3 times. Each digit in the pair "23" appears in s exactly as many times as its numeric value. Hence, the output is "23".
#
# Constraints:
# 2 <= s.length <= 100
# 	s only consists of digits from '1' to '9'.
#

class Solution(object):
    def findValidPair(self, s):
        """
        :type s: str
        :rtype: str
        """
        count = {}
        
        # Count the occurrences of each digit in the string
        for char in s:
            if char in count:
                count[char] += 1
            else:
                count[char] = 1
        
        # Traverse the string to find the first valid pair of adjacent digits
        for i in range(len(s) - 1):
            first_digit = s[i]
            second_digit = s[i + 1]
            
            # Check if the digits are different and their counts match their numeric values
            if first_digit != second_digit:
                if count[first_digit] == int(first_digit) and count[second_digit] == int(second_digit):
                    return first_digit + second_digit
        
        # If no valid pair is found, return an empty string
        return ""