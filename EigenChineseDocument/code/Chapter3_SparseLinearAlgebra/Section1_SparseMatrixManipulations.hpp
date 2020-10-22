#ifndef SPARSE_MATRIX_MANIPULATIONS_HPP
#define SPARSE_MATRIX_MANIPULATIONS_HPP
#include "HeaderFile.h"
#include "HelpFunctions.hpp"
namespace Chapter3_SparseLinearAlgebra
{
namespace Section1_SparseMatrixManipulations
{
// ϡ������ʽ
// �����Ӧ���У�������ֻ����������ϵ���������ľ����Ϊϡ�����(Sparse Matrix)��
// ����������£�����ϡ�����Ĵ洢��ʽ�������洢����ϵ�������Լ����ڴ����Ĳ�������ܡ�

// ��Eigen�У�SparseMatrix<>ģ���������ڱ�ʾϡ�����ע����ܵ��õ���Matrix<>
//SparseMatrix<>�ṩ�˸����ܺ͵��ڴ�ʹ���ʡ�
//��ʵ���˹㷺ʹ�õ�ѹ���У����У��洢�����ĸ�ͨ�õı��塣

//�����ĸ�����������ɣ�
// 1. Values: �洢�����ϵ��ֵ��ע�⣬ѹ���д洢����һ��һ�е�˳��洢����Ԫ�أ�ͬ����ѹ���а���һ��һ�е�˳��洢Ԫ�أ�
// 2. InnerIndices: �洢������У����У��±ꡣ�򵥵�˵�����ǿ����Ȱ����л����е�˳��洢values��Ȼ�����values�е�ÿһ��Ԫ�أ�ȷ�������ڵ���or�е��±ꣻ
// 3. OuterStarts: Ϊÿ�У��ֱ�Ϊ�У��洢ǰ���������е�һ�������������ע�⣬�������洢��Values��InnerIndices�е�λ�ã�
// 4. InnerNNZs:�洢ÿ�У��ֱ�Ϊ�У��ķ���Ԫ�ظ�����
// ע�⣺����innerָ�����ڲ�������������������������У�������������С�
// ����outer��ָ��һ�����򣬼���or�У�

// ��һ��ʾ���п��Ը��õؽ��ʹ˴洢���������¾���
// 0	3	0	0	0
// 22	0	0	0	17
// 7	5	0	1	0
// 0	0	0	0	0
// 0	0	14	0	8
// ������ܵ�ϡ��**����**��ʾ��ʽ֮һ��

// Values:	22	7	_	3	5	14	_	_	1	_	17	8                ע�ͣ���������ʽ��һ��һ�еĴ洢����Ԫ�أ� _ ��Ϊ�˲���Ԫ���õ�
 
// InnerIndices:	1	2	_	0	2	4	_	_	2	_	1	4      ע�ͣ�����Values�����ǿ��Կ�ValuesԪ�����ڵ�ÿһ�У����磬22�ڵ�1�У�7�ڵ�2�У��Դ�����


// OuterStarts:	0	3	5	8	10	12      ע�ͣ�OutStarts��ʾ��ÿһ���е���ʼ����Ԫ����Values or InnerIndices�е�������
// ����,��һ�з���Ԫ��22��Values�еĵ�0�������ڶ����е�3��Values�еĵ�3�������������е�14��Values�еĵ�5����...
 // ����������ǣ�OutStarts����һ��Ԫ�أ���������������5�У���ôӦ��ֻ��5��Ԫ�أ���������6��Ԫ�أ��ѵ��Ǵ洢�����һ��Ԫ�أ�


// InnerNNZs:	2	2	1	1	2       ע�ͣ�5�����еķ���Ԫ�ظ���


// TODO:
// ��ǰ��ȷ��ʼ��ͨ�������ڲ��������Ը����ڲ�������Ԫ�ؽ�������
//��"_"ָʾ���ÿռ������ٲ����µ�Ԫ�ء����費��Ҫ���·��䣬
//����O��nnz_j���в������Ԫ�أ�����nnz_j����Ӧ�ڲ������ķ�������
//��һ���棬�ڸ������ڲ������в���������ӵ��ڲ�������Ԫ�ػ������Ч��
//��Ϊ�����Ҫ����InnerNNZs��ΪO��1������ĸ���Ԫ�ء�

// û�п��ÿռ�������һ�������������Ϊѹ��ģʽ��
//����Ӧ�ڹ㷺ʹ�õ�ѹ���У����У��洢������CCS��CRS����
//ͨ������SparseMatrix :: makeCompressed�������������Խ��κ�SparseMatrixת��Ϊ������ʽ��
//����������£���Ϊ���ǵ��ڣ�[j] = [j + 1]- [j] �����Կ���ָ���������Ƕ���ġ�
//��ˣ�ʵ���ϣ���SparseMatrix :: makeCompressed�����ĵ��ý��ͷŴ˻�������
//InnerNNZsOuterStartsInnerNNZsOuterStartsOuterStarts
// ֵ��ע����ǣ����Ƕ��ⲿ��Ĵ������װ����Ҫѹ��������Ϊ���롣

//Eigen����Ľ��ʼ�ջ�����ѹ����ϡ�����
//��һ���棬��SparseMatrix�в�����Ԫ�ػὫ���Ժ�ת��Ϊ��ѹ��ģʽ��
// ������ǰ��ѹ��ģʽ��ʾ�ľ���

// Values:	22	7	3	5	14	1	17	8
// InnerIndices:	1	2	0	2	4	2	1	4
// OuterStarts:	        0	2	4	5	6	8
// һ��ϡ��������һ����һ���������ϡ���������ֻ��Values��InnerIndices����洢��
//SparseVectorû��ѹ��/δѹ��ģʽ�ĸ��

// ��һ������
// ������ÿ����֮ǰ�������Ǵ����µ���ʾ����ʼ��
//$ \ Delta u = 0 $ʹ�����޲�ַ�����Dirichlet�߽������ڹ���2D���������������˹���̡�
//�����������������ѧ�ϱ�ʾΪAx = b��ʽ���������⣬����x��һ��mά�������ڱ����У�����ʾ����ֵ, b�Ǵӱ߽������л�ã�
//����A��һ��mXm�ķ������Ǵ���ɢ����������˹�����л�õ�ϡ����󣬼���ֻ���������ķ�0Ԫ��

void FirstExample()
{
        LOG();

        int n = 300;   // size of the image
        int m = n * n; // number of unknows (=number of pixels)
        // Assembly:
        std::vector<T> coefficients;      // list of non-zeros coefficients,��HelpFunctions.hpp�е�```typedef Eigen::Triplet<double> T;```
        Eigen::VectorXd b(m);             // the right hand side-vector resulting from the constraints
        buildProblem(coefficients, b, n); //��HelpFunctions.hpp�е�```void buildProblem(std::vector<T> &coefficients, Eigen::VectorXd &b, int n);```
        SpMat A(m, m);
        A.setFromTriplets(coefficients.begin(), coefficients.end());
        // Solving:
        Eigen::SimplicialCholesky<SpMat> chol(A); // performs a Cholesky factorization of A,������ִ��ϡ������˹���ֽ�
        Eigen::VectorXd x = chol.solve(b);        // use the factorization to solve for the given right hand side��Ȼ�����Ax=b

        // Export the result to a file:
        saveAsBitmap(x, n, "result.bmp");
}

void TheSparseMatrixClass()
{
        LOG();

        //  ϡ������ʸ����һģ���࣬��������ģ�������
        //   1. Scaler�����磬double��,
        //   2. �洢˳�����磬ColMajor��RowMajor��Ĭ����ColMajor)
        //   3. ���������ͣ�Ĭ��Ϊint��

        // ������Matrix���󣬹��캯������Ϊ����Ĵ�С�����磺
        SparseMatrix<std::complex<float>> mat_c(1000, 2000); // declares a 1000x2000 column-major compressed sparse matrix of complex<float>
        SparseMatrix<double, RowMajor> mat(1000, 2000);      // declares a 1000x2000 row-major compressed sparse matrix of double
        SparseVector<std::complex<float>> vec_c(1000);       // declares a column sparse vector of complex<float> of size 1000
        SparseVector<double, RowMajor> vec(1000);            // declares a row sparse vector of double of size 1000

        // ά������ʹ������ķ�����ã�
        // Standard    dimensions����׼��ά��
        // mat.rows()
        // mat.cols()
        // vec.size()

        // Sizes along the  inner/outer dimensions���ڲ����ⲿά�ȵĴ�С
        // mat.innerSize()
        // mat.outerSize()

        // Number of non zero coefficients������ϵ���ĸ���
        // mat.nonZeros()
        // vec.nonZeros()

        //  ��������ϵ��:
        //������ʵ�ϡ������Ԫ�ؿ���ͨ�������coeffRef(i,j)���ܡ�
        //���ǣ��˹����漰�൱����Ķ������������ڴ��������£�һ����ֻ���������Ԫ�ء�
        //����ͨ�����ⲿ�ߴ��Ͻ��б�׼ѭ����Ȼ��ͨ��InnerIterator�Ե�ǰ�ڲ������ķ���ֵ���е�����ʵ�ֵġ�
        //��ˣ���������洢˳����ͬ��˳����ʷ�����Ŀ������һ�����ӣ�

        {
                SparseMatrix<double> mat(rows, cols);
                for (int k = 0; k < mat.outerSize(); ++k)
                {
                        for (SparseMatrix<double>::InnerIterator it(mat, k); it; ++it)
                        {
                                it.value();
                                it.row();   // row index
                                it.col();   // col index (here it is equal to k)
                                it.index(); // inner index, here it is equal to it.row()
                        }
                }
        }
        //���ڿ�д���ʽ������ʹ��valueRef���������޸Ĳο�ֵ�����ϡ����������������ȡ����ģ���������typename��Ҫ�ؼ�����ָʾInnerIterator��ʾ���ͣ�
}

void FillingASparseMatrix()
{
        //����SparseMatrix������洢���������������µķ�����Ŀʱ�������С�ġ����磬���������������SparseMatrix�ĳɱ�ΪO(nnz)������nnz�Ƿ���ϵ���ĵ�ǰ������

        // ��ˣ���ȷ���������ܵ�ͬʱ����ϡ��������򵥷�����:
        // ���ȹ�����ν����Ԫ���б�Ȼ����ת��ΪSparseMatrix��
        // ����һ�����͵��÷�ʾ����

        // typedef Eigen::Triplet<double> T;
        // std::vector<T> tripletList;
        // tripletList.reserve(estimation_of_entries);
        // for (...)
        // {
        //         // ...
        //         tripletList.push_back(T(i, j, v_ij));
        // }
        // SparseMatrixType mat(rows, cols);
        // mat.setFromTriplets(tripletList.begin(), tripletList.end());
        // mat is ready to go!
}

} // namespace Section1_SparseMatrixManipulations
} // namespace Chapter3_SparseLinearAlgebra
#endif