// Source: https://leetcode.com/problems/basic-calculator-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given an expression such as expression = "e + 8 - a + 5" and an evaluation map such as {"e": 1} (given in terms of evalvars = ["e"] and evalints = [1]), return a list of tokens representing the simplified expression, such as ["-1*a","14"]
//
//
// 	An expression alternates chunks and symbols, with a space separating each chunk and symbol.
// 	A chunk is either an expression in parentheses, a variable, or a non-negative integer.
// 	A variable is a string of lowercase letters (not including digits.) Note that variables can be multiple letters, and note that variables never have a leading coefficient or unary operator like "2x" or "-x".
//
//
// Expressions are evaluated in the usual order: brackets first, then multiplication, then addition and subtraction.
//
//
// 	For example, expression = "1 + 2 * 3" has an answer of ["7"].
//
//
// The format of the output is as follows:
//
//
// 	For each term of free variables with a non-zero coefficient, we write the free variables within a term in sorted order lexicographically.
// 	
// 		For example, we would never write a term like "b*a*c", only "a*b*c".
// 	
// 	
// 	Terms have degrees equal to the number of free variables being multiplied, counting multiplicity. We write the largest degree terms of our answer first, breaking ties by lexicographic order ignoring the leading coefficient of the term.
// 	
// 		For example, "a*a*b*c" has degree 4.
// 	
// 	
// 	The leading coefficient of the term is placed directly to the left with an asterisk separating it from the variables (if they exist.) A leading coefficient of 1 is still printed.
// 	An example of a well-formatted answer is ["-2*a*a*a", "3*a*a*b", "3*b*b", "4*a", "5*c", "-6"].
// 	Terms (including constant terms) with coefficient 0 are not included.
// 	
// 		For example, an expression of "0" has an output of [].
// 	
// 	
//
//
// Note: You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].
//
// Example:
// Input: expression = "e + 8 - a + 5", evalvars = ["e"], evalints = [1]
// Output: ["-1*a","14"]
//
// Constraints:
// 1 <= expression.length <= 250
// 	expression consists of lowercase English letters, digits, '+', '-', '*', '(', ')', ' '.
// 	expression does not contain any leading or trailing spaces.
// 	All the tokens in expression are separated by a single space.
// 	0 <= evalvars.length <= 100
// 	1 <= evalvars[i].length <= 20
// 	evalvars[i] consists of lowercase English letters.
// 	evalints.length == evalvars.length
// 	-100 <= evalints[i] <= 100
//
// Helpful references (internal KB):
// - Operations on polynomials and series (array, recursion)
//   • When to use: When problems involve manipulating algebraic polynomials or power series, especially when their properties or coefficients are defined recursively. It is also useful for problems involving generating functions to represent sequences.
//   • Idea: This card describes recursive approaches to perform common operations on polynomials and power series, often represented by their coefficients. The complexity varies depending on the specific operation, but many are O(N^2) or O(N log N) with optimized techniques.
//   • Invariants: For a polynomial represented by P[0...N-1], P[i] always stores the coefficient of x^i.; When performing an operation recursively, the result of subproblems correctly represents the corresponding sub-polynomial or sub-series.
//   • Tips: Represent polynomials as arrays of coefficients.; Base cases for recursion are crucial (e.g., constant polynomial, empty series).
//   • Pitfalls: Incorrectly handling polynomial degrees or series truncation.; Off-by-one errors in coefficient indexing.
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} expression
 * @param {string[]} evalvars
 * @param {number[]} evalints
 * @return {string[]}
 */
