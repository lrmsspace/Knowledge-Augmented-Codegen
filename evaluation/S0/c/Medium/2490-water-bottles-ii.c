// Source: https://leetcode.com/problems/water-bottles-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers numBottles and numExchange.
//
// numBottles represents the number of full water bottles that you initially have. In one operation, you can perform one of the following operations:
//
//
// 	Drink any number of full water bottles turning them into empty bottles.
// 	Exchange numExchange empty bottles with one full water bottle. Then, increase numExchange by one.
//
//
// Note that you cannot exchange multiple batches of empty bottles for the same value of numExchange. For example, if numBottles == 3 and numExchange == 1, you cannot exchange 3 empty water bottles for 3 full bottles.
//
// Return the maximum number of water bottles you can drink.
//
// Example:
// Input: numBottles = 13, numExchange = 6
// Output: 15
// Explanation: The table above shows the number of full water bottles, empty water bottles, the value of numExchange, and the number of bottles drunk.
//
// Constraints:
// 1 <= numBottles <= 100 
// 	1 <= numExchange <= 100
//

int maxBottlesDrunk(int numBottles, int numExchange) {
    int full = numBottles;
    int empty = 0;
    int exchange = numExchange;
    int totalDrunk = 0;

    while (full > 0) {
        // Drink all full bottles
        totalDrunk += full;
        empty += full;
        full = 0;

        // Exchange empty bottles for full ones if possible
        while (empty >= exchange) {
            empty -= exchange;
            full += 1;
            exchange += 1; // Increase the exchange requirement
        }
    }

    return totalDrunk;      
}
