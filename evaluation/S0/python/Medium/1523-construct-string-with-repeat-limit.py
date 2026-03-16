# Source: https://leetcode.com/problems/construct-string-with-repeat-limit/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s and an integer repeatLimit. Construct a new string repeatLimitedString using the characters of s such that no letter appears more than repeatLimit times in a row. You do not have to use all characters from s.
#
# Return the lexicographically largest repeatLimitedString possible.
#
# A string a is lexicographically larger than a string b if in the first position where a and b differ, string a has a letter that appears later in the alphabet than the corresponding letter in b. If the first min(a.length, b.length) characters do not differ, then the longer string is the lexicographically larger one.
#
# Example:
# Input: s = "cczazcc", repeatLimit = 3
# Output: "zzcccac"
# Explanation: We use all of the characters from s to construct the repeatLimitedString "zzcccac".
# The letter 'a' appears at most 1 time in a row.
# The letter 'c' appears at most 3 times in a row.
# The letter 'z' appears at most 2 times in a row.
# Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
# The string is the lexicographically largest repeatLimitedString possible so we return "zzcccac".
# Note that the string "zzcccca" is lexicographically larger but the letter 'c' appears more than 3 times in a row, so it is not a valid repeatLimitedString.
#
# Constraints:
# 1 <= repeatLimit <= s.length <= 105
# 	s consists of lowercase English letters.
#

class Solution(object):
    def repeatLimitedString(self, s, repeatLimit):
        """
        :type s: str
        :type repeatLimit: int
        :rtype: str
        """
        from collections import Counter
        import heapq

        count = Counter(s)
        max_heap = [(-ord(char), freq) for char, freq in count.items()]
        heapq.heapify(max_heap)

        result = []
        while max_heap:
            char1, freq1 = heapq.heappop(max_heap)
            char1 = -char1
            use_count = min(freq1, repeatLimit)

            result.append(chr(char1) * use_count)
            freq1 -= use_count

            if freq1 > 0:
                if not max_heap:
                    break
                char2, freq2 = heapq.heappop(max_heap)
                char2 = -char2

                result.append(chr(char2))
                freq2 -= 1

                if freq2 > 0:
                    heapq.heappush(max_heap, (-char2, freq2))

                heapq.heappush(max_heap, (-char1, freq1))
        
        return ''.join(result)