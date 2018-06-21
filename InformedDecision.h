#ifndef INFORMEDDECISION_H_
#define INFORMEDDECISION_H_

#include <QApplication>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QSpinBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QFile>

#include <QVBoxLayout>

class InformedDecision : public QWidget {
	Q_OBJECT
public:
	explicit InformedDecision(QWidget *parent = 0);

private:
	QVBoxLayout * mainLayout;

	QComboBox *studentType;
	QLabel *studentTypeLabel;
	QDoubleSpinBox *gpaSpinBox;
	QLabel *gpaSpinBoxLabel;
	QSlider *satSlider;
	QSpinBox *satSpinBox;
	QLabel *satLabel;
	QLineEdit *fundsInput;
	QLabel *fundsLabel;
	QListWidget *hobbiesList;
	QLabel *hobbiesLabel;
	QPushButton *okButton;
	QPushButton *cancelButton;

	void createStudentTypeWidget();
	void createGPAWidget();
	void createSATWidget();
	void createFundsWidget();
	void createHobbiesWidget();
	void createButtons();

	void createLayout();
};

#endif //IFORMEDDECISION_H_