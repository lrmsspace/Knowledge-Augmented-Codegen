// Source: https://leetcode.com/problems/longest-duplicate-substring/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, consider all duplicated substrings: (contiguous) substrings of s that occur 2 or more times. The occurrences may overlap.
//
// Return any duplicated substring that has the longest possible length. If s does not have a duplicated substring, the answer is "".
//
// Example:
// Input: s = "banana"
// Output: "ana"
//
// Constraints:
// 2 <= s.length <= 3 * 104
// 	s consists of lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this algorithm to find the maximum length of a subsequence where elements are strictly increasing. It is particularly efficient when optimizing the O(N^2) dynamic programming solution to O(N log N) using binary search.
//   • Idea: This algorithm determines the longest subsequence of a given sequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search.
//   • Invariants: The 'tails' array always stores the smallest ending element for increasing subsequences of various lengths.; The 'tails' array is always sorted in strictly increasing order.
//   • Tips: The O(N log N) approach maintains an array 'tails' where 'tails[i]' is the smallest ending element of an increasing subsequence of length 'i+1'.; Utilize binary search (e.g., `std::lower_bound`) to find the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing a subsequence with a contiguous subarray, which is a common mistake.; Incorrectly updating the 'tails' array, leading to non-increasing subsequences or incorrect lengths.
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private String searchDuplicate(String s, int length) {
        long modulus = (1L << 31) - 1; // A large prime number
        long base = 31; // A small prime number
        long hash = 0;
        int n = s.length();
        long baseL = 1;

        for (int i = 0; i < length; i++) {
            hash = (hash * base + (s.charAt(i) - 'a' + 1)) % modulus;
            if (i > 0) {
                baseL = (baseL * base) % modulus;
            }
        }

        Set<Long> seenHashes = new HashSet<>();
        seenHashes.add(hash);

        for (int start = 1; start <= n - length; start++) {
            hash = (hash * base - (s.charAt(start - 1) - 'a' + 1) * baseL % modulus + modulus) % modulus;
            hash = (hash + (s.charAt(start + length - 1) - 'a' + 1)) % modulus;

            if (seenHashes.contains(hash)) {
                return s.substring(start, start + length);
            }
            seenHashes.add(hash);
        }

        return null;
    }
    public String longestDupSubstring(String s) {
        int n = s.length();
        int left = 1, right = n - 1;
        String result = "";

        while (left <= right) {
            int mid = left + (right - left) / 2;
            String dup = searchDuplicate(s, mid);
            if (dup != null) {
                result = dup;
                left = mid + 1; // Try for a longer length
            } else {
                right = mid - 1; // Try for a shorter length
            }
        }

        return result;          
    }
}
