// Source: https://leetcode.com/problems/expressive-words/   |   Difficulty: Medium
//
// Problem Description:
// Sometimes people repeat letters to represent extra feeling. For example:
//
//
// 	"hello" -> "heeellooo"
// 	"hi" -> "hiiii"
//
//
// In these strings like "heeellooo", we have groups of adjacent letters that are all the same: "h", "eee", "ll", "ooo".
//
// You are given a string s and an array of query strings words. A query word is stretchy if it can be made to be equal to s by any number of applications of the following extension operation: choose a group consisting of characters c, and add some number of characters c to the group so that the size of the group is three or more.
//
//
// 	For example, starting with "hello", we could do an extension on the group "o" to get "hellooo", but we cannot get "helloo" since the group "oo" has a size less than three. Also, we could do another extension like "ll" -> "lllll" to get "helllllooo". If s = "helllllooo", then the query word "hello" would be stretchy because of these two extension operations: query = "hello" -> "hellooo" -> "helllllooo" = s.
//
//
// Return the number of query strings that are stretchy.
//
// Example:
// Input: s = "heeellooo", words = ["hello", "hi", "helo"]
// Output: 1
// Explanation: 
// We can extend "e" and "o" in the word "hello" to get "heeellooo".
// We can't extend "helo" to get "heeellooo" because the group "ll" is not size 3 or more.
//
// Constraints:
// 1 <= s.length, words.length <= 100
// 	1 <= words[i].length <= 100
// 	s and words[i] consist of lowercase letters.
//
// Helpful references (internal KB):
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int expressiveWords(string s, vector<string>& words) {
        auto getGroups = [](const string& str) {
            vector<pair<char, int>> groups;
            int n = str.size();
            for (int i = 0; i < n;) {
                char ch = str[i];
                int count = 0;
                while (i < n && str[i] == ch) {
                    ++count;
                    ++i;
                }
                groups.emplace_back(ch, count);
            }
            return groups;
        };

        vector<pair<char, int>> sGroups = getGroups(s);
        int expressiveCount = 0;

        for (const string& word : words) {
            vector<pair<char, int>> wGroups = getGroups(word);
            if (sGroups.size() != wGroups.size()) {
                continue;
            }

            bool isExpressive = true;
            for (size_t i = 0; i < sGroups.size(); ++i) {
                char sChar = sGroups[i].first;
                int sCount = sGroups[i].second;
                char wChar = wGroups[i].first;
                int wCount = wGroups[i].second;

                if (sChar != wChar) {
                    isExpressive = false;
                    break;
                }

                if (sCount < 3) {
                    if (sCount != wCount) {
                        isExpressive = false;
                        break;
                    }
                } else {
                    if (wCount > sCount) {
                        isExpressive = false;
                        break;
                    }
                }
            }

            if (isExpressive) {
                ++expressiveCount;
            }
        }

        return expressiveCount;         
    }
};
