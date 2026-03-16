// Source: https://leetcode.com/problems/maximum-number-of-groups-entering-a-competition/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer array grades which represents the grades of students in a university. You would like to enter all these students into a competition in ordered non-empty groups, such that the ordering meets the following conditions:
//
//
// 	The sum of the grades of students in the ith group is less than the sum of the grades of students in the (i + 1)th group, for all groups (except the last).
// 	The total number of students in the ith group is less than the total number of students in the (i + 1)th group, for all groups (except the last).
//
//
// Return the maximum number of groups that can be formed.
//
// Example:
// Input: grades = [10,6,12,7,3,5]
// Output: 3
// Explanation: The following is a possible way to form 3 groups of students:
// - 1st group has the students with grades = [12]. Sum of grades: 12. Student count: 1
// - 2nd group has the students with grades = [6,7]. Sum of grades: 6 + 7 = 13. Student count: 2
// - 3rd group has the students with grades = [10,3,5]. Sum of grades: 10 + 3 + 5 = 18. Student count: 3
// It can be shown that it is not possible to form more than 3 groups.
//
// Constraints:
// 1 <= grades.length <= 105
// 	1 <= grades[i] <= 105
//
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when tasks with associated processing times and costs need to be sequenced on a single machine to minimize a total objective function, typically involving weighted completion times or penalties. The optimal sequence is found by a greedy sort.
//   • Idea: This method finds an optimal schedule for jobs on a single machine by sorting them according to a greedy criterion derived from an exchange argument. It achieves an optimal solution with O(N log N) time complexity, dominated by the sorting step.
//   • Invariants: The relative order of any two jobs i and j in the sorted sequence is consistent with the greedy comparison rule.; Any prefix of the sorted schedule represents an optimal ordering for the jobs within that prefix.
//   • Tips: Clearly define the objective function to be minimized.; Formulate the greedy sorting rule using an exchange argument for any two adjacent jobs.
//   • Pitfalls: Incorrectly deriving the greedy comparison criterion.; Applying this method to problems with multiple machines or complex precedence constraints without adaptation.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumGroups(int* grades, int gradesSize) {
    int groups = 0;
    int students = 0;

    while (students + groups + 1 <= gradesSize) {
        groups++;
        students += groups;
    }

    return groups;      
}
