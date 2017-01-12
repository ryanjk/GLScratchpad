#include "mainwindow.h"

#include <fstream>

#include <qevent.h>
#include <qfiledialog.h>
#include "json.h"

#include "cameraview.h"
#include "programview.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), is_program_loaded_{false}
{
	ui.setupUi(this);

	command_queue_ = std::make_shared<glsp::ConcurrentCommandQueue>();
	ui.applicationFrameWidget->SetCommandQueue(command_queue_);
	ui.applicationFrameWidget->InitCommandThread();

	camera_view_ = new CameraView(this);
	program_view_ = new ProgramView(this, command_queue_.get());
	
	UpdateMenuView();
}

MainWindow::~MainWindow()
{

}

// ----- SLOTS ----- //

void MainWindow::OpenProgram() {
	QString filename = QFileDialog::getOpenFileName(
		this,
		tr("Load Program"),
		QDir::currentPath(),
		tr("Shader Program files (*.json);;All files (*.*)"));
	if (!filename.isNull()) {
		std::ifstream file(filename.toStdString());
		nlohmann::json shader_program;
		file >> shader_program;
		program_view_->InitializeProgram(shader_program);
	}

	is_program_loaded_ = true;
	UpdateMenuView();

	program_view_->show();
	program_view_->move(this->pos() + QPoint(this->width() + 20, 0));
}

void MainWindow::CloseCurrentProgram() {
	glsp::Command close_program_command = [](glsp::Application* application) {
		application->CloseProgram();
	};
	command_queue_->Enqueue(close_program_command);

	camera_view_->hide();

	program_view_->hide();
	program_view_->ClearProgramView();

	is_program_loaded_ = false;
	UpdateMenuView();
}

void MainWindow::ShowCameraView() {
	camera_view_->show();
}

void MainWindow::ShowProgramView() {
	program_view_->show();
}

// ------ END SLOTS ------ //

void MainWindow::closeEvent(QCloseEvent* evt) {
	QMainWindow::closeEvent(evt);
	ui.applicationFrameWidget->StopCommandThread();
}

void MainWindow::resizeEvent(QResizeEvent* evt) {
	QMainWindow::resizeEvent(evt);
	ui.applicationFrameWidget->resize(evt->size());
}

void MainWindow::showEvent(QShowEvent* evt) {
	QMainWindow::showEvent(evt);	
}

void MainWindow::UpdateMenuView() {
	ui.actionOpen_Program->setEnabled(!is_program_loaded_);
	ui.menuCamera->setEnabled(is_program_loaded_);
	ui.menuProgram->setEnabled(is_program_loaded_);
	ui.actionClose_Program->setEnabled(is_program_loaded_);
}
