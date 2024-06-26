import MatrixFactorizations
import numpy as np
import unittest

class TestLU_no_pivoting(unittest.TestCase):

    def test_singular_matrix(self):
        # Tests on a singular matrix
        A = np.array([[1, 1], [1, 1]])
        with self.assertRaises(ValueError):
            MatrixFactorizations.LU_no_pivoting(A)

    def test_empty_matrix(self):
        # Tests on an empty matrix
        A = np.array([])
        with self.assertRaises(ValueError):
            MatrixFactorizations.LU_no_pivoting(A)
    
    def test_non_square_matrix(self):
        # Tests on a non-square matrix input
        A = np.array([[1, 2], [2, 3], [3, 4]])
        with self.assertRaises(ValueError):
            MatrixFactorizations.LU_no_pivoting(A)
    
    def test_numeric_matrix(self):
        # Tests on a matrix of non-numeric values
        A = np.array([["cat", 1], [2, 3]], dtype=str)
        with self.assertRaises(TypeError):
            MatrixFactorizations.LU_no_pivoting(A)

    def test_nan_or_inf(self):
        # Tests on a matrix with nan/inf values
        A = np.array([[np.nan, 2], [2, 3]])
        with self.assertRaises(ValueError):
            MatrixFactorizations.LU_no_pivoting(A)

    def test_example_matrix_1(self):
        # Tests on a simple matrix input
        A = np.array([[4, 3], [6, 3]])
        L, U = MatrixFactorizations.LU_no_pivoting(A)
        self.assertTrue(np.allclose(np.tril(L), L))
        self.assertTrue(np.allclose(np.triu(U), U))
        self.assertTrue(np.allclose(A, L@U))
    
    def test_example_matrix_2(self):
        # Tests on a simple matrix input
        A = np.array([[1, 1, 0], [2, 1, -1], [3, -1, -1]])
        L, U = MatrixFactorizations.LU_no_pivoting(A)
        self.assertTrue(np.allclose(np.tril(L), L))
        self.assertTrue(np.allclose(np.triu(U), U))
        self.assertTrue(np.allclose(A, L@U))

    def test_example_matrix_3(self):
        # Tests on a matrix that can only be decomposed using partial pivoting
        A = np.array([[2, -1, -2], [-4, 6, 3], [-4, -2, 8]])
        L, U = MatrixFactorizations.LU_no_pivoting(A)
        self.assertTrue(np.allclose(np.tril(L), L))
        self.assertTrue(np.allclose(np.triu(U), U))
        self.assertTrue(np.allclose(A, L@U))


class TestLU_partial_pivoting(unittest.TestCase):
    def test_empty_matrix(self):
        # Tests on an empty matrix
        A = np.array([])
        with self.assertRaises(ValueError):
            MatrixFactorizations.LU_partial_pivoting(A)    

    def test_nan_or_inf(self):
        # Tests on a matrix with nan/inf values
        A = np.array([[np.nan, 2], [2, 3]])
        with self.assertRaises(ValueError):
            MatrixFactorizations.LU_partial_pivoting(A)
    
    def test_numeric_matrix(self):
        # Tests on a matrix of non-numeric values
        A = np.array([["cat", 1], [2, 3]], dtype=str)
        with self.assertRaises(TypeError):
            MatrixFactorizations.LU_partial_pivoting(A)

    def test_singular_matrix(self):
        # Tests on a singular matrix
        A = np.array([[1, 1], [1, 1]])
        L, U, P = MatrixFactorizations.LU_partial_pivoting(A)
        self.assertTrue(np.allclose(np.tril(L), L))
        self.assertTrue(np.allclose(np.triu(U), U))
        self.assertTrue(np.allclose(A[P], L@U))

    def test_example_matrix_1(self):
        # Tests on a simple matrix input
        A = np.array([[4, 3], [6, 3]])
        L, U, P = MatrixFactorizations.LU_partial_pivoting(A)
        self.assertTrue(np.allclose(np.tril(L), L))
        self.assertTrue(np.allclose(np.triu(U), U))
        self.assertTrue(np.allclose(A[P], L@U))
    
    def test_example_matrix_2(self):
        # Tests on a simple matrix input
        A = np.array([[1, 1, 0], [2, 1, -1], [3, -1, -1]])
        L, U, P = MatrixFactorizations.LU_partial_pivoting(A)
        self.assertTrue(np.allclose(np.tril(L), L))
        self.assertTrue(np.allclose(np.triu(U), U))
        self.assertTrue(np.allclose(A[P], L@U))


    def test_example_matrix_3(self):
        # Tests on a matrix that can only be decomposed using partial pivoting
        A = np.array([[0, 1], [2, 1]])
        L, U, P = MatrixFactorizations.LU_partial_pivoting(A)
        self.assertTrue(np.allclose(np.tril(L), L))
        self.assertTrue(np.allclose(np.triu(U), U))
        self.assertTrue(np.allclose(A[P], L@U))


    def test_example_matrix_4(self):
        # Tests on a matrix that can only be decomposed using partial pivoting
        A = np.array([[2, -1, -2], [-4, 6, 3], [-4, -2, 8]])
        L, U, P = MatrixFactorizations.LU_partial_pivoting(A)
        self.assertTrue(np.allclose(np.tril(L), L))
        self.assertTrue(np.allclose(np.triu(U), U))
        self.assertTrue(np.allclose(A[P], L@U))


