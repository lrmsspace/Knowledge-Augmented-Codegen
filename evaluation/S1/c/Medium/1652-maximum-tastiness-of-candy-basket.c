// Source: https://leetcode.com/problems/maximum-tastiness-of-candy-basket/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of positive integers price where price[i] denotes the price of the ith candy and a positive integer k.
//
// The store sells baskets of k distinct candies. The tastiness of a candy basket is the smallest absolute difference of the prices of any two candies in the basket.
//
// Return the maximum tastiness of a candy basket.
//
// Example:
// Input: price = [13,5,1,8,21,2], k = 3
// Output: 8
// Explanation: Choose the candies with the prices [13,5,21].
// The tastiness of the candy basket is: min(|13 - 5|, |13 - 21|, |5 - 21|) = min(8, 8, 16) = 8.
// It can be proven that 8 is the maximum tastiness that can be achieved.
//
// Constraints:
// 2 <= k <= price.length <= 105
// 	1 <= price[i] <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maximumTastiness(int* price, int priceSize, int k) {
    // Helper function to compare two integers (for qsort)
    int compare(const void* a, const void* b) {
        return (*(int*)a - *(int*)b);
    }

    // Function to check if a given tastiness can be achieved
    int canAchieveTastiness(int* price, int priceSize, int k, int tastiness) {
        int count = 1; // Start with the first candy
        int lastPrice = price[0];

        for (int i = 1; i < priceSize; i++) {
            if (price[i] - lastPrice >= tastiness) {
                count++;
                lastPrice = price[i];
                if (count == k) {
                    return 1; // Achieved k distinct candies
                }
            }
        }
        return 0; // Could not achieve k distinct candies
    }

    // Sort the prices
    qsort(price, priceSize, sizeof(int), compare);

    // Binary search for the maximum tastiness
    int left = 0;
    int right = price[priceSize - 1] - price[0];
    int result = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canAchieveTastiness(price, priceSize, k, mid)) {
            result = mid; // Update result and try for a larger tastiness
            left = mid + 1;
        } else {
            right = mid - 1; // Try for a smaller tastiness
        }
    }
    return result;
}
