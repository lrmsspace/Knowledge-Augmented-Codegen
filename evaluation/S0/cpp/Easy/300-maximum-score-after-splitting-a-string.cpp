// Source: https://leetcode.com/problems/maximum-score-after-splitting-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s of zeros and ones, return the maximum score after splitting the string into two non-empty substrings (i.e. left substring and right substring).
//
// The score after splitting a string is the number of zeros in the left substring plus the number of ones in the right substring.
//
// Example:
// Input: s = "011101"
// Output: 5 
// Explanation: 
// All possible ways of splitting s into two non-empty substrings are:
// left = "0" and right = "11101", score = 1 + 4 = 5 
// left = "01" and right = "1101", score = 1 + 3 = 4 
// left = "011" and right = "101", score = 1 + 2 = 3 
// left = "0111" and right = "01", score = 1 + 1 = 2 
// left = "01110" and right = "1", score = 2 + 1 = 3
//
// Constraints:
// 2 <= s.length <= 500
// 	The string s consists of characters '0' and '1' only.
//

class Solution {
public:
    int maxScore(string s) {
        int max_score = 0;
        int n = s.size();
        
        for (int i = 1; i < n; ++i) {
            int left_zeros = 0;
            int right_ones = 0;
            
            for (int j = 0; j < i; ++j) {
                if (s[j] == '0') {
                    ++left_zeros;
                }
            }
            
            for (int j = i; j < n; ++j) {
                if (s[j] == '1') {
                    ++right_ones;
                }
            }
            
            int current_score = left_zeros + right_ones;
            max_score = max(max_score, current_score);
        }
        
        return max_score;           
    }
};
