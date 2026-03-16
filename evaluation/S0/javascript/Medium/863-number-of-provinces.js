// Source: https://leetcode.com/problems/number-of-provinces/   |   Difficulty: Medium
//
// Problem Description:
// There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.
//
// A province is a group of directly or indirectly connected cities and no other cities outside of the group.
//
// You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.
//
// Return the total number of provinces.
//
// Example:
// Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
// Output: 2
//
// Constraints:
// 1 <= n <= 200
// 	n == isConnected.length
// 	n == isConnected[i].length
// 	isConnected[i][j] is 1 or 0.
// 	isConnected[i][i] == 1
// 	isConnected[i][j] == isConnected[j][i]
//

/**
 * @param {number[][]} isConnected
 * @return {number}
 */
var findCircleNum = function(isConnected) {
    const n = isConnected.length;
    const visited = new Array(n).fill(false);
    let provinceCount = 0;

    const dfs = (city) => {
        visited[city] = true;
        for (let otherCity = 0; otherCity < n; otherCity++) {
            if (isConnected[city][otherCity] === 1 && !visited[otherCity]) {
                dfs(otherCity);
            }
        }
    };

    for (let city = 0; city < n; city++) {
        if (!visited[city]) {
            dfs(city);
            provinceCount++;
        }
    }

    return provinceCount;
};