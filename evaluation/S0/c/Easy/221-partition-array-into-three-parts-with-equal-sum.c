// Source: https://leetcode.com/problems/partition-array-into-three-parts-with-equal-sum/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of integers arr, return true if we can partition the array into three non-empty parts with equal sums.
//
// Formally, we can partition the array if we can find indexes i + 1 < j with (arr[0] + arr[1] + ... + arr[i] == arr[i + 1] + arr[i + 2] + ... + arr[j - 1] == arr[j] + arr[j + 1] + ... + arr[arr.length - 1])
//
// Example:
// Input: arr = [0,2,1,-6,6,-7,9,1,2,0,1]
// Output: true
// Explanation: 0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1
//
// Constraints:
// 3 <= arr.length <= 5 * 104
// 	-104 <= arr[i] <= 104
//

bool canThreePartsEqualSum(int* arr, int arrSize) {
    int totalSum = 0;
    for (int i = 0; i < arrSize; i++) {
        totalSum += arr[i];
    }

    if (totalSum % 3 != 0) {
        return false;
    }

    int targetSum = totalSum / 3;
    int currentSum = 0;
    int partitionsFound = 0;

    for (int i = 0; i < arrSize; i++) {
        currentSum += arr[i];

        if (currentSum == targetSum) {
            partitionsFound++;
            currentSum = 0;

            if (partitionsFound == 2 && i < arrSize - 1) {
                return true;
            }
        }
    }

    return false;       
}
