// Source: https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer n representing n cities numbered from 1 to n. You are also given a 2D array roads where roads[i] = [ai, bi, distancei] indicates that there is a bidirectional road between cities ai and bi with a distance equal to distancei. The cities graph is not necessarily connected.
//
// The score of a path between two cities is defined as the minimum distance of a road in this path.
//
// Return the minimum possible score of a path between cities 1 and n.
//
// Note:
//
//
// 	A path is a sequence of roads between two cities.
// 	It is allowed for a path to contain the same road multiple times, and you can visit cities 1 and n multiple times along the path.
// 	The test cases are generated such that there is at least one path between 1 and n.
//
// Example:
// Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
// Output: 5
// Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 4. The score of this path is min(9,5) = 5.
// It can be shown that no other path has less score.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= roads.length <= 105
// 	roads[i].length == 3
// 	1 <= ai, bi <= n
// 	ai != bi
// 	1 <= distancei <= 104
// 	There are no repeated edges.
// 	There is at least one path between 1 and n.
//

/**
 * @param {number} n
 * @param {number[][]} roads
 * @return {number}
 */
var minScore = function(n, roads) {
    const graph = Array.from({ length: n + 1 }, () => []);
    for (const [a, b, distance] of roads) {
        graph[a].push([b, distance]);
        graph[b].push([a, distance]);
    }
    const visited = new Array(n + 1).fill(false);
    let minScore = Infinity;

    function dfs(city) {
        visited[city] = true;
        for (const [nextCity, distance] of graph[city]) {
            minScore = Math.min(minScore, distance);
            if (!visited[nextCity]) {
                dfs(nextCity);
            }
        }
    }

    dfs(1);
    return minScore;
};