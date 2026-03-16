// Source: https://leetcode.com/problems/shortest-distance-to-target-string-in-a-circular-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed circular string array words and a string target. A circular array means that the array's end connects to the array's beginning.
//
//
// 	Formally, the next element of words[i] is words[(i + 1) % n] and the previous element of words[i] is words[(i - 1 + n) % n], where n is the length of words.
//
//
// Starting from startIndex, you can move to either the next word or the previous word with 1 step at a time.
//
// Return the shortest distance needed to reach the string target. If the string target does not exist in words, return -1.
//
// Example:
// Input: words = ["hello","i","am","leetcode","hello"], target = "hello", startIndex = 1
// Output: 1
// Explanation: We start from index 1 and can reach "hello" by
// - moving 3 units to the right to reach index 4.
// - moving 2 units to the left to reach index 4.
// - moving 4 units to the right to reach index 0.
// - moving 1 unit to the left to reach index 0.
// The shortest distance to reach "hello" is 1.
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 100
// 	words[i] and target consist of only lowercase English letters.
// 	0 <= startIndex < words.length
//
// Helpful references (internal KB):
// - Minimum Enclosing Circle (array, geometry, randomized, recursion)
//   • When to use: Use when finding the smallest circle that contains a given set of 2D points. It provides an expected linear time solution for this fundamental geometric problem.
//   • Idea: Welzl's algorithm finds the unique minimum enclosing circle for a set of points using a randomized incremental approach. It achieves an expected time complexity of O(N).
//   • Invariants: The current candidate circle `C` encloses all points `p_1, ..., p_i` processed so far.; If `p_i` is not contained in `C_{i-1}`, then `p_i` must lie on the boundary of `C_i`.
//   • Tips: Randomly permute input points to ensure expected O(N) performance.; The MEC is uniquely determined by either two points forming a diameter or three points on its boundary.
//   • Pitfalls: Not randomizing the input can lead to a worst-case O(N^3) performance.; Floating-point precision issues can cause incorrect boundary checks or point containment tests.
// - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
//   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
//   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
//   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int closestTarget(String[] words, String target, int startIndex) {
        int n = words.length;
        int minDistance = Integer.MAX_VALUE;

        for (int i = 0; i < n; i++) {
            if (words[i].equals(target)) {
                int distance = Math.abs(i - startIndex);
                distance = Math.min(distance, n - distance); // Circular distance
                minDistance = Math.min(minDistance, distance);
            }
        }

        return minDistance == Integer.MAX_VALUE ? -1 : minDistance;         
    }
}
