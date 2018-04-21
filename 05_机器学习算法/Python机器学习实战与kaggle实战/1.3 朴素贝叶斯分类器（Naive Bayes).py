from sklearn.datasets import fetch_20newsgroups

# 与之前的人脸数据集一样，20类新闻数据同样需要临时下载函数的帮忙
news = fetch_20newsgroups(subset='all')

# 查验数据，依然采用dict格式，共有18846条样本
print (len(news.data), len(news.target))
print (news.target)

# 查验一下新闻类别和种数
print (news.target_names)
print (news.target_names.__len__())

# 同样，我们选取25%的数据用来测试模型性能
from sklearn.cross_validation import train_test_split

X_train, X_test, y_train, y_test = train_test_split(news.data, news.target, test_size=0.25)

# 许多原始数据无法直接被分类器所使用，图像可以直接使用pixel信息，文本则需要进一步处理成数值化的信息
from sklearn.feature_extraction.text import CountVectorizer, HashingVectorizer, TfidfVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.pipeline import Pipeline
from sklearn.cross_validation import *
from scipy.stats import sem
# 我们在NB_Classifier的基础上，对比几种特征抽取方法的性能。并且使用Pipline简化构建训练流程
clf_1 = Pipeline([('count_vec', CountVectorizer()), ('mnb', MultinomialNB())])
clf_2 = Pipeline([('hash_vec', HashingVectorizer(non_negative=True)), ('mnb', MultinomialNB())])
clf_3 = Pipeline([('tfidf_vec', TfidfVectorizer()), ('mnb', MultinomialNB())])

# 构造一个便于交叉验证模型性能的函数（模块）
def evaluate_cross_validation(clf, X, y, K):
    # KFold 函数需要如下参数，数据量, K,是否洗牌
    cv = KFold(len(y), K, shuffle=True, random_state = 0)
    # 采用上述的分隔方式进行交叉验证，测试模型性能，对于分类问题，这些得分默认是accuracy，也可以修改为别的
    scores = cross_val_score(clf, X, y, cv=cv)
    print (scores)
    print ('Mean score: %.3f (+/-%.3f)' % (scores.mean(), sem(scores)))


clfs = [clf_1, clf_2, clf_3]
for clf in clfs:
    evaluate_cross_validation(clf, X_train, y_train, 5)

# 从上述结果中，我们发现常用的两个特征提取方法得到的性能相当。 让我们选取其中之一，进一步靠特征的精细筛选提升性能。
clf_4 = Pipeline([('tfidf_vec_adv', TfidfVectorizer(stop_words='english')), ('mnb', MultinomialNB())])
evaluate_cross_validation(clf_4, X_train, y_train, 5)


# 如果再尝试修改贝叶斯分类器的平滑参数，也许性能会更上一层楼。
clf_5 = Pipeline([('tfidf_vec_adv', TfidfVectorizer(stop_words='english')), ('mnb', MultinomialNB(alpha=0.01))])
evaluate_cross_validation(clf_5, X_train, y_train, 5)

