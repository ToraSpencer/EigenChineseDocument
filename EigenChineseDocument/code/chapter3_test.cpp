#include "Chapter3_SparseLinearAlgebra/Section1_SparseMatrixManipulations.hpp"
#include <Eigen/Geometry>
void TestChapter3Section1()
{
        Chapter3_SparseLinearAlgebra::Section1_SparseMatrixManipulations::FirstExample();
}

void TestChapter3Section2()
{
        
        Chapter3_SparseLinearAlgebra::Section1_SparseMatrixManipulations::TheSparseMatrixClass();
}

int main()
{
        //build pass
        TestChapter3Section1();   // ������һ��ͼƬ��titiled  "result.bmp"

        TestChapter3Section2();
        return 0;
}