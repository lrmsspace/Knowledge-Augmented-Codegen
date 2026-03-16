# Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a palindromic string s and an integer k.
#
# Return the k-th lexicographically smallest palindromic permutation of s. If there are fewer than k distinct palindromic permutations, return an empty string.
#
# Note: Different rearrangements that yield the same palindromic string are considered identical and are counted once.
#
# Example:
# Input: s = "abba", k = 2
#
# Output: "baab"
#
# Explanation:
#
#
# 	The two distinct palindromic rearrangements of "abba" are "abba" and "baab".
# 	Lexicographically, "abba" comes before "baab". Since k = 2, the output is "baab".
#
# Constraints:
# 1 <= s.length <= 104
# 	s consists of lowercase English letters.
# 	s is guaranteed to be palindromic.
# 	1 <= k <= 106
#

class Solution(object):
    def smallestPalindrome(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        from math import factorial
        from collections import Counter

        def count_permutations(half_count):
            total = sum(half_count.values())
            denom = 1
            for count in half_count.values():
                denom *= factorial(count)
            return factorial(total) // denom

        n = len(s)
        half_count = Counter()
        for char in s[:n // 2]:
            half_count[char] += 1

        result_half = []
        for _ in range(n // 2):
            for char in sorted(half_count.keys()):
                if half_count[char] == 0:
                    continue
                half_count[char] -= 1
                num_permutations = count_permutations(half_count)
                if k <= num_permutations:
                    result_half.append(char)
                    break
                else:
                    k -= num_permutations
                    half_count[char] += 1

        result = ''.join(result_half)
        if n % 2 == 1:
            middle_char = [char for char, count in Counter(s).items() if count % 2 == 1][0]
            result += middle_char
        result += ''.join(reversed(result_half))

        return result