// Source: https://leetcode.com/problems/largest-number/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.
//
// Since the result may be very large, so you need to return a string instead of an integer.
//
// Example:
// Input: nums = [10,2]
// Output: "210"
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 109
//

char* largestNumber(int* nums, int numsSize) {
    char** strNums = (char**)malloc(numsSize * sizeof(char*));
    for (int i = 0; i < numsSize; i++) {
        strNums[i] = (char*)malloc(12 * sizeof(char));
        sprintf(strNums[i], "%d", nums[i]);
    }

    int compare(const void* a, const void* b) {
        char* ab = (char*)malloc(22 * sizeof(char));
        char* ba = (char*)malloc(22 * sizeof(char));
        sprintf(ab, "%s%s", *(char**)a, *(char**)b);
        sprintf(ba, "%s%s", *(char**)b, *(char**)a);
        int result = strcmp(ba, ab);
        free(ab);
        free(ba);
        return result;
    }

    qsort(strNums, numsSize, sizeof(char*), compare);

    if (strcmp(strNums[0], "0") == 0) {
        for (int i = 0; i < numsSize; i++) {
            free(strNums[i]);
        }
        free(strNums);
        return "0";
    }

    int totalLength = 0;
    for (int i = 0; i < numsSize; i++) {
        totalLength += strlen(strNums[i]);
    }

    char* result = (char*)malloc((totalLength + 1) * sizeof(char));
    result[0] = '\0';
    for (int i = 0; i < numsSize; i++) {
        strcat(result, strNums[i]);
        free(strNums[i]);
    }
    free(strNums);

    return result;      
}
