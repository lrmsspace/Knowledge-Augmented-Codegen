// Source: https://leetcode.com/problems/remove-k-digits/   |   Difficulty: Medium
//
// Problem Description:
// Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.
//
// Example:
// Input: num = "1432219", k = 3
// Output: "1219"
// Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
//
// Constraints:
// 1 <= k <= num.length <= 105
// 	num consists of only digits.
// 	num does not have any leading zeros except for the zero itself.
//

class Solution {
public:
    string removeKdigits(string num, int k) {
        string result;
        for (char digit : num) {
            while (!result.empty() && k > 0 && result.back() > digit) {
                result.pop_back();
                k--;
            }
            result.push_back(digit);
        }
        
        // If k is still greater than 0, remove from the end
        while (k > 0 && !result.empty()) {
            result.pop_back();
            k--;
        }
        
        // Remove leading zeros
        int nonZeroIndex = 0;
        while (nonZeroIndex < result.size() && result[nonZeroIndex] == '0') {
            nonZeroIndex++;
        }
        
        result = result.substr(nonZeroIndex);
        
        return result.empty() ? "0" : result;           
    }
};
