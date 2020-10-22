#ifndef REDUCTIONS_VISITORS_BROADCASTING_HPP
#define REDUCTIONS_VISITORS_BROADCASTING_HPP
#include "HeaderFile.h"
//http://eigen.tuxfamily.org/dox/group__TutorialReductionsVisitorsBroadcasting.html

namespace Chapter1_DenseMatrixAndArrary
{
namespace Section6_ReductionsVisitorsBroadcasting
{

void Reductions()
{
        LOG();
        //��Eigen�У�Լ����һ�����þ�������鲢���ص�������ֵ�ĺ�������õĹ�Լ����֮һ��.sum�����������ظ������������������ϵ�����ܺ͡�
        Eigen::Matrix2d mat;
        mat << 1, 2,
            3, 4;
        cout << "Here is mat.sum():       " << mat.sum() << endl;
        cout << "Here is mat.prod():      " << mat.prod() << endl;
        cout << "Here is mat.mean():      " << mat.mean() << endl;
        cout << "Here is mat.minCoeff():  " << mat.minCoeff() << endl;
        cout << "Here is mat.maxCoeff():  " << mat.maxCoeff() << endl;
        cout << "Here is mat.trace():     " << mat.trace() << endl;
}

void NormComputations()
{
        LOG();
        // 2������ƽ������ͨ��squaredNorm()��á����������ʸ���ĵ�������ҵ�Ч����ϵ����ƽ������ֵ���ܺ͡�
        //  norm������������squaredNorm������ƽ������
        // ��Щ����Ҳ�����ھ��������㡣����������£�n��p������Ϊ��С��n * p����������
        // ��ˣ�����norm()�������ء� Frobenius���� Hilbert-Schmidt��������
        // ���Ǳ���̸��l^2����ķ�������Ϊ�ǿ�����ζ�Ų�ͬ�����顣
        // �����Ҫ������ϵ�������l^p��������ʹ��lpNorm <p>()��
        // �����Ҫ���������ģ�����p���Բ�������ֵInfinity������ϵ������ֵ�����ֵ��
        VectorXf v(2);
        MatrixXf m(2, 2), n(2, 2);
        v << -1,
            2;

        m << 1, -2,
            -3, 4;
        // ��������
        cout << "v.squaredNorm() = " << v.squaredNorm() << endl;
        cout << "v.norm() = " << v.norm() << endl;
        cout << "v.lpNorm<1>() = " << v.lpNorm<1>() << endl;
        cout << "v.lpNorm<Infinity>() = " << v.lpNorm<Infinity>() << endl;
        cout << endl;
        // ������
        cout << "m.squaredNorm() = " << m.squaredNorm() << endl;
        cout << "m.norm() = " << m.norm() << endl;
        cout << "m.lpNorm<1>() = " << m.lpNorm<1>() << endl;
        cout << "m.lpNorm<Infinity>() = " << m.lpNorm<Infinity>() << endl;

        // Ҳ���Լ�����1�����������
        MatrixXf mat(2, 2);
        mat << 1, -2,
            -3, 4;
        cout << "1-norm(mat)     = " << mat.cwiseAbs().colwise().sum().maxCoeff()
             << " == " << mat.colwise().lpNorm<1>().maxCoeff() << endl;
        cout << "infty-norm(mat) = " << mat.cwiseAbs().rowwise().sum().maxCoeff()
             << " == " << mat.rowwise().lpNorm<1>().maxCoeff() << endl;
}

void BooleanReductions()
{
        LOG();
        // ���������������룬�򣬸����ķ���
        // all() returns true if all of the coefficients in a given Matrix or Array evaluate to true .
        // any() returns true if at least one of the coefficients in a given Matrix or Array evaluates to true .
        // count() returns the number of coefficients in a given Matrix or Array that evaluate to true.
        ArrayXXf a(2, 2);

        a << 1, 2,
            3, 4;
        cout << "(a > 0).all()   = " << (a > 0).all() << endl;
        cout << "(a > 0).any()   = " << (a > 0).any() << endl;
        cout << "(a > 0).count() = " << (a > 0).count() << endl;
        cout << endl;
        cout << "(a > 2).all()   = " << (a > 2).all() << endl;
        cout << "(a > 2).any()   = " << (a > 2).any() << endl;
        cout << "(a > 2).count() = " << (a > 2).count() << endl;
}

void Visitors()
{
        LOG();
        // �����ھ�������������Ԫ����
        //��Ҫ���һ��ϵ����Matrix��Array�е�λ��ʱ�������ߺ����á�
        //��򵥵�ʾ����maxCoeff����x����y����minCoeff����x����y���������ڲ���Matrix��Array��������Сϵ����λ�á�
        //���ݸ������ߵĲ�����ָ��Ҫ�洢�к���λ�õı�����ָ�롣��Щ����ӦΪIndex���ͣ�

        Eigen::MatrixXf m(2, 2);

        m << 1, 2,
            3, 4;
        //get location of maximum
        MatrixXf::Index maxRow, maxCol;
        float max = m.maxCoeff(&maxRow, &maxCol);
        //get location of minimum
        MatrixXf::Index minRow, minCol;
        float min = m.minCoeff(&minRow, &minCol);
        cout << "Max: " << max << ", at: " << maxRow << "," << maxCol << endl;
        cout << "Min: " << min << ", at: " << minRow << "," << minCol << endl;
}

void PartialReductions()
{
        LOG();
        // �����ھ�������������������������
        // ��ס,element-wise�ǰ�Ԫ�صģ���ôcolwise()��rowwise()��ʾ���л��е�
        //���ֹ�Լ�ǿ�����Matrix��Array�ϰ��л��в����Ĺ�Լ����ÿ���л���Ӧ�ù�Լ���㲢���ؾ�����Ӧֵ���л���������
        //��������������colwise������rowwise����
        //һ���򵥵�ʾ���ǻ�ȡ����������ÿһ����Ԫ�ص����ֵ����������洢���������У�
        // column-wise������������row-wise������������ɶ��˼��Ӧ����Ƶײ�������Ժ��ٿ�   ******TODO*******
        //ע�⣺ column-wise operations return a row vector, while row-wise operations return a column vector.
        Eigen::MatrixXf mat(2, 4);
        mat << 1, 2, 6, 9,
            3, 1, 7, 2;

        std::cout << "Column's maximum: " << std::endl
                  << mat.colwise().maxCoeff() << std::endl; // ���ھ���mat��ÿһ�У�ȡ���ϵ��ֵ

        // Ҳ���Զ��в���
        std::cout << "Row's maximum: " << std::endl
                  << mat.rowwise().maxCoeff() << std::endl; // ���ھ���mat��ÿһ�У�ȡ���ϵ��ֵ
}

void CombiningPartialReductionsWithOtherOperations()
{
        LOG();

        MatrixXf mat(2, 4);
        mat << 1, 2, 6, 9,
            3, 1, 7, 2;

        MatrixXf::Index maxIndex;
        float maxNorm = mat.colwise().sum().maxCoeff(&maxIndex); //  ���ھ����ÿһ���е�Ԫ����ͣ���������ϵ���ڵ�2��

        std::cout << "Maximum sum at position " << maxIndex << std::endl;
        std::cout << "The corresponding vector is: " << std::endl;
        std::cout << mat.col(maxIndex) << std::endl;
        std::cout << "And its sum is is: " << maxNorm << std::endl;
        // Output is :
        //Maximum sum at position 2
        // The corresponding vector is:
        // 6
        // 7
        // And its sum is is: 13
}

void Broadcasting()
{
        LOG();
        //�㲥����ĸ��������ڲ��ֹ�Լ���������ڹ㲥������һ�����ʽ�������������л��У�ͨ����һ�������ϸ��ƶ�������Ϊ����
        //һ���򵥵�ʾ���ǽ�ĳ����������ӵ������е�ÿһ�С������ͨ�����·�ʽ��ɣ�
        Eigen::MatrixXf mat(2, 4);
        Eigen::VectorXf v(2);
        mat << 1, 2, 6, 9,
            3, 1, 7, 2;
        v << 0,
            1;

        //add v to each column of m
        //mat.colwise() += v�����ֵ�Ч�ķ�ʽ����ָ�
        //�����������v�������ÿһ�С����ߣ����Խ������Ϊ�ظ�����v�Ĵ����γ��ĳ˶�����Ȼ����ӵ�mat
        mat.colwise() += v;

        std::cout << "Broadcasting result: " << std::endl;
        std::cout << mat << std::endl;

        // Output is:
        // Broadcasting result:
        // 1 2 6 9
        // 4 2 8 3

        // �ھ����ϣ����ǿ���ִ��-=,+=,+,-���������ǲ��ܽ���*=,/=,*,/����
        // �����������ǿ�ִ��*=,/=,*,/����
        // If you want multiply column 0 of a matrix mat with v(0), column 1 with v(1), and so on, then use mat = mat * v.asDiagonal().
        // Ҫ���л�������ӵ���������ΪVector���ͣ����Ҳ���ΪMatrix��
        // ��������㣬�����ֱ���ʱ����
        //��Ҳ��ζ�ţ���ʹ��Matrix���в���ʱ���㲥����ֻ��Ӧ����Vector���͵Ķ�����ͬ��������������VectorXf��ArrayXf��������һ��������Ӧ��ͬһ���ʽ�л��ʹ������;���

        // ͬ����Ҳ���Զ���ִ�д˲���
        {
                Eigen::MatrixXf mat(2, 4);
                Eigen::VectorXf v(4);

                mat << 1, 2, 6, 9,
                    3, 1, 7, 2;

                v << 0, 1, 2, 3;

                //add v to each row of m
                mat.rowwise() += v.transpose();

                std::cout << "Broadcasting result: " << std::endl;
                std::cout << mat << std::endl;

                //  Broadcasting result:
                //  1  3  8 12
                //  3  2  9  5
        }
}

void CombiningBroadcastingWithOtherOperations()
{
        LOG();
        // �㲥�����������������������������в���������Լ�Ͳ��ֹ�Լ���ϡ�
        //�����Ѿ������˹㲥��Լ��Ͳ���Լ�����ǿ��������о�һ�����߼���ʾ������ʾ��v�ھ���������ҵ������������m��
        //ŷ����¾��뽫�ڱ�ʾ����ʹ�ã�������в��ֹ�Լ��ΪsquaredNorm()��ƽ��ŷ����¾��룺
        Eigen::MatrixXf m(2, 4);
        Eigen::VectorXf v(2);

        m << 1, 23, 6, 9,
            3, 11, 7, 2;

        v << 2,
            3;
        MatrixXf::Index index;
        // find nearest neighbour
        (m.colwise() - v).colwise().squaredNorm().minCoeff(&index);
        cout << "Nearest neighbour is column " << index << ":" << endl;
        cout << m.col(index) << endl;
}
} // namespace Section6_ReductionsVisitorsBroadcasting
} // namespace Chapter1_DenseMatrixAndArrary
#endif