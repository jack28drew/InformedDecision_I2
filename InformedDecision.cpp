#include "InformedDecision.h"

InformedDecision::InformedDecision(QWidget *parent) :QWidget(parent) {
	setWindowTitle("Informed Decision");
	setLayout(mainLayout);
}

void InformedDecision::createStudentTypeWidget() {
	QStringList list = (QStringList() << "High School Student" << "University Freshman" << "University Sophomore");

	studentType = new QComboBox;
	studentType->addItems(list);

	studentTypeLabel = new QLabel;
	studentTypeLabel->setText("StudentType: ");
}

void InformedDecision::createGPAWidget() {
	gpaSpinBox = new QDoubleSpinBox;
	gpaSpinBox->setDecimals(2);
	gpaSpinBox->setSingleStep(0.01);
	gpaSpinBox->setRange(0,4);
	gpaSpinBox->setValue(3.00);

	gpaSpinBoxLabel = new QLabel;
	gpaSpinBoxLabel->setText("Current GPA: ");
}

void InformedDecision::createSATWidget() {
	satSlider = new QSlider(QT::Horizontal);
	satSlider->setRange(400, 1600);
	satSlider->setValue(1000);

	satSpinBox = new QSpinBox;
	satSpinBox->setRange(400, 1600);
	satSpinBox->setValue(1000);

	QObject::connect(satSlider, SIGNAL(valueChanged(int)), satSpinBox, SLOT(setValue(int)));
	QObject::connect(satSpinBox, SIGNAL(valueChanged(int)), satSlider, SLOT(setValue(int)));

	satLabel = new QLabel;
	satLabel->setText("SAT Score: ");
}

void InformedDecision::createFundsWidget() {

}

void InformedDecision::createHobbiesWidget() {

}

void InformedDecision::createButtons() {

}

void InformedDecision::createLayout() {

}