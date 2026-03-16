// Source: https://leetcode.com/problems/maximum-tastiness-of-candy-basket/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of positive integers price where price[i] denotes the price of the ith candy and a positive integer k.
//
// The store sells baskets of k distinct candies. The tastiness of a candy basket is the smallest absolute difference of the prices of any two candies in the basket.
//
// Return the maximum tastiness of a candy basket.
//
// Example:
// Input: price = [13,5,1,8,21,2], k = 3
// Output: 8
// Explanation: Choose the candies with the prices [13,5,21].
// The tastiness of the candy basket is: min(|13 - 5|, |13 - 21|, |5 - 21|) = min(8, 8, 16) = 8.
// It can be proven that 8 is the maximum tastiness that can be achieved.
//
// Constraints:
// 2 <= k <= price.length <= 105
// 	1 <= price[i] <= 109
//

int maximumTastiness(int* price, int priceSize, int k) {
    // Helper function to check if a given tastiness can be achieved
    int canAchieve(int* price, int priceSize, int k, int tastiness) {
        int count = 1; // Start with the first candy
        int lastPrice = price[0];

        for (int i = 1; i < priceSize; i++) {
            if (price[i] - lastPrice >= tastiness) {
                count++;
                lastPrice = price[i];
                if (count == k) {
                    return 1; // Found k candies with at least 'tastiness' difference
                }
            }
        }
        return 0; // Not enough candies found
    }

    // Sort the prices array
    qsort(price, priceSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int left = 0;
    int right = price[priceSize - 1] - price[0];
    int result = 0;

    // Binary search for the maximum tastiness
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canAchieve(price, priceSize, k, mid)) {
            result = mid; // Update result and try for a larger tastiness
            left = mid + 1;
        } else {
            right = mid - 1; // Try for a smaller tastiness
        }
    }

    return result;      
}
