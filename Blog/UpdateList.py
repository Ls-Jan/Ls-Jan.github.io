

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

def SearchReadme(struct,sep='/'):#搜索所有Readme.md文件。struct为GetSourceStruct返回的数据
	stack=[[f'.',struct]]
	rst=[]
	while(stack):
		path,subStrcut=stack.pop()
		for name in subStrcut:
			if(type(subStrcut[name])==dict):#目录
				stack.append([f'{path}{sep}{name}',subStrcut[name]])
			elif(name.lower()=='readme.md'):#Readme文件
			# elif(os.path.splitext(name)[1]=='.md'):#*.md文件
				rst.append([f'{path}{sep}{name}',subStrcut])
	return rst

def GetLatestModifyTime(path,cache={}):#遍历目录，获取最新的修改时间
	latest=os.path.getmtime(path)
	if(path in cache):
		return cache[path]
	for root, dirs, files in os.walk(path):
		for name in files:
			mTime=os.path.getmtime(os.path.join(root,name))
			if(mTime>latest):
				latest=mTime
		for name in dirs:
			mTime=GetLatestModifyTime(os.path.join(root,name),cache)
			if(mTime>latest):
				latest=mTime
	cache[path]=latest
	return latest

if __name__ == '__main__':
	path='./'
	json_list='BlogList.json'

	#获取目录资源结构，并移除无关信息，只留下博客文件夹
	blogStruct=GetSourceStruct(path)
	removeLst=['__pycache__']
	for name in blogStruct.keys():
		if(blogStruct[name]==''):
			removeLst.append(name)
	for i in removeLst:
		blogStruct.pop(i)

	#获取博客信息并对其按照修改时间降序排序(自新到旧)
	cache={}
	blogList=[]
	for item in SearchReadme(blogStruct):
		name,struct=item
		path=os.path.split(name)[0]
		cTime=os.path.getctime(path)*1000#JS的时间刻是按毫秒的，乘1k补足(js那边的代码已经够乱了，尽量在这里处理好数据
		mTime=GetLatestModifyTime(path,cache)*1000
		blogList.append({'name':name,'cTime':cTime,'mTime':mTime,'struct':struct})
	blogList.sort(key=lambda item:item['mTime'],reverse=True)

	#JSON序列化并保存
	blogList=json.dumps(blogList,ensure_ascii=False,indent=4)
	with open(json_list,'w',encoding='utf-8') as f:
		f.write(blogList)
	# print(blogList)

	print(f'【{json_list}】  更新完毕\n')
	os.system('pause')




