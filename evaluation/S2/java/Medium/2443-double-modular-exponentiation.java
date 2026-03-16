// Source: https://leetcode.com/problems/double-modular-exponentiation/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D array variables where variables[i] = [ai, bi, ci, mi], and an integer target.
//
// An index i is good if the following formula holds:
//
//
// 	0 <= i < variables.length
// 	((aibi % 10)ci) % mi == target
//
//
// Return an array consisting of good indices in any order.
//
// Example:
// Input: variables = [[2,3,3,10],[3,3,3,1],[6,1,1,4]], target = 2
// Output: [0,2]
// Explanation: For each index i in the variables array:
// 1) For the index 0, variables[0] = [2,3,3,10], (23 % 10)3 % 10 = 2.
// 2) For the index 1, variables[1] = [3,3,3,1], (33 % 10)3 % 1 = 0.
// 3) For the index 2, variables[2] = [6,1,1,4], (61 % 10)1 % 4 = 2.
// Therefore we return [0,2] as the answer.
//
// Constraints:
// 1 <= variables.length <= 100
// 	variables[i] == [ai, bi, ci, mi]
// 	1 <= ai, bi, ci, mi <= 103
// 	0 <= target <= 103
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Rabin-Karp Algorithm for string matching (string, number, hashing, rolling-hash)
//   • When to use: To efficiently find all occurrences of a given pattern string within a larger text string, especially when multiple patterns might be searched or for average-case linear time performance.
//   • Idea: The Rabin-Karp algorithm finds occurrences of a pattern in a text by comparing their hash values, using a rolling hash function to efficiently update substring hashes. It achieves an average time complexity of O(|s| + |t|) and a worst-case of O(|s| * |t|).
//   • Invariants: The hash of the pattern string remains constant throughout the search.; The current window's hash value accurately represents the substring T[i...i+len(P)-1].
//   • Tips: Choose a large prime modulus to minimize hash collisions.; Select a suitable base (e.g., a prime greater than alphabet size) for polynomial hashing.
//   • Pitfalls: Hash collisions can lead to false positives and degrade worst-case performance to O(MN).; Poor choice of base or modulus can significantly increase collision frequency.
// - Chinese Remainder Theorem (number, recursion, mod-exp)
//   • When to use: When you need to find a unique integer solution that satisfies a system of linear congruences with pairwise coprime moduli. It is used to reconstruct a number from its remainders modulo several divisors.
//   • Idea: The Chinese Remainder Theorem (CRT) finds a unique solution x modulo the product of several pairwise coprime moduli, given a system of congruences. It typically involves computing modular inverses and combining solutions, with a complexity often dominated by modular exponentiation or extended Euclidean algorithm, usually O(N log M) or O(N log(max_modulus)).
//   • Invariants: The current combined solution 'x' satisfies 'x % m_i == a_i' for all congruences '(a_i, m_i)' processed so far.; The current combined modulus 'M' is the product of all individual moduli processed so far.
//   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Use the Extended Euclidean Algorithm to find modular inverses.
//   • Pitfalls: Forgetting to check if moduli are pairwise coprime.; Incorrectly calculating modular inverses.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> getGoodIndices(int[][] variables, int target) {
        List<Integer> goodIndices = new ArrayList<>();

        for (int i = 0; i < variables.length; i++) {
            int a = variables[i][0];
            int b = variables[i][1];
            int c = variables[i][2];
            int m = variables[i][3];

            // Calculate (a^b % 10)^c % m
            int modExp = modExp(a, b, 10);
            int result = modExp(modExp, c, m);

            if (result == target) {
                goodIndices.add(i);
            }
        }

        return goodIndices;         
    }
}
