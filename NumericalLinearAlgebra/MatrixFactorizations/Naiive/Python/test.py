# Test Script for Matrix Factorizations
import test_class
import unittest

def main() -> int :
    loader = unittest.TestLoader()
    suite = loader.loadTestsFromTestCase(test_class.TestLU_no_pivoting)
    runner = unittest.TextTestRunner(verbosity=2)
    res = runner.run(suite)

    return int(not res.wasSuccessful())
    

if __name__ == "__main__":
    exit_code = main()
    exit(exit_code)