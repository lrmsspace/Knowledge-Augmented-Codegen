// Source: https://leetcode.com/problems/prime-palindrome/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the smallest prime palindrome greater than or equal to n.
//
// An integer is prime if it has exactly two divisors: 1 and itself. Note that 1 is not a prime number.
//
//
// 	For example, 2, 3, 5, 7, 11, and 13 are all primes.
//
//
// An integer is a palindrome if it reads the same from left to right as it does from right to left.
//
//
// 	For example, 101 and 12321 are palindromes.
//
//
// The test cases are generated so that the answer always exists and is in the range [2, 2 * 108].
//
// Example:
// Input: n = 6
// Output: 7
//
// Constraints:
// 1 <= n <= 108
//

class Solution {
public:
    int primePalindrome(int n) {
        if (n <= 2) return 2;
        if (n >= 8 && n <= 11) return 11;

        for (int length = 1; length <= 5; ++length) {
            for (int root = pow(10, length - 1); root < pow(10, length); ++root) {
                string s = to_string(root);
                string rs(s.rbegin(), s.rend() - 1);
                string palStr = s + rs;
                int pal = stoi(palStr);
                if (pal >= n && isPrime(pal)) {
                    return pal;
                }
            }
        }
        return -1; // Should never reach here based on problem constraints          
    }
};
