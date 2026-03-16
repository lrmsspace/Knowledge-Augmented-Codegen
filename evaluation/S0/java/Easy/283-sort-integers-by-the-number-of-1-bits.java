// Source: https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array arr. Sort the integers in the array in ascending order by the number of 1's in their binary representation and in case of two or more integers have the same number of 1's you have to sort them in ascending order.
//
// Return the array after sorting it.
//
// Example:
// Input: arr = [0,1,2,3,4,5,6,7,8]
// Output: [0,1,2,4,8,3,5,6,7]
// Explantion: [0] is the only integer with 0 bits.
// [1,2,4,8] all have 1 bit.
// [3,5,6] have 2 bits.
// [7] has 3 bits.
// The sorted array by bits is [0,1,2,4,8,3,5,6,7]
//
// Constraints:
// 1 <= arr.length <= 500
// 	0 <= arr[i] <= 104
//

class Solution {
    public int[] sortByBits(int[] arr) {
        Integer[] boxedArr = Arrays.stream(arr).boxed().toArray(Integer[]::new);

        Arrays.sort(boxedArr, (a, b) -> {
            int countA = Integer.bitCount(a);
            int countB = Integer.bitCount(b);

            if (countA != countB) {
                return Integer.compare(countA, countB);
            } else {
                return Integer.compare(a, b);
            }
        });

        return Arrays.stream(boxedArr).mapToInt(Integer::intValue).toArray();           
    }
}
