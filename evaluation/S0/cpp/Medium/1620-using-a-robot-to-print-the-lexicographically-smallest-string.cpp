// Source: https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and a robot that currently holds an empty string t. Apply one of the following operations until s and t are both empty:
//
//
// 	Remove the first character of a string s and give it to the robot. The robot will append this character to the string t.
// 	Remove the last character of a string t and give it to the robot. The robot will write this character on paper.
//
//
// Return the lexicographically smallest string that can be written on the paper.
//
// Example:
// Input: s = "zza"
// Output: "azz"
// Explanation: Let p denote the written string.
// Initially p="", s="zza", t="".
// Perform first operation three times p="", s="", t="zza".
// Perform second operation three times p="azz", s="", t="".
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of only English lowercase letters.
//

class Solution {
public:
    string robotWithString(string s) {
        vector<int> count(26, 0);
        for (char c : s) {
            count[c - 'a']++;
        }

        string t;
        string result;
        int minCharIndex = 0;

        for (char c : s) {
            t.push_back(c);
            count[c - 'a']--;

            while (minCharIndex < 26 && count[minCharIndex] == 0) {
                minCharIndex++;
            }

            while (!t.empty() && t.back() - 'a' <= minCharIndex) {
                result.push_back(t.back());
                t.pop_back();
            }
        }

        while (!t.empty()) {
            result.push_back(t.back());
            t.pop_back();
        }

        return result;          
    }
};
