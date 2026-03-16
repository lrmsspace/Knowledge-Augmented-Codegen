// Source: https://leetcode.com/problems/count-the-number-of-special-characters-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word. A letter c is called special if it appears both in lowercase and uppercase in word, and every lowercase occurrence of c appears before the first uppercase occurrence of c.
//
// Return the number of special letters in word.
//
// Example:
// Input: word = "aaAbcBC"
//
// Output: 3
//
// Explanation:
//
// The special characters are 'a', 'b', and 'c'.
//
// Constraints:
// 1 <= word.length <= 2 * 105
// 	word consists of only lowercase and uppercase English letters.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} word
 * @return {number}
 */
var numberOfSpecialChars = function(word) {
    const charCount = new Map();
    let specialCharCount = 0;

    for (const char of word) {
        const lowerChar = char.toLowerCase();
        
        if (!charCount.has(lowerChar)) {
            charCount.set(lowerChar, { lowercase: 0, uppercase: 0 });
        }
        
        const counts = charCount.get(lowerChar);
        
        if (char === lowerChar) {
            counts.lowercase++;
        } else {
            counts.uppercase++;
        }
        
        // Check if the character is special
        if (counts.lowercase > 0 && counts.uppercase > 0 && counts.lowercase <= counts.uppercase) {
            specialCharCount++;
            // Mark this character as counted to avoid double counting
            charCount.set(lowerChar, { lowercase: counts.lowercase, uppercase: counts.uppercase, counted: true });
        }
    }

    return specialCharCount;
};
