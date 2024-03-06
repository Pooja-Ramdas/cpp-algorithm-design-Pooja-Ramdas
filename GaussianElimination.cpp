#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const double EPSILON = 1e-9;

void printSolution(vector<double>& solution) {
    cout << "YES" << endl;
    for (double sol : solution) {
        cout << fixed << setprecision(2) << sol << " ";
    }
}

bool solveEquations(vector<vector<double>>& mat, int n) {
    vector<double> solution(n, 0);

    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (abs(mat[j][i]) > abs(mat[pivot][i])) {
                pivot = j;
            }
        }
        if (abs(mat[pivot][i]) < EPSILON) {
            return false; // System not solvable
        }
        swap(mat[i], mat[pivot]);

        for (int j = i + 1; j <= n; ++j) {
            mat[i][j] /= mat[i][i];
        }
        mat[i][i] = 1;

        for (int j = 0; j < n; ++j) {
            if (j != i) {
                double multiplier = mat[j][i];
                for (int k = i; k <= n; ++k) {
                    mat[j][k] -= mat[i][k] * multiplier;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        solution[i] = mat[i][n];
    }

    printSolution(solution);
    return true;
}

int main() {
    int n;
    cout << "Enter the number of variables: ";
    cin >> n;

    vector<vector<double>> mat(n, vector<double>(n + 1));

    for (int i = 0; i < n; ++i) {
        int m;
        cout << "Enter the number of coefficients in equation " << i + 1 << ": ";
        cin >> m;
        cout << "Enter the coefficients for equation " << i + 1 << " (including the constant term): ";
        for (int j = 0; j <= m; ++j) {
            cin >> mat[i][j];
        }
    }

    if (!solveEquations(mat, n)) {
        cout << "NO" << endl;
    }

    return 0;
}
