// Source: https://leetcode.com/problems/maximum-number-of-groups-with-increasing-length/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array usageLimits of length n.
//
// Your task is to create groups using numbers from 0 to n - 1, ensuring that each number, i, is used no more than usageLimits[i] times in total across all groups. You must also satisfy the following conditions:
//
//
// 	Each group must consist of distinct numbers, meaning that no duplicate numbers are allowed within a single group.
// 	Each group (except the first one) must have a length strictly greater than the previous group.
//
//
// Return an integer denoting the maximum number of groups you can create while satisfying these conditions.
//
// Example:
// Input: usageLimits = [1,2,5]
// Output: 3
// Explanation: In this example, we can use 0 at most once, 1 at most twice, and 2 at most five times.
// One way of creating the maximum number of groups while satisfying the conditions is: 
// Group 1 contains the number [2].
// Group 2 contains the numbers [1,2].
// Group 3 contains the numbers [0,1,2]. 
// It can be shown that the maximum number of groups is 3. 
// So, the output is 3.
//
// Constraints:
// 1 <= usageLimits.length <= 105
// 	1 <= usageLimits[i] <= 109
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxIncreasingGroups(List<Integer> usageLimits) {
        // Sort the usage limits to try to form groups in increasing order
        Collections.sort(usageLimits);

        int groups = 0; // Number of groups formed
        int currentGroupSize = 0; // Size of the current group being formed

        for (int limit : usageLimits) {
            // If the current limit can accommodate the next group size
            if (limit > currentGroupSize) {
                groups++; // Form a new group
                currentGroupSize++; // Increase the size for the next group
            }
        }

        return groups; // Return the total number of groups formed          
    }
}
