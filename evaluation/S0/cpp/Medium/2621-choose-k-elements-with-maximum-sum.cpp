// Source: https://leetcode.com/problems/choose-k-elements-with-maximum-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays, nums1 and nums2, both of length n, along with a positive integer k.
//
// For each index i from 0 to n - 1, perform the following:
//
//
// 	Find all indices j where nums1[j] is less than nums1[i].
// 	Choose at most k values of nums2[j] at these indices to maximize the total sum.
//
//
// Return an array answer of size n, where answer[i] represents the result for the corresponding index i.
//
// Example:
// Input: nums1 = [4,2,1,5,3], nums2 = [10,20,30,40,50], k = 2
//
// Output: [80,30,0,80,50]
//
// Explanation:
//
//
// 	For i = 0: Select the 2 largest values from nums2 at indices [1, 2, 4] where nums1[j] < nums1[0], resulting in 50 + 30 = 80.
// 	For i = 1: Select the 2 largest values from nums2 at index [2] where nums1[j] < nums1[1], resulting in 30.
// 	For i = 2: No indices satisfy nums1[j] < nums1[2], resulting in 0.
// 	For i = 3: Select the 2 largest values from nums2 at indices [0, 1, 2, 4] where nums1[j] < nums1[3], resulting in 50 + 30 = 80.
// 	For i = 4: Select the 2 largest values from nums2 at indices [1, 2] where nums1[j] < nums1[4], resulting in 30 + 20 = 50.
//
// Constraints:
// n == nums1.length == nums2.length
// 	1 <= n <= 105
// 	1 <= nums1[i], nums2[i] <= 106
// 	1 <= k <= n
//

class Solution {
public:
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        vector<long long> result(n, 0);
        vector<int> indices(n);
        for (int i = 0; i < n; ++i) {
            indices[i] = i;
        }

        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return nums1[a] < nums1[b];
        });

        priority_queue<int, vector<int>, greater<int>> minHeap;
        long long currentSum = 0;
        int idx = 0;

        for (int i = 0; i < n; ++i) {
            int currentIndex = indices[i];
            while (idx < n && nums1[indices[idx]] < nums1[currentIndex]) {
                minHeap.push(nums2[indices[idx]]);
                currentSum += nums2[indices[idx]];
                if (minHeap.size() > k) {
                    currentSum -= minHeap.top();
                    minHeap.pop();
                }
                idx++;
            }
            result[currentIndex] = currentSum;
        }

        return result;          
    }
};
