// Source: https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/   |   Difficulty: Hard
//
// Problem Description:
// Let f(x) be the number of zeroes at the end of x!. Recall that x! = 1 * 2 * 3 * ... * x and by convention, 0! = 1.
//
//
// 	For example, f(3) = 0 because 3! = 6 has no zeroes at the end, while f(11) = 2 because 11! = 39916800 has two zeroes at the end.
//
//
// Given an integer k, return the number of non-negative integers x have the property that f(x) = k.
//
// Example:
// Input: k = 0
// Output: 5
// Explanation: 0!, 1!, 2!, 3!, and 4! end with k = 0 zeroes.
//
// Constraints:
// 0 <= k <= 109
//
// Helpful references (internal KB):
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - The Inclusion-Exclusion Principle (number, counting)
//   • When to use: Used for counting elements that satisfy a specific number of conditions (exactly k, at least k) from a larger set of conditions. It is particularly effective when direct counting with overlapping properties is complex.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial technique to count the size of a union of sets by summing the sizes of individual sets, then adjusting for intersections. For problems involving 'k' conditions, optimized versions can achieve O(2^N * N) complexity, where N is the total number of conditions.
//   • Invariants: The current sum correctly reflects the inclusion-exclusion contribution for all processed subsets of conditions.; Each f(Y) term accurately represents the count of elements satisfying at least all conditions in Y.
//   • Tips: Clearly define the sets and conditions involved in the problem.; Remember the alternating signs for sums of intersections.
//   • Pitfalls: Incorrectly applying the alternating signs in the summation.; Miscalculating the sizes of intersections (f(Y) terms).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int preimageSizeFZF(int k) {
        // Helper function to compute the number of trailing zeroes in x!
        auto trailingZeroes = [](long long x) {
            long long count = 0;
            while (x > 0) {
                x /= 5;
                count += x;
            }
            return count;
        };

        // Binary search to find the smallest x such that f(x) = k
        auto findLeft = [&](int k) {
            long long low = 0, high = 5LL * (k + 1);
            while (low < high) {
                long long mid = low + (high - low) / 2;
                if (trailingZeroes(mid) < k) {
                    low = mid + 1;
                } else {
                    high = mid;
                }
            }
            return low;
        };

        // Binary search to find the largest x such that f(x) = k
        auto findRight = [&](int k) {
            long long low = 0, high = 5LL * (k + 1);
            while (low < high) {
                long long mid = low + (high - low) / 2;
                if (trailingZeroes(mid) <= k) {
                    low = mid + 1;
                } else {
                    high = mid;
                }
            }
            return low - 1;
        };

        long long left = findLeft(k);
        long long right = findRight(k);
        return (right >= left) ? (right - left + 1) : 0;            
    }
};
