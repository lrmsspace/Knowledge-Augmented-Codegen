// Source: https://leetcode.com/problems/calculate-money-in-leetcode-bank/   |   Difficulty: Easy
//
// Problem Description:
// Hercy wants to save money for his first car. He puts money in the Leetcode bank every day.
//
// He starts by putting in $1 on Monday, the first day. Every day from Tuesday to Sunday, he will put in $1 more than the day before. On every subsequent Monday, he will put in $1 more than the previous Monday. 
//
// Given n, return the total amount of money he will have in the Leetcode bank at the end of the nth day.
//
// Example:
// Input: n = 4
// Output: 10
// Explanation: After the 4th day, the total is 1 + 2 + 3 + 4 = 10.
//
// Constraints:
// 1 <= n <= 1000
//

int totalMoney(int n) {
    int weeks = n / 7;
    int days = n % 7;
    int total = 0;
    
    // Calculate total for complete weeks
    for (int i = 0; i < weeks; i++) {
        total += 28 + (i * 7); // 28 is the sum of first week (1+2+3+4+5+6+7)
    }
    
    // Calculate total for remaining days
    for (int j = 0; j < days; j++) {
        total += (weeks * 7) + (j + 1);
    }
    
    return total;       
}
