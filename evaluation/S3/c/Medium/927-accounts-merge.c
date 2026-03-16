// Source: https://leetcode.com/problems/accounts-merge/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of accounts where each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.
//
// Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.
//
// After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.
//
// Example:
// Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
// Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
// Explanation:
// The first and second John's are the same person as they have the common email "johnsmith@mail.com".
// The third John and Mary are different people as none of their email addresses are used by other accounts.
// We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
// ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
//
// Constraints:
// 1 <= accounts.length <= 1000
// 	2 <= accounts[i].length <= 10
// 	1 <= accounts[i][j].length <= 30
// 	accounts[i][0] consists of English letters.
// 	accounts[i][j] (for j > 0) is a valid email.
//
// Helpful references (internal KB):
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
//   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
//   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
//   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to efficiently manage a collection of disjoint sets, supporting operations to merge sets and determine if two elements belong to the same set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that maintains a collection of disjoint sets and supports two primary operations: union (merging two sets) and find (determining the representative of an element's set). With path compression and union by rank/size, operations achieve nearly O(1) amortized time complexity.
//   • Invariants: For any element `v`, `parent[v]` is either `v` itself (if `v` is a root) or an ancestor of `v`.; All elements belonging to the same set share a common root representative.
//   • Tips: Apply path compression during `find_set` to optimize future queries.; Utilize union by rank or size to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size results in poor performance.; Failing to correctly identify the root of a set in `find_set`.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

#include <stdlib.h>
#include <string.h>

static char* str_dup_local(const char* s) {
	size_t len;
	char* out;
	if (s == NULL) {
		return NULL;
	}
	len = strlen(s);
	out = (char*)malloc(len + 1);
	if (out == NULL) {
		return NULL;
	}
	memcpy(out, s, len + 1);
	return out;
}

static unsigned long hash_str_local(const char* s) {
	unsigned long h = 1469598103934665603UL;
	while (*s) {
		h ^= (unsigned char)(*s);
		h *= 1099511628211UL;
		s++;
	}
	return h;
}

static int dsu_find(int* parent, int x) {
	if (parent[x] != x) {
		parent[x] = dsu_find(parent, parent[x]);
	}
	return parent[x];
}

static void dsu_union(int* parent, int* dsuSize, int a, int b) {
	int ra = dsu_find(parent, a);
	int rb = dsu_find(parent, b);
	if (ra == rb) {
		return;
	}
	if (dsuSize[ra] < dsuSize[rb]) {
		int tmp = ra;
		ra = rb;
		rb = tmp;
	}
	parent[rb] = ra;
	dsuSize[ra] += dsuSize[rb];
}

static int email_map_get_or_add(
	const char* email,
	const char* name,
	char** mapKeys,
	int* mapVals,
	int mapCap,
	int* nextId,
	int* parent,
	int* dsuSize,
	char** idToEmail,
	char** idToName
) {
	unsigned long h = hash_str_local(email);
	int idx = (int)(h & (unsigned long)(mapCap - 1));
	while (mapVals[idx] != -1) {
		if (strcmp(mapKeys[idx], email) == 0) {
			return mapVals[idx];
		}
		idx = (idx + 1) & (mapCap - 1);
	}

	{
		int id = *nextId;
		char* emailCopy = str_dup_local(email);
		char* nameCopy = str_dup_local(name);
		if (emailCopy == NULL || nameCopy == NULL) {
			if (emailCopy != NULL) {
				free(emailCopy);
			}
			if (nameCopy != NULL) {
				free(nameCopy);
			}
			return -1;
		}
		mapKeys[idx] = emailCopy;
		mapVals[idx] = id;
		parent[id] = id;
		dsuSize[id] = 1;
		idToEmail[id] = emailCopy;
		idToName[id] = nameCopy;
		*nextId = id + 1;
		return id;
	}
}

static int* g_sortRoots = NULL;
static char** g_sortEmails = NULL;

static int cmp_indices_by_root_then_email(const void* a, const void* b) {
	int ia = *(const int*)a;
	int ib = *(const int*)b;
	if (g_sortRoots[ia] != g_sortRoots[ib]) {
		return (g_sortRoots[ia] < g_sortRoots[ib]) ? -1 : 1;
	}
	return strcmp(g_sortEmails[ia], g_sortEmails[ib]);
}

