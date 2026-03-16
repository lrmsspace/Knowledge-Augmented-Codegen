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
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - Suffix array (array, string, suffix-array, binary-search)
//   • When to use: Use suffix arrays for efficient string processing tasks like finding all occurrences of a pattern, locating the longest common substring, or performing various substring queries. It provides a sorted index of all suffixes.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices in lexicographical order. It enables various string operations to be performed efficiently, often with O(N log N) or O(N) time complexity for construction and O(M log N) or O(M) for queries.
//   • Invariants: The suffix array A always contains N elements, where N is the length of the original string.; For any valid index i, A[i] stores a starting position within the original string S.
//   • Tips: Append a unique sentinel character (e.g., '$') to the string to ensure all suffixes are distinct.; Combine with a Longest Common Prefix (LCP) array for enhanced functionality, such as counting distinct substrings.
//   • Pitfalls: Naive construction by sorting all suffixes directly is inefficient (O(N^2 log N) or worse).; Implementing advanced construction algorithms from scratch can be complex and error-prone.
// - Finding repetitions (string, divide-and-conquer, recursion)
//   • When to use: This algorithm is used to find all occurrences of repeating substrings within a given string. It is suitable for problems requiring the identification of periodic patterns or structural redundancies.
//   • Idea: This algorithm, often exemplified by Main-Lorentz, uses a divide-and-conquer strategy with Z-function as a subroutine to efficiently find all repetitions in a string. It typically achieves an O(N log N) time complexity for finding and describing repetitions.
//   • Invariants: All repetitions fully contained within the left or right subproblems are found recursively.; Crossing repetitions are identified by combining information from both subproblems using Z-function.
//   • Tips: Understand the definition of a 'repetition' (e.g., Crochemore triples or (i, p, r) tuples).; Leverage string algorithms like Z-function for efficient substring matching in subproblems.
//   • Pitfalls: Expanding compact repetition tuples to full start/end indices can lead to O(N^2) complexity.; Incorrectly handling string reversal or concatenation for Z-function applications.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string longestDupSubstring(string s) {
        int n = s.length(); 
        vector<long long> p_pow(n), prefix_hash(n);
        const long long p = 31, m = 1e9 + 7;
        p_pow[0] = 1;
        prefix_hash[0] = s[0] - 'a' + 1;
        for (int i = 1; i < n; ++i) {
            p_pow[i] = (p_pow[i - 1] * p) % m;
            prefix_hash[i] = (prefix_hash[i - 1] * p + (s[i] - 'a' + 1)) % m;
        }
        auto get_hash = [&](int l, int r) {
            long long hash_value = prefix_hash[r];
            if (l > 0) {
                hash_value = (hash_value - (prefix_hash[l - 1] * p_pow[r - l + 1]) % m + m) % m;
            }
            return hash_value;
        };
        string result;
        for (int length = 1; length < n; ++length) {
            unordered_set<long long> seen_hashes;
            bool found = false;
            for (int i = 0; i + length <= n; ++i) {
                long long hash_value = get_hash(i, i + length - 1);
                if (seen_hashes.count(hash_value)) {
                    result = s.substr(i, length);
                    found = true;
                    break;
                }
                seen_hashes.insert(hash_value);
            }
            if (!found) break; 
        }
        return result;
    }
};
