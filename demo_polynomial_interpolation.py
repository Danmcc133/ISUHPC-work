# -*- coding: utf-8 -*-
"""
Created on Tue Feb  4 11:50:56 2025

@author: danie
"""

import numpy as np

def gauss_elim(A,b): # Here A is a matrix and b is a vector satisfying Ax=b for a yet to be determined vector x
    n = len(b)
    x = np.zeros_like(b)
    for k in range(n-1): #This is the forward elimination step
        for i in range(k+1,n):
            fctr = A[i,k] / A[k,k]
            for j in range(k,n):
                A[i,j] = A[i,j] - fctr*A[k,j]
            b[i] = b[i] - fctr*b[k]
    
    x[n-1] = b[n-1] / A[n-1,n-1]
    for i in range(n-2,-1,-1): #This is the backwards substitution step
        Sum = b[i]
        for j in range(i+1,n):
            Sum = Sum - A[i,j]*x[j]
        x[i] = Sum / A[i,i]
    return(x)
    
A = np.array([[1.0, -0.1, 0.1**2, -0.1**3],[1.0, -0.02, 0.02**2, -0.02**3],[1.0, 0.02, 0.02**2, 0.02**3],[1.0, 0.1, 0.1**2, 0.1**3]])
b = np.array([np.cos(-0.1), np.cos(-0.02), np.cos(0.02), np.cos(0.1)])

print(gauss_elim(A,b)) # This will give the entries to the vector x satisfying Ax=b

p = np.poly1d([9.03501810e-16, -4.99566811e-01, -1.12034224e-17, 9.99999833e-01])
# Above is the interpolating polynomial for cos(x) with coefficients found from Gaussian elimination, the next step is to figure out how to directly import the entries without having to type them out
print(np.cos(0))
print(p(0))
print(np.cos(0.0) - p(0)) # This shows the difference between the exact solution and our numerical solution
        