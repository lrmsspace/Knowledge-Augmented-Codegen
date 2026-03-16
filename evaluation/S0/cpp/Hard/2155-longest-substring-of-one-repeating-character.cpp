// Source: https://leetcode.com/problems/longest-substring-of-one-repeating-character/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string s. You are also given a 0-indexed string queryCharacters of length k and a 0-indexed array of integer indices queryIndices of length k, both of which are used to describe k queries.
//
// The ith query updates the character in s at index queryIndices[i] to the character queryCharacters[i].
//
// Return an array lengths of length k where lengths[i] is the length of the longest substring of s consisting of only one repeating character after the ith query is performed.
//
// Example:
// Input: s = "babacc", queryCharacters = "bcb", queryIndices = [1,3,3]
// Output: [3,3,4]
// Explanation: 
// - 1st query updates s = "bbbacc". The longest substring consisting of one repeating character is "bbb" with length 3.
// - 2nd query updates s = "bbbccc". 
//   The longest substring consisting of one repeating character can be "bbb" or "ccc" with length 3.
// - 3rd query updates s = "bbbbcc". The longest substring consisting of one repeating character is "bbbb" with length 4.
// Thus, we return [3,3,4].
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	k == queryCharacters.length == queryIndices.length
// 	1 <= k <= 105
// 	queryCharacters consists of lowercase English letters.
// 	0 <= queryIndices[i] < s.length
//

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.size();
        vector<int> result;
        
        for (int q = 0; q < queryCharacters.size(); q++) {
            s[queryIndices[q]] = queryCharacters[q];
            
            int maxLen = 1;
            int currentLen = 1;
            for (int i = 1; i < n; i++) {
                if (s[i] == s[i - 1]) {
                    currentLen++;
                } else {
                    currentLen = 1;
                }
                maxLen = max(maxLen, currentLen);
            }
            result.push_back(maxLen);
        }
        
        return result;          
    }
};
