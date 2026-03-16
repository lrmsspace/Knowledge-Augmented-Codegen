// Source: https://leetcode.com/problems/make-array-non-decreasing/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. In one operation, you can select a subarray and replace it with a single element equal to its maximum value.
//
// Return the maximum possible size of the array after performing zero or more operations such that the resulting array is non-decreasing.
//
// Example:
// Input: nums = [4,2,5,3,5]
//
// Output: 3
//
// Explanation:
//
// One way to achieve the maximum size is:
//
//
// 	Replace subarray nums[1..2] = [2, 5] with 5 → [4, 5, 3, 5].
// 	Replace subarray nums[2..3] = [3, 5] with 5 → [4, 5, 5].
//
//
// The final array [4, 5, 5] is non-decreasing with size 3.
//
// Constraints:
// 1 <= nums.length <= 2 * 105
// 	1 <= nums[i] <= 2 * 105
//

class Solution {
public:
    int maximumPossibleSize(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);
        stack<int> st; // Monotonic stack to keep track of non-decreasing sequence

        for (int i = 0; i < n; ++i) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                dp[i] = max(dp[i], dp[st.top()] + 1);
                st.pop();
            }
            st.push(i);
        }

        return *max_element(dp.begin(), dp.end());          
    }
};
