# Source: https://leetcode.com/problems/count-the-number-of-powerful-integers/   |   Difficulty: Hard
#
# Problem Description:
# You are given three integers start, finish, and limit. You are also given a 0-indexed string s representing a positive integer.
#
# A positive integer x is called powerful if it ends with s (in other words, s is a suffix of x) and each digit in x is at most limit.
#
# Return the total number of powerful integers in the range [start..finish].
#
# A string x is a suffix of a string y if and only if x is a substring of y that starts from some index (including 0) in y and extends to the index y.length - 1. For example, 25 is a suffix of 5125 whereas 512 is not.
#
# Example:
# Input: start = 1, finish = 6000, limit = 4, s = "124"
# Output: 5
# Explanation: The powerful integers in the range [1..6000] are 124, 1124, 2124, 3124, and, 4124. All these integers have each digit <= 4, and "124" as a suffix. Note that 5124 is not a powerful integer because the first digit is 5 which is greater than 4.
# It can be shown that there are only 5 powerful integers in this range.
#
# Constraints:
# 1 <= start <= finish <= 1015
# 	1 <= limit <= 9
# 	1 <= s.length <= floor(log10(finish)) + 1
# 	s only consists of numeric digits which are at most limit.
# 	s does not have leading zeros.
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
# - Suffix Automaton (graph, string, counting)
#   • When to use: Use when processing all suffixes or substrings of a string, especially for tasks requiring counting distinct substrings or efficient pattern matching. It is particularly useful for incremental string construction.
#   • Idea: The Suffix Automaton is a directed acyclic graph that represents all distinct substrings of a given string. It has a linear number of states and transitions, allowing for efficient string processing in O(N) time complexity for construction.
#   • Invariants: The automaton correctly represents all distinct substrings of the string processed up to the current character.; Each state corresponds to an equivalence class of substrings sharing the same end positions.
#   • Tips: Mark terminal states by traversing suffix links from the state representing the full string.; The `last` pointer always tracks the state for the entire string processed.
#   • Pitfalls: Incorrectly handling the three cases for adding a new character can lead to an invalid automaton.; Forgetting to update the `last` state after each character addition breaks incremental construction.
# - Submask Enumeration
#  (number, bitset, enumeration)
#   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
#   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
#   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
#   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
#   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfPowerfulInt(self, start, finish, limit, s):
        """
        :type start: int
        :type finish: int
        :type limit: int
        :type s: str
        :rtype: int
        """
        def count_up_to(n):
            # Count powerful integers up to n
            if n < int(s):
                return 0
            
            count = 0
            suffix_len = len(s)
            suffix_num = int(s)
            
            # Generate powerful integers by appending digits to the left of s
            for prefix in range(10**(15 - suffix_len)):  # Limit prefix to avoid overflow
                powerful_int = prefix * (10 ** suffix_len) + suffix_num
                if powerful_int > n:
                    break
                if all(int(digit) <= limit for digit in str(powerful_int)):
                    count += 1
            
            return count
        
        return count_up_to(finish) - count_up_to(start - 1)