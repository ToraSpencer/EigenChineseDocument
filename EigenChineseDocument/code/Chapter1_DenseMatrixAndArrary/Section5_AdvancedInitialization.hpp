#ifndef ADVANCED_INITIALIZATION_HPP
#define ADVANCED_INITIALIZATION_HPP
#include "HeaderFile.h"


#define PI 3.14159


namespace Chapter1_DenseMatrixAndArrary
{
// ��ҳ�����˼��ֳ�ʼ������ĸ߼�������
// ���ṩ���й�֮ǰ���ܵĶ��ų�ʼ������ĸ�����ϸ��Ϣ��
// ����˵������λ������������絥λ����������

namespace Section5_AdvancedInitialization
{

void CommaInitializer()
{
        LOG();
        // Eigen�ṩ��һ�ֶ��ų�ʼ�����﷨�����﷨ʹ�û������������þ������������������ϵ��
        // �򵥵��г�ϵ������ʼ�����Ͻǣ����������ң��Ӷ�����ײ��ƶ���
        // ��ҪԤ��ָ������Ĵ�С��
        // ����г���ϵ��̫�ٻ�̫�࣬�ͻᱨ��

        Matrix3f mat;
        mat << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;

        std::cout << mat << endl;

        //���⣬��ʼ���б��Ԫ�ر�����������������
        //ͨ������;�ǽ����������������һ��
        //���磬���ǽ�����������������һ��ķ�����
        //  ע�⣺����������
        //���ס�����������ô�С��Ȼ�����ʹ�ö��ų�ʼ������
        RowVectorXd vec1(3);
        vec1 << 1, 2, 3;
        std::cout << "vec1 = " << vec1 << std::endl;
        RowVectorXd vec2(4);
        vec2 << 1, 4, 9, 16;
        std::cout << "vec2 = " << vec2 << std::endl;
        RowVectorXd joined(7);
        joined << vec1, vec2;
        std::cout << "joined = " << joined << std::endl;

        // ���Ʒֿ����ĳ�ʼ����ʽ
        MatrixXf matA(2, 2);
        matA << 1, 2, 3, 4;
        MatrixXf matB(4, 4);
        matB << matA, matA / 10, matA / 10, matA;
        std::cout << matB << std::endl;

        //  �Ծ����ĳһ�鸳ֵ
        Matrix3f m;
        m.row(0) << 1, 2, 3;
        m.block(1, 0, 2, 2) << 4, 5, 7, 8;
        m.col(2).tail(2) << 6, 9;
        std::cout << m;
}

void SpecialMatricesAndArrays()
{
        LOG();
        // ģ����Matrix<>��Array<>�о�̬���������԰�����ʼ����
        //�����ֱ���:
        //��һ�����岻��������ֻ�����ڹ̶���С�Ķ������Ҫ����̬�ߴ�����ʼ��Ϊ�㣬����Ҫָ���ߴ硣
        //�ڶ���������Ҫһ�����������ҿ�������һά��̬�ߴ����
        //������������Ҫ�������������ҿ������ڶ�ά����

        std::cout << "A fixed-size array:\n";
        Array33f a1 = Array33f::Zero();
        std::cout << a1 << "\n\n";
        std::cout << "A one-dimensional dynamic-size array:\n";
        ArrayXf a2 = ArrayXf::Zero(3);
        std::cout << a2 << "\n\n";
        std::cout << "A two-dimensional dynamic-size array:\n";
        ArrayXXf a3 = ArrayXXf::Zero(3, 4);
        std::cout << a3 << "\n";

        //ͬ������̬����Constant(value)�Ὣ����ϵ������Ϊvalue��
        // �����Ҫָ������Ĵ�С���򸽼Ӳ�������value����֮ǰ����
        // MatrixXd::Constant(rows, cols, value)��

        //Random()�����ϵ������������顣

        //Identity()��õ�λ����, �˷�����������Matrix����������Array����Ϊ����λ���������Դ������

        //�÷���LinSpaced���ߴ磬�ͣ��ߣ��ǽ������������һά����; ������һ��ָ����С����������ϵ����low��֮��ƽ�����high��
        //����LinSpaced()����ʾ��˵���˸�ʾ������ʾ����ӡһ�ű�����а����Զ�Ϊ��λ�ĽǶȣ��Ի���Ϊ��λ����Ӧ�Ƕ��Լ����ǵ����Һ�����ֵ��
        ArrayXXf table(10, 4);
        table.col(0) = ArrayXf::LinSpaced(10, 0, 90);
        table.col(1) = PI / 180 * table.col(0);
        table.col(2) = table.col(1).sin();
        table.col(3) = table.col(1).cos();
        std::cout << "  Degrees   Radians      Sine    Cosine\n";
        std::cout << table << std::endl;

        //Eigen����������setZero()��MatrixBase :: setIdentity������DenseBase :: setLinSpaced()֮���ʵ�ó������������ִ�д˲�����
        //�������Բ��ö���ĳ�Ա�������ó�ʼֵ��

        //�����ʾ���Ա������ֹ�������J =[O  I ; I O ] ����
        // ʹ�þ�̬������operator=
        const int size = 6;
        MatrixXd mat1(size, size);
        mat1.topLeftCorner(size / 2, size / 2) = MatrixXd::Zero(size / 2, size / 2);
        mat1.topRightCorner(size / 2, size / 2) = MatrixXd::Identity(size / 2, size / 2);
        mat1.bottomLeftCorner(size / 2, size / 2) = MatrixXd::Identity(size / 2, size / 2);
        mat1.bottomRightCorner(size / 2, size / 2) = MatrixXd::Zero(size / 2, size / 2);
        std::cout << mat1 << std::endl
                  << std::endl;
        //ʹ��.setXxx()����
        MatrixXd mat2(size, size);
        mat2.topLeftCorner(size / 2, size / 2).setZero();
        mat2.topRightCorner(size / 2, size / 2).setIdentity();
        mat2.bottomLeftCorner(size / 2, size / 2).setIdentity();
        mat2.bottomRightCorner(size / 2, size / 2).setZero();
        std::cout << mat2 << std::endl
                  << std::endl;
        MatrixXd mat3(size, size);
        
        //ʹ�þ�̬�����Ͷ��ų�ʼ��
        mat3 << MatrixXd::Zero(size / 2, size / 2), MatrixXd::Identity(size / 2, size / 2),
            MatrixXd::Identity(size / 2, size / 2), MatrixXd::Zero(size / 2, size / 2);
        std::cout << mat3 << std::endl;
}

void UsageAsTemporaryObjects()
{
        LOG();
        //������ʾ������������ʱ���ڸ�ֵ��������Ҳ�ʹ�þ�̬����Zero()��Constant()����ʼ��������
        //�����Խ���Щ������Ϊ���ؾ�������顣
        //ʵ���ϣ����Ƿ�����ν��**���ʽ����**����Щ���ʽ��������Ҫʱ��ֵ����������飬��˸��﷨��������κο�����
        //��Щ���ʽҲ����������ʱ����

        MatrixXd m = MatrixXd::Random(3, 3);
        m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;
        cout << "m =" << endl
             << m << endl;
        VectorXd v(3);
        v << 1, 2, 3;
        cout << "m * v =" << endl
             << m * v << endl;

        // The comma-initializer, too, can also be used to construct temporary objects.
        //The following example constructs a random matrix of size 2-by-3,
        // and then multiplies this matrix on the left with [0 1; 1 0]
        MatrixXf mat = MatrixXf::Random(2, 3);
        std::cout << mat << std::endl
                  << std::endl;
        //
        // The finished() method is necessary here to get the actual matrix object
        //  once the comma initialization of our temporary submatrix is done.
        //  finished ������endl��������������
        mat = (MatrixXf(2, 2) << 0, 1, 1, 0).finished() * mat;
        std::cout << mat << std::endl;
}

} // namespace Section5_AdvancedInitialization
} // namespace Chapter1_DenseMatrixAndArrary
#endif