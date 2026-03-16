// Source: https://leetcode.com/problems/maximum-building-height/   |   Difficulty: Hard
//
// Problem Description:
// You want to build n new buildings in a city. The new buildings will be built in a line and are labeled from 1 to n.
//
// However, there are city restrictions on the heights of the new buildings:
//
//
// 	The height of each building must be a non-negative integer.
// 	The height of the first building must be 0.
// 	The height difference between any two adjacent buildings cannot exceed 1.
//
//
// Additionally, there are city restrictions on the maximum height of specific buildings. These restrictions are given as a 2D integer array restrictions where restrictions[i] = [idi, maxHeighti] indicates that building idi must have a height less than or equal to maxHeighti.
//
// It is guaranteed that each building will appear at most once in restrictions, and building 1 will not be in restrictions.
//
// Return the maximum possible height of the tallest building.
//
// Example:
// Input: n = 5, restrictions = [[2,1],[4,1]]
// Output: 2
// Explanation: The green area in the image indicates the maximum allowed height for each building.
// We can build the buildings with heights [0,1,2,1,2], and the tallest building has a height of 2.
//
// Constraints:
// 2 <= n <= 109
// 	0 <= restrictions.length <= min(n - 1, 105)
// 	2 <= idi <= n
// 	idi is unique.
// 	0 <= maxHeighti <= 109
//

class Solution {
    public int maxBuilding(int n, int[][] restrictions) {
        Arrays.sort(restrictions, (a, b) -> Integer.compare(a[0], b[0]));
        List<int[]> resList = new ArrayList<>();
        resList.add(new int[]{1, 0});
        for (int[] r : restrictions) {
            resList.add(r);
        }
        resList.add(new int[]{n, n - 1});
        restrictions = resList.toArray(new int[0][]);

        for (int i = 1; i < restrictions.length; i++) {
            restrictions[i][1] = Math.min(restrictions[i][1],
                    restrictions[i - 1][1] + (restrictions[i][0] - restrictions[i - 1][0]));
        }

        for (int i = restrictions.length - 2; i >= 0; i--) {
            restrictions[i][1] = Math.min(restrictions[i][1],
                    restrictions[i + 1][1] + (restrictions[i + 1][0] - restrictions[i][0]));
        }

        int maxHeight = 0;
        for (int i = 1; i < restrictions.length; i++) {
            int leftPos = restrictions[i - 1][0];
            int leftHeight = restrictions[i - 1][1];
            int rightPos = restrictions[i][0];
            int rightHeight = restrictions[i][1];

            int distance = rightPos - leftPos;
            int heightDiff = Math.abs(rightHeight - leftHeight);
            if (distance >= heightDiff) {
                int peakHeight = Math.max(leftHeight, rightHeight) + (distance - heightDiff) / 2;
                maxHeight = Math.max(maxHeight, peakHeight);
            } else {
                maxHeight = Math.max(maxHeight, Math.min(leftHeight, rightHeight) + distance);
            }
        }

        return maxHeight;           
    }
}
