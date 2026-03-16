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
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int n = arr.size();
        int totalOnes = accumulate(arr.begin(), arr.end(), 0);
        if (totalOnes % 3 != 0) return {-1, -1};
        if (totalOnes == 0) return {0, n - 1};
        
        int onesPerPart = totalOnes / 3;
        int first = -1, second = -1, third = -1;
        int count = 0;
        
        for (int i = 0; i < n; i++) {
            if (arr[i] == 1) {
                count++;
                if (count == 1) first = i;
                else if (count == onesPerPart + 1) second = i;
                else if (count == 2 * onesPerPart + 1) third = i;
            }
        }
        
        // Compare the three parts
        while (third < n) {
            if (arr[first] != arr[second] || arr[first] != arr[third]) {
                return {-1, -1};
            }
            first++;
            second++;
            third++;
        }
        
        return {first - 1, second};         
    }
};
