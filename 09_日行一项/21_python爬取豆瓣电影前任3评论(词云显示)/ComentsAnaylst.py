# -*- coding: utf-8 -*-
# @Time    : 2018/4/25 11:15
# @File    : commentsAnaylst.py（再见前任3的影评f词云）

import matplotlib.pyplot as plt
from PIL import Image
from wordcloud import WordCloud
import jieba
import numpy as np
#读取txt格式的文本内容
text_from_file_with_apath = open('douban.txt','rb').read()

#使用jieba进行分词，并对分词的结果以空格隔开
wordlist_after_jieba = jieba.cut(text_from_file_with_apath, cut_all = True)
wl_space_split = " ".join(wordlist_after_jieba)

#对分词后的文本生成词云
# my_wordcloud = WordCloud().generate(wl_space_split)

font = r'C:\Windows\Fonts\simfang.ttf'
mask = np.array(Image.open('ciyun.jpg'))
wc = WordCloud(mask=mask,max_words=3000,collocations=False, font_path=font, width=5800, height=2400, margin=10,background_color='black').generate(wl_space_split)
default_colors = wc.to_array()
plt.title("QR 3")
plt.imshow(wc)
plt.axis("off")
plt.savefig("ciyun.png")
plt.show()