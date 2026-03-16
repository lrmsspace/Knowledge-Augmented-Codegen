// Source: https://leetcode.com/problems/minimum-absolute-difference/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of distinct integers arr, find all pairs of elements with the minimum absolute difference of any two elements.
//
// Return a list of pairs in ascending order(with respect to pairs), each pair [a, b] follows
//
//
// 	a, b are from arr
// 	a < b
// 	b - a equals to the minimum absolute difference of any two elements in arr
//
// Example:
// Input: arr = [4,2,1,3]
// Output: [[1,2],[2,3],[3,4]]
// Explanation: The minimum absolute difference is 1. List all pairs with difference equal to 1 in ascending order.
//
// Constraints:
// 2 <= arr.length <= 105
// 	-106 <= arr[i] <= 106
//

class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int minDiff = INT_MAX;
        vector<vector<int>> result;

        for (size_t i = 1; i < arr.size(); ++i) {
            int diff = arr[i] - arr[i - 1];
            if (diff < minDiff) {
                minDiff = diff;
                result.clear();
                result.push_back({arr[i - 1], arr[i]});
            } else if (diff == minDiff) {
                result.push_back({arr[i - 1], arr[i]});
            }
        }

        return result;          
    }
};
