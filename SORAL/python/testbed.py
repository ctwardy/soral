#!/usr/bin/python

import array
import soral

print 'PySoral testbed'

areas=4
resources=1

area = soral.doubleArray(areas)
POA =  soral.doubleArray(areas)
ESW =  soral.doubleArray(areas)
speed =  soral.doubleArray(areas)

for i in range(0, areas):
    area[i] = [28, 30, 14, 12][i]
    POA[i] = [ 0.1935,  0.2581,  0.2903,  0.2581][i]
    ESW[i] = 1
    speed[i] = 1
    
availableHours = soral.doubleArray(resources)
availableHours[0] = 40

effectiveness = soral.Array2D(areas, resources)

for resourceIdx in range(0, resources):
    for areaIdx in range(0, areas):
        value = ESW[areaIdx]*speed[areaIdx]/area[areaIdx]
        effectiveness.set(areaIdx, resourceIdx, value)

availableHoursValArray = soral.toValArray(resources, availableHours)
areasValArray = soral.toValArray(areas, POA)

theAllocation = soral.CharnesCooper(resources, areas, effectiveness, availableHoursValArray, areasValArray)

del availableHoursValArray
del areasValArray
del theAllocation


