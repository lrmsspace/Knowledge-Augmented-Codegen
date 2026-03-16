// Source: https://leetcode.com/problems/count-ways-to-build-rooms-in-an-ant-colony/   |   Difficulty: Hard
//
// Problem Description:
// You are an ant tasked with adding n new rooms numbered 0 to n-1 to your colony. You are given the expansion plan as a 0-indexed integer array of length n, prevRoom, where prevRoom[i] indicates that you must build room prevRoom[i] before building room i, and these two rooms must be connected directly. Room 0 is already built, so prevRoom[0] = -1. The expansion plan is given such that once all the rooms are built, every room will be reachable from room 0.
//
// You can only build one room at a time, and you can travel freely between rooms you have already built only if they are connected. You can choose to build any room as long as its previous room is already built.
//
// Return the number of different orders you can build all the rooms in. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: prevRoom = [-1,0,1]
// Output: 1
// Explanation: There is only one way to build the additional rooms: 0 → 1 → 2
//
// Constraints:
// n == prevRoom.length
// 	2 <= n <= 105
// 	prevRoom[0] == -1
// 	0 <= prevRoom[i] < n for all 1 <= i < n
// 	Every room is reachable from room 0 once all the rooms are built.
//

/**

 * @param {number[]} prevRoom

 * @return {number}

 */

var waysToBuildRooms = function(prevRoom) {
    const MOD = 1e9 + 7;
    const n = prevRoom.length;
    const graph = Array.from({ length: n }, () => []);
    for (let i = 1; i < n; i++) {
        graph[prevRoom[i]].push(i);
    }
    const factorial = new Array(n + 1).fill(1);
    for (let i = 2; i <= n; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    const dfs = (node) => {
        let count = 1;
        let ways = 1;
        for (const child of graph[node]) {
            const [childCount, childWays] = dfs(child);
            count += childCount;
            ways = (ways * childWays) % MOD;
        }
        ways = (ways * factorial[count - 1]) % MOD;
        for (const child of graph[node]) {
            const [childCount] = dfs(child);
            ways = (ways * modInverse(factorial[childCount], MOD)) % MOD;
        }
        return [count, ways];
    }
    const modInverse = (a, m) => {
        let m0 = m, t, q;
        let x0 = 0, x1 = 1;
        if (m === 1) return 0;
        while (a > 1) {
            q = Math.floor(a / m);
            t = m;
            m = a % m; a = t;
            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }
        if (x1 < 0) x1 += m0;
        return x1;
    }
    return dfs(0)[1];
};
