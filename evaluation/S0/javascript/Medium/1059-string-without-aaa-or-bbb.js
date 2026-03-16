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

/**
 * @param {number} a
 * @param {number} b
 * @return {string}
 */
var strWithout3a3b = function(a, b) {
    
    let result = [];
    while (a > 0 || b > 0) {
        if (a > b) {    
            if (a > 1) {
                result.push('aa');
                a -= 2;
            } else {
                result.push('a');
                a -= 1;
            }   
            if (b > 0) {
                result.push('b');
                b -= 1;
            }

        } else if (b > a) {
            if (b > 1) {
                result.push('bb');
                b -= 2;
            }
            else {  
                result.push('b');
                b -= 1;
            }
            if (a > 0) {    


                result.push('a');                a -= 1;
            }
        } else {    
            if (a > 0) {
                result.push('a');
                a -= 1;
            }
            if (b > 0) {
                result.push('b');
                b -= 1;
            }

        }
    }
    return result.join(''); 
    
};
