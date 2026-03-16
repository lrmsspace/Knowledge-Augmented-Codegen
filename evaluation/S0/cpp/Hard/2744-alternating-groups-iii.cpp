// Source: https://leetcode.com/problems/alternating-groups-iii/   |   Difficulty: Hard
//
// Problem Description:
// There are some red and blue tiles arranged circularly. You are given an array of integers colors and a 2D integers array queries.
//
// The color of tile i is represented by colors[i]:
//
//
//  colors[i] == 0 means that tile i is red.
//  colors[i] == 1 means that tile i is blue.
//
//
// An alternating group is a contiguous subset of tiles in the circle with alternating colors (each tile in the group except the first and last one has a different color from its adjacent tiles in the group).
//
// You have to process queries of two types:
//
//
//  queries[i] = [1, sizei], determine the count of alternating groups with size sizei.
//  queries[i] = [2, indexi, colori], change colors[indexi] to colori.
//
//
// Return an array answer containing the results of the queries of the first type in order.
//
// Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.
//
// Example:
// Input: colors = [0,1,1,0,1], queries = [[2,1,0],[1,4]]
//
// Output: [2]
//
// Explanation:
//
//
//
// First query:
//
// Change colors[1] to 0.
//
//
//
// Second query:
//
// Count of the alternating groups with size 4:
//
// Constraints:
// 4 <= colors.length <= 5 * 104
//  0 <= colors[i] <= 1
//  1 <= queries.length <= 5 * 104
//  queries[i][0] == 1 or queries[i][0] == 2
//  For all i that:
//  
//   queries[i][0] == 1: queries[i].length == 2, 3 <= queries[i][1] <= colors.length - 1
//   queries[i][0] == 2: queries[i].length == 3, 0 <= queries[i][1] <= colors.length - 1, 0 <= queries[i][2] <= 1
//

class Solution {
public:
    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        int n = colors.size();
        vector<int> groupSizes;
        int count = 1;
        
        // Initial grouping
        for (int i = 1; i < n; i++) {
            if (colors[i] != colors[i - 1]) {
                count++;
            } else {
                groupSizes.push_back(count);
                count = 1;
            }
        }
        // Circular check
        if (colors[0] != colors[n - 1]) {
            count++;
        } else {
            groupSizes.push_back(count);
            count = 1;
        }
        groupSizes.push_back(count);
        
        // Frequency map of group sizes
        unordered_map<int, int> sizeCount;
        for (int size : groupSizes) {
            sizeCount[size]++;
        }
        
        vector<int> result;
        
        for (const auto& query : queries) {
            if (query[0] == 1) {
                // Count query
                int size = query[1];
                result.push_back(sizeCount[size]);
            } else {
                // Update query
                int index = query[1];
                int newColor = query[2];
                
                if (colors[index] == newColor) continue; // No change
                
                // Find the group containing index
                int left = index, right = index;
                int leftColor = colors[index];
                int rightColor = colors[index];
                
                // Expand left
                while (true) {
                    left = (left - 1 + n) % n;
                    if (colors[left] != leftColor) break;
                    leftColor = colors[left];
                }
                
                // Expand right
                while (true) {
                    right = (right + 1) % n;
                    if (colors[right] != rightColor) break;
                    rightColor = colors[right];
                }
                
                // Calculate old group size
                int oldGroupSize = (right >= left) ? (right - left - 1) : (n - (left - right + 1));
                
                // Update frequency map
                sizeCount[oldGroupSize]--;
                
                // Change color
                colors[index] = newColor;
                
                // Recalculate new group sizes
                int newLeft = left, newRight = right;
                
                // Expand new left
                while (true) {
                    newLeft = (newLeft - 1 + n) % n;
                    if (colors[newLeft] != colors[(newLeft + 1) % n]) break;
                }
                // Expand new right
                while (true) {
                    newRight = (newRight + 1) % n;
                    if (colors[newRight] != colors[(newRight - 1 + n) % n]) break;
                }
                int newGroupSize = (newRight >= newLeft) ? (newRight - newLeft - 1) : (n - (newLeft - newRight + 1));
                sizeCount[newGroupSize]++;
            }
        }
        return result;      
    }
};
