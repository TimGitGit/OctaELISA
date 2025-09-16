#pragma once
struct allResu
{
	int allTime;//检测时间
	QString allName;//检测名称

};
struct testResu
{
	int testTime;//检测时间
	QString testName;//检测名称
	int caliTime;//定标时间
	QVector<int> dataChecks;//孔位是否选中
	QVector<int> dataAD;//8个孔位的检测值
};
struct caliResu
{
	QString caliName;//定标名称
	int caliTime;//定标时间
	float dataCAL1;//CAL1
	float dataCAL2;//CAL2
	int    dataVlo;//样本体积
	QVector<int> dataChecks;//孔位是否选中
	QVector<float> dataA;//直线式的A
	QVector<float> dataB;//直线式的B
};



