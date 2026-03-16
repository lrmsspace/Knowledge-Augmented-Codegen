// Source: https://leetcode.com/problems/palindrome-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of unique strings words.
//
// A palindrome pair is a pair of integers (i, j) such that:
//
//
//  0 <= i, j < words.length,
//  i != j, and
//  words[i] + words[j] (the concatenation of the two strings) is a palindrome.
//
//
// Return an array of all the palindrome pairs of words.
//
// You must write an algorithm with O(sum of words[i].length) runtime complexity.
//
// Example:
// Input: words = ["abcd","dcba","lls","s","sssll"]
// Output: [[0,1],[1,0],[3,2],[2,4]]
// Explanation: The palindromes are ["abcddcba","dcbaabcd","slls","llssssll"]
//
// Constraints:
// 1 <= words.length <= 5000
//  0 <= words[i].length <= 300
//  words[i] consists of lowercase English letters.
//

/**
 * @param {string[]} words
 * @return {number[][]}
 */
var palindromePairs = function(words) {
    const wordMap = new Map();
    for (let i = 0; i < words.length; i++) {
        wordMap.set(words[i], i);
    }
    const result = [];
    for (let i = 0; i < words.length; i++) {
        const word = words[i];
        const rev = word.split('').reverse().join('');
        if (wordMap.has(rev) && wordMap.get(rev) !== i) {
            result.push([i, wordMap.get(rev)]);
        }
        for (let j = 1; j < word.length; j++) {
            const left = word.substring(0, j);
            const right = word.substring(j);
            const revLeft = left.split('').reverse().join('');
            const revRight = right.split('').reverse().join('');
            if (isPalindrome(left) && wordMap.has(revRight) && wordMap.get(revRight) !== i) {
                result.push([wordMap.get(revRight), i]);
            }
            if (isPalindrome(right) && wordMap.has(revLeft) && wordMap.get(revLeft) !== i) {
                result.push([i, wordMap.get(revLeft)]);
            }
        }
    }
    return result;
    
};
