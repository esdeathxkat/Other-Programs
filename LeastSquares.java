import java.util.Arrays;

public class LeastSquares {

    public static double[] leastSquares(double[][] A, double[] b) {
        int m = A.length;
        int n = A[0].length;
        double[][] AtA = new double[n][n];
        double[] Atb = new double[n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                Atb[j] += A[i][j] * b[i];
                for (int k = 0; k < n; k++) {
                    AtA[j][k] += A[i][j] * A[i][k];
                }
            }
        }


        return solveSystem(AtA, Atb);
    }

    private static double[] solveSystem(double[][] A, double[] b) {
        int n = b.length;
        double[][] augmented = new double[n][n + 1];

        // Augment A with b
        for (int i = 0; i < n; i++) {
            System.arraycopy(A[i], 0, augmented[i], 0, n);
            augmented[i][n] = b[i];
        }

        // Forward elimination
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double ratio = augmented[j][i] / augmented[i][i];
                for (int k = i; k <= n; k++) {
                    augmented[j][k] -= ratio * augmented[i][k];
                }
            }
        }

        // Back substitution
        double[] x = new double[n];
        for (int i = n - 1; i >= 0; i--) {
            x[i] = augmented[i][n] / augmented[i][i];
            for (int j = 0; j < i; j++) {
                augmented[j][n] -= augmented[j][i] * x[i];
            }
        }

        return x;
    }

    // Method to compute RMSE
    public static double computeRMSE(double[][] A, double[] b, double[] x) {
        double sumSquaredErrors = 0.0;
        for (int i = 0; i < A.length; i++) {
            double predicted = 0.0;
            for (int j = 0; j < x.length; j++) {
                predicted += A[i][j] * x[j];
            }
            sumSquaredErrors += Math.pow(predicted - b[i], 2);
        }
        return Math.sqrt(sumSquaredErrors / A.length);
    }

    public static void main(String[] args) {
        // Coefficient matrix A
        double[][] A = {
            {3, -1, 2},
            {4, 1, 0},
            {-3, 2, 1},
            {1, 1, 5},
            {-2, 0, 3}
        };

        // Right-hand side vector b
        double[] b = {1, 2, 3, 4, 5}; 

        // Calculate least squares solution and RMSE
        double[] leastSquaresSolution = leastSquares(A, b);
        System.out.println("Least Squares Solution: " + Arrays.toString(leastSquaresSolution));
        System.out.println("RMSE: " + computeRMSE(A, b, leastSquaresSolution));
    }
}
