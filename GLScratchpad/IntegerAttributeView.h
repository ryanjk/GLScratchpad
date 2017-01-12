#ifndef GLSP_INT_ATTRIBUTE_VIEW_H
#define GLSP_INT_ATTRIBUTE_VIEW_H

#include "AttributeView.h"

#include <qframe.h>
#include <qlabel.h>
#include <qslider.h>

class IntegerAttributeView : public AttributeView {
public:
	IntegerAttributeView(QLayout*, ProgramView*, std::string, int, int, int);
	~IntegerAttributeView();

private:
	QSlider* slider_;
	QLabel* attribute_name_label_;
	QLabel* current_value_label_;
	QLayout* layout_;
	QFrame* frame_;
};

#endif