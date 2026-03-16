// Source: https://leetcode.com/problems/furthest-point-from-origin/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string moves of length n consisting only of characters 'L', 'R', and '_'. The string represents your movement on a number line starting from the origin 0.
//
// In the ith move, you can choose one of the following directions:
//
//
// 	move to the left if moves[i] = 'L' or moves[i] = '_'
// 	move to the right if moves[i] = 'R' or moves[i] = '_'
//
//
// Return the distance from the origin of the furthest point you can get to after n moves.
//
// Example:
// Input: moves = "L_RL__R"
// Output: 3
// Explanation: The furthest point we can reach from the origin 0 is point -3 through the following sequence of moves "LLRLLLR".
//
// Constraints:
// 1 <= moves.length == n <= 50
// 	moves consists only of characters 'L', 'R' and '_'.
//

class Solution {
public:
    int furthestDistanceFromOrigin(string moves) {
        int leftMoves = 0;
        int rightMoves = 0;
        int flexibleMoves = 0;

        for (char move : moves) {
            if (move == 'L') {
                leftMoves++;
            } else if (move == 'R') {
                rightMoves++;
            } else { // move == '_'
                flexibleMoves++;
            }
        }

        // The furthest distance is achieved by using all flexible moves in the direction
        // that maximizes the distance from the origin.
        return abs(leftMoves - rightMoves) + flexibleMoves;         
    }
};
