# -*- coding: utf-8 -*-
"""
Created on Thu Feb  6 11:43:58 2025

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

def LeastSquareApprox(x,f):
    A = np.vstack([x, np.ones(len(x))]).T #This creates the matrix needed for least squares, the transpose makes the operation possible
    f = f[:, np.newaxis] #This creates a column vector with the entries being our function f applied to the corresponding values in x
    return(gauss_elim(np.dot(A.T, A), np.dot(A.T, f)))

x = np.linspace(-np.pi, np.pi, 51)
f = np.cos(x)
print(LeastSquareApprox(x,np.cos(x)))

p = np.poly1d([-9.11210703e-17, -1.96078431e-02])
print("Polynomial of Best Approximation:" , p)
