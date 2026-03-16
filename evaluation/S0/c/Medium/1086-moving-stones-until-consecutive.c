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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* numMovesStones(int a, int b, int c, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    // Sort a, b, c
    int min = a < b ? (a < c ? a : c) : (b < c ? b : c);
    int max = a > b ? (a > c ? a : c) : (b > c ? b : c);
    int mid = a + b + c - min - max;

    int left_gap = mid - min - 1;
    int right_gap = max - mid - 1;

    // Calculate minimum moves
    if (left_gap == 0 && right_gap == 0) {
        result[0] = 0;
    } else if (left_gap <= 1 || right_gap <= 1) {
        result[0] = 1;
    } else {
        result[0] = 2;
    }

    // Calculate maximum moves
    result[1] = left_gap + right_gap;

    return result;      
}
