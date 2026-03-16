// Source: https://leetcode.com/problems/odd-string-difference/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of equal-length strings words. Assume that the length of each string is n.
//
// Each string words[i] can be converted into a difference integer array difference[i] of length n - 1 where difference[i][j] = words[i][j+1] - words[i][j] where 0 <= j <= n - 2. Note that the difference between two letters is the difference between their positions in the alphabet i.e. the position of 'a' is 0, 'b' is 1, and 'z' is 25.
//
//
// 	For example, for the string "acb", the difference integer array is [2 - 0, 1 - 2] = [2, -1].
//
//
// All the strings in words have the same difference integer array, except one. You should find that string.
//
// Return the string in words that has different difference integer array.
//
// Example:
// Input: words = ["adc","wzy","abc"]
// Output: "abc"
// Explanation: 
// - The difference integer array of "adc" is [3 - 0, 2 - 3] = [3, -1].
// - The difference integer array of "wzy" is [25 - 22, 24 - 25]= [3, -1].
// - The difference integer array of "abc" is [1 - 0, 2 - 1] = [1, 1]. 
// The odd array out is [1, 1], so we return the corresponding string, "abc".
//
// Constraints:
// 3 <= words.length <= 100
// 	n == words[i].length
// 	2 <= n <= 20
// 	words[i] consists of lowercase English letters.
//

/**
 * @param {string[]} words
 * @return {string}
 */
var oddString = function(words) {
    const getDifferenceArray = (word) => {
        const diffArray = [];
        for (let i = 1; i < word.length; i++) {
            diffArray.push(word.charCodeAt(i) - word.charCodeAt(i - 1));
        }
        return diffArray;
    }
    const diffMap = new Map();
    for (const word of words) {
        const diffArray = getDifferenceArray(word).toString();
        if (!diffMap.has(diffArray)) {
            diffMap.set(diffArray, []);
        }
        diffMap.get(diffArray).push(word);
    }
    for (const [diffArray, wordList] of diffMap.entries()) {
        if (wordList.length === 1) {
            return wordList[0];
        }
    }
    return "";
};
