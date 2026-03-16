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

class Solution {
    public int largestValsFromLabels(int[] values, int[] labels, int numWanted, int useLimit) {
        int n = values.length;
        Integer[] indices = new Integer[n];
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }

        Arrays.sort(indices, (a, b) -> Integer.compare(values[b], values[a]));

        Map<Integer, Integer> labelCount = new HashMap<>();
        int totalValue = 0;
        int itemsChosen = 0;

        for (int index : indices) {
            if (itemsChosen >= numWanted) {
                break;
            }

            int label = labels[index];
            int count = labelCount.getOrDefault(label, 0);

            if (count < useLimit) {
                totalValue += values[index];
                labelCount.put(label, count + 1);
                itemsChosen++;
            }
        }

        return totalValue;          
    }
}
