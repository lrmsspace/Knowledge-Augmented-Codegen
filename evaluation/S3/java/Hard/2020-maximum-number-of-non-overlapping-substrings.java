// Source: https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s of lowercase letters, you need to find the maximum number of non-empty substrings of s that meet the following conditions:
//
//
// 	The substrings do not overlap, that is for any two substrings s[i..j] and s[x..y], either j < x or i > y is true.
// 	A substring that contains a certain character c must also contain all occurrences of c.
//
//
// Find the maximum number of substrings that meet the above conditions. If there are multiple solutions with the same number of substrings, return the one with minimum total length. It can be shown that there exists a unique solution of minimum total length.
//
// Notice that you can return the substrings in any order.
//
// Example:
// Input: s = "adefaddaccc"
// Output: ["e","f","ccc"]
// Explanation: The following are all the possible substrings that meet the conditions:
// [
//   "adefaddaccc"
//   "adefadda",
//   "ef",
//   "e",
//   "f",
//   "ccc",
// ]
// If we choose the first string, we cannot choose anything else and we'd get only 1. If we choose "adefadda", we are left with "ccc" which is the only one that doesn't overlap, thus obtaining 2 substrings. Notice also, that it's not optimal to choose "ef" since it can be split into two. Therefore, the optimal way is to choose ["e","f","ccc"] which gives us 3 substrings. No other solution of the same number of substrings exist.
//
// Constraints:
// 1 <= s.length <= 105
// 	s contains only lowercase English letters.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<String> maxNumOfSubstrings(String s) {
        int n = s.length();
        int[] left = new int[26];
        int[] right = new int[26];
        Arrays.fill(left, Integer.MAX_VALUE);
        Arrays.fill(right, Integer.MIN_VALUE);

        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            left[c - 'a'] = Math.min(left[c - 'a'], i);
            right[c - 'a'] = Math.max(right[c - 'a'], i);
        }

        List<String> result = new ArrayList<>();
        for (int i = 0; i < 26; i++) {
            if (left[i] == Integer.MAX_VALUE) continue;

            int start = left[i];
            int end = right[i];
            boolean valid = true;

            for (int j = start; j <= end; j++) {
                char c = s.charAt(j);
                if (left[c - 'a'] < start || right[c - 'a'] > end) {
                    valid = false;
                    break;
                }
                start = Math.min(start, left[c - 'a']);
                end = Math.max(end, right[c - 'a']);
            }

            if (valid) {
                result.add(s.substring(start, end + 1));
            }
        }

        result.sort(Comparator.comparingInt(String::length));
        List<String> nonOverlappingSubstrings = new ArrayList<>();
        int lastEnd = -1;

        for (String substring : result) {
            int currentStart = s.indexOf(substring);
            int currentEnd = currentStart + substring.length() - 1;

            if (currentStart > lastEnd) {
                nonOverlappingSubstrings.add(substring);
                lastEnd = currentEnd;
            }
        }

        return nonOverlappingSubstrings;            
    }
}
