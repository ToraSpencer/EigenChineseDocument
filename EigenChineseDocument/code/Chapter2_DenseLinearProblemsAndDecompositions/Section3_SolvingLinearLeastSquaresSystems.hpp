#ifndef SOLVING_LINEAR_LEAST_SQUARES_SYSTEMS_HPP
#define SOLVING_LINEAR_LEAST_SQUARES_SYSTEMS_HPP
#include "HeaderFile.h"
namespace Chapter2_DenseLinearProblemsAndDecompositions
{

namespace Section3_SolvingLinearLeastSquaresSystems
{
// ��ҳ�������ʹ�ñ������������С����ϵͳ��һ�����������飬����Ax = b��û�н⡣
//����������£��ڲ���Ax - b������С�������ϣ�������ӽ��������x��������ġ�
//��x��Ϊ��С���˽⣨���ʹ��ŷ����÷�������
//��ҳ���۵����ַ�����SVD�ֽ⣬QR�ֽ����̬���̡�
//���У�SVD�ֽ�ͨ����׼ȷ�����������򷽳�(normal equations)��쵫�׼ȷ��QR�ֽ��������֮�䡣

void UsingTheSvdDecomposition()
{
        LOG();
        //BDCSVD���е�solve()�з�������ֱ���������������С����ϵͳ��
        //����������ֵ�������Ĭ��ֵ���ǲ����ġ�������Ҫ����ʸ��������ϡ��SVD�ֽ����Լ�����С���˽⣺
        MatrixXf A = MatrixXf::Random(3, 2);
        cout << "Here is the matrix A:\n"
             << A << endl;
        VectorXf b = VectorXf::Random(3);
        cout << "Here is the right hand side b:\n"
             << b << endl;
        cout << "The least-squares solution is:\n"
             << A.bdcSvd(ComputeThinU | ComputeThinV).solve(b) << endl;
        // Output is:
        // Here is the matrix A:
        //   0.68  0.597
        // -0.211  0.823
        //  0.566 -0.605
        // Here is the right hand side b:
        //  -0.33
        //  0.536
        // -0.444
        // The least-squares solution is:
        // -0.67
        // 0.314
}
void UsingTheQRDecomposition()
{
        LOG();
        //QR�ֽ����е�resolve()������������С���˽⡣
        //��3��QR�ֽ��ࣺHouseholderQR����pivoting����˿��ٵ����ȶ�����ColPivHouseholderQR�������ᣬ��˽�������׼ȷ����FullPivHouseholderQR��ȫ���ᣬ������������ȶ�����
        MatrixXf A = MatrixXf::Random(3, 2);
        VectorXf b = VectorXf::Random(3);
        cout << "The solution using the QR decomposition is:\n"
             << A.colPivHouseholderQr().solve(b) << endl;
        // Output is:
        // The solution using the QR decomposition is:
        // -0.67
        // 0.314
}

void UsingNormalEquations()
{
        LOG();
        //�ҵ�Ax = b����С���˽��Ч����ⷨ�߷���A T Ax = A T b��
        //�������A�ǲ�̬�ģ���ô�ⲻ��һ���÷�������ΪA T A����������A����������ƽ����
        //����ζ����ʹ������������ȣ�ʹ�����򷽳�ʽ��ʧ������Ҫ��������
        MatrixXf A = MatrixXf::Random(3, 2);
        VectorXf b = VectorXf::Random(3);
        cout << "The solution using normal equations is:\n"
             << (A.transpose() * A).ldlt().solve(A.transpose() * b) << endl;
}
} // namespace Section3_SolvingLinearLeastSquaresSystems
} // namespace Chapter2_DenseLinearProblemsAndDecompositions

#endif