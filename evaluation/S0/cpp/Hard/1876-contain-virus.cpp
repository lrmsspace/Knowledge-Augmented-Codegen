// Source: https://leetcode.com/problems/contain-virus/   |   Difficulty: Hard
//
// Problem Description:
// A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.
//
// The world is modeled as an m x n binary grid isInfected, where isInfected[i][j] == 0 represents uninfected cells, and isInfected[i][j] == 1 represents cells contaminated with the virus. A wall (and only one wall) can be installed between any two 4-directionally adjacent cells, on the shared boundary.
//
// Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall. Resources are limited. Each day, you can install walls around only one region (i.e., the affected area (continuous block of infected cells) that threatens the most uninfected cells the following night). There will never be a tie.
//
// Return the number of walls used to quarantine all the infected regions. If the world will become fully infected, return the number of walls used.
//
// Example:
// Input: isInfected = [[0,1,0,0,0,0,0,1],[0,1,0,0,0,0,0,1],[0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0]]
// Output: 10
// Explanation: There are 2 contaminated regions.
// On the first day, add 5 walls to quarantine the viral region on the left. The board after the virus spreads is:
//
// On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.
//
// Constraints:
// m == isInfected.length
// 	n == isInfected[i].length
// 	1 <= m, n <= 50
// 	isInfected[i][j] is either 0 or 1.
// 	There is always a contiguous viral region throughout the described process that will infect strictly more uncontaminated squares in the next round.
//

class Solution {
public:
    int containVirus(vector<vector<int>>& isInfected) {
        int m = isInfected.size();
        int n = isInfected[0].size();
        int totalWalls = 0;

        // Directions for 4-directional movement
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (true) {
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            vector<set<pair<int, int>>> regions;
            vector<set<pair<int, int>>> frontiers;
            vector<int> wallsNeeded;

            // Identify all regions
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (isInfected[i][j] == 1 && !visited[i][j]) {
                        set<pair<int, int>> region;
                        set<pair<int, int>> frontier;
                        int walls = 0;
                        queue<pair<int, int>> q;
                        q.push({i, j});
                        visited[i][j] = true;

                        while (!q.empty()) {
                            auto [x, y] = q.front();
                            q.pop();
                            region.insert({x, y});

                            for (auto& dir : directions) {
                                int nx = x + dir.first;
                                int ny = y + dir.second;

                                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                                    if (isInfected[nx][ny] == 0) {
                                        frontier.insert({nx, ny});
                                        walls++;
                                    } else if (isInfected[nx][ny] == 1 && !visited[nx][ny]) {
                                        visited[nx][ny] = true;
                                        q.push({nx, ny});
                                    }
                                }
                            }
                        }

                        regions.push_back(region);
                        frontiers.push_back(frontier);
                        wallsNeeded.push_back(walls);
                    }
                }
            }

            if (regions.empty()) break;

            // Find the region that threatens the most uninfected cells
            int maxThreatIdx = 0;
            for (int i = 1; i < frontiers.size(); ++i) {
                if (frontiers[i].size() > frontiers[maxThreatIdx].size()) {
                    maxThreatIdx = i;
                }           
    }
};
