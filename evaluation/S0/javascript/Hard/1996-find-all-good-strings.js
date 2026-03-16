// Source: https://leetcode.com/problems/find-all-good-strings/   |   Difficulty: Hard
//
// Problem Description:
// Given the strings s1 and s2 of size n and the string evil, return the number of good strings.
//
// A good string has size n, it is alphabetically greater than or equal to s1, it is alphabetically smaller than or equal to s2, and it does not contain the string evil as a substring. Since the answer can be a huge number, return this modulo 109 + 7.
//
// Example:
// Input: n = 2, s1 = "aa", s2 = "da", evil = "b"
// Output: 51 
// Explanation: There are 25 good strings starting with 'a': "aa","ac","ad",...,"az". Then there are 25 good strings starting with 'c': "ca","cc","cd",...,"cz" and finally there is one good string starting with 'd': "da".
//
// Constraints:
// s1.length == n
// 	s2.length == n
// 	s1 <= s2
// 	1 <= n <= 500
// 	1 <= evil.length <= 50
// 	All strings consist of lowercase English letters.
//

/**
 * @param {number} n
 * @param {string} s1
 * @param {string} s2
 * @param {string} evil
 * @return {number}
 */
var findGoodStrings = function(n, s1, s2, evil) {
     const MOD = 1e9 + 7;
     const m = evil.length;
     const lps = new Array(m).fill(0);
     for (let i = 1, j = 0; i < m; i++) {
         while (j > 0 && evil[i] !== evil[j]) {
             j = lps[j - 1];
         }
         if (evil[i] === evil[j]) {
             j++;
         }
         lps[i] = j;
     }

     const memo = new Map();
     function dfs(pos, prefix, isPrefixS1, isPrefixS2) {
         if (prefix === m) {
             return 0;
         }
         if (pos === n) {
             return 1;
         }
         const key = `${pos}-${prefix}-${isPrefixS1}-${isPrefixS2}`;
         if (memo.has(key)) {
             return memo.get(key);
         }
         let count = 0;
         const startChar = isPrefixS1 ? s1[pos] : 'a';
         const endChar = isPrefixS2 ? s2[pos] : 'z';
         for (let c = startChar.charCodeAt(0); c <= endChar.charCodeAt(0); c++) {
             const char = String.fromCharCode(c);
             let nextPrefix = prefix;
             while (nextPrefix > 0 && char !== evil[nextPrefix]) {
                 nextPrefix = lps[nextPrefix - 1];
             }
             if (char === evil[nextPrefix]) {
                 nextPrefix++;
             }
             count = (count + dfs(pos + 1, nextPrefix, isPrefixS1 && char === startChar, isPrefixS2 && char === endChar)) % MOD;
         }
         memo.set(key, count);
         return count;
     }

     return dfs(0, 0, true, true);  
};
