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

int racecar(int target) {
    int maxT = target * 2;
    int *dp = (int*)malloc((maxT + 1) * sizeof(int));
    for (int i = 0; i <= maxT; i++) dp[i] = 10000;
    dp[0] = 0;
    for (int t = 1; t <= target; t++) {
        for (int n = 1, pos = 1; pos - 1 < t; n++, pos = (1 << n) - 1) {
            if (pos == t) {
                dp[t] = n;
                break;
            }
            /* overshoot and reverse */
            if (pos > t) {
                dp[t] = (dp[t] < n + 1 + dp[pos - t]) ? dp[t] : (n + 1 + dp[pos - t]);
            }
            /* undershoot and reverse twice */
            for (int m = 0, backPos = 0; backPos < pos; m++, backPos = (1 << m) - 1) {
                int curr = n + 1 + m + 1 + dp[t - (pos - backPos)];
                dp[t] = (dp[t] < curr) ? dp[t] : curr;
            }
        }
    }
    int res = dp[target];
    free(dp);
    return res;     
}
