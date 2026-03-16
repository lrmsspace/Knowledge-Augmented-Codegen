// Source: https://leetcode.com/problems/additive-number/   |   Difficulty: Medium
//
// Problem Description:
// An additive number is a string whose digits can form an additive sequence.
//
// A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.
//
// Given a string containing only digits, return true if it is an additive number or false otherwise.
//
// Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.
//
// Example:
// Input: "112358"
// Output: true
// Explanation: 
// The digits can form an additive sequence: 1, 1, 2, 3, 5, 8. 
// 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
//
// Constraints:
// 1 <= num.length <= 35
// 	num consists only of digits.
//
//
//  
// Follow up: How would you handle overflow for very large input integers?
//

bool isAdditiveNumber(char* num) {
    int n = strlen(num);
    for (int i = 1; i <= n / 2; ++i) {
        if (num[0] == '0' && i > 1) break;
        for (int j = 1; j <= (n - i) / 2; ++j) {
            if (num[i] == '0' && j > 1) break;
            int start1 = 0, len1 = i;
            int start2 = i, len2 = j;
            int start3 = i + j, len3 = 0;
            while (start3 < n) {
                len3 = 0;
                int carry = 0;
                for (int p = len1 - 1, q = len2 - 1; p >= 0 || q >= 0 || carry; --p, --q) {
                    int digit1 = p >= 0 ? num[start1 + p] - '0' : 0;
                    int digit2 = q >= 0 ? num[start2 + q] - '0' : 0;
                    int sum = digit1 + digit2 + carry;
                    int digit3 = sum % 10;
                    carry = sum / 10;
                    if (start3 + len3 >= n || num[start3 + len3] - '0' != digit3) break;
                    ++len3;
                }
                if (carry) {
                    if (start3 + len3 >= n || num[start3 + len3] - '0' != carry) break;
                    ++len3;
                }
                if (start3 + len3 > n) break;
                start1 = start2;
                len1 = len2;
                start2 = start3;
                len2 = len3;
                start3 += len3;
            }
            if (start3 == n) return true;
        }
    }
    return false;       
}
