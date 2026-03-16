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
    public int findCheapestPrice(int n, int[][] flights, int src, int dst, int k) {
        // Create adjacency list
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] flight : flights) {
            graph.get(flight[0]).add(new int[]{flight[1], flight[2]});
        }

        // Min-heap priority queue to store (cost, current city, stops remaining)
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        pq.offer(new int[]{0, src, k + 1}); // k + 1 because we count edges

        while (!pq.isEmpty()) {
            int[] current = pq.poll();
            int cost = current[0];
            int city = current[1];
            int stops = current[2];

            // If we reach the destination, return the cost
            if (city == dst) {
                return cost;
            }

            // If we have stops remaining, explore neighbors
            if (stops > 0) {
                for (int[] neighbor : graph.get(city)) {
                    int nextCity = neighbor[0];
                    int price = neighbor[1];
                    pq.offer(new int[]{cost + price, nextCity, stops - 1});
                }
            }
        }

        // If we exhaust the queue without finding the destination
        return -1;          
    }
}
