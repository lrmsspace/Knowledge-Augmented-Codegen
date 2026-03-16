// Source: https://leetcode.com/problems/minimum-cost-to-make-array-equal/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed arrays nums and cost consisting each of n positive integers.
//
// You can do the following operation any number of times:
//
//
// 	Increase or decrease any element of the array nums by 1.
//
//
// The cost of doing one operation on the ith element is cost[i].
//
// Return the minimum total cost such that all the elements of the array nums become equal.
//
// Example:
// Input: nums = [1,3,5,2], cost = [2,3,1,14]
// Output: 8
// Explanation: We can make all the elements equal to 2 in the following way:
// - Increase the 0th element one time. The cost is 2.
// - Decrease the 1st element one time. The cost is 3.
// - Decrease the 2nd element three times. The cost is 1 + 1 + 1 = 3.
// The total cost is 2 + 3 + 3 = 8.
// It can be shown that we cannot make the array equal with a smaller cost.
//
// Constraints:
// n == nums.length == cost.length
// 	1 <= n <= 105
// 	1 <= nums[i], cost[i] <= 106
// 	Test cases are generated in a way that the output doesn't exceed 253-1
//
// Helpful references (internal KB):
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
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
    long long minCost(vector<int>& nums, vector<int>& cost) {
        int n = (int)nums.size();
        vector<pair<int, int>> pairs(n);
        for (int i = 0; i < n; ++i) {
            pairs[i] = {nums[i], cost[i]};
        }
        sort(pairs.begin(), pairs.end());

        long long totalCost = 0;
        for (const auto& p : pairs) {
            totalCost += p.second;
        }

        long long halfCost = (totalCost + 1) / 2;
        long long cumulativeCost = 0;
        int targetValue = 0;
        for (const auto& p : pairs) {
            cumulativeCost += p.second;
            if (cumulativeCost >= halfCost) {
                targetValue = p.first;
                break;
            }
        }

        long long result = 0;
        for (const auto& p : pairs) {
            result += (long long)abs(p.first - targetValue) * p.second;
        }
        return result;          
    }
};
