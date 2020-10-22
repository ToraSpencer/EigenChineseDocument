#ifndef ALIGNMENT_ISSUES_HPP
#define ALIGNMENT_ISSUES_HPP
#include "HeaderFile.h"


// ��ڱȽϳ���֪��զ�þͺã�
// TODO �������룡

// �������
//Eigen::internal::matrix_array<T, Size, MatrixOptions, Align>::internal::matrix_array()
// [with T = double, int Size = 2, int MatrixOptions = 2, bool Align = true]:
// Assertion `(reinterpret_cast<size_t>(array) & (sizemask)) == 0 && "this assertion
// is explained here: http://eigen.tuxfamily.org/dox-devel/group__TopicUnalignedArrayAssert.html
//      READ THIS WEB PAGE !!! ****"' failed.

// �����ҵ����򴥷�λ�ã�
// ���磬
//$gdb ./my_program
//>run
//...
//>bt
//Ȼ���������4��ԭ��Ժ��������޸Ĵ���

// �� ����ԭ��

// ԭ��1:�ṹ���о���Eigen�����Ա
//��ע�⣬�˴�Eigen :: Vector2d������ʾ����
//��һ����ԣ����й̶���С�Ŀ�ʸ����Eigen���Ͷ�����ִ�����
//�̶���С�Ŀ�ʸ����Eigen��������������й̶��Ĵ�С���Ҵ�С��16�ֽڵı���
// Eigen::Vector2d
// Eigen::Vector4d
// Eigen::Vector4f
// Eigen::Matrix2d
// Eigen::Matrix2f
// Eigen::Matrix4d
// Eigen::Matrix4f
// Eigen::Affine3d
// Eigen::Affine3f
// Eigen::Quaterniond
// Eigen::Quaternionf

// ����, "�̶���С"Ӧ�����������ڱ���ʱ��Eigen����������������ǹ̶��ģ�����̶���С��
// ��ˣ�����Matrix3f���й̶���С����MatrixXfû�У��̶���С�Ķ����Ƕ�̬��С����
// �̶���С��Eigen�����ϵ����������ͨ�ġ���̬���顱�����ᶯ̬���䡣���磬Matrix4f���������ֻ��һ����float array[16]����
// �̶���С�Ķ���ͨ����С������ζ������Ҫ���������ʱ���������ڴ�ʹ�ú��ٶȷ��棩���������ǡ�
// ���ڣ�ʸ������SSE��AltiVec�������Դ���128λ���ݰ������⣬��������ԭ����Щ���ݰ��������128λ���롣
//��ˣ���ʵ֤�����̶���С��Eigen���������������Ψһ�����ǣ�
//������ǵĴ�С��128λ��16���ֽڵı�����Ȼ��Eigen��Ϊ��Щ��������16�ֽڶ��룬���Ҵ˺���������Щ������ж��룬��˲���ִ������ʱ����Խ��ж��롣
// class Foo
// {
//   //...
//   Eigen::Vector2d v;
//   //...
// };
// //...
// Foo *foo = new Foo;

// Eigen��ҪEigen :: Vector2d�����飨2��˫���ȣ���128λ���롣����GCC������ͨ�����ԣ���aligned��16��������ɵġ�
// Eigen������Eigen :: Vector2d�ġ� operator new�����������ʼ�շ���128λ�����ָ�롣
// ��ˣ�ͨ������£������ص����κ����飬Eigen��Ϊ���������...

// ...����һ���������������������Foo�࣬��������������̬�����µ�Fooʱ��������Fooû�ж��롰 operator new������˷��ص�ָ��foo��һ����128λ����ġ�
// Ȼ�󣬳�Աv��alignment�����������Ŀ�ͷfoo�����fooָ��δ���룬��foo-> vҲ������룡
// �����������Foo�����һ�µġ�Operator new��

// ���������
//�������Ľṹ���й̶���С�Ŀ�ʸ����Eigen���͵ĳ�Ա��
//����������䡰 operator new�����Ա�������16�ֽڶ����ָ�롣
//���˵��ǣ�EigenΪ���ṩ��һ����EIGEN_MAKE_ALIGNED_OPERATOR_NEW��Ϊ��ִ�д˲�����
//���仰˵������һ���࣬������й̶���С�Ŀ�ʸ����Eigen������Ϊ��Ա��Ȼ��̬��������Ķ���

