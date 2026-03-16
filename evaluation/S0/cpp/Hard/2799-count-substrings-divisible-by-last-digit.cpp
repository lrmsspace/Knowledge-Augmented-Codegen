// Source: https://leetcode.com/problems/count-substrings-divisible-by-last-digit/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of digits.
//
// Return the number of substrings of s divisible by their non-zero last digit.
//
// Note: A substring may contain leading zeros.
//
// Example:
// Input: s = "12936"
//
// Output: 11
//
// Explanation:
//
// Substrings "29", "129", "293" and "2936" are not divisible by their last digit. There are 15 substrings in total, so the answer is 15 - 4 = 11.
//
// Constraints:
// 1 <= s.length <= 105
//  s consists of digits only.
//

class Solution {
public:
    long long countSubstrings(string s) {
        long long result = 0;
        int n = s.size();
        
        for (int i = 0; i < n; i++) {
            int lastDigit = s[i] - '0';
            if (lastDigit == 0) continue;
            
            for (int j = 0; j <= i; j++) {
                string substring = s.substr(j, i - j + 1);
                long long num = stoll(substring);
                
                if (num % lastDigit == 0) {
                    result++;
                }
            }
        }
        
        return result;          
    }
};
