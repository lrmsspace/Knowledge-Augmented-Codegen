// Source: https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D character matrix grid, where grid[i][j] is either 'X', 'Y', or '.', return the number of submatrices that contain:
//
//
// 	grid[0][0]
// 	an equal frequency of 'X' and 'Y'.
// 	at least one 'X'.
//
// Example:
// Input: grid = [["X","Y","."],["Y",".","."]]
//
// Output: 3
//
// Explanation:
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 1000
// 	grid[i][j] is either 'X', 'Y', or '.'.
//

class Solution {
    public int numberOfSubmatrices(char[][] grid) {
        int rows = grid.length;
        int cols = grid[0].length;
        int result = 0;

        for (int top = 0; top < rows; top++) {
            int[][] count = new int[cols][2]; // count[i][0] for 'X', count[i][1] for 'Y'

            for (int bottom = top; bottom < rows; bottom++) {
                for (int col = 0; col < cols; col++) {
                    if (grid[bottom][col] == 'X') {
                        count[col][0]++;
                    } else if (grid[bottom][col] == 'Y') {
                        count[col][1]++;
                    }
                }

                Map<String, Integer> freqMap = new HashMap<>();
                freqMap.put("0,0", 1);
                int xCount = 0;
                int yCount = 0;

                for (int col = 0; col < cols; col++) {
                    xCount += count[col][0];
                    yCount += count[col][1];

                    String key = (xCount - yCount) + "," + (xCount > 0 ? 1 : 0);
                    result += freqMap.getOrDefault(key, 0);
                    freqMap.put(key, freqMap.getOrDefault(key, 0) + 1);
                }
            }
        }

        return result;          
    }
}
