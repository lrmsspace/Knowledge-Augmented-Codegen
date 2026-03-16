// Source: https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n integers and two integers k and x.
//
// The x-sum of an array is calculated by the following procedure:
//
//
// 	Count the occurrences of all elements in the array.
// 	Keep only the occurrences of the top x most frequent elements. If two elements have the same number of occurrences, the element with the bigger value is considered more frequent.
// 	Calculate the sum of the resulting array.
//
//
// Note that if an array has less than x distinct elements, its x-sum is the sum of the array.
//
// Return an integer array answer of length n - k + 1 where answer[i] is the x-sum of the subarray nums[i..i + k - 1].
//
// Example:
// Input: nums = [1,1,2,2,3,4,2,3], k = 6, x = 2
//
// Output: [6,10,12]
//
// Explanation:
//
//
// 	For subarray [1, 1, 2, 2, 3, 4], only elements 1 and 2 will be kept in the resulting array. Hence, answer[0] = 1 + 1 + 2 + 2.
// 	For subarray [1, 2, 2, 3, 4, 2], only elements 2 and 4 will be kept in the resulting array. Hence, answer[1] = 2 + 2 + 2 + 4. Note that 4 is kept in the array since it is bigger than 3 and 1 which occur the same number of times.
// 	For subarray [2, 2, 3, 4, 2, 3], only elements 2 and 3 are kept in the resulting array. Hence, answer[2] = 2 + 2 + 2 + 3 + 3.
//
// Constraints:
// nums.length == n
// 	1 <= n <= 105
// 	1 <= nums[i] <= 109
// 	1 <= x <= k <= nums.length
//

class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        vector<long long> result;
        unordered_map<int, int> freq;
        map<int, set<int>, greater<int>> countMap; // frequency -> set of numbers
        long long currentSum = 0;
        
        auto addNumber = [&](int num) {
            int oldFreq = freq[num];
            if (oldFreq > 0) {
                countMap[oldFreq].erase(num);
                if (countMap[oldFreq].empty()) {
                    countMap.erase(oldFreq);
                }
            }
            freq[num]++;
            int newFreq = freq[num];
            countMap[newFreq].insert(num);
        };
        
        auto removeNumber = [&](int num) {
            int oldFreq = freq[num];
            countMap[oldFreq].erase(num);
            if (countMap[oldFreq].empty()) {
                countMap.erase(oldFreq);
            }
            freq[num]--;
            if (freq[num] > 0) {
                int newFreq = freq[num];
                countMap[newFreq].insert(num);
            } else {
                freq.erase(num);
            }
        };
        
        for (int i = 0; i < k; i++) {
            addNumber(nums[i]);
        }
        
        auto calculateXSum = [&]() {
            long long sum = 0;
            int remaining = x;
            for (auto& [count, numsSet] : countMap) {
                for (int num : numsSet) {
                    int times = min(remaining, count);
                    sum += (long long)num * times;
                    remaining -= times;
                    if (remaining == 0) break;
                }
                if (remaining == 0) break;
            }
            return sum;
        };
        
        currentSum = calculateXSum();
        result.push_back(currentSum);
        
        for (int i = k; i < n; i++) {
            removeNumber(nums[i - k]);
            addNumber(nums[i]);
            currentSum = calculateXSum();
            result.push_back(currentSum);
        }
        
        return result;          
    }
};
