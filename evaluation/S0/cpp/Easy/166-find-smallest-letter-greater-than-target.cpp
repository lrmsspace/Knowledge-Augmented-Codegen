// Source: https://leetcode.com/problems/find-smallest-letter-greater-than-target/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of characters letters that is sorted in non-decreasing order, and a character target. There are at least two different characters in letters.
//
// Return the smallest character in letters that is lexicographically greater than target. If such a character does not exist, return the first character in letters.
//
// Example:
// Input: letters = ["c","f","j"], target = "a"
// Output: "c"
// Explanation: The smallest character that is lexicographically greater than 'a' in letters is 'c'.
//
// Constraints:
// 2 <= letters.length <= 104
// 	letters[i] is a lowercase English letter.
// 	letters is sorted in non-decreasing order.
// 	letters contains at least two different characters.
// 	target is a lowercase English letter.
//

class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int left = 0, right = letters.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (letters[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return letters[left % letters.size()];          
    }
};
