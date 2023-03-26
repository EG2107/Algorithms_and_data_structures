#include<iostream>
#include<vector>
using namespace std;

vector<vector<long long>> multiply_matrix(vector<vector<long long>> &matrix_a, vector<vector<long long>> &matrix_b){
    vector<vector<long long>> matrix_c;
    int row_a = matrix_a.size(), col_a = matrix_a[0].size(), col_b = matrix_b[0].size();
    matrix_c.resize(row_a, vector<long long>(col_b, 0));
    for (int i = 0; i < row_a; i++){
        for (int j = 0; j < col_b; j++){
            for (int k = 0; k < col_a; k++){
                matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }
    return matrix_c;
}

vector<vector<long long>> pow_matrix(vector<vector<long long>> &matrix, int k){
    if (k == 0 || k == 1){
        return matrix;
    }
    if (k % 2 == 0){
        vector<vector<long long>> new_matrix = pow_matrix(matrix, k/2);
        return multiply_matrix(new_matrix, new_matrix);
    }
    vector<vector<long long>> new_matrix = pow_matrix(matrix, k-1);
    return multiply_matrix(new_matrix, matrix);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<vector<long long>> matrix_a;
    matrix_a.resize(2, vector<long long>(2));
    matrix_a[0][0] = 0;
    matrix_a[0][1] = 1;
    matrix_a[1][0] = 1;
    matrix_a[1][1] = 1;

    vector<vector<long long>> matrix_b;
    matrix_b.resize(2, vector<long long>(1));
    matrix_b[0][0] = 1;
    matrix_b[1][0] = 1;

    int n;
    cin >> n;
    vector<vector<long long>> pow_a_in_n;
    pow_a_in_n = pow_matrix(matrix_a, n);
    cout << multiply_matrix(pow_a_in_n, matrix_b)[0][0];

    return 0;
}