// Source: https://leetcode.com/problems/minimum-sum-of-four-digit-number-after-splitting-digits/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer num consisting of exactly four digits. Split num into two new integers new1 and new2 by using the digits found in num. Leading zeros are allowed in new1 and new2, and all the digits found in num must be used.
//
//
// 	For example, given num = 2932, you have the following digits: two 2's, one 9 and one 3. Some of the possible pairs [new1, new2] are [22, 93], [23, 92], [223, 9] and [2, 329].
//
//
// Return the minimum possible sum of new1 and new2.
//
// Example:
// Input: num = 2932
// Output: 52
// Explanation: Some possible pairs [new1, new2] are [29, 23], [223, 9], etc.
// The minimum sum can be obtained by the pair [29, 23]: 29 + 23 = 52.
//
// Constraints:
// 1000 <= num <= 9999
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumSum(int num) {
        // Convert the number to a vector of its digits
        vector<int> digits;
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }

        // Sort the digits in ascending order
        sort(digits.begin(), digits.end());

        // Form the two new numbers from the sorted digits
        int new1 = digits[0] * 10 + digits[2]; // Smallest and third smallest
        int new2 = digits[1] * 10 + digits[3]; // Second smallest and largest

        // Return the sum of the two new numbers
        return new1 + new2;         
    }
};
