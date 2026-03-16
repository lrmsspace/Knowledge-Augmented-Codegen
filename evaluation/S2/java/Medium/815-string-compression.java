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
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Data Compression (trie, array, trie-match, greedy, simulation)
//   • When to use: When needing to reduce the size of data by encoding frequently occurring patterns or symbols with shorter representations, especially for lossless compression of text or binary streams.
//   • Idea: Data compression algorithms like Huffman coding and LZW reduce data size by assigning variable-length codes based on frequency or by replacing repeated patterns with shorter references. Huffman coding typically involves O(N log N) for building the tree and O(N) for encoding/decoding, while LZW can be O(N) for both, where N is the input size.
//   • Invariants: The encoding process consistently maps input symbols or sequences to their assigned codes.; The decoding process reconstructs the original data by traversing the encoding structure using the compressed bitstream.
//   • Tips: Use a min-priority queue to efficiently build the Huffman tree from character frequencies.; Represent Huffman codes as bit strings for efficient storage and transmission.
//   • Pitfalls: Incorrectly handling edge cases like empty input or single-character input.; Off-by-one errors when reading/writing bit streams.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int compress(char[] chars) {
        int write = 0, anchor = 0;
        for (int read = 0; read < chars.length; read++) {
            if (read + 1 == chars.length || chars[read] != chars[read + 1]) {
                chars[write++] = chars[anchor];
                if (read > anchor) {
                    String count = Integer.toString(read - anchor + 1);
                    for (char c : count.toCharArray()) {
                        chars[write++] = c;
                    }
                }
                anchor = read + 1;
            }
        }
        return write;           
    }
}
