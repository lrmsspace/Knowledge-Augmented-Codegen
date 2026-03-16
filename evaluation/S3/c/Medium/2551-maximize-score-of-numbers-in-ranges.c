// Source: https://leetcode.com/problems/maximize-score-of-numbers-in-ranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers start and an integer d, representing n intervals [start[i], start[i] + d].
//
// You are asked to choose n integers where the ith integer must belong to the ith interval. The score of the chosen integers is defined as the minimum absolute difference between any two integers that have been chosen.
//
// Return the maximum possible score of the chosen integers.
//
// Example:
// Input: start = [6,0,3], d = 2
//
// Output: 4
//
// Explanation:
//
// The maximum possible score can be obtained by choosing integers: 8, 0, and 4. The score of these chosen integers is min(|8 - 0|, |8 - 4|, |0 - 4|) which equals 4.
//
// Constraints:
// 2 <= start.length <= 105
// 	0 <= start[i] <= 109
// 	0 <= d <= 109
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
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxPossibleScore(int* start, int startSize, int d) {
    // Step 1: Sort the start array to ensure we can evaluate intervals in order.
    qsort(start, startSize, sizeof(int), (int (*)(const void *, const void *))strcmp);

    // Step 2: Use binary search to find the maximum score.
    int low = 0; // Minimum possible score
    int high = d; // Maximum possible score (the length of the interval)
    int maxScore = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (isFeasible(start, startSize, d, mid)) {
            maxScore = mid; // Update maxScore if mid is feasible
            low = mid + 1; // Try for a higher score
        } else {
            high = mid - 1; // Try for a lower score
        }
    }

    return maxScore;        
}
