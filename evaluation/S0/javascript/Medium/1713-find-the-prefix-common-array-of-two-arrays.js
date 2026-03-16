// Source: https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed integer permutations A and B of length n.
//
// A prefix common array of A and B is an array C such that C[i] is equal to the count of numbers that are present at or before the index i in both A and B.
//
// Return the prefix common array of A and B.
//
// A sequence of n integers is called a permutation if it contains all integers from 1 to n exactly once.
//
// Example:
// Input: A = [1,3,2,4], B = [3,1,2,4]
// Output: [0,2,3,4]
// Explanation: At i = 0: no number is common, so C[0] = 0.
// At i = 1: 1 and 3 are common in A and B, so C[1] = 2.
// At i = 2: 1, 2, and 3 are common in A and B, so C[2] = 3.
// At i = 3: 1, 2, 3, and 4 are common in A and B, so C[3] = 4.
//
// Constraints:
// 1 <= A.length == B.length == n <= 50
// 	1 <= A[i], B[i] <= n
// 	It is guaranteed that A and B are both a permutation of n integers.
//

/**
 * @param {number[]} A
 * @param {number[]} B
 * @return {number[]}
 */
var findThePrefixCommonArray = function(A, B) {
    const n = A.length;
    const countA = new Array(n + 1).fill(0);
    const countB = new Array(n + 1).fill(0);
    const C = new Array(n).fill(0);
    let commonCount = 0;
    for (let i = 0; i < n; i++) {
        countA[A[i]]++;
        countB[B[i]]++;
        if (countA[A[i]] === 1 && countB[A[i]] === 1) {
            commonCount++;
        }
        if (countA[B[i]] === 1 && countB[B[i]] === 1) {
            commonCount++;
        }
        C[i] = commonCount;
    }
    return C;
        
};
