// Source: https://leetcode.com/problems/make-k-subarray-sums-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array arr and an integer k. The array arr is circular. In other words, the first element of the array is the next element of the last element, and the last element of the array is the previous element of the first element.
//
// You can do the following operation any number of times:
//
//
// 	Pick any element from arr and increase or decrease it by 1.
//
//
// Return the minimum number of operations such that the sum of each subarray of length k is equal.
//
// A subarray is a contiguous part of the array.
//
// Example:
// Input: arr = [1,4,1,3], k = 2
// Output: 1
// Explanation: we can do one operation on index 1 to make its value equal to 3.
// The array after the operation is [1,3,1,3]
// - Subarray starts at index 0 is [1, 3], and its sum is 4 
// - Subarray starts at index 1 is [3, 1], and its sum is 4 
// - Subarray starts at index 2 is [1, 3], and its sum is 4 
// - Subarray starts at index 3 is [3, 1], and its sum is 4
//
// Constraints:
// 1 <= k <= arr.length <= 105
// 	1 <= arr[i] <= 109
//

class Solution {
public:
    long long makeSubKSumEqual(vector<int>& arr, int k) {
        int n = arr.size();
        vector<bool> visited(n, false);
        long long totalOperations = 0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                vector<int> group;
                int index = i;

                // Collect all elements in the current group
                do {
                    group.push_back(arr[index]);
                    visited[index] = true;
                    index = (index + k) % n;
                } while (index != i);

                // Find the median of the group
                sort(group.begin(), group.end());
                int median = group[group.size() / 2];

                // Calculate the total operations needed to make all elements equal to the median
                for (int num : group) {
                    totalOperations += abs(num - median);
                }
            }
        }

        return totalOperations;         
    }
};
