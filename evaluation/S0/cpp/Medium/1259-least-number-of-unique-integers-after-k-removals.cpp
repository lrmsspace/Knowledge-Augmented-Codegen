// Source: https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers arr and an integer k. Find the least number of unique integers after removing exactly k elements.
//
// Example:
// Input: arr = [5,5,4], k = 1
// Output: 1
// Explanation: Remove the single 4, only 5 is left.
//
// Constraints:
// 1 <= arr.length <= 10^5
// 	1 <= arr[i] <= 10^9
// 	0 <= k <= arr.length
//

class Solution {

public:

    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {

        
        unordered_map<int, int> freqMap;
        for (int num : arr) {
            freqMap[num]++;
        }

        // Min-heap based on frequency
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (const auto& entry : freqMap) {
            minHeap.push(entry.second);
        }

        while (k > 0 && !minHeap.empty()) {
            int freq = minHeap.top();
            minHeap.pop();
            if (k >= freq) {
                k -= freq;
            } else {
                // Can't remove this entire number
                minHeap.push(freq); // Push it back
                break;
            }
        }

        return minHeap.size();
    }

};
