// Source: https://leetcode.com/problems/string-without-aaa-or-bbb/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers a and b, return any string s such that:
//
//
// 	s has length a + b and contains exactly a 'a' letters, and exactly b 'b' letters,
// 	The substring 'aaa' does not occur in s, and
// 	The substring 'bbb' does not occur in s.
//
// Example:
// Input: a = 1, b = 2
// Output: "abb"
// Explanation: "abb", "bab" and "bba" are all correct answers.
//
// Constraints:
// 0 <= a, b <= 100
// 	It is guaranteed such an s exists for the given a and b.
//

class Solution {
public:
    string strWithout3a3b(int a, int b) {
        string result;
        char charA = 'a';
        char charB = 'b';

        if (b > a) {
            swap(a, b);
            swap(charA, charB);
        }

        while (a > 0 || b > 0) {
            if (a > b) {
                result += charA;
                result += charA;
                a -= 2;
            } else {
                result += charA;
                a -= 1;
            }

            if (b > 0) {
                result += charB;
                b -= 1;
            }
        }

        return result;
    }
};
