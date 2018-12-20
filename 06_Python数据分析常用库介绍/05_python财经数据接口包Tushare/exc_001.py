# /usr/bin/env python3
# -*- coding:utf-8 -*-

import pandas as pd 
import tushare as ts 
import matplotlib.pyplot as plt

data = ts.get_hist_data('600848',start='2018-04-22',end='2018-10-26')

# pd = pd.DataFrame(data)
# pd.to_csv('60048交易数据.csv')

data['open'].plot()
plt.show()

