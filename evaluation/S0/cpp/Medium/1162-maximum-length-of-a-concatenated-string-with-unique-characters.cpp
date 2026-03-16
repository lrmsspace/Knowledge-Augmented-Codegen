// Source: https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings arr. A string s is formed by the concatenation of a subsequence of arr that has unique characters.
//
// Return the maximum possible length of s.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: arr = ["un","iq","ue"]
// Output: 4
// Explanation: All the valid concatenations are:
// - ""
// - "un"
// - "iq"
// - "ue"
// - "uniq" ("un" + "iq")
// - "ique" ("iq" + "ue")
// Maximum length is 4.
//
// Constraints:
// 1 <= arr.length <= 16
// 	1 <= arr[i].length <= 26
// 	arr[i] contains only lowercase English letters.
//

class Solution {
public:
    int maxLength(vector<string>& arr) {
        vector<int> masks;
        for (const string& s : arr) {
            int mask = 0;
            for (char c : s) {
                int bit = 1 << (c - 'a');
                if (mask & bit) {
                    mask = 0; // Duplicate character found
                    break;
                }
                mask |= bit;
            }
            if (mask != 0) {
                masks.push_back(mask);
            }
        }

        int maxLen = 0;
        function<void(int, int, int)> backtrack = [&](int index, int currentMask, int currentLen) {
            maxLen = max(maxLen, currentLen);
            for (int i = index; i < masks.size(); ++i) {
                if ((currentMask & masks[i]) == 0) { // No overlapping characters
                    backtrack(i + 1, currentMask | masks[i], currentLen + __builtin_popcount(masks[i]));
                }
            }
        };

        backtrack(0, 0, 0);
        return maxLen;          
    }
};
