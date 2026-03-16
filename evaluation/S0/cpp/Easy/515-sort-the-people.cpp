// Source: https://leetcode.com/problems/sort-the-people/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of strings names, and an array heights that consists of distinct positive integers. Both arrays are of length n.
//
// For each index i, names[i] and heights[i] denote the name and height of the ith person.
//
// Return names sorted in descending order by the people's heights.
//
// Example:
// Input: names = ["Mary","John","Emma"], heights = [180,165,170]
// Output: ["Mary","Emma","John"]
// Explanation: Mary is the tallest, followed by Emma and John.
//
// Constraints:
// n == names.length == heights.length
// 	1 <= n <= 103
// 	1 <= names[i].length <= 20
// 	1 <= heights[i] <= 105
// 	names[i] consists of lower and upper case English letters.
// 	All the values of heights are distinct.
//

class Solution {
public:
    vector<string> sortPeople(vector<string>& names, vector<int>& heights) {
        int n = names.size();
        vector<pair<int, string>> height_name_pairs(n);
        
        for (int i = 0; i < n; ++i) {
            height_name_pairs[i] = {heights[i], names[i]};
        }
        
        sort(height_name_pairs.rbegin(), height_name_pairs.rend());
        
        vector<string> sorted_names(n);
        for (int i = 0; i < n; ++i) {
            sorted_names[i] = height_name_pairs[i].second;
        }
        
        return sorted_names;            
    }
};
