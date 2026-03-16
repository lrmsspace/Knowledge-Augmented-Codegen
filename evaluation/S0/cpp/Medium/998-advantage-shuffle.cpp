// Source: https://leetcode.com/problems/advantage-shuffle/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 both of the same length. The advantage of nums1 with respect to nums2 is the number of indices i for which nums1[i] > nums2[i].
//
// Return any permutation of nums1 that maximizes its advantage with respect to nums2.
//
// Example:
// Input: nums1 = [2,7,11,15], nums2 = [1,10,4,11]
// Output: [2,11,7,15]
//
// Constraints:
// 1 <= nums1.length <= 105
// 	nums2.length == nums1.length
// 	0 <= nums1[i], nums2[i] <= 109
//

class Solution {
public:
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> sortedNums1 = nums1;
        sort(sortedNums1.begin(), sortedNums1.end());

        // Pair each element in nums2 with its index and sort by value
        vector<pair<int, int>> indexedNums2(n);
        for (int i = 0; i < n; ++i) {
            indexedNums2[i] = {nums2[i], i};
        }
        sort(indexedNums2.begin(), indexedNums2.end());

        vector<int> result(n);
        int left = 0;
        int right = n - 1;

        // Greedily assign elements from nums1 to maximize advantage
        for (const auto& [value, index] : indexedNums2) {
            if (sortedNums1[right] > value) {
                result[index] = sortedNums1[right];
                --right;
            } else {
                result[index] = sortedNums1[left];
                ++left;
            }
        }

        return result;          
    }
};