static void free_partial_result(char*** result, int* colSizes, int rowsBuilt) {
	int i;
	if (result != NULL) {
		for (i = 0; i < rowsBuilt; i++) {
			int j;
			if (result[i] != NULL) {
				for (j = 0; j < colSizes[i]; j++) {
					free(result[i][j]);
				}
				free(result[i]);
			}
		}
	}
	free(result);
	free(colSizes);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** accountsMerge(char*** accounts, int accountsSize, int* accountsColSize, int* returnSize, int** returnColumnSizes) {
	int i;
	int totalEmails = 0;
	int maxMapCap = 1;
	int emailCount = 0;

	char** mapKeys = NULL;
	int* mapVals = NULL;

	int* parent = NULL;
	int* dsuSize = NULL;
	char** idToEmail = NULL;
	char** idToName = NULL;

	int* roots = NULL;
	int* indices = NULL;

	char*** result = NULL;
	int* colSizes = NULL;

	*returnSize = 0;
	*returnColumnSizes = NULL;

	for (i = 0; i < accountsSize; i++) {
		totalEmails += (accountsColSize[i] - 1);
	}

	if (totalEmails <= 0) {
		return NULL;
	}

	while (maxMapCap < totalEmails * 2) {
		maxMapCap <<= 1;
	}

	mapKeys = (char**)malloc((size_t)maxMapCap * sizeof(char*));
	mapVals = (int*)malloc((size_t)maxMapCap * sizeof(int));
	parent = (int*)malloc((size_t)totalEmails * sizeof(int));
	dsuSize = (int*)malloc((size_t)totalEmails * sizeof(int));
	idToEmail = (char**)malloc((size_t)totalEmails * sizeof(char*));
	idToName = (char**)malloc((size_t)totalEmails * sizeof(char*));

	if (mapKeys == NULL || mapVals == NULL || parent == NULL || dsuSize == NULL || idToEmail == NULL || idToName == NULL) {
		free(mapKeys);
		free(mapVals);
		free(parent);
		free(dsuSize);
		free(idToEmail);
		free(idToName);
		return NULL;
	}

	for (i = 0; i < maxMapCap; i++) {
		mapKeys[i] = NULL;
		mapVals[i] = -1;
	}

	for (i = 0; i < accountsSize; i++) {
		int j;
		int firstId = -1;
		char* name = accounts[i][0];
		for (j = 1; j < accountsColSize[i]; j++) {
			int id = email_map_get_or_add(
				accounts[i][j],
				name,
				mapKeys,
				mapVals,
				maxMapCap,
				&emailCount,
				parent,
				dsuSize,
				idToEmail,
				idToName
			);
			if (id < 0) {
				int k;
				for (k = 0; k < emailCount; k++) {
					free(idToEmail[k]);
					free(idToName[k]);
				}
				free(mapKeys);
				free(mapVals);
				free(parent);
				free(dsuSize);
				free(idToEmail);
				free(idToName);
				return NULL;
			}
			if (firstId < 0) {
				firstId = id;
			} else {
				dsu_union(parent, dsuSize, firstId, id);
			}
		}
	}

	roots = (int*)malloc((size_t)emailCount * sizeof(int));
	indices = (int*)malloc((size_t)emailCount * sizeof(int));
	if (roots == NULL || indices == NULL) {
		for (i = 0; i < emailCount; i++) {
			free(idToEmail[i]);
			free(idToName[i]);
		}
		free(roots);
		free(indices);
		free(mapKeys);
		free(mapVals);
		free(parent);
		free(dsuSize);
		free(idToEmail);
		free(idToName);
		return NULL;
	}

	for (i = 0; i < emailCount; i++) {
		roots[i] = dsu_find(parent, i);
		indices[i] = i;
	}

	g_sortRoots = roots;
	g_sortEmails = idToEmail;
	qsort(indices, (size_t)emailCount, sizeof(int), cmp_indices_by_root_then_email);

	result = (char***)malloc((size_t)emailCount * sizeof(char**));
	colSizes = (int*)malloc((size_t)emailCount * sizeof(int));
	if (result == NULL || colSizes == NULL) {
		for (i = 0; i < emailCount; i++) {
			free(idToEmail[i]);
			free(idToName[i]);
		}
		free(result);
		free(colSizes);
		free(roots);
		free(indices);
		free(mapKeys);
		free(mapVals);
		free(parent);
		free(dsuSize);
		free(idToEmail);
		free(idToName);
		return NULL;
	}

	{
		int outCount = 0;
		int start = 0;
		while (start < emailCount) {
			int end = start + 1;
			int root = roots[indices[start]];
			int groupSize;
			char** row;
			int writePos;

			while (end < emailCount && roots[indices[end]] == root) {
				end++;
			}

			groupSize = end - start;
			row = (char**)malloc((size_t)(groupSize + 1) * sizeof(char*));
			if (row == NULL) {
				int k;
				for (k = 0; k < emailCount; k++) {
					free(idToEmail[k]);
					free(idToName[k]);
				}
				free_partial_result(result, colSizes, outCount);
				free(roots);
				free(indices);
				free(mapKeys);
				free(mapVals);
				free(parent);
				free(dsuSize);
				free(idToEmail);
				free(idToName);
				return NULL;
			}

			row[0] = str_dup_local(idToName[root]);
			if (row[0] == NULL) {
				int k;
				free(row);
				for (k = 0; k < emailCount; k++) {
					free(idToEmail[k]);
					free(idToName[k]);
				}
				free_partial_result(result, colSizes, outCount);
				free(roots);
				free(indices);
				free(mapKeys);
				free(mapVals);
				free(parent);
				free(dsuSize);
				free(idToEmail);
				free(idToName);
				return NULL;
			}

			writePos = 1;
			for (i = start; i < end; i++) {
				row[writePos] = str_dup_local(idToEmail[indices[i]]);
				if (row[writePos] == NULL) {
					int t;
					for (t = 0; t < writePos; t++) {
						free(row[t]);
					}
					free(row);
					for (t = 0; t < emailCount; t++) {
						free(idToEmail[t]);
						free(idToName[t]);
					}
					free_partial_result(result, colSizes, outCount);
					free(roots);
					free(indices);
					free(mapKeys);
					free(mapVals);
					free(parent);
					free(dsuSize);
					free(idToEmail);
					free(idToName);
					return NULL;
				}
				writePos++;
			}

			result[outCount] = row;
			colSizes[outCount] = groupSize + 1;
			outCount++;
			start = end;
		}

		*returnSize = outCount;
	}

	*returnColumnSizes = colSizes;

	for (i = 0; i < emailCount; i++) {
		free(idToEmail[i]);
		free(idToName[i]);
	}
	free(roots);
	free(indices);
	free(mapKeys);
	free(mapVals);
	free(parent);
	free(dsuSize);
	free(idToEmail);
	free(idToName);

	return result;
}