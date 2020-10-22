#ifndef SPACE_TRANSFORMATIONS_HPP
#define SPACE_TRANSFORMATIONS_HPP
#include "HeaderFile.h"

namespace Chapter4_Geometry
{

namespace Section1_SpaceTransformations
{

// �ڴ�ҳ���У����ǽ����ܼ���ģ���ṩ���������ԣ��Դ���2D��3D��ת�Լ���Ӱ�����任��

// Eigen��Geometryģ���ṩ�����ֲ�ͬ�ļ��α任��

// 1. ����ı任��������ת����ǻ���Ԫ����ʾ����ƽ�ƣ����š�
// ��Щת��δ��ʾΪ���󣬵�������Ȼ���Խ���������ʽ�еľ����������ϣ���������Ҫ������ת��Ϊ����

// 2. ��Ӱ�����任������μ�Transform�ࡣ��Щȷʵ�Ǿ���ע��, ���Ҫʹ��OpenGL 4x4��������ҪAffine3f��Affine3d��
// ����EigenĬ��Ϊ����洢�����������ֱ��ʹ��Transform :: data()������ת�����󴫵ݸ�OpenGL��

// �����Դӳ���ת������һ��Transform��������ʾ��
// Transform t(AngleAxis(angle,axis));
// ����������
// Transform t;
// t = AngleAxis(angle,axis);

// ������ע�⣬���ҵ��ǣ�����C ++�Ĺ�����ʽ����������������

// Transform t = AngleAxis(angle,axis);
// ˵������C ++�����У��⽫Ҫ��Transform����һ������AngleAxis�ķ���ʽת�����캯��������������Ĳ����ڴ�������ʽת����

// �任������

// �任����                        ���͵ĳ�ʼ��
// 2D��ת��ע��Ƕȵ�λ�ǻ���
// 2D rotation from an angle
// Rotation2D<float> rot2(angle_in_radian);

// 3D��ת����Ƿ�����ע�⣬������һ��(The axis vector must be normalized.)
// 3D rotation as an angle + axis
// AngleAxis<float> aa(angle_in_radian, Vector3f(ax,ay,az));

// 3D��ת����Ԫ����������������ǵõ�
// Quaternion<float> q;  q = AngleAxis<float>(angle_in_radian, axis);

// Nά����
// Scaling(sx, sy)
// Scaling(sx, sy, sz)
// Scaling(s)
// Scaling(vecN)

// Nάƽ��
// Translation<float,2>(tx, ty)
// Translation<float,3>(tx, ty, tz)
// Translation<float,N>(s)
// Translation<float,N>(vecN)

// Nά����
// Transform<float,N,Affine> t = concatenation_of_any_transformations;
// Transform<float,3,Affine> t = Translation3f(p) * AngleAxisf(a,axis) * Scaling(s);

// Nά���Ա任(pure rotations,scaling, etc.) ע�⣺������ĵ����������⣬��ΪMatrix<>��Ҫָ������������������ָ����ֻ�����������ǻ���Ҫָ������
// Matrix<float,N> t = concatenation_of_rotations_and_scalings;
// Matrix<float,2> t = Rotation2Df(a) * Scaling(s);
// Matrix<float,3> t = AngleAxisf(a,axis) * Scaling(s);

// ������ת��ע������
// Ҫ�任���ʸ������ѡ���õ�����ת���󣬶����������÷�����Ԫ���ǽ��գ����ٺ��ȶ�����ѡ��ʾ��ʽ��
// ���Rotation2D��AngleAxis��Ҫ�Ǵ���������ת����ı�����͡�

// ����ƽ�ƺ����ŵ�ע��
// ��AngleAxisһ������Щ��ּ�ڼ����ԣ�Matrix���ͷ��䣨Transform���任�Ĵ���/��ʼ����
// ���ǣ���ʹ��Ч�ʵ��µ�AngleAxis��ͬ����д�κ����͵�ת����Ϊ�����ͨ�ø�Ч�㷨������Ȼ����Ȥ��

// �����κ�ת�����Ͷ�����ת��Ϊ��ͬ���ʵ��κ��������ͣ�����ת��Ϊ��ͨ�õ����͡�������һЩ����ʾ����

// Rotation2Df r;  r  = Matrix2f(..);       // assumes a pure rotation matrix
// AngleAxisf aa;  aa = Quaternionf(..);
// AngleAxisf aa;  aa = Matrix3f(..);       // assumes a pure rotation matrix
// Matrix2f m;     m  = Rotation2Df(..);
// Matrix3f m;     m  = Quaternionf(..);       Matrix3f m;   m = Scaling(..);
// Affine3f m;     m  = AngleAxis3f(..);       Affine3f m;   m = Scaling(..);
// Affine3f m;     m  = Translation3f(..);     Affine3f m;   m = Matrix3f(..);

// ��ת�����͵�ͨ��API
// ��ĳ�̶ֳ��ϣ�Eigen�ļ���ģ����������д�������κ����͵ı任��ʾ��ʽ��ͨ���㷨��
// Concatenation of two transformations
// gen1 * gen2;
// Apply the transformation to a vector
// vec2 = gen1 * vec1;
// Get the inverse of the transformation
// gen2 = gen1.inverse();
// Spherical interpolation
// (Rotation2D and Quaternion only)
// rot3 = rot1.slerp(alpha,rot2);

void AffineTransformations()
{
        // �����ֽ��ܷ���任
        // �����ϣ�����任��һ�����������Ա任 linear()��һ��ƽ�Ʊ任t�ĸ��ϣ���������Ϊx' = linear()*x + t ;����linear()�����Բ���
        //  ����任�ı��ΪH_{A} = [ linear_part,translation part ;0 ,1 ]

        // ͨ�÷���任��Transform���ʾ�������ڲ��ǣ�Dim + 1��^ 2�ľ���
        // ��Eigen�У�����ѡ�����ֵ����������ʹ���е�ʵ���϶���ԭ�㣨$ \ mathbf {p} \ equiv \ mathbf {p} -0 $����λ��������ʾ��
        // ע����ǣ���Ӧ�ñ任ʱ�������������������

        // ���任Ӧ���ڵ�
        // VectorNf p1, p2;
        // p2 = t * p1;

        //  ���任Ӧ��������
        // VectorNf vec1, vec2;
        // vec2 = t.linear() * vec1;   // �����ǿ��ǵ�ƽ�Ʋ��ֲ���Ӱ�������ı仯

        // Ӧ��һ����һ��ı任������normal vector ���ⲿ��û����
        // VectorNf n1, n2;
        // MatrixNf normalMatrix = t.linear().inverse().transpose();     //A^{-1}^{T}???
        // n2 = (normalMatrix * n1).normalized();
        // (See subject 5.27 of this faq for the explanations)

        //������ת�任������һ�� normal vector (no scaling, no shear)
        // n2 = t.linear() * n1;
        // OpenGL compatibility 3D
        // glLoadMatrixf(t.data());
        // OpenGL compatibility 2D
        // Affine3f aux(Affine3f::Identity());
        // aux.linear().topLeftCorner<2,2>() = t.linear();
        // aux.translation().start<2>() = t.translation();
        // glLoadMatrixf(aux.data());

        // �ɷֻ�ȡ
        // ���ڲ��������ȫ��д����
        // full read-write access to the internal matrix
        // t.matrix() = matN1xN1;    // N1 means N+1
        // matN1xN1 = t.matrix();

        // ��ȡԪ��ϵ��
        // t(i,j) = scalar;   <=>   t.matrix()(i,j) = scalar;
        // scalar = t(i,j);   <=>   scalar = t.matrix()(i,j);

        // ƽ�Ʋ���
        // t.translation() = vecN;
        // vecN = t.translation();

        // ���Բ���
        // t.linear() = matNxN;
        // matNxN = t.linear();
        // extract the rotation matrix
        // matNxN = t.rotation();

        // ���ɱ任
        // �任����������˻����ҳˣ�������һϵ��APII

        // ƽ��
        // t.translate(Vector_(tx,ty,..));   �ȼ���t *= Translation_(tx,ty,..);���Ҳ�˷�
        // t.pretranslate(Vector_(tx,ty,..));�ȼ���  t = Translation_(tx,ty,..) * t; �����˷�

        // ��ת(ע�ⵥλ�ǻ���)
        // t.rotate(any_rotation);  �ȼ��� t *= any_rotation;
        // t.prerotate(any_rotation);�ȼ��� t = any_rotation * t;

        // ����
        // t.scale(Vector_(sx,sy,..));   �ȼ���  t *= Scaling(sx,sy,..);
        // t.scale(s);   �ȼ��� t *= Scaling(s);
        // t.prescale(Vector_(sx,sy,..));  �ȼ��� t = Scaling(sx,sy,..) * t;
        // t.prescale(s); �ȼ���  t = Scaling(s) * t;

        // ���б任��������2D
        // t.shear(sx,sy);
        // t.preshear(sx,sy);

        // ע�⣬�����任������Ϊһ�����ʽΪ��
        // t.pretranslate(..).rotate(..).translate(..).scale(..); �ȼ��� t = Translation_(..) * t * RotationType(..) * Translation_(..) * Scaling(..);
}

void EulerAngles()
{

        // ŷ����
        // ŷ���ǿ��ܷܺ��㴴����ת������һ���棬���ڴ���24�ֲ�ͬ��Լ�������ʹ�������൱���ҡ�
        // ��ʾ��˵����θ���2-1-2Լ��������ת����ZYZ��ʽ
        // Matrix3f m;
        // m = AngleAxisf��angle1��Vector3f :: UnitZ������
        //     * AngleAxisf��angle2��Vector3f :: UnitY������
        //     * AngleAxisf��angle3��Vector3f :: UnitZ������;
}

} // namespace Section1_SpaceTransformations

} // namespace Chapter4_Geometry

#endif