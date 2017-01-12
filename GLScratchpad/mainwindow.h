#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

#include <memory>

#include "ConcurrentCommandQueue.h"

class CameraView;
class ProgramView;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();


public slots:
	void OpenProgram();
	void CloseCurrentProgram();
	void ShowCameraView();
	void ShowProgramView();

protected:
	void closeEvent(QCloseEvent*);
	void resizeEvent(QResizeEvent*);
	void showEvent(QShowEvent*);

private:
	Ui::MainWindowClass ui;
	std::shared_ptr<glsp::ConcurrentCommandQueue> command_queue_;
	CameraView* camera_view_;
	ProgramView* program_view_;
	bool is_program_loaded_;

private:
	void UpdateMenuView();
};

#endif // MAINWINDOW_H
