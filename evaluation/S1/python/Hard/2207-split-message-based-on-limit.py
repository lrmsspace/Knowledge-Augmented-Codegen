# Source: https://leetcode.com/problems/split-message-based-on-limit/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string, message, and a positive integer, limit.
#
# You must split message into one or more parts based on limit. Each resulting part should have the suffix "<a/b>", where "b" is to be replaced with the total number of parts and "a" is to be replaced with the index of the part, starting from 1 and going up to b. Additionally, the length of each resulting part (including its suffix) should be equal to limit, except for the last part whose length can be at most limit.
#
# The resulting parts should be formed such that when their suffixes are removed and they are all concatenated in order, they should be equal to message. Also, the result should contain as few parts as possible.
#
# Return the parts message would be split into as an array of strings. If it is impossible to split message as required, return an empty array.
#
# Example:
# Input: message = "this is really a very awesome message", limit = 9
# Output: ["thi<1/14>","s i<2/14>","s r<3/14>","eal<4/14>","ly <5/14>","a v<6/14>","ery<7/14>"," aw<8/14>","eso<9/14>","me<10/14>"," m<11/14>","es<12/14>","sa<13/14>","ge<14/14>"]
# Explanation:
# The first 9 parts take 3 characters each from the beginning of message.
# The next 5 parts take 2 characters each to finish splitting message. 
# In this example, each part, including the last, has length 9. 
# It can be shown it is not possible to split message into less than 14 parts.
#
# Constraints:
# 1 <= message.length <= 104
# 	message consists only of lowercase English letters and ' '.
# 	1 <= limit <= 104
#
# Helpful references (internal KB):
# - Suffix Array (string, array, merge-sort)
#   • When to use: Use when needing to efficiently query properties of all suffixes or substrings of a given text, especially for pattern matching or finding repeated structures. It is particularly useful for problems requiring lexicographical ordering of all suffixes.
#   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices. It enables efficient string operations like pattern searching and finding longest common prefixes, typically constructed in O(N log N) time.
#   • Invariants: After k iterations, suffixes are sorted correctly up to a certain length (e.g., 2^k).; All suffixes of the original string are represented by their starting indices in the array.
#   • Tips: Append a unique sentinel character (e.g., '$') smaller than any other character to the string.; Utilize the LCP array, often built alongside, for advanced string queries and optimizations.
#   • Pitfalls: Naive sorting of suffixes by string comparison leads to an inefficient O(N^2 log N) complexity.; High memory usage for very long strings due to storing all suffixes implicitly or explicitly.
# - Binary search (interval, number, binary-search-answer, enumeration)
#   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
#   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
#   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
#   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
#   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def splitMessage(self, message, limit):
        """
        :type message: str
        :type limit: int
        :rtype: List[str]
        """
        def can_split_into_parts(total_parts):
            suffix_length = len(f"<{total_parts}/{total_parts}>")
            if suffix_length >= limit:
                return False  # Suffix itself cannot fit in the limit

            content_length = limit - suffix_length
            total_content_capacity = content_length * total_parts
            return total_content_capacity >= len(message)

        low, high = 1, len(message)
        while low < high:
            mid = (low + high) // 2
            if can_split_into_parts(mid):
                high = mid
            else:
                low = mid + 1

        total_parts = low
        if not can_split_into_parts(total_parts):
            return []  # Impossible to split as required

        parts = []
        suffix_length = len(f"<{total_parts}/{total_parts}>")
        content_length = limit - suffix_length

        for i in range(total_parts):
            start_index = i * content_length
            end_index = min(start_index + content_length, len(message))
            part_content = message[start_index:end_index]
            part_suffix = f"<{i+1}/{total_parts}>"
            parts.append(part_content + part_suffix)

        return parts