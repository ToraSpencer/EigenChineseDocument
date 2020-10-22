#ifndef LINEAR_ALGEBRA_AND_DECOMPOSITIONS_HPP
#define LINEAR_ALGEBRA_AND_DECOMPOSITIONS_HPP
#include "HeaderFile.h"
namespace Chapter2_DenseLinearProblemsAndDecompositions
{

namespace Section1_LinearAlgebraAndDecompositions
{
//��ҳ˵��������������ϵͳ��������ַֽ⣬����LU��QR��SVD�������ֽ�...�Ķ���ҳ���벻Ҫ������ǵ��ܼ�����ֽ�Ŀ¼��
//����������� Ax=b
//�ý���������ɽ����ַֽ�֮�����ѡ��ȡ������ľ���һ�����ӣ�ȡ�������Ƿ��޳��ٶȻ�׼ȷ�ԡ�
//���ǣ������Ǵ�һ�����������������ʾ����ʼ������һ���ܺõ����Է�����
void BasicLinearSolving()
{
        LOG();
        Matrix3f A;
        Vector3f b;
        A << 1, 2, 3, 4, 5, 6, 7, 8, 10;
        b << 3, 3, 4;
        cout << "Here is the matrix A:\n"
             << A << endl;
        cout << "Here is the vector b:\n"
             << b << endl;
        Vector3f x = A.colPivHouseholderQr().solve(b);
        cout << "The solution is:\n"
             << x << endl;

        // Output is:
        // Here is the matrix A:
        //  1  2  3
        //  4  5  6
        //  7  8 10
        // Here is the vector b:
        // 3
        // 3
        // 4
        // The solution is:
        // -2
        //  1
        //  1

        //�ڴ�ʾ���У�colPivHouseholderQr��������������ColPivHouseholderQR�Ķ���
        //���ڴ˴��ľ�������ΪMatrix3f����˸��п������滻Ϊ��
        //ColPivHouseholderQR <Matrix3f> dec��A��;
        //Vector3f x = dec.solve��b��;
        //�����ColPivHouseholderQR�Ǿ���ѡ������Ԫ���ܵ�QR�ֽ⡣
        //���Ǳ��̵̳�һ����������Է�������Ϊ�����������о��󣬶����ٶȷǳ��졣
        //����һЩ�����ֽ�������Ը��ݾ����Ҫ���е�Ȩ��ѡ��

        // Decomposition	Method	                Requirements on the matrix	                        Speed(small-to-medium)	                Speed (large)	                Accuracy
        // PartialPivLU	         partialPivLu()	                    Invertible	                                                                        ++	                                                ++	                                        +
        // FullPivLU	                fullPivLu()	                        None	                                                                            -	                                                     - -	                                   +++
        // HouseholderQR	householderQr()	              None	                                                                        ++	                                                ++                                              +
        // ColPivHouseholderQR	colPivHouseholderQr()	None	                                                                +	                                                     -	                                           +++
        // FullPivHouseholderQR	fullPivHouseholderQr()	None                                                            	-	                                                    - -	                                                +++
        // CompleteOrthogonalDecomposition	completeOrthogonalDecomposition()	None	+	-	+++
        // LLT	llt()	                                                                Positive definite	                                                                +++	+++	+
        // LDLT	ldlt()	                                        Positive or negative semidefinite	                                                +++	+	++
        // BDCSVD	bdcSvd()	None	-	-	+++
        // JacobiSVD	jacobiSvd()	None	-	- - -	+++

        {
                //������Щ�ֽⶼ�ṩ��һ��solve�����������÷���������ʾ��һ����
                //���磬������ľ����������ģ���??�ϱ�˵��LLT��LDLT�ֽ���һ���ܺõ�ѡ������һ��ʾ����Ҳ˵��ʹ��ͨ�þ��󣨶���ʸ������Ϊ���ֱ��ǿ��ܵġ�
                Matrix2f A, b;
                A << 2, -1, -1, 3;
                b << 1, 2, 3, 1;
                cout << "Here is the matrix A:\n"
                     << A << endl;
                cout << "Here is the right hand side b:\n"
                     << b << endl;
                Matrix2f x = A.ldlt().solve(b);
                cout << "The solution is:\n"
                     << x << endl;
                //Output is:
                // Here is the matrix A:
                //  2 -1
                // -1  3
                // Here is the right hand side b:
                // 1 2
                // 3 1
                // The solution is:
                // 1.2 1.4
                // 1.4 0.8

                // Eigen ����ֽ⣺http://eigen.tuxfamily.org/dox/group__TopicLinearAlgebraDecompositions.html
        }
}

void CheckingIfASolutionReallyExists()
{
        LOG();
        //����������ķ���
        //ֻ����֪��Ҫ��������������Ϊ��Ч����Χ����ˣ�Eigen�������Լ����д˼��㣬������ʾ����ʾ��
        MatrixXd A = MatrixXd::Random(100, 100);
        MatrixXd b = MatrixXd::Random(100, 50);
        MatrixXd x = A.fullPivLu().solve(b);
        double relative_error = (A * x - b).norm() / b.norm(); // norm() is L2 norm
        cout << "The relative error is:\n"
             << relative_error << endl;
        // Output is:
        // The relative error is:
        // 2.31495e-14
}

void ComputingEigenvaluesAndEigenvectors()
{
        LOG();
        //����Ҫ�ڴ˴����������ֽ⣬ ȷ���������Ƿ����԰���ģ�
        //����ѧ�������һ������ά���ڻ��ռ䣬һ���԰�����(self-adjoint operator)�����Լ��İ������ӣ��ȼ۵�˵������԰����ӵľ����ǰ������ؾ��󡣰������ؾ�������Լ��Ĺ���ת�á���������ά���׶����ض�������һ��������һ�������Ա���԰�����Ϊһ��ʵֵ�ĶԽǾ���
        // ��������Щ�����о�������������������һ��ʹ��SelfAdjointEigenSolver��ʾ��������ʹ��EigenSolver��ComplexEigenSolver���ɵؽ���Ӧ����һ�����
        //����ֵ�����������ļ��㲻һ����������������������ʧ�ܵ�������١�����info��������Ϊ�˼�����ֿ����ԡ�
        Matrix2f A;
        A << 1, 2, 2, 3;
        cout << "Here is the matrix A:\n"
             << A << endl;
        SelfAdjointEigenSolver<Matrix2f> eigensolver(A);
        if (eigensolver.info() != Success)
                abort();
        cout << "The eigenvalues of A are:\n"
             << eigensolver.eigenvalues() << endl;
        cout << "Here's a matrix whose columns are eigenvectors of A \n"
             << "corresponding to these eigenvalues:\n"
             << eigensolver.eigenvectors() << endl;
        //Output is:
        // Here is the matrix A:
        // 1 2
        // 2 3
        // The eigenvalues of A are:
        // -0.236
        //   4.24
        // Here's a matrix whose columns are eigenvectors of A
        // corresponding to these eigenvalues:
        // -0.851 -0.526
        //  0.526 -0.851
}

void ComputingInverseAndDeterminant()
{
        LOG();
        //���ȣ���ȷ����ȷʵ��Ҫ����������������ʽ�ǻ�������ѧ���������ֵ���Դ����У����ǲ����ڴ���ѧ�����С�
        //�����ͨ��������solve�����������棬������ʽͨ�����Ǽ������Ƿ����ĺ÷�����
        //���ǣ����ڷǳ� С�ľ������������ǲ���ȷ�ģ������������ʽ���ܷǳ����á�
        //����ĳЩ�ֽ⣨����PartialPivLU��FullPivLU���ṩ��inverse������determinant����������
        //����Ҳ����ֱ���ھ����ϵ���inverse������determinant������
        //�������Ĺ̶���С��С�����Ϊ4x4�����⽫ʹEigen����ִ��LU�ֽ⣬��Ӧʹ�öԴ���С�������Ч�Ĺ�ʽ��
        Matrix3f A;
        A << 1, 2, 1,
            2, 1, 0,
            -1, 1, 2;
        cout << "Here is the matrix A:\n"
             << A << endl;
        cout << "The determinant of A is " << A.determinant() << endl;
        cout << "The inverse of A is:\n"
             << A.inverse() << endl;

        // Output is:
        // Here is the matrix A:
        //  1  2  1
        //  2  1  0
        // -1  1  2
        // The determinant of A is -3
        // The inverse of A is:
        // -0.667      1  0.333
        //   1.33     -1 -0.667
        //     -1      1      1
}

void LeastSquaresSolving()
{
        LOG();
        //��С����������׼ȷ������SVD�ֽ⡣Eigen�ṩ������ʵ�֡�
        //�Ƽ��Ķ�����BDCSVD�࣬�����Ժܺõؽ���ϴ�����⣬���Զ��˻ص�JacobiSVD���Խ����С�����⡣
        //�����������࣬���ǵ�resolve�����������ڽ�����С������⡣

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
        //���ܸ��쵫�ɿ��Խϵ͵���һ�ַ�����ʹ�þ����Cholesky�ֽ��QR�ֽ⡣���ǹ�����С���˷�����ҳ���и�����ϸ��Ϣ��
}

void SeparatingTheComputationFromTheConstruction()
{
        LOG();
        // ������ʾ���У��ڹ���ֽ�����ͬʱ�����˷ֽ⡣���ǣ���ĳЩ����£�������ϣ�����������·ֿ���
        //���磬����ڹ���ʱ��֪��Ҫ�ֽ�ľ�������ܻ���Ҫ�����Ƿֿ������������������еķֽ����
        // ʹ֮��Ϊ���ܵ�ԭ���ǣ�
        // ���зֽⶼ��Ĭ�ϵĹ��캯����
        // ���зֽⶼ����ִ�м����compute��matrix�����������ҿ������Ѽ���ķֽ����ٴε��ø÷������Խ������³�ʼ����
        Matrix2f A, b;
        LLT<Matrix2f> llt;
        A << 2, -1, -1, 3;
        b << 1, 2, 3, 1;
        cout << "Here is the matrix A:\n"
             << A << endl;
        cout << "Here is the right hand side b:\n"
             << b << endl;
        cout << "Computing LLT decomposition..." << endl;
        llt.compute(A);
        cout << "The solution is:\n"
             << llt.solve(b) << endl;
        A(1, 1)
        ++;
        cout << "The matrix A is now:\n"
             << A << endl;
        cout << "Computing LLT decomposition..." << endl;
        llt.compute(A);
        cout << "The solution is now:\n"
             << llt.solve(b) << endl;
        //��������Ը��߷ֽ⹹�캯��Ԥ�ȷ���洢�ռ��Էֽ������С�ľ����Ա������ֽ�������ʱ����ִ�ж�̬�ڴ���䣨��Ȼ�������ʹ�õ��ǹ̶���С�ľ����򲻴��ڶ�̬�ڴ������ȫ��������
        //ֻ�轫��С���ݸ��ֽ⹹�캯��������ɣ�������ʾ����ʾ��
        {
                HouseholderQR<MatrixXf> qr(50, 50);
                MatrixXf A = MatrixXf ::Random(50, 50);
                qr.compute(A); //û�ж�̬�ڴ����
        }
}
void RankRevealingDecompositions()
{
        LOG();
        //ĳЩ�ֽ��ǽ�ʾ�����ȵġ�
        //��Щͨ��Ҳ���ڷ����Ⱦ����ڷ�������±�ʾ������󣩵�����±�����ѵķֽ⡣
        //�Ƚ�ʾ�ֽ������ṩ��rank()���������ǻ������ṩ����ķ���������isInvertible()��
        //���һ��ṩһЩ�������������ĺˣ���ռ䣩�����пռ䣩������FullPivLU������
        Matrix3f A;
        A << 1, 2, 5,
            2, 1, 4,
            3, 0, 3;
        cout << "Here is the matrix A:\n"
             << A << endl;
        FullPivLU<Matrix3f> lu_decomp(A);
        cout << "The rank of A is " << lu_decomp.rank() << endl;
        cout << "Here is a matrix whose columns form a basis of the null-space of A:\n"
             << lu_decomp.kernel() << endl;
        cout << "Here is a matrix whose columns form a basis of the column-space of A:\n"
             << lu_decomp.image(A) << endl; // yes, have to pass the original A

        // Output is:
        // Here is the matrix A:
        // 1 2 5
        // 2 1 4
        // 3 0 3
        // The rank of A is 2
        // Here is a matrix whose columns form a basis of the null-space of A:
        //  0.5
        //    1
        // -0.5
        // Here is a matrix whose columns form a basis of the column-space of A:
        // 5 1
        // 4 2
        // 3 3

        //��Ȼ���κ��ȼ��㶼ȡ���ڶ�������ֵ��ѡ����Ϊʵ����û�и������ǡ�����Ȳ���ġ�
        //Eigenѡ��һ�����ǵ�Ĭ����ֵ������ֵȡ���ڷֽ⣬��ͨ���ǶԽ��ߴ�С���Ի����š�
        //��Ȼ�������ǿ���ѡ������Ĭ��ֵ����ֻ����֪������Ӧ�ó������ȷ��ֵ�Ƕ��١�
        //������ͨ���ڵ���rank��������Ҫʹ�ô���ֵ���κ���������֮ǰ�ڷֽ�����ϵ���setThreshold�������������á�
        //�ֽⱾ����compute��������������ֵ�޹ء�������ֵ���������¼���ֽ�.
        {
                Matrix2d A;
                A << 2, 1,
                    2, 0.9999999999;
                FullPivLU<Matrix2d> lu(A);
                cout << "By default, the rank of A is found to be " << lu.rank() << endl;
                lu.setThreshold(1e-5);
                cout << "With threshold 1e-5, the rank of A is found to be " << lu.rank() << endl;

                // Output is:
                // By default, the rank of A is found to be 2
                // With threshold 1e-5, the rank of A is found to be 1
        }
}

} // namespace Section1_LinearAlgebraAndDecompositions
} // namespace Chapter2_DenseLinearProblemsAndDecompositions

#endif