//�ܼ򵥣���ֻ�轫EIGEN_MAKE_ALIGNED_OPERATOR_NEW������������public����
// class Foo
// {
//         Eigen::Vector2d v;
//         public : EIGEN_MAKE_ALIGNED_OPERATOR_NEW
// };
// Foo *foo = new Foo;
//�ú�ʹ�� new Foo��ʼ�շ��ض����ָ�롣
//һ�� Eigen::Vector2d������double���ͣ�һ��doubleΪ8�ֽ�=64λ����һ��Eigen::Vector2dΪ128λ
//��ǡ����SSE���ݰ��Ĵ�С����ʹ�ÿ���ʹ��SSE�Ը�����ִ�и��ֲ�����
//����SSEָ�����Eigenʹ�õ��ǿ���ָ���Ҫ128λ���롣�������ֶδ���
// �������ԭ��Eigen�Լ�ͨ��ִ���������������Ҫ���Eigen :: Vector2d����128λ���룺


//ԭ��2��STL�������ֶ��ڴ����
///�������Stl����������std :: vector��std :: map�ȣ�
//��Eigen��������Eigen�������һ��ʹ�ã�
// std::vector<Eigen::Matrix2f> my_vector;
// struct my_class { ... Eigen::Matrix2f m; ... };
// std::map<int, my_class> my_map;
//��ע�⣬�˴�Eigen :: Matrix2f������ʾ������һ����ԣ��������й̶���С�Ŀ�ʸ����Eigen���ͺ;��д���Eigen������Ϊmember�Ľṹ��������ִ����⡣
//�κ���/���������ƹ�new�����ڴ���������Ҳ����ͨ��ִ���Զ����ڴ���䣬Ȼ�����placement new�������
// Ҳ�������ͬ�����⡣���磬ͨ���������������std::make_shared����std::allocate_shared���������ʹ�ö���ķ�������
//��STL�������������������

//ԭ��3��ͨ��ֵ����Eigen����
//����������е�ĳЩ��������ͨ��ֵ����Eigen��������������
//void func(Eigen::Vector4d v);
//��ô����Ҫ�Ķ����µ�����ҳ�棺��Eigen����ֵ���ݸ�������
//��ע�⣬�˴�Eigen :: Vector4d������ʾ������һ����ԣ����й̶���С�Ŀ�ʸ����Eigen���Ͷ�����ִ�����

//ԭ��4:�������Զ�ջ��������������裨����Windows�ϵ�GCC��
//������Windows��ʹ��GCC������MinGW��TDM-GCC�������ǵıض����ݡ�
//��������������ľֲ��������޹��������д˶���ʧ�ܣ���ִ�����²�����
// void foo()
// {
//   Eigen::Quaternionf q;
//   //...
// }
//��ô����Ҫ�Ķ����µ�����ҳ�棺�������Զ�ջ���������˴���ļ��衣
//��ע�⣬�˴�Eigen :: Quaternionf������ʾ������һ����ԣ����й̶���С�Ŀ�ʸ����Eigen���Ͷ�����ִ����⡣

// 3  �ö��Ե�һ�����:
// �̶���С��ʸ����Eigen������������16�ֽڶ����λ�ô���������Ѱַ���ǵ�SIMDָ�������
// Eigenͨ����Ϊ�������Щ�������⣬�������ڹ̶���С�Ŀ�ʸ�������������ö������ԣ�
// ���������ǵġ� operator new����
// ���ǣ���ĳЩ��������£���Щ�������ûᱻ���ǣ������Ǵ˶��ԵĿ���ԭ��

// 4   �Ҳ��ں����ʸ��������ΰ�����Щ������
// ���ֿ����ԣ�
// ʹ��Matrix��Array��Quaternion�ȶ����DontAlignѡ�����������鷳��
// ������Eigen���᳢�Զ������ǣ���˲����ȡ�κ�������뷽ʽ��
// ������һ���ǣ�����Ϊ����֧��δ����ļ���/�洢�ĳɱ����������ִ�CPU�ϣ�����Ϊnull��߼ʵġ�
// ����EIGEN_DONT_ALIGN_STATICALLY���⽫��������16
#endif