// Source: https://leetcode.com/problems/count-partitions-with-even-sum-difference/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums of length n.
//
// A partition is defined as an index i where 0 <= i < n - 1, splitting the array into two non-empty subarrays such that:
//
//
// 	Left subarray contains indices [0, i].
// 	Right subarray contains indices [i + 1, n - 1].
//
//
// Return the number of partitions where the difference between the sum of the left and right subarrays is even.
//
// Example:
// Input: nums = [10,10,3,7,6]
//
// Output: 4
//
// Explanation:
//
// The 4 partitions are:
//
//
// 	[10], [10, 3, 7, 6] with a sum difference of 10 - 26 = -16, which is even.
// 	[10, 10], [3, 7, 6] with a sum difference of 20 - 16 = 4, which is even.
// 	[10, 10, 3], [7, 6] with a sum difference of 23 - 13 = 10, which is even.
// 	[10, 10, 3, 7], [6] with a sum difference of 30 - 6 = 24, which is even.
//
// Constraints:
// 2 <= n == nums.length <= 100
// 	1 <= nums[i] <= 100
//

class Solution {
public:
    int countPartitions(vector<int>& nums) {
        int evenCount = 0;
        int oddCount = 0;
        int n = nums.size();

        // Count even and odd numbers in the array
        for (int num : nums) {
            if (num % 2 == 0) {
                evenCount++;
            } else {
                oddCount++;
            }
        }

        int partitionCount = 0;

        // Iterate through possible partition points
        for (int i = 0; i < n - 1; i++) {
            // Check if the left subarray has an even sum
            if ((i + 1 - oddCount) % 2 == 0) {
                partitionCount++;
            }
            // Update counts based on the current element
            if (nums[i] % 2 == 0) {
                evenCount--;
            } else {
                oddCount--;
            }
        }

        return partitionCount;          
    }
};
