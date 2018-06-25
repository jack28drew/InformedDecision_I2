#ifndef INFORMEDDECISION_H_
#define INFORMEDDECISION_H_

#include <QApplication>
#include <QMainWindow>
#include <QDockWidget>
#include <QGroupBox>
#include <QString>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QSpinBox>
#include <QLineEdit>
#include <QListWidget>
#include <QDial>
#include <QLCDNumber>
#include <QPushButton>
#include <QFile>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include <QBoxLayout>


class InformedDecision : public QMainWindow {
	Q_OBJECT
public:
	explicit InformedDecision();

private slots:
    void createOutputWidget();
    void openFile();
    void saveFile();

private:
    QDockWidget *studentInfoWindow;
    QTextEdit *textEdit;
	QComboBox *studentType;
	QDoubleSpinBox *gpaSpinBox;
    QSlider *satSlider;
	QSpinBox *satSpinBox;
	QLineEdit *fundsInput;
	QListWidget *hobbiesList;
    QDial *distanceInput;
    QLCDNumber *distanceDisplay;
	QPushButton *okButton;
	QPushButton *cancelButton;

    QGroupBox *universityBox;
    QGroupBox *majorsBox;

    QVBoxLayout *studentInfoLayout;

    QMenuBar *menuBar;
    QAction *quitAct;
    QAction *openAct;
    QAction *saveAct; 
    QAction *helpAct;

    void createDockWidget();
    void createDockWidget2();
    void okButtonPressed();
	QGroupBox *createStudentTypeWidget();
	QGroupBox *createGPAWidget();
	QGroupBox *createSATWidget();
	QGroupBox *createFundsWidget();
	QGroupBox *createHobbiesWidget();
    QGroupBox *createDistanceWidget();
    QGroupBox *createUniversityList();
    QGroupBox *createMajorsList();
	QVBoxLayout *createLayout();

    void createMenuBar();
};

#endif //IFORMEDDECISION_H_