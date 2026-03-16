// Source: https://leetcode.com/problems/intervals-between-identical-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of n integers arr.
//
// The interval between two elements in arr is defined as the absolute difference between their indices. More formally, the interval between arr[i] and arr[j] is |i - j|.
//
// Return an array intervals of length n where intervals[i] is the sum of intervals between arr[i] and each element in arr with the same value as arr[i].
//
// Note: |x| is the absolute value of x.
//
// Example:
// Input: arr = [2,1,3,1,2,3,3]
// Output: [4,2,7,2,4,4,5]
// Explanation:
// - Index 0: Another 2 is found at index 4. |0 - 4| = 4
// - Index 1: Another 1 is found at index 3. |1 - 3| = 2
// - Index 2: Two more 3s are found at indices 5 and 6. |2 - 5| + |2 - 6| = 7
// - Index 3: Another 1 is found at index 1. |3 - 1| = 2
// - Index 4: Another 2 is found at index 0. |4 - 0| = 4
// - Index 5: Two more 3s are found at indices 2 and 6. |5 - 2| + |5 - 6| = 4
// - Index 6: Two more 3s are found at indices 2 and 5. |6 - 2| + |6 - 5| = 5
//
// Constraints:
// n == arr.length
// 	1 <= n <= 105
// 	1 <= arr[i] <= 105
//
//
//  
// Note: This question is the same as  2615: Sum of Distances.
//

class Solution {
    public long[] getDistances(int[] arr) {
        int n = arr.length;
        long[] result = new long[n];
        Map<Integer, List<Integer>> indexMap = new HashMap<>();

        // Collect indices for each unique value in the array
        for (int i = 0; i < n; i++) {
            indexMap.computeIfAbsent(arr[i], k -> new ArrayList<>()).add(i);
        }

        // Calculate distances for each group of identical elements
        for (List<Integer> indices : indexMap.values()) {
            int size = indices.size();
            if (size <= 1) continue;

            long[] prefixSums = new long[size];
            prefixSums[0] = indices.get(0);
            for (int i = 1; i < size; i++) {
                prefixSums[i] = prefixSums[i - 1] + indices.get(i);
            }

            for (int i = 0; i < size; i++) {
                int index = indices.get(i);
                long leftSum = (long) index * i - (i > 0 ? prefixSums[i - 1] : 0);
                long rightSum = (prefixSums[size - 1] - prefixSums[i]) - (long) index * (size - i - 1);
                result[index] = leftSum + rightSum;
            }
        }

        return result;          
    }
}
