// Source: https://leetcode.com/problems/parallel-courses-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n, which indicates that there are n courses labeled from 1 to n. You are also given an array relations where relations[i] = [prevCoursei, nextCoursei], representing a prerequisite relationship between course prevCoursei and course nextCoursei: course prevCoursei has to be taken before course nextCoursei. Also, you are given the integer k.
//
// In one semester, you can take at most k courses as long as you have taken all the prerequisites in the previous semesters for the courses you are taking.
//
// Return the minimum number of semesters needed to take all courses. The testcases will be generated such that it is possible to take every course.
//
// Example:
// Input: n = 4, relations = [[2,1],[3,1],[1,4]], k = 2
// Output: 3
// Explanation: The figure above represents the given graph.
// In the first semester, you can take courses 2 and 3.
// In the second semester, you can take course 1.
// In the third semester, you can take course 4.
//
// Constraints:
// 1 <= n <= 15
// 	1 <= k <= n
// 	0 <= relations.length <= n * (n-1) / 2
// 	relations[i].length == 2
// 	1 <= prevCoursei, nextCoursei <= n
// 	prevCoursei != nextCoursei
// 	All the pairs [prevCoursei, nextCoursei] are unique.
// 	The given graph is a directed acyclic graph.
//

/**
 * @param {number} n
 * @param {number[][]} relations
 * @param {number} k
 * @return {number}
 */
var minNumberOfSemesters = function(n, relations, k) {
    const prereq = new Array(n).fill(0);
    for (const [prev, next] of relations) {
        prereq[next - 1] |= 1 << (prev - 1);
    }
    const dp = new Array(1 << n).fill(Infinity);
    dp[0] = 0;
    for (let mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] === Infinity) continue;
        let available = 0;
        for (let i = 0; i < n; i++) {
            if ((mask & (1 << i)) === 0 && (mask & prereq[i]) === prereq[i]) {
                available |= 1 << i;
            }
        }
        for (let sub = available; sub > 0; sub = (sub - 1) & available) {
            if (countBits(sub) <= k) {
                dp[mask | sub] = Math.min(dp[mask | sub], dp[mask] + 1);
            }
        }
    }
    return dp[(1 << n) - 1];
};
