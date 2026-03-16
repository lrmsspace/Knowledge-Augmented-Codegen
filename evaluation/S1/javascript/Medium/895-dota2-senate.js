// Source: https://leetcode.com/problems/dota2-senate/   |   Difficulty: Medium
//
// Problem Description:
// In the world of Dota2, there are two parties: the Radiant and the Dire.
//
// The Dota2 senate consists of senators coming from two parties. Now the Senate wants to decide on a change in the Dota2 game. The voting for this change is a round-based procedure. In each round, each senator can exercise one of the two rights:
//
//
// 	Ban one senator's right: A senator can make another senator lose all his rights in this and all the following rounds.
// 	Announce the victory: If this senator found the senators who still have rights to vote are all from the same party, he can announce the victory and decide on the change in the game.
//
//
// Given a string senate representing each senator's party belonging. The character 'R' and 'D' represent the Radiant party and the Dire party. Then if there are n senators, the size of the given string will be n.
//
// The round-based procedure starts from the first senator to the last senator in the given order. This procedure will last until the end of voting. All the senators who have lost their rights will be skipped during the procedure.
//
// Suppose every senator is smart enough and will play the best strategy for his own party. Predict which party will finally announce the victory and change the Dota2 game. The output should be "Radiant" or "Dire".
//
// Example:
// Input: senate = "RD"
// Output: "Radiant"
// Explanation: 
// The first senator comes from Radiant and he can just ban the next senator's right in round 1. 
// And the second senator can't exercise any rights anymore since his right has been banned. 
// And in round 2, the first senator can just announce the victory since he is the only guy in the senate who can vote.
//
// Constraints:
// n == senate.length
// 	1 <= n <= 104
// 	senate[i] is either 'R' or 'D'.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} senate
 * @return {string}
 */
var predictPartyVictory = function(senate) {
	const radiantQueue = [];
	const direQueue = [];

	// Initialize the queues with the indices of the senators from each party
	for (let i = 0; i < senate.length; i++) {
		if (senate[i] === 'R') {
			radiantQueue.push(i);
		} else {
			direQueue.push(i);
		}
	}

	// Simulate the rounds of voting
	while (radiantQueue.length > 0 && direQueue.length > 0) {
		const radiantIndex = radiantQueue.shift();
		const direIndex = direQueue.shift();

		if (radiantIndex < direIndex) {
			// Radiant senator bans Dire senator and goes to the back of the queue
			radiantQueue.push(radiantIndex + senate.length);
		} else {
			// Dire senator bans Radiant senator and goes to the back of the queue
			direQueue.push(direIndex + senate.length);
		}
	}

	return radiantQueue.length > 0 ? "Radiant" : "Dire";
};
