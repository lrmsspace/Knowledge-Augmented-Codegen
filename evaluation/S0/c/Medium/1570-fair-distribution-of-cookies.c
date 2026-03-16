// Source: https://leetcode.com/problems/fair-distribution-of-cookies/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array cookies, where cookies[i] denotes the number of cookies in the ith bag. You are also given an integer k that denotes the number of children to distribute all the bags of cookies to. All the cookies in the same bag must go to the same child and cannot be split up.
//
// The unfairness of a distribution is defined as the maximum total cookies obtained by a single child in the distribution.
//
// Return the minimum unfairness of all distributions.
//
// Example:
// Input: cookies = [8,15,10,20,8], k = 2
// Output: 31
// Explanation: One optimal distribution is [8,15,8] and [10,20]
// - The 1st child receives [8,15,8] which has a total of 8 + 15 + 8 = 31 cookies.
// - The 2nd child receives [10,20] which has a total of 10 + 20 = 30 cookies.
// The unfairness of the distribution is max(31,30) = 31.
// It can be shown that there is no distribution with an unfairness less than 31.
//
// Constraints:
// 2 <= cookies.length <= 8
// 	1 <= cookies[i] <= 105
// 	2 <= k <= cookies.length
//

int distributeCookies(int* cookies, int cookiesSize, int k) {
    int ans = 1e9;
    int distribution[8] = {0};

    void backtrack(int index) {
        if (index == cookiesSize) {
            int maxCookies = 0;
            for (int i = 0; i < k; i++) {
                if (distribution[i] > maxCookies) {
                    maxCookies = distribution[i];
                }
            }
            if (maxCookies < ans) {
                ans = maxCookies;
            }
            return;
        }

        for (int i = 0; i < k; i++) {
            distribution[i] += cookies[index];
            backtrack(index + 1);
            distribution[i] -= cookies[index];
            if (distribution[i] == 0) {
                break;
            }
        }
    }

    backtrack(0);
    return ans;     
}
