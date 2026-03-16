// Source: https://leetcode.com/problems/sum-of-digits-of-string-after-convert/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting of lowercase English letters, and an integer k. Your task is to convert the string into an integer by a special process, and then transform it by summing its digits repeatedly k times. More specifically, perform the following steps:
//
//
// 	Convert s into an integer by replacing each letter with its position in the alphabet (i.e. replace 'a' with 1, 'b' with 2, ..., 'z' with 26).
// 	Transform the integer by replacing it with the sum of its digits.
// 	Repeat the transform operation (step 2) k times in total.
//
//
// For example, if s = "zbax" and k = 2, then the resulting integer would be 8 by the following operations:
//
//
// 	Convert: "zbax" ➝ "(26)(2)(1)(24)" ➝ "262124" ➝ 262124
// 	Transform #1: 262124 ➝ 2 + 6 + 2 + 1 + 2 + 4 ➝ 17
// 	Transform #2: 17 ➝ 1 + 7 ➝ 8
//
//
// Return the resulting integer after performing the operations described above.
//
// Example:
// Input: s = "iiii", k = 1
//
// Output: 36
//
// Explanation:
//
// The operations are as follows:
// - Convert: "iiii" ➝ "(9)(9)(9)(9)" ➝ "9999" ➝ 9999
// - Transform #1: 9999 ➝ 9 + 9 + 9 + 9 ➝ 36
// Thus the resulting integer is 36.
//
// Constraints:
// 1 <= s.length <= 100
// 	1 <= k <= 10
// 	s consists of lowercase English letters.
//

class Solution {
public:
    int getLucky(string s, int k) {
        int digitSum = 0;

        // Convert each character to its corresponding number and sum the digits
        for (char c : s) {
            int num = c - 'a' + 1; // Get the position in the alphabet
            while (num > 0) {
                digitSum += num % 10; // Add the last digit to the sum
                num /= 10; // Remove the last digit
            }
        }

        // Perform the transformation k-1 more times
        for (int i = 1; i < k; ++i) {
            int newSum = 0;
            while (digitSum > 0) {
                newSum += digitSum % 10; // Sum the digits of the current sum
                digitSum /= 10; // Remove the last digit
            }
            digitSum = newSum; // Update digitSum for the next iteration
        }

        return digitSum; // Return the final result         
    }
};
