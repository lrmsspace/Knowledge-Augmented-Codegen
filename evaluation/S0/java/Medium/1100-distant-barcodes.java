// Source: https://leetcode.com/problems/distant-barcodes/   |   Difficulty: Medium
//
// Problem Description:
// In a warehouse, there is a row of barcodes, where the ith barcode is barcodes[i].
//
// Rearrange the barcodes so that no two adjacent barcodes are equal. You may return any answer, and it is guaranteed an answer exists.
//
// Example:
// Input: barcodes = [1,1,1,2,2,2]
// Output: [2,1,2,1,2,1]
//
// Constraints:
// 1 <= barcodes.length <= 10000
// 	1 <= barcodes[i] <= 10000
//

class Solution {
    public int[] rearrangeBarcodes(int[] barcodes) {
        Map<Integer, Integer> countMap = new HashMap<>();
        for (int code : barcodes) {
            countMap.put(code, countMap.getOrDefault(code, 0) + 1);
        }

        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> b[1] - a[1]);
        for (Map.Entry<Integer, Integer> entry : countMap.entrySet()) {
            maxHeap.offer(new int[]{entry.getKey(), entry.getValue()});
        }

        int n = barcodes.length;
        int[] result = new int[n];
        int index = 0;

        while (maxHeap.size() > 1) {
            int[] first = maxHeap.poll();
            int[] second = maxHeap.poll();

            result[index++] = first[0];
            result[index++] = second[0];

            if (--first[1] > 0) {
                maxHeap.offer(first);
            }
            if (--second[1] > 0) {
                maxHeap.offer(second);
            }
        }

        if (!maxHeap.isEmpty()) {
            int[] last = maxHeap.poll();
            while (last[1]-- > 0) {
                result[index++] = last[0];
            }
        }

        return result;          
    }
}
