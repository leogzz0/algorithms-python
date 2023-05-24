#duck song
# input: the first line contains three integers x, y and z (1<=x,y,z <=10^5)- the number of grapes Andrew, Dimitry and Michal want to eat.
# the second line contains three integers a, b ,c (1<=a,b,c<=10^5) - the number of green, purple, and black grapes in the box
# output: if there is a grape distribution that allow everyone to be happy, print "YES", otherwise print "NO"

#with open('ej.txt', 'r') as f:
    #x, y, z = map(int, f.readline().split())
    #a, b, c = map(int, f.readline().split())

x, y, z = map(int, input().split())
a, b, c = map(int, input().split())

if a >= x and (a+b) >= (x+y) and (a+b+c) >= (x+y+z):
    print("YES")
else:
    print("NO")

