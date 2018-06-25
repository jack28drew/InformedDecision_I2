#include "InformedDecision.h"

InformedDecision::InformedDecision() : textEdit(new QTextEdit) {
	setWindowTitle("Informed Decision");
    resize(800, 1000);
    setCentralWidget(textEdit);
    createDockWidget();
    createMenuBar();
    setMenuBar(menuBar); 

    universityBox = NULL;
    majorsBox = NULL;
}

void InformedDecision::createDockWidget() {
    studentInfoWindow = new QDockWidget("Student Info", this);
    studentInfoWindow->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, studentInfoWindow);

    QWidget *dockContents = new QWidget;
    dockContents->setLayout(createLayout());
    studentInfoWindow->setWidget(dockContents);
}

QGroupBox *InformedDecision::createStudentTypeWidget() {
	QStringList list = (QStringList() << "High School Student" << "University Freshman" 
                                      << "University Sophomore");

	studentType = new QComboBox;
	studentType->addItems(list);

	QGroupBox *box = new QGroupBox;
    box->setTitle("Student Type");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(studentType);

    box->setLayout(layout);
    return box;
}

QGroupBox *InformedDecision::createGPAWidget() {
	gpaSpinBox = new QDoubleSpinBox;
	gpaSpinBox->setDecimals(2);
	gpaSpinBox->setSingleStep(0.01);
	gpaSpinBox->setRange(0,4);
	gpaSpinBox->setValue(3.00);

    QGroupBox *box = new QGroupBox;
    box->setTitle("Current GPA");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(gpaSpinBox);

    box->setLayout(layout);
    return box;
}

QGroupBox *InformedDecision::createSATWidget() {
	satSlider = new QSlider(Qt::Horizontal);
	satSlider->setRange(400, 1600);
	satSlider->setValue(1000);

	satSpinBox = new QSpinBox;
	satSpinBox->setRange(400, 1600);
	satSpinBox->setValue(1000);

	QObject::connect(satSlider, SIGNAL(valueChanged(int)), satSpinBox, SLOT(setValue(int)));
	QObject::connect(satSpinBox, SIGNAL(valueChanged(int)), satSlider, SLOT(setValue(int)));

    QGroupBox *box = new QGroupBox;
    box->setTitle("SAT Score");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(satSlider);
    layout->addWidget(satSpinBox);

    box->setLayout(layout);
    return box;
}

QGroupBox *InformedDecision::createFundsWidget() {
    fundsInput = new QLineEdit;

    QGroupBox *box = new QGroupBox;
    box->setTitle("Available Funds");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(fundsInput);

    box->setLayout(layout);
    return box;
}

QGroupBox *InformedDecision::createHobbiesWidget() {
    QStringList hobbies;
    hobbies << "3D Printing" << "Cooking" << "Dance" << "Drawing" << "Exercise" 
            << "Camping & Hiking" << "Flying" << "Photography" << "Swimming";

    hobbiesList = new QListWidget;
    hobbiesList->addItems(hobbies);

    QListWidgetItem *item = 0;
    for(int i=0; i < hobbiesList->count(); i++){
        item = hobbiesList->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
    }

    QGroupBox *box = new QGroupBox;
    box->setTitle("Hobbies");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(hobbiesList);

    box->setLayout(layout);
    return box;
}

QGroupBox *InformedDecision::createDistanceWidget() {
    distanceInput = new QDial;
    distanceInput->setMaximum(1000);
    distanceInput->setSingleStep(10);

    distanceDisplay = new QLCDNumber;
    distanceDisplay->setDigitCount(5);
    distanceDisplay->setDecMode();
    QObject::connect(distanceInput, SIGNAL(valueChanged(int)), distanceDisplay, SLOT(display(int)));

    QGroupBox *box = new QGroupBox;
    box->setTitle("Maximum Distance");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(distanceInput);
    layout->addWidget(distanceDisplay);

    box->setLayout(layout);
    return box;
}

