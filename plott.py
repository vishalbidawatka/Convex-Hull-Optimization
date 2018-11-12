import matplotlib.pyplot as plt 

# x axis values 
f = open("inp.txt","r")
t = f.readlines()
x = []
y = []
print(f)
plot1 = plt.figure(1)
for i in range(1,len(t)):
    if(i%2 == 1 and t[i] != ' ' and len(t[i]) != 0):
        try:
            x.append(int(t[i].strip()))
        except:
            pass
    elif (t[i] != ' ' and len(t[i]) != 0):
        try:
            y.append(int(t[i].strip()))
        except:
            pass


print(x)
print(y)
plt.plot(x, y,  linestyle='dashed', linewidth = 0, 
		marker='.', markerfacecolor='blue', markersize=12) 

# setting x and y axis range 
# plt.ylim(min(x)-10,max(x)+10) 
# plt.xlim(min(y)-10,max(y)+10) 

# naming the x axis 
plt.xlabel('x - axis') 
# naming the y axis 
plt.ylabel('y - axis') 

# giving a title to my graph 
plt.title('Before Pruning') 

# function to show the plot 
mng = plt.get_current_fig_manager()
#mng.frame.Maximize(True)
plot1.show() 







plot2 = plt.figure(2)
plt.plot(x, y,  linestyle='dashed', linewidth = 0, 
		marker='.', markerfacecolor='blue', markersize=12 ) 

# setting x and y axis range 
# plt.ylim(min(x)-10,max(x)+10) 
# plt.xlim(min(y)-10,max(y)+10) 
f2 = open("output.txt","r")
x1 = []
y1 = []
t2 = f2.readlines()
for i in range(0,len(t2)):
    if(i%2 == 0 and t2[i] != ' ' and len(t2[i]) != 0):
        try:
            x1.append(int(t2[i].strip()))
        except:
            pass
    elif (t2[i] != ' ' and len(t2[i]) != 0):
        try:
            y1.append(int(t2[i].strip()))
        except:
            pass
print(x1)
print(y1)
x1.append(x1[0])
y1.append(y1[0])
plt.plot(x1, y1, color='green', linestyle='solid', linewidth = 1, 
		marker='.', markerfacecolor='red', markersize=12) 

# naming the x axis 
plt.xlabel('x - axis') 
# naming the y axis 
plt.ylabel('y - axis') 

# giving a title to my graph 
plt.title('Pruning boundary region') 

# function to show the plot 
mng = plt.get_current_fig_manager()
# mng.frame.Maximize(True)
plot2.show() 





##########################################################################################

f = open("afterpruning.txt","r")
t = f.readlines()
x = []
y = []
print(f)
plot3 = plt.figure(3)
for i in range(0,len(t)):
    if(i%2 == 0 and t[i] != ' ' and len(t[i]) != 0):
        try:
            x.append(int(t[i].strip()))
        except:
            pass
    elif (t[i] != ' ' and len(t[i]) != 0):
        try:
            y.append(int(t[i].strip()))
        except:
            pass


print(x)
print(y)
plt.plot(x, y,  linestyle='dashed', linewidth = 0, 
		marker='.', markerfacecolor='blue', markersize=12) 

# setting x and y axis range 
# plt.ylim(min(x)-10,max(x)+10) 
# plt.xlim(min(y)-10,max(y)+10) 

# naming the x axis 
plt.xlabel('x - axis') 
# naming the y axis 
plt.ylabel('y - axis') 

# giving a title to my graph 
plt.title('Points to be Considered') 

# function to show the plot 
mng = plt.get_current_fig_manager()
#mng.frame.Maximize(True)
plot3.show() 




########################################################################################################

plot4 = plt.figure(4)


# setting x and y axis range 
# plt.ylim(min(x)-10,max(x)+10) 
# plt.xlim(min(y)-10,max(y)+10) 
f2 = open("finalresult.txt","r")
x1 = []
y1 = []
t2 = f2.readlines()
for i in range(0,len(t2)):
    if(i%2 == 0 and t2[i] != ' ' and len(t2[i]) != 0):
        try:
            x1.append(int(t2[i].strip()))
        except:
            pass
    elif (t2[i] != ' ' and len(t2[i]) != 0):
        try:
            y1.append(int(t2[i].strip()))
        except:
            pass
print(x1)
print(y1)
x1.append(x1[0])
y1.append(y1[0])
plt.plot(x1, y1, color='green', linestyle='solid', linewidth = 0, 
		marker='.', markerfacecolor='red', markersize=12) 

# naming the x axis 
plt.xlabel('x - axis') 
# naming the y axis 
plt.ylabel('y - axis') 

# giving a title to my graph 
plt.title('Convex Hull Points') 

# function to show the plot 
mng = plt.get_current_fig_manager()
# mng.frame.Maximize(True)
plot4.show() 







































input()
# f.close()

# f = open("output.txt","r")

