# -*- coding: utf-8 -*-
"""
Created on Fri Jan 24 20:13:04 2025

@author: danie
"""

def sqrt(x,n):
    if x == 0.0:
        return 0
    if x < 0.0:
        print("ERROR")
        return -1.0
    if x > 0.0:
        s=1.0
        for k in range(n):
            s=0.5*(s+x/s)
        return s
    
    
def factorial(k):
    ftl=1
    for i in range(1,k+1):
        ftl=ftl*i
    return(ftl)


def exp(x,n):
    e_x = 0
    for i in range(n):
        e_x += x**i/factorial(i)
    return e_x


def ln(x,n):
    if x <= 0.0:
        print("ERROR")
    if x > 0.0:
        s=0.0
        for k in range(n):
            s=s-1+x*exp(-s,10)
        return s
    

print(sqrt(2,100))   
print(factorial(6))
print(exp(1,100))
print(ln(2,100)) 
    
