// Source: https://leetcode.com/problems/count-good-triplets/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers arr, and three integers a, b and c. You need to find the number of good triplets.
//
// A triplet (arr[i], arr[j], arr[k]) is good if the following conditions are true:
//
//
// 	0 <= i < j < k < arr.length
// 	|arr[i] - arr[j]| <= a
// 	|arr[j] - arr[k]| <= b
// 	|arr[i] - arr[k]| <= c
//
//
// Where |x| denotes the absolute value of x.
//
// Return the number of good triplets.
//
// Example:
// Input: arr = [3,0,1,1,9,7], a = 7, b = 2, c = 3
// Output: 4
// Explanation: There are 4 good triplets: [(3,0,1), (3,0,1), (3,1,1), (0,1,1)].
//
// Constraints:
// 3 <= arr.length <= 100
// 	0 <= arr[i] <= 1000
// 	0 <= a, b, c <= 1000
//



int countGoodTriplets(int* arr, int arrSize, int a, int b, int c){
    int count = 0;
    for (int i = 0; i < arrSize - 2; i++) {
        for (int j = i + 1; j < arrSize - 1; j++) {
            if (abs(arr[i] - arr[j]) <= a) {
                for (int k = j + 1; k < arrSize; k++) {
                    if (abs(arr[j] - arr[k]) <= b && abs(arr[i] - arr[k]) <= c) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}
