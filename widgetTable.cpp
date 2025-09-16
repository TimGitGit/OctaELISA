#include "widgetTable.h"

widgetTable::widgetTable(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//ui.logTabWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//�п�
	ui.logTabWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//�и�
	//���õ�ѡģʽ
	ui.logTabWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	//����������ʱΪ����
	ui.tableBack->setCursor(QCursor(Qt::PointingHandCursor));
	ui.comTable->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tableUp->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tableNext->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tableJump->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tableRemove->setCursor(QCursor(Qt::PointingHandCursor));
	ui.tableRemoveAll->setCursor(QCursor(Qt::PointingHandCursor));

	//����QCombo
	ui.comTable->setView(new QListView());
	//initHeader(QStringList() << QStringLiteral( "�ʿ�ʱ��") << QStringLiteral( "����") << QStringLiteral("���") << QStringLiteral("��ע"));
	inconn();
	currentPageSum = 8;
	currentPage = 1;
}

widgetTable::~widgetTable()
{
	//delete& ui;
}
void widgetTable::inconn()
{
	//connect(ui.logTabWidget, SIGNAL(itemSelectionChanged(int row, int col)), this, SLOT(settingTableChanged(int row, int col)));


	QObject::connect(ui.logTabWidget, &QTableWidget::itemClicked, [=]() {
		//����鿴����ʱ
		QTableWidgetItem* curItem = ui.logTabWidget->currentItem();
		if (curItem != NULL) {
			qDebug() << curItem->column() << curItem->row();
			if (curItem->column() == 0) {
				if (curItem->checkState()) {
					qDebug() << curItem->column() << curItem->row();
					for (int row = 0; row < ui.logTabWidget->rowCount(); row++) {
						if (row != curItem->row()) {
							QTableWidgetItem* item = ui.logTabWidget->item(row, 0); // ��һ���� checkbox ��
							if (item) {
								item->setCheckState(Qt::Unchecked);
							}
						}
					}
				}
			}
			if (curItem->column() == 4) {
				//��ȡ��Ԫ���ڵ�����  
				int nowRow = curItem->row();
				QString data1 = ui.logTabWidget->item(nowRow, 1)->text();
				QString data2 = ui.logTabWidget->item(nowRow, 2)->text();
				QString data3 = ui.logTabWidget->item(nowRow, 3)->text();
				emit showResult(data1, data2, data3);
			}
		}
		});
	QObject::connect(ui.comTable, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
		searchType(index);
		});
	QObject::connect(ui.tableRemoveAll, &QPushButton::clicked, [=]() {
		int res;
		MyMessageBox msgBox(this, MsgBoxType_Warn, QStringLiteral("��ȷ���Ƿ�Ҫȫ��ɾ��"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
		res = msgBox.exec();

		if (res == QDialog::Accepted)
		{
			emit removeAll();
		}
		});

}
/**
 * @brief Widget::getCheckAll �Ա�����ȫѡ����ȫ����ѡ
 * @param check �ж���ȫѡ����ȫ����ѡ
 */
void widgetTable::getCheckAll(int check) {
	int count = ui.logTabWidget->rowCount();
	if (count == 0) {//��ǰ��������
		emit backCheckAll();
		int res;
		MyMessageBox msgBox(this, MsgBoxType_Error, QStringLiteral("�������޷�ѡ��"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
		res = msgBox.exec();
	}
	else {
		if (check == 1) {//ȫѡ
			for (int i = 0; i < count; i++) {
				ui.logTabWidget->item(i, 0)->setCheckState(Qt::Checked);
			}
		}
		else {//ȫ����ѡ
			for (int i = 0; i < count; i++) {
				ui.logTabWidget->item(i, 0)->setCheckState(Qt::Unchecked);
			}
		}
	}

}
/**
 * @brief Widget::getDeleteData ɾ�����Ԫ��
 */
void widgetTable::getDeleteData() {
	int count = ui.logTabWidget->rowCount();
	int checkNum = 0;
	for (int i = 0; i < count; i++) {
		if (ui.logTabWidget->item(i, 0)->checkState() == Qt::Checked) {
			checkNum++;
		}
	}
	if (checkNum > 0) {
		int res;
		MyMessageBox msgBox(this, MsgBoxType_Warn, QStringLiteral("��ȷ���Ƿ�Ҫɾ������"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
		res = msgBox.exec();

		if (res == QDialog::Accepted)
		{
			for (int row = ui.logTabWidget->rowCount() - 1; row >= 0; row--)
			{
				if (ui.logTabWidget->item(row, 0)->checkState() == Qt::Checked) {
					QDateTime nowTime = QDateTime::fromString(ui.logTabWidget->item(row, 3)->text(), "yyyy.MM.dd hh:mm:ss"); // ��QStringת��ΪQDateTime����
					int timestamp = nowTime.toSecsSinceEpoch(); // ��QDateTime����ת��Ϊʱ���
					emit removeOne(timestamp);
				}
			}
			//emit backCheckAll();
			//m_lDatas.clear();
			//m_lDatas = m_lDatasAll;
			//updataPage();
			//updataPageData();
		}
	}
	else {//��ѡ������
		int res;
		MyMessageBox msgBox(this, MsgBoxType_Error, QStringLiteral("��ѡ������"), QStringLiteral("ȷ��"), QStringLiteral("ȡ��"));
		res = msgBox.exec();



	}
}
void widgetTable::getDeleteAllData()
{
	for (int row = ui.logTabWidget->rowCount() - 1; row >= 0; row--)
	{
		m_lDatasAll.removeAt((currentPage - 1) * 8 + row);

	}
	m_lDatas.clear();
	m_lDatas = m_lDatasAll;
	updataPage();
	updataPageData();
}
void widgetTable::getDeleteOneData()
{
	for (int row = ui.logTabWidget->rowCount() - 1; row >= 0; row--)
	{
		if (ui.logTabWidget->item(row, 0)->checkState() == Qt::Checked) {
			//ui->logTabWidget->removeRow(row);
			m_lDatasAll.removeAt((currentPage - 1) * 8 + row);
		}
	}
	emit backCheckAll();
	m_lDatas.clear();
	m_lDatas = m_lDatasAll;
	updataPage();
	updataPageData();
}
/**
 * @brief Widget::searchType �Ա����а���������
 * @param type ���ͷ��ࣺҺ���ʿ�Ϊ0�������ʿ�Ϊ1
 */
void widgetTable::searchType(int type) {
	QList<QVariantList> m_lDatasSearch;
	QString comData;
	if (type == 0) {//ȫ����Ŀ
		for (int i = 0; i < m_lDatasAll.size(); i++) {

			if (m_lDatasAll[i][1].toString() == QStringLiteral("�����Ŀ") || m_lDatasAll[i][1].toString() == QStringLiteral("������Ŀ")) {
				m_lDatasSearch.append(m_lDatasAll[i]);

			}
		}
		m_lDatas.clear();
		m_lDatas = m_lDatasSearch;
		currentPage = 1;
		updataPage();
		updataPageData();
		
	}
	else if(type == 1){//�����Ŀ
		comData = QStringLiteral("�����Ŀ");
		for (int i = 0; i < m_lDatasAll.size(); i++) {

			if (m_lDatasAll[i][1].toString() == comData) {
				m_lDatasSearch.append(m_lDatasAll[i]);

			}
		}
		m_lDatas.clear();
		m_lDatas = m_lDatasSearch;
		currentPage = 1;
		updataPage();
		updataPageData();
	}
	else if (type == 2) {
		comData = QStringLiteral("������Ŀ");
		for (int i = 0; i < m_lDatasAll.size(); i++) {

			if (m_lDatasAll[i][1].toString() == comData) {
				m_lDatasSearch.append(m_lDatasAll[i]);

			}
		}
		m_lDatas.clear();
		m_lDatas = m_lDatasSearch;
		currentPage = 1;
		updataPage();
		updataPageData();
	}
	
	//emit searchOk();
}



void widgetTable::updataPage()
{
	if (m_lDatas.size() <= 8) {
		pageSum = 1;
	}
	if ((m_lDatas.size() % 8) == 0) {
		pageSum = m_lDatas.size() / 8;

	}
	else {
		pageSum = (m_lDatas.size() / 8) + 1;
	}

	ui.label->setText(QString("%1/%2").arg(currentPage).arg(pageSum));
}

void widgetTable::updataPageData()
{
	if (currentPage == 0) {
		return;
	}

	//��ȡ�����±� ����ǰҳ��*��ǰҳ��������-��ǰҳ��������= ĳһҳ�ĵ�һ���ľ��������±�
	int index = (currentPage * currentPageSum) - currentPageSum;

	//ɾ��
	for (int row = ui.logTabWidget->rowCount() - 1; row >= 0; row--)
	{
		ui.logTabWidget->removeRow(row);
	}
	if (m_lDatas.size() > 0) {
		int i = 0;
		for (; index < m_lDatas.size(); ++index) {
			if (index >= (currentPage * currentPageSum)) {
				break;
			}


			int rowcount = ui.logTabWidget->rowCount();
			ui.logTabWidget->insertRow(rowcount);

			QVariantList varList = m_lDatas.at(index);
			for (int j = 0; j < varList.size(); ++j) {
				QTableWidgetItem* item = new QTableWidgetItem();
				if (j == 0)
					item->setCheckState(Qt::Unchecked);
				if (j == 4)
					item->setIcon(QIcon(":/images/image/chakan.png"));
				item->setData(0, varList.at(j));
				item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
				ui.logTabWidget->setItem(i, j, item);
			}
			i++;
		}
	}
	else {
		int i = 0;
		for (; index < m_lDatas.size(); ++index) {
			if (index >= (currentPage * currentPageSum)) {
				break;
			}
			int rowcount = ui.logTabWidget->rowCount();
			ui.logTabWidget->insertRow(rowcount);

			QVariantList varList = m_lDatas.at(index);
			for (int j = 0; j < varList.size(); ++j) {
				QTableWidgetItem* item = new QTableWidgetItem();
				if (j == 0)
					item->setCheckState(Qt::Unchecked);
				if (j == 3)
					item->setIcon(QIcon(":/images/image/chakan.png"));
				item->setData(0, varList.at(j));
				item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
				ui.logTabWidget->setItem(i, j, item);
			}
			i++;
		}



	}

}

void widgetTable::initHeader(const QStringList& headers)
{
	ui.logTabWidget->setAlternatingRowColors(true);//���汳��ɫ
	//ui.logTabWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ��ʱΪ����ѡ��       
	ui.logTabWidget->setColumnCount(headers.size());
	ui.logTabWidget->setHorizontalHeaderLabels(headers);
	ui.logTabWidget->verticalHeader()->setHidden(false);
	ui.logTabWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//ui.logTabWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//�и�
	ui.logTabWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//�п�
	ui.logTabWidget->verticalHeader()->setDefaultSectionSize(48);
	QHeaderView* header = ui.logTabWidget->verticalHeader();
	header->setHidden(true);// �����к�
}



void widgetTable::addLogData(const QVariantList& data)
{
	m_lDatas.append(data);
	updataPageData();
	updataPage();
}

void widgetTable::addLogDatas(const QList<QVariantList>& datas)
{
	m_lDatas.append(datas);
	currentPage = 1;
	updataPageData();
	updataPage();
}
void widgetTable::on_tableBack_clicked()
{
	//����
	emit tableBack();
}

void widgetTable::on_tableUp_clicked()
{
	//��һҳ
	emit backCheckAll();

	if (currentPage == 1) {
		return;
	}

	currentPage--;
	updataPageData();
	updataPage();
}

void widgetTable::on_tableNext_clicked()
{
	//��һҳ
	emit backCheckAll();
	if (currentPage >= pageSum) {
		return;
	}
	currentPage++;
	updataPageData();
	updataPage();
}

void widgetTable::on_tableJump_clicked()
{
	//��ת
	emit backCheckAll();
	if (ui.spinBox->value() > pageSum
		|| currentPage == ui.spinBox->value()
		|| ui.spinBox->value() == 0
		|| pageSum == 1) {
		return;
	}
	currentPage = ui.spinBox->value();
	updataPageData();
	updataPage();
}

void widgetTable::on_tableRemove_clicked()
{
	//ɾ��
	getDeleteData();
}
