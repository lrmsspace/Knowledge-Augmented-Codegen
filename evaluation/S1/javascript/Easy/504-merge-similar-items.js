// Source: https://leetcode.com/problems/merge-similar-items/   |   Difficulty: Easy
//
// Problem Description:
// You are given two 2D integer arrays, items1 and items2, representing two sets of items. Each array items has the following properties:
//
//
// 	items[i] = [valuei, weighti] where valuei represents the value and weighti represents the weight of the ith item.
// 	The value of each item in items is unique.
//
//
// Return a 2D integer array ret where ret[i] = [valuei, weighti], with weighti being the sum of weights of all items with value valuei.
//
// Note: ret should be returned in ascending order by value.
//
// Example:
// Input: items1 = [[1,1],[4,5],[3,8]], items2 = [[3,1],[1,5]]
// Output: [[1,6],[3,9],[4,5]]
// Explanation: 
// The item with value = 1 occurs in items1 with weight = 1 and in items2 with weight = 5, total weight = 1 + 5 = 6.
// The item with value = 3 occurs in items1 with weight = 8 and in items2 with weight = 1, total weight = 8 + 1 = 9.
// The item with value = 4 occurs in items1 with weight = 5, total weight = 5.  
// Therefore, we return [[1,6],[3,9],[4,5]].
//
// Constraints:
// 1 <= items1.length, items2.length <= 1000
// 	items1[i].length == items2[i].length == 2
// 	1 <= valuei, weighti <= 1000
// 	Each valuei in items1 is unique.
// 	Each valuei in items2 is unique.
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - String Hashing (string, array, hashing)
//   • When to use: Use when you need to efficiently compare strings or substrings, detect duplicates, or perform pattern matching in large text datasets. It's particularly useful for speeding up operations that would otherwise be O(N*M) or O(N^2).
//   • Idea: String hashing maps strings to numerical values, allowing for fast comparisons and operations like substring search. It typically uses a polynomial rolling hash function, achieving O(N) preprocessing and O(1) or O(log N) query time for substrings.
//   • Invariants: The hash of any prefix of the string is correctly computed based on its characters and chosen parameters.; For a rolling hash, the hash of the current window is always maintained correctly as the window slides.
//   • Tips: Choose a large prime modulus (or two) to minimize collision probability.; Select a base (prime number) larger than the alphabet size to ensure unique contributions from characters.
//   • Pitfalls: Hash collisions are possible and can lead to incorrect results if not properly handled or verified.; A poorly chosen base or modulus can significantly increase the frequency of collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} items1
 * @param {number[][]} items2
 * @return {number[][]}
 */
var mergeSimilarItems = function(items1, items2) {
    const weightMap = new Map();
    for (const [value, weight] of items1) {
        weightMap.set(value, (weightMap.get(value) || 0) + weight);
    }
    for (const [value, weight] of items2) {
        weightMap.set(value, (weightMap.get(value) || 0) + weight);
    }
    const result = [];
    for (const [value, weight] of weightMap.entries()) {
        result.push([value, weight]);
    }
    result.sort((a, b) => a[0] - b[0]);
    return result;
};