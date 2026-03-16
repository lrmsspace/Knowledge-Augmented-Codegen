// Source: https://leetcode.com/problems/latest-time-by-replacing-hidden-digits/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string time in the form of  hh:mm, where some of the digits in the string are hidden (represented by ?).
//
// The valid times are those inclusively between 00:00 and 23:59.
//
// Return the latest valid time you can get from time by replacing the hidden digits.
//
// Example:
// Input: time = "2?:?0"
// Output: "23:50"
// Explanation: The latest hour beginning with the digit '2' is 23 and the latest minute ending with the digit '0' is 50.
//
// Constraints:
// time is in the format hh:mm.
// 	It is guaranteed that you can produce a valid time from the given string.
//

class Solution {
    public String maximumTime(String time) {
        char[] arr = time.toCharArray();

        // Handle hours
        if (arr[0] == '?') {
            if (arr[1] == '?' || arr[1] <= '3') {
                arr[0] = '2';
            } else {
                arr[0] = '1';
            }
        }

        if (arr[1] == '?') {
            if (arr[0] == '2') {
                arr[1] = '3';
            } else {
                arr[1] = '9';
            }
        }

        // Handle minutes
        if (arr[3] == '?') {
            arr[3] = '5';
        }

        if (arr[4] == '?') {
            arr[4] = '9';
        }

        return new String(arr);         
    }
}
