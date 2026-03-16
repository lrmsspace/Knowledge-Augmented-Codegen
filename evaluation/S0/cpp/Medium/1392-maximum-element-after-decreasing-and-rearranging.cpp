// Source: https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of positive integers arr. Perform some operations (possibly none) on arr so that it satisfies these conditions:
//
//
// 	The value of the first element in arr must be 1.
// 	The absolute difference between any 2 adjacent elements must be less than or equal to 1. In other words, abs(arr[i] - arr[i - 1]) <= 1 for each i where 1 <= i < arr.length (0-indexed). abs(x) is the absolute value of x.
//
//
// There are 2 types of operations that you can perform any number of times:
//
//
// 	Decrease the value of any element of arr to a smaller positive integer.
// 	Rearrange the elements of arr to be in any order.
//
//
// Return the maximum possible value of an element in arr after performing the operations to satisfy the conditions.
//
// Example:
// Input: arr = [2,2,1,2,1]
// Output: 2
// Explanation: 
// We can satisfy the conditions by rearranging arr so it becomes [1,2,2,2,1].
// The largest element in arr is 2.
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i] <= 109
//

class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int n = arr.size();
        vector<int> count(n + 1, 0);

        // Count occurrences of each number, capped at n
        for (int num : arr) {
            if (num <= n) {
                count[num]++;
            } else {
                count[n]++;
            }
        }

        int maxValue = 0;
        int available = 0;

        // Iterate through possible values from 1 to n
        for (int i = 1; i <= n; ++i) {
            available += count[i];
            if (available > 0) {
                maxValue = i;
                available--; // Use one occurrence for this value
            }
        }

        return maxValue;            
    }
};
