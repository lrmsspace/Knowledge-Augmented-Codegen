// Source: https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers called nums, you can perform any of the following operation while nums contains at least 2 elements:
//
//
// 	Choose the first two elements of nums and delete them.
// 	Choose the last two elements of nums and delete them.
// 	Choose the first and the last elements of nums and delete them.
//
//
// The score of the operation is the sum of the deleted elements.
//
// Your task is to find the maximum number of operations that can be performed, such that all operations have the same score.
//
// Return the maximum number of operations possible that satisfy the condition mentioned above.
//
// Example:
// Input: nums = [3,2,1,2,3,4]
// Output: 3
// Explanation: We perform the following operations:
// - Delete the first two elements, with score 3 + 2 = 5, nums = [1,2,3,4].
// - Delete the first and the last elements, with score 1 + 4 = 5, nums = [2,3].
// - Delete the first and the last elements, with score 2 + 3 = 5, nums = [].
// We are unable to perform any more operations as nums is empty.
//
// Constraints:
// 2 <= nums.length <= 2000
// 	1 <= nums[i] <= 1000
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: When you need to calculate the area of a simple polygon given its vertices in sequential order. It efficiently handles both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing the signed areas of trapezoids or triangles formed by its edges and a reference point/axis. It achieves O(N) time complexity.
//   • Invariants: The sum accumulates the signed area contribution of processed edges.; The current vertex and the next vertex define an edge of the polygon.
//   • Tips: Ensure vertices are provided in sequential order (clockwise or counter-clockwise).; The absolute value of the final result is the polygon's area.
//   • Pitfalls: Supplying vertices in a non-sequential or arbitrary order will yield an incorrect area.; Applying the formula to self-intersecting polygons will not give the true geometric area.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxOperations(int* nums, int numsSize) {
    int max_score = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > max_score) {
            max_score = nums[i];
        }
    }
    max_score *= 2;

    int count[max_score + 1];
    for (int i = 0; i <= max_score; ++i) {
        count[i] = 0;
    }
    for (int i = 0; i < numsSize; ++i) {
        ++count[nums[i]];
    }

    int max_operations = 0;
    for (int score = 2; score <= max_score; ++score) {
        int operations = 0;
        for (int num = 1; num < score && num <= max_score; ++num) {
            int complement = score - num;
            if (complement > max_score) {
                continue;
            }
            if (num == complement) {
                operations += count[num] / 2;
            } else {
                operations += count[num] < count[complement] ? count[num] : count[complement];
            }
        }
        if (operations > max_operations) {
            max_operations = operations;
        }
    }

    return max_operations;      
}
