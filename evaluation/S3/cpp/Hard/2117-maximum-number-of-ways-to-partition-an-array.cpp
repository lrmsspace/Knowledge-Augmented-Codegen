// Source: https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n. The number of ways to partition nums is the number of pivot indices that satisfy both conditions:
//
//
// 	1 <= pivot < n
// 	nums[0] + nums[1] + ... + nums[pivot - 1] == nums[pivot] + nums[pivot + 1] + ... + nums[n - 1]
//
//
// You are also given an integer k. You can choose to change the value of one element of nums to k, or to leave the array unchanged.
//
// Return the maximum possible number of ways to partition nums to satisfy both conditions after changing at most one element.
//
// Example:
// Input: nums = [2,-1,2], k = 3
// Output: 1
// Explanation: One optimal approach is to change nums[0] to k. The array becomes [3,-1,2].
// There is one way to partition the array:
// - For pivot = 2, we have the partition [3,-1 | 2]: 3 + -1 == 2.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 105
// 	-105 <= k, nums[i] <= 105
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
//   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
//   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
//   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
// - Sqrt Decomposition (array, enumeration, prefix-sum)
//   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
//   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
//   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
//   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int waysToPartition(vector<int>& nums, int k) {
        int n = (int)nums.size();
        vector<long long> prefixSum(n + 1, 0);
        unordered_map<long long, int> leftCount;
        unordered_map<long long, int> rightCount;

        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        for (int i = 1; i < n; ++i) {
            rightCount[prefixSum[i]]++;
        }

        int maxWays = rightCount[0];
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                leftCount[prefixSum[i]]++;
                rightCount[prefixSum[i]]--;
            }

            long long target = prefixSum[i] - k;
            int currentWays = leftCount[target] + rightCount[target];
            maxWays = max(maxWays, currentWays);
        }

        return maxWays;        
    }
};
