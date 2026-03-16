// Source: https://leetcode.com/problems/number-of-digit-one/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
//
// Example:
// Input: n = 13
// Output: 6
//
// Constraints:
// 0 <= n <= 109
//

class Solution {
public:
    int countDigitOne(int n) {
        long long count = 0;
        long long factor = 1;
        
        while (factor <= n) {
            long long lower = n - (n / factor) * factor;
            long long curr = (n / factor) % 10;
            long long higher = n / (factor * 10);
            
            if (curr == 0) {
                count += higher * factor;
            } else if (curr == 1) {
                count += higher * factor + lower + 1;
            } else {
                count += (higher + 1) * factor;
            }
            
            factor *= 10;
        }
        
        return (int)count;          
    }
};
