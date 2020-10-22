#include <Eigen/Geometry>
#include <iostream>

using namespace Eigen;
using namespace std;
int main()
{
        // scaling ����Ϊһ���Խ���
        //2 0
        //0 1
        Matrix<float, 2, 2> t = Scaling(2.0f, 1.0f);
        std::cout << t.matrix() << std::endl;

        Affine3f aux(Affine3f::Identity());

        cout << aux.affine().matrix() << endl;  // aux��һ����ξ��󣬲���.affine()���������һ��

        cout  << aux.matrix()<<endl;

        Transform<double, 3, Affine> Affine_transform;     // ����
        Affine_transform.setIdentity();
        Transform<double, 3, Isometry> Isometry_transform;   //�Ⱦ�
        Transform<double, 3, Projective> Projective_transform; // ��Ӱ�任
        Affine_transform.prerotate(AngleAxisd(3.14,Vector3d::UnitX()));


}