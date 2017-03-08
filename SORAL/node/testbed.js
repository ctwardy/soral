console=require("console");
soral=require("./build/Release/soral");

console.log( "NodeSoral test based on tom.cpp\n" );

function runTest() {
    var areas=4;
    var resources=1;
    
    var area = new soral.doubleArray(areas);
    var POA =  new soral.doubleArray(areas);
    var ESW =  new soral.doubleArray(areas);
    var speed =  new soral.doubleArray(areas);
    
    // Configure the arrays with some test values
    for (var i = 0; i < areas; i++) {
        area.setitem(i, [28, 30, 14, 12][i]);
        POA.setitem(i,  [0.1935,  0.2581,  0.2903,  0.2581][i]);
        ESW.setitem(i, 1);
        speed.setitem(i, 1);
    }

    var availableHours = new soral.doubleArray(resources);
    availableHours[0] = 40;
    
    var effectiveness = new soral.Array2D(areas, resources);
    
    for (var resourceIdx  = 0; resourceIdx < resources; resourceIdx++) {
        for (var areaIdx = 0; areaIdx < areas; areaIdx++) {
            var value = ESW[areaIdx] * speed[areaIdx] / area[areaIdx];
            effectiveness.set(areaIdx, resourceIdx, value);
            // console.log("Effectiveness("+areaIdx+","+resourceIdx+" = "+value);
        }
    }
    
    var theAllocation = soral.newCharnesCooper(resources, areas, effectiveness, availableHours, POA);
    printAssignments(theAllocation);
	
}


function printAssignments( theAllocation ) {
    activeItr = new soral.ActiveAreasIterator(theAllocation);
    
    console.log("activeItr.currentActiveAreaNum = " + activeItr.getCurrentActiveAreaNum() );
    // While there are still areas with assignments
    while ( !activeItr.atEnd() ) {
        console.log( "A\n");	  
        areaIndex = activeItr.getCurrentActiveAreaNum();
        area = new soral.ActiveArea(areaIndex);

    	resItr = new soral.ResourceIterator(theAllocation, areaIndex);
    	
    	while ( !resItr.atEnd() ) {
	        console.log( "B\n");	  
            resAssign = resItr.getResourceAssignment();
            resIndex = resAssign.getResourceNum();
            time = resAssign.getTime();
            
            console.log( "Area: " + areaIndex + "  Resource: " + resIndex + "  Time: " + time+"\n");	  
            resItr.increment();
        }
    	activeItr.increment();
	}
}






runTest();

