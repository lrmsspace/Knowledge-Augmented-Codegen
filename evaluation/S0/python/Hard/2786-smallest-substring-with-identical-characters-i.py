# Source: https://leetcode.com/problems/smallest-substring-with-identical-characters-i/   |   Difficulty: Hard
#
# Problem Description:
# You are given a binary string s of length n and an integer numOps.
#
# You are allowed to perform the following operation on s at most numOps times:
#
#
# 	Select any index i (where 0 <= i < n) and flip s[i]. If s[i] == '1', change s[i] to '0' and vice versa.
#
#
# You need to minimize the length of the longest substring of s such that all the characters in the substring are identical.
#
# Return the minimum length after the operations.
#
# Example:
# Input: s = "000001", numOps = 1
#
# Output: 2
#
# Explanation: 
#
# By changing s[2] to '1', s becomes "001001". The longest substrings with identical characters are s[0..1] and s[3..4].
#
# Constraints:
# 1 <= n == s.length <= 1000
# 	s consists only of '0' and '1'.
# 	0 <= numOps <= n
#

class Solution(object):
    def minLength(self, s, numOps):
        """
        :type s: str
        :type numOps: int
        :rtype: int
        """
        n = len(s)
        
        def canAchieve(length):
            left = 0
            count0 = 0
            count1 = 0
            
            for right in range(n):
                if s[right] == '0':
                    count0 += 1
                else:
                    count1 += 1
                
                if right - left + 1 > length:
                    if s[left] == '0':
                        count0 -= 1
                    else:
                        count1 -= 1
                    left += 1
                
                if right - left + 1 == length:
                    if min(count0, count1) <= numOps:
                        return True
            
            return False
        
        low, high = 1, n
        result = n
        
        while low <= high:
            mid = (low + high) // 2
            if canAchieve(mid):
                result = mid
                high = mid - 1
            else:
                low = mid + 1
        
        return result