// Source: https://leetcode.com/problems/peaks-in-array/   |   Difficulty: Hard
//
// Problem Description:
// A peak in an array arr is an element that is greater than its previous and next element in arr.
//
// You are given an integer array nums and a 2D integer array queries.
//
// You have to process queries of two types:
//
//
// 	queries[i] = [1, li, ri], determine the count of peak elements in the subarray nums[li..ri].
// 	queries[i] = [2, indexi, vali], change nums[indexi] to vali.
//
//
// Return an array answer containing the results of the queries of the first type in order.
//
// Notes:
//
//
// 	The first and the last element of an array or a subarray cannot be a peak.
//
// Example:
// Input: nums = [3,1,4,2,5], queries = [[2,3,4],[1,0,4]]
//
// Output: [0]
//
// Explanation:
//
// First query: We change nums[3] to 4 and nums becomes [3,1,4,4,5].
//
// Second query: The number of peaks in the [3,1,4,4,5] is 0.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i][0] == 1 or queries[i][0] == 2
// 	For all i that:
// 	
// 		queries[i][0] == 1: 0 <= queries[i][1] <= queries[i][2] <= nums.length - 1
// 		queries[i][0] == 2: 0 <= queries[i][1] <= nums.length - 1, 1 <= queries[i][2] <= 105
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, divide-and-conquer)
//   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
//   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
//   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
//   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
// - MEX (minimal excluded) of a sequence (ds, enumeration)
//   • When to use: Use when needing to efficiently find the smallest non-negative integer not present in a dynamic sequence or range, supporting both updates and queries in logarithmic time.
//   • Idea: This technique finds the Minimal Excluded (MEX) value in a sequence by maintaining counts of distinct elements in ranges using a specialized data structure, typically a segment tree. It supports both updates and queries in O(log N) time.
//   • Invariants: Each segment tree node accurately reflects the count of distinct numbers within its corresponding range.; If a range [L, R) contains R-L distinct numbers, then all integers from L to R-1 are present.
//   • Tips: Implement a segment tree where each node stores the count of distinct numbers in its range.; The binary search for MEX checks if a range [0, k) contains k distinct numbers to decide which child to traverse.
//   • Pitfalls: Incorrectly calculating distinct counts in segment tree nodes, especially after updates.; Off-by-one errors when comparing the number of distinct elements with the expected count for a full range.
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    static class SegmentTree {
        private final int size;
        private final int[] tree;

        public SegmentTree(int n) {
            size = 1;
            while (size < n) size <<= 1;
            tree = new int[2 * size];
        }

        public void update(int index, int value) {
            int pos = index + size;
            tree[pos] = value;
            while (pos > 1) {
                pos >>= 1;
                tree[pos] = tree[2 * pos] + tree[2 * pos + 1];
            }
        }

        public int query(int left, int right) {
            int result = 0;
            left += size;
            right += size;
            while (left <= right) {
                if ((left & 1) == 1) result += tree[left++];
                if ((right & 1) == 0) result += tree[right--];
                left >>= 1;
                right >>= 1;
            }
            return result;
        }
    }
    private boolean isPeak(int[] nums, int index) {
        return nums[index] > nums[index - 1] && nums[index] > nums[index + 1];
    }
    public List<Integer> countOfPeaks(int[] nums, int[][] queries) {
        int n = nums.length;
        SegmentTree segTree = new SegmentTree(n);
        for (int i = 1; i < n - 1; i++) {
            if (isPeak(nums, i)) {
                segTree.update(i, 1);
            }
        }

        List<Integer> result = new ArrayList<>();
        for (int[] query : queries) {
            if (query[0] == 1) {
                int l = query[1];
                int r = query[2];
                if (r - l + 1 < 3) {
                    result.add(0);
                } else {
                    result.add(segTree.query(l + 1, r - 1));
                }
            } else {
                int index = query[1];
                int value = query[2];
                nums[index] = value;

                for (int i = Math.max(1, index - 1); i <= Math.min(n - 2, index + 1); i++) {
                    if (isPeak(nums, i)) {
                        segTree.update(i, 1);
                    } else {
                        segTree.update(i, 0);
                    }
                }
            }
        }
        return result;          
    }
}
