// Source: https://leetcode.com/problems/number-of-pairs-of-strings-with-concatenation-equal-to-target/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of digit strings nums and a digit string target, return the number of pairs of indices (i, j) (where i != j) such that the concatenation of nums[i] + nums[j] equals target.
//
// Example:
// Input: nums = ["777","7","77","77"], target = "7777"
// Output: 4
// Explanation: Valid pairs are:
// - (0, 1): "777" + "7"
// - (1, 0): "7" + "777"
// - (2, 3): "77" + "77"
// - (3, 2): "77" + "77"
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i].length <= 100
// 	2 <= target.length <= 100
// 	nums[i] and target consist of digits.
// 	nums[i] and target do not have leading zeros.
//

int numOfPairs(char** nums, int numsSize, char* target) {
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < numsSize; j++) {
            if (i != j) {
                // Calculate lengths
                int len_i = strlen(nums[i]);
                int len_j = strlen(nums[j]);
                int len_target = strlen(target);
                
                // Check if concatenation length matches target length
                if (len_i + len_j == len_target) {
                    // Create concatenated string
                    char* concat = (char*)malloc((len_i + len_j + 1) * sizeof(char));
                    strcpy(concat, nums[i]);
                    strcat(concat, nums[j]);
                    
                    // Compare with target
                    if (strcmp(concat, target) == 0) {
                        count++;
                    }
                    
                    free(concat);
                }
            }
        }
    }
    return count;       
}
