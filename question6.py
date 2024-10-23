import numpy as np

# Jacobi method implementation
def jacobi(A, b, tolerance=1e-6, max_iterations=100):
    n = len(A)
    x = np.zeros_like(b, dtype=np.float64)
    x_new = np.zeros_like(b, dtype=np.float64)
    
    for k in range(max_iterations):
        for i in range(n):
            s = sum(A[i][j] * x[j] for j in range(n) if j != i)
            x_new[i] = (b[i] - s) / A[i][i]
        
        # Check for convergence
        if np.linalg.norm(x_new - x, ord=np.inf) < tolerance:
            break
        
        x = np.copy(x_new)
    
    return x_new, k  # Solution and number of iterations

# Define matrix A and vector b for the system
A = np.array([[10, -2, 1], [-2, 10, -1], [1, -2, 10]], dtype=np.float64)
b = np.array([6, 6, 6], dtype=np.float64)

# Call Jacobi method
solution, iterations = jacobi(A, b)
print("Solution:", solution)
print("Iterations:", iterations)
