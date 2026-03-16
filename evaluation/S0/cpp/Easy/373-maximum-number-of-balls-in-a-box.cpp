// Source: https://leetcode.com/problems/maximum-number-of-balls-in-a-box/   |   Difficulty: Easy
//
// Problem Description:
// You are working in a ball factory where you have n balls numbered from lowLimit up to highLimit inclusive (i.e., n == highLimit - lowLimit + 1), and an infinite number of boxes numbered from 1 to infinity.
//
// Your job at this factory is to put each ball in the box with a number equal to the sum of digits of the ball's number. For example, the ball number 321 will be put in the box number 3 + 2 + 1 = 6 and the ball number 10 will be put in the box number 1 + 0 = 1.
//
// Given two integers lowLimit and highLimit, return the number of balls in the box with the most balls.
//
// Example:
// Input: lowLimit = 1, highLimit = 10
// Output: 2
// Explanation:
// Box Number:  1 2 3 4 5 6 7 8 9 10 11 ...
// Ball Count:  2 1 1 1 1 1 1 1 1 0  0  ...
// Box 1 has the most number of balls with 2 balls.
//
// Constraints:
// 1 <= lowLimit <= highLimit <= 105
//

class Solution {
public:
    int countBalls(int lowLimit, int highLimit) {
        vector<int> box(46, 0); // max sum of digits for 10^5 is 45
        int maxBalls = 0;

        for (int ballNumber = lowLimit; ballNumber <= highLimit; ++ballNumber) {
            int sumOfDigits = 0;
            int num = ballNumber;

            while (num > 0) {
                sumOfDigits += num % 10;
                num /= 10;
            }

            box[sumOfDigits]++;
            maxBalls = max(maxBalls, box[sumOfDigits]);
        }

        return maxBalls;            
    }
};
