// Source: https://leetcode.com/problems/super-washing-machines/   |   Difficulty: Hard
//
// Problem Description:
// You have n super washing machines on a line. Initially, each washing machine has some dresses or is empty.
//
// For each move, you could choose any m (1 <= m <= n) washing machines, and pass one dress of each washing machine to one of its adjacent washing machines at the same time.
//
// Given an integer array machines representing the number of dresses in each washing machine from left to right on the line, return the minimum number of moves to make all the washing machines have the same number of dresses. If it is not possible to do it, return -1.
//
// Example:
// Input: machines = [1,0,5]
// Output: 3
// Explanation:
// 1st move:    1     0 <-- 5    =>    1     1     4
// 2nd move:    1 <-- 1 <-- 4    =>    2     1     3
// 3rd move:    2     1 <-- 3    =>    2     2     2
//
// Constraints:
// n == machines.length
// 	1 <= n <= 104
// 	0 <= machines[i] <= 105
//

/**
 * @param {number[]} machines
 * @return {number}
 */
var findMinMoves = function(machines) {
    const total = machines.reduce((a, b) => a + b, 0);
    const n = machines.length;
    if (total % n !== 0) return -1;
    const target = total / n;
    let maxMoves = 0, currentBalance = 0;
    for (let i = 0; i < n; i++) {
        currentBalance += machines[i] - target;
        maxMoves = Math.max(maxMoves, Math.abs(currentBalance), machines[i] - target);
    }
    return maxMoves;    
};
