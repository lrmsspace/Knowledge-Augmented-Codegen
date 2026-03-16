// Source: https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/   |   Difficulty: Easy
//
// Problem Description:
// There are n kids with candies. You are given an integer array candies, where each candies[i] represents the number of candies the ith kid has, and an integer extraCandies, denoting the number of extra candies that you have.
//
// Return a boolean array result of length n, where result[i] is true if, after giving the ith kid all the extraCandies, they will have the greatest number of candies among all the kids, or false otherwise.
//
// Note that multiple kids can have the greatest number of candies.
//
// Example:
// Input: candies = [2,3,5,1,3], extraCandies = 3
// Output: [true,true,true,false,true] 
// Explanation: If you give all extraCandies to:
// - Kid 1, they will have 2 + 3 = 5 candies, which is the greatest among the kids.
// - Kid 2, they will have 3 + 3 = 6 candies, which is the greatest among the kids.
// - Kid 3, they will have 5 + 3 = 8 candies, which is the greatest among the kids.
// - Kid 4, they will have 1 + 3 = 4 candies, which is not the greatest among the kids.
// - Kid 5, they will have 3 + 3 = 6 candies, which is the greatest among the kids.
//
// Constraints:
// n == candies.length
// 	2 <= n <= 100
// 	1 <= candies[i] <= 100
// 	1 <= extraCandies <= 50
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* kidsWithCandies(int* candies, int candiesSize, int extraCandies, int* returnSize) {
    int max_candies = 0;
    for (int i = 0; i < candiesSize; i++) {
        if (candies[i] > max_candies) {
            max_candies = candies[i];
        }
    }

    bool* result = (bool*)malloc(candiesSize * sizeof(bool));
    for (int i = 0; i < candiesSize; i++) {
        result[i] = (candies[i] + extraCandies >= max_candies);
    }

    *returnSize = candiesSize;
    return result;      
}
