// Source: https://leetcode.com/problems/duplicate-zeros/   |   Difficulty: Easy
//
// Problem Description:
// Given a fixed-length integer array arr, duplicate each occurrence of zero, shifting the remaining elements to the right.
//
// Note that elements beyond the length of the original array are not written. Do the above modifications to the input array in place and do not return anything.
//
// Example:
// Input: arr = [1,0,2,3,0,4,5,0]
// Output: [1,0,0,2,3,0,0,4]
// Explanation: After calling your function, the input array is modified to: [1,0,0,2,3,0,0,4]
//
// Constraints:
// 1 <= arr.length <= 104
// 	0 <= arr[i] <= 9
//

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int n = arr.size();
        int possibleDups = 0;
        int length_ = n - 1;

        // Find the number of zeros to be duplicated
        for (int left = 0; left <= length_ - possibleDups; left++) {
            if (arr[left] == 0) {
                // Edge case: This zero can't be duplicated. We have to set the last element to zero.
                if (left == length_ - possibleDups) {
                    arr[length_] = 0; // For this zero we just copy it without duplication.
                    length_ -= 1;
                    break;
                }
                possibleDups++;
            }
        }

        // Start backwards from the last element which would be part of the new array.
        int last = length_ - possibleDups;

        // Copy zero twice, and non-zero once.
        for (int i = last; i >= 0; i--) {
            if (arr[i] == 0) {
                arr[i + possibleDups] = 0;
                possibleDups--;
                arr[i + possibleDups] = 0;
            } else {
                arr[i + possibleDups] = arr[i];
            }
        }           
    }
};
