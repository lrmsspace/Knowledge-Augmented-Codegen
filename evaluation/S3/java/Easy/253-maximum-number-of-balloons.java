// Source: https://leetcode.com/problems/maximum-number-of-balloons/   |   Difficulty: Easy
//
// Problem Description:
// Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as possible.
//
// You can use each character in text at most once. Return the maximum number of instances that can be formed.
//
// Example:
// Input: text = "nlaebolko"
// Output: 1
//
// Constraints:
// 1 <= text.length <= 104
// 	text consists of lower case English letters only.
//
//
//  
// Note: This question is the same as  2287: Rearrange Characters to Make Target String.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Data Compression (tree, heap, greedy, recursion, counting)
//   • When to use: Use when you need to losslessly compress data by assigning shorter bit sequences to more frequent symbols, aiming for the shortest possible average code length. It is effective for data with non-uniform character distributions.
//   • Idea: Huffman coding is a greedy algorithm that constructs an optimal prefix code for a given set of symbols and their frequencies. It builds a binary tree (Huffman trie) by repeatedly merging the two nodes with the smallest frequencies, resulting in an encoding with O(N + K log K) time complexity, where N is input length and K is alphabet size.
//   • Invariants: The priority queue always contains valid Huffman nodes, each representing a subtree or a leaf character.; Every internal node in the Huffman tree has exactly two children, and its frequency is the sum of its children's frequencies.
//   • Tips: Use a min-priority queue to efficiently retrieve and combine the two lowest-frequency nodes.; Represent the Huffman tree explicitly to generate codes and for decoding.
//   • Pitfalls: The overhead of storing the Huffman tree or frequency table can negate compression benefits for small inputs.; Not truly optimal for all data types; it's a statistical compression method.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxNumberOfBalloons(String text) {
        int[] count = new int[26];
        for (char c : text.toCharArray()) {
            count[c - 'a']++;
        }

        int balloonCount = 0;
        while (count['b' - 'a'] > 0 && count['a' - 'a'] > 0 && count['l' - 'a'] > 1 && count['o' - 'a'] > 1 && count['n' - 'a'] > 0) {
            balloonCount++;
            count['b' - 'a']--;
            count['a' - 'a']--;
            count['l' - 'a'] -= 2;
            count['o' - 'a'] -= 2;
            count['n' - 'a']--;
        }

        return balloonCount;            
    }
}
