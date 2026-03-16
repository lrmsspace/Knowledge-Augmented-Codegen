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

class Solution {
    public int[] numMovesStonesII(int[] stones) {
        Arrays.sort(stones);
        int n = stones.length;

        // Calculate maximum moves
        int maxMoves = Math.max(stones[n - 2] - stones[0] - n + 2,
                                stones[n - 1] - stones[1] - n + 2);

        // Calculate minimum moves using sliding window
        int minMoves = n;
        int left = 0;
        for (int right = 0; right < n; right++) {
            while (stones[right] - stones[left] + 1 > n) {
                left++;
            }
            int currentWindowSize = right - left + 1;
            if (currentWindowSize == n - 1 && stones[right] - stones[left] + 1 == n - 1) {
                minMoves = Math.min(minMoves, 2);
            } else {
                minMoves = Math.min(minMoves, n - currentWindowSize);
            }
        }

        return new int[]{minMoves, maxMoves};           
    }
}
