function [p,T,w] = randsar(numAreas,numResources)
% RANDSAR   Generate random values for testing washburn.m
%    [p,T,w] = RANDSAR(numAreas,numResources);
%    Fills p with uniform probabilities.
%    Fills T with positive values (Lognormal(2.3,1)).
%    Fills w with positive values (Lognormal(1.6,1)).
%
%    You may then run 'washburn(p,T,w)'

p = random('Uniform',0,1,1,numAreas);
p = p/sum(p);

T = random('Lognormal',2.3,1,1,numResources);

w = random('Lognormal',1.6,1,numAreas,numResources);
