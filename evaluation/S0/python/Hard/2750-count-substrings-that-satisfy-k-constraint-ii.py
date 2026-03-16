# Source: https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a binary string s and an integer k.
#
# You are also given a 2D integer array queries, where queries[i] = [li, ri].
#
# A binary string satisfies the k-constraint if either of the following conditions holds:
#
#
# 	The number of 0's in the string is at most k.
# 	The number of 1's in the string is at most k.
#
#
# Return an integer array answer, where answer[i] is the number of substrings of s[li..ri] that satisfy the k-constraint.
#
# Example:
# Input: s = "0001111", k = 2, queries = [[0,6]]
#
# Output: [26]
#
# Explanation:
#
# For the query [0, 6], all substrings of s[0..6] = "0001111" satisfy the k-constraint except for the substrings s[0..5] = "000111" and s[0..6] = "0001111".
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is either '0' or '1'.
# 	1 <= k <= s.length
# 	1 <= queries.length <= 105
# 	queries[i] == [li, ri]
# 	0 <= li <= ri < s.length
# 	All queries are distinct.
#

class Solution(object):
    def countKConstraintSubstrings(self, s, k, queries):
        """
        :type s: str
        :type k: int
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        n = len(s)
        pre0 = [0] * (n + 1)
        pre1 = [0] * (n + 1)
        
        for i in range(n):
            pre0[i + 1] = pre0[i] + (1 if s[i] == '0' else 0)
            pre1[i + 1] = pre1[i] + (1 if s[i] == '1' else 0)
        
        res = []
        
        for l, r in queries:
            total_substrings = (r - l + 1) * (r - l + 2) // 2
            
            count_invalid = 0
            
            count_0 = {}
            count_1 = {}
            
            for i in range(l, r + 1):
                count_0[pre0[i]] = count_0.get(pre0[i], 0) + 1
                count_1[pre1[i]] = count_1.get(pre1[i], 0) + 1
                
                if pre0[i + 1] - pre0[l] > k:
                    count_invalid += count_0.get(pre0[i + 1] - k - 1, 0)
                if pre1[i + 1] - pre1[l] > k:
                    count_invalid += count_1.get(pre1[i + 1] - k - 1, 0)
            
            res.append(total_substrings - count_invalid)
        
        return res