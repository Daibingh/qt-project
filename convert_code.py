import os
import os.path
import sys

def convert_code(dir1, dir2, code_in="gbk", code_out="utf-8"):
	file_list = os.listdir(dir1)
	if not os.path.exists(dir2):
		os.makedirs(dir2)
	for file in file_list:
		with open(dir1 + '/' + file, mode="r", encoding=code_in) as f:
			content = f.read()
			with open(dir2 + '/' + file, "mode=w", encoding=code_out):
				f.write(content)

if __name__ == '__main__':
	if len(sys.argv)==5:
		convert_code(sys.argv[1], sys.argv[2], sys.argv[3],sys.argv[4])
	elif len(sys.argv)==3:
		print("hhhh")
		convert_code(sys.argv[1], sys.argv[2])