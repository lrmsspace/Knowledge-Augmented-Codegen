// Source: https://leetcode.com/problems/find-the-sequence-of-strings-appeared-on-the-screen/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string target.
//
// Alice is going to type target on her computer using a special keyboard that has only two keys:
//
//
// 	Key 1 appends the character "a" to the string on the screen.
// 	Key 2 changes the last character of the string on the screen to its next character in the English alphabet. For example, "c" changes to "d" and "z" changes to "a".
//
//
// Note that initially there is an empty string "" on the screen, so she can only press key 1.
//
// Return a list of all strings that appear on the screen as Alice types target, in the order they appear, using the minimum key presses.
//
// Example:
// Input: target = "abc"
//
// Output: ["a","aa","ab","aba","abb","abc"]
//
// Explanation:
//
// The sequence of key presses done by Alice are:
//
//
// 	Press key 1, and the string on the screen becomes "a".
// 	Press key 1, and the string on the screen becomes "aa".
// 	Press key 2, and the string on the screen becomes "ab".
// 	Press key 1, and the string on the screen becomes "aba".
// 	Press key 2, and the string on the screen becomes "abb".
// 	Press key 2, and the string on the screen becomes "abc".
//
// Constraints:
// 1 <= target.length <= 400
// 	target consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Z-function and its calculation (string, array, counting)
//   • When to use: Use when you need to find all occurrences of a pattern within a text, or to identify repeated prefixes within a string efficiently.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the string and its suffix starting at index i. It runs in linear time, O(N), where N is the length of the string.
//   • Invariants: For all j < i, z[j] correctly stores the length of the longest common prefix between S and S[j...].; The segment [l, r-1] represents the rightmost segment that is a prefix of S and has been fully processed.
//   • Tips: Initialize z[0] to 0 (or N, depending on definition) and handle it as a base case.; Utilize previously computed Z-values to avoid redundant comparisons, especially within the 'rightmost matching segment' [l, r].
//   • Pitfalls: Incorrectly updating or using the 'rightmost matching segment' boundaries (l and r).; Off-by-one errors when calculating indices or lengths, especially with 0-based vs. 1-based indexing.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<String> stringSequence(String target) {
        List<String> result = new ArrayList<>();
        StringBuilder current = new StringBuilder();

        for (char c : target.toCharArray()) {
            // Press key 1 to append 'a' until we reach the desired character
            while (current.length() < target.indexOf(c) + 1) {
                current.append('a');
                result.add(current.toString());
            }
            // Press key 2 to change the last character to the desired character
            while (current.charAt(current.length() - 1) != c) {
                char lastChar = current.charAt(current.length() - 1);
                char nextChar = (char) ((lastChar - 'a' + 1) % 26 + 'a');
                current.setCharAt(current.length() - 1, nextChar);
                result.add(current.toString());
            }
        }

        return result;          
    }
}
