// Source: https://leetcode.com/problems/top-k-frequent-elements/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
//
// Example:
// Input: nums = [1,1,1,2,2,3], k = 2
//
// Output: [1,2]
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
// 	k is in the range [1, the number of unique elements in the array].
// 	It is guaranteed that the answer is unique.
//
//
//  
// Follow up: Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
//

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freqMap;
        for (int num : nums) {
            freqMap[num]++;
        }

        // Min-heap to store the top k frequent elements
        auto cmp = [](pair<int, int>& a, pair<int, int>& b) {
            return a.second > b.second; // Min-heap based on frequency
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);

        for (const auto& entry : freqMap) {
            minHeap.push({entry.first, entry.second});
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }

        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().first);
            minHeap.pop();
        }
        return result;          
    }
};
