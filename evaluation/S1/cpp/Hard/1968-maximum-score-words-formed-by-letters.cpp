// Source: https://leetcode.com/problems/maximum-score-words-formed-by-letters/   |   Difficulty: Hard
//
// Problem Description:
// Given a list of words, list of  single letters (might be repeating) and score of every character.
//
// Return the maximum score of any valid set of words formed by using the given letters (words[i] cannot be used two or more times).
//
// It is not necessary to use all characters in letters and each letter can only be used once. Score of letters 'a', 'b', 'c', ... ,'z' is given by score[0], score[1], ... , score[25] respectively.
//
// Example:
// Input: words = ["dog","cat","dad","good"], letters = ["a","a","c","d","d","d","g","o","o"], score = [1,0,9,5,0,0,3,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0]
// Output: 23
// Explanation:
// Score  a=1, c=9, d=5, g=3, o=2
// Given letters, we can form the words "dad" (5+1+5) and "good" (3+2+2+5) with a score of 23.
// Words "dad" and "dog" only get a score of 21.
//
// Constraints:
// 1 <= words.length <= 14
// 	1 <= words[i].length <= 15
// 	1 <= letters.length <= 100
// 	letters[i].length == 1
// 	score.length == 26
// 	0 <= score[i] <= 10
// 	words[i], letters[i] contains only lower case English letters.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        int letterCount[26] = {0};
        for (char ch : letters) {
            letterCount[ch - 'a']++;
        }

        int n = words.size();
        int maxScore = 0;

        for (int mask = 0; mask < (1 << n); ++mask) {
            int currentScore = 0;
            int currentCount[26] = {0};
            bool valid = true;

            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    for (char ch : words[i]) {
                        currentCount[ch - 'a']++;
                        if (currentCount[ch - 'a'] > letterCount[ch - 'a']) {
                            valid = false;
                            break;
                        }
                        currentScore += score[ch - 'a'];
                    }
                }
                if (!valid) break;
            }

            if (valid) {
                maxScore = max(maxScore, currentScore);
            }
        }

        return maxScore;            
    }
};
