// Source: https://leetcode.com/problems/count-good-meals/   |   Difficulty: Medium
//
// Problem Description:
// A good meal is a meal that contains exactly two different food items with a sum of deliciousness equal to a power of two.
//
// You can pick any two different foods to make a good meal.
//
// Given an array of integers deliciousness where deliciousness[i] is the deliciousness of the i​​​​​​th​​​​​​​​ item of food, return the number of different good meals you can make from this list modulo 109 + 7.
//
// Note that items with different indices are considered different even if they have the same deliciousness value.
//
// Example:
// Input: deliciousness = [1,3,5,7,9]
// Output: 4
// Explanation: The good meals are (1,3), (1,7), (3,5) and, (7,9).
// Their respective sums are 4, 8, 8, and 16, all of which are powers of 2.
//
// Constraints:
// 1 <= deliciousness.length <= 105
// 	0 <= deliciousness[i] <= 220
//

class Solution {
    public int countPairs(int[] deliciousness) {
        Map<Integer, Integer> countMap = new HashMap<>();
        int MOD = 1_000_000_007;
        long result = 0;

        for (int val : deliciousness) {
            for (int power = 1; power <= 2_097_152; power <<= 1) {
                int complement = power - val;
                if (countMap.containsKey(complement)) {
                    result = (result + countMap.get(complement)) % MOD;
                }
            }
            countMap.put(val, countMap.getOrDefault(val, 0) + 1);
        }

        return (int) result;            
    }
}
