// Source: https://leetcode.com/problems/minimum-cost-to-make-arrays-identical/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays arr and brr of length n, and an integer k. You can perform the following operations on arr any number of times:
//
//
// 	Split arr into any number of contiguous subarrays and rearrange these subarrays in any order. This operation has a fixed cost of k.
// 	
// 	Choose any element in arr and add or subtract a positive integer x to it. The cost of this operation is x.
// 	
//
//
// Return the minimum total cost to make arr equal to brr.
//
// Example:
// Input: arr = [-7,9,5], brr = [7,-2,-5], k = 2
//
// Output: 13
//
// Explanation:
//
//
// 	Split arr into two contiguous subarrays: [-7] and [9, 5] and rearrange them as [9, 5, -7], with a cost of 2.
// 	Subtract 2 from element arr[0]. The array becomes [7, 5, -7]. The cost of this operation is 2.
// 	Subtract 7 from element arr[1]. The array becomes [7, -2, -7]. The cost of this operation is 7.
// 	Add 2 to element arr[2]. The array becomes [7, -2, -5]. The cost of this operation is 2.
//
//
// The total cost to make the arrays equal is 2 + 2 + 7 + 2 = 13.
//
// Constraints:
// 1 <= arr.length == brr.length <= 105
// 	0 <= k <= 2 * 1010
// 	-105 <= arr[i] <= 105
// 	-105 <= brr[i] <= 105
//

class Solution {
public:
    long long minCost(vector<int>& arr, vector<int>& brr, long long k) {
        long long totalDiff = 0;
        for (size_t i = 0; i < arr.size(); ++i) {
            totalDiff += abs(arr[i] - brr[i]);
        }

        if (k == 0) {
            return totalDiff;
        }

        unordered_map<int, int> countMap;
        for (const int& num : arr) {
            countMap[num]++;
        }
        for (const int& num : brr) {
            countMap[num]--;
        }

        long long splitCost = 0;
        for (const auto& [num, count] : countMap) {
            if (count != 0) {
                splitCost += k;
            }
        }

        return min(totalDiff, splitCost + totalDiff);           
    }
};
