// Source: https://leetcode.com/problems/maximum-number-of-weeks-for-which-you-can-work/   |   Difficulty: Medium
//
// Problem Description:
// There are n projects numbered from 0 to n - 1. You are given an integer array milestones where each milestones[i] denotes the number of milestones the ith project has.
//
// You can work on the projects following these two rules:
//
//
// 	Every week, you will finish exactly one milestone of one project. You must work every week.
// 	You cannot work on two milestones from the same project for two consecutive weeks.
//
//
// Once all the milestones of all the projects are finished, or if the only milestones that you can work on will cause you to violate the above rules, you will stop working. Note that you may not be able to finish every project's milestones due to these constraints.
//
// Return the maximum number of weeks you would be able to work on the projects without violating the rules mentioned above.
//
// Example:
// Input: milestones = [1,2,3]
// Output: 6
// Explanation: One possible scenario is:
// ​​​​- During the 1st week, you will work on a milestone of project 0.
// - During the 2nd week, you will work on a milestone of project 2.
// - During the 3rd week, you will work on a milestone of project 1.
// - During the 4th week, you will work on a milestone of project 2.
// - During the 5th week, you will work on a milestone of project 1.
// - During the 6th week, you will work on a milestone of project 2.
// The total number of weeks is 6.
//
// Constraints:
// n == milestones.length
// 	1 <= n <= 105
// 	1 <= milestones[i] <= 109
//
// Helpful references (internal KB):
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} milestones
 * @return {number}
 */
var numberOfWeeks = function(milestones) {
    const totalMilestones = milestones.reduce((sum, m) => sum + m, 0);
    const maxMilestone = Math.max(...milestones);
    
    // If the largest project has more milestones than the sum of the rest, we can only work for (totalMilestones - maxMilestone) * 2 + 1 weeks
    if (maxMilestone > totalMilestones - maxMilestone) {
        return (totalMilestones - maxMilestone) * 2 + 1;
    }
    
    // Otherwise, we can work for all milestones
    return totalMilestones;
};
