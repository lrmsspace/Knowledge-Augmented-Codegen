// Source: https://leetcode.com/problems/largest-number-after-digit-swaps-by-parity/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer num. You may swap any two digits of num that have the same parity (i.e. both odd digits or both even digits).
//
// Return the largest possible value of num after any number of swaps.
//
// Example:
// Input: num = 1234
// Output: 3412
// Explanation: Swap the digit 3 with the digit 1, this results in the number 3214.
// Swap the digit 2 with the digit 4, this results in the number 3412.
// Note that there may be other sequences of swaps but it can be shown that 3412 is the largest possible number.
// Also note that we may not swap the digit 4 with the digit 1 since they are of different parities.
//
// Constraints:
// 1 <= num <= 109
//

class Solution {
    public int largestInteger(int num) {
        char[] digits = String.valueOf(num).toCharArray();
        List<Character> oddDigits = new ArrayList<>();
        List<Character> evenDigits = new ArrayList<>();

        // Separate digits into odd and even lists
        for (char digit : digits) {
            if ((digit - '0') % 2 == 0) {
                evenDigits.add(digit);
            } else {
                oddDigits.add(digit);
            }
        }

        // Sort both lists in descending order
        Collections.sort(oddDigits, Collections.reverseOrder());
        Collections.sort(evenDigits, Collections.reverseOrder());

        StringBuilder result = new StringBuilder();
        int oddIndex = 0, evenIndex = 0;

        // Reconstruct the largest number by choosing from the sorted lists
        for (char digit : digits) {
            if ((digit - '0') % 2 == 0) {
                result.append(evenDigits.get(evenIndex++));
            } else {
                result.append(oddDigits.get(oddIndex++));
            }
        }

        return Integer.parseInt(result.toString());         
    }
}
