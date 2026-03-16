// Source: https://leetcode.com/problems/keyboard-row/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.
//
// Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are at the same row.
//
// In the American keyboard:
//
//
// 	the first row consists of the characters "qwertyuiop",
// 	the second row consists of the characters "asdfghjkl", and
// 	the third row consists of the characters "zxcvbnm".
//
// Example:
// Input: words = ["Hello","Alaska","Dad","Peace"]
//
// Output: ["Alaska","Dad"]
//
// Explanation:
//
// Both "a" and "A" are in the 2nd row of the American keyboard due to case insensitivity.
//
// Constraints:
// 1 <= words.length <= 20
// 	1 <= words[i].length <= 100
// 	words[i] consists of English letters (both lowercase and uppercase).
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
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        vector<string> result;
        unordered_map<char, int> charToRow = {
            {'q', 0}, {'w', 0}, {'e', 0}, {'r', 0}, {'t', 0}, {'y', 0}, {'u', 0}, {'i', 0}, {'o', 0}, {'p', 0},
            {'a', 1}, {'s', 1}, {'d', 1}, {'f', 1}, {'g', 1}, {'h', 1}, {'j', 1}, {'k', 1}, {'l', 1},
            {'z', 2}, {'x', 2}, {'c', 2}, {'v', 2}, {'b', 2}, {'n', 2}, {'m', 2}
        };
        
        for (const string& word : words) {
            int row = -1;
            bool canType = true;
            for (char ch : word) {
                char lowerCh = tolower(ch);
                if (charToRow.find(lowerCh) == charToRow.end()) {
                    canType = false;
                    break;
                }
                int currentRow = charToRow[lowerCh];
                if (row == -1) {
                    row = currentRow;
                } else if (row != currentRow) {
                    canType = false;
                    break;
                }
            }
            if (canType) {
                result.push_back(word);
            }
        }
        
        return result;          
    }
};
