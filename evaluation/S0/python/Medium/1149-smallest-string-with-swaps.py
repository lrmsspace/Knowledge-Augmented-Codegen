# Source: https://leetcode.com/problems/smallest-string-with-swaps/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s, and an array of pairs of indices in the string pairs where pairs[i] = [a, b] indicates 2 indices(0-indexed) of the string.
#
# You can swap the characters at any pair of indices in the given pairs any number of times.
#
# Return the lexicographically smallest string that s can be changed to after using the swaps.
#
# Example:
# Input: s = "dcab", pairs = [[0,3],[1,2]]
# Output: "bacd"
# Explaination: 
# Swap s[0] and s[3], s = "bcad"
# Swap s[1] and s[2], s = "bacd"
#
# Constraints:
# 1 <= s.length <= 10^5
# 	0 <= pairs.length <= 10^5
# 	0 <= pairs[i][0], pairs[i][1] < s.length
# 	s only contains lower case English letters.
#

class Solution(object):
    def smallestStringWithSwaps(self, s, pairs):
        """
        :type s: str
        :type pairs: List[List[int]]
        :rtype: str
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        for a, b in pairs:
            graph[a].append(b)
            graph[b].append(a)

        visited = [False] * len(s)
        res = list(s)

        for i in range(len(s)):
            if not visited[i]:
                indices = []
                chars = []
                queue = deque([i])
                visited[i] = True

                while queue:
                    node = queue.popleft()
                    indices.append(node)
                    chars.append(s[node])

                    for neighbor in graph[node]:
                        if not visited[neighbor]:
                            visited[neighbor] = True
                            queue.append(neighbor)

                indices.sort()
                chars.sort()

                for idx, char in zip(indices, chars):
                    res[idx] = char

        return ''.join(res)