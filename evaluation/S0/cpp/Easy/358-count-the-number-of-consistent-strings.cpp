// Source: https://leetcode.com/problems/count-the-number-of-consistent-strings/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string allowed consisting of distinct characters and an array of strings words. A string is consistent if all characters in the string appear in the string allowed.
//
// Return the number of consistent strings in the array words.
//
// Example:
// Input: allowed = "ab", words = ["ad","bd","aaab","baa","badab"]
// Output: 2
// Explanation: Strings "aaab" and "baa" are consistent since they only contain characters 'a' and 'b'.
//
// Constraints:
// 1 <= words.length <= 104
// 	1 <= allowed.length <= 26
// 	1 <= words[i].length <= 10
// 	The characters in allowed are distinct.
// 	words[i] and allowed contain only lowercase English letters.
//

class Solution {
public:
    int countConsistentStrings(string allowed, vector<string>& words) {
        unordered_set<char> allowedSet(allowed.begin(), allowed.end());
        int consistentCount = 0;

        for (const string& word : words) {
            bool isConsistent = true;
            for (char c : word) {
                if (allowedSet.find(c) == allowedSet.end()) {
                    isConsistent = false;
                    break;
                }
            }
            if (isConsistent) {
                consistentCount++;
            }
        }

        return consistentCount;         
    }
};
