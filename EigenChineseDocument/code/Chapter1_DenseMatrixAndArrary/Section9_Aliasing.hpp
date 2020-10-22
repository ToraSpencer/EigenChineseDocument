#ifndef ALIASING_HPP
#define ALIASING_HPP
#include "HeaderFile.h"

namespace Chapter1_DenseMatrixAndArrary
{

namespace Section9_Aliasing
{
// ��һ�ڱȽ���
// ��Eigen�У�����(aliasing)��ָ��ͬ�ľ��󣨻�����������������ڸ�ֵ������������Ҳ�ĸ�ֵ���;
// ���磬A = AB ,  a = a^Tb  A=A*A
// ����������ԭ����Eigen���ö�����ֵ
// �����������к��ģ�Ҳ�������޺���,�к��Ļ��������¿��ܲ���ȷ�Ľ�����޺��Ļ������Բ�����ȷ�Ľ��

// �к�����
// ʹ��.eval()���������Խ���������⡣�����˵��.eval()����������ʱ����Ȼ����ִ�и�ֵ����
//  ���Eigen�мٶ��ò����ǻ����ģ���ô�����Զ�ʹ��.eval()������������Ҫ������ʾ����

// �޺����������ǲ���Ҫ����������ϵ�������޺�������������˷��;��������ӷ���

// �������������ʱ��Eigen��ٶ��������(ע�⣬Eigen3.3�Ժ�İ汾����Ҫ����Ŀ������С�Ƿ�ı���)
//�����֪��û�л����������ʹ��noalias()��

// ��������������£�Eigen�ٶ������ڻ�����⣬������ʵ���Ϸ������������������Ľ����
// Ϊ��ֹ���������������ʹ��eval������xxxInPlace��������֮һ��

void Aliasing()
{
        LOG();
        //��Eigen�У�����(aliasing)��ָ��ͬ�ľ��󣨻�����������������ڸ�ֵ������������Ҳ�ĸ�ֵ��䡣
        // ����mat = 2 * mat(��������޺�);��mat = mat.transpose();(�к��Ļ���)��

        MatrixXi mat(3, 3);
        mat << 1, 2, 3, 4, 5, 6, 7, 8, 9;
        cout << "Here is the matrix mat:\n"
             << mat << endl;
        // This assignment shows the aliasing problem
        mat.bottomRightCorner(2, 2) = mat.topLeftCorner(2, 2);
        cout << "After the assignment, mat = \n"
             << mat << endl;

        // Output  is:
        // Here is the matrix mat:
        // 1 2 3
        // 4 5 6
        // 7 8 9
        // After the assignment, mat =
        // 1 2 3
        // 4 1 2
        // 7 4 1

        // �������Ĺؼ����˽������ֵ

        // ���������������������ģ������ǲ������к�����
        // mat.bottomRightCorner��2,2��= mat.topLeftCorner��2,2��;
        // �ø�ֵ���л���aliasing����ϵ��mat(1,1)�ȳ�����mat.bottomRightCorner(2,2)�������Ŀ���mat.topLeftCorner(2,2)���ֳ������Ҳ�Ŀ��С�
        // ��������½ǵģ�2,2����Ӧ����mat(1,1)����ǰ��ֵ5�����ǣ������ʾmat(2,2)ʵ����Ϊ1��
        // ��������Eigenʹ���˶�����ֵ�����������
        // mat��1,1��= mat��0,0��;
        // mat��1,2��= mat��0,1��;
        // mat��2,1��= mat��1,0��;
        // mat��2,2��= mat��1,1��;
        // ��ˣ�mat(2,2)��������ֵmat(1,1)�����Ǿ�ֵ��
        // ����ͨ������eval()���������(ע:eval()����������ʱ������������)
        // ������С����ʱ������Ҳ�ᷢ����
        // ���磬���ʽvec = vec.head(n)��mat = mat.block(i,j,r,c)���л�����

        //ͨ�����ڱ���ʱ�޷���⵽���������mat�ڵ�һ��ʾ�����Դ�һ�㣬��齫�����ص���Ҳ������ֻ������⡣
        //����Eigenȷʵ��������ʱ��⵽һЩ����ʵ����Matrix�������������ᵽ��������ʾ������ʾ����

        // ע�⣺��δ���ᱨ������������

        // Matrix2i a;
        // a << 1, 2, 3, 4;
        // cout << "Here is the matrix a:\n"
        //      << a << endl;
        // a = a.transpose(); // !!! do NOT do this !!!
        // cout << "and the result of the aliasing effect:\n"
        //      << a << endl;

        // �����ʾ����(alising)���⡣
        // ���ǣ�Ĭ������£�Eigenʹ������ʱ��������⵽��������˳�������ʾ������Ϣ
        // void Eigen::DenseBase<Derived>::checkTransposeAliasing(const OtherDerived&) const
        // [with OtherDerived = Eigen::Transpose<Eigen::Matrix<int, 2, 2, 0, 2, 2> >, Derived = Eigen::Matrix<int, 2, 2, 0, 2, 2>]:
        // Assertion `(!internal::check_transpose_aliasing_selector<Scalar,internal::blas_traits<Derived>::IsTransposed,OtherDerived>::run(internal::extract_data(derived()), other))
        // && "aliasing detected during transposition, use transposeInPlace() or evaluate the rhs into a temporary using .eval()"' failed.

        //�û�����ͨ������EIGEN_NO_DEBUG�����ر�Eigen������ʱ����
}

void ResolvingAliasingIssues()
{
        LOG();
        //���������Eigen���뽫�Ҳ���ȫ����һ����ʱ����/���飬Ȼ����������ࡣ
        //����**eval()**������������,����Ϊ����һ����ʱ����
        MatrixXi mat(3, 3);
        mat << 1, 2, 3, 4, 5, 6, 7, 8, 9;
        cout << "Here is the matrix mat:\n"
             << mat << endl;
        // The eval() solves the aliasing problem
        mat.bottomRightCorner(2, 2) = mat.topLeftCorner(2, 2).eval();
        cout << "After the assignment, mat = \n"
             << mat << endl;

        //��ͬ�Ľ������Ҳ�����ڵڶ�ʾ���У���ת�ã�ֻ�������a = a.transpose();��a = a.transpose().eval();�����ǣ������ֳ�������£��и��õĽ��������
        //Eigen�ṩ��ר�ú���transposeInPlace()���ú���ͨ����ת�����滻����������ʾ��
        MatrixXf a(2, 3);
        a << 1, 2, 3, 4, 5, 6;
        cout << "Here is the initial matrix a:\n"
             << a << endl;
        a.transposeInPlace();
        cout << "and after being transposed:\n"
             << a << endl;
             
        //���xxxInPlace()�������ã������ʹ��������Ϊ�����Ը������ָʾ��������ʲô��
        //��Ҳ������Eigen�������ؽ����Ż�����Щ���ṩ��һЩxxxInPlace()������
        // Original function	                      In-place function
        // MatrixBase::adjoint()	          MatrixBase::adjointInPlace()
        // DenseBase::reverse()	                 DenseBase::reverseInPlace()
        // LDLT::solve()	                            LDLT::solveInPlace()
        // LLT::solve()	                                      LLT::solveInPlace()
        // TriangularView::solve()	        TriangularView::solveInPlace()
        // DenseBase::transpose()	       DenseBase::transposeInPlace()

        //����������£����������ʹ�����Ƶı��ʽ��Сvec = vec.head(n)�������ʹ��conservativeResize()��
}

void AliasingAndComponentWiseOperations()
{
        LOG();
        //���ͬһ���������ͬʱ�����ڸ�ֵ������������Ҳ࣬����ܺ�Σ�գ����ͨ���б�Ҫ��ʾ�������Ҳ�
        //���ǣ�Ӧ�û���Ԫ�صĲ������������ӷ��������˷�������˷����ǰ�ȫ�ġ�
        //����ʾ�������л�������Ĳ�������ˣ���ʹ��ͬ�ľ�������ڸ�ֵ���ŵ����࣬Ҳ����Ҫeval()��
        MatrixXf mat(2, 2);
        mat << 1, 2, 4, 7;
        cout << "Here is the matrix mat:\n"
             << mat << endl
             << endl;
        mat = 2 * mat;
        cout << "After 'mat = 2 * mat', mat = \n"
             << mat << endl
             << endl;
        mat = mat - MatrixXf::Identity(2, 2);
        cout << "After the subtraction, it becomes\n"
             << mat << endl
             << endl;
        ArrayXXf arr = mat;
        arr = arr.square();
        cout << "After squaring, it becomes\n"
             << arr << endl
             << endl;
        // Combining all operations in one statement:
        mat << 1, 2, 4, 7;
        mat = (2 * mat - MatrixXf::Identity(2, 2)).array().square();
        cout << "Doing everything at once yields\n"
             << mat << endl
             << endl;
        // Output is:
        // Here is the matrix mat:
        // 1 2
        // 4 7

        // After 'mat = 2 * mat', mat =
        //  2  4
        //  8 14

        // After the subtraction, it becomes
        //  1  4
        //  8 13

        // After squaring, it becomes
        //   1  16
        //  64 169

        // Doing everything at once yields
        //   1  16
        //  64 169
        //ͨ����������ʽ�Ҳ�ģ�i��j����Ŀ��ȡ���������������ģ�i��j����Ŀ
        //���������������κα��ʽ����ֵ�ǰ�ȫ�ġ�����������£�������ʾ�������Ҳ�(.evl())��
}

void AliasingAndMatrixMultiplication()
{
        LOG();

        //��Ŀ�����**δ������С**������£�����˷���Eigen��Ψһ�ٶ�Ĭ�������Ϊ�����ġ�
        // ���ٶ����������ʹ��eval()������ʱ����,�����ǰ�ȫ�ġ�
        //��ˣ����matA��ƽ������������matA = matA * matA�ǰ�ȫ�ġ�
        //Eigen�е����������������ٶ�û�л������⣬������Ϊ�����������˲�ͬ�ľ��󣬻�����Ϊ�������Ԫ�صĲ�����
        {
                MatrixXf matA(2, 2);
                matA << 2, 0, 0, 2;
                matA = matA * matA;
                cout << matA << endl;
        }

        // ���ǣ������д��۵ġ�ִ�б��ʽʱmatA = matA * matA
        // Eigen���ڼ�������ʱ������������ֵ��matA�ĳ˻���
        //��Ȼ���ԣ������ڽ��˻������������������matB = matA * matA��ʱ��Eigen��ִ����ͬ�Ĳ�����
        //����������£�ֱ������matB,
        // �������Ƚ�matA*matA������ʱ����Ȼ��������ʱ���������ʱ����ֵ������matB����Ч
        //���ǿ���ʹ��noalias����ָʾû�л�����������ʾ��matB.noalias() = matA * matA��
        //��ʹEigen����matA * matAֱ�ӽ�����˻���matB��������
        {
                MatrixXf matA(2, 2), matB(2, 2);
                matA << 2, 0, 0, 2;
                // Simple but not quite as efficient
                matB = matA * matA;
                cout << matB << endl;
                // More complicated but also more efficient
                matB.noalias() = matA * matA;
                cout << matB << endl;
                // Output is:
                //4 0
                // 0 4

                // 4 0
                // 0 4
        }

        {
                //��Ȼ����Ӧ����ʵ���Ϸ�������ʱʹ��noalias()���������������**����**��õ�����Ľ����
                //�������ҵ�ƽ̨��û����
                MatrixXf matA(2, 2);
                matA << 2, 0, 0, 2;
                matA.noalias() = matA * matA;
                cout << matA << endl;
                // Output is:
                //4 0
                // 0 4
        }

        {
                //���⣬��Eigen 3.3 ��ʼ��
                //���������Ŀ�����Ĵ�С(ע�⣬�����еĲ����ٶ�Ŀ������С����)
                //����δ���˻�ֱ�ӷ����Ŀ�꣬�򲻼ٶ���������ˣ�����ʾ��Ҳ�Ǵ���ģ�
                MatrixXf A(2, 2), B(3, 2);
                B << 2, 0, 0, 3, 1, 1;
                A << 2, 0, 0, -2;
                A = (B * A).cwiseAbs(); // ���ڲ��ٶ�������������Ҫ������ʾ����
                cout << A << endl;
                //�������ҵ�ƽ̨��û����
                // Output is
                // 4 0
                // 0 6
                // 2 2
        }

        {
                //�����κλ������⣬��������ͨ���ڸ�ֵ֮ǰ��ʽ�������ʽ���������
                MatrixXf A(2, 2), B(3, 2);
                B << 2, 0, 0, 3, 1, 1;
                A << 2, 0, 0, -2;
                A = (B * A).eval().cwiseAbs();
                cout << A << endl;

                // Output is
                // 4 0
                // 0 6
                // 2 2
        }
}

} // namespace Section9_Aliasing
} // namespace Chapter1_DenseMatrixAndArrary

#endif