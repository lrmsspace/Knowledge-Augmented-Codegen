// Source: https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed string s, a string a, a string b, and an integer k.
//
// An index i is beautiful if:
//
//
// 	0 <= i <= s.length - a.length
// 	s[i..(i + a.length - 1)] == a
// 	There exists an index j such that:
// 	
// 		0 <= j <= s.length - b.length
// 		s[j..(j + b.length - 1)] == b
// 		|j - i| <= k
// 	
// 	
//
//
// Return the array that contains beautiful indices in sorted order from smallest to largest.
//
// Example:
// Input: s = "isawsquirrelnearmysquirrelhouseohmy", a = "my", b = "squirrel", k = 15
// Output: [16,33]
// Explanation: There are 2 beautiful indices: [16,33].
// - The index 16 is beautiful as s[16..17] == "my" and there exists an index 4 with s[4..11] == "squirrel" and |16 - 4| <= 15.
// - The index 33 is beautiful as s[33..34] == "my" and there exists an index 18 with s[18..25] == "squirrel" and |33 - 18| <= 15.
// Thus we return [16,33] as the result.
//
// Constraints:
// 1 <= k <= s.length <= 105
// 	1 <= a.length, b.length <= 10
// 	s, a, and b contain only lowercase English letters.
//
// Helpful references (internal KB):
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
// - Finding the nearest pair of points (geometry, array, divide-and-conquer, merge-sort, two-pointers)
//   • When to use: Use this when finding the pair of points with the minimum Euclidean distance in a 2D plane. It efficiently handles large datasets by recursively dividing the problem and merging results.
//   • Idea: It finds the closest pair of points in a 2D plane by recursively dividing the set, solving subproblems, and merging results in O(N log N) time. The merge step efficiently handles cross-boundary pairs within a narrow strip.
//   • Invariants: The minimum distance returned by a recursive call is the true minimum for its input subset.; All points in the left subproblem have x-coordinates less than or equal to the median x-coordinate.
//   • Tips: Pre-sort points by x-coordinate to enable efficient splitting.; Maintain a y-sorted list of points for efficient merging of the strip.
//   • Pitfalls: An inefficient merge step can degrade complexity from O(N log N) to O(N^2).; Failing to correctly identify and process cross-boundary pairs.
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        int n = s.size();
        int a_len = a.size();
        int b_len = b.size();

        vector<int> a_pos;
        for (int i = 0; i <= n - a_len; ++i) {
            if (s.substr(i, a_len) == a) {
                a_pos.push_back(i);
            }
        }

        vector<int> b_pos;
        for (int j = 0; j <= n - b_len; ++j) {
            if (s.substr(j, b_len) == b) {
                b_pos.push_back(j);
            }
        }

        vector<int> ans;
        for (int i : a_pos) {
            // Find if there exists j in b_pos such that |j - i| <= k
            // This means j in [i - k, i + k]
            int left = i - k;
            int right = i + k;
            // Binary search in b_pos
            auto it = lower_bound(b_pos.begin(), b_pos.end(), left);
            if (it != b_pos.end() && *it <= right) {
                ans.push_back(i);
            }
        }

        return ans;         
    }
};
