


class A:
	def __init__(self,isPublic=False):
		if(isPublic):
			self.Print("aaa")
			# A.Print(self,"aaa")#要通过这种方式才能正确调用到
		else:
			self.__Print("aaa")
	def __Print(self,val):
		print(f">>>[PRIVATE]A-{val}")
	def Print(self,val):
		print(f">>>[PUBLIC]A-{val}")

class B(A):
	def __init__(self,isPublic=False):
		super().__init__(isPublic)
		if(isPublic):
			self.Print("bbb")
		else:
			self.__Print("bbb")
	def __Print(self,val):
		print(f">>>[PRIVATE]B-{val}")
	def Print(self,val):
		print(f">>>[PUBLIC]B-{val}")

if __name__=='__main__':
	print("it's Python")
	for flag in [False,True]:
		print(f'\nisPublic={flag}')
		B(isPublic=flag)





