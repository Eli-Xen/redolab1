#include <iostream>
#include <cstdio>
using namespace std;

class Matrix {
public:
    int matrix_size;
    double** matrix_data; //double pointer array 

    Matrix(int size = 0) : matrix_size(size) { //constructor initalizes variables for matrix size and data 
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
        }
    }

    ~Matrix() { //destructor deletes all matrix variables and data 
        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;
    }
};

void read_matrix_from_file(const string& file_name, Matrix& matrix_1, Matrix& matrix_2) {
    // TODO: Read matrix data from the file
    FILE *file=fopen(file_name.c_str(), "r"); //open the file in read mode 
    int n; 
    fscanf(file, "%d", &n); //gets the size of the matrix 
    Matrix temp_matrix_1(n); //initilize new matricies since other ones werent initlized with a size
    Matrix temp_matrix_2(n);
    for (int i=0; i<n; i++) //read each line of file into first matrix
    {
        for (int j=0; j<n; j++) //read each elemnt of each line into matrix properly 
        {fscanf(file, "%lf", &temp_matrix_1.matrix_data[i][j]);}
    }
    for (int i=0; i<n; i++) //read each line of file into first matrix
    {
        for (int j=0; j<n; j++) //read each elemnt of each line into matrix properly 
        {fscanf(file, "%lf", &temp_matrix_2.matrix_data[i][j]);}
    }

    fclose(file); //close file 
    //swap data between temp matrices and real matrices
    std::swap(matrix_1.matrix_size, temp_matrix_1.matrix_size);
    std::swap(matrix_1.matrix_data, temp_matrix_1.matrix_data);
    std::swap(matrix_2.matrix_size, temp_matrix_2.matrix_size);
    std::swap(matrix_2.matrix_data, temp_matrix_2.matrix_data);
    
}

void print_matrix(const Matrix& matrix) { //iterates through row and column and print matrix data object value 
    for (int i=0; i<matrix.matrix_size; i++) 
    {
        for (int j=0; j<matrix.matrix_size; j++) 
        {
            cout << matrix.matrix_data[i][j] << " ";
        }
        cout << endl; //print end line after each row so that each element in in the same printed row 
    }
}

void print_matrix(const Matrix& matrix_1, const Matrix& matrix_2) { //function overload prints 2 matricies, calls other print matrix to simplify and decrease file weight/size 
    // TODO: Print both matrices to the console
    print_matrix(matrix_1); 
    cout << endl; //this seems to basically be equivalent to \n plus clears the input buffer line 
    print_matrix(matrix_2); 
}

Matrix add_matrices(const Matrix& matrix_1, const Matrix& matrix_2) { //
    // TODO: Implement matrix addition
    Matrix addedMat(matrix_1.matrix_size); //creates new matrix to save result to 
    for (int i=0; i<matrix_1.matrix_size; i++) //read each line of file into first matrix
    {
        for (int j=0; j<matrix_1.matrix_size; j++) //read each elemnt of each line into matrix properly 
        {addedMat.matrix_data[i][j]=matrix_1.matrix_data[i][j]+matrix_2.matrix_data[i][j];}
    }
    return addedMat; 
}

Matrix multiply_matrices(const Matrix& matrix_1, const Matrix& matrix_2) { //iteraties through row and column and adds row times column dot product 
    // TODO: Implement matrix multiplication
    Matrix multMat(matrix_1.matrix_size); //creates new matrix to save result to 
    for (int i=0; i<matrix_1.matrix_size; i++)
    {
        for (int j=0; j<matrix_1.matrix_size; j++)
        {
            for (int k=0; k<matrix_1.matrix_size; k++) //dot product of the i row of m1 and j column of m2; goes through k times
            {
                multMat.matrix_data[i][j]+=matrix_1.matrix_data[i][k]*matrix_2.matrix_data[k][j]; //keeps adding result for each k iteration as it goes through k row and k column in common 
            }
        }
    }

    return multMat; 
}

