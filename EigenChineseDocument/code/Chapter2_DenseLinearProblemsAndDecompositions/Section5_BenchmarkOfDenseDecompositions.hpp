#ifndef BENCHMARK_OF_DENSE_DECOMPOSITIONS_HPP
#define BENCHMARK_OF_DENSE_DECOMPOSITIONS_HPP
#include "HeaderFile.h"
namespace Chapter2_DenseLinearProblemsAndDecompositions
{
//complete pivoting��partial pivoting
// ��1�� complete pivoting����full pivoting���������ھ���ֽ���˹��Ԫ�Ĺ����У���Ԫ����δ���б任�������к���֮�����ѡ��Ҳ������Ҫͬʱ�����н������н�����
// ��2�� partial pivoting����ֻ�ڵ�ǰ���б任������ѡ����Ԫ��ֻ��Ҫ�����н���
namespace Section5_BenchmarkOfDenseDecompositions
{

// ��ҳ������Eigen��Ը��ַ���͹�Լ�������ṩ�ĳ��ܾ���ֽ���ٶȱȽϡ�

// �й�����������ͷֽ����������ֵ³���Եĸ�һ��ĸ�������鿴�˱�http://eigen.tuxfamily.org/dox/group__TopicLinearAlgebraDecompositions.html

// �û�׼���������䱸Intel Core i7 @ 2,6 GHz�ıʼǱ����������У�
//��ʹ��������AVX��FMAָ���û�ж��̵߳�clang���б��롣��ʹ�õ� ���� ������������˫���ȣ�������ͨ����ʱ�����2��������õĹ��ơ�

// �������ǶԳƵģ����ڹ���Լ���ľ��󣬱����ʱ�����$ A ^ TA $����Cholesky��LUΪǰ�ĸ����������Գ�Э�������ĳɱ�����*������ʾ��������Ͻǲ��֣� ����
//ʱ���Ժ���Ϊ��λ�����������������LLT�ֽ���Եģ��������ģ���Ҳ���ͨ������ɿ��ġ�

// �����/��С	8x8	100x100	1000x1000	4000x4000	10000x8	10000x100	10000x1000	10000x4000
// LLT	0.05	0.42	5.83	374.55	6.79 *	30.15 *	236.34 *	3847.17 *
// LDLT	0.07��x1.3��	0.65��x1.5��	26.86��x4.6��	2361.18��x6.3��	6.81��x1��*	31.91��x1.1��*	252.61��x1.1��*	5807.66��x1.5��*
// PartialPivLU	0.08��x1.5��	0.69��x1.6��	15.63��x2.7��	709.32��x1.9��	6.81��x1��*	31.32��x1��*	241.68��x1��*	4270.48��x1.1��*
// FullPivLU	0.1��x1.9��	4.48��x10.6��	281.33��x48.2��	--	6.83��x1��*	32.67��x1.1��*	498.25��x2.1��*	--
// HouseholderQR	0.19��x3.5��	2.18��x5.2��	23.42��x4��	1337.52��x3.6��	34.26��x5��	129.01��x4.3��	377.37��x1.6��	4839.1��x1.3��
// ColPivHouseholderQR	0.23��x4.3��	2.23��x5.3��	103.34��x17.7��	9987.16��x26.7��	36.05��x5.3��	163.18��x5.4��	2354.08��x10��	37860.5��x9.8��
// CompleteOrthogonalDecomposition	0.23��x4.3��	2.22��x5.2��	99.44��x17.1��	10555.3��x28.2��	35.75��x5.3��	169.39��x5.6��	2150.56��x9.1��	36981.8��x9.6��
// FullPivHouseholderQR	0.23��x4.3��	4.64��x11��	289.1��x49.6��	--	69.38��x10.2��	446.73��x14.8��	4852.12��x20.5��	--
// JacobiSVD	1.01��x18.6��	71.43��x168.4��	--	--	113.81��x16.7��	1179.66��x39.1��	--	--
// BDCSVD	1.07��x19.7��	21.83��x51.5��	331.77��x56.9��	18587.9��x49.6��	110.53��x16.3��	397.67��x13.2��	2975��x12.6��	48593.2��x12.6��
// *���˷ֽⲻ֧�ֶԹ���Լ�����������ֱ����С���˷���⣬�����������ʱ������γɶԳ�Э�������ĳɱ�$ A ^ TA $��

// �۲�����

// LLTʼ�������Ľ��������
// ���ںܴ�̶��Ϲ���Լ�������⣬Cholesky / LU�ֽ�ĳɱ���Ҫ�ɶԳ�Э�������ļ��������
// ���ڽϴ�����⣬ֻ��ʵ�ָ��ٻ����Ѻõķֿ���Եķֽ���ܺܺõؽ�����չ��
//��Щ����LLT��PartialPivLU��HouseholderQR��BDCSVD���������Ϊʲô����4k x 4k����HouseholderQR��LDLT���졣������LDLT��ColPivHouseholderQRҲ��ʵʩ�ֿ���ԡ�
// CompleteOrthogonalDecomposition����ColPivHouseholderQR����˿��Դﵽ��ͬ������ˮƽ��
// �ϱ�����bench / dense_solvers.cpp�ļ����ɵģ����������޸�������������Ӳ������������ϲ���������С��ƥ��ı�

} // namespace Section5_BenchmarkOfDenseDecompositions
} // namespace Chapter2_DenseLinearProblemsAndDecompositions
#endif