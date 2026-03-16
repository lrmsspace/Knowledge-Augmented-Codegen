// Source: https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/   |   Difficulty: Hard
//
// Problem Description:
// Let's define a function countUniqueChars(s) that returns the number of unique characters in s.
//
//
// 	For example, calling countUniqueChars(s) if s = "LEETCODE" then "L", "T", "C", "O", "D" are the unique characters since they appear only once in s, therefore countUniqueChars(s) = 5.
//
//
// Given a string s, return the sum of countUniqueChars(t) where t is a substring of s. The test cases are generated such that the answer fits in a 32-bit integer.
//
// Notice that some substrings can be repeated so in this case you have to count the repeated ones too.
//
// Example:
// Input: s = "ABC"
// Output: 10
// Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
// Every substring is composed with only unique letters.
// Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of uppercase English letters only.
//

class Solution {
public:
    int uniqueLetterString(string s) {
        int n = s.size();
        vector<vector<int>> pos(26);
        
        // Record positions of each character
        for (int i = 0; i < n; i++) {
            pos[s[i] - 'A'].push_back(i);
        }
        
        int result = 0;
        
        // Calculate contribution of each character
        for (int c = 0; c < 26; c++) {
            const vector<int>& indices = pos[c];
            int m = indices.size();
            
            for (int i = 0; i < m; i++) {
                int left = (i == 0) ? indices[i] + 1 : indices[i] - indices[i - 1];
                int right = (i == m - 1) ? n - indices[i] : indices[i + 1] - indices[i];
                
                result += left * right;
            }
        }
        
        return result;          
    }
};