var basicCalculatorIV = function(expression, evalvars, evalints) {
	const evalMap = new Map();
	for (let i = 0; i < evalvars.length; i += 1) {
		evalMap.set(evalvars[i], evalints[i]);
	}

	const tokenize = (expr) => {
		const tokens = [];
		let i = 0;
		while (i < expr.length) {
			const ch = expr[i];
			if (ch === ' ') {
				i += 1;
				continue;
			}
			if (ch === '+' || ch === '-' || ch === '*' || ch === '(' || ch === ')') {
				tokens.push(ch);
				i += 1;
				continue;
			}
			if (ch >= '0' && ch <= '9') {
				let j = i;
				while (j < expr.length && expr[j] >= '0' && expr[j] <= '9') {
					j += 1;
				}
				tokens.push(expr.slice(i, j));
				i = j;
				continue;
			}
			let j = i;
			while (j < expr.length) {
				const c = expr[j];
				if (c < 'a' || c > 'z') {
					break;
				}
				j += 1;
			}
			tokens.push(expr.slice(i, j));
			i = j;
		}
		return tokens;
	};

	const normalizeVars = (vars) => vars.slice().sort();
	const keyFromVars = (vars) => vars.join('*');
	const varsFromKey = (key) => (key === '' ? [] : key.split('*'));

	const polyFromConstant = (value) => {
		const map = new Map();
		if (value !== 0) {
			map.set('', value);
		}
		return map;
	};

	const polyFromVariable = (name) => {
		if (evalMap.has(name)) {
			return polyFromConstant(evalMap.get(name));
		}
		const map = new Map();
		map.set(name, 1);
		return map;
	};

	const addPoly = (a, b, sign) => {
		const result = new Map(a);
		for (const [key, value] of b.entries()) {
			const nextValue = (result.get(key) || 0) + sign * value;
			if (nextValue === 0) {
				result.delete(key);
			} else {
				result.set(key, nextValue);
			}
		}
		return result;
	};

	const mulPoly = (a, b) => {
		if (a.size === 0 || b.size === 0) {
			return new Map();
		}
		const result = new Map();
		for (const [keyA, valA] of a.entries()) {
			const varsA = varsFromKey(keyA);
			for (const [keyB, valB] of b.entries()) {
				const varsB = varsFromKey(keyB);
				const merged = normalizeVars(varsA.concat(varsB));
				const mergedKey = keyFromVars(merged);
				const nextValue = (result.get(mergedKey) || 0) + valA * valB;
				if (nextValue === 0) {
					result.delete(mergedKey);
				} else {
					result.set(mergedKey, nextValue);
				}
			}
		}
		return result;
	};

	const precedence = (op) => {
		if (op === '*') {
			return 2;
		}
		if (op === '+' || op === '-') {
			return 1;
		}
		return 0;
	};

	const applyOp = (values, op) => {
		const right = values.pop();
		const left = values.pop();
		if (op === '+') {
			values.push(addPoly(left, right, 1));
			return;
		}
		if (op === '-') {
			values.push(addPoly(left, right, -1));
			return;
		}
		values.push(mulPoly(left, right));
	};

	const tokens = tokenize(expression);
	const values = [];
	const ops = [];

	for (const token of tokens) {
		if (token === '(') {
			ops.push(token);
			continue;
		}
		if (token === ')') {
			while (ops.length > 0 && ops[ops.length - 1] !== '(') {
				applyOp(values, ops.pop());
			}
			ops.pop();
			continue;
		}
		if (token === '+' || token === '-' || token === '*') {
			while (ops.length > 0 && precedence(ops[ops.length - 1]) >= precedence(token)) {
				applyOp(values, ops.pop());
			}
			ops.push(token);
			continue;
		}
		if (token[0] >= '0' && token[0] <= '9') {
			values.push(polyFromConstant(Number(token)));
			continue;
		}
		values.push(polyFromVariable(token));
	}

	while (ops.length > 0) {
		applyOp(values, ops.pop());
	}

	const resultPoly = values.length > 0 ? values[0] : new Map();
	const terms = Array.from(resultPoly.entries());
	terms.sort((a, b) => {
		const varsA = a[0] === '' ? [] : a[0].split('*');
		const varsB = b[0] === '' ? [] : b[0].split('*');
		if (varsA.length !== varsB.length) {
			return varsB.length - varsA.length;
		}
		if (a[0] < b[0]) {
			return -1;
		}
		if (a[0] > b[0]) {
			return 1;
		}
		return 0;
	});

	const output = [];
	for (const [key, coef] of terms) {
		if (coef === 0) {
			continue;
		}
		if (key === '') {
			output.push(String(coef));
		} else {
			output.push(`${coef}*${key}`);
		}
	}
	return output;
};
