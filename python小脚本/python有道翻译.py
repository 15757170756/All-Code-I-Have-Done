import urllib.request
import urllib.parse
import json
import time
while 1:
    content = input("请输入你要翻译的内容(按q键退出)：")
    if content=='q':
        break
    val="http://fanyi.youdao.com/translate?smartresult=dict&smartresult=rule"
    data={}
    data['action']='FY_BY_REALTIME'
    data['client']='fanyideskweb'
    data['doctype']='json'
    data['from']='AUTO'
    data['i']=content
    data['keyfrom']='fanyi.web'
    data['salt']='1525252417040'
    data['sign']='4632e1f3f77f0c44a487ab5c674bf964'
    data['smartresult']='dict'
    data['to']='AUTO'
    data['typoResult']='false'
    data['version']='2.1'
    data=urllib.parse.urlencode(data).encode('utf-8')
    url=urllib.request.urlopen(val,data)
    html = url.read().decode('utf-8')
    a = json.loads(html)
    print("翻译结果：%s" % (a['translateResult'][0][0]['tgt']))
    time.sleep(1)