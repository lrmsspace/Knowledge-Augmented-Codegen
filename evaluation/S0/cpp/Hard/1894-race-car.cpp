// Source: https://leetcode.com/problems/race-car/   |   Difficulty: Hard
//
// Problem Description:
// Your car starts at position 0 and speed +1 on an infinite number line. Your car can go into negative positions. Your car drives automatically according to a sequence of instructions 'A' (accelerate) and 'R' (reverse):
//
//
// 	When you get an instruction 'A', your car does the following:
//
// 	
// 		position += speed
// 		speed *= 2
// 	
// 	
// 	When you get an instruction 'R', your car does the following:
// 	
// 		If your speed is positive then speed = -1
// 		otherwise speed = 1
// 	
// 	Your position stays the same.
//
//
// For example, after commands "AAR", your car goes to positions 0 --> 1 --> 3 --> 3, and your speed goes to 1 --> 2 --> 4 --> -1.
//
// Given a target position target, return the length of the shortest sequence of instructions to get there.
//
// Example:
// Input: target = 3
// Output: 2
// Explanation: 
// The shortest instruction sequence is "AA".
// Your position goes from 0 --> 1 --> 3.
//
// Constraints:
// 1 <= target <= 104
//

class Solution {
public:
    int racecar(int target) {
        vector<int> dp(target + 2, INT_MAX);
        dp[0] = 0;
        
        for (int t = 1; t <= target; t++) {
            for (int k = 1; ; k++) {
                int dist = (1 << k) - 1;  // distance after k 'A's
                if (dist == t) {
                    dp[t] = min(dp[t], k);
                    break;
                } else if (dist > t) {
                    dp[t] = min(dp[t], k + 1 + dp[dist - t]);
                    break;
                } else {
                    // Try reversing before reaching t
                    for (int j = 0; j < k - 1; j++) {
                        int backDist = (1 << j) - 1;  // distance after j 'A's in reverse
                        dp[t] = min(dp[t], k + 1 + j + 1 + dp[t - (dist - backDist)]);
                    }
                }
            }
        }
        
        return dp[target];          
    }
};
