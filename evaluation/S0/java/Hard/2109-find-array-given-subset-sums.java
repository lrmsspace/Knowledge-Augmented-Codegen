// Source: https://leetcode.com/problems/find-array-given-subset-sums/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n representing the length of an unknown array that you are trying to recover. You are also given an array sums containing the values of all 2n subset sums of the unknown array (in no particular order).
//
// Return the array ans of length n representing the unknown array. If multiple answers exist, return any of them.
//
// An array sub is a subset of an array arr if sub can be obtained from arr by deleting some (possibly zero or all) elements of arr. The sum of the elements in sub is one possible subset sum of arr. The sum of an empty array is considered to be 0.
//
// Note: Test cases are generated such that there will always be at least one correct answer.
//
// Example:
// Input: n = 3, sums = [-3,-2,-1,0,0,1,2,3]
// Output: [1,2,-3]
// Explanation: [1,2,-3] is able to achieve the given subset sums:
// - []: sum is 0
// - [1]: sum is 1
// - [2]: sum is 2
// - [1,2]: sum is 3
// - [-3]: sum is -3
// - [1,-3]: sum is -2
// - [2,-3]: sum is -1
// - [1,2,-3]: sum is 0
// Note that any permutation of [1,2,-3] and also any permutation of [-1,-2,3] will also be accepted.
//
// Constraints:
// 1 <= n <= 15
// 	sums.length == 2n
// 	-104 <= sums[i] <= 104
//

class Solution {
    public int[] recoverArray(int n, int[] sums) {
        Arrays.sort(sums);
        List<Integer> res = new ArrayList<>();
        List<Integer> currSums = new ArrayList<>();
        for (int sum : sums) {
            currSums.add(sum);
        }

        while (res.size() < n) {
            int diff = currSums.get(1) - currSums.get(0);
            Map<Integer, Integer> countMap = new HashMap<>();
            for (int sum : currSums) {
                countMap.put(sum, countMap.getOrDefault(sum, 0) + 1);
            }

            List<Integer> withDiff = new ArrayList<>();
            List<Integer> withoutDiff = new ArrayList<>();
            boolean foundZeroInWithDiff = false;

            for (int sum : currSums) {
                if (countMap.get(sum) == 0) continue;

                countMap.put(sum, countMap.get(sum) - 1);
                int sumWithDiff = sum + diff;
                if (countMap.getOrDefault(sumWithDiff, 0) > 0) {
                    countMap.put(sumWithDiff, countMap.get(sumWithDiff) - 1);
                    withDiff.add(sumWithDiff);
                    withoutDiff.add(sum);
                    if (sumWithDiff == 0) {
                        foundZeroInWithDiff = true;
                    }
                }
            }

            if (foundZeroInWithDiff) {
                res.add(diff);
                currSums = withDiff;
            } else {
                res.add(-diff);
                currSums = withoutDiff;
            }
        }

        int[] resultArray = new int[res.size()];
        for (int i = 0; i < res.size(); i++) {
            resultArray[i] = res.get(i);
        }
        return resultArray;         
    }
}
