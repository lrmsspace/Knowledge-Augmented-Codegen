// Source: https://leetcode.com/problems/sort-characters-by-frequency/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.
//
// Return the sorted string. If there are multiple answers, return any of them.
//
// Example:
// Input: s = "tree"
// Output: "eert"
// Explanation: 'e' appears twice while 'r' and 't' both appear once.
// So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
//
// Constraints:
// 1 <= s.length <= 5 * 105
// 	s consists of uppercase and lowercase English letters and digits.
//

class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> freqMap;
        for (char c : s) {
            freqMap[c]++;
        }

        vector<pair<char, int>> freqVec(freqMap.begin(), freqMap.end());
        sort(freqVec.begin(), freqVec.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
            return a.second > b.second;
        });

        string result;
        for (const auto& p : freqVec) {
            result.append(p.second, p.first);
        }

        return result;          
    }
};
