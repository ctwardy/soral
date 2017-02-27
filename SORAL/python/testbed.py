#!/usr/bin/python

import array
import soral

print 'PySoral testbed'


def runTest():
    areas=4
    resources=1
    
    area = soral.doubleArray(areas)
    POA =  soral.doubleArray(areas)
    ESW =  soral.doubleArray(areas)
    speed =  soral.doubleArray(areas)
    
    # Configure the arrays with some test values
    for i in range(0, areas):
        area[i] = [28, 30, 14, 12][i]
        POA[i] = [ 0.1935,  0.2581,  0.2903,  0.2581][i]
        ESW[i] = 1
        speed[i] = 1
        
    availableHours = soral.doubleArray(resources)
    availableHours[0] = 40
    #availableHours = [40]
    
    effectiveness = soral.Array2D(areas, resources)
    
    for resourceIdx in range(0, resources):
        for areaIdx in range(0, areas):
            value = ESW[areaIdx]*speed[areaIdx]/area[areaIdx]
            effectiveness.set(areaIdx, resourceIdx, value)
    
    theAllocation = soral.newCharnesCooper(resources, areas, effectiveness, availableHours, area)
    
    print "The calculated allocation\n";
    printAssignments(theAllocation);
    
    del theAllocation



def printAssignments( theAllocation ):
    activeItr = soral.ActiveAreasIterator(theAllocation)
    
    # While there are still areas with assignments
    while ( False == activeItr.atEnd() ):
        areaIndex = activeItr.getCurrentActiveAreaNum()
        area = soral.ActiveArea(areaIndex)
        #area = soral.ActiveArea(activeItr)
        #areaIndex = area.getActiveAreaNum()

    	resItr = soral.ResourceIterator(theAllocation, areaIndex)
    	
    	while ( False == resItr.atEnd() ):
            resAssign = resItr.getResourceAssignment()
            resIndex = resAssign.getResourceNum()
            time = resAssign.getTime()
            
            print "  Area: " + str(areaIndex) + "  Resource: " + str(resIndex) + "  Time: " + str(time) + "\n"		  
            resItr.increment()
    
    	activeItr.increment()





runTest()

