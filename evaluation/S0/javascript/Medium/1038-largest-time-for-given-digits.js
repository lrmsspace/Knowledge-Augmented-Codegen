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

/**
 * @param {number[]} arr
 * @return {string}
 */
var largestTimeFromDigits = function(arr) {
    let maxTime = -1;

    // Generate all permutations of arr
    const permute = (nums, l, r) => {
        if (l === r) {
            const hour = nums[0] * 10 + nums[1];
            const minute = nums[2] * 10 + nums[3];
            if (hour < 24 && minute < 60) {
                const totalMinutes = hour * 60 + minute;
                maxTime = Math.max(maxTime, totalMinutes);
            }
        } else {
            for (let i = l; i <= r; i++) {
                [nums[l], nums[i]] = [nums[i], nums[l]];
                permute(nums, l + 1, r);
                [nums[l], nums[i]] = [nums[i], nums[l]];
            }
        }
    }
    permute(arr, 0, arr.length - 1);

    if (maxTime === -1) return "";
    const hh = Math.floor(maxTime / 60).toString().padStart(2, '0');
    const mm = (maxTime % 60).toString().padStart(2, '0');
    return `${hh}:${mm}`;
}
