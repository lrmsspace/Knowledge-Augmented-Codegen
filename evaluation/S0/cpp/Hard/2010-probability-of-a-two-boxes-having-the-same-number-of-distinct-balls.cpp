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
public:
    double getProbability(vector<int>& balls) {
        int k = balls.size();
        int n = 0;
        for (int count : balls) {
            n += count;
        }
        n /= 2;
        
        double totalWays = 0.0;
        double validWays = 0.0;
        
        function<void(int, int, int, int, double, double)> backtrack = [&](int colorIdx, int box1Count, int box2Count, int box1Distinct, int box2Distinct, double ways) {
            if (colorIdx == k) {
                if (box1Count == n && box2Count == n) {
                    totalWays += ways;
                    if (box1Distinct == box2Distinct) {
                        validWays += ways;
                    }
                }
                return;
            }
            
            for (int i = 0; i <= balls[colorIdx]; i++) {
                int box1Balls = i;
                int box2Balls = balls[colorIdx] - i;
                
                backtrack(colorIdx + 1,
                          box1Count + box1Balls,
                          box2Count + box2Balls,
                          box1Distinct + (box1Balls > 0 ? 1 : 0),
                          box2Distinct + (box2Balls > 0 ? 1 : 0),
                          ways * comb(balls[colorIdx], box1Balls));
            }
        };
        
        backtrack(0, 0, 0, 0, 0, 1.0);
        
        return validWays / totalWays;           
    }
};
