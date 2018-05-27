// 1AC, great job!
class Solution {
public:
	int maximalRectangle(vector<vector<char> > &matrix) {
		int n, m;
		
		n = (int)matrix.size();
		if (n == 0) {
			return 0;
		}
		m = (int)matrix[0].size();
		if (m == 0) {
			return 0;
		}
		
		vector<int> histogram;
		
		histogram.resize(m);
		int i, j;
		
		for (j = 0; j < m; ++j) {
			histogram[j] = 0;
		}
		
		int max_area = 0;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				if (matrix[i][j] == '0') {
					histogram[j] = 0;
				} else {
					histogram[j] = histogram[j] + 1;
				}
			}
			max_area = max(max_area, largestRectangleArea(histogram));
		}
		
		histogram.clear();
		return max_area;
	}
private:
	int largestRectangleArea(vector<int> &height) {
		int i;
		int n;
		
		n = (int)height.size();
		if (n == 0) {
			return 0;
		}
		
		int max_area = 0;
		int area;
		stack<int> st;
		int top;
		
		for (i = 0; i < n; ++i) {
			if (st.empty() || height[st.top()] <= height[i]) {
				st.push(i);
			} else {
				while (!st.empty() && height[st.top()] > height[i]) {
					top = st.top();
					st.pop();
					if (st.empty()) {
						area = i * height[top];
					} else {
						area = (i - st.top() - 1) * height[top];
					}
					if (area > max_area) {
						max_area = area;
					}
				}
				st.push(i);
			}
		}
		while (!st.empty()) {
			top = st.top();
			st.pop();
			if (st.empty()) {
				area = i * height[top];
			} else {
				area = (i - st.top() - 1) * height[top];
			}
			if (area > max_area) {
				max_area = area;
			}
		}
		
		return max_area;
	}
};