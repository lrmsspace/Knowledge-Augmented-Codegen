// Source: https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums consisting of integers. You are also given a 2D array queries, where queries[i] = [posi, xi].
//
// For query i, we first set nums[posi] equal to xi, then we calculate the answer to query i which is the maximum sum of a subsequence of nums where no two adjacent elements are selected.
//
// Return the sum of the answers to all queries.
//
// Since the final answer may be very large, return it modulo 109 + 7.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [3,5,9], queries = [[1,-2],[0,-3]]
//
// Output: 21
//
// Explanation:
// After the 1st query, nums = [3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 3 + 9 = 12.
// After the 2nd query, nums = [-3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 9.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-105 <= nums[i] <= 105
// 	1 <= queries.length <= 5 * 104
// 	queries[i] == [posi, xi]
// 	0 <= posi <= nums.length - 1
// 	-105 <= xi <= 105
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, divide-and-conquer)
//   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
//   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
//   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
//   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
// - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
//   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
//   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
//   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
// - Segment Tree (tree, array, segment-tree)
//   • When to use: Use when you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in logarithmic time.
//   • Idea: A Segment Tree is a tree-based data structure that stores information about array intervals, enabling efficient O(log n) range queries and point/range updates.
//   • Invariants: Each node in the segment tree represents a contiguous subsegment of the original array.; The value stored in a non-leaf node is an aggregation of the values from its direct children.
//   • Tips: Build the tree recursively, dividing the array into halves.; Use lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors when defining segment boundaries or array indices.; Forgetting to push down lazy tags before querying or updating children nodes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        const int MOD = 1000000007; 
        int n = nums.size();
        vector<long long> dp(n);
        dp[0] = max(0, (long long)nums[0]);
        for (int i = 1; i < n; ++i) {
            dp[i] = max(dp[i - 1], (i > 1 ? dp[i - 2] : 0) + nums[i]);
        }
        long long result = 0;
        for (const auto& query : queries) {
            int pos = query[0];
            int val = query[1];
            long long oldVal = nums[pos];
            nums[pos] = val;
            if (pos == 0) {
                dp[0] = max(0LL, (long long)nums[0]);
            } else if (pos == 1) {
                dp[1] = max(dp[0], (long long)nums[1]);
            } else {
                dp[pos] = max(dp[pos - 1], dp[pos - 2] + nums[pos]);
            }
            for (int i = pos + 1; i < n; ++i) {
                dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
            }
            result = (result + dp[n - 1]) % MOD;
            nums[pos] = oldVal; // revert the change for the next query
        }
        return result;
    }
};
