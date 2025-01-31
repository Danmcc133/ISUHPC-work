# -*- coding: utf-8 -*-
"""
Created on Fri Jan 24 20:13:04 2025

@author: danie
"""

import math

def sqrt(x,n,epsilon):
    if x == 0.0:
        return 0
    if x < 0.0:
        print("ERROR") # We aren't interested in complex values at the moment
        return -1.0
    if x > 0.0:
        s=1.0
        for k in range(n):
            s_old = s
            s=0.5*(s+x/s) # This is Newton's method apllied to f(s) = s^2 -x
            if (abs(s - s_old) < epsilon): # this makes the program terminate if we get to a desired tolerance before running all iterations
                break
        return s
    
    
def factorial(k):
    if k < 0.0:
        print("ERROR") # We only want this defined for positive integers at the moment
    if k == 0 or k == 1:
        return 1
    else:
        return k * factorial(k-1) # This gives us a recursive formula for factorials


def exp(x,n,epsilon):
    e_x = 0
    for i in range(n):
        e_x += x**i/factorial(i)
        if (abs(x**i/factorial(i)) < epsilon): # This makes the program terminate if a term of the Taylor series is small enough that we don't need to compute it
            break
    return e_x


def ln(x,n,epsilon):
    if x <= 0.0:
        print("ERROR") # ln is not defined for negative numbers or for zero
    if x > 0.0:
        s=0.0 #Starting guess
        for k in range(n):
            s_prev = s
            s=s-1+x*exp(-s,10,epsilon) # This is Newton's method again
            if (abs(s - s_prev) < epsilon): # This makes the program terminate if we achieve a desired tolerance before all of the iterations are run
                break
        return s
    

print(sqrt(2,100,10**-16))   
print(factorial(6))
print(exp(1,100,10**-16))
print(ln(2,100,10**-16)) 
    
print("Difference between my functions and math in Python:")
print(sqrt(2,100,10**-16) - math.sqrt(2))
print(factorial(6) - math.factorial(6))
print(exp(1,100,10**-16) - math.exp(1))
print(ln(2,100,10**-16) - math.log(2))

