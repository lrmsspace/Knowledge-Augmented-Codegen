// Source: https://leetcode.com/problems/richest-customer-wealth/   |   Difficulty: Easy
//
// Problem Description:
// You are given an m x n integer grid accounts where accounts[i][j] is the amount of money the i​​​​​​​​​​​th​​​​ customer has in the j​​​​​​​​​​​th​​​​ bank. Return the wealth that the richest customer has.
//
// A customer's wealth is the amount of money they have in all their bank accounts. The richest customer is the customer that has the maximum wealth.
//
// Example:
// Input: accounts = [[1,2,3],[3,2,1]]
// Output: 6
// Explanation:
// 1st customer has wealth = 1 + 2 + 3 = 6
// 2nd customer has wealth = 3 + 2 + 1 = 6
// Both customers are considered the richest with a wealth of 6 each, so return 6.
//
// Constraints:
// m == accounts.length
// 	n == accounts[i].length
// 	1 <= m, n <= 50
// 	1 <= accounts[i][j] <= 100
//

class Solution {
public:
    int maximumWealth(vector<vector<int>>& accounts) {
        int maxWealth = 0;
        for (const auto& customer : accounts) {
            int currentWealth = 0;
            for (const auto& bank : customer) {
                currentWealth += bank;
            }
            maxWealth = std::max(maxWealth, currentWealth);
        }
        return maxWealth;           
    }
};
