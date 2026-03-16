// Source: https://leetcode.com/problems/length-of-the-longest-increasing-path/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array of integers coordinates of length n and an integer k, where 0 <= k < n.
//
// coordinates[i] = [xi, yi] indicates the point (xi, yi) in a 2D plane.
//
// An increasing path of length m is defined as a list of points (x1, y1), (x2, y2), (x3, y3), ..., (xm, ym) such that:
//
//
// 	xi < xi + 1 and yi < yi + 1 for all i where 1 <= i < m.
// 	(xi, yi) is in the given coordinates for all i where 1 <= i <= m.
//
//
// Return the maximum length of an increasing path that contains coordinates[k].
//
// Example:
// Input: coordinates = [[3,1],[2,2],[4,1],[0,0],[5,3]], k = 1
//
// Output: 3
//
// Explanation:
//
// (0, 0), (2, 2), (5, 3) is the longest increasing path that contains (2, 2).
//
// Constraints:
// 1 <= n == coordinates.length <= 105
// 	coordinates[i].length == 2
// 	0 <= coordinates[i][0], coordinates[i][1] <= 109
// 	All elements in coordinates are distinct.
// 	0 <= k <= n - 1
//
// Helpful references (internal KB):
// - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
//   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
//   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
// - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
//   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
//   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
//   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
// - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
//   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
//   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
//   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
//   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
//   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxPathLength(int[][] coordinates, int k) {
        int n = coordinates.length;
        int[][] points = new int[n][3];
        for (int i = 0; i < n; i++) {
            points[i][0] = coordinates[i][0];
            points[i][1] = coordinates[i][1];
            points[i][2] = i;
        }
        Arrays.sort(points, (a, b) -> a[0] != b[0] ? Integer.compare(a[0], b[0]) : Integer.compare(a[1], b[1]));

        // Coordinate compression for y-coordinates
        TreeSet<Integer> ys = new TreeSet<>();
        for (int[] point : points) {
            ys.add(point[1]);
        }
        Map<Integer, Integer> yToIndex = new HashMap<>();
        int idx = 0;
        for (int y : ys) {
            yToIndex.put(y, idx++);
        }

        // Segment tree to store the longest increasing path length
        SegmentTree segTree = new SegmentTree(idx);
        int maxLength = 1;

        for (int[] point : points) {
            int x = point[0];
            int y = point[1];
            int originalIndex = point[2];
            int compressedY = yToIndex.get(y);

            // Get the longest path length for all points with smaller x and y
            int currentLength = segTree.query(0, compressedY - 1) + 1;
            segTree.update(compressedY, currentLength);

            if (originalIndex == k) {
                maxLength = currentLength;
            }
        }

        return maxLength;           
    }
}
