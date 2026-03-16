// Source: https://leetcode.com/problems/largest-palindrome-product/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, return the largest palindromic integer that can be represented as the product of two n-digits integers. Since the answer can be very large, return it modulo 1337.
//
// Example:
// Input: n = 2
// Output: 987
// Explanation: 99 x 91 = 9009, 9009 % 1337 = 987
//
// Constraints:
// 1 <= n <= 8
//

class Solution {
public:
    int largestPalindrome(int n) {
        if (n == 1) return 9;
        
        long long upper = 1;
        for (int i = 0; i < n; i++) {
            upper *= 10;
        }
        upper -= 1;
        long long lower = upper / 10 + 1;
        
        for (long long firstHalf = upper; firstHalf >= lower; firstHalf--) {
            // Construct palindrome
            string strHalf = to_string(firstHalf);
            string revHalf = strHalf;
            reverse(revHalf.begin(), revHalf.end());
            string palinStr = strHalf + revHalf;
            long long palinNum = stoll(palinStr);
            
            // Check if it can be factored into two n-digit numbers
            for (long long i = upper; i * i >= palinNum; i--) {
                if (palinNum % i == 0) {
                    long long otherFactor = palinNum / i;
                    if (otherFactor >= lower && otherFactor <= upper) {
                        return palinNum % 1337;
                    }
                }
            }
        }
        
        return -1; // Should not reach here         
    }
};
