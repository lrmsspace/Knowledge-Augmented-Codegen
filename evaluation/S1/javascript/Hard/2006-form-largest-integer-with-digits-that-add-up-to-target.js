// Source: https://leetcode.com/problems/form-largest-integer-with-digits-that-add-up-to-target/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers cost and an integer target, return the maximum integer you can paint under the following rules:
//
//
// 	The cost of painting a digit (i + 1) is given by cost[i] (0-indexed).
// 	The total cost used must be equal to target.
// 	The integer does not have 0 digits.
//
//
// Since the answer may be very large, return it as a string. If there is no way to paint any integer given the condition, return "0".
//
// Example:
// Input: cost = [4,3,2,5,6,7,2,5,5], target = 9
// Output: "7772"
// Explanation: The cost to paint the digit '7' is 2, and the digit '2' is 3. Then cost("7772") = 2*3+ 3*1 = 9. You could also paint "977", but "7772" is the largest number.
// Digit    cost
//   1  ->   4
//   2  ->   3
//   3  ->   2
//   4  ->   5
//   5  ->   6
//   6  ->   7
//   7  ->   2
//   8  ->   5
//   9  ->   5
//
// Constraints:
// cost.length == 9
// 	1 <= cost[i], target <= 5000
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} cost
 * @param {number} target
 * @return {string}
 */
var largestNumber = function(cost, target) {
    const dp = new Array(target + 1).fill("");
    
    for (let i = 0; i < cost.length; i++) {
        for (let j = cost[i]; j <= target; j++) {
            if (dp[j - cost[i]].length !== 0 || j === cost[i]) {
                const candidate = dp[j - cost[i]] + (i + 1);
                dp[j] = candidate.length > dp[j].length || (candidate.length === dp[j].length && candidate > dp[j]) ? candidate : dp[j];
            }
        }
    }

    return dp[target] === "" ? "0" : dp[target];
};
