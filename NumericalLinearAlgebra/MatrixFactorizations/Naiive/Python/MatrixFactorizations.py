"""
Writing Matrix factorizations for the following decompositions:
    - LU
        - (done) No pivoting
        - (done) partial 
        - rook pivoting
        - sparse 
    - (done for now) QR (Givens)
    - SVD
    - Cholesky

Also adding forward and back substitution
"""
import numpy as np
import math
import typing

def LU_no_pivoting(A: np.ndarray) -> typing.Tuple[np.ndarray, np.ndarray]:
    #For matrix of size n x n
    n = max(A.shape)

    if n == 0:
        raise ValueError("The input matrix is empty.")
    
    if not np.issubdtype(A.dtype, np.number):
        raise TypeError("The Input Matrix has non numeric values!")
    
    if np.isnan(A).any() or np.isinf(A).any():
        raise ValueError("Nan or Inf entry found.")
    
    if n != A.shape[0] or n != A.shape[1]:
        raise ValueError("The input matrix is not square.")

    L = np.eye(n, dtype= np.double)
    U = A.astype(np.double).copy()

    for i in range(n):
        if np.isclose(U[i, i], 0):
            raise ValueError("Diagonal is zero.")
            
        
        fac = U[i+1:, i] / U[i, i]
        L[i+1:, i] = fac
        U[i+1:] -= fac[:, np.newaxis]* U[i]

    return L, U

def LU_partial_pivoting(A: np.ndarray) -> typing.Tuple[np.ndarray, np.ndarray, np.ndarray]:
    m, n = A.shape
    
    if m == 0 or n == 0:
        raise ValueError("Input Matrix is empty")
    
    if not np.issubdtype(A.dtype, np.number):
        raise TypeError("The Input Matrix has non-numeric values!")
    
    if np.isnan(A).any() or np.isinf(A).any():
        raise ValueError("NaN or Inf entry found.")
    
    L = np.eye(m)
    U = A.astype(np.double).copy()
    P = np.arange(m)

    for k in range(n):
        pivot, m = np.max(np.abs(U[k:, k])), np.argmax(np.abs(U[k:, k])) + k
        if m != k:
            U[[m, k], :] = U[[k, m], :]
            
            P[k], P[m] = P[m], P[k]
            if k >= 1:
                # interchange rows m and k in L
                temp = np.copy(L[k, :k])
                L[k, :k] = L[m, :k]
                L[m, :k] = temp
        for j in range(k+1, n):
            L[j, k] = U[j, k] / U[k, k]
            U[j, :] = U[j, :] - L[j, k] * U[k, :]

    return L, U, P.astype(int)


def QR_Givens(A: np.ndarray) -> typing.Tuple[np.ndarray, np.ndarray]:
    """
    Calculates the QR Decomposition of an n times n matrix using Givens Rotations.
    The Square constraint on the input matrix is just for simplicity in implementing.
    Using the Givens method for easing into paralellizability.
    """
    def givens_matrix(A: np.ndarray, n: int, i: int, j: int) -> np.ndarray:
        """
        Returns the Givens Matrix for the inputed indices i and j.
        n is the size of the matrix A.
        """
        a = A[i-1][j]
        b = A[i][j]
        
        G = np.eye(n)
        
        #Calculate c, s, r
        if np.isclose(b, 0.0):
            #c is approx 1, s is approx 0
            return G
    
        r = np.hypot(a, b)
        d = 1.0/r
        c = a * d
        s = -b * d
        
        G[i][i] = c
        G[j][j] = c
        G[i][j] = s
        G[j][i] = -s
        return G
    
    # Continue funciton
    n = max(A.shape)

    if n == 0:
            raise ValueError("The input matrix is empty.")
        
    if not np.issubdtype(A.dtype, np.number):
        raise TypeError("The Input Matrix has non numeric values!")
    
    if np.isnan(A).any() or np.isinf(A).any():
        raise ValueError("Nan or Inf entry found.")
    
    if n != A.shape[0] or n != A.shape[1]:
        raise ValueError("The input matrix is not square.")   
    
    R = A.astype(np.double)
    Q = np.eye(n)
    for i in range(n):
        for j in range(n):
            if i > j:
                G = givens_matrix(R, n, i, j)
                Q = (G@Q).T
                R = G@R
    
    # Flipping signs so that QR is unique
    for i in range(n):
        if R[i, i] < 0:
            R[i, :] *= 1.0
            Q[:, i] *= 1.0

    return Q, R


def Chol(A: np.ndarray) -> np.ndarray:
    """
    Performs cholesky decomposition of the input matrix.
    This is an implementation of the Cholesky–Banachiewicz algorithm.
    """
    n = max(A.shape)

    if n == 0:
            raise ValueError("The input matrix is empty.")
        
    if not np.issubdtype(A.dtype, np.number):
        raise TypeError("The Input Matrix has non numeric values!")
    
    if np.isnan(A).any() or np.isinf(A).any():
        raise ValueError("Nan or Inf entry found.")
    
    if n != A.shape[0] or n != A.shape[1]:
        raise ValueError("The input matrix is not square.")   

    L = np.eye(n)
    D = np.zeros_like(A)

    for i in range(n):
        for j in range(i+1):
            sum = 0.0
            for k in range(j-1):
                sum += L[j][k] * L[j][k] * D[k][k]
            
            if A[j][j] - sum < 0:
                raise ValueError("The input matrix is not Postive Semi Definite!")
            
            D[j][j] = A[j][j] - sum
            
            if i == j:
                L[i][j] = 1.0
            else:
                sum = 0
                for k in range(j-1):
                    sum += L[i][k] * L[j][k] * D[k][k]
                
                sum *= (1.0 / D[j][j])
                L[i][j] = sum 

    return L, D

            


if __name__ == "__main__":
    print("Running the Library!")
    exit()
