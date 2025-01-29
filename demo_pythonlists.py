# -*- coding: utf-8 -*-
"""
Created on Tue Jan 28 18:06:37 2025

@author: danie
"""

x= [1,2,3,4,5]
L = list(x)
L.append(10)
print(L)

L.clear()
print(L)

y = [1,2,3]
L = list(y)

M = L.copy()
print(M)

z= M.count(2)
print(z)

a = [3,4,5]
N = list(a)
M.extend(N)
print(M)

u = M.index(3)
print(u)

M.insert(2,9)
print(M)

H = M.pop(3)
print(H)

M.remove(9)
print(M)

M.reverse()
print(M)

M.sort()
print(M)
