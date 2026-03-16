// Source: https://leetcode.com/problems/three-equal-parts/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array arr which consists of only zeros and ones, divide the array into three non-empty parts such that all of these parts represent the same binary value.
//
// If it is possible, return any [i, j] with i + 1 < j, such that:
//
//
// 	arr[0], arr[1], ..., arr[i] is the first part,
// 	arr[i + 1], arr[i + 2], ..., arr[j - 1] is the second part, and
// 	arr[j], arr[j + 1], ..., arr[arr.length - 1] is the third part.
// 	All three parts have equal binary values.
//
//
// If it is not possible, return [-1, -1].
//
// Note that the entire part is used when considering what binary value it represents. For example, [1,1,0] represents 6 in decimal, not 3. Also, leading zeros are allowed, so [0,1,1] and [1,1] represent the same value.
//
// Example:
// Input: arr = [1,0,1,0,1]
// Output: [0,3]
//
// Constraints:
// 3 <= arr.length <= 3 * 104
// 	arr[i] is 0 or 1
//

class Solution {
    public int[] threeEqualParts(int[] arr) {
        int n = arr.length;
        int totalOnes = 0;
        for (int num : arr) {
            totalOnes += num;
        }

        if (totalOnes % 3 != 0) {
            return new int[]{-1, -1};
        }
        if (totalOnes == 0) {
            return new int[]{0, n - 1};
        }

        int onesPerPart = totalOnes / 3;
        int firstPartStart = -1, firstPartEnd = -1;
        int secondPartStart = -1, secondPartEnd = -1;
        int thirdPartStart = -1, thirdPartEnd = -1;
        int count = 0;

        for (int i = 0; i < n; i++) {
            if (arr[i] == 1) {
                count++;
                if (count == 1) firstPartStart = i;
                if (count == onesPerPart) firstPartEnd = i;
                if (count == onesPerPart + 1) secondPartStart = i;
                if (count == 2 * onesPerPart) secondPartEnd = i;
                if (count == 2 * onesPerPart + 1) thirdPartStart = i;
                if (count == 3 * onesPerPart) thirdPartEnd = i;
            }
        }

        while (thirdPartEnd < n && arr[firstPartStart] == arr[secondPartStart] && arr[secondPartStart] == arr[thirdPartStart]) {
            firstPartStart++;
            secondPartStart++;
            thirdPartStart++;
            thirdPartEnd++;
        }

        if (thirdPartEnd == n) {
            return new int[]{firstPartEnd, secondPartStart};
        } else {
            return new int[]{-1, -1};
        }           
    }
}
