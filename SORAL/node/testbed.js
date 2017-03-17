console=require("console");
soral=require("./build/Release/soral");


function runTest() {
    var i;
    
    console.log( "NodeSoral test based on tom.cpp" );
    
    var areas=4;
    var resources=1;
    
    var area = new soral.doubleArray(areas);
    var POA =  new soral.doubleArray(areas);
    var ESW =  new soral.doubleArray(areas);
    var speed = new soral.doubleArray(areas);
    
    // Configure the arrays with some test values
    for (i = 0; i < areas; i++) {
        area.setitem(i, [28, 30, 14, 12][i]);
        POA.setitem(i,  [0.1935,  0.2581,  0.2903,  0.2581][i]);
        ESW.setitem(i, 1);
        speed.setitem(i, 1);
    }

    var availableHours = new soral.doubleArray(resources);
    availableHours.setitem(0, 40);
    
    var effectiveness = new soral.Array2D(areas, resources);
    
    for (var resourceIdx  = 0; resourceIdx < resources; resourceIdx++) {
        for (var areaIdx = 0; areaIdx < areas; areaIdx++) {
            var value = ESW.getitem(areaIdx) * speed.getitem(areaIdx) / area.getitem(areaIdx);
            effectiveness.set(areaIdx, resourceIdx, value);
            // console.log("Effectiveness["+areaIdx+","+resourceIdx+"] = "+value + " // " + effectiveness.get(areaIdx, resourceIdx));
        }
    }
    
    var theAllocation = soral.newCharnesCooper(resources, areas, effectiveness, availableHours, POA);
    
    console.log("The calculated allocation");
    printAssignments(theAllocation);
    
    console.log("PODs: ");
    for (i = 0; i < areas; i++) { 
        console.log("  " +i + ": " + theAllocation.getPOD(i));
    }

    console.log("Adjusted POAs: ");
    for (i = 0; i < areas; i++) { 
        console.log("  " +i + ": " + theAllocation.getNewPOC(i));
    }

    console.log("Segment POSs: ");
    for (i = 0; i < areas; i++) { 
        console.log("  " +i + ": " + theAllocation.getPOS(i));
    }

    console.log(" Cumulative POS: " + theAllocation.getTotalPOS());
    
    delete theAllocation
	
}


function printAssignments( theAllocation ) {
    activeItr = new soral.ActiveAreasIterator(theAllocation);
    
    // While there are still areas with assignments
    while ( !activeItr.atEnd() ) {
        areaIndex = activeItr.getCurrentActiveAreaNum();
        area = new soral.ActiveArea(areaIndex);

    	resItr = new soral.ResourceIterator(theAllocation, areaIndex);
    	
    	while ( !resItr.atEnd() ) {
            resAssign = resItr.getResourceAssignment();
            resIndex = resAssign.getResourceNum();
            time = resAssign.getTime();
            
            console.log("  Area: " + areaIndex + "  Resource: " + resIndex + "  Time: " + time);	  
            resItr.increment();
        }
    	activeItr.increment();
	}
}






runTest();

