// Source: https://leetcode.com/problems/numbers-with-repeated-digits/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, return the number of positive integers in the range [1, n] that have at least one repeated digit.
//
// Example:
// Input: n = 20
// Output: 1
// Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
//
// Constraints:
// 1 <= n <= 109
//

class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        vector<int> digits;
        int x = n + 1;
        while (x > 0) {
            digits.push_back(x % 10);
            x /= 10;
        }
        reverse(digits.begin(), digits.end());
        
        int len = digits.size();
        int res = 0;
        
        // Count numbers with unique digits and length < len
        for (int l = 1; l < len; l++) {
            int count = 9;
            for (int i = 1; i < l; i++) {
                count *= (10 - i);
            }
            res += count;
        }
        
        // Count numbers with unique digits and length == len
        unordered_set<int> used;
        for (int i = 0; i < len; i++) {
            for (int d = (i == 0 ? 1 : 0); d < digits[i]; d++) {
                if (used.find(d) == used.end()) {
                    int count = 1;
                    for (int j = i + 1; j < len; j++) {
                        count *= (10 - used.size() - 1 - (j - i - 1));
                    }
                    res += count;
                }
            }
            if (used.find(digits[i]) != used.end()) {
                break;
            }
            used.insert(digits[i]);
            if (i == len - 1) {
                res += 1; // Count n itself if all digits are unique
            }
        }
        
        return n - res;         
    }
};
