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

int maxScore(char* s) {
    int max_score = 0;
    int n = 0, m = 0; // n: number of '0's in left substring, m: number of '1's in right substring

    // Count total number of '1's in the string
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '1') {
            m++;
        }
    }

    // Iterate through the string to find the maximum score
    for (int i = 0; s[i] != '\0' && s[i + 1] != '\0'; i++) {
        if (s[i] == '0') {
            n++;
        } else {
            m--;
        }
        int current_score = n + m;
        if (current_score > max_score) {
            max_score = current_score;
        }
    }

    return max_score;       
}
