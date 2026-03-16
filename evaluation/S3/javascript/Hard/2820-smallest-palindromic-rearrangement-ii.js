// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a palindromic string s and an integer k.
//
// Return the k-th lexicographically smallest palindromic permutation of s. If there are fewer than k distinct palindromic permutations, return an empty string.
//
// Note: Different rearrangements that yield the same palindromic string are considered identical and are counted once.
//
// Example:
// Input: s = "abba", k = 2
//
// Output: "baab"
//
// Explanation:
//
//
// 	The two distinct palindromic rearrangements of "abba" are "abba" and "baab".
// 	Lexicographically, "abba" comes before "baab". Since k = 2, the output is "baab".
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
// 	s is guaranteed to be palindromic.
// 	1 <= k <= 106
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {number} k
 * @return {string}
 */
var smallestPalindrome = function(s, k) {
    const n = s.length;
    const charCount = new Array(26).fill(0);
    for (let char of s) {
        charCount[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
    }
    
    // Check if a palindromic rearrangement is possible
    let oddCount = 0;
    for (let count of charCount) {
        if (count % 2 !== 0) oddCount++;
    }
    if (oddCount > 1) return ""; // More than one odd count means no palindrome is possible
    
    // Build the first half of the palindrome
    const half = [];
    let middle = '';
    for (let i = 0; i < 26; i++) {
        const count = charCount[i];
        if (count % 2 !== 0) {
            middle = String.fromCharCode(i + 'a'.charCodeAt(0));
        }
        half.push(String.fromCharCode(i + 'a'.charCodeAt(0)).repeat(Math.floor(count / 2)));
    }
    
    // Generate all unique permutations of the half string
    const uniquePermutations = new Set();
    const backtrack = (path, used) => {
        if (path.length === half.join('').length) {
            uniquePermutations.add(path.join(''));
            return;
        }
        for (let i = 0; i < half.length; i++) {
            if (used[i] || (i > 0 && half[i] === half[i - 1] && !used[i - 1])) continue;
            used[i] = true;
            path.push(half[i]);
            backtrack(path, used);
            path.pop();
            used[i] = false;
        }
    };
    
    backtrack([], new Array(half.length).fill(false));
    
    // Sort the unique permutations and find the k-th one
    const sortedPermutations = Array.from(uniquePermutations).sort();
    if (k > sortedPermutations.length) return "";
    
    const chosenHalf = sortedPermutations[k - 1];
    const fullPalindrome = chosenHalf + middle + chosenHalf.split('').reverse().join('');
    
    return fullPalindrome;
};
