#include <iostream>
#include <vector>

class matrix
{
    std::vector<std::vector<double>> m;
public:
    matrix(int rows, int cols); //прямоуг. матрица
    matrix(int size = 0); //квадратная матрица
    matrix(const std::vector<double>& diag);  //диаг. матрица
    matrix(const std::vector<std::vector<double>>& elements) { m = elements; }
    static matrix create_unit_matrix(int size);

    std::vector<double>& operator[](int row);
    const std::vector<double>& operator[](int row) const;

    int rows() const;
    int cols() const;
    int size() const;

    matrix transpose();
    matrix operator=(const matrix& arg2);
    matrix operator+(const matrix& arg2)const;
    matrix operator-(const matrix& arg2)const;
    matrix operator*(const matrix& arg2)const;
    matrix operator^(int n)const;

    void print_matrix();

    matrix inverse() const;
    double det() const;
    std::vector<double> gaussian_elimination(const std::vector<double>& rhs);
};

int main()
{
    /*matrix A(5, 5);
    matrix B(5, 5);
    matrix C = matrix::create_unit_matrix(5);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            A[i][j] = i;
            B[i][j] = 2;
        }
    }
    (A + B).print_matrix();
    std::cout << std::endl;
    A.print_matrix();
    std::cout << std::endl;
    C.print_matrix();
    std::cout << std::endl;
    (A * C).print_matrix();
    std::cout << std::endl;
    (A ^ 4).print_matrix();*/

    matrix A3({ {0,8,7},{6,5,4},{3,2,1} });
    std::cout << A3.det() << std::endl;
    A3 = A3.inverse();
    A3.print_matrix();
}

matrix::matrix(int rows, int cols)
{
    m.assign(rows, std::vector<double>(cols));
}

matrix::matrix(int size)
{
    m.assign(size, std::vector<double>(size));
}

matrix::matrix(const std::vector<double>& diag)
{
    int size = diag.size();
    m.assign(size, std::vector<double>(size));
    for (size_t i = 0; i < size; i++)
    {
        m[i][i] = diag[i];
    }
}

matrix matrix::create_unit_matrix(int size)
{
    matrix res(size);
    for (size_t i = 0; i < size; i++)
    {
        res[i][i] = 1.0;
    }
    return res;
}

std::vector<double>& matrix::operator[](int row)
{
    return m[row];
}

const std::vector<double>& matrix::operator[](int row) const
{
    return m[row];
}

int matrix::rows() const
{
    return m.size();
}

int matrix::cols() const
{
    return m[0].size();
}

int matrix::size() const
{
    return m.size();
}

matrix matrix::operator=(const matrix& arg2)
{
    this->m = arg2.m;
    matrix res(m.size(), m[0].size());
    res.m = this->m;
    return res;
}

matrix matrix::transpose() 
{
    matrix trans_res(m.size(), m[0].size());
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[i].size(); j++)
        {
            trans_res[i][j] = m[j][i];
        }
    }
    return trans_res;
}

matrix matrix::operator+(const matrix& arg2) const
{
    matrix sum_res(arg2.rows(), arg2.cols());
    for (int i = 0; i < arg2.rows(); i++)
    {
        for (int j = 0; j < arg2.cols(); j++)
        {
            sum_res[i][j] = m[i][j] + arg2[i][j];
        }
    }
    return sum_res;
}

matrix matrix::operator-(const matrix& arg2) const
{
    matrix sub_res(arg2.rows(), arg2.cols());
    for (int i = 0; i < arg2.rows(); i++)
    {
        for (int j = 0; j < arg2.cols(); j++)
        {
            sub_res[i][j] = m[i][j] - arg2[i][j];
        }
    }
    return sub_res;
}

matrix matrix::operator*(const matrix& arg2) const
{
    matrix mul_res(m.size(), arg2.cols());
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < arg2.cols(); j++)
        {
            for (int k = 0; k < arg2.rows(); k++)
            {
                mul_res[i][j] += m[i][k] * arg2[k][j];
            }
        }
    }
    return mul_res;
}

matrix matrix::operator^(int n) const
{
    matrix res = matrix::create_unit_matrix(m.size());
    matrix pow;
    pow.m = this->m;
    while (n > 0)
    {
        if (n % 2 == 1)
        {   
            res = (pow * res);
        }
        n /= 2;
        if (n == 0)
        {
            break;
        }
        pow = pow * pow;
    }
    return res;
}

void matrix::print_matrix()
{
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[i].size(); j++)
        {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

matrix matrix::inverse() const
{
    if (rows() != cols())
        return 0;
    matrix M{ *this };
    matrix E = matrix::create_unit_matrix(M.size());
    double d = 1.0;
    for (size_t k = 0, N = size(); k < N; k++)
    {
        if (M[k][k] == 0)
        {
            for (size_t i = k + 1; i < N; i++)
            {
                if (M[i][k] != 0)
                {
                    iter_swap(M.m.begin() + k, M.m.begin() + i);
                    iter_swap(E.m.begin() + k, E.m.begin() + i);
                }
            }
        }
        double mkk = M[k][k];
        d *= mkk;
        for (size_t j = k; j < N; j++)
        {
            M[k][j] /= mkk;
            E[k][j] /= mkk;
        }
        for (size_t i = k + 1; i < N; i++)
        {
            double mik = M[i][k];
            for (size_t j = 0; j < N; j++)
            {
                M[i][j] -= mik * M[k][j];
                M[i][j] -= mik * E[k][j];
            }
        }
        for (size_t i = k - 1; i >= 0; i--)
        {
            double mik = M[i][k];
            for (size_t j = 0; j < N; j++)
            {
                M[i][j] -= mik * M[k][j];
                M[i][j] -= mik * E[k][j];
            }
        }
    }

    return E;
}

double matrix::det() const
{
    if (rows() != cols())
        return 0;
    matrix M{ *this };
    double d = 1.0;
    int count_swaps = 0;
    for (size_t k = 0, N = size(); k < N; k++)
    {
        if (M[k][k] == 0)
        {
            for (size_t i = k + 1; i < N; i++)
            {
                if (M[i][k] != 0)
                {
                    iter_swap(M.m.begin() + k, M.m.begin() + i);
                    count_swaps++;
                }
            }
        }
        double mkk = M[k][k];
        d *= mkk;
        for (size_t j = k; j < N; j++)
            M[k][j] /= mkk;
        for (size_t i = k + 1; i < N; i++)
        {
            double mik = M[i][k];
            for (size_t j = 0; j < N; j++)
            {
                M[i][j] -= mik * M[k][j];
            }
        }
    }
    if (count_swaps % 2 == 1)
    {
        return d * -1;
    }
    return d;
}

std::vector<double> matrix::gaussian_elimination(const std::vector<double>& rhs)
{
    return std::vector<double>();
}
