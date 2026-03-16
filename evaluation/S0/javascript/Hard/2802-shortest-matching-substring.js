// Source: https://leetcode.com/problems/shortest-matching-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and a pattern string p, where p contains exactly two '*' characters.
//
// The '*' in p matches any sequence of zero or more characters.
//
// Return the length of the shortest substring in s that matches p. If there is no such substring, return -1.
// Note: The empty substring is considered valid.
//
// Example:
// Input: s = "abaacbaecebce", p = "ba*c*ce"
//
// Output: 8
//
// Explanation:
//
// The shortest matching substring of p in s is "baecebce".
//
// Constraints:
// 1 <= s.length <= 105
// 	2 <= p.length <= 105
// 	s contains only lowercase English letters.
// 	p contains only lowercase English letters and exactly two '*'.
//

/**
 * @param {string} s
 * @param {string} p
 * @return {number}
 */
var shortestMatchingSubstring = function(s, p) {
    const n = s.length;
    const parts = p.split('*');
    const firstPart = parts[0];
    const secondPart = parts[1];
    const thirdPart = parts[2];
    const m1 = firstPart.length;
    const m2 = secondPart.length;
    const m3 = thirdPart.length;
    let minLength = Infinity;
    for (let i = 0; i <= n - m1; i++) {
        if (s.substr(i, m1) === firstPart) {
            for (let j = i + m1; j <= n - m3; j++) {
                if (s.substr(j, m3) === thirdPart) {
                    let k = j + m3;
                    let found = false;
                    while (k <= n - m2) {
                        if (s.substr(k, m2) === secondPart) {
                            found = true;
                            break;
                        }
                        k++;
                    }
                    if (found) {
                        const currentLength = k + m2 - i;
                        minLength = Math.min(minLength, currentLength);
                    }
                }
            }
        }
    }
    return minLength === Infinity ? -1 : minLength; 
};
