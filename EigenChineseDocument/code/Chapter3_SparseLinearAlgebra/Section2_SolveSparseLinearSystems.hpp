#ifndef SOLVE_SPARSE_LINEAR_SYSTEMS_HPP
#define SOLVE_SPARSE_LINEAR_SYSTEMS_HPP
#include "HeaderFile.h"

// http : //eigen.tuxfamily.org/dox/group__TopicSparseSystems.html
namespace Chapter3_SparseLinearAlgebra
{

//��Eigen�У���ϵ������ϡ��ʱ���м��ַ����������������ϵͳ��
// ���ڴ������������ʾ�����Ӧ����С�ģ��Ի�����õ����ܡ�
// �й�Eigen��ϡ��������ϸ���ܣ���μ�ϡ����������
//��ҳ���г���Eigen�п��õ�ϡ�����������������������Щ������������е���Ҫ���衣
//ȡ���ھ�������ԣ�����ľ��ȣ������û��ܹ�������Щ���裬��������������ܡ�
//��ע�⣬������Ҫ�����˽���Щ���豳������ݣ�
//���һ�����ṩ��һ����׼���̣��������ɵ�ʹ�����������˽����п�������������ܡ�
namespace Section2_SolveSparseLinearSystems
{

void ListofSparseSolvers()
{
        //  Here SPD means symmetric positive definite SPD��Ӧ�Գ���������
        //Eigen��ǰ�ṩ�˹㷺��������������Լ��ⲿ�������İ�װ�����±��л��������ǣ�

        // 1. ����ֱ�������: LLT LDLT��Ҫ������������LU��Ҫ����QR�������������

        // Class	Solver kind	Matrix kind	Features related to performance	License        Notes

        // SimplicialLLT
        // #include<Eigen/SparseCholesky>	Direct LLt factorization	SPD	Fill-in reducing	LGPL    SimplicialLDLT is often preferable

        // SimplicialLDLT
        // #include<Eigen/SparseCholesky>	Direct LDLt factorization	SPD	Fill-in reducing	LGPL  Recommended for very sparse and not too large problems (e.g., 2D Poisson eq.)

        // SparseLU
        // #include<Eigen/SparseLU>	LU factorization	Square	Fill-in reducing, Leverage fast dense algebra	MPL2   optimized for small and large problems with irregular patterns

        // SparseQR
        // #include<Eigen/SparseQR>	QR factorization	Any, rectangular	Fill-in reducing	MPL2	recommended for least-square problems, has a basic rank-revealing feature

        // 2.���õ��������

        //  Class	Solver kind	Matrix kind	Supported preconditioners, [default]	License  Notes

        // ConjugateGradient
        // #include<Eigen/IterativeLinearSolvers>	Classic iterative CG	SPD	IdentityPreconditioner, [DiagonalPreconditioner], IncompleteCholesky	MPL2
        // Recommended for large symmetric problems (e.g., 3D Poisson eq.)

        // LeastSquaresConjugateGradient
        // #include<Eigen/IterativeLinearSolvers>	CG for rectangular least-square problem	Rectangular	IdentityPreconditioner, [LeastSquareDiagonalPreconditioner]	MPL2
        // Solve for min |A'Ax-b|^2 without forming A'A

        // BiCGSTAB
        // #include<Eigen/IterativeLinearSolvers>	Iterative stabilized bi-conjugate gradient	Square	IdentityPreconditioner, [DiagonalPreconditioner], IncompleteLUT	MPL2	To speedup the convergence, try it with the IncompleteLUT preconditioner.

        //3.�ⲿ�����
        //         Class	Module	Solver kind	Matrix kind	Features related to performance	Dependencies,License   Notes
        // PastixLLT
        // PastixLDLT
        // PastixLU	PaStiXSupport	Direct LLt, LDLt, LU factorizations	SPD
        // SPD
        // Square	Fill-in reducing, Leverage fast dense algebra, Multithreading	Requires the PaStiX package, CeCILL-C	optimized for tough problems and symmetric patterns
        // CholmodSupernodalLLT	CholmodSupport	Direct LLt factorization	SPD	Fill-in reducing, Leverage fast dense algebra	Requires the SuiteSparse package, GPL
        // UmfPackLU	UmfPackSupport	Direct LU factorization	Square	Fill-in reducing, Leverage fast dense algebra	Requires the SuiteSparse package, GPL
        // SuperLU	SuperLUSupport	Direct LU factorization	Square	Fill-in reducing, Leverage fast dense algebra	Requires the SuperLU library, (BSD-like)
        // SPQR	SPQRSupport	QR factorization	Any, rectangular	fill-in reducing, multithreaded, fast dense algebra	requires the SuiteSparse package, GPL	recommended for linear least-squares problems, has a rank-revealing feature
        // PardisoLLT
        // PardisoLDLT
        // PardisoLU	PardisoSupport	Direct LLt, LDLt, LU factorizations	SPD
        // SPD
        // Square	Fill-in reducing, Leverage fast dense algebra, Multithreading	Requires the Intel MKL package, Proprietary	optimized for tough problems patterns, see also using MKL with Eigen
}

void SparseSolverConcept()
{
        // һ��ͨ�õ�����
        // #include <Eigen/RequiredModuleName>
        // // ...
        // SparseMatrix<double> A;
        // // fill A
        // VectorXd b, x;
        // // fill b
        // // solve Ax = b
        // SolverClassName<SparseMatrix<double>> solver;
        // solver.compute(A);
        // if (solver.info() != Success)
        // {
        //         // decomposition failed
        //         return;
        // }
        // x = solver.solve(b);
        // if (solver.info() != Success)
        // {
        //         // solving failed
        //         return;
        // }
        // // solve for another right hand side:
        // x1 = solver.solve(b1);

        // ����SPD��������ڶ�����ѡģ���������ָ������ʹ���ĸ������β��֣����磺
        //```
        // #include <Eigen / IterativeLinearSolvers>
        // ConjugateGradient <SparseMatrix <double>��Eigen :: Upper >�����;
        // x = Solver.compute��A��.solve��b��;

        // ```
        // �������ʾ���У��������������A�������ǲ��ֽ�����⡣����������ο���Ϊ�ջ��������ֵ��

        // �ڱ�����������ͬϡ��ģʽ�Ķ�����������£����Խ������㡱����ֽ����£�

        // SolverClassName<SparseMatrix<double>> �����;
        // Solver.analyzePattern��A��; //���ڴ˲��裬��ʹ��A����ֵ
        // resolver.factorize��A��;
        // x1 = Solver.solve��b1��;
        // x2 = Solver.solve��b2��;
        // ... A = ...; //�޸�A�ķ���ֵ������ģʽ���뱣�ֲ���
        // resolver.factorize��A��;
        // x1 = Solver.solve��b1��;
        // x2 = Solver.solve��b2��;
        // ...

        // ��compute����������Ч�ڵ���analyzerPattern������factorize������

        // ÿ����������ṩһЩ�ض����ܣ���������ʽ�������ӵķ��ʣ��������Ƶȡ��йظ�����ϸ��Ϣ����μ���Ӧ����ĵ���

        // ��󣬴�������������Ҳ�������޾������������ʹ�ã���μ�����ʾ����
}

void TheComputeStep()
{
        // ��compute���������У�ͨ���Ծ���������ӷֽ⣺LLT�����԰������LDLT������ͨ�������ؾ���LU���ڷǰ������ؾ���QR���ھ��ξ���
        //  ��Щ��ʹ��ֱ��������Ľ������������������������㲽���һ��ϸ��ΪanalyzerPattern������factorize������

        // analyticsPattern������Ŀ���ǶԾ���ķ���Ԫ�ؽ�������������ʹ�ֽⲽ�贴���������١�
        //�˲�������þ���Ľṹ����ˣ��ò���Ľ�������ھ���ṹ��ͬ����������ϵͳ��
        //������ע�⣬��ʱĳЩ�ⲿ�����������SuperLU��Ҫ���ڴ˲��������þ����ֵ����ƽ�������к��С�
        // ����������£��˲���Ľ����Ӧ����������һ��ʹ�á�

        // Eigen�ڴ˲������ṩ��һ�����޵ķ������Ծ����������������Щ�������������õģ�COLAMD��AMD�����ⲿ�ģ�METIS����
        // ��Щ�������������ģ������б������ã�

        // DirectSolverClassName <SparseMatrix <double>��OrderingMethod <IndexType>> solver;
        // �йؿ��÷��������ѡ����б���μ�OrderingMethodsģ�顣

        // ��factorize�����У�����ϵ�������������ÿ������ֵ����ʱ����Ӧ���ô˲��衣���ǣ�����Ľṹģʽ��Ӧ�ڶ������֮��ı䡣

        // ���ڵ�������������㲽��������������Ԥ�����������磬ʹ��ILUTԤ���������ڴ˲����м��㲻��ȫ����L��U��
        // ���ס�������ϣ�Ԥ��������Ŀ����ͨ�����ϵ��������и����������ֵ�ĸĽ�����ϵͳ���ӿ���������������ٶȡ�
        //����ʵ�����⣬���������Ӧʼ����ǰ������һ��ʹ�á���Eigen�У�ֻ�轫Ԥ��������Ϊģ�������ӵ���������������У�����ѡ��Ԥ��������

        // IterativeSolverClassName <SparseMatrix <double>��PreconditionerName <SparseMatrix <double>>�����;
        // ��Ա����preconditioner�������ض�preconditioner�Ķ�д������ֱ�����佻�����йؿ��÷������б���μ����������ģ���ÿ������ĵ���
}

void TheSolveStep()
{
        //resolve()�����������һ�������Ҳ������ϵͳ�Ľ⡣
        // X = Solver.solve��B��;
        // �ڴˣ�B������������������и����γɲ�ͬ���Ҳࡣ���Զ�ε���solve�������������磬�������Ҳ඼�޷�ͬʱʹ��ʱ��

        // x1 = Solver.solve��b1��;
        // //��õڶ����Ҳ�b2
        // x2 = Solver.solve��b2��;
        // // ...
        // ����ֱ�ӷ�������������Ի������ȼ��㡣
        // ��ʱ�������������̫��ȷ������������£��������������ʣ����ҿ�����ʹ��setTolerance��������ⲽ��֮ǰ��������ľ��ȡ�
        // �й����п��ù��ܣ�����ġ� �����������ģ����ĵ���
}

void BenchmarkRoutine()
{

        // �����ʱ������Ҫ֪�����ǽ��ϵͳ�����ʱ�䣬��ϣ��ʲô������ʵ��������
        // ��Eigen�У������ṩ�˿����ڴ�Ŀ�ĵĻ�׼���̡����Ƿǳ�����ʹ�á�
        // �ڹ���Ŀ¼�У�������bench / spbench��ͨ������make spbenchsolver���������̡�
        // ʹ�èChelpѡ���������Ի�ȡ���п���ѡ����б������ϣ�Ҫ���Եľ���ӦΪMatrixMarket�����ʽ���������̴�Eigen�����п������������ͳ����Ϣ��
        // Ҫ�Ծ����г���ʽ����������Ҳ�ʸ��������ʹ�ò���֧�ֵ�SparseExtraģ�飺
        // #include <unsupported / Eigen / SparseExtra>
        // ...
        // Eigen :: saveMarket��A���� filename.mtx����;
        // Eigen :: saveMarket��A���� filename_SPD.mtx����Eigen :: Symmetric��; //���AΪ�Գ�����
        // Eigen :: saveMarketVector��B���� filename_b.mtx����;
        // �±��ṩ��һЩEigen���ú��ⲿ�������XMLͳ����Ϣʾ����
        // �μ��ĵ������ﲻ�г���
}
} // namespace Section2_SolveSparseLinearSystems

} // namespace Chapter3_SparseLinearAlgebra
#endif