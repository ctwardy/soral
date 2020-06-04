#!/usr/bin/python

import soral

print('PySoral test based on tom.cpp')


def runTest():
    areas=4
    resources=1

    area = soral.doubleArray(areas)
    POA =  soral.doubleArray(areas)
    ESW =  soral.doubleArray(areas)
    speed =  soral.doubleArray(areas)

    # Configure the arrays with some test values
    for i in range(areas):
        area[i] = [28, 30, 14, 12][i]
        POA[i] = [0.1935,  0.2581,  0.2903,  0.2581][i]
        ESW[i] = 1
        speed[i] = 1

    availableHours = soral.doubleArray(resources)
    availableHours[0] = 40

    effectiveness = soral.Array2D(areas, resources)

    for resourceIdx in range(resources):
        for areaIdx in range(areas):
            value = ESW[areaIdx]*speed[areaIdx]/area[areaIdx]
            effectiveness.set(areaIdx, resourceIdx, value)
            # print "Effectiveness("+str(areaIdx)+","+str(resourceIdx)+" = "+str(value);


    theAllocation = soral.newCharnesCooper(resources, areas, effectiveness, availableHours, POA)

    print("The calculated allocation")
    printAssignments(theAllocation)

    print("PODs: ")
    for i in range(areas):
        print("  " +str(i) + ": " + str(theAllocation.getPOD(i)))

    print("Adjusted POAs: ")
    for i in range(areas):
        print("  " +str(i) + ": " + str(theAllocation.getNewPOC(i)))

    print("Segment POSs: ")
    for i in range(areas):
        print("  " +str(i) + ": " + str(theAllocation.getPOS(i)))

    print(" Cumulative POS: " + str(theAllocation.getTotalPOS()) )

    del theAllocation



def printAssignments( theAllocation ):
    activeItr = soral.ActiveAreasIterator(theAllocation)
    
    # While there are still areas with assignments
    while ( False == activeItr.atEnd() ):
        areaIndex = activeItr.getCurrentActiveAreaNum()
        area = soral.ActiveArea(areaIndex)

        resItr = soral.ResourceIterator(theAllocation, areaIndex)
    	
        while ( False == resItr.atEnd() ):
            resAssign = resItr.getResourceAssignment()
            resIndex = resAssign.getResourceNum()
            time = resAssign.getTime()
            
            print("  Area: " + str(areaIndex) + "  Resource: " + str(resIndex) + "  Time: " + str(time)	  )
            resItr.increment()
    
        activeItr.increment()


runTest()

