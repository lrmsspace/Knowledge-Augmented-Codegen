// Source: https://leetcode.com/problems/cheapest-flights-within-k-stops/   |   Difficulty: Medium
//
// Problem Description:
// There are n cities connected by some number of flights. You are given an array flights where flights[i] = [fromi, toi, pricei] indicates that there is a flight from city fromi to city toi with cost pricei.
//
// You are also given three integers src, dst, and k, return the cheapest price from src to dst with at most k stops. If there is no such route, return -1.
//
// Example:
// Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
// Output: 700
// Explanation:
// The graph is shown above.
// The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
// Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.
//
// Constraints:
// 1 <= n <= 100
// 	0 <= flights.length <= (n * (n - 1) / 2)
// 	flights[i].length == 3
// 	0 <= fromi, toi < n
// 	fromi != toi
// 	1 <= pricei <= 104
// 	There will not be any multiple flights between two cities.
// 	0 <= src, dst, k < n
// 	src != dst
//

/**
 * @param {number} n
 * @param {number[][]} flights
 * @param {number} src
 * @param {number} dst
 * @param {number} k
 * @return {number}
 */
var findCheapestPrice = function(n, flights, src, dst, k) {
    const adjList = Array.from({ length: n }, () => []);
    for (const [from, to, price] of flights) {
        adjList[from].push([to, price]);
    }
    const pq = [[0, src, 0]]; // [cost, city, stops]
    const distances = Array.from({ length: n }, () => Array(k + 2).fill(Infinity));
    distances[src][0] = 0;
    while (pq.length > 0) {
        pq.sort((a, b) => a[0] - b[0]);
        const [cost, city, stops] = pq.shift();
        if (city === dst) {
            return cost;
        }
        if (stops > k) {
            continue;
        }
        for (const [nextCity, price] of adjList[city]) {
            const newCost = cost + price;
            if (newCost < distances[nextCity][stops + 1]) {
                distances[nextCity][stops + 1] = newCost;
                pq.push([newCost, nextCity, stops + 1]);
            }
        }
    }
    return -1;
};