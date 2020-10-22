#ifndef MATRIX_CLASS_HPP
#define MATRIX_CLASS_HPP
#include "HeaderFile.h"

namespace Chapter1_DenseMatrixAndArrary
{

namespace Section1_MatrixClass
{
/*
	 Eigen�е�matrix��vector�ײ����Matrix<>ģ�����ʾ
	  Matrix<>ģ���ඨ�壺
			Matrix<typename Scalar, int RowsAtCompileTime, int ColsAtCompileTime>
			typedef Matrix<double, Dynamic, Dynamic> MatrixXd;
			typedef Matrix<int, Dynamic, 1> VectorXi;



	MatrixXt�������Ƕ�̬�ڴ����ͳ�ʼ���ֿ�



	�̶���С�������ṩ�˳�ʼ������
				   Vector2d a(5.0, 6.0);
				   Vector3d b(5.0, 6.0, 7.0);
				   Vector4d c(5.0, 6.0, 7.0, 8.0);

	 ��ȡԪ�أ�
			 ����Ԫ�أ�m(index)�ķ�ʽ���Ի�ȡ���ݣ����Ǻʹ洢��ʽ�йأ�
			 eigenĬ�ϲ����д洢����˳�򣬿��Ը�Ϊ�д洢����˳��, ע�⣬�洢˳���붺�ų�ʼ�����޹�ϵ��
			 []�����ֻ�ܻ�ȡ����Ԫ�أ���ΪC++[]ֻ֧��һ��������
 */




void CoefficientAccessors()
{
        LOG();
		
		
		// ��������С����δ��ʼ��,�÷�ʽ�ڶ��Ϸ����ڴ�
        MatrixXd m(2, 2);


        // ����Ԫ�ظ�ֵ��index ��0��ʼ
        m(0, 0) = 3;
        m(1, 0) = 2.5;
        m(0, 1) = -1;
        m(1, 1) = m(1, 0) + m(0, 1);
        std::cout << m << std::endl;
 
}



void CommaInitialization()
{
        LOG();

        // ���ų�ʼ��
        Matrix3f m;
        m << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
        std::cout << m;
}




void Resizing()
{
        LOG();
        // ����ĵ�ǰ��С����ͨ��rows()��cols()��size()��ȡ��
        //			������̬��С����Ĵ�С��ͨ��resize()������ɵġ�
        //			���ʵ�ʾ����С���䣬��resize()����Ϊ�ղ�����
        //			��������ƻ��ԣ�Ԫ�ص�ֵ���ܻ���ġ�������������С()�������ı�Ԫ�أ�ʹ��conservativeResize()
		

        MatrixXd m(2, 5);
        m.resize(4, 3);
        std::cout << "The matrix m is of size "
                  << m.rows() << "x" << m.cols() << std::endl;
        std::cout << "It has " << m.size() << " coefficients" << std::endl;
        VectorXd v(2);
        v.resize(5);
        std::cout << "The vector v is of size " << v.size() << std::endl;
        std::cout << "As a matrix, v is of size "
                  << v.rows() << "x" << v.cols() << std::endl;
        // Output is:
        // The matrix m is of size 4x3
        // It has 12 coefficients
        // The vector v is of size 5
        // As a matrix, v is of size 5x1

        {
                // ���Խ��̶���С����Ϊʵ�ʲ�ͬ��ֵ����������ʧ�ܡ�
                //		�������´����ǺϷ��ģ�
                Matrix4d m;
                m.resize(4, 4); // no operation
                std::cout << "The matrix m is of size "
                          << m.rows() << "x" << m.cols() << std::endl;
        }
}



void MatrixAndVectorRunTime()
{
        LOG();
        // �̶���С�ľ���������ջ�Ϸ����ڴ棬��Ϊ���ڱ���ʱ�ھͿ���ȷ����С
        // MatrixX��ʾ����ʱ��ȷ������Ĵ�С����Ϊ���ڶ��Ϸ����ڴ�

        MatrixXd m = MatrixXd::Random(3, 3);          // between -1 and 1
        m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50; // MatrixXd::Constant()
        cout << "m =" << endl
             << m << endl;
        VectorXd v(3); // ��δ��ʼ��
        v << 1, 2, 3;   
        cout << "m * v =" << endl
             << m * v << endl;
}



void MatrixAndVectorCompileTime()
{
        LOG();
        // ����ʱ��ȷ������ߴ磬��ջ�Ϸ����ڴ�
        Matrix3d m = Matrix3d::Random(); //a fixed size
        m = (m + Matrix3d::Constant(1.2)) * 50;
        cout << "m =" << endl
             << m << endl;
        Vector3d v(1, 2, 3);

        cout << "m * v =" << endl
             << m * v << endl;
}



void AssignmentAndResizing()
{
        LOG();
        // operator= �������Ƶ���һ�������еĲ�����
		//		Eigen�Զ�����������Ĵ�С��ʹ�����Ҳ��С�ľ����Сƥ�䡣���磺

        MatrixXf a(2, 2);
        std::cout << "a is of size " << a.rows() << "x" << a.cols() << std::endl;


        MatrixXf b(3, 3);
        a = b;
        std::cout << "a is now of size " << a.rows() << "x" << a.cols() << std::endl;
        
}



void FixedSizeAndDynamicSize()
{

        LOG();
        // �̶��ߴ��붯̬�ߴ�
        //		ʹ�ù̶��ߴ�����ʾ�ǳ�С�ĳߴ磬ʹ�ö�̬�ߴ�����ʾ�ϴ�ĳߴ硣
        //		����С�ߴ磬�����Ƕ���С�ڣ���Լ��16�ĳߴ磬�������м���ĺô�
        //		Matrix4f mymatrix; ��ĵ���ֻ������float[16]; �����ȷʵ����������ʱ��ɱ���

        // MatrixXf mymatrix���У��У�������float * mymatrix = new [��*��];
        //		����֮�⣬MatrixXf���󻹽��������������洢Ϊ��Ա������

        // �����㹻��ĳߴ磨���磬���ڴ��ڣ���Լ��32�ĳߴ磩��ʹ�ù̶��ߴ���������Ʊ�ÿ��Ժ��Բ��ơ�
        //		ʹ�ú����ڲ��Ĺ̶���С�����ǳ���ľ�����ܻᵼ�¶�ջ�������ΪEigen�᳢���Զ����������Ϊ�ֲ�����������ͨ�����ڶ�ջ����ɵġ�
        //		��ʹ�ö�̬�ߴ�ʱ��Eigen���ɳ��Խ���ʸ������ʹ��SIMDָ�����μ��ο�ʸ������
}



void OptionalTemplateParameters()
{
        LOG();
        // ��ѡģ�����
        // ������ҳ�濪ʼʱ�ᵽMatrix���������ģ�����������ĿǰΪֹ�����ǽ�������ǰ�������������������ǿ�ѡ�ġ�����ģ������������б�

        //       Matrix<typename Scalar,
        //        int RowsAtCompileTime,
        //        int ColsAtCompileTime,
        //        int Options = 0,
        //        int MaxRowsAtCompileTime = RowsAtCompileTime,
        //        int MaxColsAtCompileTime = ColsAtCompileTime>

        // Options��λ�ֶΡ����������ֻ����һ�㣺RowMajor����ʹ�������ȴ洢˳�� �� Matrix<float��3��3��RowMajor>
        
		
		// MaxRowsAtCompileTime��MaxColsAtCompileTimeָ�������С���ޡ�
        // ��������ԭ���Ǳ��⶯̬�ڴ���䡣���磬���¾�������ʹ��12������������ͨ���飬�������䶯̬�ڴ棺
        // Matrix<float��Dynamic��Dynamic��0��3��4>
}



void ConvenienceTypedefs()
{
        LOG();
        // �������typedef��

        // MatrixNt for Matrix<type, N, N>.  
        // VectorNt for Matrix<type, N, 1> 
        // RowVectorNt for Matrix<type, 1, N>. 

        //		 N�������κ�һ��2��3��4����X����˼Dynamic����
        //		 t������i����ʾint����f����ʾfloat����d����ʾdouble����cf����ʾcomplex <float>����cd����ʾcomplex <double>�����κ�һ�֡�
        //		N֧�����б�׼�������ͣ�����ı������͡�
}

} // namespace Section1_MatrixClass

} // namespace Chapter1_DenseMatrixAndArrary

#endif