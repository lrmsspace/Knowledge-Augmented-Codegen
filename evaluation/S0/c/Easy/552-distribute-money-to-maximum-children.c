// Source: https://leetcode.com/problems/distribute-money-to-maximum-children/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer money denoting the amount of money (in dollars) that you have and another integer children denoting the number of children that you must distribute the money to.
//
// You have to distribute the money according to the following rules:
//
//
// 	All money must be distributed.
// 	Everyone must receive at least 1 dollar.
// 	Nobody receives 4 dollars.
//
//
// Return the maximum number of children who may receive exactly 8 dollars if you distribute the money according to the aforementioned rules. If there is no way to distribute the money, return -1.
//
// Example:
// Input: money = 20, children = 3
// Output: 1
// Explanation: 
// The maximum number of children with 8 dollars will be 1. One of the ways to distribute the money is:
// - 8 dollars to the first child.
// - 9 dollars to the second child. 
// - 3 dollars to the third child.
// It can be proven that no distribution exists such that number of children getting 8 dollars is greater than 1.
//
// Constraints:
// 1 <= money <= 200
// 	2 <= children <= 30
//

int distMoney(int money, int children) {
    if (money < children) {
        return -1;
    }
    
    int max_eight_dollar_children = money / 8;
    if (max_eight_dollar_children > children) {
        max_eight_dollar_children = children;
    }
    
    for (int i = max_eight_dollar_children; i >= 0; i--) {
        int remaining_money = money - (i * 8);
        int remaining_children = children - i;
        
        if (remaining_children == 0 && remaining_money == 0) {
            return i;
        }
        
        if (remaining_children > 0) {
            if (remaining_money >= remaining_children && remaining_money <= remaining_children * 3) {
                return i;
            }
        }
    }
    
    return -1;      
}
