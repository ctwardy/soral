#!/usr/bin/python

import soral
from collections import defaultdict

"""Updated to hold many test cases."""

class Region():
    """A region has POA, geometric area, and optionally a polygon.
    :param id: string or int identifier, used for hashing esp. in Resources
    :param POA: nonnegative float, probability target is in region
    :param area: positive float, geometric area of region [1]
    :param polygon: sequence of tuples; unused here [None]
    :param pden: positive float, calculated

    Note that "probabilities" are relative, so can be > 1.
    There are situations where this is even preferable.

    """
    def __init__(self, id, POA, area=1, polygon=None):
        assert POA >= 0
        assert area > 0
        self.id = id
        self.POA = POA
        self.area = area
        self.pden = 1.*POA / area

class Resource():
    """SAR resource. Resources have W and speed.
    :param id: - string or int identifier, used in hashing
    :param hours: - hours available this period, nonnegative float
    W & speed have both singular & plural forms; all default to None:
    If the plural forms are None, the singulars are used to fill them.
    If the singulars are also None, values of 1 are used. 
      :param W: nonneg float - the sweepwidth, assumed same for all regions
      :param Ws: dict {region_id: W} of sweepwidths, one per region
      :param speed: +ive float - search speed, assumed same for all regions
      :param speeds: dict {region_id: speed} of speeds, one per region

    """
    def __init__(self, id, hours, W=None, Ws=None, speed=None, speeds=None):
        self.id = id
        assert hours >= 0
        self.hours = hours
        self.set_Ws(W, Ws)
        self.set_speeds(speed, speeds)

    def set_Ws(self, W, Ws):
        """Ensure self.Ws is well-defined."""
        if Ws:
            assert isinstance(Ws, defaultdict)
            assert all(Ws.values() >= 0)
            self.Ws = Ws
        elif W:
            assert W >= 0
            self.Ws = defaultdict(lambda W=W: W)
        else:
            self.Ws = defaultdict(lambda: 1)

    def set_speeds(self, speed, speeds):
        """Run after set_Ws. Ensure self.speeds is well-defined."""
        if speeds:
            assert all(speeds.values() > 0)
            assert all(speeds.keys() in self.Ws)
            self.speeds = speeds
        elif speed:
            assert speed > 0
            self.speeds = defaultdict(lambda speed=speed: speed)
        else:
            self.speeds = defaultdict(lambda: 1)


