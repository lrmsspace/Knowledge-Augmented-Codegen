// Source: https://leetcode.com/problems/minimum-operations-to-collect-elements/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array nums of positive integers and an integer k.
//
// In one operation, you can remove the last element of the array and add it to your collection.
//
// Return the minimum number of operations needed to collect elements 1, 2, ..., k.
//
// Example:
// Input: nums = [3,1,5,4,2], k = 2
// Output: 4
// Explanation: After 4 operations, we collect elements 2, 4, 5, and 1, in this order. Our collection contains elements 1 and 2. Hence, the answer is 4.
//
// Constraints:
// 1 <= nums.length <= 50
// 	1 <= nums[i] <= nums.length
// 	1 <= k <= nums.length
// 	The input is generated such that you can collect elements 1, 2, ..., k.
//

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int n = nums.size();
        int count = 0;

        for (int i = n - 1; i >= 0; --i) {
            if (nums[i] <= k) {
                ++count;
                if (count == k) {
                    return n - i;
                }
            }
        }

        return -1; // This line should never be reached due to problem constraints          
    }
};
