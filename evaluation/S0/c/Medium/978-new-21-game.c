// Source: https://leetcode.com/problems/new-21-game/   |   Difficulty: Medium
//
// Problem Description:
// Alice plays the following game, loosely based on the card game "21".
//
// Alice starts with 0 points and draws numbers while she has less than k points. During each draw, she gains an integer number of points randomly from the range [1, maxPts], where maxPts is an integer. Each draw is independent and the outcomes have equal probabilities.
//
// Alice stops drawing numbers when she gets k or more points.
//
// Return the probability that Alice has n or fewer points.
//
// Answers within 10-5 of the actual answer are considered accepted.
//
// Example:
// Input: n = 10, k = 1, maxPts = 10
// Output: 1.00000
// Explanation: Alice gets a single card, then stops.
//
// Constraints:
// 0 <= k <= n <= 104
// 	1 <= maxPts <= 104
//

double new21Game(int n, int k, int maxPts) {
    if (k == 0 || n >= k + maxPts) {
        return 1.0;
    }

    double dp[n + 1];
    for (int i = 0; i <= n; i++) {
        dp[i] = 0.0;
    }
    dp[0] = 1.0;

    double windowSum = 1.0;
    double result = 0.0;

    for (int points = 1; points <= n; points++) {
        dp[points] = windowSum / maxPts;

        if (points < k) {
            windowSum += dp[points];
        } else {
            result += dp[points];
        }

        if (points - maxPts >= 0) {
            windowSum -= dp[points - maxPts];
        }
    }

    return result;      
}
