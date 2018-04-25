# -*- coding: utf-8 -*-

#############################################################################################################
##测试成功与否(未成功，缺少MySQLdb库)(MySQLdb 模块还不支持 Python3.x)
# import pandas as pd
# import MySQLdb
# handle = MySQLdb.connect(host="127.0.0.1",port=3306,user="root",passwd="***",db="sunshine",charset="utf8")
# sql =  'SELECT * FROM `dataanalyst`;' 
# df = pd.read_sql(sql, con=handle)
# handle.close()
# df.to_csv('DataAnalyst.csv')
#############################################################################################################


#############################################################################################################
##成功导出数据库
import pandas as pd
import pymysql

conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', passwd='***', db='sunshine',charset="utf8")
cursor = conn.cursor()

sql =  'SELECT * FROM `rawdata`;'

df = pd.read_sql(sql, conn)

df.to_csv('RawData.csv')

cursor.close()
conn.close()

###############################################################################################################

###############################################################################################
##测试成功与否(未成功，缺少MySQLdb库, MySQLdb 模块还不支持 Python3.x)
# import pandas as pd    
# from sqlalchemy import create_engine  

# # engine = create_engine('mysql+mysqldb://root:password@localhost:3306/databasename?charset=utf8')
# engine = create_engine('mysql+mysqldb://root:password@localhost:3306/sunshine?charset=utf8')

# df = pd.DataFrame()   
# df["A"] = [1,2,3,4]    
# df["B"] = [11,22,33,44] 
# df["C"] = [1,2,3,4]    
# df["D"] = [11,22,33,44]   
# df.to_sql('student',con=engine,if_exists='replace/append/fail',index=False)  

# engine.close()
################################################################################################

###############################################################################################
##测试成功与否(未成功，缺少MySQLdb库, MySQLdb 模块还不支持 Python3.x)
# import tushare as ts 
# import pandas as pd    
# from sqlalchemy import create_engine  

# df = ts.get_hist_data('000875')#读取数据，格式为DataFrame

# # engine = create_engine('mysql+mysqldb://root:password@localhost:3306/databasename?charset=utf8')
# engine = create_engine('mysql+mysqldb://root:password@localhost:3306/sunshine?charset=utf8')

# ##需要现在数据库中创建table 
# df.to_sql('student',con=engine,if_exists='replace/append/fail',index=False)  

# engine.close()
# ################################################################################################