#-*- coding: UTF-8 -*-

'''
### 背景介绍
 	穿戴式设备的流行，让我们可以更便利地使用传感器获取人体的各项数据，甚至生理数据。 
当传感器采集到大量数据后，我们就可以通过对数据进行分析和建模，通过各项特征的数值进行用户状态的判断，根据用户所处的状态提供给用户更加精准、便利的服务。

### 数据介绍
	我们现在收集了来自 A,B,C,D,E 5位用户的可穿戴设备上的传感器数据，每位用户的数据集包含一个特征文件（a.feature）和一个标签文件（a.label）。 
特征文件中每一行对应一个时刻的所有传感器数值，标签文件中每行记录了和特征文件中对应时刻的标记过的用户姿态，两个文件的行数相同，相同行之间互相对应。

'''

import pandas as pd
import numpy as np  

from sklearn.preprocessing import Imputer
from sklearn.cross_validation import train_test_split 
from sklearn.metrics import classification_report

from sklearn.neighbors import KNeighborsClassifier
from sklearn.tree import DecisionTreeClassifier
from sklearn.naive_bayes import GaussianNB

def load_datasets(feature_paths, label_paths):
    feature = np.ndarray(shape=(0,41))
    label = np.ndarray(shape=(0,1))
    for file in feature_paths:
        df = pd.read_table(file, delimiter=',', na_values='?', header=None)
        imp = Imputer(missing_values='NaN', strategy='mean', axis=0)
        imp.fit(df)
        df = imp.transform(df)
        feature = np.concatenate((feature, df))

    for file in label_paths:
        df = pd.read_table(file, header=None)
        label = np.concatenate((label, df))

    label = np.ravel(label)
    return feature, label

if __name__ == '__main__':
    ''' 数据路径 '''
    featurePaths = ['A/A.feature','B/B.feature','C/C.feature','D/D.feature','E/E.feature']
    labelPaths = ['A/A.label','B/B.label','C/C.label','D/D.label','E/E.label']
    ''' 读入数据  '''
    x_train,y_train = load_datasets(featurePaths[:4],labelPaths[:4])
    x_test,y_test = load_datasets(featurePaths[4:],labelPaths[4:])
    x_train, x_, y_train, y_ = train_test_split(x_train, y_train, test_size = 0.0)

    print('Start training knn')
    knn = KNeighborsClassifier().fit(x_train, y_train)
    print('Training done')
    answer_knn = knn.predict(x_test)
    print('Prediction done')

    print('Start training DT')
    dt = DecisionTreeClassifier().fit(x_train, y_train)
    print('Training done')
    answer_dt = dt.predict(x_test)
    print('Prediction done')

    print('Start training Bayes')
    gnb = GaussianNB().fit(x_train, y_train)
    print('Training done')
    answer_gnb = gnb.predict(x_test)
    print('Prediction done')

    print('\n\nThe classification report for knn:')
    print(classification_report(y_test, answer_knn))
    print('\n\nThe classification report for DT:')
    print(classification_report(y_test, answer_dt))
    print('\n\nThe classification report for Bayes:')
    print(classification_report(y_test, answer_gnb))

