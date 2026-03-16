// Source: https://leetcode.com/problems/find-the-k-sum-of-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k. You can choose any subsequence of the array and sum all of its elements together.
//
// We define the K-Sum of the array as the kth largest subsequence sum that can be obtained (not necessarily distinct).
//
// Return the K-Sum of the array.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Note that the empty subsequence is considered to have a sum of 0.
//
// Example:
// Input: nums = [2,4,-2], k = 5
// Output: 2
// Explanation: All the possible subsequence sums that we can obtain are the following sorted in decreasing order:
// 6, 4, 4, 2, 2, 0, 0, -2.
// The 5-Sum of the array is 2.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	-109 <= nums[i] <= 109
// 	1 <= k <= min(2000, 2n)
//

class Solution {
public:
    long long kSum(vector<int>& nums, int k) {
        priority_queue<long long> maxHeap;
        long long totalSum = 0;
        vector<long long> absNums;
        
        // Calculate total sum of positive numbers and store absolute values
        for (int num : nums) {
            if (num > 0) {
                totalSum += num;
            }
            absNums.push_back(abs((long long)num));
        }
        
        // Sort absolute values in descending order
        sort(absNums.rbegin(), absNums.rend());
        
        // Use a max-heap to find the k-th largest subsequence sum
        maxHeap.push(totalSum);
        
        for (long long absNum : absNums) {
            int currentHeapSize = maxHeap.size();
            for (int i = 0; i < currentHeapSize; ++i) {
                long long currentSum = maxHeap.top();
                maxHeap.pop();
                
                // Generate new subsequence sums by excluding the current absolute number
                long long newSum = currentSum - absNum;
                maxHeap.push(newSum);
                
                // If we have enough sums, we can stop early
                if (maxHeap.size() > k) {
                    maxHeap.pop();
                }
            }
        }
        
        // The k-th largest subsequence sum is at the top of the max-heap
        return maxHeap.top();           
    }
};
