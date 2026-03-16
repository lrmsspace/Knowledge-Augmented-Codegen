// Source: https://leetcode.com/problems/minimum-operations-to-make-character-frequencies-equal/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s.
//
// A string t is called good if all characters of t occur the same number of times.
//
// You can perform the following operations any number of times:
//
//
//  Delete a character from s.
//  Insert a character in s.
//  Change a character in s to its next letter in the alphabet.
//
//
// Note that you cannot change 'z' to 'a' using the third operation.
//
// Return the minimum number of operations required to make s good.
//
// Example:
// Input: s = "acab"
//
// Output: 1
//
// Explanation:
//
// We can make s good by deleting one occurrence of character 'a'.
//
// Constraints:
// 3 <= s.length <= 2 * 104
//  s contains only lowercase English letters.
//

class Solution {
public:
    int makeStringGood(string s) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c - 'a']++;
        }
        
        unordered_map<int, int> countFreq;
        for (int f : freq) {
            if (f > 0) {
                countFreq[f]++;
            }
        }
        
        int minOps = INT_MAX;
        for (int targetFreq = 1; targetFreq <= s.length(); targetFreq++) {
            int ops = 0;
            for (auto& [f, cnt] : countFreq) {
                if (f < targetFreq) {
                    ops += (targetFreq - f) * cnt; // insertions
                } else if (f > targetFreq) {
                    ops += (f - targetFreq) * cnt; // deletions
                }
            }
            minOps = min(minOps, ops);
        }
        
        return minOps;          
    }
};
