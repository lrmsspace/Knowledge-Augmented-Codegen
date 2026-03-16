# Source: https://leetcode.com/problems/partition-string-into-minimum-beautiful-substrings/   |   Difficulty: Medium
#
# Problem Description:
# Given a binary string s, partition the string into one or more substrings such that each substring is beautiful.
#
# A string is beautiful if:
#
#
# 	It doesn't contain leading zeros.
# 	It's the binary representation of a number that is a power of 5.
#
#
# Return the minimum number of substrings in such partition. If it is impossible to partition the string s into beautiful substrings, return -1.
#
# A substring is a contiguous sequence of characters in a string.
#
# Example:
# Input: s = "1011"
# Output: 2
# Explanation: We can paritition the given string into ["101", "1"].
# - The string "101" does not contain leading zeros and is the binary representation of integer 51 = 5.
# - The string "1" does not contain leading zeros and is the binary representation of integer 50 = 1.
# It can be shown that 2 is the minimum number of beautiful substrings that s can be partitioned into.
#
# Constraints:
# 1 <= s.length <= 15
# 	s[i] is either '0' or '1'.
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Submask Enumeration
#  (number, bitset, enumeration)
#   • When to use: When you need to iterate through all possible submasks of a given bitmask efficiently, typically for problems involving subsets or combinations represented by bits.
#   • Idea: This algorithm efficiently iterates through all submasks of a given bitmask in descending order using a clever bitwise trick. It processes each submask in O(1) time, leading to an overall complexity of O(2^k) where k is the number of set bits in the original mask.
#   • Invariants: Each `s` generated is a valid submask of the original mask `m`.; The value of `s` strictly decreases in each iteration until it reaches 0 (or the loop terminates).
#   • Tips: Always consider processing the submask 0 separately if it's a valid case for your problem.; The iteration naturally generates submasks in strictly descending numerical order.
#   • Pitfalls: Forgetting that the standard loop structure `for (int s = m; s > 0; s = (s - 1) & m)` omits submask 0.; Incorrectly assuming the iteration order is ascending; it is always descending.
# - Fibonacci Numbers (number, greedy, enumeration)
#   • When to use: When you need a unique, non-ambiguous binary representation of positive integers based on Fibonacci numbers, ensuring no two consecutive Fibonacci numbers are used in the sum.
#   • Idea: This algorithm encodes a positive integer into a unique binary string by greedily finding its Zeckendorf representation (sum of non-consecutive Fibonacci numbers). The encoding process typically involves iterating through Fibonacci numbers, resulting in a logarithmic time complexity relative to the input number's magnitude.
#   • Invariants: The remaining value 'n' to be encoded is always non-negative.; The partial binary code constructed so far represents a valid Zeckendorf sum of non-consecutive Fibonacci numbers.
#   • Tips: Precompute Fibonacci numbers up to a certain limit to optimize lookups.; Always start with the largest Fibonacci number less than or equal to the target value.
#   • Pitfalls: Incorrectly handling the base cases for small numbers like 1 or 2.; Forgetting to append the mandatory final '1' bit to the codeword.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumBeautifulSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        # Precompute the set of beautiful numbers (powers of 5) that can be represented in binary with up to 15 bits
        beautiful_numbers = set()
        power_of_5 = 1
        while power_of_5 <= (1 << 15):  # 2^15 is the largest number we need to consider
            beautiful_numbers.add(bin(power_of_5)[2:])  # Add binary representation without '0b' prefix
            power_of_5 *= 5

        n = len(s)
        dp = [float('inf')] * (n + 1)
        dp[0] = 0  # Base case: no substrings needed for an empty string

        for i in range(1, n + 1):
            for j in range(i):
                if dp[j] != float('inf') and s[j:i] in beautiful_numbers:
                    dp[i] = min(dp[i], dp[j] + 1)

        return dp[n] if dp[n] != float('inf') else -1