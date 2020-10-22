#ifndef INPLACE_MATRIX_DECOMPOSITIONS_HPP
#define INPLACE_MATRIX_DECOMPOSITIONS_HPP
#include "HeaderFile.h"
namespace Chapter2_DenseLinearProblemsAndDecompositions
{
//complete pivoting��partial pivoting
// ��1�� complete pivoting����full pivoting���������ھ���ֽ���˹��Ԫ�Ĺ����У���Ԫ����δ���б任�������к���֮�����ѡ��Ҳ������Ҫͬʱ�����н������н�����
// ��2�� partial pivoting����ֻ�ڵ�ǰ���б任������ѡ����Ԫ��ֻ��Ҫ�����н���
namespace Section4_InplaceDecompisitions
{
void InplaceMatrixDecompositions()
{
        LOG();
        // ��Eigen 3.3��ʼ��LU��Cholesky��QR�ֽ���Ծ͵ؽ��в�������ֱ���ڸ�������������ڽ��С�
        //������������������ڴ�ǳ����ޣ�Ƕ��ʽϵͳ��ʱ���˹����ر����á�

        // Ϊ�ˣ�����ʹ��Ref <>��������ʵ���������ֽ��࣬
        //���ұ���ʹ�����������Ϊ����������ֽ������Ϊʾ���������ǿ���partial pivoting��LU�ֽ⡣

        //����һ��2x2���� A:

        MatrixXd A(2, 2);
        A << 2, -1, 1, 3;
        cout << "Here is the input matrix A before decomposition:\n"
             << A << endl;
        // Output is:
        // Here is the input matrix A before decomposition:
        //  2 -1
        //  1  3

        //������֣�Ȼ���������ǵ�Inplace LU����lu���������������A:
        // ���൱�ڰ�A��lu���ˣ����Ժ����м�ʹ����A1��A1������Ҳ����ı�
        PartialPivLU<Ref<MatrixXd>> lu(A);
        cout << "Here is the input matrix A after decomposition:\n"
             << A << endl;

        // Output is:
        // Here is the input matrix A after decomposition:
        //   2  -1
        // 0.5 3.5

        // �����lu������㲢��L��U�����洢�ھ�����������ڴ���A��
        //��ˣ�ϵ��A�ڷֽ�������ѱ��ƻ�������L��U���Ӵ��棬������֤��
        // Ҳ���Ƿֽ�Ľ�������ھ�����
        cout << "Here is the matrix storing the L and U factors:\n"
             << lu.matrixLU() << endl;
        // Output is:
        // Here is the matrix storing the L and U factors:
        //   2  -1
        // 0.5 3.5
        //Ȼ�󣬸�lu�������������һ��ʹ�ã�������Ax = b���⣺
        MatrixXd A0(2, 2);
        A0 << 2, -1, 1, 3;
        VectorXd b(2);
        b << 1, 2;
        VectorXd x = lu.solve(b);
        cout << "Residual: " << (A0 * x - b).norm() << endl;
        // Output is:
        //Residual: 0
        //���������ԭʼ���������A�Ѷ�ʧ��������Ǳ�������һ���¾���A0����֤�����

        //������A��lu֮�乲���ڴ棬����޸ľ���A������lu��Ч��
        //����ͨ���޸ĵ�����A�������ٴν����ʼ������������֤��һ�㣺
        A << 3, 4, -2, 1;
        x = lu.solve(b);
        // Output is:
        //Residual: 15.8114
        //��ע�⣬��û�й���ָ�룬���Ա����������A��lu���й�ͬ�������������û�������

        //���Ҫʹ���޸ĺ��A������ʽ�ֽ⣬�����������һ������compute������
        A0 = A; // save A
        lu.compute(A);
        x = lu.solve(b);
        cout << "Residual: " << (A0 * x - b).norm() << endl;
        // Output is:
        //Residual: 0

        //��ע�⣬����compute������ĸ�lu�������õ��ڴ档
        //��ˣ����ʹ��A1��ͬ�ڵ���һ��������ü��㷽��A��
        //��A1�����޸����ݡ�����ȻA�ǽ����ڴ洢�����L��U���ӵ�����A1�����Ժ����׵���֤���£�
        MatrixXd A1(2, 2);
        A1 << 5, -2, 3, 4;
        lu.compute(A1);
        cout << "Here is the input matrix A1 after decomposition:\n"
             << A1 << endl;
        // Output is:
        // Here is the input matrix A1 after decomposition:
        //  5 -2
        //  3  4

        //����A1�ǲ���ģ���˿������A1 *x = b��ֱ�Ӽ��в�������κθ���A1 :
        x = lu.solve(b);
        cout << "Residual: " << (A1 * x - b).norm() << endl;
        // Output is:
        //Residual: 2.48253e-16

        //����֧�ִ˾�λ���Ƶľ���ֽ��б�
        // class LLT
        // class LDLT
        // class PartialPivLU
        // class FullPivLU
        // class HouseholderQR
        // class ColPivHouseholderQR
        // class FullPivHouseholderQR
        // class CompleteOrthogonalDecomposition
}

} // namespace Section4_InplaceDecompisitions
} // namespace Chapter2_DenseLinearProblemsAndDecompositions

#endif