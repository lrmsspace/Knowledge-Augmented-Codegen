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

int furthestDistanceFromOrigin(char* moves) {
    int left = 0, right = 0, wildcard = 0;
    for (int i = 0; moves[i] != '\0'; i++) {
        if (moves[i] == 'L') {
            left++;
        } else if (moves[i] == 'R') {
            right++;
        } else {
            wildcard++;
        }
    }
    return abs(left - right) + wildcard;        
}
