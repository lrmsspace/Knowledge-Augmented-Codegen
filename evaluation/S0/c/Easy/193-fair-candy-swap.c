// Source: https://leetcode.com/problems/fair-candy-swap/   |   Difficulty: Easy
//
// Problem Description:
// Alice and Bob have a different total number of candies. You are given two integer arrays aliceSizes and bobSizes where aliceSizes[i] is the number of candies of the ith box of candy that Alice has and bobSizes[j] is the number of candies of the jth box of candy that Bob has.
//
// Since they are friends, they would like to exchange one candy box each so that after the exchange, they both have the same total amount of candy. The total amount of candy a person has is the sum of the number of candies in each box they have.
//
// Return an integer array answer where answer[0] is the number of candies in the box that Alice must exchange, and answer[1] is the number of candies in the box that Bob must exchange. If there are multiple answers, you may return any one of them. It is guaranteed that at least one answer exists.
//
// Example:
// Input: aliceSizes = [1,1], bobSizes = [2,2]
// Output: [1,2]
//
// Constraints:
// 1 <= aliceSizes.length, bobSizes.length <= 104
// 	1 <= aliceSizes[i], bobSizes[j] <= 105
// 	Alice and Bob have a different total number of candies.
// 	There will be at least one valid answer for the given input.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* fairCandySwap(int* aliceSizes, int aliceSizesSize, int* bobSizes, int bobSizesSize, int* returnSize) {
    int sumA = 0, sumB = 0;
    for (int i = 0; i < aliceSizesSize; i++) {
        sumA += aliceSizes[i];
    }
    for (int j = 0; j < bobSizesSize; j++) {
        sumB += bobSizes[j];
    }
    
    int delta = (sumB - sumA) / 2;
    
    // Use a hash set to store Bob's candy sizes for O(1) lookups
    int maxBobSize = 100000; // Given constraint
    char* bobSet = (char*)calloc(maxBobSize + 1, sizeof(char));
    for (int j = 0; j < bobSizesSize; j++) {
        bobSet[bobSizes[j]] = 1;
    }
    
    int* result = (int*)malloc(2 * sizeof(int));
    for (int i = 0; i < aliceSizesSize; i++) {
        int targetBobSize = aliceSizes[i] + delta;
        if (targetBobSize >= 1 && targetBobSize <= maxBobSize && bobSet[targetBobSize]) {
            result[0] = aliceSizes[i];
            result[1] = targetBobSize;
            *returnSize = 2;
            free(bobSet);
            return result;
        }
    }
    
    free(bobSet);
    *returnSize = 0; // Should never reach here as per problem guarantee
    return NULL;        
}
