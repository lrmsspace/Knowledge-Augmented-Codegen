// Source: https://leetcode.com/problems/subarray-with-elements-greater-than-varying-threshold/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer threshold.
//
// Find any subarray of nums of length k such that every element in the subarray is greater than threshold / k.
//
// Return the size of any such subarray. If there is no such subarray, return -1.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,3,4,3,1], threshold = 6
// Output: 3
// Explanation: The subarray [3,4,3] has a size of 3, and every element is greater than 6 / 3 = 2.
// Note that this is the only valid subarray.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i], threshold <= 109
//

class Solution {
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        int n = nums.size();
        stack<int> st;
        st.push(-1);  // Sentinel
        
        for (int i = 0; i <= n; i++) {
            int cur = (i == n) ? 0 : nums[i];
            
            while (st.top() != -1 && nums[st.top()] * (i - st.top()) <= threshold) {
                int idx = st.top();
                st.pop();
                
                if (nums[idx] * (i - st.top() - 1) > threshold) {
                    return i - st.top() - 1;
                }
            }
            
            st.push(i);
        }
        
        return -1;          
    }
};
