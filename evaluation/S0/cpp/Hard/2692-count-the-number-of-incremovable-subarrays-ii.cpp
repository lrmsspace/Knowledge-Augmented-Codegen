// Source: https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of positive integers nums.
//
// A subarray of nums is called incremovable if nums becomes strictly increasing on removing the subarray. For example, the subarray [3, 4] is an incremovable subarray of [5, 3, 4, 6, 7] because removing this subarray changes the array [5, 3, 4, 6, 7] to [5, 6, 7] which is strictly increasing.
//
// Return the total number of incremovable subarrays of nums.
//
// Note that an empty array is considered strictly increasing.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 10
// Explanation: The 10 incremovable subarrays are: [1], [2], [3], [4], [1,2], [2,3], [3,4], [1,2,3], [2,3,4], and [1,2,3,4], because on removing any one of these subarrays nums becomes strictly increasing. Note that you cannot select an empty subarray.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    long long incremovableSubarrayCount(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n), right(n);
        
        // Compute left array
        left[0] = 1;
        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1]) {
                left[i] = left[i - 1] + 1;
            } else {
                left[i] = 1;
            }
        }
        
        // Compute right array
        right[n - 1] = 1;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < nums[i + 1]) {
                right[i] = right[i + 1] + 1;
            } else {
                right[i] = 1;
            }
        }
        
        long long total = 0;
        
        // Count single element subarrays
        total += n;
        
        // Count longer subarrays
        for (int i = 0; i < n; i++) {
            // Extend to the left
            for (int len = 2; len <= left[i]; len++) {
                total++;
            }
            // Extend to the right
            for (int len = 2; len <= right[i]; len++) {
                total++;
            }
            // Combine left and right
            if (i > 0 && i < n - 1 && nums[i - 1] < nums[i + 1]) {
                total += (long long)(left[i - 1]) * (right[i + 1]);
            }
        }
        
        return total;           
    }
};
