# coding: utf-8

import pandas as pd
loans_2007 = pd.read_csv("LoanStats3a.csv",skiprows=1)
#数据清理过滤无用特征 
half_count = len(loans_2007)/2
loans_2007 = loans_2007.dropna(thresh=half_count,axis=1)
loans_2007 = loans_2007.drop(['desc','url'],axis=1)
loans_2007.to_csv("loans_2007.csv",index=False)



import pandas as pd
loans_2007 = pd.read_csv("loans_2007.csv")
loans_2007.drop_duplicates()
print (loans_2007.iloc[0])
print (loans_2007.shape[1])



#数据预处理
loans_2007 = loans_2007.drop(['id','member_id','funded_amnt','funded_amnt_inv','grade','sub_grade','emp_title','last_pymnt_d','last_pymnt_amnt'],axis=1)
loans_2007 = loans_2007.drop(['zip_code','out_prncp','out_prncp_inv','total_pymnt','total_pymnt_inv','total_rec_prncp'],axis=1)
loans_2007 = loans_2007.drop(['total_rec_int','total_rec_late_fee','recoveries','collection_recovery_fee','issue_d'],axis=1)
print (loans_2007.iloc[0])
print (loans_2007.shape[1])




#loan_status是当前贷款的状态 
print (loans_2007["loan_status"].value_counts())



#Fully Paid代表已放款，Charged Off代表拒贷,进行二分类
loans_2007 = loans_2007[(loans_2007['loan_status']=='Fully Paid') | (loans_2007['loan_status']=='Charged Off')]
#将字符串转化成数字
status_replace = {
    'loan_status':{
        'Fully Paid':1,
        'Charged Off':0,
    }
}
#将要替换的做成字典，key是对应的列
loans_2007 = loans_2007.replace(status_replace)



orig_columns = loans_2007.columns
drop_columns = []
for col in orig_columns:
    col_series = loans_2007[col].dropna().unique()
    if len(col_series) == 1:
        #如果某一列都是一种值，也将其去掉
        drop_columns.append(col)
        
loans_2007 = loans_2007.drop(drop_columns,axis=1)
print (drop_columns)
print (loans_2007.shape)



#检查是否有缺失值
null_count=loans_2007.isnull().sum()
print (null_count)



loans_2007 = loans_2007.drop("pub_rec_bankruptcies",axis=1)
#去掉有缺失值的行
loans_2007 = loans_2007.dropna(axis=0)
print (loans_2007.dtypes.value_counts())



#从以上结果看，由于sklearn只接受数值形的数据，不接受字符，所以显示为object，我们需要将其转化为字数值
object_columns_df = loans_2007.select_dtypes(include=["object"])
print (object_columns_df.iloc[0])



cols = ['home_ownership','verification_status','emp_length','term','addr_state']
for c in cols:
    print (loans_2007[c].value_counts())



mapping_dict = {
    "emp_length":{
        "10+ years":10,
        "9 years":9,
        "8 years":8,
        "7 years":7,
        "6 years":6,
        "5 years":5,
        "4 years":4,
        "3 years":3,
        "2 years":2,
        "1 year":1,  
        "< 1 year":0,
        "n/a":0
    }   
}
loans_2007 = loans_2007.drop(["last_credit_pull_d","earliest_cr_line","addr_state","title"],axis=1)
#去掉%并转化为浮点型数据
loans_2007["int_rate"]=loans_2007["int_rate"].str.rstrip("%").astype("float")
loans_2007["revol_util"]=loans_2007["revol_util"].str.rstrip("%").astype("float")
loans_2007 = loans_2007.replace(mapping_dict)


cat_columns = ['home_ownership','verification_status','emp_length','purpose','term']
dummy_df = pd.get_dummies(loans_2007[cat_columns])
loans_2007 = pd.concat([loans_2007,dummy_df],axis=1)
loans_2007 = loans_2007.drop(cat_columns,axis=1)


#贷款这样的项目，精度高的意义不大，因为只要亏了一笔，最终可能亏损很大
#所以要考虑ROC指标

#以上为数据预处理的流程，获取已经整理好的数据
loans = pd.read_csv("cleaned_loans2007.csv")
print (loans.info())



#使用逻辑回归来分析数据,逻辑回归是一个非常经典的二分类
from sklearn.linear_model import LogisticRegression
from sklearn.cross_validation import cross_val_predict,KFold

lr = LogisticRegression()
cols = loans.columns
train_cols = cols.drop("loan_status")
features = loans[train_cols]
target = loans["loan_status"]
kf = KFold(features.shape[0],random_state=1)
predictions = cross_val_predict(lr,features,target,cv=kf)
predictions = pd.Series(predictions)


#False positive
fp_filter = (predictions == 1) & (loans["loan_status"]==0)
fp = len(predictions[fp_filter])
#True Positive
tp_filter = (predictions == 1) & (loans["loan_status"]==1)
tp = len(predictions[tp_filter])
#False negative
fn_filter = (predictions == 0) & (loans["loan_status"]==1)
fn = len(predictions[fn_filter])
#True negative
tn_filter = (predictions == 0) & (loans["loan_status"]==0)
tn = len(predictions[tn_filter])

