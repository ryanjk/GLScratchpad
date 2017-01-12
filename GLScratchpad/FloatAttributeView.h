#ifndef GLSP_FLOAT_ATTRIBUTE_VIEW_H
#define GLSP_FLOAT_ATTRIBUTE_VIEW_H

#include "AttributeView.h"

#include <qframe.h>
#include <qlabel.h>
#include <qslider.h>
#include <qspinbox.h>

class FloatAttributeView : public AttributeView {
public:
	FloatAttributeView(QLayout*, ProgramView*, std::string, float, float, float);
	~FloatAttributeView();

private:
	QSlider* slider_;
	QLabel* attribute_name_label_;
	QLabel* current_value_label_;
	QLayout* layout_;
	QFrame* frame_;
};

#endif