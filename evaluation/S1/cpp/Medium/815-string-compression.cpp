// Source: https://leetcode.com/problems/string-compression/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of characters chars, compress it using the following algorithm:
//
// Begin with an empty string s. For each group of consecutive repeating characters in chars:
//
//
// 	If the group's length is 1, append the character to s.
// 	Otherwise, append the character followed by the group's length.
//
//
// The compressed string s should not be returned separately, but instead, be stored in the input character array chars. Note that group lengths that are 10 or longer will be split into multiple characters in chars.
//
// After you are done modifying the input array, return the new length of the array.
//
// You must write an algorithm that uses only constant extra space.
//
// Note: The characters in the array beyond the returned length do not matter and should be ignored.
//
// Example:
// Input: chars = ["a","a","b","b","c","c","c"]
// Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
// Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".
//
// Constraints:
// 1 <= chars.length <= 2000
// 	chars[i] is a lowercase English letter, uppercase English letter, digit, or symbol.
//
// Helpful references (internal KB):
// - Data Compression (trie, array, trie-match, greedy, simulation)
//   • When to use: When needing to reduce the size of data by encoding frequently occurring patterns or symbols with shorter representations, especially for lossless compression of text or binary streams.
//   • Idea: Data compression algorithms like Huffman coding and LZW reduce data size by assigning variable-length codes based on frequency or by replacing repeated patterns with shorter references. Huffman coding typically involves O(N log N) for building the tree and O(N) for encoding/decoding, while LZW can be O(N) for both, where N is the input size.
//   • Invariants: The encoding process consistently maps input symbols or sequences to their assigned codes.; The decoding process reconstructs the original data by traversing the encoding structure using the compressed bitstream.
//   • Tips: Use a min-priority queue to efficiently build the Huffman tree from character frequencies.; Represent Huffman codes as bit strings for efficient storage and transmission.
//   • Pitfalls: Incorrectly handling edge cases like empty input or single-character input.; Off-by-one errors when reading/writing bit streams.
// - Z-function and its calculation (string, array, two-pointers)
//   • When to use: Use when you need to find the length of the longest common prefix between a string and all its suffixes efficiently. It is fundamental for various string matching and pattern searching problems.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the original string and its suffix starting at index i. This algorithm calculates the entire Z-array in O(N) time complexity.
//   • Invariants: For all k < i, z[k] has been correctly computed.; The interval [l, r) always represents the rightmost segment match found so far.
//   • Tips: Leverage previously computed Z-values to avoid redundant comparisons.; Maintain a [l, r) window representing the rightmost segment match found so far.
//   • Pitfalls: Incorrectly handling the base case z[0] (usually set to 0).; Off-by-one errors when calculating the length of the prefix or updating the window.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size();
        if (n == 0) return 0;
        int writePos = 0;
        int readPos = 0;

        while (readPos < n) {
            char currentChar = chars[readPos];
            int count = 0;

            // Count occurrences of the current character
            while (readPos < n && chars[readPos] == currentChar) {
                readPos++;
                count++;
            }

            // Write the character
            chars[writePos++] = currentChar;

            // Write the count if greater than 1
            if (count > 1) {
                string countStr = to_string(count);
                for (char c : countStr) {
                    chars[writePos++] = c;
                }
            }
        }

        return writePos;            
    }
};
