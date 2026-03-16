// Source: https://leetcode.com/problems/minimum-money-required-before-transactions/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array transactions, where transactions[i] = [costi, cashbacki].
//
// The array describes transactions, where each transaction must be completed exactly once in some order. At any given moment, you have a certain amount of money. In order to complete transaction i, money >= costi must hold true. After performing a transaction, money becomes money - costi + cashbacki.
//
// Return the minimum amount of money required before any transaction so that all of the transactions can be completed regardless of the order of the transactions.
//
// Example:
// Input: transactions = [[2,1],[5,0],[4,2]]
// Output: 10
// Explanation:
// Starting with money = 10, the transactions can be performed in any order.
// It can be shown that starting with money < 10 will fail to complete all transactions in some order.
//
// Constraints:
// 1 <= transactions.length <= 105
// 	transactions[i].length == 2
// 	0 <= costi, cashbacki <= 109
//

long long minimumMoney(int** transactions, int transactionsSize, int* transactionsColSize) {
    long long totalCost = 0;
    long long maxDiff = 0;
    for (int i = 0; i < transactionsSize; ++i) {
        int cost = transactions[i][0];
        int cashback = transactions[i][1];
        totalCost += cost;
        if (cost > cashback) {
            long long diff = (long long)(cost - cashback);
            if (diff > maxDiff) {
                maxDiff = diff;
            }
        }
    }
    return totalCost - maxDiff;     
}
