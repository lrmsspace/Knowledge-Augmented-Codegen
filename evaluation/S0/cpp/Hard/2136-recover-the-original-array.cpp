// Source: https://leetcode.com/problems/recover-the-original-array/   |   Difficulty: Hard
//
// Problem Description:
// Alice had a 0-indexed array arr consisting of n positive integers. She chose an arbitrary positive integer k and created two new 0-indexed integer arrays lower and higher in the following manner:
//
//
// 	lower[i] = arr[i] - k, for every index i where 0 <= i < n
// 	higher[i] = arr[i] + k, for every index i where 0 <= i < n
//
//
// Unfortunately, Alice lost all three arrays. However, she remembers the integers that were present in the arrays lower and higher, but not the array each integer belonged to. Help Alice and recover the original array.
//
// Given an array nums consisting of 2n integers, where exactly n of the integers were present in lower and the remaining in higher, return the original array arr. In case the answer is not unique, return any valid array.
//
// Note: The test cases are generated such that there exists at least one valid array arr.
//
// Example:
// Input: nums = [2,10,6,4,8,12]
// Output: [3,7,11]
// Explanation:
// If arr = [3,7,11] and k = 1, we get lower = [2,6,10] and higher = [4,8,12].
// Combining lower and higher gives us [2,6,10,4,8,12], which is a permutation of nums.
// Another valid possibility is that arr = [5,7,9] and k = 3. In that case, lower = [2,4,6] and higher = [8,10,12].
//
// Constraints:
// 2 * n == nums.length
// 	1 <= n <= 1000
// 	1 <= nums[i] <= 109
// 	The test cases are generated such that there exists at least one valid array arr.
//

class Solution {
public:
    vector<int> recoverArray(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        for (int i = 1; i < n; i++) {
            int diff = nums[i] - nums[0];
            if (diff <= 0 || diff % 2 != 0) continue;
            int k = diff / 2;
            
            multiset<int> s(nums.begin(), nums.end());
            vector<int> result;
            bool valid = true;
            
            while (!s.empty()) {
                int val = *s.begin();
                s.erase(s.begin());
                
                if (s.find(val + 2 * k) == s.end()) {
                    valid = false;
                    break;
                } else {
                    s.erase(s.find(val + 2 * k));
                    result.push_back(val + k);
                }
            }
            
            if (valid) {
                return result;
            }
        }
        
        return {};          
    }
};
