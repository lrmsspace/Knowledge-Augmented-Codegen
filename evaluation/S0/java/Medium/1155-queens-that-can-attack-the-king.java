// Source: https://leetcode.com/problems/queens-that-can-attack-the-king/   |   Difficulty: Medium
//
// Problem Description:
// On a 0-indexed 8 x 8 chessboard, there can be multiple black queens and one white king.
//
// You are given a 2D integer array queens where queens[i] = [xQueeni, yQueeni] represents the position of the ith black queen on the chessboard. You are also given an integer array king of length 2 where king = [xKing, yKing] represents the position of the white king.
//
// Return the coordinates of the black queens that can directly attack the king. You may return the answer in any order.
//
// Example:
// Input: queens = [[0,1],[1,0],[4,0],[0,4],[3,3],[2,4]], king = [0,0]
// Output: [[0,1],[1,0],[3,3]]
// Explanation: The diagram above shows the three queens that can directly attack the king and the three queens that cannot attack the king (i.e., marked with red dashes).
//
// Constraints:
// 1 <= queens.length < 64
// 	queens[i].length == king.length == 2
// 	0 <= xQueeni, yQueeni, xKing, yKing < 8
// 	All the given positions are unique.
//

class Solution {
    public List<List<Integer>> queensAttacktheKing(int[][] queens, int[] king) {
        Set<String> queenPositions = new HashSet<>();
        for (int[] queen : queens) {
            queenPositions.add(queen[0] + "," + queen[1]);
        }

        List<List<Integer>> attackingQueens = new ArrayList<>();
        int[][] directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
        };

        for (int[] direction : directions) {
            int x = king[0];
            int y = king[1];

            while (true) {
                x += direction[0];
                y += direction[1];

                if (x < 0 || x >= 8 || y < 0 || y >= 8) {
                    break;
                }

                if (queenPositions.contains(x + "," + y)) {
                    attackingQueens.add(Arrays.asList(x, y));
                    break;
                }
            }
        }

        return attackingQueens;         
    }
}
