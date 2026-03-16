// Source: https://leetcode.com/problems/best-poker-hand/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array ranks and a character array suits. You have 5 cards where the ith card has a rank of ranks[i] and a suit of suits[i].
//
// The following are the types of poker hands you can make from best to worst:
//
//
// 	"Flush": Five cards of the same suit.
// 	"Three of a Kind": Three cards of the same rank.
// 	"Pair": Two cards of the same rank.
// 	"High Card": Any single card.
//
//
// Return a string representing the best type of poker hand you can make with the given cards.
//
// Note that the return values are case-sensitive.
//
// Example:
// Input: ranks = [13,2,3,1,9], suits = ["a","a","a","a","a"]
// Output: "Flush"
// Explanation: The hand with all the cards consists of 5 cards with the same suit, so we have a "Flush".
//
// Constraints:
// ranks.length == suits.length == 5
// 	1 <= ranks[i] <= 13
// 	'a' <= suits[i] <= 'd'
// 	No two cards have the same rank and suit.
//
// Helpful references (internal KB):
// - Binomial Coefficients (number, enumeration)
//   • When to use: Use when needing to calculate multiple binomial coefficients or when a single coefficient is required and N and K are not excessively large, allowing for table precomputation.
//   • Idea: This method computes binomial coefficients C(n, k) using Pascal's recurrence relation C(n, k) = C(n-1, k-1) + C(n-1, k), typically building a table. It has a time complexity of O(N*K) or O(N^2) for building the full triangle up to N.
//   • Invariants: C[i][0] is always 1 for any row i.; C[i][i] is always 1 for any row i.
//   • Tips: Intermediate results for Pascal's Triangle never exceed the final answer, simplifying overflow checks if not using modular arithmetic.; Each new table element requires only one addition, making it computationally efficient per element.
//   • Pitfalls: Building the entire Pascal's Triangle for a single C(N, K) can be slow for large N and K, as it computes many unnecessary values.; Directly computing C(N, K) using factorials can lead to overflow issues for large N, even if the final result fits.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} ranks
 * @param {character[]} suits
 * @return {string}
 */
var bestHand = function(ranks, suits) {
    const suitSet = new Set(suits);
    if (suitSet.size === 1) {
        return "Flush";
    }
    const rankCount = new Map();
    for (const rank of ranks) {
        rankCount.set(rank, (rankCount.get(rank) || 0) + 1);
    }
    for (const count of rankCount.values()) {
        if (count >= 3) {
            return "Three of a Kind";
        }
    }
    return "Pair";
};