#Rate:True Positive很高，因为我们能赚到，但是False positive的也很高，我们亏本的概率也非常高
#经分析是因为来的人我们几乎都借钱给它了，是因为我们的数据样本不平衡
#解决方法:1.数据增强，增加一些没有借钱给他的数据案例，可以自己制造，也可以自己去收集
tpr = tp/float((tp+fn))
fpr = fp/float((fp+fn))
print (tpr)
print (fpr)
print (predictions[:20])


# In[99]:

#指定参数，调整正负样本的权重
lr = LogisticRegression(class_weight='balanced')
kf = KFold(features.shape[0],random_state=1)
predictions = cross_val_predict(lr,features,target,cv=kf)
predictions = pd.Series(predictions)
#False positive
fp_filter = (predictions == 1) & (loans["loan_status"]==0)
fp = len(predictions[fp_filter])
#True Positive
tp_filter = (predictions == 1) & (loans["loan_status"]==1)
tp = len(predictions[tp_filter])
#False negative
fn_filter = (predictions == 0) & (loans["loan_status"]==1)
fn = len(predictions[fn_filter])
#True negative
tn_filter = (predictions == 0) & (loans["loan_status"]==0)
tn = len(predictions[tn_filter])
tpr = tp/float((tp+fn))
fpr = fp/float((fp+fn))
#经权重项的调整后，训练的模型更加有意义，但是tpr不够高，fpr也不够低
print (tpr)
print (fpr)
print (predictions[:20])


# In[102]:

#以上是使用库函数自带的权重，我们也可以自己指定权重
penalty = {
    0:5,
    1:1
}
lr = LogisticRegression(class_weight=penalty)
kf = KFold(features.shape[0],random_state=1)

predictions = cross_val_predict(lr,features,target,cv=kf)
predictions = pd.Series(predictions)
#False positive
fp_filter = (predictions == 1) & (loans["loan_status"]==0)
fp = len(predictions[fp_filter])
#True Positive
tp_filter = (predictions == 1) & (loans["loan_status"]==1)
tp = len(predictions[tp_filter])
#False negative
fn_filter = (predictions == 0) & (loans["loan_status"]==1)
fn = len(predictions[fn_filter])
#True negative
tn_filter = (predictions == 0) & (loans["loan_status"]==0)
tn = len(predictions[tn_filter])
tpr = tp/float((tp+fn))
fpr = fp/float((fp+fn))
#发现权重项对我们最终的结果影响很大，实际情况中根据需求自己调整权重
print (tpr)
print (fpr)
print (predictions[:20])


# In[106]:

#使用随机森林进行分析
#以上是使用库函数自带的权重，我们也可以自己指定权重
from sklearn.ensemble import RandomForestClassifier

lr = RandomForestClassifier(class_weight="balanced",random_state=1)
kf = KFold(features.shape[0],random_state=1)

predictions = cross_val_predict(lr,features,target,cv=kf)
predictions = pd.Series(predictions)
#False positive
fp_filter = (predictions == 1) & (loans["loan_status"]==0)
fp = len(predictions[fp_filter])
#True Positive
tp_filter = (predictions == 1) & (loans["loan_status"]==1)
tp = len(predictions[tp_filter])
#False negative
fn_filter = (predictions == 0) & (loans["loan_status"]==1)
fn = len(predictions[fn_filter])
#True negative
tn_filter = (predictions == 0) & (loans["loan_status"]==0)
tn = len(predictions[tn_filter])
tpr = tp/float((tp+fn))
fpr = fp/float((fp+fn))
#发现使用随机森林效果也不是很好
print (tpr)
print (fpr)
print (predictions[:20])



# In[108]:

#使用随机森林进行分析
#将树的数量增加到10颗
from sklearn.ensemble import RandomForestClassifier

lr = RandomForestClassifier(n_estimators=10,class_weight="balanced",random_state=1)
kf = KFold(features.shape[0],random_state=1)

predictions = cross_val_predict(lr,features,target,cv=kf)
predictions = pd.Series(predictions)
#False positive
fp_filter = (predictions == 1) & (loans["loan_status"]==0)
fp = len(predictions[fp_filter])
#True Positive
tp_filter = (predictions == 1) & (loans["loan_status"]==1)
tp = len(predictions[tp_filter])
#False negative
fn_filter = (predictions == 0) & (loans["loan_status"]==1)
fn = len(predictions[fn_filter])
#True negative
tn_filter = (predictions == 0) & (loans["loan_status"]==0)
tn = len(predictions[tn_filter])
tpr = tp/float((tp+fn))
fpr = fp/float((fp+fn))
#发现效果也不是很好
print (tpr)
print (fpr)
print (predictions[:20])

#实际中:换算法模型，去掉一些特征，生成一些新的特征，调模型的参数，比如权重等来实现更好的效果

