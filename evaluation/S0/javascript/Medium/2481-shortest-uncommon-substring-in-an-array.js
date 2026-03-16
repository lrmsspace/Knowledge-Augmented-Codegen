// Source: https://leetcode.com/problems/shortest-uncommon-substring-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array arr of size n consisting of non-empty strings.
//
// Find a string array answer of size n such that:
//
//
// 	answer[i] is the shortest substring of arr[i] that does not occur as a substring in any other string in arr. If multiple such substrings exist, answer[i] should be the lexicographically smallest. And if no such substring exists, answer[i] should be an empty string.
//
//
// Return the array answer.
//
// Example:
// Input: arr = ["cab","ad","bad","c"]
// Output: ["ab","","ba",""]
// Explanation: We have the following:
// - For the string "cab", the shortest substring that does not occur in any other string is either "ca" or "ab", we choose the lexicographically smaller substring, which is "ab".
// - For the string "ad", there is no substring that does not occur in any other string.
// - For the string "bad", the shortest substring that does not occur in any other string is "ba".
// - For the string "c", there is no substring that does not occur in any other string.
//
// Constraints:
// n == arr.length
// 	2 <= n <= 100
// 	1 <= arr[i].length <= 20
// 	arr[i] consists only of lowercase English letters.
//

/**
 * @param {string[]} arr
 * @return {string[]}
 */
var shortestSubstrings = function(arr) {
    const n = arr.length;
    const result = new Array(n).fill("");
    const substrMap = new Map();
    for (let i = 0; i < n; i++) {
        const str = arr[i];
        const len = str.length; 
        for (let start = 0; start < len; start++) {
            for (let end = start + 1; end <= len; end++) {
                const substr = str.slice(start, end);
                if (!substrMap.has(substr)) {
                    substrMap.set(substr, new Set());
                }
                substrMap.get(substr).add(i);
            }
        }
    }
    for (let i = 0; i < n; i++) {
        const str = arr[i];
        const len = str.length;
        let shortest = null;
        for (let start = 0; start < len; start++) {                                         
            for (let end = start + 1; end <= len; end++) {
                const substr = str.slice(start, end);
                if (substrMap.get(substr).size === 1) {
                    if (shortest === null || substr.length < shortest.length || (substr.length === shortest.length && substr < shortest)) {
                        shortest = substr;
                    }
                }
            }
        }
        result[i] = shortest === null ? "" : shortest;
    }
    return result;  
};
