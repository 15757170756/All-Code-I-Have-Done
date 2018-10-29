import pandas as pd
import time
import math
import requests
import matplotlib.pyplot as plt
from wordcloud import WordCloud
import jieba

# 获取请求结果
# kind 搜索关键字
# page 页码 默认是1
def get_json(kind, page=1,):
    # post请求参数
    param = {
        'first': 'true',
        'pn': page,
        'kd': kind
    }
    header = {
        'Host': 'www.lagou.com',
        'Referer': 'https://www.lagou.com/jobs/list_python?labelWords=&fromSearch=true&suginput=',
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36'
    }
    # 设置代理
    proxies = [
        {'http': '140.143.96.216:80', 'https': '140.143.96.216:80'},
        {'http': '119.27.177.169:80', 'https': '119.27.177.169:80'},
        {'http': '221.7.255.168:8080', 'https': '221.7.255.168:8080'}
    ]
    # 请求的url
    url = 'https://www.lagou.com/jobs/positionAjax.json?px=default&city=%E5%8C%97%E4%BA%AC&needAddtionalResult=false'
    # 使用代理访问
    # response = requests.post(url, headers=header, data=param, proxies=random.choices(proxies))
    response = requests.post(url, headers=header, data=param, proxies=proxies)
    response.encoding = 'utf-8'
    if response.status_code == 200:
        response = response.json()
        # 请求响应中的positionResult 包括查询总数 以及该页的招聘信息(公司名、地址、薪资、福利待遇等...)
        return response['content']['positionResult']
    return None

if __name__ == '__main__':
    # 默认先查询第一页的数据
    kind = 'python'
    # 请求一次 获取总条数
    position_result = get_json(kind=kind)
    # 总条数
    total = position_result['totalCount']
    print('{}开发职位，招聘信息总共{}条.....'.format(kind, total))
    # 每页15条 向上取整 算出总页数
    page_total = math.ceil(total/15)

    # 所有查询结果
    search_job_result = []
    #for i in range(1, total + 1)
    # 为了节约效率 只爬去前100页的数据
    for i in range(1, 100):
        position_result = get_json(kind=kind, page= i)
        # 每次抓取完成后,暂停一会,防止被服务器拉黑
        time.sleep(15)
        # 当前页的招聘信息
        page_python_job = []
        for j in position_result['result']:
            python_job = []
            # 公司全名
            python_job.append(j['companyFullName'])
            # 公司简称
            python_job.append(j['companyShortName'])
            # 公司规模
            python_job.append(j['companySize'])
            # 融资
            python_job.append(j['financeStage'])
            # 所属区域
            python_job.append(j['district'])
            # 职称
            python_job.append(j['positionName'])
            # 要求工作年限
            python_job.append(j['workYear'])
            # 招聘学历
            python_job.append(j['education'])
            # 薪资范围
            python_job.append(j['salary'])
            # 福利待遇
            python_job.append(j['positionAdvantage'])

            page_python_job.append(python_job)

        # 放入所有的列表中
        search_job_result += page_python_job
        print('第{}页数据爬取完毕, 目前职位总数:{}'.format(i, len(search_job_result)))
        # 每次抓取完成后,暂停一会,防止被服务器拉黑
        time.sleep(15)

    # 将总数据转化为data frame再输出
    df = pd.DataFrame(data=search_job_result,
                      columns=['公司全名', '公司简称', '公司规模', '融资阶段', '区域', '职位名称', '工作经验', '学历要求', '工资', '职位福利'])
    df.to_csv('lagou.csv', index=False, encoding='utf-8_sig')


    # 读取数据
    df = pd.read_csv('lagou.csv', encoding='utf-8')
    # 数据清洗,剔除实习岗位
    df.drop(df[df['职位名称'].str.contains('实习')].index, inplace=True)
    # print(df.describe())
    # 由于CSV文件内的数据是字符串形式,先用正则表达式将字符串转化为列表,再取区间的均值
    pattern = 'd+'
    df['work_year'] = df['工作经验'].str.findall(pattern)
    # 数据处理后的工作年限
    avg_work_year = []
    # 工作年限
    for i in df['work_year']:
        # 如果工作经验为'不限'或'应届毕业生',那么匹配值为空,工作年限为0
        if len(i) == 0:
            avg_work_year.append(0)
            # 如果匹配值为一个数值,那么返回该数值
        elif len(i) == 1:
            avg_work_year.append(int(''.join(i)))
            # 如果匹配值为一个区间,那么取平均值
        else:
            num_list = [int(j) for j in i]
            avg_year = sum(num_list) / 2
            avg_work_year.append(avg_year)
    df['工作经验'] = avg_work_year

    # 将字符串转化为列表,再取区间的前25%，比较贴近现实
    df['salary'] = df['工资'].str.findall(pattern)
    # 月薪
    avg_salary = []
    for k in df['salary']:
        int_list = [int(n) for n in k]
        avg_wage = int_list[0] + (int_list[1] - int_list[0]) / 4
        avg_salary.append(avg_wage)
    df['月工资'] = avg_salary

    # 将学历不限的职位要求认定为最低学历:大专
    df['学历要求'] = df['学历要求'].replace('不限', '大专')

    # 绘制频率直方图并保存
    plt.hist(df['月工资'])
    plt.xlabel('工资 (千元)')
    plt.ylabel('频数')
    plt.title("工资直方图")
    plt.savefig('薪资.jpg')
    plt.show()


    # 绘制饼图并保存
    count = df['区域'].value_counts()
    plt.pie(count, labels=count.keys(), labeldistance=1.4, autopct='%2.1f%%')
    plt.axis('equal')  # 使饼图为正圆形
    plt.legend(loc='upper left', bbox_to_anchor=(-0.1, 1))
    plt.savefig('pie_chart.jpg')
    plt.show()


    # {'本科': 1304, '大专': 94, '硕士': 57, '博士': 1}
    dict = {}
    for i in df['学历要求']:
        if i not in dict.keys():
            dict[i] = 0
        else:
            dict[i] += 1
    index = list(dict.keys())
    print(index)
    num = []
    for i in index:
        num.append(dict[i])
    print(num)
    plt.bar(left=index, height=num, width=0.5)
    plt.show()


    # 绘制词云,将职位福利中的字符串汇总
    text = ''
    for line in df['职位福利']:
        text += line
        # 使用jieba模块将字符串分割为单词列表
    cut_text = ' '.join(jieba.cut(text))
    # color_mask = imread('cloud.jpg')  #设置背景图
    cloud = WordCloud(
        background_color='white',
        # 对中文操作必须指明字体
        font_path='yahei.ttf',
        # mask = color_mask,
        max_words=1000,
        max_font_size=100
    ).generate(cut_text)

    # 保存词云图片
    cloud.to_file('word_cloud.jpg')
    plt.imshow(cloud)
    plt.axis('off')
    plt.show()