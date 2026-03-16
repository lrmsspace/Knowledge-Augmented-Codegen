// Source: https://leetcode.com/problems/rotating-the-box/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix of characters boxGrid representing a side-view of a box. Each cell of the box is one of the following:
//
//
// 	A stone '#'
// 	A stationary obstacle '*'
// 	Empty '.'
//
//
// The box is rotated 90 degrees clockwise, causing some of the stones to fall due to gravity. Each stone falls down until it lands on an obstacle, another stone, or the bottom of the box. Gravity does not affect the obstacles' positions, and the inertia from the box's rotation does not affect the stones' horizontal positions.
//
// It is guaranteed that each stone in boxGrid rests on an obstacle, another stone, or the bottom of the box.
//
// Return an n x m matrix representing the box after the rotation described above.
//
// Example:
// Input: boxGrid = [["#",".","#"]]
// Output: [["."],
//          ["#"],
//          ["#"]]
//
// Constraints:
// m == boxGrid.length
// 	n == boxGrid[i].length
// 	1 <= m, n <= 500
// 	boxGrid[i][j] is either '#', '*', or '.'.
//

class Solution {
    public char[][] rotateTheBox(char[][] boxGrid) {
        int m = boxGrid.length;
        int n = boxGrid[0].length;
        char[][] rotatedBox = new char[n][m];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rotatedBox[j][m - 1 - i] = boxGrid[i][j];
            }
        }

        for (int j = 0; j < n; j++) {
            int emptySpot = m - 1;
            for (int i = m - 1; i >= 0; i--) {
                if (rotatedBox[j][i] == '*') {
                    emptySpot = i - 1;
                } else if (rotatedBox[j][i] == '#') {
                    if (i != emptySpot) {
                        rotatedBox[j][emptySpot] = '#';
                        rotatedBox[j][i] = '.';
                    }
                    emptySpot--;
                }
            }
        }

        return rotatedBox;          
    }
}
