// Source: https://leetcode.com/problems/maximum-sum-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays nums1 and nums2, each of length n, and a 1-indexed 2D array queries where queries[i] = [xi, yi].
//
// For the ith query, find the maximum value of nums1[j] + nums2[j] among all indices j (0 <= j < n), where nums1[j] >= xi and nums2[j] >= yi, or -1 if there is no j satisfying the constraints.
//
// Return an array answer where answer[i] is the answer to the ith query.
//
// Example:
// Input: nums1 = [4,3,1,2], nums2 = [2,4,9,5], queries = [[4,1],[1,3],[2,5]]
// Output: [6,10,7]
// Explanation: 
// For the 1st query xi = 4 and yi = 1, we can select index j = 0 since nums1[j] >= 4 and nums2[j] >= 1. The sum nums1[j] + nums2[j] is 6, and we can show that 6 is the maximum we can obtain.
//
// For the 2nd query xi = 1 and yi = 3, we can select index j = 2 since nums1[j] >= 1 and nums2[j] >= 3. The sum nums1[j] + nums2[j] is 10, and we can show that 10 is the maximum we can obtain. 
//
// For the 3rd query xi = 2 and yi = 5, we can select index j = 3 since nums1[j] >= 2 and nums2[j] >= 5. The sum nums1[j] + nums2[j] is 7, and we can show that 7 is the maximum we can obtain.
//
// Therefore, we return [6,10,7].
//
// Constraints:
// nums1.length == nums2.length 
// 	n == nums1.length 
// 	1 <= n <= 105
// 	1 <= nums1[i], nums2[i] <= 109 
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	xi == queries[i][1]
// 	yi == queries[i][2]
// 	1 <= xi, yi <= 109
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, divide-and-conquer)
//   • When to use: When you need to perform range queries (like sum, min, max) and point or range updates on an array efficiently, typically in O(log N) time.
//   • Idea: A tree-based data structure that stores information about array segments, allowing for efficient O(log N) range queries and point/range updates. It recursively divides the array into halves, with each node representing an interval.
//   • Invariants: Each node in the segment tree corresponds to a contiguous subsegment of the original array.; The value stored in a node is the aggregate result (e.g., sum, min) of its corresponding array subsegment.
//   • Tips: Use 1-based indexing for array and tree nodes to simplify parent/child calculations.; Implement lazy propagation for efficient range updates to avoid O(N) updates.
//   • Pitfalls: Off-by-one errors in segment boundaries or query ranges are common.; Forgetting to push down lazy updates before accessing children or returning a node's value.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Point location in O(logn) (geometry, ds, simulation)
//   • When to use: Use when needing to efficiently determine which region (face or edge) of a planar subdivision a given query point lies within, especially for multiple online queries.
//   • Idea: This algorithm preprocesses a planar subdivision to answer point location queries in logarithmic time. It typically involves building a specialized data structure, possibly persistent, to quickly identify the containing face or edge for any given point.
//   • Invariants: The search process always maintains the invariant that the query point is within the current candidate region.; After each step, the search space for the point's location is reduced by a constant factor.
//   • Tips: Use a suitable geometric data structure like a trapezoidal map or persistent segment tree.; Carefully handle points lying exactly on edges or vertices.
//   • Pitfalls: Degenerate cases (vertical edges, collinear points) require careful handling.; Floating-point precision errors can lead to incorrect classifications.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumSumQueries(int* nums1, int nums1Size, int* nums2, int nums2Size, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int n = nums1Size;
    int* result = (int*)malloc(queriesSize * sizeof(int));
    typedef struct {
        int x, y, index;
    } Query;
    Query* queryList = (Query*)malloc(queriesSize * sizeof(Query));
    for (int i = 0; i < queriesSize; i++) {
        queryList[i].x = queries[i][0];
        queryList[i].y = queries[i][1];
        queryList[i].index = i;
    }

    // Sort nums by nums1 descending, if tie by nums2 descending
    typedef struct {
        int num1, num2;
    } NumPair;
    NumPair* numPairs = (NumPair*)malloc(n * sizeof(NumPair));
    for (int i = 0; i < n; i++) {
        numPairs[i].num1 = nums1[i];
        numPairs[i].num2 = nums2[i];
    }
    qsort(numPairs, n, sizeof(NumPair), [](const void* a, const void* b) {
        NumPair* p1 = (NumPair*)a;
        NumPair* p2 = (NumPair*)b;
        if (p1->num1 != p2->num1) return p2->num1 - p1->num1;
        return p2->num2 - p1->num2;
    });

    // Sort queries by x descending, if tie by y descending
    qsort(queryList, queriesSize, sizeof(Query), [](const void* a, const void* b) {
        Query* q1 = (Query*)a;
        Query* q2 = (Query*)b;
        if (q1->x != q2->x) return q2->x - q1->x;
        return q2->y - q1->y;
    });

    // Segment Tree for max nums2 + nums1
    #define MAXN 100005
    int segTree[4 * MAXN];
    void segTreeUpdate(int node, int start, int end, int idx, int value) {
        if (start == end) {
            if (value > segTree[node]) {
                segTree[node] = value;
            }
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                segTreeUpdate(2 * node, start, mid, idx, value);
            } else {
                segTreeUpdate(2 * node + 1, mid + 1, end, idx, value);
            }
            segTree[node] = (segTree[2 * node] > segTree[2 * node + 1]) ? segTree[2 * node] : segTree[2 * node + 1];
        }
    }
    int segTreeQuery(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return -1;
        }
        if (l <= start && end <= r) {
            return segTree[node];
        }
        int mid = (start + end) / 2;
        int leftQuery = segTreeQuery(2 * node, start, mid, l, r);
        int rightQuery = segTreeQuery(2 * node + 1, mid + 1, end, l, r);
        return (leftQuery > rightQuery) ? leftQuery : rightQuery;
    }
    // Coordinate compression for nums2
    int* sortedNums2 = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        sortedNums2[i] = numPairs[i].num2;
    }
    qsort(sortedNums2, n, sizeof(int), [](const void* a, const void* b) {
        return (*(int*)a) - (*(int*)b);
    });
    int uniqueCount = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || sortedNums2[i] != sortedNums2[i - 1]) {
            sortedNums2[uniqueCount++] = sortedNums2[i];
        }
    }
    int getCompressedIndex(int value) {
        int left = 0, right = uniqueCount - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (sortedNums2[mid] == value) return mid + 1;
            else if (sortedNums2[mid] < value) left = mid + 1;
            else right = mid - 1;
        }
        return -1; // Should not happen
    }
    // Process queries
    int j = 0;
    for (int i = 0; i < queriesSize; i++) {
        int x = queryList[i].x;
        int y = queryList[i].y;
        while (j < n && numPairs[j].num1 >= x) {
            int compressedIdx = getCompressedIndex(numPairs[j].num2);
            segTreeUpdate(1, 1, uniqueCount, compressedIdx, numPairs[j].num1 + numPairs[j].num2);
            j++;
        }
        int compressedY = getCompressedIndex(y);
        if (compressedY == -1) {
            result[queryList[i].index] = -1;
        } else {
            int queryResult = segTreeQuery(1, 1, uniqueCount, compressedY, uniqueCount);
            result[queryList[i].index] = queryResult;
        }
    }
    free(numPairs);
    free(sortedNums2);
    free(queryList);
    return result;

}
