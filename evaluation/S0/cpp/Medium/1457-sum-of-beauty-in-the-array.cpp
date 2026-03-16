// Source: https://leetcode.com/problems/sum-of-beauty-in-the-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. For each index i (1 <= i <= nums.length - 2) the beauty of nums[i] equals:
//
//
// 	2, if nums[j] < nums[i] < nums[k], for all 0 <= j < i and for all i < k <= nums.length - 1.
// 	1, if nums[i - 1] < nums[i] < nums[i + 1], and the previous condition is not satisfied.
// 	0, if none of the previous conditions holds.
//
//
// Return the sum of beauty of all nums[i] where 1 <= i <= nums.length - 2.
//
// Example:
// Input: nums = [1,2,3]
// Output: 2
// Explanation: For each index i in the range 1 <= i <= 1:
// - The beauty of nums[1] equals 2.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
public:
    int sumOfBeauties(vector<int>& nums) {
        int n = nums.size();
        vector<int> leftMin(n, 0);
        vector<int> rightMax(n, 0);

        leftMin[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            leftMin[i] = min(leftMin[i - 1], nums[i]);
        }

        rightMax[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            rightMax[i] = max(rightMax[i + 1], nums[i]);
        }

        int totalBeauty = 0;
        for (int i = 1; i <= n - 2; ++i) {
            if (leftMin[i - 1] < nums[i] && nums[i] < rightMax[i + 1]) {
                totalBeauty += 2;
            } else if (nums[i - 1] < nums[i] && nums[i] < nums[i + 1]) {
                totalBeauty += 1;
            }
        }

        return totalBeauty;         
    }
};
