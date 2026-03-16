// Source: https://leetcode.com/problems/maximum-number-of-balloons/   |   Difficulty: Easy
//
// Problem Description:
// Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as possible.
//
// You can use each character in text at most once. Return the maximum number of instances that can be formed.
//
// Example:
// Input: text = "nlaebolko"
// Output: 1
//
// Constraints:
// 1 <= text.length <= 104
// 	text consists of lower case English letters only.
//
//
//  
// Note: This question is the same as  2287: Rearrange Characters to Make Target String.
//

class Solution {
public:
    int maxNumberOfBalloons(string text) {
        unordered_map<char, int> count;
        for (char c : text) {
            count[c]++;
        }

        int res = INT_MAX;
        res = min(res, count['b']);
        res = min(res, count['a']);
        res = min(res, count['l'] / 2);
        res = min(res, count['o'] / 2);
        res = min(res, count['n']);

        return res;         
    }
};
