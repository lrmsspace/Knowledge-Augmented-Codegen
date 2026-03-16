// Source: https://leetcode.com/problems/maximum-performance-of-a-team/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers n and k and two integer arrays speed and efficiency both of length n. There are n engineers numbered from 1 to n. speed[i] and efficiency[i] represent the speed and efficiency of the ith engineer respectively.
//
// Choose at most k different engineers out of the n engineers to form a team with the maximum performance.
//
// The performance of a team is the sum of its engineers' speeds multiplied by the minimum efficiency among its engineers.
//
// Return the maximum performance of this team. Since the answer can be a huge number, return it modulo 109 + 7.
//
// Example:
// Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
// Output: 60
// Explanation: 
// We have the maximum performance of the team by selecting engineer 2 (with speed=10 and efficiency=4) and engineer 5 (with speed=5 and efficiency=7). That is, performance = (10 + 5) * min(4, 7) = 60.
//
// Constraints:
// 1 <= k <= n <= 105
// 	speed.length == n
// 	efficiency.length == n
// 	1 <= speed[i] <= 105
// 	1 <= efficiency[i] <= 108
//

/**
 * @param {number} n
 * @param {number[]} speed
 * @param {number[]} efficiency
 * @param {number} k
 * @return {number}
 */
var maxPerformance = function(n, speed, efficiency, k) {
    const engineers = [];
    for (let i = 0; i < n; i++) {
        engineers.push({ speed: speed[i], efficiency: efficiency[i] });
    }
    engineers.sort((a, b) => b.efficiency - a.efficiency);
    const speedHeap = new MinPriorityQueue({ priority: x => x });
    let speedSum = 0;
    let maxPerf = 0;
    const MOD = 1e9 + 7;
    for (const engineer of engineers) {
        if (speedHeap.size() === k) {
            speedSum -= speedHeap.dequeue().element;
        }
        speedHeap.enqueue(engineer.speed);
        speedSum += engineer.speed;
        maxPerf = Math.max(maxPerf, speedSum * engineer.efficiency);
    }
    return maxPerf % MOD;
};
