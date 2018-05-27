# My code looks ugly enough...
class Solution:
    # @param {integer} numCourses
    # @param {integer[][]} prerequisites
    # @return {boolean}
    def canFinish(self, numCourses, prerequisites):
		e = prerequisites
		n = numCourses
		
		g = [set() for i in xrange(n)]
		ind = [0 for i in xrange(n)]
		ec = len(e)
		for i in xrange(ec):
			g[e[i][1]].add(e[i][0])
		ec = 0
		for i in xrange(n):
			for j in g[i]:
				ind[j] += 1
			ec += len(g[i])
		b = [False for i in xrange(n)]
		while True:
			i = 0
			while i < n:
				if ind[i] == 0 and not b[i]:
					break
				i += 1
			if i == n:
				break
			for j in g[i]:
				ind[j] -= 1
			g[i] = set()
			b[i] = True
		i = 0
		while i < n:
		    if not b[i]:
		        return False
		    i += 1
		return True
