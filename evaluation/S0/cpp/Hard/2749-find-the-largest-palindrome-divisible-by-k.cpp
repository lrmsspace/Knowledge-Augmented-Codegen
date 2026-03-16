// Source: https://leetcode.com/problems/find-the-largest-palindrome-divisible-by-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers n and k.
//
// An integer x is called k-palindromic if:
//
//
// 	x is a palindrome.
// 	x is divisible by k.
//
//
// Return the largest integer having n digits (as a string) that is k-palindromic.
//
// Note that the integer must not have leading zeros.
//
// Example:
// Input: n = 3, k = 5
//
// Output: "595"
//
// Explanation:
//
// 595 is the largest k-palindromic integer with 3 digits.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= k <= 9
//

class Solution {
public:
    string largestPalindrome(int n, int k) {
        if (n == 1 && k <= 9) {
            return to_string(9 - (9 % k));
        }
        
        string half;
        for (int i = 0; i < (n + 1) / 2; i++) {
            half += '9';
        }
        
        long long halfNum = stoll(half);
        
        while (halfNum > 0) {
            string halfStr = to_string(halfNum);
            string revHalfStr = halfStr;
            reverse(revHalfStr.begin(), revHalfStr.end());
            
            string palinStr = halfStr;
            if (n % 2 == 1) {
                palinStr += revHalfStr.substr(1);
            } else {
                palinStr += revHalfStr;
            }
            
            long long palinNum = stoll(palinStr);
            if (palinNum % k == 0) {
                return palinStr;
            }
            
            halfNum--;
        }
        
        return "-1";            
    }
};
