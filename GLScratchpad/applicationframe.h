#ifndef APPLICATIONFRAME_H
#define APPLICATIONFRAME_H

#include <QGLWidget>

#include <memory>

#include "applicationcommandthread.h"
#include "ConcurrentCommandQueue.h"

class ApplicationFrame : public QGLWidget
{
	Q_OBJECT

public:
	ApplicationFrame(QWidget *parent);
	~ApplicationFrame();

	void SetCommandQueue(std::shared_ptr<glsp::ConcurrentCommandQueue>);
	void InitCommandThread();
	void StopCommandThread();

protected:
	void resizeEvent(QResizeEvent*);
	void closeEvent(QCloseEvent*);
	void paintEvent(QPaintEvent*);

private:
	ApplicationCommandThread command_thread_;
	std::shared_ptr<glsp::ConcurrentCommandQueue> command_queue_;
};

#endif // APPLICATIONFRAME_H
