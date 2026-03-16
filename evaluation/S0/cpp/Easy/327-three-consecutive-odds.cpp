// Source: https://leetcode.com/problems/three-consecutive-odds/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array arr, return true if there are three consecutive odd numbers in the array. Otherwise, return false.
//
// Example:
// Input: arr = [2,6,4,1]
// Output: false
// Explanation: There are no three consecutive odds.
//
// Constraints:
// 1 <= arr.length <= 1000
// 	1 <= arr[i] <= 1000
//

class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int count = 0;
        for (int num : arr) {
            if (num % 2 != 0) {
                count++;
                if (count == 3) {
                    return true;
                }
            } else {
                count = 0;
            }
        }
        return false;           
    }
};
