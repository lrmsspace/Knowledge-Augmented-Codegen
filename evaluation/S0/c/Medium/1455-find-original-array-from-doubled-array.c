// Source: https://leetcode.com/problems/find-original-array-from-doubled-array/   |   Difficulty: Medium
//
// Problem Description:
// An integer array original is transformed into a doubled array changed by appending twice the value of every element in original, and then randomly shuffling the resulting array.
//
// Given an array changed, return original if changed is a doubled array. If changed is not a doubled array, return an empty array. The elements in original may be returned in any order.
//
// Example:
// Input: changed = [1,3,4,2,6,8]
// Output: [1,3,4]
// Explanation: One possible original array could be [1,3,4]:
// - Twice the value of 1 is 1 * 2 = 2.
// - Twice the value of 3 is 3 * 2 = 6.
// - Twice the value of 4 is 4 * 2 = 8.
// Other original arrays could be [4,3,1] or [3,1,4].
//
// Constraints:
// 1 <= changed.length <= 105
// 	0 <= changed[i] <= 105
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findOriginalArray(int* changed, int changedSize, int* returnSize) {
    if (changedSize % 2 != 0) {
        *returnSize = 0;
        return NULL;
    }

    int maxVal = 0;
    for (int i = 0; i < changedSize; i++) {
        if (changed[i] > maxVal) {
            maxVal = changed[i];
        }
    }

    int freqSize = maxVal + 1;
    int* freq = (int*)calloc(freqSize, sizeof(int));
    for (int i = 0; i < changedSize; i++) {
        freq[changed[i]]++;
    }

    int* original = (int*)malloc((changedSize / 2) * sizeof(int));
    int index = 0;

    for (int i = 0; i < freqSize; i++) {
        if (freq[i] > 0) {
            if (i == 0) {
                if (freq[i] % 2 != 0) {
                    free(freq);
                    free(original);
                    *returnSize = 0;
                    return NULL;
                }
                for (int j = 0; j < freq[i] / 2; j++) {
                    original[index++] = 0;
                }
            } else {
                while (freq[i] > 0) {
                    if (i * 2 >= freqSize || freq[i * 2] <= 0) {
                        free(freq);
                        free(original);
                        *returnSize = 0;
                        return NULL;
                    }
                    original[index++] = i;
                    freq[i]--;
                    freq[i * 2]--;
                }
            }
        }
    }

    free(freq);
    *returnSize = index;
    return original;        
}
