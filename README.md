# SORAL

SORAL is the [SAR*Bayes*](http://sarbayes.org) Optimal Resource Allocation Library, 
a programmer's API of optimization algorithms tailored to Search And Rescue (SAR). 
  * Written in C++ (fast)
  * Python & Node wrappers
  * Charnes-Cooper algorithm for single resources
  * Washburn's _JOTA_ algorithm for multiple resources
    * _JOTA_ algorithm also in MATLAB
    * (MATLAB developed first, from _JOTA_ paper and FORTRAN code)
    * Many thanks to Prof. Alan Washburn
  * Manual (user-specified) "algorithm"
  * Clean object-oriented structure allows plug-in algorithms
  
SORAL is an abstract _effort allocator_: it determines how _much_ 
effort to apply to each region, but not _how_ to apply it. Those
tactics or path planning are left to the calling program, or the
humans. However, SORAL is fast, and can be used to provide a good
starting point, or test variations.

#### End-User Perspective
SORAL is a black box with functions to best allocate a set of SAR 
resources across areas, where "best" means "find the lost person fastest". 
Being open-source means the whole SAR and operations-research
community can potentially review and improve the code. 

Effort allocation requires an initial probability map for the lost person,
and three key kinds of information about each search resource type:
  * Travel Speed (can vary by region)
  * Hours Available (total)
  * Sweep Width (can vary by region)
The first two should be known to search planners, or quickly estimated.
Sweep Width ideally has to be measured experimentally, and is
specific to a \<sensor, target, environment\> combination.  _However_,
after analyzing 20+ experiments, empirically it seems Sweep Width
can be estimated quite well from by applying a correction factor
(between 1.0 and 2.0) to the "average maximum detection range"
obtained from a "Northumbrian Rain Dance" or "AMDR" procedure. 
That fact opens up optimal allocation to practical use.

#### Programmer Perspective
The SORAL API is a simple, clean, modular collection of algorithms,
each of which is optimal in its own domain. By virtue of plugging
in to SORAL, each also provides important values for the end-user,
such as probability of detection, coverage, and others. Also:
* Tested
* Documented
* Open-source
* Etc.

# AGMSAR

AGMSAR is a text-based resource-allocation program that uses SORAL. 
Perhaps it should get its own repository that refers to SORAL.

# Status
* 2017-04: Cleaned code uploaded to GitHub
    * Code cleaned by Sarah George at Heartfelt Tech.
    * Using two snapshots from 200x, and Tom Russo's site [link]
    * Wrapped for Python and Node (using SWIG to wrap)
    * Need to update docs
* 201x: Tom Russo's site [link]
* 200x - 201x: Available on sarbayes.org
  - Self-hosted CVStrac 
  - CVSdude?
  - Google Code
  - Failed to migrate from Google Code
  - SARBayes hosting company vanished, with hosted copy
200x: Code Review and Release of v__
200x: Development

# License
 SORAL is free (<em>libre</em>) software available under the GNU
 General Public License (GPL). Unless you secure a separate
 license, this requires any software which uses SORAL to 
 also be GPL. In order to ensure that
 using SORAL will not adversely affect the licensing status of your
 own software, please see the the file COPYING for the full
 text of the GPL.

TODO: Create a LICENSE file, and update to state ownership & history. 
