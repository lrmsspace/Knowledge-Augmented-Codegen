// Source: https://leetcode.com/problems/replace-words/   |   Difficulty: Medium
//
// Problem Description:
// In English, we have a concept called root, which can be followed by some other word to form another longer word - let's call this word derivative. For example, when the root "help" is followed by the word "ful", we can form a derivative "helpful".
//
// Given a dictionary consisting of many roots and a sentence consisting of words separated by spaces, replace all the derivatives in the sentence with the root forming it. If a derivative can be replaced by more than one root, replace it with the root that has the shortest length.
//
// Return the sentence after the replacement.
//
// Example:
// Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
// Output: "the cat was rat by the bat"
//
// Constraints:
// 1 <= dictionary.length <= 1000
// 	1 <= dictionary[i].length <= 100
// 	dictionary[i] consists of only lower-case letters.
// 	1 <= sentence.length <= 106
// 	sentence consists of only lower-case letters and spaces.
// 	The number of words in sentence is in the range [1, 1000]
// 	The length of each word in sentence is in the range [1, 1000]
// 	Every two consecutive words in sentence will be separated by exactly one space.
// 	sentence does not have leading or trailing spaces.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        // Sort the dictionary to ensure shorter roots come first
        sort(dictionary.begin(), dictionary.end());

        // Split the sentence into words
        istringstream iss(sentence);
        string word;
        vector<string> result;

        while (iss >> word) {
            string replacement = word; // Default to the original word

            // Check for each root in the dictionary
            for (const string& root : dictionary) {
                if (word.substr(0, root.size()) == root) {
                    replacement = root; // Found a root that is a prefix
                    break; // No need to check further since we want the shortest root
                }
            }

            result.push_back(replacement);
        }

        // Join the result back into a sentence
        return accumulate(result.begin(), result.end(), string(),
                          [](const string& a, const string& b) {
                              return a.empty() ? b : a + " " + b;
                          });           
    }
};
