// Source: https://leetcode.com/problems/minimum-cost-to-convert-string-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English characters. You are also given two 0-indexed string arrays original and changed, and an integer array cost, where cost[i] represents the cost of converting the string original[i] to the string changed[i].
//
// You start with the string source. In one operation, you can pick a substring x from the string, and change it to y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y. You are allowed to do any number of operations, but any pair of operations must satisfy either of these two conditions:
//
//
// 	The substrings picked in the operations are source[a..b] and source[c..d] with either b < c or d < a. In other words, the indices picked in both operations are disjoint.
// 	The substrings picked in the operations are source[a..b] and source[c..d] with a == c and b == d. In other words, the indices picked in both operations are identical.
//
//
// Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.
//
// Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].
//
// Example:
// Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
// Output: 28
// Explanation: To convert "abcd" to "acbe", do the following operations:
// - Change substring source[1..1] from "b" to "c" at a cost of 5.
// - Change substring source[2..2] from "c" to "e" at a cost of 1.
// - Change substring source[2..2] from "e" to "b" at a cost of 2.
// - Change substring source[3..3] from "d" to "e" at a cost of 20.
// The total cost incurred is 5 + 1 + 2 + 20 = 28. 
// It can be shown that this is the minimum possible cost.
//
// Constraints:
// 1 <= source.length == target.length <= 1000
// 	source, target consist only of lowercase English characters.
// 	1 <= cost.length == original.length == changed.length <= 100
// 	1 <= original[i].length == changed[i].length <= source.length
// 	original[i], changed[i] consist only of lowercase English characters.
// 	original[i] != changed[i]
// 	1 <= cost[i] <= 106
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to efficiently compare strings or substrings, especially in scenarios involving large texts or numerous comparisons. It's also useful for pattern matching and detecting duplicates in collections of strings.
//   • Idea: String hashing converts a string into a numerical value (hash) to enable fast comparisons and lookups. This technique typically uses polynomial hashing with a base and a modulus, offering O(L) for initial hash computation and O(1) for substring hashes after O(N) precomputation.
//   • Invariants: The hash of a string S of length L is (S[0]*P^(L-1) + S[1]*P^(L-2) + ... + S[L-1]*P^0) % M.; For any substring S[i...j], its hash can be derived from precomputed prefix hashes in O(1) time.
//   • Tips: Use multiple hash functions with different bases and moduli to reduce collision probability.; Choose a large prime modulus (e.g., 10^9 + 7) and a random base for robustness.
//   • Pitfalls: Hash collisions are possible; always verify equality for critical applications or use multiple hashes.; Choosing a small or non-prime modulus significantly increases the risk of collisions.
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to compare strings or substrings quickly, reducing comparison time from linear to constant. It is ideal for problems requiring frequent string equality checks or pattern matching across large texts.
//   • Idea: String hashing maps a string to an integer hash value, allowing for O(1) equality checks between strings or substrings. This technique relies on a hash function where equal strings must produce equal hashes, though the reverse is not guaranteed.
//   • Invariants: The hash of any prefix s[0...i] is correctly computed based on s[0...i-1] and s[i].; All characters processed up to the current index i contribute to the current hash value.
//   • Tips: Use a polynomial rolling hash function with a prime base and a large prime modulus.; Employ double hashing (two different bases/moduli) to significantly reduce collision probability.
//   • Pitfalls: Hash collisions: Different strings can produce the same hash, leading to false positives if not handled.; Poor choice of base or modulus can lead to more frequent collisions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long minimumCost(String source, String target, String[] original, String[] changed, int[] cost) {
        int n = source.length();
        long[][] dp = new long[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = Long.MAX_VALUE;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (source.charAt(i) == target.charAt(j)) {
                    dp[i][j] = (i > 0 && j > 0) ? dp[i - 1][j - 1] : 0;
                }
                for (int k = 0; k < original.length; k++) {
                    String o = original[k], c = changed[k];
                    if (i + o.length() <= n && j + c.length() <= n
                            && source.substring(i, i + o.length()).equals(o)
                            && target.substring(j, j + c.length()).equals(c)) {
                        long prevCost = (i > 0 && j > 0) ? dp[i - 1][j - 1] : 0;
                        if (prevCost != Long.MAX_VALUE) {
                            dp[i + o.length() - 1][j + c.length() - 1] =
                                    Math.min(dp[i + o.length() - 1][j + c.length() - 1], prevCost + cost[k]);
                        }
                    }
                }
            }
        }

        return dp[n - 1][n - 1] == Long.MAX_VALUE ? -1 : dp[n - 1][n - 1];          
    }
}
