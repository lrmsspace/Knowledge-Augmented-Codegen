# Source: https://leetcode.com/problems/longest-path-with-different-adjacent-characters/   |   Difficulty: Hard
#
# Problem Description:
# You are given a tree (i.e. a connected, undirected graph that has no cycles) rooted at node 0 consisting of n nodes numbered from 0 to n - 1. The tree is represented by a 0-indexed array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.
#
# You are also given a string s of length n, where s[i] is the character assigned to node i.
#
# Return the length of the longest path in the tree such that no pair of adjacent nodes on the path have the same character assigned to them.
#
# Example:
# Input: parent = [-1,0,0,1,1,2], s = "abacbe"
# Output: 3
# Explanation: The longest path where each two adjacent nodes have different characters in the tree is the path: 0 -> 1 -> 3. The length of this path is 3, so 3 is returned.
# It can be proven that there is no longer path that satisfies the conditions.
#
# Constraints:
# n == parent.length == s.length
# 	1 <= n <= 105
# 	0 <= parent[i] <= n - 1 for all i >= 1
# 	parent[0] == -1
# 	parent represents a valid tree.
# 	s consists of only lowercase English letters.
#

class Solution(object):
    def longestPath(self, parent, s):
        """
        :type parent: List[int]
        :type s: str
        :rtype: int
        """
        from collections import defaultdict
        
        tree = defaultdict(list)
        for child, par in enumerate(parent):
            if par != -1:
                tree[par].append(child)
        
        self.max_path = 1
        
        def dfs(node):
            longest, second_longest = 0, 0
            
            for child in tree[node]:
                child_path_length = dfs(child)
                
                if s[child] != s[node]:
                    if child_path_length > longest:
                        second_longest = longest
                        longest = child_path_length
                    elif child_path_length > second_longest:
                        second_longest = child_path_length
            
            self.max_path = max(self.max_path, longest + second_longest + 1)
            return longest + 1
        
        dfs(0)
        return self.max_path