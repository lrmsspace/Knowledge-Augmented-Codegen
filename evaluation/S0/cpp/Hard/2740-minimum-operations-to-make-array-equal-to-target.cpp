// Source: https://leetcode.com/problems/minimum-operations-to-make-array-equal-to-target/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integer arrays nums and target, of the same length.
//
// In a single operation, you can select any subarray of nums and increment each element within that subarray by 1 or decrement each element within that subarray by 1.
//
// Return the minimum number of operations required to make nums equal to the array target.
//
// Example:
// Input: nums = [3,5,1,2], target = [4,6,2,4]
//
// Output: 2
//
// Explanation:
//
// We will perform the following operations to make nums equal to target:
// - Increment nums[0..3] by 1, nums = [4,6,2,3].
// - Increment nums[3..3] by 1, nums = [4,6,2,4].
//
// Constraints:
// 1 <= nums.length == target.length <= 105
// 	1 <= nums[i], target[i] <= 108
//

class Solution {
public:
    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        int n = nums.size();
        vector<int> diff(n);
        for (int i = 0; i < n; i++) {
            diff[i] = target[i] - nums[i];
        }
        
        long long operations = 0;
        for (int i = 1; i < n; i++) {
            if (diff[i] != diff[i - 1]) {
                operations += abs(diff[i] - diff[i - 1]);
            }
        }
        operations += abs(diff[0]);
        
        return operations;          
    }
};
