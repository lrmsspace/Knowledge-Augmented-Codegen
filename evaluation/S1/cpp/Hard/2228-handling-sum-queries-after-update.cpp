// Source: https://leetcode.com/problems/handling-sum-queries-after-update/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed arrays nums1 and nums2 and a 2D array queries of queries. There are three types of queries:
//
//
// 	For a query of type 1, queries[i] = [1, l, r]. Flip the values from 0 to 1 and from 1 to 0 in nums1 from index l to index r. Both l and r are 0-indexed.
// 	For a query of type 2, queries[i] = [2, p, 0]. For every index 0 <= i < n, set nums2[i] = nums2[i] + nums1[i] * p.
// 	For a query of type 3, queries[i] = [3, 0, 0]. Find the sum of the elements in nums2.
//
//
// Return an array containing all the answers to the third type queries.
//
// Example:
// Input: nums1 = [1,0,1], nums2 = [0,0,0], queries = [[1,1,1],[2,1,0],[3,0,0]]
// Output: [3]
// Explanation: After the first query nums1 becomes [1,1,1]. After the second query, nums2 becomes [1,1,1], so the answer to the third query is 3. Thus, [3] is returned.
//
// Constraints:
// 1 <= nums1.length,nums2.length <= 105
// 	nums1.length = nums2.length
// 	1 <= queries.length <= 105
// 	queries[i].length = 3
// 	0 <= l <= r <= nums1.length - 1
// 	0 <= p <= 106
// 	0 <= nums1[i] <= 1
// 	0 <= nums2[i] <= 109
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
//   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
//   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
//   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        long long sumNums2 = 0;
        for (int num : nums2) {
            sumNums2 += num;
        }

        int n = nums1.size();
        int size = 1;
        while (size < n) size <<= 1;

        vector<int> segTree(2 * size, 0);
        vector<int> lazy(2 * size, 0);

        auto apply = [&](int node, int nodeLeft, int nodeRight) {
            segTree[node] = (nodeRight - nodeLeft + 1) - segTree[node];
            if (nodeLeft != nodeRight) {
                lazy[node * 2] ^= 1;
                lazy[node * 2 + 1] ^= 1;
            }
            lazy[node] = 0;
        };

        function<void(int, int, int, int, int)> updateRange = [&](int node, int nodeLeft, int nodeRight, int left, int right) {
            if (lazy[node]) {
                apply(node, nodeLeft, nodeRight);
            }
            if (nodeRight < left || nodeLeft > right) {
                return;
            }
            if (left <= nodeLeft && nodeRight <= right) {
                apply(node, nodeLeft, nodeRight);
                return;
            }
            int mid = (nodeLeft + nodeRight) / 2;
            updateRange(node * 2, nodeLeft, mid, left, right);
            updateRange(node * 2 + 1, mid + 1, nodeRight, left, right);
            segTree[node] = segTree[node * 2] + segTree[node * 2 + 1];
        };

        vector<long long> result;
        for (const auto& query : queries) {
            if (query[0] == 1) {
                updateRange(1, 0, size - 1, query[1], query[2]);
            } else if (query[0] == 2) {
                long long p = query[1];
                sumNums2 += static_cast<long long>(segTree[1]) * p;
            } else if (query[0] == 3) {
                result.push_back(sumNums2);
            }
        }

        return result;          
    }
};
