#include "MainWindow.xaml.h"
#include "DataModel.h"

MainWindow::MainWindow() {
    InitializeComponent();

    DataModel* dataModel = new DataModel();
    this->DataContext = dataModel;

    dataModel->startMonitoring();
}
