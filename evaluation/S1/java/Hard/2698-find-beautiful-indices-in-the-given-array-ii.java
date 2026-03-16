// Source: https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-ii/   |   Difficulty: Hard
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
// 1 <= k <= s.length <= 5 * 105
// 	1 <= a.length, b.length <= 5 * 105
// 	s, a, and b contain only lowercase English letters.
//
// Helpful references (internal KB):
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
// - Z-function and its calculation (string, array, two-pointers)
//   • When to use: Use when you need to find the length of the longest common prefix between a string and all its suffixes efficiently. It is fundamental for various string matching and pattern searching problems.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the original string and its suffix starting at index i. This algorithm calculates the entire Z-array in O(N) time complexity.
//   • Invariants: For all k < i, z[k] has been correctly computed.; The interval [l, r) always represents the rightmost segment match found so far.
//   • Tips: Leverage previously computed Z-values to avoid redundant comparisons.; Maintain a [l, r) window representing the rightmost segment match found so far.
//   • Pitfalls: Incorrectly handling the base case z[0] (usually set to 0).; Off-by-one errors when calculating the length of the prefix or updating the window.
// - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
//   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
//   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
//   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> beautifulIndices(String s, String a, String b, int k) {
        List<Integer> result = new ArrayList<>();
        int n = s.length();
        int m = a.length();
        int p = b.length();

        boolean[] isAStart = new boolean[n];
        boolean[] isBStart = new boolean[n];

        // Find all occurrences of a in s
        for (int i = 0; i <= n - m; i++) {
            if (s.substring(i, i + m).equals(a)) {
                isAStart[i] = true;
            }
        }

        // Find all occurrences of b in s
        for (int i = 0; i <= n - p; i++) {
            if (s.substring(i, i + p).equals(b)) {
                isBStart[i] = true;
            }
        }

        // Collect all starting indices of b
        List<Integer> bIndices = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (isBStart[i]) {
                bIndices.add(i);
            }
        }

        // For each occurrence of a, check for a valid b within distance k
        for (int i = 0; i <= n - m; i++) {
            if (isAStart[i]) {
                // Binary search to find the closest b index
                int left = 0, right = bIndices.size() - 1;
                boolean found = false;

                while (left <= right) {
                    int mid = left + (right - left) / 2;
                    int bIndex = bIndices.get(mid);

                    if (Math.abs(bIndex - i) <= k) {
                        found = true;
                        break;
                    } else if (bIndex < i) {
                        left = mid + 1;
                    } else {
                        right = mid - 1;
                    }
                }

                if (found) {
                    result.add(i);
                }
            }
        }

        return result;          
    }
}
