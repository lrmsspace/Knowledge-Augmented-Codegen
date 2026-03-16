// Source: https://leetcode.com/problems/minimum-cost-of-a-path-with-special-roads/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array start where start = [startX, startY] represents your initial position (startX, startY) in a 2D space. You are also given the array target where target = [targetX, targetY] represents your target position (targetX, targetY).
//
// The cost of going from a position (x1, y1) to any other position in the space (x2, y2) is |x2 - x1| + |y2 - y1|.
//
// There are also some special roads. You are given a 2D array specialRoads where specialRoads[i] = [x1i, y1i, x2i, y2i, costi] indicates that the ith special road goes in one direction from (x1i, y1i) to (x2i, y2i) with a cost equal to costi. You can use each special road any number of times.
//
// Return the minimum cost required to go from (startX, startY) to (targetX, targetY).
//
// Example:
// Input: start = [1,1], target = [4,5], specialRoads = [[1,2,3,3,2],[3,4,4,5,1]]
//
// Output: 5
//
// Explanation:
//
//
// 	(1,1) to (1,2) with a cost of |1 - 1| + |2 - 1| = 1.
// 	(1,2) to (3,3). Use specialRoads[0] with the cost 2.
// 	(3,3) to (3,4) with a cost of |3 - 3| + |4 - 3| = 1.
// 	(3,4) to (4,5). Use specialRoads[1] with the cost 1.
//
//
// So the total cost is 1 + 2 + 1 + 1 = 5.
//
// Constraints:
// start.length == target.length == 2
// 	1 <= startX <= targetX <= 105
// 	1 <= startY <= targetY <= 105
// 	1 <= specialRoads.length <= 200
// 	specialRoads[i].length == 5
// 	startX <= x1i, x2i <= targetX
// 	startY <= y1i, y2i <= targetY
// 	1 <= costi <= 105
//

class Solution {
    public int minimumCost(int[] start, int[] target, int[][] specialRoads) {
        int n = specialRoads.length;
        int[][] points = new int[n + 2][2];
        points[0] = start;
        points[n + 1] = target;
        for (int i = 0; i < n; i++) {
            points[i + 1][0] = specialRoads[i][0];
            points[i + 1][1] = specialRoads[i][1];
        }

        int[] dist = new int[n + 2];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[0] = 0;

        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[1]));
        pq.offer(new int[]{0, 0});

        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int u = curr[0];
            int currDist = curr[1];

            if (currDist > dist[u]) continue;

            for (int v = 0; v < n + 2; v++) {
                if (u == v) continue;

                int cost;
                if (u == 0 || v == n + 1) {
                    cost = Math.abs(points[u][0] - points[v][0]) + Math.abs(points[u][1] - points[v][1]);
                } else {
                    cost = Math.min(
                            Math.abs(points[u][0] - points[v][0]) + Math.abs(points[u][1] - points[v][1]),
                            specialRoads[v - 1][4]
                    );
                }

                if (dist[u] + cost < dist[v]) {
                    dist[v] = dist[u] + cost;
                    pq.offer(new int[]{v, dist[v]});
                }
            }
        }

        return dist[n + 1];         
    }
}
