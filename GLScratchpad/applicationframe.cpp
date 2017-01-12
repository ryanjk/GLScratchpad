#include "applicationframe.h"

#include <qevent.h>

ApplicationFrame::ApplicationFrame(QWidget *parent)
	: QGLWidget(parent), command_thread_(this) {
	setAutoBufferSwap(false);
}

ApplicationFrame::~ApplicationFrame() {

}

void ApplicationFrame::SetCommandQueue(std::shared_ptr<glsp::ConcurrentCommandQueue> command_queue) {
	command_queue_ = command_queue;
	command_thread_.SetCommandQueue(command_queue);
}

void ApplicationFrame::InitCommandThread() {
	doneCurrent();
	context()->moveToThread(&command_thread_);
	command_thread_.start();
}

void ApplicationFrame::StopCommandThread() {
	command_thread_.stop();
	command_thread_.wait();
}

void ApplicationFrame::resizeEvent(QResizeEvent* evt) {
	int width = evt->size().width();
	int height = evt->size().height();
	glsp::Command resize_command = [=](glsp::Application* application) {
		application->Resize(width, height);
	};
	command_queue_->Enqueue(resize_command);
}

void ApplicationFrame::paintEvent(QPaintEvent* evt) {

}

void ApplicationFrame::closeEvent(QCloseEvent* evt) {
	QGLWidget::closeEvent(evt);
	StopCommandThread();
}