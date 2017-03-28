from pprint import pprint

dataFile  = open("car3d.txt")

allData = dataFile.read().split("--")

vertexData = [i for i in allData[0].split('\r\n') if i]
edgeData = [i for i in allData[1].split('\r\n') if i]

vertexes = []
edges = []

# parse out vertexes
for i in vertexData:
	k = i.split()
	if k:
		vertexName, x, y = k
		x = 500 - float(x)
		y = 238 - float(y)
	vertexes.append((vertexName, x, y))

print "Vertexes"
pprint(vertexes)


# parse out Edges
for i in edgeData:
	k = i.split()
	if k:
		v1, v2 = k
	edges.append((v1, v2))

print "Edges"
pprint(edges)


## change this to appropriate size
extrusionLength = 366

print 
print 
print 

print "float car_vertexes[][3] = {"
for m, i in enumerate(vertexes):
	print "{ ",i[1], ',', i[2], ', 0},  //', m

for m, i in enumerate(vertexes):
	print "{ ",i[1], ',', i[2], ', ',extrusionLength ,'},  //', m+len(vertexes)

print '''{0,0,0}

};'''


print "int car_edges[][2] = {"
for m, i in enumerate(edges):
	index1 = [t[0] for t in vertexes].index(i[0])
	index2 = [t[0] for t in vertexes].index(i[1])
 
	print "{ ",index1, ',', index2, '},  //', m


print '''{0,0}

};'''

