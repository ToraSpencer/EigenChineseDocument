#include "Chapter2_DenseLinearProblemsAndDecompositions/Section1_LinearAlgebraAndDecompositions.hpp"
#include "Chapter2_DenseLinearProblemsAndDecompositions/Section2_CatalogueOfDenseDecompositions.hpp"
#include "Chapter2_DenseLinearProblemsAndDecompositions/Section3_SolvingLinearLeastSquaresSystems.hpp"
#include "Chapter2_DenseLinearProblemsAndDecompositions/Section4_InplaceDecompisitions.hpp"
#include "Chapter2_DenseLinearProblemsAndDecompositions/Section5_BenchmarkOfDenseDecompositions.hpp"

void PrintMsg(int i)
{
        cout << endl
             << "*******  Results   of   Chapter2   Section" << i << "  ********" << endl;
}

void TestChapter2Section1()
{
        PrintMsg(1);
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::BasicLinearSolving();
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::CheckingIfASolutionReallyExists();
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::ComputingEigenvaluesAndEigenvectors();
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::ComputingInverseAndDeterminant();
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::LeastSquaresSolving();
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::RankRevealingDecompositions();
        Chapter2_DenseLinearProblemsAndDecompositions::Section1_LinearAlgebraAndDecompositions::SeparatingTheComputationFromTheConstruction();
}

void TestChapter2Section2()
{
        //�ⲿ��û�г�����Ҫ������ܾ���ķֽ�
}

void TestChapter2Section3()
{
        PrintMsg(3);
        //���۵����ַ�����SVD�ֽ⣬QR�ֽ����̬���̡�
        //���У�SVD�ֽ�ͨ����׼ȷ�����������򷽳�(normal equations)��쵫�׼ȷ��QR�ֽ��������֮�䡣
        Chapter2_DenseLinearProblemsAndDecompositions::Section3_SolvingLinearLeastSquaresSystems::UsingNormalEquations();
        Chapter2_DenseLinearProblemsAndDecompositions::Section3_SolvingLinearLeastSquaresSystems::UsingTheQRDecomposition();
        Chapter2_DenseLinearProblemsAndDecompositions::Section3_SolvingLinearLeastSquaresSystems::UsingTheSvdDecomposition();
}
void TestChapter2Section4()
{
        PrintMsg(4);
        Chapter2_DenseLinearProblemsAndDecompositions::Section4_InplaceDecompisitions::InplaceMatrixDecompositions();
}
void TestChapter2Section5()
{
        //�ⲿ��û�г��򣬽�������Ը��ַ���͹�Լ�������ṩ�ĳ��ܾ���ֽ���ٶȱȽϡ�
}
int main()
{
        // build pass
        TestChapter2Section1();

        // build pass
        TestChapter2Section3();

        // build pass
        TestChapter2Section4();

        return 0;
}