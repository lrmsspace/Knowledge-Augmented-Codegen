// Source: https://leetcode.com/problems/find-the-kth-largest-integer-in-the-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings nums and an integer k. Each string in nums represents an integer without leading zeros.
//
// Return the string that represents the kth largest integer in nums.
//
// Note: Duplicate numbers should be counted distinctly. For example, if nums is ["1","2","2"], "2" is the first largest integer, "2" is the second-largest integer, and "1" is the third-largest integer.
//
// Example:
// Input: nums = ["3","6","7","10"], k = 4
// Output: "3"
// Explanation:
// The numbers in nums sorted in non-decreasing order are ["3","6","7","10"].
// The 4th largest integer in nums is "3".
//
// Constraints:
// 1 <= k <= nums.length <= 104
// 	1 <= nums[i].length <= 100
// 	nums[i] consists of only digits.
// 	nums[i] will not have any leading zeros.
//

char* kthLargestNumber(char** nums, int numsSize, int k) {
    int compare(const void* a, const void* b) {
        char* str1 = *(char**)a;
        char* str2 = *(char**)b;
        int len1 = strlen(str1);
        int len2 = strlen(str2);
        
        if (len1 != len2) {
            return len2 - len1; // Longer string is larger
        }
        return strcmp(str2, str1); // Lexicographical comparison
    }

    qsort(nums, numsSize, sizeof(char*), compare);
    return nums[k - 1];     
}
