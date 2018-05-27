# 1RE, 2WA, 1AC, DFS
class Solution:
	# @param {integer} k
	# @param {integer} n
	# @return {integer[][]}
	def combinationSum3(self, k, n):
		ans = []
		self.__dfs__(ans, 1, [], 0, k, n)
		return ans
		
	def __dfs__(self, ans, idx, a, s, k, n):
		if len(a) == k:
			if s == n:
				ans.append(a[:])
			return
		if s + idx * (k - len(a)) > n:
			return
		if s + 9 * (k - len(a)) < n:
			return
		for i in xrange(idx, 10):
			if s + i > n:
				continue
			a.append(i)
			self.__dfs__(ans, i + 1, a, s + i, k, n)
			a.pop()