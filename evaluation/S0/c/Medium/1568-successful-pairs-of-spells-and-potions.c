// Source: https://leetcode.com/problems/successful-pairs-of-spells-and-potions/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integer arrays spells and potions, of length n and m respectively, where spells[i] represents the strength of the ith spell and potions[j] represents the strength of the jth potion.
//
// You are also given an integer success. A spell and potion pair is considered successful if the product of their strengths is at least success.
//
// Return an integer array pairs of length n where pairs[i] is the number of potions that will form a successful pair with the ith spell.
//
// Example:
// Input: spells = [5,1,3], potions = [1,2,3,4,5], success = 7
// Output: [4,0,3]
// Explanation:
// - 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
// - 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
// - 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
// Thus, [4,0,3] is returned.
//
// Constraints:
// n == spells.length
// 	m == potions.length
// 	1 <= n, m <= 105
// 	1 <= spells[i], potions[i] <= 105
// 	1 <= success <= 1010
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* successfulPairs(int* spells, int spellsSize, int* potions, int potionsSize, long long success, int* returnSize) {
    // Sort potions array for binary search
    qsort(potions, potionsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int* result = (int*)malloc(spellsSize * sizeof(int));
    *returnSize = spellsSize;

    for (int i = 0; i < spellsSize; i++) {
        long long requiredPotionStrength = (success + spells[i] - 1) / spells[i]; // Ceiling division

        // Binary search to find the first potion that meets or exceeds the required strength
        int left = 0, right = potionsSize;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (potions[mid] < requiredPotionStrength) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        result[i] = potionsSize - left; // Count of successful pairs
    }

    return result;      
}
