# Source: https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed string s, a string a, a string b, and an integer k.
#
# An index i is beautiful if:
#
#
# 	0 <= i <= s.length - a.length
# 	s[i..(i + a.length - 1)] == a
# 	There exists an index j such that:
# 	
# 		0 <= j <= s.length - b.length
# 		s[j..(j + b.length - 1)] == b
# 		|j - i| <= k
# 	
# 	
#
#
# Return the array that contains beautiful indices in sorted order from smallest to largest.
#
# Example:
# Input: s = "isawsquirrelnearmysquirrelhouseohmy", a = "my", b = "squirrel", k = 15
# Output: [16,33]
# Explanation: There are 2 beautiful indices: [16,33].
# - The index 16 is beautiful as s[16..17] == "my" and there exists an index 4 with s[4..11] == "squirrel" and |16 - 4| <= 15.
# - The index 33 is beautiful as s[33..34] == "my" and there exists an index 18 with s[18..25] == "squirrel" and |33 - 18| <= 15.
# Thus we return [16,33] as the result.
#
# Constraints:
# 1 <= k <= s.length <= 5 * 105
# 	1 <= a.length, b.length <= 5 * 105
# 	s, a, and b contain only lowercase English letters.
#

class Solution(object):
    def beautifulIndices(self, s, a, b, k):
        """
        :type s: str
        :type a: str
        :type b: str
        :type k: int
        :rtype: List[int]
        """
        n = len(s)
        la, lb = len(a), len(b)
        pre_b = [0] * (n + 1)
        
        for i in range(n - lb + 1):
            if s[i:i+lb] == b:
                pre_b[i + 1] = 1
        
        for i in range(1, n + 1):
            pre_b[i] += pre_b[i - 1]
        
        result = []
        
        for i in range(n - la + 1):
            if s[i:i+la] == a:
                left = max(0, i - k)
                right = min(n - lb, i + k)
                if pre_b[right + 1] - pre_b[left] > 0:
                    result.append(i)
        
        return result