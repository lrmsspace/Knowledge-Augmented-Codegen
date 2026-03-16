// Source: https://leetcode.com/problems/maximum-profit-of-operating-a-centennial-wheel/   |   Difficulty: Medium
//
// Problem Description:
// You are the operator of a Centennial Wheel that has four gondolas, and each gondola has room for up to four people. You have the ability to rotate the gondolas counterclockwise, which costs you runningCost dollars.
//
// You are given an array customers of length n where customers[i] is the number of new customers arriving just before the ith rotation (0-indexed). This means you must rotate the wheel i times before the customers[i] customers arrive. You cannot make customers wait if there is room in the gondola. Each customer pays boardingCost dollars when they board on the gondola closest to the ground and will exit once that gondola reaches the ground again.
//
// You can stop the wheel at any time, including before serving all customers. If you decide to stop serving customers, all subsequent rotations are free in order to get all the customers down safely. Note that if there are currently more than four customers waiting at the wheel, only four will board the gondola, and the rest will wait for the next rotation.
//
// Return the minimum number of rotations you need to perform to maximize your profit. If there is no scenario where the profit is positive, return -1.
//
// Example:
// Input: customers = [8,3], boardingCost = 5, runningCost = 6
// Output: 3
// Explanation: The numbers written on the gondolas are the number of people currently there.
// 1. 8 customers arrive, 4 board and 4 wait for the next gondola, the wheel rotates. Current profit is 4 * $5 - 1 * $6 = $14.
// 2. 3 customers arrive, the 4 waiting board the wheel and the other 3 wait, the wheel rotates. Current profit is 8 * $5 - 2 * $6 = $28.
// 3. The final 3 customers board the gondola, the wheel rotates. Current profit is 11 * $5 - 3 * $6 = $37.
// The highest profit was $37 after rotating the wheel 3 times.
//
// Constraints:
// n == customers.length
// 	1 <= n <= 105
// 	0 <= customers[i] <= 50
// 	1 <= boardingCost, runningCost <= 100
//

class Solution {
    public int minOperationsMaxProfit(int[] customers, int boardingCost, int runningCost) {
        int waitingCustomers = 0;
        int totalCustomers = 0;
        int maxProfit = 0;
        int rotationsAtMaxProfit = -1;
        int currentProfit = 0;
        int rotationCount = 0;
        int i = 0;

        while (i < customers.length || waitingCustomers > 0) {
            if (i < customers.length) {
                waitingCustomers += customers[i];
            }

            int boardingNow = Math.min(4, waitingCustomers);
            waitingCustomers -= boardingNow;
            totalCustomers += boardingNow;
            rotationCount++;

            currentProfit = totalCustomers * boardingCost - rotationCount * runningCost;

            if (currentProfit > maxProfit) {
                maxProfit = currentProfit;
                rotationsAtMaxProfit = rotationCount;
            }

            i++;
        }

        return maxProfit > 0 ? rotationsAtMaxProfit : -1;           
    }
}
