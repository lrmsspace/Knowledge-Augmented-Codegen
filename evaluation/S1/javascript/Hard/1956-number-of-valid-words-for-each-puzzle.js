// Source: https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// With respect to a given puzzle string, a word is valid if both the following conditions are satisfied:
//
// 	word contains the first letter of puzzle.
// 	For each letter in word, that letter is in puzzle.
// 	
// 		For example, if the puzzle is "abcdefg", then valid words are "faced", "cabbage", and "baggage", while
// 		invalid words are "beefed" (does not include 'a') and "based" (includes 's' which is not in the puzzle).
// 	
// 	
//
// Return an array answer, where answer[i] is the number of words in the given word list words that is valid with respect to the puzzle puzzles[i].
//
// Example:
// Input: words = ["aaaa","asas","able","ability","actt","actor","access"], puzzles = ["aboveyz","abrodyz","abslute","absoryz","actresz","gaswxyz"]
// Output: [1,1,3,2,4,0]
// Explanation: 
// 1 valid word for "aboveyz" : "aaaa" 
// 1 valid word for "abrodyz" : "aaaa"
// 3 valid words for "abslute" : "aaaa", "asas", "able"
// 2 valid words for "absoryz" : "aaaa", "asas"
// 4 valid words for "actresz" : "aaaa", "asas", "actt", "access"
// There are no valid words for "gaswxyz" cause none of the words in the list contains letter 'g'.
//
// Constraints:
// 1 <= words.length <= 105
// 	4 <= words[i].length <= 50
// 	1 <= puzzles.length <= 104
// 	puzzles[i].length == 7
// 	words[i] and puzzles[i] consist of lowercase English letters.
// 	Each puzzles[i] does not contain repeated characters.
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} words
 * @param {string[]} puzzles
 * @return {number[]}
 */
var findNumOfValidWords = function(words, puzzles) {
    const wordCount = new Map();

    for (const word of words) {
        let mask = 0;
        for (const char of new Set(word)) {
            mask |= 1 << (char.charCodeAt(0) - 'a'.charCodeAt(0));
        }
        if (mask.toString(2).split('1').length - 1 <= 7) {
            wordCount.set(mask, (wordCount.get(mask) || 0) + 1);
        }
    }

    const results = [];
    for (const puzzle of puzzles) {
        const firstCharMask = 1 << (puzzle.charCodeAt(0) - 'a'.charCodeAt(0));
        let count = 0;

        let mask = 0;
        for (const char of puzzle) {
            mask |= 1 << (char.charCodeAt(0) - 'a'.charCodeAt(0));
        }

        for (let submask = mask; submask > 0; submask = (submask - 1) & mask) {
            if ((submask & firstCharMask) !== 0 && wordCount.has(submask)) {
                count += wordCount.get(submask);
            }
        }

        results.push(count);
    }

    return results;
};
