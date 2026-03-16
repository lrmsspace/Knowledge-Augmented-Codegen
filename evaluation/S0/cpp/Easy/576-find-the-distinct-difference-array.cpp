// Source: https://leetcode.com/problems/find-the-distinct-difference-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array nums of length n.
//
// The distinct difference array of nums is an array diff of length n such that diff[i] is equal to the number of distinct elements in the suffix nums[i + 1, ..., n - 1] subtracted from the number of distinct elements in the prefix nums[0, ..., i].
//
// Return the distinct difference array of nums.
//
// Note that nums[i, ..., j] denotes the subarray of nums starting at index i and ending at index j inclusive. Particularly, if i > j then nums[i, ..., j] denotes an empty subarray.
//
// Example:
// Input: nums = [1,2,3,4,5]
// Output: [-3,-1,1,3,5]
// Explanation: For index i = 0, there is 1 element in the prefix and 4 distinct elements in the suffix. Thus, diff[0] = 1 - 4 = -3.
// For index i = 1, there are 2 distinct elements in the prefix and 3 distinct elements in the suffix. Thus, diff[1] = 2 - 3 = -1.
// For index i = 2, there are 3 distinct elements in the prefix and 2 distinct elements in the suffix. Thus, diff[2] = 3 - 2 = 1.
// For index i = 3, there are 4 distinct elements in the prefix and 1 distinct element in the suffix. Thus, diff[3] = 4 - 1 = 3.
// For index i = 4, there are 5 distinct elements in the prefix and no elements in the suffix. Thus, diff[4] = 5 - 0 = 5.
//
// Constraints:
// 1 <= n == nums.length <= 50
// 	1 <= nums[i] <= 50
//

class Solution {
public:
    vector<int> distinctDifferenceArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefixDistinctCount(n, 0);
        vector<int> suffixDistinctCount(n, 0);
        unordered_set<int> prefixSet;
        unordered_set<int> suffixSet;

        // Calculate prefix distinct counts
        for (int i = 0; i < n; ++i) {
            prefixSet.insert(nums[i]);
            prefixDistinctCount[i] = prefixSet.size();
        }

        // Calculate suffix distinct counts
        for (int i = n - 1; i >= 0; --i) {
            suffixSet.insert(nums[i]);
            suffixDistinctCount[i] = suffixSet.size();
        }

        // Calculate the distinct difference array
        vector<int> diff(n, 0);
        for (int i = 0; i < n; ++i) {
            int suffixCount = (i + 1 < n) ? suffixDistinctCount[i + 1] : 0;
            diff[i] = prefixDistinctCount[i] - suffixCount;
        }

        return diff;            
    }
};
