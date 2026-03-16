// Source: https://leetcode.com/problems/maximum-possible-number-by-binary-concatenation/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums of size 3.
//
// Return the maximum possible number whose binary representation can be formed by concatenating the binary representation of all elements in nums in some order.
//
// Note that the binary representation of any number does not contain leading zeros.
//
// Example:
// Input: nums = [1,2,3]
//
// Output: 30
//
// Explanation:
//
// Concatenate the numbers in the order [3, 1, 2] to get the result "11110", which is the binary representation of 30.
//
// Constraints:
// nums.length == 3
// 	1 <= nums[i] <= 127
//

int maxGoodNumber(int* nums, int numsSize) {
    // Custom comparator for sorting based on binary concatenation
    int compare(const void* a, const void* b) {
        int num1 = *(int*)a;
        int num2 = *(int*)b;

        // Create binary strings
        char bin1[15], bin2[15];
        itoa(num1, bin1, 2);
        itoa(num2, bin2, 2);

        // Concatenate in both possible orders
        char concat1[30], concat2[30];
        strcpy(concat1, bin1);
        strcat(concat1, bin2);
        strcpy(concat2, bin2);
        strcat(concat2, bin1);

        // Compare concatenated results
        return strcmp(concat2, concat1); // Descending order
    }

    // Sort the array using the custom comparator
    qsort(nums, numsSize, sizeof(int), compare);

    // Build the final binary string
    char result[45] = "";
    for (int i = 0; i < numsSize; i++) {
        char bin[15];
        itoa(nums[i], bin, 2);
        strcat(result, bin);
    }

    // Convert the final binary string to an integer
    int maxNumber = 0;
    for (int i = 0; result[i] != '\0'; i++) {
        maxNumber = (maxNumber << 1) | (result[i] - '0');
    }

    return maxNumber;       
}
