// Source: https://leetcode.com/problems/sentence-similarity-iii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings sentence1 and sentence2, each representing a sentence composed of words. A sentence is a list of words that are separated by a single space with no leading or trailing spaces. Each word consists of only uppercase and lowercase English characters.
//
// Two sentences s1 and s2 are considered similar if it is possible to insert an arbitrary sentence (possibly empty) inside one of these sentences such that the two sentences become equal. Note that the inserted sentence must be separated from existing words by spaces.
//
// For example,
//
//
// 	s1 = "Hello Jane" and s2 = "Hello my name is Jane" can be made equal by inserting "my name is" between "Hello" and "Jane" in s1.
// 	s1 = "Frog cool" and s2 = "Frogs are cool" are not similar, since although there is a sentence "s are" inserted into s1, it is not separated from "Frog" by a space.
//
//
// Given two sentences sentence1 and sentence2, return true if sentence1 and sentence2 are similar. Otherwise, return false.
//
// Example:
// Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
//
// Output: true
//
// Explanation:
//
// sentence2 can be turned to sentence1 by inserting "name is" between "My" and "Haley".
//
// Constraints:
// 1 <= sentence1.length, sentence2.length <= 100
// 	sentence1 and sentence2 consist of lowercase and uppercase English letters and spaces.
// 	The words in sentence1 and sentence2 are separated by a single space.
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
    bool areSentencesSimilar(string sentence1, string sentence2) {
        vector<string> words1, words2;
        stringstream ss1(sentence1), ss2(sentence2);
        string word;

        while (ss1 >> word) {
            words1.push_back(word);
        }
        while (ss2 >> word) {
            words2.push_back(word);
        }

        int i = 0, j = 0;
        while (i < words1.size() && j < words2.size() && words1[i] == words2[j]) {
            i++;
            j++;
        }

        int k = 0, l = 0;
        while (k < words1.size() && l < words2.size() && words1[words1.size() - 1 - k] == words2[words2.size() - 1 - l]) {
            k++;
            l++;
        }

        return i + k >= words1.size() || j + l >= words2.size();            
    }
};
