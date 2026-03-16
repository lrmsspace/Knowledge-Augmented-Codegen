// Source: https://leetcode.com/problems/equal-sum-arrays-with-minimum-number-of-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays of integers nums1 and nums2, possibly of different lengths. The values in the arrays are between 1 and 6, inclusive.
//
// In one operation, you can change any integer's value in any of the arrays to any value between 1 and 6, inclusive.
//
// Return the minimum number of operations required to make the sum of values in nums1 equal to the sum of values in nums2. Return -1​​​​​ if it is not possible to make the sum of the two arrays equal.
//
// Example:
// Input: nums1 = [1,2,3,4,5,6], nums2 = [1,1,2,2,2,2]
// Output: 3
// Explanation: You can make the sums of nums1 and nums2 equal with 3 operations. All indices are 0-indexed.
// - Change nums2[0] to 6. nums1 = [1,2,3,4,5,6], nums2 = [6,1,2,2,2,2].
// - Change nums1[5] to 1. nums1 = [1,2,3,4,5,1], nums2 = [6,1,2,2,2,2].
// - Change nums1[2] to 2. nums1 = [1,2,2,4,5,1], nums2 = [6,1,2,2,2,2].
//
// Constraints:
// 1 <= nums1.length, nums2.length <= 105
// 	1 <= nums1[i], nums2[i] <= 6
//

class Solution {
public:
    int minOperations(vector<int>& nums1, vector<int>& nums2) {
        int sum1 = accumulate(nums1.begin(), nums1.end(), 0);
        int sum2 = accumulate(nums2.begin(), nums2.end(), 0);
        
        if (sum1 < sum2) {
            return minOperations(nums2, nums1);
        }
        
        int diff = sum1 - sum2;
        vector<int> count(7, 0);
        
        for (int num : nums1) {
            count[num]++;
        }
        
        for (int num : nums2) {
            count[7 - num]++;
        }
        
        int operations = 0;
        
        for (int change = 5; change >= 1 && diff > 0; --change) {
            while (count[change] > 0 && diff > 0) {
                diff -= change;
                count[change]--;
                operations++;
            }
        }
        
        return diff > 0 ? -1 : operations;          
    }
};
