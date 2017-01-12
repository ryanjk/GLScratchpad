#include "Util.h"

#include <qdebug.h>

namespace glsp {
	void PrintLine(std::string line) {
		qDebug() << (line).c_str();
	}
}
