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
# Helpful references (internal KB):
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - String Sorts (array, string, number, radix-sort, counting-sort)
#   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
#   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
#   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
#   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
#   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
# - String Sorts (array, string, number, radix-sort, recursion, counting-sort)
#   • When to use: Use when sorting a large collection of strings or integers with a limited range of character/digit values. It is particularly efficient for fixed-length keys but can be adapted for variable lengths.
#   • Idea: Radix sort is a non-comparative integer sorting algorithm that sorts data with integer keys by grouping keys by individual digits or characters which share the same significant position and value. It typically achieves O(N*W) time complexity, where N is the number of items and W is the key length.
#   • Invariants: After each pass `d`, the elements are stably sorted according to their digits up to position `d`.; The counting sort subroutine correctly places elements into their sorted positions for the current digit, preserving relative order.
#   • Tips: LSD (Least Significant Digit) is simpler for fixed-length keys.; MSD (Most Significant Digit) is better for variable-length keys or when keys are very long.
#   • Pitfalls: Not efficient for small N or very large W due to constant factors.; Requires extra space for auxiliary array and counting array.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def repeatLimitedString(self, s, repeatLimit):
        """
        :type s: str
        :type repeatLimit: int
        :rtype: str
        """
        from collections import Counter
        import heapq

        char_count = Counter(s)
        max_heap = [(-ord(char), count) for char, count in char_count.items()]
        heapq.heapify(max_heap)

        result = []
        prev_char = None
        prev_count = 0

        while max_heap:
            char, count = heapq.heappop(max_heap)
            char = chr(-char)

            if char == prev_char and prev_count == repeatLimit:
                if not max_heap:
                    break
                next_char, next_count = heapq.heappop(max_heap)
                next_char = chr(-next_char)

                result.append(next_char)
                next_count -= 1

                if next_count > 0:
                    heapq.heappush(max_heap, (-ord(next_char), next_count))

                heapq.heappush(max_heap, (-ord(char), count))
            else:
                result.append(char)
                count -= 1

                if count > 0:
                    heapq.heappush(max_heap, (-ord(char), count))

                prev_char = char
                prev_count = (prev_count + 1) if char == prev_char else 1

        return ''.join(result)