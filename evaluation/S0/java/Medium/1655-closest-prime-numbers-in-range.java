// Source: https://leetcode.com/problems/closest-prime-numbers-in-range/   |   Difficulty: Medium
//
// Problem Description:
// Given two positive integers left and right, find the two integers num1 and num2 such that:
//
//
// 	left <= num1 < num2 <= right .
// 	Both num1 and num2 are prime numbers.
// 	num2 - num1 is the minimum amongst all other pairs satisfying the above conditions.
//
//
// Return the positive integer array ans = [num1, num2]. If there are multiple pairs satisfying these conditions, return the one with the smallest num1 value. If no such numbers exist, return [-1, -1].
//
// Example:
// Input: left = 10, right = 19
// Output: [11,13]
// Explanation: The prime numbers between 10 and 19 are 11, 13, 17, and 19.
// The closest gap between any pair is 2, which can be achieved by [11,13] or [17,19].
// Since 11 is smaller than 17, we return the first pair.
//
// Constraints:
// 1 <= left <= right <= 106
//
//
//  
// .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
// }
// .spoiler {overflow:hidden;}
// .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
// .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
// .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
//

class Solution {
    public int[] closestPrimes(int left, int right) {
        boolean[] isPrime = new boolean[right + 1];
        for (int i = 2; i <= right; i++) {
            isPrime[i] = true;
        }

        for (int i = 2; i * i <= right; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= right; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        int prevPrime = -1;
        int minDiff = Integer.MAX_VALUE;
        int[] result = {-1, -1};

        for (int num = left; num <= right; num++) {
            if (isPrime[num]) {
                if (prevPrime != -1) {
                    int diff = num - prevPrime;
                    if (diff < minDiff) {
                        minDiff = diff;
                        result[0] = prevPrime;
                        result[1] = num;
                    }
                }
                prevPrime = num;
            }
        }

        return result;          
    }
}
