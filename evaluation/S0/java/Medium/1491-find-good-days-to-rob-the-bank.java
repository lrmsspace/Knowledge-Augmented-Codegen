// Source: https://leetcode.com/problems/find-good-days-to-rob-the-bank/   |   Difficulty: Medium
//
// Problem Description:
// You and a gang of thieves are planning on robbing a bank. You are given a 0-indexed integer array security, where security[i] is the number of guards on duty on the ith day. The days are numbered starting from 0. You are also given an integer time.
//
// The ith day is a good day to rob the bank if:
//
//
// 	There are at least time days before and after the ith day,
// 	The number of guards at the bank for the time days before i are non-increasing, and
// 	The number of guards at the bank for the time days after i are non-decreasing.
//
//
// More formally, this means day i is a good day to rob the bank if and only if security[i - time] >= security[i - time + 1] >= ... >= security[i] <= ... <= security[i + time - 1] <= security[i + time].
//
// Return a list of all days (0-indexed) that are good days to rob the bank. The order that the days are returned in does not matter.
//
// Example:
// Input: security = [5,3,3,3,5,6,2], time = 2
// Output: [2,3]
// Explanation:
// On day 2, we have security[0] >= security[1] >= security[2] <= security[3] <= security[4].
// On day 3, we have security[1] >= security[2] >= security[3] <= security[4] <= security[5].
// No other days satisfy this condition, so days 2 and 3 are the only good days to rob the bank.
//
// Constraints:
// 1 <= security.length <= 105
// 	0 <= security[i], time <= 105
//

class Solution {
    public List<Integer> goodDaysToRobBank(int[] security, int time) {
        List<Integer> result = new ArrayList<>();
        int n = security.length;
        if (n == 0 || time == 0) {
            for (int i = 0; i < n; i++) {
                result.add(i);
            }
            return result;
        }

        int[] nonIncreasing = new int[n];
        int[] nonDecreasing = new int[n];

        // Calculate non-increasing days before each day
        for (int i = 1; i < n; i++) {
            if (security[i] <= security[i - 1]) {
                nonIncreasing[i] = nonIncreasing[i - 1] + 1;
            }
        }

        // Calculate non-decreasing days after each day
        for (int i = n - 2; i >= 0; i--) {
            if (security[i] <= security[i + 1]) {
                nonDecreasing[i] = nonDecreasing[i + 1] + 1;
            }
        }

        // Find all good days to rob the bank
        for (int i = time; i < n - time; i++) {
            if (nonIncreasing[i] >= time && nonDecreasing[i] >= time) {
                result.add(i);
            }
        }

        return result;          
    }
}
