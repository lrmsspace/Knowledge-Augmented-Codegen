// Source: https://leetcode.com/problems/first-bad-version/   |   Difficulty: Easy
//
// Problem Description:
// You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.
//
// Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.
//
// You are given an API bool isBadVersion(version) which returns whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.
//
// Example:
// Input: n = 5, bad = 4
// Output: 4
// Explanation:
// call isBadVersion(3) -> false
// call isBadVersion(5) -> true
// call isBadVersion(4) -> true
// Then 4 is the first bad version.
//
// Constraints:
// 1 <= bad <= n <= 231 - 1
//
// Helpful references (internal KB):
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
// - Binary search (interval, number, binary-search-answer, recursion)
//   • When to use: When searching for the extremum (maximum or minimum) of a unimodal function over a continuous or discrete interval. It is efficient for functions where direct differentiation or analytical solutions are complex.
//   • Idea: Ternary search is an algorithm that efficiently finds the extremum of a unimodal function within a given interval by repeatedly narrowing the search space. It typically achieves a logarithmic time complexity, O(log N), where N is the interval size.
//   • Invariants: The extremum of the unimodal function always lies within the current search interval [l, r].; The function value at m1 is compared with m2 to narrow the interval while preserving unimodality.
//   • Tips: Ensure the function is strictly unimodal within the search interval.; Handle discrete intervals carefully, especially the stopping condition (r - l) < 3.
//   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Incorrect stopping conditions can lead to infinite loops or suboptimal answers.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

int firstBadVersion(int n) {
    int low = 1, high = n;
    while (low < high) {
        int mid = low + (high - low) / 2; // Avoid potential overflow
        if (isBadVersion(mid)) {
            high = mid; // The first bad version is at mid or before
        } else {
            low = mid + 1; // The first bad version is after mid
        }
    }
    return low; // At the end of the loop, low is the first bad version     
}
