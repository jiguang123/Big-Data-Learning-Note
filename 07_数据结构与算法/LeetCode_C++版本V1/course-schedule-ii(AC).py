class Solution:
    # @param {integer} numCourses
    # @param {integer[][]} prerequisites
    # @return {integer[]}
    def findOrder(self, numCourses, prerequisites):
		e = prerequisites
		n = numCourses
		
		g = [set() for i in xrange(n)]
		ind = [0 for i in xrange(n)]
		ec = len(e)
		for i in xrange(ec):
			g[e[i][1]].add(e[i][0])
		for i in xrange(n):
			for j in g[i]:
				ind[j] += 1
		b = [False for i in xrange(n)]
		seq = []
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
			seq.append(i)
		i = 0
		while i < n:
		    if not b[i]:
		        return []
		    i += 1
		return seq
