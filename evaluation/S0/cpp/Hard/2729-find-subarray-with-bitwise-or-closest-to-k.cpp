// Source: https://leetcode.com/problems/find-subarray-with-bitwise-or-closest-to-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums and an integer k. You need to find a subarray of nums such that the absolute difference between k and the bitwise OR of the subarray elements is as small as possible. In other words, select a subarray nums[l..r] such that |k - (nums[l] OR nums[l + 1] ... OR nums[r])| is minimum.
//
// Return the minimum possible value of the absolute difference.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,4,5], k = 3
//
// Output: 0
//
// Explanation:
//
// The subarray nums[0..1] has OR value 3, which gives the minimum absolute difference |3 - 3| = 0.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 109
//

class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        int n = nums.size();
        int result = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            int currOr = 0;
            for (int j = i; j < n; j++) {
                currOr |= nums[j];
                result = min(result, abs(k - currOr));
                
                // Early stopping if we reach k
                if (currOr == k) {
                    return 0;
                }
            }
        }
        
        return result;          
    }
};
