// Source: https://leetcode.com/problems/shortest-string-that-contains-three-strings/   |   Difficulty: Medium
//
// Problem Description:
// Given three strings a, b, and c, your task is to find a string that has the minimum length and contains all three strings as substrings.
// If there are multiple such strings, return the lexicographically smallest one.
//
// Return a string denoting the answer to the problem.
//
// Notes
//
//
// 	A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b.
// 	A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: a = "abc", b = "bca", c = "aaa"
// Output: "aaabca"
// Explanation:  We show that "aaabca" contains all the given strings: a = ans[2...4], b = ans[3..5], c = ans[0..2]. It can be shown that the length of the resulting string would be at least 6 and "aaabca" is the lexicographically smallest one.
//
// Constraints:
// 1 <= a.length, b.length, c.length <= 100
// 	a, b, c consist only of lowercase English letters.
//

/**
 * @param {string} a
 * @param {string} b
 * @param {string} c
 * @return {string}
 */
var minimumString = function(a, b, c) {
    const merge = (s1, s2) => {
        for (let i = 0; i <= s1.length; i++) {
            if (s2.startsWith(s1.slice(i))) {
                return s1 + s2.slice(s1.length - i);
            }
        }
        return s1 + s2;
    };
    const candidates = [];
    const strings = [a, b, c];
    const permute = (arr, l, r) => {
        if (l === r) {
            let merged = merge(arr[0], arr[1]);
            merged = merge(merged, arr[2]);
            candidates.push(merged);
        }
        for (let i = l; i <= r; i++) {
            [arr[l], arr[i]] = [arr[i], arr[l]];
            permute(arr, l + 1, r);
            [arr[l], arr[i]] = [arr[i], arr[l]];
        }
    };
    permute(strings, 0, 2);
    candidates.sort((s1, s2) => {
        if (s1.length !== s2.length) {
            return s1.length - s2.length;
        }
        return s1.localeCompare(s2);
    }                           
    );
    return candidates[0];
};  

