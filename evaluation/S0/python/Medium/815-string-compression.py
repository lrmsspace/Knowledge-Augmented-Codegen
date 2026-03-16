# Source: https://leetcode.com/problems/string-compression/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of characters chars, compress it using the following algorithm:
#
# Begin with an empty string s. For each group of consecutive repeating characters in chars:
#
#
# 	If the group's length is 1, append the character to s.
# 	Otherwise, append the character followed by the group's length.
#
#
# The compressed string s should not be returned separately, but instead, be stored in the input character array chars. Note that group lengths that are 10 or longer will be split into multiple characters in chars.
#
# After you are done modifying the input array, return the new length of the array.
#
# You must write an algorithm that uses only constant extra space.
#
# Note: The characters in the array beyond the returned length do not matter and should be ignored.
#
# Example:
# Input: chars = ["a","a","b","b","c","c","c"]
# Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
# Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".
#
# Constraints:
# 1 <= chars.length <= 2000
# 	chars[i] is a lowercase English letter, uppercase English letter, digit, or symbol.
#

class Solution(object):
    def compress(self, chars):
        """
        :type chars: List[str]
        :rtype: int
        """
        write_index = 0
        read_index = 0
        n = len(chars)

        while read_index < n:
            current_char = chars[read_index]
            count = 0

            # Count occurrences of the current character
            while read_index < n and chars[read_index] == current_char:
                read_index += 1
                count += 1

            # Write the character
            chars[write_index] = current_char
            write_index += 1

            # Write the count if greater than 1
            if count > 1:
                for digit in str(count):
                    chars[write_index] = digit
                    write_index += 1

        return write_index