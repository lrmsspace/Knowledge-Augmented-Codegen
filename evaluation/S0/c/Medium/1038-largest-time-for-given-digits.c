// Source: https://leetcode.com/problems/largest-time-for-given-digits/   |   Difficulty: Medium
//
// Problem Description:
// Given an array arr of 4 digits, find the latest 24-hour time that can be made using each digit exactly once.
//
// 24-hour times are formatted as "HH:MM", where HH is between 00 and 23, and MM is between 00 and 59. The earliest 24-hour time is 00:00, and the latest is 23:59.
//
// Return the latest 24-hour time in "HH:MM" format. If no valid time can be made, return an empty string.
//
// Example:
// Input: arr = [1,2,3,4]
// Output: "23:41"
// Explanation: The valid 24-hour times are "12:34", "12:43", "13:24", "13:42", "14:23", "14:32", "21:34", "21:43", "23:14", and "23:41". Of these times, "23:41" is the latest.
//
// Constraints:
// arr.length == 4
// 	0 <= arr[i] <= 9
//

char* largestTimeFromDigits(int* arr, int arrSize) {
    int maxTime = -1;

    // Try every permutation of the 4 digits
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (j == i) continue;
            for (int k = 0; k < 4; ++k) {
                if (k == i || k == j) continue;
                int l = 6 - i - j - k; // since i+j+k+l=0+1+2+3=6

                int hours = arr[i] * 10 + arr[j];
                int minutes = arr[k] * 10 + arr[l];

                if (hours < 24 && minutes < 60) {
                    int totalMinutes = hours * 60 + minutes;
                    if (totalMinutes > maxTime) {
                        maxTime = totalMinutes;
                    }
                }
            }
        }
    }

    if (maxTime == -1) {
        return "";
    } else {
        char* result = (char*)malloc(6 * sizeof(char));
        sprintf(result, "%02d:%02d", maxTime / 60, maxTime % 60);
        return result;
    }       
}
