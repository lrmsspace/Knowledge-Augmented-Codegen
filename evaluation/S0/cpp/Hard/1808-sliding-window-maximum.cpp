// Source: https://leetcode.com/problems/sliding-window-maximum/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
//
// Return the max sliding window.
//
// Example:
// Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
// Output: [3,3,5,5,6,7]
// Explanation: 
// Window position                Max
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       3
//  1 [3  -1  -3] 5  3  6  7       3
//  1  3 [-1  -3  5] 3  6  7       5
//  1  3  -1 [-3  5  3] 6  7       5
//  1  3  -1  -3 [5  3  6] 7       6
//  1  3  -1  -3  5 [3  6  7]      7
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
// 	1 <= k <= nums.length
//

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq; // stores indices
        vector<int> result;
        
        for (int i = 0; i < nums.size(); i++) {
            // Remove elements out of the current window
            if (!dq.empty() && dq.front() == i - k) {
                dq.pop_front();
            }
            
            // Remove elements smaller than the current element from the back
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            
            // Add current element at the back of the deque
            dq.push_back(i);
            
            // The front of the deque is the largest element for the current window
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        
        return result;          
    }
};
