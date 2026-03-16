// Source: https://leetcode.com/problems/text-justification/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of strings words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.
//
// You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.
//
// Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line does not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
//
// For the last line of text, it should be left-justified, and no extra space is inserted between words.
//
// Note:
//
//
// 	A word is defined as a character sequence consisting of non-space characters only.
// 	Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
// 	The input array words contains at least one word.
//
// Example:
// Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
// Output:
// [
//    "This    is    an",
//    "example  of text",
//    "justification.  "
// ]
//
// Constraints:
// 1 <= words.length <= 300
// 	1 <= words[i].length <= 20
// 	words[i] consists of only English letters and symbols.
// 	1 <= maxWidth <= 100
// 	words[i].length <= maxWidth
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int n = words.size();
        int index = 0;

        while (index < n) {
            int totalChars = words[index].length();
            int last = index + 1;

            // Determine how many words can fit in the current line
            while (last < n) {
                if (totalChars + 1 + words[last].length() > maxWidth) break;
                totalChars += 1 + words[last].length();
                last++;
            }

            string line;
            int numberOfWords = last - index;
            // If we're on the last line or the line contains only one word
            if (last == n || numberOfWords == 1) {
                for (int i = index; i < last; i++) {
                    line += words[i];
                    if (i < last - 1) line += " ";
                }
                line += string(maxWidth - line.length(), ' '); // Pad with spaces
            } else {
                // Calculate spaces to distribute
                int totalSpaces = maxWidth - totalChars + (numberOfWords - 1);
                int spaceBetweenWords = totalSpaces / (numberOfWords - 1);
                int extraSpaces = totalSpaces % (numberOfWords - 1);

                for (int i = index; i < last; i++) {
                    line += words[i];
                    if (i < last - 1) {
                        line += string(spaceBetweenWords + (extraSpaces > 0 ? 1 : 0), ' ');
                        if (extraSpaces > 0) extraSpaces--;
                    }
                }
            }
            result.push_back(line);
            index = last;
        }

        return result;          
    }
};
