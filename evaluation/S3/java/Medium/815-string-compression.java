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
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
//   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
//   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
//   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
//   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
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
