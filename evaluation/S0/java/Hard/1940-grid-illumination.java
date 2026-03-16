// Source: https://leetcode.com/problems/grid-illumination/   |   Difficulty: Hard
//
// Problem Description:
// There is a 2D grid of size n x n where each cell of this grid has a lamp that is initially turned off.
//
// You are given a 2D array of lamp positions lamps, where lamps[i] = [rowi, coli] indicates that the lamp at grid[rowi][coli] is turned on. Even if the same lamp is listed more than once, it is turned on.
//
// When a lamp is turned on, it illuminates its cell and all other cells in the same row, column, or diagonal.
//
// You are also given another 2D array queries, where queries[j] = [rowj, colj]. For the jth query, determine whether grid[rowj][colj] is illuminated or not. After answering the jth query, turn off the lamp at grid[rowj][colj] and its 8 adjacent lamps if they exist. A lamp is adjacent if its cell shares either a side or corner with grid[rowj][colj].
//
// Return an array of integers ans, where ans[j] should be 1 if the cell in the jth query was illuminated, or 0 if the lamp was not.
//
// Example:
// Input: n = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
// Output: [1,0]
// Explanation: We have the initial grid with all lamps turned off. In the above picture we see the grid after turning on the lamp at grid[0][0] then turning on the lamp at grid[4][4].
// The 0th query asks if the lamp at grid[1][1] is illuminated or not (the blue square). It is illuminated, so set ans[0] = 1. Then, we turn off all lamps in the red square.
//
// The 1st query asks if the lamp at grid[1][0] is illuminated or not (the blue square). It is not illuminated, so set ans[1] = 0. Then, we turn off all lamps in the red rectangle.
//
// Constraints:
// 1 <= n <= 109
// 	0 <= lamps.length <= 20000
// 	0 <= queries.length <= 20000
// 	lamps[i].length == 2
// 	0 <= rowi, coli < n
// 	queries[j].length == 2
// 	0 <= rowj, colj < n
//

class Solution {
    public int[] gridIllumination(int n, int[][] lamps, int[][] queries) {
        Map<Integer, Integer> rowMap = new HashMap<>();
        Map<Integer, Integer> colMap = new HashMap<>();
        Map<Integer, Integer> diagMap = new HashMap<>();
        Map<Integer, Integer> antiDiagMap = new HashMap<>();
        Set<Long> lampSet = new HashSet<>();

        for (int[] lamp : lamps) {
            int r = lamp[0], c = lamp[1];
            long code = ((long) r << 32) | c;
            if (lampSet.add(code)) {
                rowMap.put(r, rowMap.getOrDefault(r, 0) + 1);
                colMap.put(c, colMap.getOrDefault(c, 0) + 1);
                diagMap.put(r - c, diagMap.getOrDefault(r - c, 0) + 1);
                antiDiagMap.put(r + c, antiDiagMap.getOrDefault(r + c, 0) + 1);
            }
        }

        int[] result = new int[queries.length];
        int[][] directions = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        for (int i = 0; i < queries.length; i++) {
            int r = queries[i][0], c = queries[i][1];
            if (rowMap.getOrDefault(r, 0) > 0 || colMap.getOrDefault(c, 0) > 0 ||
                diagMap.getOrDefault(r - c, 0) > 0 || antiDiagMap.getOrDefault(r + c, 0) > 0) {
                result[i] = 1;
            } else {
                result[i] = 0;
            }

            for (int[] dir : directions) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                long code = ((long) nr << 32) | nc;
                if (lampSet.remove(code)) {
                    rowMap.put(nr, rowMap.get(nr) - 1);
                    colMap.put(nc, colMap.get(nc) - 1);
                    diagMap.put(nr - nc, diagMap.get(nr - nc) - 1);
                    antiDiagMap.put(nr + nc, antiDiagMap.get(nr + nc) - 1);
                    
                }
            }
        }
        return result;
    }
}
