// Source: https://leetcode.com/problems/find-xor-sum-of-all-pairs-bitwise-and/   |   Difficulty: Hard
//
// Problem Description:
// The XOR sum of a list is the bitwise XOR of all its elements. If the list only contains one element, then its XOR sum will be equal to this element.
//
//
// 	For example, the XOR sum of [1,2,3,4] is equal to 1 XOR 2 XOR 3 XOR 4 = 4, and the XOR sum of [3] is equal to 3.
//
//
// You are given two 0-indexed arrays arr1 and arr2 that consist only of non-negative integers.
//
// Consider the list containing the result of arr1[i] AND arr2[j] (bitwise AND) for every (i, j) pair where 0 <= i < arr1.length and 0 <= j < arr2.length.
//
// Return the XOR sum of the aforementioned list.
//
// Example:
// Input: arr1 = [1,2,3], arr2 = [6,5]
// Output: 0
// Explanation: The list = [1 AND 6, 1 AND 5, 2 AND 6, 2 AND 5, 3 AND 6, 3 AND 5] = [0,1,2,0,2,1].
// The XOR sum = 0 XOR 1 XOR 2 XOR 0 XOR 2 XOR 1 = 0.
//
// Constraints:
// 1 <= arr1.length, arr2.length <= 105
// 	0 <= arr1[i], arr2[j] <= 109
//

int getXORSum(int* arr1, int arr1Size, int* arr2, int arr2Size) {
    int xor1 = 0, xor2 = 0;
    for (int i = 0; i < arr1Size; ++i) {
        xor1 ^= arr1[i];
    }
    for (int j = 0; j < arr2Size; ++j) {
        xor2 ^= arr2[j];
    }
    return xor1 & xor2;     
}
