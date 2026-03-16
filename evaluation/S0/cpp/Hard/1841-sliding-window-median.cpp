// Source: https://leetcode.com/problems/sliding-window-median/   |   Difficulty: Hard
//
// Problem Description:
// The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.
//
//
// 	For examples, if arr = [2,3,4], the median is 3.
// 	For examples, if arr = [1,2,3,4], the median is (2 + 3) / 2 = 2.5.
//
//
// You are given an integer array nums and an integer k. There is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
//
// Return the median array for each window in the original array. Answers within 10-5 of the actual value will be accepted.
//
// Example:
// Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
// Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
// Explanation: 
// Window position                Median
// ---------------                -----
// [1  3  -1] -3  5  3  6  7        1
//  1 [3  -1  -3] 5  3  6  7       -1
//  1  3 [-1  -3  5] 3  6  7       -1
//  1  3  -1 [-3  5  3] 6  7        3
//  1  3  -1  -3 [5  3  6] 7        5
//  1  3  -1  -3  5 [3  6  7]       6
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	-231 <= nums[i] <= 231 - 1
//

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> result;
        multiset<int> lo; // max heap (lower half)
        multiset<int> hi; // min heap (upper half)

        auto addNum = [&](int num) {
            if (lo.empty() || num <= *lo.rbegin()) {
                lo.insert(num);
            } else {
                hi.insert(num);
            }

            // Balance the sizes
            if (lo.size() > hi.size() + 1) {
                hi.insert(*lo.rbegin());
                lo.erase(prev(lo.end()));
            } else if (hi.size() > lo.size()) {
                lo.insert(*hi.begin());
                hi.erase(hi.begin());
            }
        };

        auto removeNum = [&](int num) {
            if (lo.find(num) != lo.end()) {
                lo.erase(lo.find(num));
            } else {
                hi.erase(hi.find(num));
            }

            // Balance the sizes
            if (lo.size() > hi.size() + 1) {
                hi.insert(*lo.rbegin());
                lo.erase(prev(lo.end()));
            } else if (hi.size() > lo.size()) {
                lo.insert(*hi.begin());
                hi.erase(hi.begin());
            }
        };

        for (int i = 0; i < nums.size(); i++) {
            addNum(nums[i]);
            if (i >= k - 1) {
                // Calculate median
                if (k % 2 == 0) {
                    double median = ((double)*lo.rbegin() + (double)*hi.begin()) / 2.0;
                    result.push_back(median);
                } else {
                    result.push_back((double)*lo.rbegin());
                }
                removeNum(nums[i - k + 1]);
            }
        }

        return result;          
    }
};
