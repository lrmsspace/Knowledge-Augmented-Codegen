// Source: https://leetcode.com/problems/finding-3-digit-even-numbers/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array digits, where each element is a digit. The array may contain duplicates.
//
// You need to find all the unique integers that follow the given requirements:
//
//
// 	The integer consists of the concatenation of three elements from digits in any arbitrary order.
// 	The integer does not have leading zeros.
// 	The integer is even.
//
//
// For example, if the given digits were [1, 2, 3], integers 132 and 312 follow the requirements.
//
// Return a sorted array of the unique integers.
//
// Example:
// Input: digits = [2,1,3,0]
// Output: [102,120,130,132,210,230,302,310,312,320]
// Explanation: All the possible integers that follow the requirements are in the output array. 
// Notice that there are no odd integers or integers with leading zeros.
//
// Constraints:
// 3 <= digits.length <= 100
// 	0 <= digits[i] <= 9
//

class Solution {
    public int[] findEvenNumbers(int[] digits) {
        Set<Integer> resultSet = new HashSet<>();

        int n = digits.length;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (i != j && j != k && i != k) {
                        int hundreds = digits[i];
                        int tens = digits[j];
                        int units = digits[k];

                        if (hundreds != 0 && units % 2 == 0) {
                            int number = hundreds * 100 + tens * 10 + units;
                            resultSet.add(number);
                        }
                    }
                }
            }
        }

        int[] result = new int[resultSet.size()];
        int index = 0;
        for (int num : resultSet) {
            result[index++] = num;
        }

        Arrays.sort(result);
        return result;          
    }
}
