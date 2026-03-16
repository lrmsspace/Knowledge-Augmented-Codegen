// Source: https://leetcode.com/problems/circular-sentence/   |   Difficulty: Easy
//
// Problem Description:
// A sentence is a list of words that are separated by a single space with no leading or trailing spaces.
//
//
// 	For example, "Hello World", "HELLO", "hello world hello world" are all sentences.
//
//
// Words consist of only uppercase and lowercase English letters. Uppercase and lowercase English letters are considered different.
//
// A sentence is circular if:
//
//
// 	The last character of each word in the sentence is equal to the first character of its next word.
// 	The last character of the last word is equal to the first character of the first word.
//
//
// For example, "leetcode exercises sound delightful", "eetcode", "leetcode eats soul" are all circular sentences. However, "Leetcode is cool", "happy Leetcode", "Leetcode" and "I like Leetcode" are not circular sentences.
//
// Given a string sentence, return true if it is circular. Otherwise, return false.
//
// Example:
// Input: sentence = "leetcode exercises sound delightful"
// Output: true
// Explanation: The words in sentence are ["leetcode", "exercises", "sound", "delightful"].
// - leetcode's last character is equal to exercises's first character.
// - exercises's last character is equal to sound's first character.
// - sound's last character is equal to delightful's first character.
// - delightful's last character is equal to leetcode's first character.
// The sentence is circular.
//
// Constraints:
// 1 <= sentence.length <= 500
// 	sentence consist of only lowercase and uppercase English letters and spaces.
// 	The words in sentence are separated by a single space.
// 	There are no leading or trailing spaces.
//
// Helpful references (internal KB):
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
// - Floyd's Linked List Cycle Finding Algorithm (linked-list, two-pointers, simulation)
//   • When to use: Use this algorithm to efficiently detect if a linked list contains a cycle and, optionally, find the entry point of that cycle, using only constant extra space.
//   • Idea: This algorithm uses two pointers, one moving faster than the other, to detect if a cycle exists in a linked list. If a cycle is found, it can then determine the cycle's starting node in O(N) time complexity and O(1) space complexity.
//   • Invariants: The slow and fast pointers are always valid nodes or null.; In the detection phase, the fast pointer always covers twice the distance of the slow pointer.
//   • Tips: Initialize both slow and fast pointers at the head of the list.; Move the slow pointer by one step and the fast pointer by two steps in each iteration.
//   • Pitfalls: Forgetting to check for null on 'fast' and 'fast.next' before dereferencing them.; Incorrectly assuming the list is non-empty or has at least two nodes.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} sentence
 * @return {boolean}
 */
var isCircularSentence = function(sentence) {
    const words = sentence.split(' ');
    const n = words.length;
    
    // If there's only one word, check if the first and last characters are the same
    if (n === 1) {
        return words[0][0] === words[0][words[0].length - 1];
    }
    
    // Check each adjacent pair of words
    for (let i = 0; i < n - 1; i++) {
        if (words[i][words[i].length - 1] !== words[i + 1][0]) {
            return false;
        }
    }
    
    // Check if the last word's last character matches the first word's first character
    return words[n - 1][words[n - 1].length - 1] === words[0][0];
};
