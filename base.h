#pragma once
struct allResu
{
	int allTime;//���ʱ��
	QString allName;//�������

};
struct testResu
{
	int testTime;//���ʱ��
	QString testName;//�������
	int caliTime;//����ʱ��
	QVector<int> dataChecks;//��λ�Ƿ�ѡ��
	QVector<int> dataAD;//8����λ�ļ��ֵ
};
struct caliResu
{
	QString caliName;//��������
	int caliTime;//����ʱ��
	float dataCAL1;//CAL1
	float dataCAL2;//CAL2
	int    dataVlo;//�������
	QVector<int> dataChecks;//��λ�Ƿ�ѡ��
	QVector<float> dataA;//ֱ��ʽ��A
	QVector<float> dataB;//ֱ��ʽ��B
};



