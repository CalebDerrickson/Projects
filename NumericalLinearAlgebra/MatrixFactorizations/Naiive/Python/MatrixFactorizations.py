"""
Writing Matrix factorizations for the following decompositions:
    - LU
        - No pivoting, partial, and full pivoting
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
    U = A.astype(np.double)

    for i in range(n):
        if np.isclose(U[i, i], 0):
            raise ValueError("Diagonal is zero.")
            
        
        fac = U[i+1:, i] / U[i, i]
        L[i+1:, i] = fac
        U[i+1:] -= fac[:, np.newaxis]* U[i]

    return (L, U)



if __name__ == "__main__":
    print("Running the Library!")
    exit()
