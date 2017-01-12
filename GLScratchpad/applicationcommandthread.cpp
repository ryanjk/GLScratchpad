#include "applicationcommandthread.h"

#include <qdebug.h>

#include "glew.h"
#include "applicationframe.h"

namespace {

	decltype(auto) CurrentTimePoint() {
		return std::chrono::steady_clock::now();
	}

} // namespace

ApplicationCommandThread::ApplicationCommandThread(ApplicationFrame* application_frame)
	: QThread(), application_frame_{ application_frame }, 
	application_{ new glsp::Application() }, running_{ false }
{

}

ApplicationCommandThread::~ApplicationCommandThread()
{

}

void ApplicationCommandThread::SetCommandQueue(std::shared_ptr<glsp::ConcurrentCommandQueue> command_queue) {
	command_queue_ = command_queue;
}

void ApplicationCommandThread::run() {
	application_frame_->makeCurrent();

	glewInit();
	msleep(100);
	qDebug() << (const char*)glGetString(GL_VERSION);

	auto last_render_started = CurrentTimePoint();
	float dt = 0.0f;
	running_ = true;
	int frames = 0;
	float time = 0.0f;
	while (running_) {
		auto now = CurrentTimePoint();
		std::chrono::duration<float> time_since_last_render = now - last_render_started;
		dt = time_since_last_render.count();
		time += dt;

		while (!command_queue_->IsEmpty()) {
			auto command = command_queue_->Pop();
			command(application_);
		}		

		{
			glsp::RenderData render_data;
			render_data.dt = dt;

			last_render_started = CurrentTimePoint();
			application_frame_->makeCurrent();
			application_->Draw(render_data);
			application_frame_->swapBuffers();
			frames++;
		}		

		if (time >= 2) {
			//qDebug() << "FPS: " << frames / time;
			frames = 0;
			time = 0;
		}
	}
}

void ApplicationCommandThread::stop() {
	running_ = false;
}
