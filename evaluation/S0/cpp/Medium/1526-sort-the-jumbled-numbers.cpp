// Source: https://leetcode.com/problems/sort-the-jumbled-numbers/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array mapping which represents the mapping rule of a shuffled decimal system. mapping[i] = j means digit i should be mapped to digit j in this system.
//
// The mapped value of an integer is the new integer obtained by replacing each occurrence of digit i in the integer with mapping[i] for all 0 <= i <= 9.
//
// You are also given another integer array nums. Return the array nums sorted in non-decreasing order based on the mapped values of its elements.
//
// Example:
// Input: mapping = [8,9,4,0,2,1,3,5,7,6], nums = [991,338,38]
// Output: [338,38,991]
// Explanation: 
// Map the number 991 as follows:
// 1. mapping[9] = 6, so all occurrences of the digit 9 will become 6.
// 2. mapping[1] = 9, so all occurrences of the digit 1 will become 9.
// Therefore, the mapped value of 991 is 669.
// 338 maps to 007, or 7 after removing the leading zeros.
// 38 maps to 07, which is also 7 after removing leading zeros.
// Since 338 and 38 share the same mapped value, they should remain in the same relative order, so 338 comes before 38.
// Thus, the sorted array is [338,38,991].
//
// Constraints:
// mapping.length == 10
// 	0 <= mapping[i] <= 9
// 	All the values of mapping[i] are unique.
// 	1 <= nums.length <= 3 * 104
// 	0 <= nums[i] < 109
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums) {
        auto getMappedValue = [&](int num) {
            if (num == 0) return mapping[0];
            int mappedNum = 0, place = 1;
            while (num > 0) {
                int digit = num % 10;
                mappedNum += mapping[digit] * place;
                place *= 10;
                num /= 10;
            }
            return mappedNum;
        };

        vector<pair<int, int>> mappedNums; // pair of (mapped value, original value)
        for (int num : nums) {
            mappedNums.emplace_back(getMappedValue(num), num);
        }

        stable_sort(mappedNums.begin(), mappedNums.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.first < b.first;
        });

        vector<int> result;
        for (const auto& p : mappedNums) {
            result.push_back(p.second);
        }

        return result;          
    }
};
