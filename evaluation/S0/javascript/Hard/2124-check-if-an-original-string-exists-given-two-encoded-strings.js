// Source: https://leetcode.com/problems/check-if-an-original-string-exists-given-two-encoded-strings/   |   Difficulty: Hard
//
// Problem Description:
// An original string, consisting of lowercase English letters, can be encoded by the following steps:
//
//
// 	Arbitrarily split it into a sequence of some number of non-empty substrings.
// 	Arbitrarily choose some elements (possibly none) of the sequence, and replace each with its length (as a numeric string).
// 	Concatenate the sequence as the encoded string.
//
//
// For example, one way to encode an original string "abcdefghijklmnop" might be:
//
//
// 	Split it as a sequence: ["ab", "cdefghijklmn", "o", "p"].
// 	Choose the second and third elements to be replaced by their lengths, respectively. The sequence becomes ["ab", "12", "1", "p"].
// 	Concatenate the elements of the sequence to get the encoded string: "ab121p".
//
//
// Given two encoded strings s1 and s2, consisting of lowercase English letters and digits 1-9 (inclusive), return true if there exists an original string that could be encoded as both s1 and s2. Otherwise, return false.
//
// Note: The test cases are generated such that the number of consecutive digits in s1 and s2 does not exceed 3.
//
// Example:
// Input: s1 = "internationalization", s2 = "i18n"
// Output: true
// Explanation: It is possible that "internationalization" was the original string.
// - "internationalization" 
//   -> Split:       ["internationalization"]
//   -> Do not replace any element
//   -> Concatenate:  "internationalization", which is s1.
// - "internationalization"
//   -> Split:       ["i", "nternationalizatio", "n"]
//   -> Replace:     ["i", "18",                 "n"]
//   -> Concatenate:  "i18n", which is s2
//
// Constraints:
// 1 <= s1.length, s2.length <= 40
// 	s1 and s2 consist of digits 1-9 (inclusive), and lowercase English letters only.
// 	The number of consecutive digits in s1 and s2 does not exceed 3.
//

/**
 * @param {string} s1
 * @param {string} s2
 * @return {boolean}
 */
var possiblyEquals = function(s1, s2) {
    const memo = new Map();
    const dfs = (i, j, diff) => {
        const key = `${i},${j},${diff}`;
        if (memo.has(key)) {
            return memo.get(key);
        }
        if (i === s1.length && j === s2.length) {
            return diff === 0;
        }
        if (i < s1.length && j < s2.length && diff === 0 && s1[i] === s2[j]) {
            if (dfs(i + 1, j + 1, diff)) {
                memo.set(key, true);
                return true;
            }
        }
        if (i < s1.length && s1[i] >= '1' && s1[i] <= '9') {
            let num = 0;
            for (let k = i; k < Math.min(i + 3, s1.length) && s1[k] >= '1' && s1[k] <= '9'; k++) {
                num = num * 10 + (s1[k] - '0');
                if (dfs(k + 1, j, diff + num)) {
                    memo.set(key, true);
                    return true;
                }
            }
        }
        if (j < s2.length && s2[j] >= '1' && s2[j] <= '9') {
            let num = 0;
            for (let k = j; k < Math.min(j + 3, s2.length) && s2[k] >= '1' && s2[k] <= '9'; k++) {
                num = num * 10 + (s2[k] - '0');
                if (dfs(i, k + 1, diff - num)) {
                    memo.set(key, true);
                    return true;
                }
            }
        }
        memo.set(key, false);
        return false;
    }
    return dfs(0, 0, 0);
};
