// Source: https://leetcode.com/problems/create-sorted-array-through-instructions/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array instructions, you are asked to create a sorted array from the elements in instructions. You start with an empty container nums. For each element from left to right in instructions, insert it into nums. The cost of each insertion is the minimum of the following:
//
//
// 	The number of elements currently in nums that are strictly less than instructions[i].
// 	The number of elements currently in nums that are strictly greater than instructions[i].
//
//
// For example, if inserting element 3 into nums = [1,2,3,5], the cost of insertion is min(2, 1) (elements 1 and 2 are less than 3, element 5 is greater than 3) and nums will become [1,2,3,3,5].
//
// Return the total cost to insert all elements from instructions into nums. Since the answer may be large, return it modulo 109 + 7
//
// Example:
// Input: instructions = [1,5,6,2]
// Output: 1
// Explanation: Begin with nums = [].
// Insert 1 with cost min(0, 0) = 0, now nums = [1].
// Insert 5 with cost min(1, 0) = 0, now nums = [1,5].
// Insert 6 with cost min(2, 0) = 0, now nums = [1,5,6].
// Insert 2 with cost min(1, 2) = 1, now nums = [1,2,5,6].
// The total cost is 0 + 0 + 0 + 1 = 1.
//
// Constraints:
// 1 <= instructions.length <= 105
// 	1 <= instructions[i] <= 105
//



int createSortedArray(int* instructions, int instructionsSize){
    int MOD = 1000000007;
    int maxVal = 0;
    for (int i = 0; i < instructionsSize; i++) {
        if (instructions[i] > maxVal) {
            maxVal = instructions[i];
        }
    }

    int fenwickTree[maxVal + 1];
    memset(fenwickTree, 0, sizeof(fenwickTree));

    int getSum(int index) {
        int sum = 0;
        while (index > 0) {
            sum += fenwickTree[index];
            index -= index & -index;
        }
        return sum;
    }

    void update(int index, int value) {
        while (index <= maxVal) {
            fenwickTree[index] += value;
            index += index & -index;
        }
    }

    long totalCost = 0;
    for (int i = 0; i < instructionsSize; i++) {
        int lessCount = getSum(instructions[i] - 1);
        int greaterCount = i - getSum(instructions[i]);
        totalCost = (totalCost + (lessCount < greaterCount ? lessCount : greaterCount)) % MOD;
        update(instructions[i], 1);
    }

    return (int)totalCost;
}
