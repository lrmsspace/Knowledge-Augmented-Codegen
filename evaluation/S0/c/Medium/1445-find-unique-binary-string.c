// Source: https://leetcode.com/problems/find-unique-binary-string/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings nums containing n unique binary strings each of length n, return a binary string of length n that does not appear in nums. If there are multiple answers, you may return any of them.
//
// Example:
// Input: nums = ["01","10"]
// Output: "11"
// Explanation: "11" does not appear in nums. "00" would also be correct.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 16
// 	nums[i].length == n
// 	nums[i] is either '0' or '1'.
// 	All the strings of nums are unique.
//

char* findDifferentBinaryString(char** nums, int numsSize) {
    char* result = (char*)malloc((numsSize + 1) * sizeof(char));
    for (int i = 0; i < numsSize; i++) {
        result[i] = (nums[i][i] == '0') ? '1' : '0';
    }
    result[numsSize] = '\0';
    return result;      
}
