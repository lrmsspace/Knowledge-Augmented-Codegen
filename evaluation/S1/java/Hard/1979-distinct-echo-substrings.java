// Source: https://leetcode.com/problems/distinct-echo-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Return the number of distinct non-empty substrings of text that can be written as the concatenation of some string with itself (i.e. it can be written as a + a where a is some string).
//
// Example:
// Input: text = "abcabcabc"
// Output: 3
// Explanation: The 3 substrings are "abcabc", "bcabca" and "cabcab".
//
// Constraints:
// 1 <= text.length <= 2000
// 	text has only lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int distinctEchoSubstrings(String text) {
        int n = text.length();
        Set<Long> seen = new HashSet<>();
        long mod1 = (long)1e9 + 7, mod2 = (long)1e9 + 9, base = 31;

        long[] hash1 = new long[n + 1];
        long[] hash2 = new long[n + 1];
        long[] power1 = new long[n + 1];
        long[] power2 = new long[n + 1];
        power1[0] = 1;
        power2[0] = 1;

        for (int i = 0; i < n; i++) {
            hash1[i + 1] = (hash1[i] * base + (text.charAt(i) - 'a' + 1)) % mod1;
            hash2[i + 1] = (hash2[i] * base + (text.charAt(i) - 'a' + 1)) % mod2;
            power1[i + 1] = (power1[i] * base) % mod1;
            power2[i + 1] = (power2[i] * base) % mod2;
        }

        for (int length = 1; length <= n / 2; length++) {
            for (int start = 0; start <= n - 2 * length; start++) {
                int mid = start + length;
                int end = start + 2 * length;

                long hashFirst1 = (hash1[mid] - (hash1[start] * power1[length]) % mod1 + mod1) % mod1;
                long hashSecond1 = (hash1[end] - (hash1[mid] * power1[length]) % mod1 + mod1) % mod1;

                long hashFirst2 = (hash2[mid] - (hash2[start] * power2[length]) % mod2 + mod2) % mod2;
                long hashSecond2 = (hash2[end] - (hash2[mid] * power2[length]) % mod2 + mod2) % mod2;

                if (hashFirst1 == hashSecond1 && hashFirst2 == hashSecond2) {
                    long combinedHash = (hashFirst1 << 32) | hashFirst2;
                    seen.add(combinedHash);
                }
            }
        }
        return seen.size();
    }
}
