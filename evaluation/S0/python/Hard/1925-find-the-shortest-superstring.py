# Source: https://leetcode.com/problems/find-the-shortest-superstring/   |   Difficulty: Hard
#
# Problem Description:
# Given an array of strings words, return the smallest string that contains each string in words as a substring. If there are multiple valid strings of the smallest length, return any of them.
#
# You may assume that no string in words is a substring of another string in words.
#
# Example:
# Input: words = ["alex","loves","leetcode"]
# Output: "alexlovesleetcode"
# Explanation: All permutations of "alex","loves","leetcode" would also be accepted.
#
# Constraints:
# 1 <= words.length <= 12
# 	1 <= words[i].length <= 20
# 	words[i] consists of lowercase English letters.
# 	All the strings of words are unique.
#

class Solution(object):
    def shortestSuperstring(self, words):
        """
        :type words: List[str]
        :rtype: str
        """
        n = len(words)
        overlap = [[0] * n for _ in range(n)]
        
        for i in range(n):
            for j in range(n):
                if i != j:
                    max_ov = min(len(words[i]), len(words[j]))
                    for k in range(max_ov, 0, -1):
                        if words[i][-k:] == words[j][:k]:
                            overlap[i][j] = k
                            break
        
        dp = [[float('inf')] * n for _ in range(1 << n)]
        parent = [[-1] * n for _ in range(1 << n)]
        
        for i in range(n):
            dp[1 << i][i] = len(words[i])
        
        for mask in range(1 << n):
            for u in range(n):
                if mask & (1 << u):
                    for v in range(n):
                        if mask & (1 << v) == 0:
                            new_mask = mask | (1 << v)
                            cost = dp[mask][u] + len(words[v]) - overlap[u][v]
                            if cost < dp[new_mask][v]:
                                dp[new_mask][v] = cost
                                parent[new_mask][v] = u
        
        min_len = float('inf')
        last = -1
        final_mask = (1 << n) - 1
        
        for i in range(n):
            if dp[final_mask][i] < min_len:
                min_len = dp[final_mask][i]
                last = i
        
        path = []
        mask = final_mask
        while last != -1:
            path.append(last)
            temp = parent[mask][last]
            mask ^= (1 << last)
            last = temp
        
        path.reverse()
        
        result = words[path[0]]
        for i in range(1, len(path)):
            ov = overlap[path[i-1]][path[i]]
            result += words[path[i]][ov:]
        
        return result