class TestQR_givens(unittest.TestCase):
    def test_empty_matrix(self):
        # Tests on an empty matrix
        A = np.array([])
        with self.assertRaises(ValueError):
            MatrixFactorizations.QR_Givens(A)    

    def test_nan_or_inf(self):
        # Tests on a matrix with nan/inf values
        A = np.array([[np.nan, 2], [2, 3]])
        with self.assertRaises(ValueError):
            MatrixFactorizations.QR_Givens(A)
    
    def test_numeric_matrix(self):
        # Tests on a matrix of non-numeric values
        A = np.array([["cat", 1], [2, 3]], dtype=str)
        with self.assertRaises(TypeError):
            MatrixFactorizations.QR_Givens(A)

    def test_singular_matrix(self):
        # Tests on a singular matrix
        A = np.array([[1, 1], [1, 1]])
        Q, R = MatrixFactorizations.QR_Givens(A)
        self.assertTrue(np.alltrue(np.isclose(Q@Q.T, np.eye(Q.shape[0]))))
        self.assertTrue(np.alltrue(np.isclose(Q@R - A, 0.0)))
        self.assertTrue(np.allclose(np.triu(R), R))

    def test_example_matrix_1(self):
        # Tests on a simple matrix input
        A = np.array([[4, 3], [6, 3]])
        Q, R = MatrixFactorizations.QR_Givens(A)
        self.assertTrue(np.alltrue(np.isclose(Q@Q.T, np.eye(Q.shape[0]))))
        self.assertTrue(np.alltrue(np.isclose(Q@R - A, 0.0)))
        self.assertTrue(np.allclose(np.triu(R), R))

    def test_example_matrix_2(self):
        # Tests on a simple matrix input
        A = np.array([[1, 1, 0], [2, 1, -1], [3, -1, -1]])
        Q, R = MatrixFactorizations.QR_Givens(A)
        self.assertTrue(np.alltrue(np.isclose(Q@Q.T, np.eye(Q.shape[0]))))
        self.assertTrue(np.alltrue(np.isclose(Q@R - A, 0.0)))
        self.assertTrue(np.allclose(np.triu(R), R))

    def test_example_matrix_3(self):
        # Tests on a matrix that can only be decomposed using partial pivoting
        A = np.array([[0, 1], [2, 1]])
        Q, R = MatrixFactorizations.QR_Givens(A)
        self.assertTrue(np.alltrue(np.isclose(Q@Q.T, np.eye(Q.shape[0]))))
        self.assertTrue(np.alltrue(np.isclose(Q@R - A, 0.0)))
        self.assertTrue(np.allclose(np.triu(R), R))
        

if __name__ == "__main__" :
    pass