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
    public int containVirus(int[][] isInfected) {
        int m = isInfected.length, n = isInfected[0].length;
        int totalWalls = 0;

        while (true) {
            boolean[][] visited = new boolean[m][n];
            List<Set<int[]>> regions = new ArrayList<>();
            List<Set<int[]>> frontiers = new ArrayList<>();
            List<Integer> wallsNeeded = new ArrayList<>();

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (isInfected[i][j] == 1 && !visited[i][j]) {
                        Set<int[]> region = new HashSet<>();
                        Set<int[]> frontier = new HashSet<>();
                        int[] walls = new int[1];
                        dfs(isInfected, visited, i, j, region, frontier, walls);
                        regions.add(region);
                        frontiers.add(frontier);
                        wallsNeeded.add(walls[0]);
                    }
                }
            }

            if (regions.isEmpty()) break;

            int maxFrontierIdx = 0;
            for (int i = 1; i < frontiers.size(); i++) {
                if (frontiers.get(i).size() > frontiers.get(maxFrontierIdx).size()) {
                    maxFrontierIdx = i;
                }
            }

            totalWalls += wallsNeeded.get(maxFrontierIdx);

            for (int i = 0; i < regions.size(); i++) {
                if (i == maxFrontierIdx) {
                    for (int[] cell : regions.get(i)) {
                        isInfected[cell[0]][cell[1]] = -1;
                    }
                } else {
                    for (int[] cell : frontiers.get(i)) {
                        isInfected[cell[0]][cell[1]] = 1;
                    }
                }
            }
        }

        return totalWalls;          
    }
}
