// Source: https://leetcode.com/problems/alternating-groups-ii/   |   Difficulty: Medium
//
// Problem Description:
// There is a circle of red and blue tiles. You are given an array of integers colors and an integer k. The color of tile i is represented by colors[i]:
//
//
// 	colors[i] == 0 means that tile i is red.
// 	colors[i] == 1 means that tile i is blue.
//
//
// An alternating group is every k contiguous tiles in the circle with alternating colors (each tile in the group except the first and last one has a different color from its left and right tiles).
//
// Return the number of alternating groups.
//
// Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.
//
// Example:
// Input: colors = [0,1,0,1,0], k = 3
//
// Output: 3
//
// Explanation:
//
//
//
// Alternating groups:
//
// Constraints:
// 3 <= colors.length <= 105
// 	0 <= colors[i] <= 1
// 	3 <= k <= colors.length
//

class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int n = colors.size();
        int count = 0;

        for (int start = 0; start < n; ++start) {
            bool isAlternating = true;
            for (int i = 0; i < k; ++i) {
                if (colors[(start + i) % n] == colors[(start + i + 1) % n]) {
                    isAlternating = false;
                    break;
                }
            }
            if (isAlternating) {
                count++;
            }
        }

        return count;           
    }
};
