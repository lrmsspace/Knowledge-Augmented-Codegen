// Source: https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n integers and two integers k and x.
//
// The x-sum of an array is calculated by the following procedure:
//
//
// 	Count the occurrences of all elements in the array.
// 	Keep only the occurrences of the top x most frequent elements. If two elements have the same number of occurrences, the element with the bigger value is considered more frequent.
// 	Calculate the sum of the resulting array.
//
//
// Note that if an array has less than x distinct elements, its x-sum is the sum of the array.
//
// Return an integer array answer of length n - k + 1 where answer[i] is the x-sum of the subarray nums[i..i + k - 1].
//
// Example:
// Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
//
// Output: [6,10,12]
//
// Explanation:
//
//
// 	For subarray [1, 1, 2, 2, 3, 4], only elements 1 and 2 will be kept in the resulting array. Hence, answer[0] = 1 + 1 + 2 + 2.
// 	For subarray [1, 2, 2, 3, 4, 2], only elements 2 and 4 will be kept in the resulting array. Hence, answer[1] = 2 + 2 + 2 + 4. Note that 4 is kept in the array since it is bigger than 3 and 1 which occur the same number of times.
// 	For subarray [2, 2, 3, 4, 2, 3], only elements 2 and 3 are kept in the resulting array. Hence, answer[2] = 2 + 2 + 2 + 3 + 3.
//
// Constraints:
// nums.length == n
// 	1 <= n <= 105
// 	1 <= nums[i] <= 109
// 	1 <= x <= k <= nums.length
//

class Solution {
    public long[] findXSum(int[] nums, int k, int x) {
        int n = nums.length;
        long[] result = new long[n - k + 1];

        Map<Integer, Integer> freqMap = new HashMap<>();
        TreeMap<Integer, TreeSet<Integer>> countMap = new TreeMap<>(Collections.reverseOrder());
        long currentXSum = 0;

        for (int i = 0; i < n; i++) {
            if (i >= k) {
                int outNum = nums[i - k];
                int outCount = freqMap.get(outNum);
                freqMap.put(outNum, outCount - 1);

                countMap.get(outCount).remove(outNum);
                if (countMap.get(outCount).isEmpty()) {
                    countMap.remove(outCount);
                }

                if (outCount == x) {
                    currentXSum -= outNum;
                    if (countMap.containsKey(x - 1)) {
                        int toAdd = countMap.get(x - 1).last();
                        currentXSum += toAdd;
                    }
                } else if (outCount > x) {
                    // do nothing
                } else {
                    currentXSum -= outNum;
                }

                if (outCount - 1 > 0) {
                    countMap.computeIfAbsent(outCount - 1, key -> new TreeSet<>()).add(outNum);
                }
            }

            int inNum = nums[i];
            int inCount = freqMap.getOrDefault(inNum, 0);
            freqMap.put(inNum, inCount + 1);

            countMap.computeIfAbsent(inCount + 1, key -> new TreeSet<>()).add(inNum);
            if (inCount > 0) {
                countMap.get(inCount).remove(inNum);
                if (countMap.get(inCount).isEmpty()) {
                    countMap.remove(inCount);
                }
            }

            if (inCount + 1 == x) {
                currentXSum += inNum;
                if (countMap.containsKey(x + 1)) {
                    int toRemove = countMap.get(x + 1).first();
                    currentXSum -= toRemove;
                }
            } else if (inCount + 1 > x) {
                // do nothing
            } else {
                currentXSum += inNum;
            }

            if (i >= k - 1) {
                result[i - k + 1] = currentXSum;      
            }
        }
        return result;      
    }
}
