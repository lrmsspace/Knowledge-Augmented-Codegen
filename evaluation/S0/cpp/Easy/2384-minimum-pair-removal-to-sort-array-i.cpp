// Source: https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/   |   Difficulty: Easy
//
// Problem Description:
// Given an array nums, you can perform the following operation any number of times:
//
//
// 	Select the adjacent pair with the minimum sum in nums. If multiple such pairs exist, choose the leftmost one.
// 	Replace the pair with their sum.
//
//
// Return the minimum number of operations needed to make the array non-decreasing.
//
// An array is said to be non-decreasing if each element is greater than or equal to its previous element (if it exists).
//
// Example:
// Input: nums = [5,2,3,1]
//
// Output: 2
//
// Explanation:
//
//
// 	The pair (3,1) has the minimum sum of 4. After replacement, nums = [5,2,4].
// 	The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
//
//
// The array nums became non-decreasing in two operations.
//
// Constraints:
// 1 <= nums.length <= 50
// 	-1000 <= nums[i] <= 1000
//

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        int operations = 0;

        while (true) {
            bool isNonDecreasing = true;
            for (int i = 1; i < n; ++i) {
                if (nums[i] < nums[i - 1]) {
                    isNonDecreasing = false;
                    break;
                }
            }
            if (isNonDecreasing) {
                break;
            }

            int minSum = INT_MAX;
            int minIndex = -1;
            for (int i = 0; i < n - 1; ++i) {
                int currentSum = nums[i] + nums[i + 1];
                if (currentSum < minSum) {
                    minSum = currentSum;
                    minIndex = i;
                }
            }

            nums[minIndex] = minSum;
            nums.erase(nums.begin() + minIndex + 1);
            --n;
            ++operations;
        }

        return operations;          
    }
};