// Overloaded + operator for matrix addition
Matrix operator+(const Matrix& matrix_1, const Matrix& matrix_2) //overload for + operator to add entry-wise 
{
    Matrix addedOvrld(matrix_1.matrix_size); //initilize new result matrix
    for (int i=0; i<matrix_1.matrix_size; i++) //iterates through row and column and adds entries to result matrix 
    {
        for (int j=0; j<matrix_1.matrix_size; j++) 
        {addedOvrld.matrix_data[i][j]=matrix_1.matrix_data[i][j]+matrix_2.matrix_data[i][j];}
    }
    return addedOvrld; 
}

// Overloaded * operator for matrix multiplication
Matrix operator*(const Matrix& matrix_1, const Matrix& matrix_2)
{
    Matrix multOvrld(matrix_1.matrix_size); //creates new matrix to save result to 
    for (int i=0; i<matrix_1.matrix_size; i++)
    {
        for (int j=0; j<matrix_1.matrix_size; j++)
        {
            for (int k=0; k<matrix_1.matrix_size; k++) //dot product of the i row of m1 and j column of m2; goes through k times
            {
                multOvrld.matrix_data[i][j]+=matrix_1.matrix_data[i][k]*matrix_2.matrix_data[k][j]; //keeps adding result for each k iteration as it goes through k row and k column in common 
            }
        }
    }

    return multOvrld; 
}

void get_diagonal_sum(const Matrix& matrix) {
    // TODO: Calculate and print the sum of the diagonal elements 
    int diag1=0, diag2=0; //main and decondary diagonal initilized to 0 to avoid random numbers 
    for (int i=0; i<matrix.matrix_size; i++) //iterates through row and column and if they match add the value to diagonal 1 
    {
        for (int j=0; j<matrix.matrix_size; j++)
        {
            if (i==j)
            {diag1+=matrix.matrix_data[i][j];}
            
        }
    }

    int counter=matrix.matrix_size-1; //counter to do antidiagonal, will start at edge and go across 
    for (int i=0; i<matrix.matrix_size; i++) //iterates through row and column and if column matches counter then add to diagonal 2 and incriment counter 
    {
        for (int j=0; j<matrix.matrix_size; j++)
        {
            if (j==counter)
            {diag2+=matrix.matrix_data[i][j]; counter--;}
        }
    }
    cout << "sum of main diagonal: " << diag1 << endl; //prints data pretty 
    cout << "sum of seconday diagonal: " << diag2 << endl;
}

void swap_matrix_row(Matrix& matrix, int row1, int row2) {
    // TODO: Swap the rows 'row1' and 'row2' in the matrix
    //    Handle invalid row indices 
    if (row1<0 || row1>matrix.matrix_size || row2<0 || row2>matrix.matrix_size)
    {cout << "invalid row indecies, please make another call to swap function with valid indecies" << endl;} //incase theres invalid row indecies given from main 
    for (int j=0; j<matrix.matrix_size; j++) //takes each column and swaps it between row1 and row2
    {
        int temp=matrix.matrix_data[row1][j]; //temp var to store first value 
        matrix.matrix_data[row1][j]=matrix.matrix_data[row2][j]; //second value stores to var1 
        matrix.matrix_data[row2][j]=temp; //temp value stores to var2 
    }
}

int main(int argc, char* argv[]) {
    Matrix matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);

    cout << "print_matrix" << endl;
    print_matrix(matrix_1, matrix_2);

    // cout << "add_matrices result:" << endl;
    Matrix add_result_1 = add_matrices(matrix_1, matrix_2);
    Matrix add_result_2 = matrix_1 + matrix_2;
    cout << endl; 
    cout << "add_matrices function result:" << endl;
    print_matrix(add_result_1);
    cout << "+ operator overload result:" << endl;
    print_matrix(add_result_2);

    cout << endl; 
    // cout << "multiply_matrices result:" << endl;
    Matrix multiply_result_1 = multiply_matrices(matrix_1, matrix_2);
    Matrix multiply_result_2 = matrix_1 * matrix_2;
    cout << "add_matrices function result:" << endl;
    print_matrix(multiply_result_1);
    cout << "* operator overload result:" << endl;
    print_matrix(multiply_result_2);

    cout << endl; 
    // cout << "get matrix diagonal sum: " << endl;
    get_diagonal_sum(matrix_1);

    cout << endl; 
    cout << "swap matrix_1 rows: " << endl;
    swap_matrix_row(matrix_1, 0, 1);
    print_matrix(matrix_1); //prints the edited matrix object 

    return 0;
}