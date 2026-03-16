// Source: https://leetcode.com/problems/construct-string-with-repeat-limit/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and an integer repeatLimit. Construct a new string repeatLimitedString using the characters of s such that no letter appears more than repeatLimit times in a row. You do not have to use all characters from s.
//
// Return the lexicographically largest repeatLimitedString possible.
//
// A string a is lexicographically larger than a string b if in the first position where a and b differ, string a has a letter that appears later in the alphabet than the corresponding letter in b. If the first min(a.length, b.length) characters do not differ, then the longer string is the lexicographically larger one.
//
// Example:
// Input: s = "cczazcc", repeatLimit = 3
// Output: "zzcccac"
// Explanation: We use all of the characters from s to construct the repeatLimitedString "zzcccac".
// The letter 'a' appears at most 1 time in a row.
// The letter 'c' appears at most 3 times in a row.
// The letter 'z' appears at most 2 times in a row.
// Hence, no letter appears more than repeatLimit times in a row and the string is a valid repeatLimitedString.
// The string is the lexicographically largest repeatLimitedString possible so we return "zzcccac".
// Note that the string "zzcccca" is lexicographically larger but the letter 'c' appears more than 3 times in a row, so it is not a valid repeatLimitedString.
//
// Constraints:
// 1 <= repeatLimit <= s.length <= 105
// 	s consists of lowercase English letters.
//

/**
 * @param {string} s
 * @param {number} repeatLimit
 * @return {string}
 */
var repeatLimitedString = function(s, repeatLimit) {
    const charCount = new Array(26).fill(0);
    for (const char of s) {
        charCount[char.charCodeAt(0) - 97]++;
    }
    let result = '';
    while (true) {
        let added = false;
        for (let i = 25; i >= 0; i--) {
            if (charCount[i] === 0) continue;
            const char = String.fromCharCode(i + 97);
            const useCount = Math.min(charCount[i], repeatLimit);
            result += char.repeat(useCount);
            charCount[i] -= useCount;
            added = true;
            if (charCount[i] > 0) {
                let j = i - 1;
                while (j >= 0 && charCount[j] === 0) {
                    j--;
                }
                if (j < 0) {
                    return result;
                }
                const nextChar = String.fromCharCode(j + 97);
                result += nextChar;
                charCount[j]--;
            }
            break;
        }
        if (!added) {
            break;
        }
    }
    return result;  
};
