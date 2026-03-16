// Source: https://leetcode.com/problems/most-frequent-prime/   |   Difficulty: Medium
//
// Problem Description:
// You are given a m x n 0-indexed 2D matrix mat. From every cell, you can create numbers in the following way:
//
//
// 	There could be at most 8 paths from the cells namely: east, south-east, south, south-west, west, north-west, north, and north-east.
// 	Select a path from them and append digits in this path to the number being formed by traveling in this direction.
// 	Note that numbers are generated at every step, for example, if the digits along the path are 1, 9, 1, then there will be three numbers generated along the way: 1, 19, 191.
//
//
// Return the most frequent prime number greater than 10 out of all the numbers created by traversing the matrix or -1 if no such prime number exists. If there are multiple prime numbers with the highest frequency, then return the largest among them.
//
// Note: It is invalid to change the direction during the move.
//
// Example:
// Input: mat = [[1,1],[9,9],[1,1]]
// Output: 19
// Explanation: 
// From cell (0,0) there are 3 possible directions and the numbers greater than 10 which can be created in those directions are:
// East: [11], South-East: [19], South: [19,191].
// Numbers greater than 10 created from the cell (0,1) in all possible directions are: [19,191,19,11].
// Numbers greater than 10 created from the cell (1,0) in all possible directions are: [99,91,91,91,91].
// Numbers greater than 10 created from the cell (1,1) in all possible directions are: [91,91,99,91,91].
// Numbers greater than 10 created from the cell (2,0) in all possible directions are: [11,19,191,19].
// Numbers greater than 10 created from the cell (2,1) in all possible directions are: [11,19,19,191].
// The most frequent prime number among all the created numbers is 19.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 6
// 	1 <= mat[i][j] <= 9
//

/**
 * @param {number[][]} mat
 * @return {number}
 */
var mostFrequentPrime = function(mat) {
    const m = mat.length;
    const n = mat[0].length;
    const directions = [
        [0, 1], [1, 1], [1, 0], [1, -1],
        [0, -1], [-1, -1], [-1, 0], [-1, 1]
    ];
    const primeCount = new Map();

    function isPrime(num) {
        if (num < 2) return false;
        for (let i = 2; i * i <= num; i++) {
            if (num % i === 0) return false;
        }
        return true;
    }
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            for (const [dx, dy] of directions) {
                let x = i;;
                let y = j;
                let numStr = '';
                while (x >= 0 && x < m && y >= 0 && y < n) {
                    numStr += mat[x][y].toString();
                    const num = parseInt(numStr, 10);
                    if (num > 10 && isPrime(num)) {
                        primeCount.set(num, (primeCount.get(num) || 0) + 1);
                    }
                    x += dx;
                    y += dy;
                }
            }
        }
    }
    let maxFreq = 0;
    let result = -1;
    for (const [prime, freq] of primeCount.entries()) {
        if (freq > maxFreq || (freq === maxFreq && prime > result)) {
            maxFreq = freq;
            result = prime;
        }
    }
    return result;  
};
