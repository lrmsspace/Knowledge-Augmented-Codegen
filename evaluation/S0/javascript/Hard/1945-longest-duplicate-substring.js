// Source: https://leetcode.com/problems/longest-duplicate-substring/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s, consider all duplicated substrings: (contiguous) substrings of s that occur 2 or more times. The occurrences may overlap.
//
// Return any duplicated substring that has the longest possible length. If s does not have a duplicated substring, the answer is "".
//
// Example:
// Input: s = "banana"
// Output: "ana"
//
// Constraints:
// 2 <= s.length <= 3 * 104
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @return {string}
 */
var longestDupSubstring = function(s) {
    const n = s.length;
    const mod = 2 ** 31 - 1;
    const base = 26;
    const charToInt = (char) => char.charCodeAt(0) - 'a'.charCodeAt(0);

    const search = (length) => {
        let hash = 0;
        for (let i = 0; i < length; i++) {
            hash = (hash * base + charToInt(s[i])) % mod;
        }
        const seen = new Set([hash]);
        const baseL = Math.pow(base, length) % mod;
        for (let i = length; i < n; i++) {
            hash = (hash * base - charToInt(s[i - length]) * baseL + charToInt(s[i])) % mod;
            if (seen.has(hash)) {
                return i - length + 1;
            }
            seen.add(hash);
        }
        return -1;
    };

    let left = 1;
    let right = n;
    let start = -1;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        const idx = search(mid);
        if (idx !== -1) {
            left = mid + 1;
            start = idx;
        } else {
            right = mid - 1;
        }
    }
    return start !== -1 ? s.substring(start, start + left - 1) : "";    
};
