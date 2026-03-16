// Source: https://leetcode.com/problems/block-placement-queries/   |   Difficulty: Hard
//
// Problem Description:
// There exists an infinite number line, with its origin at 0 and extending towards the positive x-axis.
//
// You are given a 2D array queries, which contains two types of queries:
//
//
// 	For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin. It is guaranteed that there is no obstacle at distance x when the query is asked.
// 	For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range [0, x]. A block cannot be placed if it intersects with any obstacle, but it may touch it. Note that you do not actually place the block. Queries are separate.
//
//
// Return a boolean array results, where results[i] is true if you can place the block specified in the ith query of type 2, and false otherwise.
//
// Example:
// Input: queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]
//
// Output: [false,true,true]
//
// Explanation:
//
//
//
// For query 0, place an obstacle at x = 2. A block of size at most 2 can be placed before x = 3.
//
// Constraints:
// 1 <= queries.length <= 15 * 104
// 	2 <= queries[i].length <= 3
// 	1 <= queries[i][0] <= 2
// 	1 <= x, sz <= min(5 * 104, 3 * queries.length)
// 	The input is generated such that for queries of type 1, no obstacle exists at distance x when the query is asked.
// 	The input is generated such that there is at least one query of type 2.
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
//   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
//   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
//   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
// - MEX (minimal excluded) of a sequence (ds, enumeration)
//   • When to use: Use when needing to efficiently find the smallest non-negative integer not present in a dynamic sequence or range, supporting both updates and queries in logarithmic time.
//   • Idea: This technique finds the Minimal Excluded (MEX) value in a sequence by maintaining counts of distinct elements in ranges using a specialized data structure, typically a segment tree. It supports both updates and queries in O(log N) time.
//   • Invariants: Each segment tree node accurately reflects the count of distinct numbers within its corresponding range.; If a range [L, R) contains R-L distinct numbers, then all integers from L to R-1 are present.
//   • Tips: Implement a segment tree where each node stores the count of distinct numbers in its range.; The binary search for MEX checks if a range [0, k) contains k distinct numbers to decide which child to traverse.
//   • Pitfalls: Incorrectly calculating distinct counts in segment tree nodes, especially after updates.; Off-by-one errors when comparing the number of distinct elements with the expected count for a full range.
// - Point location in O(logn) (geometry, ds, simulation)
//   • When to use: Use when needing to efficiently determine which region (face or edge) of a planar subdivision a given query point lies within, especially for multiple online queries.
//   • Idea: This algorithm preprocesses a planar subdivision to answer point location queries in logarithmic time. It typically involves building a specialized data structure, possibly persistent, to quickly identify the containing face or edge for any given point.
//   • Invariants: The search process always maintains the invariant that the query point is within the current candidate region.; After each step, the search space for the point's location is reduced by a constant factor.
//   • Tips: Use a suitable geometric data structure like a trapezoidal map or persistent segment tree.; Carefully handle points lying exactly on edges or vertices.
//   • Pitfalls: Degenerate cases (vertical edges, collinear points) require careful handling.; Floating-point precision errors can lead to incorrect classifications.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        const int MAX_X = 50000;
        struct SegTree {
            int sizePow;
            vector<int> data;
        };

        auto seg_build = [](int n) -> SegTree {
            SegTree t;
            t.sizePow = 1;
            while (t.sizePow < n) t.sizePow <<= 1;
            t.data.assign(t.sizePow << 1, -1);
            return t;
        };

        auto seg_update = [&](SegTree& t, int idx, int val) {
            idx += t.sizePow;
            t.data[idx] = val;
            while (idx > 1) {
                idx >>= 1;
                t.data[idx] = max(t.data[idx << 1], t.data[(idx << 1) | 1]);
            }
        };

        auto seg_range_max = [&](const SegTree& t, int l, int r) -> int {
            if (l > r) return -1;
            l += t.sizePow;
            r += t.sizePow;
            int res = -1;
            while (l <= r) {
                if (l & 1) {
                    if (t.data[l] > res) res = t.data[l];
                    ++l;
                }
                if (!(r & 1)) {
                    if (t.data[r] > res) res = t.data[r];
                    --r;
                }
                l >>= 1;
                r >>= 1;
            }
            return res;
        };

        SegTree seg = seg_build(MAX_X + 1);
        vector<bool> results;

        for (const auto& query : queries) {
            if (query[0] == 1) {
                // Place obstacle
                seg_update(seg, query[1], query[1]);
            } else if (query[0] == 2) {
                // Check block placement
                int x = query[1];
                int sz = query[2];
                int maxObstacle = seg_range_max(seg, max(0, x - sz + 1), x);
                if (maxObstacle == -1 || maxObstacle < x - sz + 1) {
                    results.push_back(true);
                } else {
                    results.push_back(false);
                }
            }
        }

        return results;         
    }
};
