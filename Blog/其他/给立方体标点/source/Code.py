

import matplotlib.pyplot as plt


def NumConvert(num:int,n:int,*,symbol:list=[hex(i)[2:].upper() for i in range(36)],returnList:bool=False):
	'''
		进制转换，将十进制数转为指定进制并作为字符串返回。
		是int的逆转换，int可以将字串返回对应十进制数，不建议超过36进制，超过的话不仅得指定symbol而且之后也无法通过int转回十进制。
		可以指定symbol符号表，只不过不是很建议对其进行更改。
		例如NumConvert(-233,16)，将返回'-E9'

		如果returnList为真，则返回元组，同时不保留符号位，即num为负数时返回的结果与abs(num)是相同的。
		例如NumConvert(147,60,returnTuple=True)，将返回[2,27]
	'''
	sign='' if num>=0 else '-'
	num=abs(num)
	lst=[]
	if(num==0):
		lst.append(0)
	while(num>0):
		lst.append(num%n)
		num//=n
	lst.reverse()
	lst=lst if len(lst) else [0]
	if(returnList):
		return lst
	if(n>len(symbol)):
		raise Exception('Error:args n is larger than the length of symbol!')
	return sign+''.join(map(lambda pst:symbol[pst],lst))


fig=plt.figure()
fig.subplots_adjust(0,0,1,1,0,0)

for n in range(3):
	n+=1
	canvas = fig.add_subplot(1,3,n,projection='3d')
	canvas.axis('off')
	canvas.invert_xaxis()
	canvas.invert_zaxis()

	nodes=[*range(1,1+pow(3,n))]
	nodesPos=[(0,0,*NumConvert(node-1,3,returnList=True))[-3:] if node>0 else (1,-1,1) for node in nodes]
	nodesPos=[tuple(reversed(pos)) for pos in nodesPos]
	for i in range(len(nodes)):
		node=nodes[i]
		pos=nodesPos[i]
		# canvas.text(*pos,str(node))#使用十进制编号
		canvas.text(*pos,NumConvert(node-1,3).zfill(n))#使用三进制编号
		if(len(list(filter(lambda i:pos[i]%2,range(3))))):
			continue
		for i in range(3):
			pos2=list(pos)
			pos2[i]+=2
			pos2=tuple(pos2)
			if(pos2 in nodesPos):
				canvas.plot(*[[pos[i],pos2[i]] for i in range(3)])
plt.show()
exit()


