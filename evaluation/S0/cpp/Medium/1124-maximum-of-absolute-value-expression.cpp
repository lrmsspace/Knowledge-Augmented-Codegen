// Source: https://leetcode.com/problems/maximum-of-absolute-value-expression/   |   Difficulty: Medium
//
// Problem Description:
// Given two arrays of integers with equal lengths, return the maximum value of:
//
// |arr1[i] - arr1[j]| + |arr2[i] - arr2[j]| + |i - j|
//
// where the maximum is taken over all 0 <= i, j < arr1.length.
//
// Example:
// Input: arr1 = [1,2,3,4], arr2 = [-1,4,5,6]
// Output: 13
//
// Constraints:
// 2 <= arr1.length == arr2.length <= 40000
// 	-10^6 <= arr1[i], arr2[i] <= 10^6
//

class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        int n = arr1.size();
        int result = 0;

        // There are 4 possible sign combinations for the absolute values
        vector<pair<int, int>> signs = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        for (const auto& sign : signs) {
            int maxVal = INT_MIN;
            int minVal = INT_MAX;

            for (int i = 0; i < n; ++i) {
                int current = sign.first * arr1[i] + sign.second * arr2[i] + i;
                maxVal = max(maxVal, current);
                minVal = min(minVal, current);
            }

            result = max(result, maxVal - minVal);
        }

        return result;          
    }
};
