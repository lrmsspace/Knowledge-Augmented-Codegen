// Source: https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s consisting of digits. Perform the following operation repeatedly until the string has exactly two digits:
//
//
// 	For each pair of consecutive digits in s, starting from the first digit, calculate a new digit as the sum of the two digits modulo 10.
// 	Replace s with the sequence of newly calculated digits, maintaining the order in which they are computed.
//
//
// Return true if the final two digits in s are the same; otherwise, return false.
//
// Example:
// Input: s = "3902"
//
// Output: true
//
// Explanation:
//
//
// 	Initially, s = "3902"
// 	First operation:
// 	
// 		(s[0] + s[1]) % 10 = (3 + 9) % 10 = 2
// 		(s[1] + s[2]) % 10 = (9 + 0) % 10 = 9
// 		(s[2] + s[3]) % 10 = (0 + 2) % 10 = 2
// 		s becomes "292"
// 	
// 	
// 	Second operation:
// 	
// 		(s[0] + s[1]) % 10 = (2 + 9) % 10 = 1
// 		(s[1] + s[2]) % 10 = (9 + 2) % 10 = 1
// 		s becomes "11"
// 	
// 	
// 	Since the digits in "11" are the same, the output is true.
//
// Constraints:
// 3 <= s.length <= 105
// 	s consists of only digits.
//

class Solution {
    public boolean hasSameDigits(String s) {
        int n = s.length();
        int[] fact = new int[n];
        fact[0] = 1;
        for (int i = 1; i < n; i++) {
            fact[i] = (fact[i - 1] * i) % 10;
        }

        int[] invFact = new int[n];
        invFact[n - 1] = modInverse(fact[n - 1], 10);
        for (int i = n - 2; i >= 0; i--) {
            invFact[i] = (invFact[i + 1] * (i + 1)) % 10;
        }

        int[] coeffs = new int[n];
        for (int i = 0; i < n; i++) {
            coeffs[i] = (((fact[n - 2] * invFact[i]) % 10) * invFact[n - 2 - i]) % 10;
        }

        int result = 0;
        for (int i = 0; i < n; i++) {
            result = (result + (Character.getNumericValue(s.charAt(i)) * coeffs[i]) % 10) % 10;
        }

        return result % 10 == (result / 10) % 10;           
    }
}
