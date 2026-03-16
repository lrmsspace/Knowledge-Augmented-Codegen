// Source: https://leetcode.com/problems/largest-multiple-of-three/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of digits digits, return the largest multiple of three that can be formed by concatenating some of the given digits in any order. If there is no answer return an empty string.
//
// Since the answer may not fit in an integer data type, return the answer as a string. Note that the returning answer must not contain unnecessary leading zeros.
//
// Example:
// Input: digits = [8,1,9]
// Output: "981"
//
// Constraints:
// 1 <= digits.length <= 104
// 	0 <= digits[i] <= 9
//

class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        vector<int> count(10, 0);
        int sum = 0;
        for (int d : digits) {
            count[d]++;
            sum += d;
        }
        
        auto removeDigits = [&](int mod, int cnt) {
            for (int i = mod; i <= 9 && cnt > 0; i += 3) {
                while (count[i] > 0 && cnt > 0) {
                    count[i]--;
                    cnt--;
                }
            }
            return cnt == 0;
        };
        
        int rem = sum % 3;
        if (rem != 0) {
            if (!removeDigits(rem, 1)) {
                if (!removeDigits(3 - rem, 2)) {
                    return "";
                }
            }
        }
        
        string result;
        for (int i = 9; i >= 0; i--) {
            result += string(count[i], '0' + i);
        }
        
        // Handle leading zeros
        if (!result.empty() && result[0] == '0') {
            return "0";
        }
        
        return result;          
    }
};
