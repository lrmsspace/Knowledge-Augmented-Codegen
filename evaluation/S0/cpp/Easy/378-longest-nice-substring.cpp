// Source: https://leetcode.com/problems/longest-nice-substring/   |   Difficulty: Easy
//
// Problem Description:
// A string s is nice if, for every letter of the alphabet that s contains, it appears both in uppercase and lowercase. For example, "abABB" is nice because 'A' and 'a' appear, and 'B' and 'b' appear. However, "abA" is not because 'b' appears, but 'B' does not.
//
// Given a string s, return the longest substring of s that is nice. If there are multiple, return the substring of the earliest occurrence. If there are none, return an empty string.
//
// Example:
// Input: s = "YazaAay"
// Output: "aAa"
// Explanation: "aAa" is a nice string because 'A/a' is the only letter of the alphabet in s, and both 'A' and 'a' appear.
// "aAa" is the longest nice substring.
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of uppercase and lowercase English letters.
//

class Solution {
public:
    string longestNiceSubstring(string s) {
        int n = s.size();
        string res = "";

        for (int i = 0; i < n; ++i) {
            unordered_set<char> charSet;
            for (int j = i; j < n; ++j) {
                charSet.insert(s[j]);
                if (isNice(charSet)) {
                    if (j - i + 1 > res.size()) {
                        res = s.substr(i, j - i + 1);
                    }
                }
            }
        }

        return res;         
    }
};
