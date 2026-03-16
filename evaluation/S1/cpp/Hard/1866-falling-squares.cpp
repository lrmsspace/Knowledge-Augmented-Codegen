// Source: https://leetcode.com/problems/falling-squares/   |   Difficulty: Hard
//
// Problem Description:
// There are several squares being dropped onto the X-axis of a 2D plane.
//
// You are given a 2D integer array positions where positions[i] = [lefti, sideLengthi] represents the ith square with a side length of sideLengthi that is dropped with its left edge aligned with X-coordinate lefti.
//
// Each square is dropped one at a time from a height above any landed squares. It then falls downward (negative Y direction) until it either lands on the top side of another square or on the X-axis. A square brushing the left/right side of another square does not count as landing on it. Once it lands, it freezes in place and cannot be moved.
//
// After each square is dropped, you must record the height of the current tallest stack of squares.
//
// Return an integer array ans where ans[i] represents the height described above after dropping the ith square.
//
// Example:
// Input: positions = [[1,2],[2,3],[6,1]]
// Output: [2,5,5]
// Explanation:
// After the first drop, the tallest stack is square 1 with a height of 2.
// After the second drop, the tallest stack is squares 1 and 2 with a height of 5.
// After the third drop, the tallest stack is still squares 1 and 2 with a height of 5.
// Thus, we return an answer of [2, 5, 5].
//
// Constraints:
// 1 <= positions.length <= 1000
// 	1 <= lefti <= 108
// 	1 <= sideLengthi <= 106
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
//   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
//   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
//   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
// - Minimum stack / Minimum queue (stack, simulation)
//   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
//   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
//   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
//   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
//   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
//   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
//   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
//   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
//   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<int> xs;
        for (const auto& pos : positions) {
            xs.push_back(pos[0]);
            xs.push_back(pos[0] + pos[1] - 1);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        
        int m = xs.size();
        vector<int> segTree(4 * m, 0);
        vector<int> lazy(4 * m, 0);
        
        function<void(int, int, int, int, int, int)> update = [&](int node, int start, int end, int l, int r, int val) {
            if (lazy[node] != 0) {
                segTree[node] = max(segTree[node], lazy[node]);
                if (start != end) {
                    lazy[node * 2 + 1] = max(lazy[node * 2 + 1], lazy[node]);
                    lazy[node * 2 + 2] = max(lazy[node * 2 + 2], lazy[node]);
                }
                lazy[node] = 0;
            }
            if (start > end || start > r || end < l) return;
            if (start >= l && end <= r) {
                segTree[node] = max(segTree[node], val);
                if (start != end) {
                    lazy[node * 2 + 1] = max(lazy[node * 2 + 1], val);
                    lazy[node * 2 + 2] = max(lazy[node * 2 + 2], val);
                }
                return;
            }
            int mid = (start + end) / 2;
            update(node * 2 + 1, start, mid, l, r, val);
            update(node * 2 + 2, mid + 1, end, l, r, val);
            segTree[node] = max(segTree[node * 2 + 1], segTree[node * 2 + 2]);
        };
        
        function<int(int, int, int, int, int)> query = [&](int node, int start, int end, int l, int r) {
            if (start > end || start > r || end < l) return 0;
            if (lazy[node] != 0) {
                segTree[node] = max(segTree[node], lazy[node]);
                if (start != end) {
                    lazy[node * 2 + 1] = max(lazy[node * 2 + 1], lazy[node]);
                    lazy[node * 2 + 2] = max(lazy[node * 2 + 2], lazy[node]);
                }
                lazy[node] = 0;
            }
            if (start >= l && end <= r) {
                return segTree[node];
            }
            int mid = (start + end) / 2;
            int leftQuery = query(node * 2 + 1, start, mid, l, r);
            int rightQuery = query(node * 2 + 2, mid + 1, end, l, r);
            return max(leftQuery, rightQuery);
        };
        vector<int> result;
        int currentMax = 0;
        for (const auto& pos : positions) {
            int left = pos[0];
            int right = pos[0] + pos[1] - 1;
            int l = lower_bound(xs.begin(), xs.end(), left) - xs.begin();
            int r = lower_bound(xs.begin(), xs.end(), right) - xs.begin();
            int height = query(0, 0, m - 1, l, r) + pos[1];
            update(0, 0, m - 1, l, r, height);
            currentMax = max(currentMax, height);
            result.push_back(currentMax);
        }
        return result;
    }
};
