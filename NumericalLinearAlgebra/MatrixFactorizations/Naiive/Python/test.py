# Test Script for Matrix Factorizations
import test_class
# begin temp
import MatrixFactorizations
import numpy as np
# end temp
import unittest


def test_function(t_class) :
    loader = unittest.TestLoader()
    suite = loader.loadTestsFromTestCase(t_class)
    runner = unittest.TextTestRunner(verbosity=2)
    res = runner.run(suite)

    return int(not res.wasSuccessful())
    

def main() -> int :
    return test_function(test_class.TestQR_givens)

if __name__ == "__main__":
    exit_code = main()
    exit(exit_code)