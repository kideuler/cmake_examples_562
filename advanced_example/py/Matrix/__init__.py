import Matrixutil
import copy
import math

class Matrix:
    def __init__(self, data):
        if not all(len(row) == len(data[0]) for row in data):
            raise ValueError("All rows must have the same size")
        self.data = data
        self.m = len(data)
        self.n = len(data[0])

    def LUFactorization(self):
        return Matrixutil.LUFactorization(copy.deepcopy(self.data),self.m,self.n)
    
    def LUPFactorization(self, use_parallel=False):
        if use_parallel:
            return Matrixutil.LUPFactorization_Parallel(copy.deepcopy(self.data),self.m,self.n)
        else:
            return Matrixutil.LUPFactorization(copy.deepcopy(self.data),self.m,self.n)
    
    def QRFactorization(self):
        return Matrixutil.QRFactorization(copy.deepcopy(self.data),self.m,self.n)
        
    def QRCPFactorization(self, use_parallel=False):
        if use_parallel:
            return Matrixutil.QRCPFactorization(copy.deepcopy(self.data),self.m,self.n)
        else:
            return Matrixutil.QRCPFactorization_Parallel(copy.deepcopy(self.data),self.m,self.n)