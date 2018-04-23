# -*- coding:utf-8 -*-
import numpy as np
import csv
import re
import matplotlib.pyplot as plt
plt.rcParams['font.sans-serif'] = ['SimHei']


if __name__ == "__main__":
    csv_reader = csv.reader(open('lianjia_re_v4.csv'))
    content = []
    for row in csv_reader:
        content.append(row)

    all_region = []
    regions = ['徐汇', '静安', '浦东', '杨浦', '闵行', '长宁', '宝山', '青浦',
               '金山', '普陀','松江', '嘉定', '闸北', '虹口', '奉贤',
               '崇明', '黄浦', '上海周边']
    tmp = []
    region_statistics = []
    region_statistics_dict = {}
    for item in content:
        all_region.append(item[5])

    for region in regions:
        if all_region.count(region):
            region_statistics.append(all_region.count(region))
            region_statistics_dict[region] = all_region.count(region)
            tmp.append(region)
    regions = tmp

    fangzu = {}
    for region in regions:
        fangzu[region] = 0
    for item in content:
        fangzu[item[5]] += int(item[-3])
    fangzu_average = []
    for region in regions:
        fangzu_average.append(fangzu[region]/region_statistics_dict[region])

    area = {}
    for region in regions:
        area[region] = 0
    for item in content:
        tmp = item[4]
        tmp = re.sub(r'[^\x00-\x7f]', '', tmp)
        area[item[5]] += int(tmp)
    area_average = []
    for region in regions:
        area_average.append(area[region] / region_statistics_dict[region])
    for i in range(len(area_average)):
        area_average[i] = fangzu_average[i]/area_average[i]

    # 地区分布
    a = [i for i in range(1, len(regions) + 1)]
    plt.bar(a, region_statistics, 0.4, color="blue")
    xlocations = np.array(range(1, len(regions) + 1))
    plt.xticks(xlocations, regions, rotation=60)
    plt.ylabel("房屋数量")
    plt.xlabel("地区")
    plt.title("上海各区租房数量")
    for a, b in zip(a, region_statistics):
        plt.text(a, b, '%.0f' % b, ha='center', va='bottom', fontsize=7)
    plt.savefig("上海各区租房数量.jpg", dpi=300)
    plt.close()

    # 各区房租情况
    a = [i for i in range(1, len(regions) + 1)]
    plt.bar(a, fangzu_average, 0.4, color="blue")
    xlocations = np.array(range(1, len(regions) + 1))
    plt.xticks(xlocations, regions, rotation=60)
    plt.ylabel("月租 元/月")
    plt.xlabel("地区")
    plt.title("上海各区租房平均月租")
    for a, b in zip(a, fangzu_average):
        plt.text(a, b, '%.0f' % b, ha='center', va='bottom', fontsize=7)
    plt.savefig("上海各区租房房租信息.jpg", dpi=300)
    plt.close()

    # 各区每平米平均月租
    a = [i for i in range(1, len(regions) + 1)]
    plt.bar(a, area_average, 0.4, color="blue")
    xlocations = np.array(range(1, len(regions) + 1))
    plt.xticks(xlocations, regions, rotation=60)
    plt.ylabel("月租 元/月/平米")
    plt.xlabel("地区")
    plt.title("上海各区租房每平米平均月租")
    for a, b in zip(a, area_average):
        plt.text(a, b, '%.0f' % b, ha='center', va='bottom', fontsize=7)
    plt.savefig("上海各区租房每平米房租信息.jpg", dpi=300)
    plt.close()