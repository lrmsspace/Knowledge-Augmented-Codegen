// Source: https://leetcode.com/problems/two-out-of-three/   |   Difficulty: Easy
//
// Problem Description:
// Given three integer arrays nums1, nums2, and nums3, return a distinct array containing all the values that are present in at least two out of the three arrays. You may return the values in any order.
//
// Example:
// Input: nums1 = [1,1,3,2], nums2 = [2,3], nums3 = [3]
// Output: [3,2]
// Explanation: The values that are present in at least two arrays are:
// - 3, in all three arrays.
// - 2, in nums1 and nums2.
//
// Constraints:
// 1 <= nums1.length, nums2.length, nums3.length <= 100
// 	1 <= nums1[i], nums2[j], nums3[k] <= 100
//

class Solution {
public:
    vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {
        vector<int> count(101, 0);
        vector<int> result;

        auto markPresence = [&](const vector<int>& nums) {
            vector<bool> seen(101, false);
            for (int num : nums) {
                if (!seen[num]) {
                    count[num]++;
                    seen[num] = true;
                }
            }
        };

        markPresence(nums1);
        markPresence(nums2);
        markPresence(nums3);

        for (int i = 1; i <= 100; ++i) {
            if (count[i] >= 2) {
                result.push_back(i);
            }
        }

        return result;          
    }
};
