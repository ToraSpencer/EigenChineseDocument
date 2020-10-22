#ifndef MAP_CLASS_HPP
#define MAP_CLASS_HPP
#include "HeaderFile.h"
//http://eigen.tuxfamily.org/dox/group__TutorialMapClass.html
//��ҳ˵�������ʹ�á�ԭʼ�� C / C ++���顣���ڸ�������¶��������ã��ر����ڽ��������е������;��󡰵��롱Eigen��
//��ʱ������Ҫ��Eigen��ʹ��Ԥ�������������(C++)��Ϊʸ�������(Eigen)��
//һ��ѡ���Ǹ������ݣ�������������������ϣ�������ڴ档���˵��ǣ�ʹ��Map��ǳ����ס�
// Map �� ʵ��C++�е������ڴ��Eigen����Ľ���
// Map< Matrix<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>  >
// ��ע�⣬������Ĭ������£�Map����Ҫһ��ģ�������
// Ҫ����Map������������Ҫ����������Ϣ��ָ����ϵ��������ڴ������ָ�룬�Լ�����ľ����ʸ����״��(ע������ģ������ͺ����β�)
// ���磬Ҫ����һ��float�ڱ���ʱȷ����С�ľ���������ִ�����²�����
// Map <MatrixXf> mf��pf��rows��columns��;
// ����pf��һ��float *ָ��Ĵ洢�����С��̶���С������ֻ���������ܻ�����Ϊ
// Map <const Vector4i> mi��pi��;
// ����pi��int *������������£����ؽ���С���ݸ����캯������Ϊ���Ѿ���Matrix / Array����ָ����

// ��ע�⣬Mapû��Ĭ�ϵĹ��캯���������봫��һ��ָ������ʼ�����󡣵��ǣ������Խ����Ҫ������ĸ���Map���飩��

// Map�㹻���������ɸ��ֲ�ͬ�����ݱ�ʾ��ʽ������������������ѡ��ģ�������
// Map<typename MatrixType,    int MapOptions,     typename StrideType>
//MapOptionsָ��ָ����Aligned����Unaligned��Ĭ��ֵΪUnaligned��
//StrideType������ʹ��Stride��Ϊ�ڴ�����ָ���Զ��岼�֡�һ��ʾ����ָ�����������������ȸ�ʽ������֯MapConstruct()

namespace Chapter1_DenseMatrixAndArrary
{

namespace Section7_MapClass
{

void MapConstruct()
{
        LOG();
        int array[8];
        for (int i = 0; i < 8; ++i)
                array[i] = i;
        cout << "Column-major:\n"
             << Map<Matrix<int, 2, 4>>(array) << endl;
        cout << "Row-major:\n"
             << Map<Matrix<int, 2, 4, RowMajor>>(array) << endl;
        cout << "Row-major using stride:\n"
             << Map<Matrix<int, 2, 4>, Unaligned, Stride<1, 4>>(array) << endl;
        //Output is:
        //Column-major:
        // 0 2 4 6
        // 1 3 5 7
        // Row-major:
        // 0 1 2 3
        // 4 5 6 7
        // Row-major using stride:
        // 0 1 2 3
        // 4 5 6 7

        //However, Stride is even more flexible than this; for details, see the documentation for the Map and Stride classes.
}

void UsingMapVariables()
{
        LOG();
        typedef Matrix<float, 1, Dynamic> MatrixType;
        typedef Map<MatrixType> MapType;
        typedef Map<const MatrixType> MapTypeConst; // a read-only map
        const int n_dims = 5;

        MatrixType m1(n_dims), m2(n_dims);
        m1.setRandom();
        m2.setRandom();
        float *p = &m2(0);                     // get the address storing the data for m2
        MapType m2map(p, m2.size());           // m2map shares data with m2
        MapTypeConst m2mapconst(p, m2.size()); // a read-only accessor for m2
        cout << "m1: " << m1 << endl;
        cout << "m2: " << m2 << endl;
        cout << "Squared euclidean distance: " << (m1 - m2).squaredNorm() << endl;
        cout << "Squared euclidean distance, using map: " << (m1 - m2map).squaredNorm() << endl;
        m2map(3) = 7; // this will change m2, since they share the same array
        cout << "Updated m2: " << m2 << endl;
        cout << "m2 coefficient 2, constant accessor: " << m2mapconst(2) << endl;
        /* m2mapconst(2) = 5; */ // this yields a compile-time error

        //Output is:
        // m1:   0.68 -0.211  0.566  0.597  0.823
        // m2: -0.605  -0.33  0.536 -0.444  0.108
        // Squared euclidean distance: 3.26
        // Squared euclidean distance, using map: 3.26
        // Updated m2: -0.605  -0.33  0.536      7  0.108
        // m2 coefficient 2, constant accessor: 0.536
}

void ChangingTheMappedArray()
{
        LOG();
        //����ʹ��C ++�� placement new"(λ��new���ڳ���Ա�������ڴ����Ԫ��) �﷨������������Map���������
        ////�����г��֣�������������ڴ����������Ϊ�﷨ָ���˴洢�����λ�á�(����ο���C++primer���е�����)
        // �򵥵�˵��λ��newֻ����ָ��λ��д�����ݣ���������newһ�������ڶ��Ϸ����ڴ棬Ȼ�������γ�ʼ������
        // ��Ҳ��Ϊʲô��λ��new����Ϊ���ᰴ������ָ����λ�ù������
        int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        Map<RowVectorXi> v(data, 4);
        cout << "The mapped vector v is: " << v << "\n";
        new (&v) Map<RowVectorXi>(data + 4, 5);
        cout << "Now v is: " << v << "\n";
        //The mapped vector v is: 1 2 3 4
        //Now v is: 5 6 7 8 9

        // TODO : �̳���û��ָ��n_matrices
        // Map<Matrix3f> A(NULL); // don't try to use this matrix yet!
        // VectorXf b(n_matrices);
        // for (int i = 0; i < n_matrices; i++)
        // {
        //         new (&A) Map<Matrix3f>(get_matrix_pointer(i));
        //         b(i) = A.trace();
        // }
}
} // namespace Section7_MapClass

} // namespace Chapter1_DenseMatrixAndArrary

#endif