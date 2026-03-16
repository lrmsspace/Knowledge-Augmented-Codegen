// Source: https://leetcode.com/problems/rearranging-fruits/   |   Difficulty: Hard
//
// Problem Description:
// You have two fruit baskets containing n fruits each. You are given two 0-indexed integer arrays basket1 and basket2 representing the cost of fruit in each basket. You want to make both baskets equal. To do so, you can use the following operation as many times as you want:
//
//
// 	Choose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
// 	The cost of the swap is min(basket1[i], basket2[j]).
//
//
// Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.
//
// Return the minimum cost to make both the baskets equal or -1 if impossible.
//
// Example:
// Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
// Output: 1
// Explanation: Swap index 1 of basket1 with index 0 of basket2, which has cost 1. Now basket1 = [4,1,2,2] and basket2 = [2,4,1,2]. Rearranging both the arrays makes them equal.
//
// Constraints:
// basket1.length == basket2.length
// 	1 <= basket1.length <= 105
// 	1 <= basket1[i], basket2[i] <= 109
//

class Solution {
    public long minCost(int[] basket1, int[] basket2) {
        Map<Integer, Integer> countMap = new HashMap<>();
        int n = basket1.length;
        int minFruitCost = Integer.MAX_VALUE;

        for (int i = 0; i < n; i++) {
            countMap.put(basket1[i], countMap.getOrDefault(basket1[i], 0) + 1);
            countMap.put(basket2[i], countMap.getOrDefault(basket2[i], 0) - 1);
            minFruitCost = Math.min(minFruitCost, Math.min(basket1[i], basket2[i]));
        }

        List<Integer> surplusFruits = new ArrayList<>();
        for (Map.Entry<Integer, Integer> entry : countMap.entrySet()) {
            int fruitCost = entry.getKey();
            int countDiff = entry.getValue();

            if (countDiff % 2 != 0) {
                return -1; // Impossible to make baskets equal
            }

            for (int i = 0; i < Math.abs(countDiff) / 2; i++) {
                if (countDiff > 0) {
                    surplusFruits.add(fruitCost); // Surplus in basket1
                }
            }
        }

        Collections.sort(surplusFruits);
        long totalCost = 0;
        int halfSize = surplusFruits.size() / 2;

        for (int i = 0; i < halfSize; i++) {
            int fruitCost = surplusFruits.get(i);
            totalCost += Math.min(fruitCost, 2 * minFruitCost);
        }

        return totalCost;           
    }
}
