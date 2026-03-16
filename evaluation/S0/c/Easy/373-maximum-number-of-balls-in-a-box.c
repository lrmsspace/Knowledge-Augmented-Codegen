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

int countBalls(int lowLimit, int highLimit) {
    int boxCounts[46] = {0}; // Maximum sum of digits for 105 is 45
    int maxCount = 0;

    for (int ballNumber = lowLimit; ballNumber <= highLimit; ballNumber++) {
        int sumOfDigits = 0;
        int num = ballNumber;

        // Calculate the sum of digits
        while (num > 0) {
            sumOfDigits += num % 10;
            num /= 10;
        }

        // Increment the count for the corresponding box
        boxCounts[sumOfDigits]++;

        // Update maxCount if necessary
        if (boxCounts[sumOfDigits] > maxCount) {
            maxCount = boxCounts[sumOfDigits];
        }
    }

    return maxCount;        
}
