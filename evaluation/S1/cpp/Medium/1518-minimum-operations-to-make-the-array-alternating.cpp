// Source: https://leetcode.com/problems/minimum-operations-to-make-the-array-alternating/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisting of n positive integers.
//
// The array nums is called alternating if:
//
//
// 	nums[i - 2] == nums[i], where 2 <= i <= n - 1.
// 	nums[i - 1] != nums[i], where 1 <= i <= n - 1.
//
//
// In one operation, you can choose an index i and change nums[i] into any positive integer.
//
// Return the minimum number of operations required to make the array alternating.
//
// Example:
// Input: nums = [3,1,3,2,4,3]
// Output: 3
// Explanation:
// One way to make the array alternating is by converting it to [3,1,3,1,3,1].
// The number of operations required in this case is 3.
// It can be proven that it is not possible to make the array alternating in less than 3 operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        // Frequency maps for even and odd indices
        unordered_map<int, int> freqEven, freqOdd;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                freqEven[nums[i]]++;
            } else {
                freqOdd[nums[i]]++;
            }
        }

        // Find top two frequencies for even indices
        pair<int, int> topEven = {0, 0}; // {value, frequency}
        pair<int, int> secondEven = {0, 0};
        for (const auto& [num, count] : freqEven) {
            if (count > topEven.second) {
                secondEven = topEven;
                topEven = {num, count};
            } else if (count > secondEven.second) {
                secondEven = {num, count};
            }
        }

        // Find top two frequencies for odd indices
        pair<int, int> topOdd = {0, 0}; // {value, frequency}
        pair<int, int> secondOdd = {0, 0};
        for (const auto& [num, count] : freqOdd) {
            if (count > topOdd.second) {
                secondOdd = topOdd;
                topOdd = {num, count};
            } else if (count > secondOdd.second) {
                secondOdd = {num, count};
            }
        }

        // Calculate minimum operations
        if (topEven.first != topOdd.first) {
            return n - (topEven.second + topOdd.second);
        } else {
            return min(n - (topEven.second + secondOdd.second),
                       n - (secondEven.second + topOdd.second));
        }
    }
};
