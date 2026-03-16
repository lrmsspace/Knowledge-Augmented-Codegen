// Source: https://leetcode.com/problems/count-of-integers/   |   Difficulty: Hard
//
// Problem Description:
// You are given two numeric strings num1 and num2 and two integers max_sum and min_sum. We denote an integer x to be good if:
//
//
// 	num1 <= x <= num2
// 	min_sum <= digit_sum(x) <= max_sum.
//
//
// Return the number of good integers. Since the answer may be large, return it modulo 109 + 7.
//
// Note that digit_sum(x) denotes the sum of the digits of x.
//
// Example:
// Input: num1 = "1", num2 = "12", min_sum = 1, max_sum = 8
// Output: 11
// Explanation: There are 11 integers whose sum of digits lies between 1 and 8 are 1,2,3,4,5,6,7,8,10,11, and 12. Thus, we return 11.
//
// Constraints:
// 1 <= num1 <= num2 <= 1022
// 	1 <= min_sum <= max_sum <= 400
//

/**
 * @param {string} num1
 * @param {string} num2
 * @param {number} min_sum
 * @param {number} max_sum
 * @return {number}
 */
var count = function(num1, num2, min_sum, max_sum) {
	var MOD = 1000000007;

	function decString(s) {
		var digits = s.split('').map(function(ch) { return ch.charCodeAt(0) - 48; });
		var i = digits.length - 1;
		while (i >= 0 && digits[i] === 0) {
			digits[i] = 9;
			i -= 1;
		}
		if (i >= 0) {
			digits[i] -= 1;
		}
		while (digits.length > 1 && digits[0] === 0) {
			digits.shift();
		}
		return digits.join('');
	}

	function countUpTo(numStr) {
		var n = numStr.length;
		var memo = Array.from({ length: n + 1 }, function() {
			return Array(max_sum + 1).fill(-1);
		});

		function dfs(pos, sum, tight) {
			if (sum > max_sum) {
				return 0;
			}
			if (pos === n) {
				return (sum >= min_sum && sum <= max_sum) ? 1 : 0;
			}
			if (!tight && memo[pos][sum] !== -1) {
				return memo[pos][sum];
			}

			var limit = tight ? (numStr.charCodeAt(pos) - 48) : 9;
			var total = 0;
			for (var d = 0; d <= limit; d += 1) {
				total += dfs(pos + 1, sum + d, tight && d === limit);
				if (total >= MOD) {
					total %= MOD;
				}
			}

			if (!tight) {
				memo[pos][sum] = total % MOD;
			}
			return total % MOD;
		}

		return dfs(0, 0, true);
	}

	var num1MinusOne = (num1 === '0') ? '0' : decString(num1);
	var result = countUpTo(num2) - countUpTo(num1MinusOne);
	result %= MOD;
	if (result < 0) {
		result += MOD;
	}
	return result;
};
