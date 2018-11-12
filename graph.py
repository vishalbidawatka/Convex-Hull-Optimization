import matplotlib.pyplot as plt
def listutilityfuntion(filename):

    f = open(filename)
    k = f.readlines()
    return list(map(int,k))

# x axis values
x1 = [10,100,500,1000,2000,4000,8000,16000,32000,64000,128000,256000,512000,1024000]
# corresponding y axis values
y1 = listutilityfuntion("quickhullresults_pruned.txt")

#y2 = listutilityfuntion("jarvisresults.txt")

y2 = listutilityfuntion("quickhullresults.txt")

# plotting the points
plt.plot(x1, y1, label="Quickhull  with pruning", color='green', linestyle='solid', linewidth=2,
         marker='o', markerfacecolor='blue', markersize=5)
plt.plot(x1, y2, label="Quickhull  without pruning", color='red', linestyle='solid', linewidth=2,
         marker='o', markerfacecolor='yellow', markersize=5)
# plt.plot(x1, y3, label="Graham Scan", color='blue', linestyle='solid', linewidth=2,
#          marker='o', markerfacecolor='green', markersize=5)

plt.legend()    
# naming the x axis
plt.xlabel('Number of Points')
# naming the y axis
plt.ylabel('Time(in micro seconds)')

# giving a title to my graph
plt.title('Quickhull with pruning Vs without pruning')

# function to show the plot
plt.show()
