// Source: https://leetcode.com/problems/minimum-total-distance-traveled/   |   Difficulty: Hard
//
// Problem Description:
// There are some robots and factories on the X-axis. You are given an integer array robot where robot[i] is the position of the ith robot. You are also given a 2D integer array factory where factory[j] = [positionj, limitj] indicates that positionj is the position of the jth factory and that the jth factory can repair at most limitj robots.
//
// The positions of each robot are unique. The positions of each factory are also unique. Note that a robot can be in the same position as a factory initially.
//
// All the robots are initially broken; they keep moving in one direction. The direction could be the negative or the positive direction of the X-axis. When a robot reaches a factory that did not reach its limit, the factory repairs the robot, and it stops moving.
//
// At any moment, you can set the initial direction of moving for some robot. Your target is to minimize the total distance traveled by all the robots.
//
// Return the minimum total distance traveled by all the robots. The test cases are generated such that all the robots can be repaired.
//
// Note that
//
//
// 	All robots move at the same speed.
// 	If two robots move in the same direction, they will never collide.
// 	If two robots move in opposite directions and they meet at some point, they do not collide. They cross each other.
// 	If a robot passes by a factory that reached its limits, it crosses it as if it does not exist.
// 	If the robot moved from a position x to a position y, the distance it moved is |y - x|.
//
// Example:
// Input: robot = [0,4,6], factory = [[2,2],[6,2]]
// Output: 4
// Explanation: As shown in the figure:
// - The first robot at position 0 moves in the positive direction. It will be repaired at the first factory.
// - The second robot at position 4 moves in the negative direction. It will be repaired at the first factory.
// - The third robot at position 6 will be repaired at the second factory. It does not need to move.
// The limit of the first factory is 2, and it fixed 2 robots.
// The limit of the second factory is 2, and it fixed 1 robot.
// The total distance is |2 - 0| + |2 - 4| + |6 - 6| = 4. It can be shown that we cannot achieve a better total distance than 4.
//
// Constraints:
// 1 <= robot.length, factory.length <= 100
// 	factory[j].length == 2
// 	-109 <= robot[i], positionj <= 109
// 	0 <= limitj <= robot.length
// 	The input will be generated such that it is always possible to repair every robot.
//

class Solution {
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());
        
        int m = robot.size();
        int n = factory.size();
        
        // dp[i][j]: minimum distance to repair first i robots with first j factories
        vector<vector<long long>> dp(m + 1, vector<long long>(n + 1, LLONG_MAX / 2));
        dp[0][0] = 0;
        
        for (int j = 1; j <= n; j++) {
            dp[0][j] = 0;  // 0 robots can be repaired with any number of factories
            int limit = factory[j - 1][1];
            for (int i = 1; i <= m; i++) {
                // Not use j-th factory
                dp[i][j] = dp[i][j - 1];
                
                // Use j-th factory
                long long totalDist = 0;
                for (int k = 1; k <= limit && k <= i; k++) {
                    totalDist += abs(robot[i - k] - factory[j - 1][0]);
                    dp[i][j] = min(dp[i][j], dp[i - k][j - 1] + totalDist);
                }
            }
        }
        
        return dp[m][n];            
    }
};
