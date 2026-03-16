// Source: https://leetcode.com/problems/moving-stones-until-consecutive/   |   Difficulty: Medium
//
// Problem Description:
// There are three stones in different positions on the X-axis. You are given three integers a, b, and c, the positions of the stones.
//
// In one move, you pick up a stone at an endpoint (i.e., either the lowest or highest position stone), and move it to an unoccupied position between those endpoints. Formally, let's say the stones are currently at positions x, y, and z with x < y < z. You pick up the stone at either position x or position z, and move that stone to an integer position k, with x < k < z and k != y.
//
// The game ends when you cannot make any more moves (i.e., the stones are in three consecutive positions).
//
// Return an integer array answer of length 2 where:
//
//
// 	answer[0] is the minimum number of moves you can play, and
// 	answer[1] is the maximum number of moves you can play.
//
// Example:
// Input: a = 1, b = 2, c = 5
// Output: [1,2]
// Explanation: Move the stone from 5 to 3, or move the stone from 5 to 4 to 3.
//
// Constraints:
// 1 <= a, b, c <= 100
// 	a, b, and c have different values.
//

class Solution {
    public int[] numMovesStones(int a, int b, int c) {
        int[] stones = new int[]{a, b, c};
        Arrays.sort(stones);
        int leftGap = stones[1] - stones[0] - 1;
        int rightGap = stones[2] - stones[1] - 1;

        int minMoves;
        if (leftGap == 0 && rightGap == 0) {
            minMoves = 0;
        } else if (leftGap <= 1 || rightGap <= 1) {
            minMoves = 1;
        } else {
            minMoves = 2;
        }

        int maxMoves = leftGap + rightGap;

        return new int[]{minMoves, maxMoves};           
    }
}
