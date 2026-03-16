// Source: https://leetcode.com/problems/integer-to-english-words/   |   Difficulty: Hard
//
// Problem Description:
// Convert a non-negative integer num to its English words representation.
//
// Example:
// Input: num = 123
// Output: "One Hundred Twenty Three"
//
// Constraints:
// 0 <= num <= 231 - 1
//

class Solution {
public:
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        
        vector<string> below20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
                                  "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen",
                                  "Eighteen", "Nineteen"};
        vector<string> tens = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        vector<string> thousands = {"", "Thousand", "Million", "Billion"};
        
        string result;
        int i = 0;
        
        while (num > 0) {
            if (num % 1000 != 0) {
                result = helper(num % 1000, below20, tens) + (thousands[i].empty() ? "" : " " + thousands[i]) + (result.empty() ? "" : " " + result);
            }
            num /= 1000;
            i++;
        }
        
        return result;          
    }
};
