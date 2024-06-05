# Test Script for Matrix Factorizations
import test_class
import unittest


def test_function(t_class) :
    loader = unittest.TestLoader()
    suite = loader.loadTestsFromTestCase(t_class)
    runner = unittest.TextTestRunner(verbosity=2)
    res = runner.run(suite)

    return int(not res.wasSuccessful())
    

def main() -> int :
    return test_function(test_class.TestLU_partial_pivoting)

if __name__ == "__main__":
    exit_code = main()
    exit(exit_code)