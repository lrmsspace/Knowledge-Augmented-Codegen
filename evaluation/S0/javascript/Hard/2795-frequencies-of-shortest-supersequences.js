// Source: https://leetcode.com/problems/frequencies-of-shortest-supersequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings words. Find all shortest common supersequences (SCS) of words that are not permutations of each other.
//
// A shortest common supersequence is a string of minimum length that contains each string in words as a subsequence.
//
// Return a 2D array of integers freqs that represent all the SCSs. Each freqs[i] is an array of size 26, representing the frequency of each letter in the lowercase English alphabet for a single SCS. You may return the frequency arrays in any order.
//
// Example:
// Input: words = ["ab","ba"]
//
// Output: [[1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],[2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]
//
// Explanation:
//
// The two SCSs are "aba" and "bab". The output is the letter frequencies for each one.
//
// Constraints:
// 1 <= words.length <= 256
// 	words[i].length == 2
// 	All strings in words will altogether be composed of no more than 16 unique lowercase letters.
// 	All strings in words are unique.
//

/**
 * @param {string[]} words
 * @return {number[][]}
 */
var supersequences = function(words) {
    const fromCharCode = 'a'.charCodeAt(0);         
    const n = words.length;
    const graph = Array.from({ length: 26 }, () => Array(26).fill(false));
    const inDegree = Array(26).fill(0);
    const used = Array(26).fill(false);
    for (const word of words) {
        const u = word.charCodeAt(0) - fromCharCode;
        const v = word.charCodeAt(1) - fromCharCode;
        if (!graph[u][v]) {
            graph[u][v] = true;
            inDegree[v]++;
        }
        used[u] = true;
        used[v] = true;
    }
    const results = [];
    function backtrack(path, inDeg) {
        let added = false;
        for (let i = 0; i < 26; i++) {
            if (used[i] && inDeg[i] === 0) {
                added = true;
                path.push(i);
                const newInDeg = inDeg.slice();
                for (let j = 0; j < 26; j++) {
                    if (graph[i][j]) {
                        newInDeg[j]--;
                    }
                }
                backtrack(path, newInDeg);
                path.pop();
            }
        }   
        if (!added) {
            if (path.length === n + 1) {
                const freq = Array(26).fill(0);
                for (const idx of path) {
                    freq[idx]++;
                }
                results.push(freq);
            }
        }
    }
    backtrack([], inDegree);
    return results; 
};
