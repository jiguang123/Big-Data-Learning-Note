## 1、导入数据
##首先导入整理数据和数据可视化的包
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
%matplotlib inline

df=pd.read_csv('HR_comma_sep.csv')

## 2、检查和理解数据

# 通常，清理数据需要大量的工作，并且可能是一个非常繁琐的过程。这个数据集从是Kaggle上下载的数据，相对而言很干净，不含缺失值。但是，我仍然需要检查数据集，以确保所有其他内容都是可读的，并且观察值与特征名称适当地匹配。

##检查是否有缺失值

df.isnull().any()
# satisfaction_level       False
# last_evaluation          False
# number_project           False
# average_montly_hours     False
# time_spend_company       False
# Work_accident            False
# left                     False
# promotion_last_5years    False
# sales                    False
# salary                   False
# dtype: bool

df = df.rename(columns={'satisfaction_level': 'satisfaction_level', 
                        'last_evaluation': 'last_evaluation',
                        'number_project': 'number_project',
                        'average_montly_hours': 'average_montly_hours',
                        'time_spend_company': 'time_spend_company',
                        'Work_accident': 'Work_accident',
                        'promotion_last_5years': 'promotion',
                        'sales' : 'department',
                        'left' : 'left'
                        })


##由于“部门”和“薪金”的功能是明确的，我将把它转换为数值，以便更好地分析。
##分别查看department列和salary列唯一值有多少个
df1=pd.Series(df['department']).unique()
df2=pd.Series(df['salary']).unique()

df['department'].replace(list(pd.Series(df['department']).unique()),np.arange(10),inplace=True)
df['salary'].replace(list(pd.Series(df['salary']).unique()),[0,1,2],inplace=True)


##把left列移到表的前面，方便分析
front=df['left']
df.drop(labels='left',axis=1,inplace=True)
df.insert(0,'left',front)
df.head()

##查看数据形状和结构

df.shape
# (14999, 10)
df.dtypes
# left                      int64
# satisfaction_level      float64
# last_evaluation         float64
# number_project            int64
# average_montly_hours      int64
# time_spend_company        int64
# Work_accident             int64
# promotion                 int64
# department                int64
# salary                    int64
# dtype: object


# 整理好后，首先对数据变量进行说明：

# left：是否离职
# satisfaction_level：满意度
# last_evaluation：绩效评估
# number_project：完成项目数
# average_montly_hours：平均每月工作时间
# time_spend_company：为公司服务的年限
# work_accident：是否有工作事故
# promotion：过去5 年是否有升职
# salary：薪资水平

##看一下整体数据，大概有76%的人留下了，24%的人离开了
left_rate=df.left.value_counts()/14999
# 0    0.761917
# 1    0.238083
# Name: left, dtype: float64


## 3、对数据进行探索分析

# 1)、初步分析

##对left列进行聚合运算，描述性分析

left_summary=df.groupby('left')
left_summary.mean()
format=lambda x: '%.2f'%x
df.describe().applymap(format)

# 2)、相关性分析

sns.heatmap(corr,xticklabels=corr.columns.values,yticklabels=corr.columns.values);
sns.plt.title('Heatmap of Correlation Matrix')

# 3)、变量分析

##department  vs  left
depart_left_table=pd.crosstab(index=df['department'],columns=df['left'])
##职位：'sales', 'accounting', 'hr', 'technical', 'support', 'management','IT', 'product_mng', 'marketing', 'RandD'
depart_left_table.plot(kind='bar',figsize=(5,5),stacked=True)
##department  vs  salary
depart_salary_table=pd.crosstab(index=df['department'],columns=df['salary'])
depart_salary_table.plot(kind="bar",figsize=(5,5),stacked=True)
##salary  vs left
salary_left_table=pd.crosstab(index=df['salary'],columns=df['left'])
salary_left_table.plot(kind='bar',figsize=(5,5),stacked=True)
##promotion  vs  left
promotion_left_table=pd.crosstab(index=df['promotion'],columns=df['left'])
promotion_left_table.plot(kind='bar',figsize=(5,5),stacked=True)
##number_project  vs  left
project_left_table=pd.crosstab(index=df['number_project'],columns=df['left'])
project_left_table.plot(kind='bar',figsize=(5,5),stacked=True)
df.loc[(df['left']==1),'number_project'].plot(kind='hist',normed=1,bins=15,stacked=False,alpha=1)
##time_spend_company  vs  left
company_left_table=pd.crosstab(index=df['time_spend_company'],columns=df['left'])
company_left_table.plot(kind='bar',figsize=(5,5),stacked=True)
df.loc[(df['left']==1),'time_spend_company'].plot(kind='hist',normed=1,bins=10,stacked=False,alpha=1)
##average_montly_hours  vs  left
hours_left_table=pd.crosstab(index=df['average_montly_hours'],columns=df['left'])
fig=plt.figure(figsize=(10,5))
letf=sns.kdeplot(df.loc[(df['left']==0),'average_montly_hours'],color='b',shade=True,label='no left')
left=sns.kdeplot(df.loc[(df['left']==1),'average_montly_hours'],color='r',shade=True,label='left')
##last_evaluation  vs  left
evaluation_left_table=pd.crosstab(index=df['last_evaluation'],columns=df['left'])
fig=plt.figure(figsize=(10,5))
left=sns.kdeplot(df.loc[(df['left']==0),'last_evaluation'],color='b',shade=True,label='no left')
left=sns.kdeplot(df.loc[(df['left']==1),'last_evaluation'],color='r',shade=True,label='left')
##satisfaction_level  vs  left  
satis_left_table=pd.crosstab(index=df['satisfaction_level'],columns=df['left'])
fig=plt.figure(figsize=(10,5))
left=sns.kdeplot(df.loc[(df['left']==0),'satisfaction_level'],color='b',shade=True,label='no left')
left=sns.kdeplot(df.loc[(df['left']==1),'satisfaction_level'],color='r',shade=True,label='left')
##last_evaluation  vs  satisfaction_level
df1=df[df['left']==1]
fig, ax = plt.subplots(figsize=(10,10))
pd.scatter_matrix(df1[['satisfaction_level','last_evaluation']],color='k',ax=ax)
plt.savefig('scatter.png',dpi=1000,bbox_inches='tight')


# ## 4、总结

# 员工离职概述：

# 离职员工工作时间大部分是~6hours /天（工作）和~10小时/天（劳累）；

# 大部分离职员工薪资都在low~medium这一档，薪资水平低；

# 离职员工，几乎都没有得到升职；

# 大多数离职员工的评价分数在0.6以下和0.8以上；

# 离职员工大多数有2个项目，但同样有4-7个项目的员工离开，3个项目的员工离职率最低；

# 完成项目数，每月平均工作时间，绩效评估有正相关关系。意味着你工作越多，得到的评价就越高；

# 离职率、满意度与薪酬呈负相关关系。这意味着较低的满意度和工资产生了较高的离职率；

# 公司需要考虑的问题：

# 1、失去优秀员工会让公司产生多大损失？招新人和优秀老员工之间的成本与变现孰轻孰重？

# 2、什么原因产生了较低的满意度？

# 3、为什么离开的员工平均比没有离开的员工得到更高的评价，甚至是项目数量的增加？低评价的员工不应该更倾向于离开公司吗？

# 优秀员工看中的是良好的待遇，和更好的职业发展，这些因素都直接影响员工的主观感受，公司给予了员工高的评价，
# 但没有相应转化到薪资和升职的变量中，即使一部分离职的优秀员工给予了公司不错的满意度，但依然不能阻挡他们会追寻更好的工作机会。