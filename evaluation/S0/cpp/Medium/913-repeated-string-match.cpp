// Source: https://leetcode.com/problems/repeated-string-match/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings a and b, return the minimum number of times you should repeat string a so that string b is a substring of it. If it is impossible for b​​​​​​ to be a substring of a after repeating it, return -1.
//
// Notice: string "abc" repeated 0 times is "", repeated 1 time is "abc" and repeated 2 times is "abcabc".
//
// Example:
// Input: a = "abcd", b = "cdabcdab"
// Output: 3
// Explanation: We return 3 because by repeating a three times "abcdabcdabcd", b is a substring of it.
//
// Constraints:
// 1 <= a.length, b.length <= 104
// 	a and b consist of lowercase English letters.
//

class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        int count = 0;
        string repeatedA;
        
        while (repeatedA.length() < b.length()) {
            repeatedA += a;
            count++;
        }
        
        if (repeatedA.find(b) != string::npos) {
            return count;
        }
        
        repeatedA += a;
        count++;
        
        if (repeatedA.find(b) != string::npos) {
            return count;
        }
        
        return -1;          
    }
};
