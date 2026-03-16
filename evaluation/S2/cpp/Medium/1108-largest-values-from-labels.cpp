// Source: https://leetcode.com/problems/largest-values-from-labels/   |   Difficulty: Medium
//
// Problem Description:
// You are given n item's value and label as two integer arrays values and labels. You are also given two integers numWanted and useLimit.
//
// Your task is to find a subset of items with the maximum sum of their values such that:
//
//
// 	The number of items is at most numWanted.
// 	The number of items with the same label is at most useLimit.
//
//
// Return the maximum sum.
//
// Example:
// Input: values = [5,4,3,2,1], labels = [1,1,2,2,3], numWanted = 3, useLimit = 1
//
// Output: 9
//
// Explanation:
//
// The subset chosen is the first, third, and fifth items with the sum of values 5 + 3 + 1.
//
// Constraints:
// n == values.length == labels.length
// 	1 <= n <= 2 * 104
// 	0 <= values[i], labels[i] <= 2 * 104
// 	1 <= numWanted, useLimit <= n
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int numWanted, int useLimit) {
        vector<pair<int, int>> items;
        for (size_t i = 0; i < values.size(); ++i) {
            items.emplace_back(values[i], labels[i]);
        }

        // Sort items by value in descending order
        sort(items.begin(), items.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first > b.first;
        });

        unordered_map<int, int> labelCount; // Count of items used for each label
        int totalValue = 0;
        int itemsUsed = 0;

        for (const auto& item : items) {
            if (itemsUsed >= numWanted) {
                break; // Reached the limit of numWanted
            }
            if (labelCount[item.second] < useLimit) {
                totalValue += item.first; // Add the value of the item
                labelCount[item.second]++; // Increment the count for this label
                itemsUsed++; // Increment the count of items used
            }
        }

        return totalValue;          
    }
};
