// Source: https://leetcode.com/problems/counting-words-with-a-given-prefix/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of strings words and a string pref.
//
// Return the number of strings in words that contain pref as a prefix.
//
// A prefix of a string s is any leading contiguous substring of s.
//
// Example:
// Input: words = ["pay","attention","practice","attend"], pref = "at"
// Output: 2
// Explanation: The 2 strings that contain "at" as a prefix are: "attention" and "attend".
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length, pref.length <= 100
// 	words[i] and pref consist of lowercase English letters.
//

class Solution {
public:
    int prefixCount(vector<string>& words, string pref) {
        int count = 0;
        for (const string& word : words) {
            if (word.substr(0, pref.size()) == pref) {
                count++;
            }
        }
        return count;           
    }
};
