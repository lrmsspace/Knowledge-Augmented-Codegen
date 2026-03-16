// Source: https://leetcode.com/problems/minimum-interval-to-include-each-query/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals, where intervals[i] = [lefti, righti] describes the ith interval starting at lefti and ending at righti (inclusive). The size of an interval is defined as the number of integers it contains, or more formally righti - lefti + 1.
//
// You are also given an integer array queries. The answer to the jth query is the size of the smallest interval i such that lefti <= queries[j] <= righti. If no such interval exists, the answer is -1.
//
// Return an array containing the answers to the queries.
//
// Example:
// Input: intervals = [[1,4],[2,4],[3,6],[4,4]], queries = [2,3,4,5]
// Output: [3,3,1,4]
// Explanation: The queries are processed as follows:
// - Query = 2: The interval [2,4] is the smallest interval containing 2. The answer is 4 - 2 + 1 = 3.
// - Query = 3: The interval [2,4] is the smallest interval containing 3. The answer is 4 - 2 + 1 = 3.
// - Query = 4: The interval [4,4] is the smallest interval containing 4. The answer is 4 - 4 + 1 = 1.
// - Query = 5: The interval [3,6] is the smallest interval containing 5. The answer is 6 - 3 + 1 = 4.
//
// Constraints:
// 1 <= intervals.length <= 105
// 	1 <= queries.length <= 105
// 	intervals[i].length == 2
// 	1 <= lefti <= righti <= 107
// 	1 <= queries[j] <= 107
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Priority Queues (array, heap, heap-select)
//   • When to use: Use when you need to efficiently retrieve the highest or lowest priority item from a dynamic collection. It's ideal for scenarios requiring frequent insertions and extractions of extreme values without full sorting.
//   • Idea: A Priority Queue is an abstract data type that provides efficient retrieval of the maximum or minimum element. It is typically implemented using a binary heap, which stores elements in an array representing a complete binary tree, maintaining the heap-ordered property for O(log N) insertion and deletion.
//   • Invariants: For a max-heap, every parent node's key is greater than or equal to its children's keys.; The heap structure is always a complete binary tree, represented contiguously in an array.
//   • Tips: Represent the complete binary tree using an array, often 1-indexed for simpler parent/child calculations.; Use 'swim' (bottom-up reheapify) after insertion to restore heap order.
//   • Pitfalls: Forgetting to handle 0-indexed vs 1-indexed array representations correctly (parent/child formulas differ).; Violating the heap-ordered property during updates or custom operations.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int n = intervals.size();
        int m = queries.size();
        vector<pair<int, int>> qs(m);
        for (int i = 0; i < m; ++i) {
            qs[i] = {queries[i], i};
        }
        sort(qs.begin(), qs.end());
        sort(intervals.begin(), intervals.end());

        vector<int> res(m, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

        int idx = 0;
        for (int i = 0; i < m; ++i) {
            int q = qs[i].first;
            while (idx < n && intervals[idx][0] <= q) {
                int len = intervals[idx][1] - intervals[idx][0] + 1;
                minHeap.push({len, intervals[idx][1]});
                ++idx;
            }
            while (!minHeap.empty() && minHeap.top().second < q) {
                minHeap.pop();
            }
            if (!minHeap.empty()) {
                res[qs[i].second] = minHeap.top().first;
            }
        }

        return res;         
    }
};
