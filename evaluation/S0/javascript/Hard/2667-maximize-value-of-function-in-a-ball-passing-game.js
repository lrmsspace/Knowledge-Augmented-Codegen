// Source: https://leetcode.com/problems/maximize-value-of-function-in-a-ball-passing-game/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array receiver of length n and an integer k. n players are playing a ball-passing game.
//
// You choose the starting player, i. The game proceeds as follows: player i passes the ball to player receiver[i], who then passes it to receiver[receiver[i]], and so on, for k passes in total. The game's score is the sum of the indices of the players who touched the ball, including repetitions, i.e. i + receiver[i] + receiver[receiver[i]] + ... + receiver(k)[i].
//
// Return the maximum possible score.
//
// Example:
// Input: receiver = [2,0,1], k = 4
//
// Output: 6
//
// Explanation:
//
// Starting with player i = 2 the initial score is 2:
//
//
// 	
// 		
// 			Pass
// 			Sender Index
// 			Receiver Index
// 			Score
// 		
// 		
// 			1
// 			2
// 			1
// 			3
// 		
// 		
// 			2
// 			1
// 			0
// 			3
// 		
// 		
// 			3
// 			0
// 			2
// 			5
// 		
// 		
// 			4
// 			2
// 			1
// 			6
//
// Constraints:
// 1 <= receiver.length == n <= 105
// 	0 <= receiver[i] <= n - 1
// 	1 <= k <= 1010
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} receiver
 * @param {number} k
 * @return {number}
 */
var getMaxFunctionValue = function(receiver, k) {
    const n = receiver.length;
    const visited = new Array(n).fill(false);
    let maxScore = 0;
    for (let i = 0; i < n; i++) {
        if (visited[i]) {
            continue;
        }
        const cycle = [];
        let current = i;
        while (!visited[current]) {
            visited[current] = true;
            cycle.push(current);
            current = receiver[current];
        }
        const cycleLength = cycle.length;
        const cycleSum = cycle.reduce((sum, idx) => sum + idx, 0);
        const fullCycles = Math.floor(k / cycleLength);
        const remainder = k % cycleLength;
        let score = fullCycles * cycleSum;
        for (let j = 0; j < remainder; j++) {
            score += cycle[j];
        }
        maxScore = Math.max(maxScore, score);
    }
    return maxScore;
};
