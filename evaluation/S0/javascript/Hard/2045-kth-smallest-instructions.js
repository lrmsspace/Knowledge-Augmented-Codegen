// Source: https://leetcode.com/problems/kth-smallest-instructions/   |   Difficulty: Hard
//
// Problem Description:
// Bob is standing at cell (0, 0), and he wants to reach destination: (row, column). He can only travel right and down. You are going to help Bob by providing instructions for him to reach destination.
//
// The instructions are represented as a string, where each character is either:
//
//
// 	'H', meaning move horizontally (go right), or
// 	'V', meaning move vertically (go down).
//
//
// Multiple instructions will lead Bob to destination. For example, if destination is (2, 3), both "HHHVV" and "HVHVH" are valid instructions.
//
// However, Bob is very picky. Bob has a lucky number k, and he wants the kth lexicographically smallest instructions that will lead him to destination. k is 1-indexed.
//
// Given an integer array destination and an integer k, return the kth lexicographically smallest instructions that will take Bob to destination.
//
// Example:
// Input: destination = [2,3], k = 1
// Output: "HHHVV"
// Explanation: All the instructions that reach (2, 3) in lexicographic order are as follows:
// ["HHHVV", "HHVHV", "HHVVH", "HVHHV", "HVHVH", "HVVHH", "VHHHV", "VHHVH", "VHVHH", "VVHHH"].
//
// Constraints:
// destination.length == 2
// 	1 <= row, column <= 15
// 	1 <= k <= nCr(row + column, row), where nCr(a, b) denotes a choose b​​​​​.
//

/**
 * @param {number[]} destination
 * @param {number} k
 * @return {string}
 */
var kthSmallestPath = function(destination, k) {
    const [row, column] = destination;
    const totalSteps = row + column;
    const choose = (n, r) => {
        if (r > n || r < 0) return 0;
        let res = 1;
        for (let i = 1; i <= r; i++) {
            res = res * (n - i + 1) / i;
        }
        return res;
    };
    let path = '';
    for (let i = 0; i < totalSteps; i++) {
        const remainingDown = row - path.split('V').length + 1;
        const remainingRight = column - path.split('H').length + 1;
        const countDownFirst = choose(remainingDown + remainingRight - 1, remainingDown - 1);   
        if (k <= countDownFirst) {
            path += 'H';
        }
        else {
            path += 'V';
            k -= countDownFirst;
        }
    }
    return path;
};
