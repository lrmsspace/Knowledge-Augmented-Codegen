// Source: https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums consisting of 3 * n elements.
//
// You are allowed to remove any subsequence of elements of size exactly n from nums. The remaining 2 * n elements will be divided into two equal parts:
//
//
// 	The first n elements belonging to the first part and their sum is sumfirst.
// 	The next n elements belonging to the second part and their sum is sumsecond.
//
//
// The difference in sums of the two parts is denoted as sumfirst - sumsecond.
//
//
// 	For example, if sumfirst = 3 and sumsecond = 2, their difference is 1.
// 	Similarly, if sumfirst = 2 and sumsecond = 3, their difference is -1.
//
//
// Return the minimum difference possible between the sums of the two parts after the removal of n elements.
//
// Example:
// Input: nums = [3,1,2]
// Output: -1
// Explanation: Here, nums has 3 elements, so n = 1. 
// Thus we have to remove 1 element from nums and divide the array into two equal parts.
// - If we remove nums[0] = 3, the array will be [1,2]. The difference in sums of the two parts will be 1 - 2 = -1.
// - If we remove nums[1] = 1, the array will be [3,2]. The difference in sums of the two parts will be 3 - 2 = 1.
// - If we remove nums[2] = 2, the array will be [3,1]. The difference in sums of the two parts will be 3 - 1 = 2.
// The minimum difference between sums of the two parts is min(-1,1,2) = -1.
//
// Constraints:
// nums.length == 3 * n
// 	1 <= n <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        int n = nums.size() / 3;
        priority_queue<int, vector<int>, greater<int>> minHeap;
        priority_queue<int> maxHeap;
        vector<long long> leftSums(3 * n + 1, 0);
        vector<long long> rightSums(3 * n + 1, 0);
        
        long long leftSum = 0;
        for (int i = 0; i < 2 * n; i++) {
            leftSum += nums[i];
            minHeap.push(nums[i]);
            if (minHeap.size() > n) {
                leftSum -= minHeap.top();
                minHeap.pop();
            }
            if (minHeap.size() == n) {
                leftSums[i + 1] = leftSum;
            } else {
                leftSums[i + 1] = LLONG_MAX;
            }
        }
        
        long long rightSum = 0;
        for (int i = 3 * n - 1; i >= n; i--) {
            rightSum += nums[i];
            maxHeap.push(nums[i]);
            if (maxHeap.size() > n) {
                rightSum -= maxHeap.top();
                maxHeap.pop();
            }
            if (maxHeap.size() == n) {
                rightSums[i] = rightSum;
            } else {
                rightSums[i] = LLONG_MAX;
            }
        }
        
        long long result = LLONG_MAX;
        for (int i = n; i <= 2 * n; i++) {
            if (leftSums[i] != LLONG_MAX && rightSums[i] != LLONG_MAX) {
                result = min(result, leftSums[i] - rightSums[i]);
            }
        }
        
        return result;          
    }
};
