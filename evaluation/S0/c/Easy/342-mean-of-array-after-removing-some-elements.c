// Source: https://leetcode.com/problems/mean-of-array-after-removing-some-elements/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array arr, return the mean of the remaining integers after removing the smallest 5% and the largest 5% of the elements.
//
// Answers within 10-5 of the actual answer will be considered accepted.
//
// Example:
// Input: arr = [1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3]
// Output: 2.00000
// Explanation: After erasing the minimum and the maximum values of this array, all elements are equal to 2, so the mean is 2.
//
// Constraints:
// 20 <= arr.length <= 1000
// 	arr.length is a multiple of 20.
// 	0 <= arr[i] <= 105
//

double trimMean(int* arr, int arrSize) {
    // Sort the array to easily remove the smallest and largest 5%
    qsort(arr, arrSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int trimCount = arrSize / 20; // Calculate 5% of the array size
    int sum = 0;
    int count = arrSize - 2 * trimCount; // Remaining elements after trimming

    // Sum the remaining elements after removing the smallest and largest 5%
    for (int i = trimCount; i < arrSize - trimCount; i++) {
        sum += arr[i];
    }

    // Calculate and return the mean
    return (double)sum / count;     
}
