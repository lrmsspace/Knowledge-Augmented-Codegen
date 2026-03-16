// Source: https://leetcode.com/problems/moving-stones-until-consecutive-ii/   |   Difficulty: Medium
//
// Problem Description:
// There are some stones in different positions on the X-axis. You are given an integer array stones, the positions of the stones.
//
// Call a stone an endpoint stone if it has the smallest or largest position. In one move, you pick up an endpoint stone and move it to an unoccupied position so that it is no longer an endpoint stone.
//
//
//  In particular, if the stones are at say, stones = [1,2,5], you cannot move the endpoint stone at position 5, since moving it to any position (such as 0, or 3) will still keep that stone as an endpoint stone.
//
//
// The game ends when you cannot make any more moves (i.e., the stones are in three consecutive positions).
//
// Return an integer array answer of length 2 where:
//
//
//  answer[0] is the minimum number of moves you can play, and
//  answer[1] is the maximum number of moves you can play.
//
// Example:
// Input: stones = [7,4,9]
// Output: [1,2]
// Explanation: We can move 4 -> 8 for one move to finish the game.
// Or, we can move 9 -> 5, 4 -> 6 for two moves to finish the game.
//
// Constraints:
// 3 <= stones.length <= 104
//  1 <= stones[i] <= 109
//  All the values of stones are unique.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* numMovesStonesII(int* stones, int stonesSize, int* returnSize) {
    // Sort the stones array
    qsort(stones, stonesSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int maxMoves = 0;
    int minMoves = stonesSize;

    // Calculate maximum moves
    maxMoves = (stones[stonesSize - 1] - stones[0] + 1 - stonesSize) - 
               fmin(stones[1] - stones[0] - 1, stones[stonesSize - 1] - stones[stonesSize - 2] - 1);

    // Calculate minimum moves using sliding window
    int left = 0;
    for (int right = 0; right < stonesSize; right++) {
        while (stones[right] - stones[left] + 1 > stonesSize) {
            left++;
        }
        int currentWindowSize = right - left + 1;
        if (currentWindowSize == stonesSize - 1 && 
            stones[right] - stones[left] + 1 == stonesSize - 1) {
            minMoves = fmin(minMoves, 2);
        } else {
            minMoves = fmin(minMoves, stonesSize - currentWindowSize);
        }
    }

    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = minMoves;
    result[1] = maxMoves;
    *returnSize = 2;
    return result;      
}
