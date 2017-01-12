#ifndef APPLICATIONCOMMANDTHREAD_H
#define APPLICATIONCOMMANDTHREAD_H

#include <QThread>

#include <memory>
#include <chrono>

#include "ConcurrentCommandQueue.h"
#include "Application.h"

class ApplicationFrame;

class ApplicationCommandThread : public QThread
{
	Q_OBJECT

public:
	ApplicationCommandThread(ApplicationFrame*);
	~ApplicationCommandThread();

	void run() override;
	void stop();
	void SetCommandQueue(std::shared_ptr<glsp::ConcurrentCommandQueue>);

private:
	ApplicationFrame* application_frame_;
	glsp::Application* application_;
	std::shared_ptr<glsp::ConcurrentCommandQueue> command_queue_;

	bool running_;
	
};

#endif // APPLICATIONCOMMANDTHREAD_H
