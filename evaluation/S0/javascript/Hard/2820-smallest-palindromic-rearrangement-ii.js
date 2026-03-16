// Source: https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a palindromic string s and an integer k.
//
// Return the k-th lexicographically smallest palindromic permutation of s. If there are fewer than k distinct palindromic permutations, return an empty string.
//
// Note: Different rearrangements that yield the same palindromic string are considered identical and are counted once.
//
// Example:
// Input: s = "abba", k = 2
//
// Output: "baab"
//
// Explanation:
//
//
// 	The two distinct palindromic rearrangements of "abba" are "abba" and "baab".
// 	Lexicographically, "abba" comes before "baab". Since k = 2, the output is "baab".
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of lowercase English letters.
// 	s is guaranteed to be palindromic.
// 	1 <= k <= 106
//

/**
 * @param {string} s
 * @param {number} k
 * @return {string}
 */
var smallestPalindrome = function(s, k) {
    const n = s.length; 
    const halfCount = Array(26).fill(0);
    for (let i = 0; i < n / 2; i++) {
        halfCount[s.charCodeAt(i) - 97]++;
    }
    const halfLength = n / 2;
    const factorial = [1];
    for (let i = 1; i <= halfLength; i++) {
        factorial[i] = factorial[i - 1] * i;
    }
    const countPermutations = (countArr) => {
        let total = 0;
        let denom = 1;
        for (let count of countArr) {   
            total += count;
            denom *= factorial[count];
        }
        return factorial[total] / denom;
    }
    let resultHalf = '';
    for (let i = 0; i < halfLength; i++) {
        for (let c = 0; c < 26; c++) {
            if (halfCount[c] === 0) continue;
            halfCount[c]--;
            const numPerms = countPermutations(halfCount);
            if (k <= numPerms) {
                resultHalf += String.fromCharCode(c + 97);
                break;
            }
            else {
                k -= numPerms;
                halfCount[c]++;
            }
        }   
    }
    const middleChar = (n % 2 === 1) ? s[Math.floor(n / 2)] : '';
    const result = resultHalf + middleChar + resultHalf.split('').reverse().join('');
    return result;
};
