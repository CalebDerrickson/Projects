"""
Writing Matrix factorizations for the following decompositions:
    - LU
        - (done) No pivoting
        - partial 
        - rook pivoting
    - QR
    - SVD
    - Cholesky

Also adding forward and back substitution
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

    return (L, U)

def LU_partial_pivoting(A: np.ndarray) -> typing.Tuple[np.ndarray, np.ndarray, np.ndarray]:
    m, n = A.shape
    
    if m == 0 or n == 0:
        raise ValueError("Input Matrix is empty")
    
    if not np.issubdtype(A.dtype, np.number):
        raise TypeError("The Input Matrix has non numeric values!")
    
    if np.isnan(A).any() or np.isinf(A).any():
        raise ValueError("Nan or Inf entry found.")
    
    L = np.eye(n)
    P = np.zeros(n)
    U = A.astype(np.double).copy()

    for k in range(1, m-1):
        # Find Pivot
        pivot_index = np.argmax(np.abs(U[k:m, k]))
        pivot = np.abs(U[pivot_index, k])

        if np.isclose(pivot, 0):
            raise ValueError("Input Matrix is Singular.")
        

        # Perform the Pivot
        U[[k, pivot_index], k:m] = U[[pivot_index, k], k:m]
        L[[k, pivot_index], 1:k-1] = L[[pivot_index, k], 1:k-1]
        #P[[k, pivot_index], :] = P[[pivot_index, k], :]
        P[k] = pivot_index

        for j in range(k+1, m):
            L[j, k] = U[j, k] / U[k, k]
            U[j, k:m] = U[j, k:m] - L[j, k] * U[k, k:m]

    return L, U, P


if __name__ == "__main__":
    print("Running the Library!")
    exit()
