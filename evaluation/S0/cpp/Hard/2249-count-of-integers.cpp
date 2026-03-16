// Source: https://leetcode.com/problems/count-of-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given two numeric strings num1 and num2 and two integers max_sum and min_sum. We denote an integer x to be good if:
//
//
// 	num1 <= x <= num2
// 	min_sum <= digit_sum(x) <= max_sum.
//
//
// Return the number of good integers. Since the answer may be large, return it modulo 109 + 7.
//
// Note that digit_sum(x) denotes the sum of the digits of x.
//
// Example:
// Input: num1 = "1", num2 = "12", min_sum = 1, max_sum = 8
// Output: 11
// Explanation: There are 11 integers whose sum of digits lies between 1 and 8 are 1,2,3,4,5,6,7,8,10,11, and 12. Thus, we return 11.
//
// Constraints:
// 1 <= num1 <= num2 <= 1022
// 	1 <= min_sum <= max_sum <= 400
//

class Solution {
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        const int MOD = 1e9 + 7;
        int n1 = num1.size();
        int n2 = num2.size();
        
        // dp[pos][sum][is_tight]
        auto dp_func = [&](const string& num, auto&& self, int pos, int sum, bool is_tight) -> int {
            if (pos == num.size()) {
                return (sum >= min_sum && sum <= max_sum) ? 1 : 0;
            }
            
            int limit = is_tight ? (num[pos] - '0') : 9;
            int res = 0;
            
            for (int digit = 0; digit <= limit; digit++) {
                res = (res + self(num, self, pos + 1, sum + digit, is_tight && (digit == limit))) % MOD;
            }
            
            return res;
        };
        
        int count_up_to_num2 = dp_func(num2, dp_func, 0, 0, true);
        int count_up_to_num1_minus_1 = dp_func(num1, dp_func, 0, 0, true);
        
        // Check if num1 itself is a good integer
        int digit_sum_num1 = 0;
        for (char c : num1) {
            digit_sum_num1 += (c - '0');
        }
        int is_num1_good = (digit_sum_num1 >= min_sum && digit_sum_num1 <= max_sum) ? 1 : 0;
        
        int result = (count_up_to_num2 - count_up_to_num1_minus_1 + is_num1_good + MOD) % MOD;
        
        return result;          
    }
};
