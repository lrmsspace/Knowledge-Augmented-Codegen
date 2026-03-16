// Source: https://leetcode.com/problems/valid-mountain-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers arr, return true if and only if it is a valid mountain array.
//
// Recall that arr is a mountain array if and only if:
//
//
// 	arr.length >= 3
// 	There exists some i with 0 < i < arr.length - 1 such that:
// 	
// 		arr[0] < arr[1] < ... < arr[i - 1] < arr[i] 
// 		arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
//
// Example:
// Input: arr = [2,1]
// Output: false
//
// Constraints:
// 1 <= arr.length <= 104
// 	0 <= arr[i] <= 104
//



bool validMountainArray(int* arr, int arrSize){
    if (arrSize < 3) {
        return false;
    }
    
    int i = 0;
    
    // Ascend to the peak
    while (i + 1 < arrSize && arr[i] < arr[i + 1]) {
        i++;
    }
    
    // Peak can't be first or last
    if (i == 0 || i == arrSize - 1) {
        return false;
    }
    
    // Descend from the peak
    while (i + 1 < arrSize && arr[i] > arr[i + 1]) {
        i++;
    }
    
    return i == arrSize - 1;
}
