# 载入手写数字的图像像素数据。对于图像处理，除了后续的各种启发式提取有效特征以外，
# 最直接常用的就是像素数据，每个像素都是一个数值，反映颜色。
from sklearn.datasets import load_digits
digits = load_digits()
# 这些经典数据的存储格式非常统一。这是好习惯，统一了接口，也便于快速使用。
digits

# 老套路
X_digits, y_digits = digits.data, digits.target

from sklearn.decomposition import PCA
from matplotlib import pyplot as plt
# 最关键的参数就是n_components = 2个主成分

estimator = PCA(n_components=2)

X_pca = estimator.fit_transform(X_digits)
# scikit-learn的接口设计的很统一。

# 聚类问题经常需要直观的展现数据，降维度的一个直接目的也为此；因此我们这里多展现几个图片直观一些。

def plot_pca_scatter():
    colors = ['black', 'blue', 'purple', 'yellow', 'white', 'red', 'lime', 'cyan', 'orange', 'gray']
    for i in xrange(len(colors)):
        px = X_pca[:, 0][y_digits == i]
        py = X_pca[:, 1][y_digits == i]
        plt.scatter(px, py, c=colors[i])
    plt.legend(digits.target_names)
    plt.xlabel('First Principal Component')
    plt.ylabel('Second Principal Component')
    plt.show()
    
plot_pca_scatter()


