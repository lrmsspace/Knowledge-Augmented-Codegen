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



char * strWithout3a3b(int a, int b){
    int total = a + b;
    char *result = (char *)malloc((total + 1) * sizeof(char));
    int index = 0;

    while (a > 0 || b > 0) {
        if (a > b) {
            if (a >= 2) {
                result[index++] = 'a';
                result[index++] = 'a';
                a -= 2;
            } else {
                result[index++] = 'a';
                a--;
            }
            if (b > 0) {
                result[index++] = 'b';
                b--;
            }
        } else if (b > a) {
            if (b >= 2) {
                result[index++] = 'b';
                result[index++] = 'b';
                b -= 2;
            } else {
                result[index++] = 'b';
                b--;
            }
            if (a > 0) {
                result[index++] = 'a';
                a--;
            }
        } else { // a == b
            if (a > 0) {
                result[index++] = 'a';
                a--;
            }
            if (b > 0) {
                result[index++] = 'b';
                b--;
            }
        }
    }

    result[index] = '\0';
    return result;
}
