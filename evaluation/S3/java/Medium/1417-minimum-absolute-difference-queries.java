// Source: https://leetcode.com/problems/minimum-absolute-difference-queries/   |   Difficulty: Medium
//
// Problem Description:
// The minimum absolute difference of an array a is defined as the minimum value of |a[i] - a[j]|, where 0 <= i < j < a.length and a[i] != a[j]. If all elements of a are the same, the minimum absolute difference is -1.
//
//
// 	For example, the minimum absolute difference of the array [5,2,3,7,2] is |2 - 3| = 1. Note that it is not 0 because a[i] and a[j] must be different.
//
//
// You are given an integer array nums and the array queries where queries[i] = [li, ri]. For each query i, compute the minimum absolute difference of the subarray nums[li...ri] containing the elements of nums between the 0-based indices li and ri (inclusive).
//
// Return an array ans where ans[i] is the answer to the ith query.
//
// A subarray is a contiguous sequence of elements in an array.
//
// The value of |x| is defined as:
//
//
// 	x if x >= 0.
// 	-x if x < 0.
//
// Example:
// Input: nums = [1,3,4,8], queries = [[0,1],[1,2],[2,3],[0,3]]
// Output: [2,1,4,1]
// Explanation: The queries are processed as follows:
// - queries[0] = [0,1]: The subarray is [1,3] and the minimum absolute difference is |1-3| = 2.
// - queries[1] = [1,2]: The subarray is [3,4] and the minimum absolute difference is |3-4| = 1.
// - queries[2] = [2,3]: The subarray is [4,8] and the minimum absolute difference is |4-8| = 4.
// - queries[3] = [0,3]: The subarray is [1,3,4,8] and the minimum absolute difference is |3-4| = 1.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= 100
// 	1 <= queries.length <= 2 * 104
// 	0 <= li < ri < nums.length
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - Sqrt Decomposition (array, enumeration, prefix-sum)
//   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
//   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
//   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
//   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] minDifference(int[] nums, int[][] queries) {
        int n = nums.length;
        int m = queries.length;
        int[] ans = new int[m];
        int[][] prefixCount = new int[101][n + 1];

        // Build prefix count for each number from 1 to 100
        for (int i = 0; i < n; i++) {
            for (int num = 1; num <= 100; num++) {
                prefixCount[num][i + 1] = prefixCount[num][i];
            }
            prefixCount[nums[i]][i + 1]++;
        }

        // Process each query
        for (int i = 0; i < m; i++) {
            int l = queries[i][0];
            int r = queries[i][1];
            ans[i] = findMinDifference(prefixCount, l, r);
        }

        return ans;         
    }
}
