// Source: https://leetcode.com/problems/minimize-the-maximum-adjacent-element-difference/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums. Some values in nums are missing and are denoted by -1.
//
// You must choose a pair of positive integers (x, y) exactly once and replace each missing element with either x or y.
//
// You need to minimize the maximum absolute difference between adjacent elements of nums after replacements.
//
// Return the minimum possible difference.
//
// Example:
// Input: nums = [1,2,-1,10,8]
//
// Output: 4
//
// Explanation:
//
// By choosing the pair as (6, 7), nums can be changed to [1, 2, 6, 10, 8].
//
// The absolute differences between adjacent elements are:
//
//
// 	|1 - 2| == 1
// 	|2 - 6| == 4
// 	|6 - 10| == 4
// 	|10 - 8| == 2
//
// Constraints:
// 2 <= nums.length <= 105
// 	nums[i] is either -1 or in the range [1, 109].
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = (int)nums.size();
        int maxVal = -1;
        int minVal = 1000000001;

        for (int i = 0; i < n; ++i) {
            if (nums[i] != -1) {
                if (nums[i] > maxVal) {
                    maxVal = nums[i];
                }
                if (nums[i] < minVal) {
                    minVal = nums[i];
                }
            }
        }

        if (maxVal == -1) {
            return 0;
        }

        int ans = maxVal - minVal;
        if (ans <= 1) {
            return ans;
        }

        return (ans + 1) / 2;           
    }
};
