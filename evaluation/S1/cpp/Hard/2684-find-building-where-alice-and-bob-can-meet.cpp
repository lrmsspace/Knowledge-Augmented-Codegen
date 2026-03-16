// Source: https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array heights of positive integers, where heights[i] represents the height of the ith building.
//
// If a person is in building i, they can move to any other building j if and only if i < j and heights[i] < heights[j].
//
// You are also given another array queries where queries[i] = [ai, bi]. On the ith query, Alice is in building ai while Bob is in building bi.
//
// Return an array ans where ans[i] is the index of the leftmost building where Alice and Bob can meet on the ith query. If Alice and Bob cannot move to a common building on query i, set ans[i] to -1.
//
// Example:
// Input: heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
// Output: [2,5,-1,5,2]
// Explanation: In the first query, Alice and Bob can move to building 2 since heights[0] < heights[2] and heights[1] < heights[2]. 
// In the second query, Alice and Bob can move to building 5 since heights[0] < heights[5] and heights[3] < heights[5]. 
// In the third query, Alice cannot meet Bob since Alice cannot move to any other building.
// In the fourth query, Alice and Bob can move to building 5 since heights[3] < heights[5] and heights[4] < heights[5].
// In the fifth query, Alice and Bob are already in the same building.  
// For ans[i] != -1, It can be shown that ans[i] is the leftmost building where Alice and Bob can meet.
// For ans[i] == -1, It can be shown that there is no building where Alice and Bob can meet.
//
// Constraints:
// 1 <= heights.length <= 5 * 104
// 	1 <= heights[i] <= 109
// 	1 <= queries.length <= 5 * 104
// 	queries[i] = [ai, bi]
// 	0 <= ai, bi <= heights.length - 1
//
// Helpful references (internal KB):
// - Range Minimum Query (array, ds, divide-and-conquer)
//   • When to use: Use when you need to find the minimum element within specified ranges of an array efficiently, especially for many queries after initial setup.
//   • Idea: A Range Minimum Query (RMQ) problem asks to find the minimum value in a specified range [L, R] of an array. It can be solved with various data structures, often achieving O(1) or O(log N) query time after O(N log N) or O(N) precomputation.
//   • Invariants: For any query range [L, R], the returned value is the minimum of elements A[i] where L <= i <= R.; The precomputed data structure correctly stores minimums for all relevant sub-intervals.
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) precomputation.; For dynamic arrays (with updates), Segment Tree provides O(log N) query and update times.
//   • Pitfalls: Incorrectly handling edge cases for range boundaries (L, R).; High memory usage for Sparse Table if N is very large (N log N space).
// - Check if point belongs to the convex pol (geometry, array, binary-search)
//   • When to use: This algorithm is used to efficiently determine if a given query point lies inside or on the boundary of a convex polygon, especially when many queries are performed on the same polygon.
//   • Idea: The core idea is to decompose the convex polygon into triangles originating from a reference vertex. Binary search is then used to find the specific triangle that could contain the query point, followed by a point-in-triangle check.
//   • Invariants: The reference point p_0 is the lexicographically smallest vertex of the polygon.; All polygon vertices p_1, ..., p_n are ordered counter-clockwise by polar angle around p_0.
//   • Tips: Choose a consistent reference point, typically the lexicographically smallest vertex, to simplify angular sorting.; Ensure polygon vertices are ordered (e.g., counter-clockwise) relative to the reference point for correct binary search behavior.
//   • Pitfalls: Floating point precision errors can lead to incorrect results for collinear points or boundary checks; prefer integer arithmetic with cross products.; Incorrectly handling boundary conditions (points exactly on an edge or vertex) can lead to false negatives or positives.
// - Sqrt Tree (array, tree, divide-and-conquer, recursion, prefix-sum)
//   • When to use: When performing associative range queries on an array, especially when O(1) query time is critical and O(N log log N) preprocessing is acceptable.
//   • Idea: The Sqrt Tree is a data structure that answers associative range queries on an array in O(1) time after O(N log log N) preprocessing. It achieves this by recursively applying sqrt decomposition, precomputing block-wise prefix/suffix operations and inter-block results.
//   • Invariants: The `prefixOp` array for any block `k` stores the associative sum from the block's start to each element within it.; The `suffixOp` array for any block `k` stores the associative sum from each element within it to the block's end.
//   • Tips: Ensure the operation is strictly associative for correctness.; Carefully handle block boundaries and partial blocks during query processing.
//   • Pitfalls: Using non-associative operations will yield incorrect results.; High memory usage for the 'between' array if not optimized or if N is very large.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        int n = heights.size();
        int q = queries.size();
        vector<int> res(q, -1);

        // Preprocess next greater elements to the right
        vector<int> nextGreater(n, n);
        stack<int> st;
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && heights[st.top()] <= heights[i]) {
                st.pop();
            }
            if (!st.empty()) {
                nextGreater[i] = st.top();
            }
            st.push(i);
        }

        // For each query, find the leftmost building where Alice and Bob can meet
        for (int i = 0; i < q; ++i) {
            int a = queries[i][0];
            int b = queries[i][1];
            if (a == b) {
                res[i] = a;
                continue;
            }
            int left = min(a, b);
            int right = max(a, b);
            int meetBuilding = -1;
            for (int j = left; j < right; ++j) {
                if (nextGreater[j] <= right) {
                    meetBuilding = nextGreater[j];
                    break;
                }
            }
            res[i] = meetBuilding;
        }

        return res;         
    }
};
