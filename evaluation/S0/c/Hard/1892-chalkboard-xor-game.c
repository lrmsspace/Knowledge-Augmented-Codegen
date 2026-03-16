// Source: https://leetcode.com/problems/chalkboard-xor-game/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums represents the numbers written on a chalkboard.
//
// Alice and Bob take turns erasing exactly one number from the chalkboard, with Alice starting first. If erasing a number causes the bitwise XOR of all the elements of the chalkboard to become 0, then that player loses. The bitwise XOR of one element is that element itself, and the bitwise XOR of no elements is 0.
//
// Also, if any player starts their turn with the bitwise XOR of all the elements of the chalkboard equal to 0, then that player wins.
//
// Return true if and only if Alice wins the game, assuming both players play optimally.
//
// Example:
// Input: nums = [1,1,2]
// Output: false
// Explanation: 
// Alice has two choices: erase 1 or erase 2. 
// If she erases 1, the nums array becomes [1, 2]. The bitwise XOR of all the elements of the chalkboard is 1 XOR 2 = 3. Now Bob can remove any element he wants, because Alice will be the one to erase the last element and she will lose. 
// If Alice erases 2 first, now nums become [1, 1]. The bitwise XOR of all the elements of the chalkboard is 1 XOR 1 = 0. Alice will lose.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	0 <= nums[i] < 216
//

bool xorGame(int* nums, int numsSize) {
    int xorSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        xorSum ^= nums[i];
    }
    return (xorSum == 0) || (numsSize % 2 == 0);        
}
