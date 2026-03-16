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
    public List<Integer> numberOfAlternatingGroups(int[] colors, int[][] queries) {
        int n = colors.length;
        int[] groupSizes = new int[n + 1];
        List<Integer> result = new ArrayList<>();

        // Function to initialize group sizes
        Runnable initializeGroups = () -> {
            Arrays.fill(groupSizes, 0);
            int count = 1;
            for (int i = 1; i < n; i++) {
                if (colors[i] != colors[i - 1]) {
                    count++;
                } else {
                    groupSizes[count]++;
                    count = 1;
                }
            }
            if (colors[0] != colors[n - 1]) {
                groupSizes[count]++;
            } else {
                groupSizes[count]++;
            }
        };

        initializeGroups.run();

        for (int[] query : queries) {
            if (query[0] == 1) {
                result.add(groupSizes[query[1]]);
            } else {
                int index = query[1];
                int newColor = query[2];
                if (colors[index] != newColor) {
                    int left = (index - 1 + n) % n;
                    int right = (index + 1) % n;

                    boolean leftDiff = colors[left] != colors[index];
                    boolean rightDiff = colors[right] != colors[index];
                    boolean newLeftDiff = colors[left] != newColor;
                    boolean newRightDiff = colors[right] != newColor;

                    int oldGroupSize = 1;
                    if (leftDiff) oldGroupSize++;
                    if (rightDiff) oldGroupSize++;

                    groupSizes[oldGroupSize]--;

                    int newGroupSize = 1;
                    if (newLeftDiff) newGroupSize++;
                    if (newRightDiff) newGroupSize++;

                    groupSizes[newGroupSize]++;

                    colors[index] = newColor;
                }
            }
        }

        return result;
    }
}
