// Source: https://leetcode.com/problems/number-of-ways-to-split-a-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, you can split s into 3 non-empty strings s1, s2, and s3 where s1 + s2 + s3 = s.
//
// Return the number of ways s can be split such that the number of ones is the same in s1, s2, and s3. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: s = "10101"
// Output: 4
// Explanation: There are four ways to split s in 3 parts where each part contain the same number of letters '1'.
// "1|010|1"
// "1|01|01"
// "10|10|1"
// "10|1|01"
//
// Constraints:
// 3 <= s.length <= 105
// 	s[i] is either '0' or '1'.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int numWays(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        long long totalOnes = 0;
        for (char c : s) {
            if (c == '1') totalOnes++;
        }
        if (totalOnes % 3 != 0) return 0;
        if (totalOnes == 0) {
            // Choose any 2 split points from n-1 gaps
            return (long long)(n - 1) * (n - 2) / 2 % MOD;
        }
        long long onesPerPart = totalOnes / 3;
        long long firstCutWays = 0;
        long long secondCutWays = 0;
        long long onesCount = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') onesCount++;
            if (onesCount == onesPerPart) {
                firstCutWays++;
            } else if (onesCount == 2 * onesPerPart) {
                secondCutWays++;
            }
        }
        return (firstCutWays * secondCutWays) % MOD;            
    }
};
