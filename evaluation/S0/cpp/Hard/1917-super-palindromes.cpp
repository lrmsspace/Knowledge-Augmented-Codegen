// Source: https://leetcode.com/problems/super-palindromes/   |   Difficulty: Hard
//
// Problem Description:
// Let's say a positive integer is a super-palindrome if it is a palindrome, and it is also the square of a palindrome.
//
// Given two positive integers left and right represented as strings, return the number of super-palindromes integers in the inclusive range [left, right].
//
// Example:
// Input: left = "4", right = "1000"
// Output: 4
// Explanation: 4, 9, 121, and 484 are superpalindromes.
// Note that 676 is not a superpalindrome: 26 * 26 = 676, but 26 is not a palindrome.
//
// Constraints:
// 1 <= left.length, right.length <= 18
// 	left and right consist of only digits.
// 	left and right cannot have leading zeros.
// 	left and right represent integers in the range [1, 1018 - 1].
// 	left is less than or equal to right.
//

class Solution {
public:
    int superpalindromesInRange(string left, string right) {
        long long l = stoll(left);
        long long r = stoll(right);
        int count = 0;

        // Generate palindromic roots
        for (int len = 1; len <= 9; ++len) {
            // Odd length palindromes
            for (int half = pow(10, (len - 1) / 2); half < pow(10, (len + 1) / 2); ++half) {
                string halfStr = to_string(half);
                string revHalfStr = halfStr;
                reverse(revHalfStr.begin(), revHalfStr.end());
                string palinStr = halfStr + revHalfStr.substr(1);
                long long palinRoot = stoll(palinStr);
                long long palinSquare = palinRoot * palinRoot;
                if (palinSquare > r) break;
                if (palinSquare >= l && isPalindrome(to_string(palinSquare))) {
                    count++;
                }
            }

            // Even length palindromes
            for (int half = pow(10, len / 2 - 1); half < pow(10, len / 2); ++half) {
                string halfStr = to_string(half);
                string revHalfStr = halfStr;
                reverse(revHalfStr.begin(), revHalfStr.end());
                string palinStr = halfStr + revHalfStr;
                long long palinRoot = stoll(palinStr);
                long long palinSquare = palinRoot * palinRoot;
                if (palinSquare > r) break;
                if (palinSquare >= l && isPalindrome(to_string(palinSquare))) {
                    count++;
                }
            }
        }

        return count;           
    }
};
