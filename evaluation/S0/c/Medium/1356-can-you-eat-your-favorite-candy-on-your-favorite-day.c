// Source: https://leetcode.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/   |   Difficulty: Medium
//
// Problem Description:
// You are given a (0-indexed) array of positive integers candiesCount where candiesCount[i] represents the number of candies of the ith type you have. You are also given a 2D array queries where queries[i] = [favoriteTypei, favoriteDayi, dailyCapi].
//
// You play a game with the following rules:
//
//
// 	You start eating candies on day 0.
// 	You cannot eat any candy of type i unless you have eaten all candies of type i - 1.
// 	You must eat at least one candy per day until you have eaten all the candies.
//
//
// Construct a boolean array answer such that answer.length == queries.length and answer[i] is true if you can eat a candy of type favoriteTypei on day favoriteDayi without eating more than dailyCapi candies on any day, and false otherwise. Note that you can eat different types of candy on the same day, provided that you follow rule 2.
//
// Return the constructed array answer.
//
// Example:
// Input: candiesCount = [7,4,5,3,8], queries = [[0,2,2],[4,2,4],[2,13,1000000000]]
// Output: [true,false,true]
// Explanation:
// 1- If you eat 2 candies (type 0) on day 0 and 2 candies (type 0) on day 1, you will eat a candy of type 0 on day 2.
// 2- You can eat at most 4 candies each day.
//    If you eat 4 candies every day, you will eat 4 candies (type 0) on day 0 and 4 candies (type 0 and type 1) on day 1.
//    On day 2, you can only eat 4 candies (type 1 and type 2), so you cannot eat a candy of type 4 on day 2.
// 3- If you eat 1 candy each day, you will eat a candy of type 2 on day 13.
//
// Constraints:
// 1 <= candiesCount.length <= 105
// 	1 <= candiesCount[i] <= 105
// 	1 <= queries.length <= 105
// 	queries[i].length == 3
// 	0 <= favoriteTypei < candiesCount.length
// 	0 <= favoriteDayi <= 109
// 	1 <= dailyCapi <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* canEat(int* candiesCount, int candiesCountSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Precompute prefix sums of candiesCount
    long long* prefixSums = (long long*)malloc((candiesCountSize + 1) * sizeof(long long));
    prefixSums[0] = 0;
    for (int i = 0; i < candiesCountSize; i++) {
        prefixSums[i + 1] = prefixSums[i] + candiesCount[i];
    }

    // Prepare the result array
    bool* result = (bool*)malloc(queriesSize * sizeof(bool));
    *returnSize = queriesSize;

    // Process each query
    for (int i = 0; i < queriesSize; i++) {
        int favoriteType = queries[i][0];
        long long favoriteDay = queries[i][1];
        long long dailyCap = queries[i][2];

        // Calculate the minimum and maximum candies that can be eaten by favoriteDay
        long long minCandiesByDay = favoriteDay + 1; // At least one candy per day
        long long maxCandiesByDay = (favoriteDay + 1) * dailyCap; // At most dailyCap candies per day

        // Calculate the range of candies for the favorite type
        long long candiesBeforeType = prefixSums[favoriteType];
        long long candiesUpToType = prefixSums[favoriteType + 1];

        // Check if there is an overlap between [minCandiesByDay, maxCandiesByDay] and [candiesBeforeType + 1, candiesUpToType]
        if (maxCandiesByDay > candiesBeforeType && minCandiesByDay <= candiesUpToType) {
            result[i] = true;
        } else {
            result[i] = false;
        }
    }

    free(prefixSums);
    return result;      
}
