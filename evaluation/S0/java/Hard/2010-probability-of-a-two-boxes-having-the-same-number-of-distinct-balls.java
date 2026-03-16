// Source: https://leetcode.com/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/   |   Difficulty: Hard
//
// Problem Description:
// Given 2n balls of k distinct colors. You will be given an integer array balls of size k where balls[i] is the number of balls of color i.
//
// All the balls will be shuffled uniformly at random, then we will distribute the first n balls to the first box and the remaining n balls to the other box (Please read the explanation of the second example carefully).
//
// Please note that the two boxes are considered different. For example, if we have two balls of colors a and b, and two boxes [] and (), then the distribution [a] (b) is considered different than the distribution [b] (a) (Please read the explanation of the first example carefully).
//
// Return the probability that the two boxes have the same number of distinct balls. Answers within 10-5 of the actual value will be accepted as correct.
//
// Example:
// Input: balls = [1,1]
// Output: 1.00000
// Explanation: Only 2 ways to divide the balls equally:
// - A ball of color 1 to box 1 and a ball of color 2 to box 2
// - A ball of color 2 to box 1 and a ball of color 1 to box 2
// In both ways, the number of distinct colors in each box is equal. The probability is 2/2 = 1
//
// Constraints:
// 1 <= balls.length <= 8
// 	1 <= balls[i] <= 6
// 	sum(balls) is even.
//

class Solution {
    public double getProbability(int[] balls) {
        int n = 0;
        for (int b : balls) n += b;
        n /= 2;

        double[][] comb = new double[n + 1][n + 1];
        for (int i = 0; i <= n; i++) {
            comb[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
            }
        }

        double[] res = new double[2];
        backtrack(balls, 0, 0, 0, 0, n, comb, res);
        return res[0] / res[1];                 
    }
}