QGroupBox *InformedDecision::createUniversityList() {
    QFile file("universities.data");
    file.open(QIODevice::ReadOnly);

    QStringList universities;

    double gpa = gpaSpinBox->value();
    int sat = satSpinBox->value();
    int funds = fundsInput->text().toInt();

    while(!file.atEnd()) {
        QString line = file.readLine();
        QStringList info = line.split(',');

        if(gpa >= info[1].toDouble() && sat >= info[2].toInt() && funds >= info[3].toInt()) 
            universities << info[0];
    }

    QListWidget *universityList = new QListWidget;
    universityList->addItems(universities);
    universityList->setResizeMode(QListView::Adjust);

    QGroupBox *box = new QGroupBox;
    box->setTitle("Recommended Universities");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(universityList);

    box->setLayout(layout);
    return box;
}

QGroupBox *InformedDecision::createMajorsList() {
    QFile file("majors.data");
    file.open(QIODevice::ReadOnly);

    QStringList majors;

    while(!file.atEnd()) {
        QString line = file.readLine();
        majors << line.simplified();
    }

    QListWidget *majorsList = new QListWidget;
    majorsList->addItems(majors);

    QGroupBox *box = new QGroupBox;
    box->setTitle("Recommended Majors");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(majorsList);

    box->setLayout(layout);
    return box;
}

void InformedDecision::okButtonPressed() {
    QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(createOutputWidget()));
}

void InformedDecision::createOutputWidget() {
    QString input = studentType->currentText();

    if(input == "High School Student") {
        if(majorsBox != NULL) {
            delete majorsBox;
            majorsBox = NULL;
        }
        if(universityBox != NULL) {
            delete universityBox;
            universityBox = NULL;
        }
        studentInfoLayout->addWidget(universityBox = createUniversityList());
    }

    else if(input == "University Freshman" || input == "University Sophomore") {
        if(universityBox != NULL) {
            delete universityBox;
            universityBox = NULL;
        }
        if(majorsBox != NULL) {
            delete majorsBox;
            majorsBox = NULL;
        }
        studentInfoLayout->addWidget(majorsBox = createMajorsList());
    }
    studentInfoLayout->setStretch(6,3);
}

QVBoxLayout *InformedDecision::createLayout() {
    studentInfoLayout = new QVBoxLayout;

    studentInfoLayout->addWidget(createStudentTypeWidget());
    studentInfoLayout->addWidget(createGPAWidget());
    studentInfoLayout->addWidget(createSATWidget());
    studentInfoLayout->addWidget(createFundsWidget());
    studentInfoLayout->addWidget(createHobbiesWidget());
    studentInfoLayout->addWidget(createDistanceWidget());
    studentInfoLayout->addWidget(okButton = new QPushButton("OK"));
    okButtonPressed();

    return studentInfoLayout;
}

void InformedDecision::createMenuBar() {
    menuBar = new QMenuBar();

    QMenu *file = new QMenu("File");
    menuBar->addMenu(file);

    openAct = new QAction("Open", file);
    QObject::connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));
    file->addAction(openAct);

    saveAct = new QAction("Save", file);
    QObject::connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));
    file->addAction(saveAct);

    quitAct = new QAction("Quit", file);
    QObject::connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));
    file->addAction(quitAct);

    QMenu *help = new QMenu("Help");
    menuBar->addMenu(help);

    helpAct = new QAction("help", help);
    help->addAction(helpAct);
}

void InformedDecision::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open", "text files (*.txt)", "text files (*.txt)");
   
    if(fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, "Unable to open file", file.errorString());
            return;
        }
        file.open(QIODevice::ReadOnly);
        QTextStream readFile(&file);
        textEdit->setText(readFile.readAll());

    }
}

void InformedDecision::saveFile() {
    QFileDialog dialog(this);
    QString fileName = dialog.getSaveFileName(this, "Save", "", "Text files (*.txt)");

    if(fileName.isEmpty())
        return;
    else {
        QFile file(fileName);

        if(!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, "Unable to open file", file.errorString());
            return;
        }
        file.open((QIODevice::WriteOnly));
        QTextStream writeFile(&file);
        writeFile << textEdit->toPlainText();
    }
    dialog.setDefaultSuffix("txt");
}
