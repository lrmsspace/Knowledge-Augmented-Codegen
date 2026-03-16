// Source: https://leetcode.com/problems/shopping-offers/   |   Difficulty: Medium
//
// Problem Description:
// In LeetCode Store, there are n items to sell. Each item has a price. However, there are some special offers, and a special offer consists of one or more different kinds of items with a sale price.
//
// You are given an integer array price where price[i] is the price of the ith item, and an integer array needs where needs[i] is the number of pieces of the ith item you want to buy.
//
// You are also given an array special where special[i] is of size n + 1 where special[i][j] is the number of pieces of the jth item in the ith offer and special[i][n] (i.e., the last integer in the array) is the price of the ith offer.
//
// Return the lowest price you have to pay for exactly certain items as given, where you could make optimal use of the special offers. You are not allowed to buy more items than you want, even if that would lower the overall price. You could use any of the special offers as many times as you want.
//
// Example:
// Input: price = [2,5], special = [[3,0,5],[1,2,10]], needs = [3,2]
// Output: 14
// Explanation: There are two kinds of items, A and B. Their prices are $2 and $5 respectively. 
// In special offer 1, you can pay $5 for 3A and 0B
// In special offer 2, you can pay $10 for 1A and 2B. 
// You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.
//
// Constraints:
// n == price.length == needs.length
// 	1 <= n <= 6
// 	0 <= price[i], needs[i] <= 10
// 	1 <= special.length <= 100
// 	special[i].length == n + 1
// 	0 <= special[i][j] <= 50
// 	The input is generated that at least one of special[i][j] is non-zero for 0 <= j <= n - 1.
//

int shoppingOffers(int* price, int priceSize, int** special, int specialSize, int* specialColSize, int* needs, int needsSize) {
    int minCost = 0;
    for (int i = 0; i < priceSize; i++) {
        minCost += price[i] * needs[i];
    }

    for (int i = 0; i < specialSize; i++) {
        int* offer = special[i];
        int canUseOffer = 1;
        for (int j = 0; j < needsSize; j++) {
            if (offer[j] > needs[j]) {
                canUseOffer = 0;
                break;
            }
        }
        if (canUseOffer) {
            int* updatedNeeds = (int*)malloc(needsSize * sizeof(int));
            for (int j = 0; j < needsSize; j++) {
                updatedNeeds[j] = needs[j] - offer[j];
            }
            int offerCost = shoppingOffers(price, priceSize, special, specialSize, specialColSize, updatedNeeds, needsSize) + offer[needsSize];
            if (offerCost < minCost) {
                minCost = offerCost;
            }
            free(updatedNeeds);
        }
    }

    return minCost;     
}