class TestCase():
    """TestCase has regions and resources.
    :param regions: sequence of Region
    :param resources: sequence of Resource

    """
    def __init__(self, regions, resources):
        for region in regions:
            assert(isinstance(region, Region)) # assert(type(region) == Region)
        for resource in resources:
            assert(isinstance(resource, Resource)) # assert(type(resource) == Resource)

        self.regions = regions
        self.resources = resources
        # self.hours = hours # hours are part of Resource not TestCase
        self.num_regions = len(regions)
        self.num_resources = len(resources)
        self.soral_init()

    def soral_init(self):
        """Split from objects to SORAL-style arrays to prepare for calling.
        
        """
        # TODO: use DataFrames to read the dicts?
        N_reg, N_rsrcs = self.num_regions, self.num_resources
        self._areas = soral.doubleArray(N_reg)
        self._POAs = soral.doubleArray(N_reg)
        self._hours = soral.doubleArray(N_rsrcs)
        self._Ws = soral.doubleArray(N_reg)
        self._speeds = soral.Array2D(N_reg, N_rsrcs)
        self._effectiveness = soral.Array2D(N_reg, N_rsrcs)

        # Split the regions in to areas & POAs
        for i in range(self.num_regions):
            region = self.regions[i]
            self._areas[i] = region.area
            self._POAs[i] = region.POA

        # Split the resources
        for i in range(N_rsrcs):
            resource = self.resources[i]
            self._hours[i] = resource.hours
            # In general, speeds & effectiveness are 2D
            for j in range(N_reg):
                region = self.regions[j]
                reg_id = region.id
                print("Reg_id: ")
                print(reg_id)
                print("resource.Ws[1]:")
                print(resource.Ws[1])
                print("resource.speeds[1]:")
                print(resource.speeds[1])
                W, v = resource.Ws[reg_id], resource.speeds[reg_id]
                self._speeds.set(j, i, v)
                self._effectiveness.set(j, i, W * v / region.area)

        print('Done with init.')

    def _charnes_cooper(self):
        """Create a Charnes-Cooper allocation.
        Assumes soral_init() has been run.
        If >1 resources, just takes the first.
        
        """
        # TODO: pick best resource
        CC = soral.newCharnesCooper
        resource = self.resources[0]
        effect = self._effectiveness[0] # actually need to use iterator, right?
        theAllocation = CC(self.num_resources,
                           self.num_areas,
                           self._effectiveness,
                           self._hours,
                           self._POAs)
        # TODO: unpack theAllocation
        return theAllocation

    def _washburn(self):
        Wash = soral.Washburn(self.num_resources,
                              self.num_areas,
                              self._effectiveness,
                              self._hours,
                              self._POAs)
        return Wash

    def allocate(self):
        if self.num_resources > 1:
            ans = self._washburn()
        else:
            ans = self._charnes_cooper()
        self.allocation = ans
        self.POD = np.array([ans.getPOD(i) for i in range(self.num_regions)])
        self.POCnew = np.array([ans.getNewPOC(i) for i in range(self.num_regions)])
        self.POS = np.array([ans.getPOS(i) for i in range(self.num_regions)])
    
    def getTotalPOS(self):
        return self.allocation.getTotalPOS()

    def reset(self):
        del self.allocation, self.POD, self.POS, self.POCnew, self.TotalPOS

    def __repr__(self):
        # TODO: Use DataFrame for aligned printing?
        print("TotalPOS: %7.2f" % self.allocation.getTotalPOS())
        print("PODs:\n----\n", self.POD)
        print("POCnew:\n-------\n", self.POCnew)
        print("POS:\n----\n", self.POS)


    def printAssignments(self):
        activeItr = soral.ActiveAreasIterator(self.allocation)

        # While there are still areas with assignments
        while not activeItr.atEnd():
            areaIndex = activeItr.getCurrentActiveAreaNum()
            area = soral.ActiveArea(areaIndex)
            #area = soral.ActiveArea(activeItr)
            #areaIndex = area.getActiveAreaNum()
            resItr = soral.ResourceIterator(theAllocation, areaIndex)
            while not resItr.atEnd():
                resAssign = resItr.getResourceAssignment()
                resIndex = resAssign.getResourceNum()
                time = resAssign.getTime()
                print("  Area: %d, Resource: %d, Time: %5.2f" % (areaIndex, resIndex, time) )
                resItr.increment()

            activeItr.increment()

######################   
# Cases
######################

def case_0():
    """1 area, 1 resource"""
    
    regions = [Region(id=1, POA=4)]
    resources = [Resource(id='A', W=4, speed=1, hours=0.05)]
    answer = 0.05
    case = TestCase(regions, resources)
    print(case)
    np.testing.assert_allclose(case._charnes_cooper(), answer)
    np.testing.assert_allclose(case._washburn(), answer)
    
def case_1():
    """4 areas, 1 resource"""
    
    regions = [Region(id=i, POA=p) for i, p in enumerate([8, 4, 1, 2])]
    resources = [Resource(id='A', Ws={'0':1, '1':4, '2':12, '3':8}, hours=0.05)]
    answer = np.array([0, 0.033333, 0, 0.01666667])

    case = TestCase(regions, resources)
    assert case._charnes_cooper() == answer
    assert case._washburn() == answer
    print(case)
    np.testing.assert_allclose(case._charnes_cooper(), answer)
    np.testing.assert_allclose(case._washburn(), answer)

    
def case_7():
    """2 areas, 2 resources"""
    
    regions = [Region(id=i, POA=p) for i, p in enumerate([0.5, 0.5])]
    resources = [Resource(id='A', Ws={'0':0.1, '1':0.05}, hours=16.1),
                 Resource(id='B', Ws={'0':0.02, '1':0.005}, hours=13.9)]
    answer = np.array([[10.30365, 13.9],
                       [5.79635, 0]])

    case = TestCase(regions, resources)
    print(case)
    np.testing.assert_allclose(case.allocate(), answer)

def case_tom():
    regions = [Region(id=1, POA=.1935, area=28),
               Region(id=2, POA=.2581, area=30),
               Region(id=3, POA=.2903, area=14),
               Region(id=4, POA=.2581, area=12)]
    resources = [Resource(id='A', W=1, speed=1, hours=40)]
    case = TestCase(regions, resources)
    #assert case._charnes_cooper() == answer
    #assert case._washburn() == answer
    print(case_tom)

    
if __name__ == '__main__':
    # case_11()
    #case_41()
    case_0()
    case_1()
    case_tom()

