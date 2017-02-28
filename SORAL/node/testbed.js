console=require("console");
soral=require("./build/Release/soral");

console.log( 'NodeSoral test based on tom.cpp' );

function runTest() {
    var areas=4;
    var resources=1;
    
    var area = soral.doubleArray(areas);
    var POA =  soral.doubleArray(areas);
    var ESW =  soral.doubleArray(areas);
    var speed =  soral.doubleArray(areas);
    
    // Configure the arrays with some test values
    for (var i = 0; i < areas; i++) {
        area[i] = [28, 30, 14, 12][i];
        POA[i] = [0.1935,  0.2581,  0.2903,  0.2581][i];
        ESW[i] = 1;
        speed[i] = 1;
    }

    var availableHours = soral.doubleArray(resources);
    availableHours[0] = 40;
    
    var effectiveness = soral.Array2D(areas, resources);
    
    for (var resourceIdx  = 0; resourceIdx < resources; resourceIdx++) {
        for (var areaIdx = 0; areaIdx < areas; areaIdx++) {
            var value = ESW[areaIdx]*speed[areaIdx]/area[areaIdx];
            effectiveness.set(areaIdx, resourceIdx, value);
        }
    }
    
    var theAllocation = soral.newCharnesCooper(resources, areas, effectiveness, availableHours, POA)
	
}


runTest();

