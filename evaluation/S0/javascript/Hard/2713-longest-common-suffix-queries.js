// Source: https://leetcode.com/problems/longest-common-suffix-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays of strings wordsContainer and wordsQuery.
//
// For each wordsQuery[i], you need to find a string from wordsContainer that has the longest common suffix with wordsQuery[i]. If there are two or more strings in wordsContainer that share the longest common suffix, find the string that is the smallest in length. If there are two or more such strings that have the same smallest length, find the one that occurred earlier in wordsContainer.
//
// Return an array of integers ans, where ans[i] is the index of the string in wordsContainer that has the longest common suffix with wordsQuery[i].
//
// Example:
// Input: wordsContainer = ["abcd","bcd","xbcd"], wordsQuery = ["cd","bcd","xyz"]
//
// Output: [1,1,1]
//
// Explanation:
//
// Let's look at each wordsQuery[i] separately:
//
//
// 	For wordsQuery[0] = "cd", strings from wordsContainer that share the longest common suffix "cd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// 	For wordsQuery[1] = "bcd", strings from wordsContainer that share the longest common suffix "bcd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// 	For wordsQuery[2] = "xyz", there is no string from wordsContainer that shares a common suffix. Hence the longest common suffix is "", that is shared with strings at index 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
//
// Constraints:
// 1 <= wordsContainer.length, wordsQuery.length <= 104
// 	1 <= wordsContainer[i].length <= 5 * 103
// 	1 <= wordsQuery[i].length <= 5 * 103
// 	wordsContainer[i] consists only of lowercase English letters.
// 	wordsQuery[i] consists only of lowercase English letters.
// 	Sum of wordsContainer[i].length is at most 5 * 105.
// 	Sum of wordsQuery[i].length is at most 5 * 105.
//

/**
 * @param {string[]} wordsContainer
 * @param {string[]} wordsQuery
 * @return {number[]}
 */
var stringIndices = function(wordsContainer, wordsQuery) {
    const n = wordsContainer.length;
    const m = wordsQuery.length;
    const result = new Array(m).fill(0);
    for (let i = 0; i < m; i++) {
        let maxSuffixLength = 0;
        let minLength = Infinity;
        let index = -1;
        for (let j = 0; j < n; j++) {
            const suffixLength = getCommonSuffixLength(wordsContainer[j], wordsQuery[i]);
            if (suffixLength > maxSuffixLength || (suffixLength === maxSuffixLength && wordsContainer[j].length < minLength)) {
                maxSuffixLength = suffixLength;
                minLength = wordsContainer[j].length;
                index = j;
            }
        }
        result[i] = index;
    }
    return result;  
};
