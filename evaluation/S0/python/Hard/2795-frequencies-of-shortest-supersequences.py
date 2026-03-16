# Source: https://leetcode.com/problems/frequencies-of-shortest-supersequences/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of strings words. Find all shortest common supersequences (SCS) of words that are not permutations of each other.
#
# A shortest common supersequence is a string of minimum length that contains each string in words as a subsequence.
#
# Return a 2D array of integers freqs that represent all the SCSs. Each freqs[i] is an array of size 26, representing the frequency of each letter in the lowercase English alphabet for a single SCS. You may return the frequency arrays in any order.
#
# Example:
# Input: words = ["ab","ba"]
#
# Output: [[1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]
#
# Explanation:
#
# The two SCSs are "aba" and "bab". The output is the letter frequencies for each one.
#
# Constraints:
# 1 <= words.length <= 256
# 	words[i].length == 2
# 	All strings in words will altogether be composed of no more than 16 unique lowercase letters.
# 	All strings in words are unique.
#

class Solution(object):
    def supersequences(self, words):
        """
        :type words: List[str]
        :rtype: List[List[int]]
        """
        from collections import defaultdict
        
        graph = defaultdict(set)
        in_degree = defaultdict(int)
        unique_chars = set()
        
        for w1, w2 in words:
            graph[w1].add(w2)
            in_degree[w2] += 1
            unique_chars.add(w1)
            unique_chars.add(w2)
        
        def backtrack(path, visited):
            if len(path) == len(unique_chars):
                scs = ''.join(path)
                freq = [0] * 26
                for ch in scs:
                    freq[ord(ch) - ord('a')] += 1
                result.add(tuple(freq))
                return
            
            for ch in unique_chars:
                if ch not in visited and in_degree[ch] == 0:
                    visited.add(ch)
                    for neighbor in graph[ch]:
                        in_degree[neighbor] -= 1
                    
                    path.append(ch)
                    backtrack(path, visited)
                    path.pop()
                    
                    for neighbor in graph[ch]:
                        in_degree[neighbor] += 1
                    visited.remove(ch)
        
        result = set()
        backtrack([], set())
        return [list(freq) for freq in result]