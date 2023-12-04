

import json
import os


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


if __name__ == '__main__':
	path='./'
	file_json='BlogList.json'

	struct=GetSourceStruct(path)
	for i in ['__pycache__',file_json,os.path.split(__file__)[1]]:#移除这些信息，只留下博客文件夹
		struct.pop(i)

	data=json.dumps(struct,ensure_ascii=False,indent=4)
	# print(data)
	with open('BlogList.json','w',encoding='utf-8') as f:
		f.write(data)

	print(f'{file_json} 更新完毕\n')
	os.system('pause')
