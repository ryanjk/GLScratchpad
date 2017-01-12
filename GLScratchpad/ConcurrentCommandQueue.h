#pragma once

#include <queue>
#include <mutex>

#include "glsp_types.h"

namespace glsp {

class ConcurrentCommandQueue {
public:
	ConcurrentCommandQueue() : queue_{}, queue_mutex_{} {}
	~ConcurrentCommandQueue() {}

	void Enqueue(const glsp::Command& data) {
		std::lock_guard<std::mutex> lock(queue_mutex_);
		queue_.emplace(data);
	}

	glsp::Command Pop() {
		std::lock_guard<std::mutex> lock(queue_mutex_);
		auto data = queue_.front();
		queue_.pop();
		return data;
	}

	bool IsEmpty() const {
		std::lock_guard<std::mutex> lock(queue_mutex_);
		return queue_.empty();
	}

private:
	std::queue<glsp::Command> queue_;
	mutable std::mutex queue_mutex_;
};

} // namespace glsp

