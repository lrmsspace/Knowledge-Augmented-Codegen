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
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        using PII = pair<int, int>;
        using Edge = pair<int, PII>; // cost, (x, y)
        auto cmp = [](const Edge& a, const Edge& b) {
            return a.first > b.first;
        };
        priority_queue<Edge, vector<Edge>, decltype(cmp)> pq(cmp);
        unordered_map<long long, int> dist;

        auto encode = [](int x, int y) {
            return ((long long)x << 32) | (long long)y;
        };

        pq.push({0, {start[0], start[1]}});
        dist[encode(start[0], start[1])] = 0;

        while (!pq.empty()) {
            auto [cost, pos] = pq.top();
            pq.pop();
            int x = pos.first;
            int y = pos.second;

            if (x == target[0] && y == target[1]) {
                return cost;
            }

            // Direct move to target
            int directCost = cost + abs(target[0] - x) + abs(target[1] - y);
            long long targetCode = encode(target[0], target[1]);
            if (dist.find(targetCode) == dist.end() || directCost < dist[targetCode]) {
                dist[targetCode] = directCost;
                pq.push({directCost, {target[0], target[1]}});
            }

            // Use special roads
            for (const auto& road : specialRoads) {
                int x1 = road[0], y1 = road[1], x2 = road[2], y2 = road[3], roadCost = road[4];
                int moveToRoadCost = cost + abs(x1 - x) + abs(y1 - y) + roadCost;
                long long roadEndCode = encode(x2, y2);
                if (dist.find(roadEndCode) == dist.end() || moveToRoadCost < dist[roadEndCode]) {
                    dist[roadEndCode] = moveToRoadCost;
                    pq.push({moveToRoadCost, {x2, y2}});
                }
            }
        }

        return -1; // Should never reach here           
    }
};
