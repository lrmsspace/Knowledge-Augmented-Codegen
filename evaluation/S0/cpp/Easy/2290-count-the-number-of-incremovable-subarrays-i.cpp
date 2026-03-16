// Source: https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-i/   |   Difficulty: Easy
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
// 1 <= nums.length <= 50
// 	1 <= nums[i] <= 50
//

class Solution {
public:
    int incremovableSubarrayCount(vector<int>& nums) {
        int n = nums.size();
        int count = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                vector<int> temp;
                for (int k = 0; k < n; ++k) {
                    if (k < i || k > j) {
                        temp.push_back(nums[k]);
                    }
                }

                bool isIncreasing = true;
                for (int k = 1; k < temp.size(); ++k) {
                    if (temp[k] <= temp[k - 1]) {
                        isIncreasing = false;
                        break;
                    }
                }

                if (isIncreasing) {
                    count++;
                }
            }
        }

        return count;           
    }
};
