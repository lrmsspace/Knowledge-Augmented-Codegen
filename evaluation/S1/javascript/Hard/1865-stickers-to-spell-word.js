// Source: https://leetcode.com/problems/stickers-to-spell-word/   |   Difficulty: Hard
//
// Problem Description:
// We are given n different types of stickers. Each sticker has a lowercase English word on it.
//
// You would like to spell out the given string target by cutting individual letters from your collection of stickers and rearranging them. You can use each sticker more than once if you want, and you have infinite quantities of each sticker.
//
// Return the minimum number of stickers that you need to spell out target. If the task is impossible, return -1.
//
// Note: In all test cases, all words were chosen randomly from the 1000 most common US English words, and target was chosen as a concatenation of two random words.
//
// Example:
// Input: stickers = ["with","example","science"], target = "thehat"
// Output: 3
// Explanation:
// We can use 2 "with" stickers, and 1 "example" sticker.
// After cutting and rearrange the letters of those stickers, we can form the target "thehat".
// Also, this is the minimum number of stickers necessary to form the target string.
//
// Constraints:
// n == stickers.length
// 	1 <= n <= 50
// 	1 <= stickers[i].length <= 10
// 	1 <= target.length <= 15
// 	stickers[i] and target consist of lowercase English letters.
//
// Helpful references (internal KB):
// - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
//   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
//   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
//   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
//   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
//   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Counting labeled graphs (number, recursion, counting, dp-1d)
//   • When to use: When the problem requires enumerating distinct labeled graphs with specific properties, such as connectivity, on a given number of vertices. It is suitable for combinatorial counting problems involving graph structures.
//   • Idea: This technique determines the number of connected labeled graphs by subtracting the count of disconnected graphs from the total. It typically employs a recursive or dynamic programming approach, often involving combinatorial terms like binomial coefficients, with a polynomial time complexity.
//   • Invariants: The total number of labeled graphs $G_n$ for $n$ vertices is always $2^{n(n-1)/2}$.; For any $n$, the sum of connected and disconnected labeled graphs equals the total number of labeled graphs.
//   • Tips: Start with the total number of labeled graphs $G_n = 2^{n(n-1)/2}$.; Use complementary counting: total graphs minus disconnected graphs.
//   • Pitfalls: Forgetting to divide by $n$ when converting from rooted to unrooted disconnected graphs.; Incorrectly handling base cases for recursive definitions or DP states.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} stickers
 * @param {string} target
 * @return {number}
 */
var minStickers = function(stickers, target) {
    const m = stickers.length;
    const n = target.length;
    const stickerCounts = Array.from({ length: m }, () => Array(26).fill(0));
    const targetCount = Array(26).fill(0);

    for (let i = 0; i < m; i++) {
        for (const c of stickers[i]) {
            stickerCounts[i][c.charCodeAt(0) - 97]++;
        }
    }

    for (const c of target) {
        targetCount[c.charCodeAt(0) - 97]++;
    }

    const memo = new Map();

    function dfs(remain) {
        if (remain === 0) return 0;
        if (memo.has(remain)) return memo.get(remain);

        let minStickersNeeded = Infinity;

        for (let i = 0; i < m; i++) {
            let newRemain = remain;
            for (let j = 0; j < 26; j++) {
                if (((remain >> j) & 1) === 1) {
                    const needed = targetCount[j];
                    const available = stickerCounts[i][j];
                    if (available > 0) {
                        newRemain &= ~(1 << j);
                    }
                }
            }

            if (newRemain !== remain) {
                minStickersNeeded = Math.min(minStickersNeeded, 1 + dfs(newRemain));
            }
        }

        memo.set(remain, minStickersNeeded);
        return minStickersNeeded;
    }

    const result = dfs((1 << n) - 1);
    return result === Infinity ? -1 : result;
};
