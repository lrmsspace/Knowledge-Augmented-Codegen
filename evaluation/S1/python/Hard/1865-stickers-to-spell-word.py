# Source: https://leetcode.com/problems/stickers-to-spell-word/   |   Difficulty: Hard
#
# Problem Description:
# We are given n different types of stickers. Each sticker has a lowercase English word on it.
#
# You would like to spell out the given string target by cutting individual letters from your collection of stickers and rearranging them. You can use each sticker more than once if you want, and you have infinite quantities of each sticker.
#
# Return the minimum number of stickers that you need to spell out target. If the task is impossible, return -1.
#
# Note: In all test cases, all words were chosen randomly from the 1000 most common US English words, and target was chosen as a concatenation of two random words.
#
# Example:
# Input: stickers = ["with","example","science"], target = "thehat"
# Output: 3
# Explanation:
# We can use 2 "with" stickers, and 1 "example" sticker.
# After cutting and rearrange the letters of those stickers, we can form the target "thehat".
# Also, this is the minimum number of stickers necessary to form the target string.
#
# Constraints:
# n == stickers.length
# 	1 <= n <= 50
# 	1 <= stickers[i].length <= 10
# 	1 <= target.length <= 15
# 	stickers[i] and target consist of lowercase English letters.
#
# Helpful references (internal KB):
# - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
#   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
#   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
#   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
#   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
#   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Counting labeled graphs (number, recursion, counting, dp-1d)
#   • When to use: When the problem requires enumerating distinct labeled graphs with specific properties, such as connectivity, on a given number of vertices. It is suitable for combinatorial counting problems involving graph structures.
#   • Idea: This technique determines the number of connected labeled graphs by subtracting the count of disconnected graphs from the total. It typically employs a recursive or dynamic programming approach, often involving combinatorial terms like binomial coefficients, with a polynomial time complexity.
#   • Invariants: The total number of labeled graphs $G_n$ for $n$ vertices is always $2^{n(n-1)/2}$.; For any $n$, the sum of connected and disconnected labeled graphs equals the total number of labeled graphs.
#   • Tips: Start with the total number of labeled graphs $G_n = 2^{n(n-1)/2}$.; Use complementary counting: total graphs minus disconnected graphs.
#   • Pitfalls: Forgetting to divide by $n$ when converting from rooted to unrooted disconnected graphs.; Incorrectly handling base cases for recursive definitions or DP states.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minStickers(self, stickers, target):
        """
        :type stickers: List[str]
        :type target: str
        :rtype: int
        """
        # Step 1: Count the frequency of each character in the target
        target_count = [0] * 26
        for char in target:
            target_count[ord(char) - ord('a')] += 1

        # Step 2: Count the frequency of each character in each sticker
        sticker_counts = []
        for sticker in stickers:
            count = [0] * 26
            for char in sticker:
                count[ord(char) - ord('a')] += 1
            sticker_counts.append(count)

        # Step 3: Use a recursive function with memoization to find the minimum stickers needed
        memo = {}

        def dfs(target_count):
            # Convert target_count to a tuple to use as a key for memoization
            key = tuple(target_count)
            if key in memo:
                return memo[key]

            # Base case: if all counts are zero, we need 0 stickers
            if all(x == 0 for x in target_count):
                return 0

            min_stickers = float('inf')

            # Try using each sticker and see how it reduces the target_count
            for sticker in sticker_counts:
                # If the sticker does not contribute to reducing the target, skip it
                if all(sticker[i] <= target_count[i] for i in range(26)):
                    continue

                # Create a new target count after using this sticker
                new_target_count = [max(0, target_count[i] - sticker[i]) for i in range(26)]
                stickers_needed = dfs(new_target_count)
                if stickers_needed != -1:
                    min_stickers = min(min_stickers, stickers_needed + 1)

            memo[key] = -1 if min_stickers == float('inf') else min_stickers
            return memo[key]

        return dfs(target_count)