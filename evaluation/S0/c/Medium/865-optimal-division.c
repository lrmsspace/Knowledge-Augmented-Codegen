// Source: https://leetcode.com/problems/optimal-division/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. The adjacent integers in nums will perform the float division.
//
//
// 	For example, for nums = [2,3,4], we will evaluate the expression "2/3/4".
//
//
// However, you can add any number of parenthesis at any position to change the priority of operations. You want to add these parentheses such the value of the expression after the evaluation is maximum.
//
// Return the corresponding expression that has the maximum value in string format.
//
// Note: your expression should not contain redundant parenthesis.
//
// Example:
// Input: nums = [1000,100,10,2]
// Output: "1000/(100/10/2)"
// Explanation: 1000/(100/10/2) = 1000/((100/10)/2) = 200
// However, the bold parenthesis in "1000/((100/10)/2)" are redundant since they do not influence the operation priority.
// So you should return "1000/(100/10/2)".
// Other cases:
// 1000/(100/10)/2 = 50
// 1000/(100/(10/2)) = 50
// 1000/100/10/2 = 0.5
// 1000/100/(10/2) = 2
//
// Constraints:
// 1 <= nums.length <= 10
// 	2 <= nums[i] <= 1000
// 	There is only one optimal division for the given input.
//

char* optimalDivision(int* nums, int numsSize) {
    char* result = (char*)malloc(32 * numsSize * sizeof(char));
    if (numsSize == 1) {
        sprintf(result, "%d", nums[0]);
    } else if (numsSize == 2) {
        sprintf(result, "%d/%d", nums[0], nums[1]);
    } else {
        char* ptr = result;
        ptr += sprintf(ptr, "%d/(", nums[0]);
        for (int i = 1; i < numsSize; ++i) {
            ptr += sprintf(ptr, "%d", nums[i]);
            if (i != numsSize - 1) {
                ptr += sprintf(ptr, "/");
            }
        }
        sprintf(ptr, ")");
    }
    return result;      
}
