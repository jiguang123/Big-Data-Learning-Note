from sklearn.datasets import fetch_olivetti_faces

# 这部分数据没有直接存储在现有包中，都是通过这类函数在线下载
faces = fetch_olivetti_faces()

# 这里证明，数据是以Dict的形式存储的，与多数实验性数据的格式一致
print (faces.keys())

# 使用shape属性检验数据规模
print (faces.data.shape)
print (faces.target.shape)

from sklearn.cross_validation import train_test_split
from sklearn.svm import SVC

# 同样是分割数据 25%用于测试
X_train, X_test, y_train, y_test = train_test_split(faces.data, faces.target, test_size=0.25, random_state=0)

from sklearn.cross_validation import cross_val_score, KFold
from scipy.stats import sem

# 构造一个便于交叉验证模型性能的函数（模块）
def evaluate_cross_validation(clf, X, y, K):
    # KFold 函数需要如下参数：数据量, 叉验次数, 是否洗牌
    cv = KFold(len(y), K, shuffle=True, random_state = 0)
    # 采用上述的分隔方式进行交叉验证，测试模型性能，对于分类问题，这些得分默认是accuracy，也可以修改为别的
    scores = cross_val_score(clf, X, y, cv=cv)
    print (scores)
    print ('Mean score: %.3f (+/-%.3f)' % (scores.mean(), sem(scores)))
    
# 使用线性核的SVC （后面会说到不同的核，结果可能大不相同）
svc_linear = SVC(kernel='linear')
# 五折交叉验证 K = 5
evaluate_cross_validation(svc_linear, X_train, y_train, 5)


