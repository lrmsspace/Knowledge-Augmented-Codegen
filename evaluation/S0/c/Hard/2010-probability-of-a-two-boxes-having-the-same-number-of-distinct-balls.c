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

double getProbability(int* balls, int ballsSize) {
    int totalBalls = 0;
    for (int i = 0; i < ballsSize; ++i) {
        totalBalls += balls[i];
    }
    int halfBalls = totalBalls / 2;

    double factorials[13];
    factorials[0] = 1.0;
    for (int i = 1; i <= 12; ++i) {
        factorials[i] = factorials[i - 1] * i;
    }

    double validWays = 0.0;
    double totalWays = 0.0;

    void backtrack(int index, int box1Count, int box2Count, double waysBox1, double waysBox2) {
        if (index == ballsSize) {
            if (box1Count == halfBalls && box2Count == halfBalls) {
                totalWays += waysBox1 * waysBox2;
                int distinctBox1 = 0, distinctBox2 = 0;
                for (int i = 0; i < ballsSize; ++i) {
                    if (balls[i] > 0) {
                        distinctBox1 += (balls[i] > 0);
                        distinctBox2 += (balls[i] > 0);
                    }
                }
                if (distinctBox1 == distinctBox2) {
                    validWays += waysBox1 * waysBox2;
                }
            }
            return;
        }

        for (int countInBox1 = 0; countInBox1 <= balls[index]; ++countInBox1) {
            int countInBox2 = balls[index] - countInBox1;
            backtrack(index + 1,
                      box1Count + countInBox1,
                      box2Count + countInBox2,
                      waysBox1 * factorials[balls[index]] / (factorials[countInBox1] * factorials[countInBox2]),
                      waysBox2);
        }
    }

    backtrack(0, 0, 0, 1.0, 1.0);

    return validWays / totalWays;       
}
