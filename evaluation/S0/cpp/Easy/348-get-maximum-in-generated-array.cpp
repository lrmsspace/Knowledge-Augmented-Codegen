// Source: https://leetcode.com/problems/get-maximum-in-generated-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer n. A 0-indexed integer array nums of length n + 1 is generated in the following way:
//
//
// 	nums[0] = 0
// 	nums[1] = 1
// 	nums[2 * i] = nums[i] when 2 <= 2 * i <= n
// 	nums[2 * i + 1] = nums[i] + nums[i + 1] when 2 <= 2 * i + 1 <= n
//
//
// Return the maximum integer in the array nums​​​.
//
// Example:
// Input: n = 7
// Output: 3
// Explanation: According to the given rules:
//   nums[0] = 0
//   nums[1] = 1
//   nums[(1 * 2) = 2] = nums[1] = 1
//   nums[(1 * 2) + 1 = 3] = nums[1] + nums[2] = 1 + 1 = 2
//   nums[(2 * 2) = 4] = nums[2] = 1
//   nums[(2 * 2) + 1 = 5] = nums[2] + nums[3] = 1 + 2 = 3
//   nums[(3 * 2) = 6] = nums[3] = 2
//   nums[(3 * 2) + 1 = 7] = nums[3] + nums[4] = 2 + 1 = 3
// Hence, nums = [0,1,1,2,1,3,2,3], and the maximum is max(0,1,1,2,1,3,2,3) = 3.
//
// Constraints:
// 0 <= n <= 100
//

class Solution {
public:
    int getMaximumGenerated(int n) {
        if (n == 0) return 0;
        vector<int> nums(n + 1, 0);
        nums[0] = 0;
        nums[1] = 1;
        int maxVal = 1;

        for (int i = 1; i <= n / 2; ++i) {
            int evenIndex = 2 * i;
            int oddIndex = 2 * i + 1;

            if (evenIndex <= n) {
                nums[evenIndex] = nums[i];
                maxVal = max(maxVal, nums[evenIndex]);
            }

            if (oddIndex <= n) {
                nums[oddIndex] = nums[i] + nums[i + 1];
                maxVal = max(maxVal, nums[oddIndex]);
            }
        }

        return maxVal;          
    }
};
