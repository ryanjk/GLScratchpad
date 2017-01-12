#ifndef GLSP_ATTRIBUTE_VIEW_H
#define GLSP_ATTRIBUTE_VIEW_H

#include <qlayout.h>

class ProgramView;

class AttributeView {
public:
	AttributeView(QLayout* container, ProgramView*) { container_ = container; }
	virtual ~AttributeView();

protected:
	QLayout* container_;
};

#endif

