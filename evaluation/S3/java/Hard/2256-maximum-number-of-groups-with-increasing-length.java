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
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - Binary search (interval, number, binary-search-answer, recursion)
//   • When to use: Use when optimizing a unimodal function (finding its maximum or minimum) over a continuous interval, where direct differentiation is hard or impossible.
//   • Idea: This algorithm finds the extremum (maximum or minimum) of a unimodal function over a given interval by repeatedly narrowing the search space. It evaluates the function at two internal points to achieve logarithmic convergence.
//   • Invariants: The extremum of the unimodal function f(x) is always within the current interval [l, r].; The function f(x) remains unimodal within the current interval [l, r].
//   • Tips: Use a fixed number of iterations as a stopping criterion instead of an epsilon value for robustness against floating point errors.; For golden section search, reuse one function evaluation from the previous step to minimize expensive computations.
//   • Pitfalls: Applying this algorithm to a non-unimodal function will yield an incorrect result.; Floating point precision issues can lead to incorrect comparisons or infinite loops if `eps` is too small.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxIncreasingGroups(List<Integer> usageLimits) {
        Collections.sort(usageLimits);
        int groups = 0;
        long total = 0;

        for (int limit : usageLimits) {
            if (total < groups) {
                break;
            }
            total += limit;
            groups++;
        }

        return groups;          
    }
}
