// Source: https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/   |   Difficulty: Hard
//
// Problem Description:
// You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.
//
// We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.
//
// Example:
// Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
// Output: [20,24]
// Explanation: 
// List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
// List 2: [0, 9, 12, 20], 20 is in range [20,24].
// List 3: [5, 18, 22, 30], 22 is in range [20,24].
//
// Constraints:
// nums.length == k
// 	1 <= k <= 3500
// 	1 <= nums[i].length <= 50
// 	-105 <= nums[i][j] <= 105
// 	nums[i] is sorted in non-decreasing order.
//

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        typedef pair<int, pair<int, int>> Node; // value, (list index, element index)
        auto cmp = [](const Node& a, const Node& b) {
            return a.first > b.first; // min-heap
        };
        
        priority_queue<Node, vector<Node>, decltype(cmp)> minHeap(cmp);
        int currentMax = INT_MIN;
        
        // Initialize the heap with the first element of each list
        for (int i = 0; i < nums.size(); i++) {
            minHeap.push({nums[i][0], {i, 0}});
            currentMax = max(currentMax, nums[i][0]);
        }
        
        int rangeStart = -100000, rangeEnd = 100000;
        
        while (minHeap.size() == nums.size()) {
            auto [currentMin, indices] = minHeap.top();
            minHeap.pop();
            int listIdx = indices.first;
            int elemIdx = indices.second;
            
            // Update the range if it's smaller
            if (currentMax - currentMin < rangeEnd - rangeStart) {
                rangeStart = currentMin;
                rangeEnd = currentMax;
            }
            
            // If there's a next element in the same list, add it to the heap
            if (elemIdx + 1 < nums[listIdx].size()) {
                int nextVal = nums[listIdx][elemIdx + 1];
                minHeap.push({nextVal, {listIdx, elemIdx + 1}});
                currentMax = max(currentMax, nextVal);
            }
        }
        
        return {rangeStart, rangeEnd};          
    }
};
