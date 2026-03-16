// Source: https://leetcode.com/problems/happy-students/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n where n is the total number of students in the class. The class teacher tries to select a group of students so that all the students remain happy.
//
// The ith student will become happy if one of these two conditions is met:
//
//
// 	The student is selected and the total number of selected students is strictly greater than nums[i].
// 	The student is not selected and the total number of selected students is strictly less than nums[i].
//
//
// Return the number of ways to select a group of students so that everyone remains happy.
//
// Example:
// Input: nums = [1,1]
// Output: 2
// Explanation: 
// The two possible ways are:
// The class teacher selects no student.
// The class teacher selects both students to form the group. 
// If the class teacher selects just one student to form a group then the both students will not be happy. Therefore, there are only two possible ways.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] < nums.length
//

int countWays(int* nums, int numsSize) {
    int MOD = 1e9 + 7;
    long long result = 0;
    
    // Sort the array to facilitate counting
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);
    
    // Count occurrences of each number
    int* count = (int*)calloc(numsSize + 1, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }
    
    // Calculate the number of ways
    long long prefixSum = 0;
    for (int k = 0; k <= numsSize; k++) {
        prefixSum += count[k];
        if (prefixSum == k) {
            result = (result + 1) % MOD;
        }
    }
    
    free(count);
    return (int)result;     
}
