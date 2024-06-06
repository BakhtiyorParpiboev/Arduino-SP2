digit = [0,1,2,3,4,5,6,7,8,9,10]
wirte = int(input("write any number: (0~9)"))
write = str(wirte)
shout_flag = False
for i in str(write):
    if i == '3' or i == '6' or i == '9':
        shout_flag = True
        break
if shout_flag:
    print("shout: meow-meow")
else:
    print("survival")

