# Source: https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-i/   |   Difficulty: Medium
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
# 1 <= k <= s.length <= 105
# 	1 <= a.length, b.length <= 10
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
        a_len = len(a)
        b_len = len(b)
        n = len(s)
        
        a_indices = []
        b_indices = []
        
        # Find all starting indices of substring a
        for i in range(n - a_len + 1):
            if s[i:i + a_len] == a:
                a_indices.append(i)
        
        # Find all starting indices of substring b
        for j in range(n - b_len + 1):
            if s[j:j + b_len] == b:
                b_indices.append(j)
        
        beautiful_indices = set()
        
        # Check each index of a against indices of b
        for i in a_indices:
            for j in b_indices:
                if abs(j - i) <= k:
                    beautiful_indices.add(i)
                    break  # No need to check further b indices for this a index
        
        return sorted(beautiful_indices)