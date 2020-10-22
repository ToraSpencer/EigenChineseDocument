#ifndef STORAGE_ORDERS_HPP
#define STORAGE_ORDERS_HPP
#include "HeaderFile.h"

namespace Chapter1_DenseMatrixAndArrary
{
//����Ͷ�ά���������ֲ�ͬ�Ĵ洢˳�������Ⱥ������ȡ���ҳ˵������Щ�洢˳���Լ����ָ��Ӧʹ�õĴ洢˳��
//�������Ŀ�γ�һ����ά���񡣵��ǣ�������洢�ڴ洢����ʱ��������ĳ�ַ�ʽ����������Ŀ����������Ҫ��������������һ�㣬���кͰ��С�
//����˵������**�������ȴ洢**�����ȴ洢������һ�У�Ȼ��洢�����ڶ��У��������ơ�
//��һ���棬������������д洢�ģ���������˳��洢����������һ�п�ʼ��Ȼ���������ڶ��У���������

//����ͨ��OptionsΪMatrix��Arrayָ��ģ����������þ�����ά����Ĵ洢˳��
//����Matrix����ͣ�Matrix��ģ��������ģ�������
// ����������ǿ���Եģ�Scalar��RowsAtCompileTime��ColsAtCompileTime��
// �����ǿ�ѡ�ģ�Options��MaxRowsAtCompileTime��MaxColsAtCompileTime����
//���Options��������ΪRowMajor��������������������˳��洢��
//�����������ΪColMajor������������˳��洢��
//���δָ���洢˳����EigenĬ�Ͻ���Ŀ�洢��column-major�С�
//��������typedef��Matrix3f��ArrayXXd�ȣ�Ҳ��Ĭ�ϰ��д洢��

//���Խ�ʹ��һ�ִ洢˳��ľ������������ʹ����һ�ִ洢˳��ľ�������飬��һ�����д洢�ľ���ʹ�ð��д洢�����ʼ����
//Eigen���Զ���Ԫ���������򡣸�һ����ԣ����д洢����Ͱ��д洢������Ը�����Ҫ�ڱ��ʽ�л��ʹ�á�

//ѡ���ĸ��洢˳��
//��ô����Ӧ���ڳ�����ʹ���ĸ��洢˳���������û�м򵥵Ĵ𰸡���ȡ��������Ӧ�ó������ס���¼��㣺

//�����û�����ϣ����ʹ���ض��Ĵ洢˳�򡣻��ߣ�������ʹ��Eigen����������⣬������Щ�����������Ҫһ���Ĵ洢˳��
//����Щ����£�������������ʹ�ô˴洢˳���������򵥣����ġ�
//��������������˳��洢ʱ�����б���������㷨����죬��Ϊ����λ�ø��á�ͬ����������Ҫ�о������б������졣������Ҫ����һ�����ҳ��������ض�Ӧ�ó������ķ�����
//Eigen�е�Ĭ��ֵ��column-major����Ȼ����Eigen��Ĵ���������Ͳ��Զ���ʹ������������ɵġ�
//����ζ�ţ���ʹ����ּ��͸����֧�������洢�������洢˳��Eigen��Ҳ����������洢�������ʹ�á�
namespace Section10_StorageOrders
{

void testColumnAndRowMajorStorage()
{
        LOG();
        // PlainObjectBase::data()  ���ص�һ��Ԫ�ص��ڴ�λ�ã���C++������������һ��

        Matrix<int, 3, 4, ColMajor> Acolmajor;
        Acolmajor << 8, 2, 2, 9,
            9, 1, 4, 4,
            3, 5, 4, 5;
        cout << "The matrix A:" << endl;
        cout << Acolmajor << endl
             << endl;
        cout << "In memory (column-major):" << endl;
        for (int i = 0; i < Acolmajor.size(); i++)
                cout << *(Acolmajor.data() + i) << "  ";
        cout << endl
             << endl;
        Matrix<int, 3, 4, RowMajor> Arowmajor = Acolmajor;
        cout << "In memory (row-major):" << endl;
        for (int i = 0; i < Arowmajor.size(); i++)
                cout << *(Arowmajor.data() + i) << "  ";
        cout << endl;

        // Output is
        // The matrix A:
        // 8 2 2 9
        // 9 1 4 4
        // 3 5 4 5

        // In memory (column-major):
        // 8  9  3  2  1  5  2  4  4  9  4  5

        // In memory (row-major):
        // 8  2  2  9  9  1  4  4  3  5  4  5
}

} // namespace Section10_StorageOrders
} // namespace Chapter1_DenseMatrixAndArrary

#endif