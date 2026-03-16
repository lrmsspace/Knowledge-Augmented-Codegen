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

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& flight : flights) {
            graph[flight[0]].emplace_back(flight[1], flight[2]);
        }

        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        for (int i = 0; i <= k; ++i) {
            vector<int> tempDist = dist;
            for (int u = 0; u < n; ++u) {
                if (dist[u] == INT_MAX) continue;
                for (const auto& [v, price] : graph[u]) {
                    if (dist[u] + price < tempDist[v]) {
                        tempDist[v] = dist[u] + price;
                    }
                }
            }
            dist = tempDist;
        }

        return dist[dst] == INT_MAX ? -1 : dist[dst];           
    }
};
