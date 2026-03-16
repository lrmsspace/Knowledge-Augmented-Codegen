// Source: https://leetcode.com/problems/find-the-substring-with-maximum-cost/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s, a string chars of distinct characters and an integer array vals of the same length as chars.
//
// The cost of the substring is the sum of the values of each character in the substring. The cost of an empty string is considered 0.
//
// The value of the character is defined in the following way:
//
//
// 	If the character is not in the string chars, then its value is its corresponding position (1-indexed) in the alphabet.
//
// 	
// 		For example, the value of 'a' is 1, the value of 'b' is 2, and so on. The value of 'z' is 26.
// 	
// 	
// 	Otherwise, assuming i is the index where the character occurs in the string chars, then its value is vals[i].
//
//
// Return the maximum cost among all substrings of the string s.
//
// Example:
// Input: s = "adaa", chars = "d", vals = [-1000]
// Output: 2
// Explanation: The value of the characters "a" and "d" is 1 and -1000 respectively.
// The substring with the maximum cost is "aa" and its cost is 1 + 1 = 2.
// It can be proven that 2 is the maximum cost.
//
// Constraints:
// 1 <= s.length <= 105
// 	s consist of lowercase English letters.
// 	1 <= chars.length <= 26
// 	chars consist of distinct lowercase English letters.
// 	vals.length == chars.length
// 	-1000 <= vals[i] <= 1000
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
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
    public int maximumCostSubstring(String s, String chars, int[] vals) {
        // Step 1: Create a mapping of characters to their costs
        Map<Character, Integer> charCostMap = new HashMap<>();
        for (int i = 0; i < chars.length(); i++) {
            charCostMap.put(chars.charAt(i), vals[i]);
        }

        // Step 2: Calculate the maximum cost of any substring using a modified Kadane's algorithm
        int maxCost = 0;
        int currentCost = 0;

        for (char c : s.toCharArray()) {
            int cost = charCostMap.getOrDefault(c, c - 'a' + 1); // Get cost from map or default to alphabet position
            currentCost += cost;

            if (currentCost > maxCost) {
                maxCost = currentCost; // Update max cost if current cost is higher
            }

            if (currentCost < 0) {
                currentCost = 0; // Reset current cost if it drops below zero
            }
        }

        return maxCost;         
    }
}
