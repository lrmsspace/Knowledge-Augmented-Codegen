// Source: https://leetcode.com/problems/split-with-minimum-sum/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer num, split it into two non-negative integers num1 and num2 such that:
//
//
// 	The concatenation of num1 and num2 is a permutation of num.
//
// 	
// 		In other words, the sum of the number of occurrences of each digit in num1 and num2 is equal to the number of occurrences of that digit in num.
// 	
// 	
// 	num1 and num2 can contain leading zeros.
//
//
// Return the minimum possible sum of num1 and num2.
//
// Example:
// Input: num = 4325
// Output: 59
// Explanation: We can split 4325 so that num1 is 24 and num2 is 35, giving a sum of 59. We can prove that 59 is indeed the minimal possible sum.
//
// Constraints:
// 10 <= num <= 109
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int splitNum(int num) {
        std::vector<int> digits;
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
        std::sort(digits.begin(), digits.end());

        int num1 = 0, num2 = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            if (i % 2 == 0) {
                num1 = num1 * 10 + digits[i];
            } else {
                num2 = num2 * 10 + digits[i];
            }
        }

        return num1 + num2;         
    }
};
