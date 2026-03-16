// Source: https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer mountainHeight denoting the height of a mountain.
//
// You are also given an integer array workerTimes representing the work time of workers in seconds.
//
// The workers work simultaneously to reduce the height of the mountain. For worker i:
//
//
// 	To decrease the mountain's height by x, it takes workerTimes[i] + workerTimes[i] * 2 + ... + workerTimes[i] * x seconds. For example:
//
// 	
// 		To reduce the height of the mountain by 1, it takes workerTimes[i] seconds.
// 		To reduce the height of the mountain by 2, it takes workerTimes[i] + workerTimes[i] * 2 seconds, and so on.
// 	
// 	
//
//
// Return an integer representing the minimum number of seconds required for the workers to make the height of the mountain 0.
//
// Example:
// Input: mountainHeight = 4, workerTimes = [2,1,1]
//
// Output: 3
//
// Explanation:
//
// One way the height of the mountain can be reduced to 0 is:
//
//
// 	Worker 0 reduces the height by 1, taking workerTimes[0] = 2 seconds.
// 	Worker 1 reduces the height by 2, taking workerTimes[1] + workerTimes[1] * 2 = 3 seconds.
// 	Worker 2 reduces the height by 1, taking workerTimes[2] = 1 second.
//
//
// Since they work simultaneously, the minimum time needed is max(2, 3, 1) = 3 seconds.
//
// Constraints:
// 1 <= mountainHeight <= 105
// 	1 <= workerTimes.length <= 104
// 	1 <= workerTimes[i] <= 106
//
// Helpful references (internal KB):
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - Ternary Search (number, binary-search)
//   • When to use: Use when searching for the minimum or maximum of a unimodal function over a continuous interval. It efficiently narrows down the search space by evaluating the function at two internal points.
//   • Idea: Ternary search is an optimization algorithm for finding the extremum (minimum or maximum) of a unimodal function within a given interval. It repeatedly reduces the search interval by two-thirds, achieving logarithmic time complexity with respect to the interval size.
//   • Invariants: The global extremum of the unimodal function within the initial range is always contained within the current interval [L, R].; The interval [L, R] is non-empty and its length strictly decreases in each iteration.
//   • Tips: Carefully define the search interval [L, R] for the function.; Choose two internal points, typically L + (R-L)/3 and R - (R-L)/3.
//   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Floating-point precision issues can lead to infinite loops or incorrect bounds.
// - Binary search (interval, number, binary-search-answer, recursion)
//   • When to use: Use when optimizing a unimodal function (finding its maximum or minimum) over a continuous interval, where direct differentiation is hard or impossible.
//   • Idea: This algorithm finds the extremum (maximum or minimum) of a unimodal function over a given interval by repeatedly narrowing the search space. It evaluates the function at two internal points to achieve logarithmic convergence.
//   • Invariants: The extremum of the unimodal function f(x) is always within the current interval [l, r].; The function f(x) remains unimodal within the current interval [l, r].
//   • Tips: Use a fixed number of iterations as a stopping criterion instead of an epsilon value for robustness against floating point errors.; For golden section search, reuse one function evaluation from the previous step to minimize expensive computations.
//   • Pitfalls: Applying this algorithm to a non-unimodal function will yield an incorrect result.; Floating point precision issues can lead to incorrect comparisons or infinite loops if `eps` is too small.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        long long left = 0, right = 1e15; // Set a large upper bound for binary search
        while (left < right) {
            long long mid = left + (right - left) / 2;
            long long totalHeightReduced = 0;
            for (int time : workerTimes) {
                // Calculate how many times this worker can work within mid seconds
                long long n = (-1 + sqrt(1 + 8 * mid / time)) / 2; // Solve n(n+1)/2 * time <= mid
                totalHeightReduced += n;
                if (totalHeightReduced >= mountainHeight) {
                    break; // No need to calculate further if we've already reduced enough height
                }
            }
            if (totalHeightReduced >= mountainHeight) {
                right = mid; // Try to find a smaller time
            } else {
                left = mid + 1; // Need more time
            }
        }
        return left;            
    }
};
