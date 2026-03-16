// Source: https://leetcode.com/problems/rank-transform-of-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers arr, replace each element with its rank.
//
// The rank represents how large the element is. The rank has the following rules:
//
//
// 	Rank is an integer starting from 1.
// 	The larger the element, the larger the rank. If two elements are equal, their rank must be the same.
// 	Rank should be as small as possible.
//
// Example:
// Input: arr = [40,10,20,30]
// Output: [4,1,2,3]
// Explanation: 40 is the largest element. 10 is the smallest. 20 is the second smallest. 30 is the third smallest.
//
// Constraints:
// 0 <= arr.length <= 105
// 	-109 <= arr[i] <= 109
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Range Minimum Query (array, bitset, bit-fenwick)
//   • When to use: When you need to efficiently query the minimum value within a range and perform point updates on an array. It's suitable for scenarios requiring logarithmic time complexity for both operations.
//   • Idea: A Fenwick tree (BIT) can be adapted to answer Range Minimum Queries and perform point updates in O(log N) time. It achieves this by storing prefix minimums in a tree-like structure, allowing efficient aggregation.
//   • Invariants: Each node `tree[i]` stores the minimum of a specific range `[i - (i & -i) + 1, i]`.; An update to `arr[idx]` correctly propagates the new minimum to all relevant `tree` nodes.
//   • Tips: Adapt standard BIT operations for minimums instead of sums.; Use `min(current_value, new_value)` for updates and queries.
//   • Pitfalls: Standard BIT operations are for sums; direct application for minimums is incorrect.; Querying a range `[L, R]` for minimum is not a simple `query(R) - query(L-1)`.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] arrayRankTransform(int[] arr) {
        int n = arr.length;
        int[] sorted = arr.clone();
        Arrays.sort(sorted);
        Map<Integer, Integer> rankMap = new HashMap<>();
        int rank = 1;
        for (int num : sorted) {
            if (!rankMap.containsKey(num)) {
                rankMap.put(num, rank++);
            }
        }
        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            result[i] = rankMap.get(arr[i]);
        }
        return result;          
    }
}
