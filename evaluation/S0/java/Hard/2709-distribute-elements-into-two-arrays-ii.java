// Source: https://leetcode.com/problems/distribute-elements-into-two-arrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 1-indexed array of integers nums of length n.
//
// We define a function greaterCount such that greaterCount(arr, val) returns the number of elements in arr that are strictly greater than val.
//
// You need to distribute all the elements of nums between two arrays arr1 and arr2 using n operations. In the first operation, append nums[1] to arr1. In the second operation, append nums[2] to arr2. Afterwards, in the ith operation:
//
//
// 	If greaterCount(arr1, nums[i]) > greaterCount(arr2, nums[i]), append nums[i] to arr1.
// 	If greaterCount(arr1, nums[i]) < greaterCount(arr2, nums[i]), append nums[i] to arr2.
// 	If greaterCount(arr1, nums[i]) == greaterCount(arr2, nums[i]), append nums[i] to the array with a lesser number of elements.
// 	If there is still a tie, append nums[i] to arr1.
//
//
// The array result is formed by concatenating the arrays arr1 and arr2. For example, if arr1 == [1,2,3] and arr2 == [4,5,6], then result = [1,2,3,4,5,6].
//
// Return the integer array result.
//
// Example:
// Input: nums = [2,1,3,3]
// Output: [2,3,1,3]
// Explanation: After the first 2 operations, arr1 = [2] and arr2 = [1].
// In the 3rd operation, the number of elements greater than 3 is zero in both arrays. Also, the lengths are equal, hence, append nums[3] to arr1.
// In the 4th operation, the number of elements greater than 3 is zero in both arrays. As the length of arr2 is lesser, hence, append nums[4] to arr2.
// After 4 operations, arr1 = [2,3] and arr2 = [1,3].
// Hence, the array result formed by concatenation is [2,3,1,3].
//
// Constraints:
// 3 <= n <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
    public int[] resultArray(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];
        
        // Using TreeMap to maintain sorted order of elements and their counts
        TreeMap<Integer, Integer> arr1Map = new TreeMap<>();
        TreeMap<Integer, Integer> arr2Map = new TreeMap<>();
        
        int arr1Size = 0;
        int arr2Size = 0;
        
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            
            int greaterInArr1 = getGreaterCount(arr1Map, num);
            int greaterInArr2 = getGreaterCount(arr2Map, num);
            
            if (greaterInArr1 > greaterInArr2) {
                // Append to arr1
                result[i] = num;
                arr1Map.put(num, arr1Map.getOrDefault(num, 0) + 1);
                arr1Size++;
            } else if (greaterInArr1 < greaterInArr2) {
                // Append to arr2
                result[i] = num;
                arr2Map.put(num, arr2Map.getOrDefault(num, 0) + 1);
                arr2Size++;
            } else {
                // Equal greater counts
                if (arr1Size <= arr2Size) {
                    // Append to arr1
                    result[i] = num;
                    arr1Map.put(num, arr1Map.getOrDefault(num, 0) + 1);
                    arr1Size++;
                } else {
                    // Append to arr2
                    result[i] = num;
                    arr2Map.put(num, arr2Map.getOrDefault(num, 0) + 1);
                    arr2Size++;
                }
            }
        }
        
        return result;          
    }
}
