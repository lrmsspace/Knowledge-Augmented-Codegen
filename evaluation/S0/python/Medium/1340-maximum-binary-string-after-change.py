# Source: https://leetcode.com/problems/maximum-binary-string-after-change/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary string binary consisting of only 0's or 1's. You can apply each of the following operations any number of times:
#
#
#  Operation 1: If the number contains the substring "00", you can replace it with "10".
#
#  
#   For example, "00010" -> "10010"
#  
#  
#  Operation 2: If the number contains the substring "10", you can replace it with "01".
#  
#   For example, "00010" -> "00001"
#  
#  
#
#
# Return the maximum binary string you can obtain after any number of operations. Binary string x is greater than binary string y if x's decimal representation is greater than y's decimal representation.
#
# Example:
# Input: binary = "000110"
# Output: "111011"
# Explanation: A valid transformation sequence can be:
# "000110" -> "000101" 
# "000101" -> "100101" 
# "100101" -> "110101" 
# "110101" -> "110011" 
# "110011" -> "111011"
#
# Constraints:
# 1 <= binary.length <= 105
#  binary consist of '0' and '1'.
#

class Solution(object):
    def maximumBinaryString(self, binary):
        """
        :type binary: str
        :rtype: str
        """
        n = len(binary)
        count0 = binary.count('0')
        
        if count0 == 0:
            return binary
        
        first0 = binary.index('0')
        result = ['1'] * n
        
        # Place '0's in the appropriate positions
        for i in range(count0 - 1):
            result[first0 + i] = '0'
        
        # The last '0' goes one position to the right
        result[first0 + count0 - 1] = '0'
        
        return ''.join(result)