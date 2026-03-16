# Source: https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s and an integer k. Your task is to find the maximum difference between the frequency of two characters, freq[a] - freq[b], in a substring subs of s, such that:
#
#
# 	subs has a size of at least k.
# 	Character a has an odd frequency in subs.
# 	Character b has a non-zero even frequency in subs.
#
#
# Return the maximum difference.
#
# Note that subs can contain more than 2 distinct characters.
#
# Example:
# Input: s = "12233", k = 4
#
# Output: -1
#
# Explanation:
#
# For the substring "12233", the frequency of '1' is 1 and the frequency of '3' is 2. The difference is 1 - 2 = -1.
#
# Constraints:
# 3 <= s.length <= 3 * 104
# 	s consists only of digits '0' to '4'.
# 	The input is generated that at least one substring has a character with an even frequency and a character with an odd frequency.
# 	1 <= k <= s.length
#

class Solution(object):
    def maxDifference(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        from collections import defaultdict

        n = len(s)
        max_diff = float('-inf')

        for a in set(s):
            for b in set(s):
                if a == b:
                    continue

                freq = defaultdict(int)
                left = 0
                odd_count = 0
                even_count = 0

                for right in range(n):
                    freq[s[right]] += 1

                    if freq[s[right]] % 2 == 1:
                        odd_count += 1
                        even_count -= 1
                    else:
                        odd_count -= 1
                        even_count += 1

                    while right - left + 1 > k:
                        freq[s[left]] -= 1
                        if freq[s[left]] % 2 == 1:
                            odd_count += 1
                            even_count -= 1
                        else:
                            odd_count -= 1
                            even_count += 1
                        left += 1

                    if right - left + 1 >= k and freq[a] % 2 == 1 and freq[b] % 2 == 0 and freq[b] > 0:
                        max_diff = max(max_diff, freq[a] - freq[b])

        return max_diff if max_diff != float('-inf') else -1