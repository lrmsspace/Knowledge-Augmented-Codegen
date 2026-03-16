// Source: https://leetcode.com/problems/make-a-square-with-the-same-color/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 2D matrix grid of size 3 x 3 consisting only of characters 'B' and 'W'. Character 'W' represents the white color, and character 'B' represents the black color.
//
// Your task is to change the color of at most one cell so that the matrix has a 2 x 2 square where all cells are of the same color.
//
// Return true if it is possible to create a 2 x 2 square of the same color, otherwise, return false.
//
//  
// .grid-container {
//   display: grid;
//   grid-template-columns: 30px 30px 30px;
//   padding: 10px;
// }
// .grid-item {
//   background-color: black;
//   border: 1px solid gray;
//   height: 30px;
//   font-size: 30px;
//   text-align: center;
// }
// .grid-item-white {
//   background-color: white;
// }
//
// Example:
// Input: grid = [["B","W","B"],["B","W","W"],["B","W","B"]]
//
// Output: true
//
// Explanation:
//
// It can be done by changing the color of the grid[0][2].
//
// Constraints:
// grid.length == 3
// 	grid[i].length == 3
// 	grid[i][j] is either 'W' or 'B'.
//

class Solution {
    public boolean canMakeSquare(char[][] grid) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                int blackCount = 0;
                int whiteCount = 0;

                for (int x = i; x < i + 2; x++) {
                    for (int y = j; y < j + 2; y++) {
                        if (grid[x][y] == 'B') {
                            blackCount++;
                        } else {
                            whiteCount++;
                        }
                    }
                }

                if (blackCount >= 3 || whiteCount >= 3) {
                    return true;
                }
            }
        }

        return false;           
    }
}
