// Source: https://leetcode.com/problems/minimum-window-substring/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".
//
// The testcases will be generated such that the answer is unique.
//
// Example:
// Input: s = "ADOBECODEBANC", t = "ABC"
// Output: "BANC"
// Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
//
// Constraints:
// m == s.length
// 	n == t.length
// 	1 <= m, n <= 105
// 	s and t consist of uppercase and lowercase English letters.
//
//
//  
// Follow up: Could you find an algorithm that runs in O(m + n) time?
//

/**
 * @param {string} s
 * @param {string} t
 * @return {string}
 */
var minWindow = function(s, t) {
    

    const need = new Map();
    for (const c of t) {
        need.set(c, (need.get(c) || 0) + 1);
    }

    let left = 0;
    let right = 0;
    let valid = 0;
    const window = new Map();
    let start = 0;
    let len = Infinity;
    while (right < s.length) {
        const c = s[right];
        right++;
        if (need.has(c)) {
            window.set(c, (window.get(c) || 0) + 1);    
            if (window.get(c) === need.get(c)) {
                valid++;
            }

        }
        while (valid === need.size) {   
            if (right - left < len) {
                start = left;
                len = right - left;
            }
            const d = s[left];  
            left++;
            if (need.has(d)) {  
                if (window.get(d) === need.get(d)) {
                    valid--;
                }
                window.set(d, window.get(d) - 1);
            }   
        }   
    }  
        
    return len === Infinity ? "" : s.substring(start, start + len);  
};
