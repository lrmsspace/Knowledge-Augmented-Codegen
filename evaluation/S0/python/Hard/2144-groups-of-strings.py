# Source: https://leetcode.com/problems/groups-of-strings/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed array of strings words. Each string consists of lowercase English letters only. No letter occurs more than once in any string of words.
#
# Two strings s1 and s2 are said to be connected if the set of letters of s2 can be obtained from the set of letters of s1 by any one of the following operations:
#
#
# 	Adding exactly one letter to the set of the letters of s1.
# 	Deleting exactly one letter from the set of the letters of s1.
# 	Replacing exactly one letter from the set of the letters of s1 with any letter, including itself.
#
#
# The array words can be divided into one or more non-intersecting groups. A string belongs to a group if any one of the following is true:
#
#
# 	It is connected to at least one other string of the group.
# 	It is the only string present in the group.
#
#
# Note that the strings in words should be grouped in such a manner that a string belonging to a group cannot be connected to a string present in any other group. It can be proved that such an arrangement is always unique.
#
# Return an array ans of size 2 where:
#
#
# 	ans[0] is the maximum number of groups words can be divided into, and
# 	ans[1] is the size of the largest group.
#
# Example:
# Input: words = ["a","b","ab","cde"]
# Output: [2,3]
# Explanation:
# - words[0] can be used to obtain words[1] (by replacing 'a' with 'b'), and words[2] (by adding 'b'). So words[0] is connected to words[1] and words[2].
# - words[1] can be used to obtain words[0] (by replacing 'b' with 'a'), and words[2] (by adding 'a'). So words[1] is connected to words[0] and words[2].
# - words[2] can be used to obtain words[0] (by deleting 'b'), and words[1] (by deleting 'a'). So words[2] is connected to words[0] and words[1].
# - words[3] is not connected to any string in words.
# Thus, words can be divided into 2 groups ["a","b","ab"] and ["cde"]. The size of the largest group is 3.
#
# Constraints:
# 1 <= words.length <= 2 * 104
# 	1 <= words[i].length <= 26
# 	words[i] consists of lowercase English letters only.
# 	No letter occurs more than once in words[i].
#

class Solution(object):
    def groupStrings(self, words):
        """
        :type words: List[str]
        :rtype: List[int]
        """
        parent = {}
        size = {}

        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            rootX = find(x)
            rootY = find(y)
            if rootX != rootY:
                parent[rootY] = rootX
                size[rootX] += size[rootY]

        for word in words:
            bitmask = 0
            for char in word:
                bitmask |= 1 << (ord(char) - ord('a'))
            parent[bitmask] = bitmask
            size[bitmask] = 1

        for bitmask in parent.keys():
            for i in range(26):
                # Deletion
                neighbor = bitmask & ~(1 << i)
                if neighbor in parent:
                    union(bitmask, neighbor)
                # Addition
                neighbor = bitmask | (1 << i)
                if neighbor in parent:
                    union(bitmask, neighbor)
                # Replacement
                for j in range(26):
                    if i != j:
                        neighbor = (bitmask & ~(1 << i)) | (1 << j)
                        if neighbor in parent:
                            union(bitmask, neighbor)

        group_count = len(set(find(x) for x in parent.keys()))
        largest_group_size = max(size.values()) if size else 0

        return [group_count, largest_group_size]