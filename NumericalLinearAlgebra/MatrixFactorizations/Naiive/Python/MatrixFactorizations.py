"""
Writing Matrix factorizations for the following decompositions:
    - LU
        - (done) No pivoting
        - (done) partial 
        - rook pivoting
    - QR
    - SVD
    - Cholesky

Also adding forward and back substitution
Should also do in place
"""
import numpy as np
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

if __name__ == "__main__":
    print("Running the Library!")
    exit()
