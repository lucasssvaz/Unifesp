#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Mar  7 16:00:01 2019

@author: lucassvaz
"""

def dfa_iter(dfa,string,end,q0):
    atual = q0
    for letra in string:
        print(atual)
        atual = dfa[atual][int(letra)]
    if atual in end:
        print("Valido")
    else:
        print('Invalido')
    

dfa = {}

states = int(input("numero de estados:\n"))

q0 = int(input("estado inicial:\n"))

end = []

for i in range(states):
    s0 = int(input("estado "+str(i)+" vai para onde quando ver 0:\n"))
    s1 = int(input("estado "+str(i)+" vai para onde quando ver 1:\n"))
    dfa[i] = [s0,s1]

end_states = int(input("numero de estados finais:\n"))

for i in range(end_states):
    end.append(int(input("estado final:\n")))
    

string = str(input("string:\n"))

dfa_iter(dfa,string,end,q0)
print(dfa)