// Source: https://leetcode.com/problems/adding-two-negabinary-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given two numbers arr1 and arr2 in base -2, return the result of adding them together.
//
// Each number is given in array format:  as an array of 0s and 1s, from most significant bit to least significant bit.  For example, arr = [1,1,0,1] represents the number (-2)^3 + (-2)^2 + (-2)^0 = -3.  A number arr in array, format is also guaranteed to have no leading zeros: either arr == [0] or arr[0] == 1.
//
// Return the result of adding arr1 and arr2 in the same format: as an array of 0s and 1s with no leading zeros.
//
// Example:
// Input: arr1 = [1,1,1,1,1], arr2 = [1,0,1]
// Output: [1,0,0,0,0]
// Explanation: arr1 represents 11, arr2 represents 5, the output represents 16.
//
// Constraints:
// 1 <= arr1.length, arr2.length <= 1000
// 	arr1[i] and arr2[i] are 0 or 1
// 	arr1 and arr2 have no leading zeros
//

class Solution {
    public int[] addNegabinary(int[] arr1, int[] arr2) {
        int i = arr1.length - 1;
        int j = arr2.length - 1;
        int carry = 0;
        List<Integer> result = new ArrayList<>();

        while (i >= 0 || j >= 0 || carry != 0) {
            int sum = carry;
            if (i >= 0) {
                sum += arr1[i];
                i--;
            }
            if (j >= 0) {
                sum += arr2[j];
                j--;
            }

            result.add((sum & 1) == 1 ? 1 : 0);
            carry = -(sum >> 1);
        }

        // Remove leading zeros
        while (result.size() > 1 && result.get(result.size() - 1) == 0) {
            result.remove(result.size() - 1);
        }

        // Reverse the result to get the correct order
        Collections.reverse(result);

        // Convert List<Integer> to int[]
        return result.stream().mapToInt(Integer::intValue).toArray();           
    }
}
