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
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        unordered_map<int, int> count;
        for (int fruit : basket1) {
            count[fruit]++;
        }
        for (int fruit : basket2) {
            count[fruit]--;
        }
        
        vector<int> toSwap;
        for (auto& [fruit, cnt] : count) {
            if (cnt % 2 != 0) {
                return -1;  // Impossible to make equal
            }
            for (int i = 0; i < abs(cnt) / 2; i++) {
                toSwap.push_back(fruit);
            }
        }
        
        sort(toSwap.begin(), toSwap.end());
        long long totalCost = 0;
        int minFruit = min(*min_element(basket1.begin(), basket1.end()), *min_element(basket2.begin(), basket2.end()));
        
        for (int i = 0; i < toSwap.size() / 2; i++) {
            totalCost += min(toSwap[i], 2 * minFruit);
        }
        
        return totalCost;           
    }
};
