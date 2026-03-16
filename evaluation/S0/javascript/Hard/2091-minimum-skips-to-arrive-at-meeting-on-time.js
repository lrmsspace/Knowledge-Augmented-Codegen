// Source: https://leetcode.com/problems/minimum-skips-to-arrive-at-meeting-on-time/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer hoursBefore, the number of hours you have to travel to your meeting. To arrive at your meeting, you have to travel through n roads. The road lengths are given as an integer array dist of length n, where dist[i] describes the length of the ith road in kilometers. In addition, you are given an integer speed, which is the speed (in km/h) you will travel at.
//
// After you travel road i, you must rest and wait for the next integer hour before you can begin traveling on the next road. Note that you do not have to rest after traveling the last road because you are already at the meeting.
//
//
// 	For example, if traveling a road takes 1.4 hours, you must wait until the 2 hour mark before traveling the next road. If traveling a road takes exactly 2 hours, you do not need to wait.
//
//
// However, you are allowed to skip some rests to be able to arrive on time, meaning you do not need to wait for the next integer hour. Note that this means you may finish traveling future roads at different hour marks.
//
//
// 	For example, suppose traveling the first road takes 1.4 hours and traveling the second road takes 0.6 hours. Skipping the rest after the first road will mean you finish traveling the second road right at the 2 hour mark, letting you start traveling the third road immediately.
//
//
// Return the minimum number of skips required to arrive at the meeting on time, or -1 if it is impossible.
//
// Example:
// Input: dist = [1,3,2], speed = 4, hoursBefore = 2
// Output: 1
// Explanation:
// Without skipping any rests, you will arrive in (1/4 + 3/4) + (3/4 + 1/4) + (2/4) = 2.5 hours.
// You can skip the first rest to arrive in ((1/4 + 0) + (3/4 + 0)) + (2/4) = 1.5 hours.
// Note that the second rest is shortened because you finish traveling the second road at an integer hour due to skipping the first rest.
//
// Constraints:
// n == dist.length
// 	1 <= n <= 1000
// 	1 <= dist[i] <= 105
// 	1 <= speed <= 106
// 	1 <= hoursBefore <= 107
//

/**
 * @param {number[]} dist
 * @param {number} speed
 * @param {number} hoursBefore
 * @return {number}
 */
var minSkips = function(dist, speed, hoursBefore) {
    const n = dist.length;
    const dp = Array.from({ length: n + 1 }, () => new Array(n + 1).fill(Infinity));
    dp[0][0] = 0;
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j <= i; j++) {
            const time = dp[i - 1][j] + dist[i - 1] / speed;
            if (j < i) {
                dp[i][j] = Math.min(dp[i][j], Math.ceil(time));
            }
            if (j > 0) {
                dp[i][j] = Math.min(dp[i][j], time);
            }
        }
    }   
    for (let j = 0; j <= n; j++) {
        if (dp[n][j] <= hoursBefore) {
            return j;
        }
    }
    return -1;  
};
