#ifndef ARRAY_AND_COEFFICIENTWISE_OPERATIONS_HPP
#define ARRAY_AND_COEFFICIENTWISE_OPERATIONS_HPP
#include "HeaderFile.h"

// http://eigen.tuxfamily.org/dox/group__TutorialArrayClass.html

namespace Chapter1_DenseMatrixAndArrary
{

// ���������Դ�����Matrix���෴��Array���ṩ��ͨ�����顣
// ���⣬Array���ṩ��һ��ִ����ϵ������ļ�㷽�������������û�����Դ������壬
// ���罫������ӵ������е�ÿ��ϵ����ϵ�����������顣

// Array<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>

// Eigen��ΪĳЩ��������ṩ��typedef���䷽ʽ������Matrix typedef������һЩϸ΢�Ĳ���
// ��Ϊ���ʡ� array��������һά���飬Ҳ���ڶ�ά����.

//**һά����**����ArrayNt��ʽ��typedef��������N��t�Ǵ�С�ͱ�������

// **��ά����**����ArrayNNt��ʽ��typedef
// Type	                                                        Typedef
// Array<float,Dynamic,1>                   ArrayXf
// Array<float,3,1>                                            Array3f
// Array<double,Dynamic,Dynamic>        ArrayXXd
// Array<double,3,3>                                            Array33d

namespace Section3_ArrayAndCoefficientwiseOperations
{

void AccessingValuesInsideAnArray()
{
        LOG();
        ArrayXXf m(2, 2); // ��ά��̬float��������

        // assign some values coefficient by coefficient
        m(0, 0) = 1.0;
        m(0, 1) = 2.0;
        m(1, 0) = 3.0;
        m(1, 1) = m(0, 1) + m(1, 0);

        // print values to standard output
        cout << m << endl
             << endl;

        // using the comma-initializer is also allowed
        m << 1.0, 2.0,
            3.0, 4.0;

        // print values to standard output
        cout << m << endl;

        // Output is:
        // 1 2
        // 3 5

        // 1 2
        // 3 4
}

void AdditionAndSubtraction()
{
        // �Ӽ���
        // ��������ļӼ����������ͬ��
        // �����������Ĵ�С��ͬ�����Ҹüӷ�������ǰ�ϵ�����еģ���˲�����Ч��
        // ���黹֧��������ʽ�ı��ʽ���ñ��ʽarray + scalar��������ӵ������е�ÿ��ϵ����
        // ���ṩ�˲���ֱ������Matrix����Ĺ��ܡ�
        LOG();
        ArrayXXf a(3, 3);
        ArrayXXf b(3, 3);
        a << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
        b << 1, 2, 3,
            1, 2, 3,
            1, 2, 3;

        // Adding two arrays
        cout << "a + b = " << endl
             << a + b << endl
             << endl;
        // Subtracting a scalar from an array
        cout << "a - 2 = " << endl
             << a - 2 << endl;
        // Output is:
        // a + b =
        //  2  4  6
        //  5  7  9
        //  8 10 12

        // a - 2 =
        // -1  0  1
        //  2  3  4
        //  5  6  7
}

void ArrayMultiplication()
{
        //�����Խ�һ��������Ա������������Ĺ�����ʽ��ͬ��
        //��������������ͬ�ĵط��ǽ�����������ˡ�
        //���󽫳˷�����Ϊ����˻��������齫�˷�����Ϊ��ϵ���˻���
        //��ˣ����ҽ����������������ͬ��ά��ʱ�����ǲ������
        LOG();
        ArrayXXf a(2, 2);
        ArrayXXf b(2, 2);
        a << 1, 2,
            3, 4;
        b << 5, 6,
            7, 8;
        cout << "a * b = " << endl
             << a * b << endl;
        // Output is:
        // a * b =
        //  5 12
        // 21 32
}

void OtherCoefficientwiseOperations()
{
        // �����ඨ��������ӷ��������ͳ˷����������ϵ��Ϊ��λ�����㡣
        // ���磬.abs()������ȡÿ��ϵ���ľ���ֵ����.sqrt��������ϵ����ƽ������
        //�������������С��ͬ�����飬����Ե���.min()��������ϵ�����������������ж�Ӧϵ������Сֵ�����顣
        //ע��:.array()��.matrix() ת��Ϊ��ͬ��ά�������ǲ�ͬ�Ķ�����в�ͬ�ķ���
        LOG();
        ArrayXf a = ArrayXf::Random(5);
        a *= 2;
        cout << "a =" << endl
             << a << endl;
        cout << "a.abs() =" << endl
             << a.abs() << endl;
        cout << "a.abs().sqrt() =" << endl
             << a.abs().sqrt() << endl;
        cout << "a.min(a.abs().sqrt()) =" << endl
             << a.min(a.abs().sqrt()) << endl;
        // Output is:
        // a =
        //   1.36
        // -0.422
        //   1.13
        //   1.19
        //   1.65
        // a.abs() =
        //  1.36
        // 0.422
        //  1.13
        //  1.19
        //  1.65
        // a.abs().sqrt() =
        // 1.17
        // 0.65
        // 1.06
        // 1.09
        // 1.28
        // a.min(a.abs().sqrt()) =
        //   1.17
        // -0.422
        //   1.06
        //   1.09
        //   1.28
}

void ConvertingBetweenArrayAndMatrixExpressions()
{
        // ʲôʱ��Ӧ��ʹ��Matrix��Ķ���ʲôʱ��Ӧ��ʹ��Array��Ķ���
        //�����ܶ�����Ӧ�þ������㣬Ҳ���ܶԾ���Ӧ���������㡣
        //��ˣ��������Ҫ�������Դ������㣨�������˷�������Ӧʹ�þ���
        //�����Ҫ����ϵ�����㣬��Ӧʹ�����顣
        //���ǣ���ʱ��������ô�򵥣���������Ҫͬʱʹ��Matrix��Array������
        //����������£�����Ҫ������ת��Ϊ�������ת��������ѡ�񽫶�������Ϊ���黹�Ǿ��󣬶����Է������в�����
        // ������ʽ����.array()���������Խ����ǡ�ת����Ϊ������ʽ����˿������ɵ�Ӧ�ð�ϵ���������㡣
        //�෴��������ʽ����.matrix()������
        //������Eigen���ʽ����һ������û���κ�����ʱ������ֻҪ���ñ����������Ż���
        //.array������.matrix() �ɱ�������ֵ����Ϊ��ֵ��

        // Eigen��ֹ�ڱ��ʽ�л�Ͼ�������顣
        // ���磬������ֱ�Ӿ����������ӡ������+�Ĳ�����Ҫô���Ǿ���Ҫô�������顣
        //���ǣ�ʹ��.array������.matrix�����������ɵؽ���ת��Ϊ��һ�֡�

        //��������ע�⡫��������
        //�˹���������Ǹ�ֵ�����=������������ʽ����������������������ʽ��������������

        // �����ʾ����ʾ���ͨ��ʹ��.array����������Matrix����ʹ�����������
        // ���磬�����Ҫ��������ͣ���������ת��Ϊ���У��������������ϵ�����ǲ������ָ����������������ǺϷ��ģ���Ϊ�����������������ʽ������ı�������result = m.array() * n.array()mnresult

        // ʵ���ϣ�����ʹ������ǳ��ձ飬������EigenΪ�����ṩ��const .cwiseProduct()����������ϵ���˻���
        LOG();
        MatrixXf m(2, 2);
        MatrixXf n(2, 2);
        MatrixXf result(2, 2);
        m << 1, 2,
            3, 4;
        n << 5, 6,
            7, 8;
        result = m * n;
        cout << "-- Matrix m*n: --" << endl
             << result << endl
             << endl;
        result = m.array() * n.array();
        cout << "-- Array m*n: --" << endl
             << result << endl
             << endl;
        result = m.cwiseProduct(n);
        cout << "-- With cwiseProduct: --" << endl
             << result << endl
             << endl;
        result = m.array() + 4;
        cout << "-- Array m + 4: --" << endl
             << result << endl
             << endl;

        // Output is:
        // -- Matrix m*n: --
        // 19 22
        // 43 50

        // -- Array m*n: --
        //  5 12
        // 21 32

        // -- With cwiseProduct: --
        //  5 12
        // 21 32

        // -- Array m + 4: --
        // 5 6
        // 7 8
}
} // namespace Section3_ArrayAndCoefficientwiseOperations
} // namespace Chapter1_DenseMatrixAndArrary
#endif