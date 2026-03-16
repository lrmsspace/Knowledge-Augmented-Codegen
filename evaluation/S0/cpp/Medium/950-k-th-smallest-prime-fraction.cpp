// Source: https://leetcode.com/problems/k-th-smallest-prime-fraction/   |   Difficulty: Medium
//
// Problem Description:
// You are given a sorted integer array arr containing 1 and prime numbers, where all the integers of arr are unique. You are also given an integer k.
//
// For every i and j where 0 <= i < j < arr.length, we consider the fraction arr[i] / arr[j].
//
// Return the kth smallest fraction considered. Return your answer as an array of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].
//
// Example:
// Input: arr = [1,2,3,5], k = 3
// Output: [2,5]
// Explanation: The fractions to be considered in sorted order are:
// 1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
// The third fraction is 2/5.
//
// Constraints:
// 2 <= arr.length <= 1000
// 	1 <= arr[i] <= 3 * 104
// 	arr[0] == 1
// 	arr[i] is a prime number for i > 0.
// 	All the numbers of arr are unique and sorted in strictly increasing order.
// 	1 <= k <= arr.length * (arr.length - 1) / 2
//
//
//  
// Follow up: Can you solve the problem with better than O(n2) complexity?
//

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        auto compare = [&](pair<int, int>& a, pair<int, int>& b) {
            return (long long)arr[a.first] * arr[b.second] > (long long)arr[b.first] * arr[a.second];
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> minHeap(compare);

        for (int j = 1; j < n; ++j) {
            minHeap.emplace(0, j);
        }

        pair<int, int> fraction;
        for (int i = 0; i < k; ++i) {
            fraction = minHeap.top();
            minHeap.pop();
            int numeratorIndex = fraction.first;
            int denominatorIndex = fraction.second;

            if (numeratorIndex + 1 < denominatorIndex) {
                minHeap.emplace(numeratorIndex + 1, denominatorIndex);
            }
        }

        return {arr[fraction.first], arr[fraction.second]};         
    }
};
