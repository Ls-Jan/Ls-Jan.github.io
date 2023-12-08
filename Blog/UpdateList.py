

import json
import os
from datetime import datetime as dt

def GetSourceStruct(path):#获取资源结构
	struct={path:{}}
	cache={path:struct[path]}
	for root, dirs, files in os.walk(path):
		data=cache[root]
		for name in dirs:
			data[name]={}
			cache[os.path.join(root,name)]=data[name]
		for name in files:
			data[name]=''
	return struct[path]

def GetLatestModifyTime(path):#遍历目录，获取最新的修改时间
	latest=os.path.getmtime(path)
	for root, dirs, files in os.walk(path):
		for name in files:
			mTime=os.path.getmtime(os.path.join(root,name))
			if(mTime>latest):
				latest=mTime
	return latest

if __name__ == '__main__':
	path='./'
	json_list='BlogList.json'
	json_struct='BlogStruct.json'

	blogStruct=GetSourceStruct(path)
	for i in ['__pycache__',json_list,json_struct,os.path.split(__file__)[1]]:#移除这些信息，只留下博客文件夹
		if(i in blogStruct):
			blogStruct.pop(i)

	blogList=[{'name':name,'cTime':os.path.getctime(os.path.join(path,name)),'mTime':GetLatestModifyTime(name)} for name in blogStruct ]
	blogList.sort(key=lambda item:item['mTime'],reverse=True)

	blogStruct=json.dumps(blogStruct,ensure_ascii=False,indent=4)
	blogList=json.dumps(blogList,ensure_ascii=False,indent=4)
	# print(blogStruct)
	# print(blogList)
	with open(json_list,'w',encoding='utf-8') as f:
		f.write(blogList)
	with open(json_struct,'w',encoding='utf-8') as f:
		f.write(blogStruct)

	print(f'【{json_list}】  【{json_struct}】  更新完毕\n')
	os.system('pause')
