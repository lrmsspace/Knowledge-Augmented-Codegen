# Source: https://leetcode.com/problems/similar-string-groups/   |   Difficulty: Hard
#
# Problem Description:
# Two strings, X and Y, are considered similar if either they are identical or we can make them equivalent by swapping at most two letters (in distinct positions) within the string X.
#
# For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar, but "star" is not similar to "tars", "rats", or "arts".
#
# Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.  Notice that "tars" and "arts" are in the same group even though they are not similar.  Formally, each group is such that a word is in the group if and only if it is similar to at least one other word in the group.
#
# We are given a list strs of strings where every string in strs is an anagram of every other string in strs. How many groups are there?
#
# Example:
# Input: strs = ["tars","rats","arts","star"]
# Output: 2
#
# Constraints:
# 1 <= strs.length <= 300
# 	1 <= strs[i].length <= 300
# 	strs[i] consists of lowercase letters only.
# 	All words in strs have the same length and are anagrams of each other.
#

class Solution(object):
    def numSimilarGroups(self, strs):
        """
        :type strs: List[str]
        :rtype: int
        """
        parent = {}
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                parent[rootY] = rootX
        
        def is_similar(s1, s2):
            diff = [i for i in range(len(s1)) if s1[i] != s2[i]]
            return len(diff) == 0 or (len(diff) == 2 and s1[diff[0]] == s2[diff[1]] and s1[diff[1]] == s2[diff[0]])
        
        for s in strs:
            parent[s] = s
        
        for i in range(len(strs)):
            for j in range(i + 1, len(strs)):
                if is_similar(strs[i], strs[j]):
                    union(strs[i], strs[j])
        
        groups = set()
        for s in strs:
            groups.add(find(s))
        
        return len(groups)