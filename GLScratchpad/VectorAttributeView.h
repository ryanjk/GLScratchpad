#ifndef VECTOR_ATTRIBUTE_VIEW_H
#define VECTOR_ATTRIBUTE_VIEW_H

#include "AttributeView.h"

#include <memory>

#include <qlabel.h>
#include <qspinbox.h>

#include "VectorAttribute.h"

class VectorAttributeView : public AttributeView {
public:
	VectorAttributeView(QLayout*, ProgramView*, std::string, const vec_attribute_t&, const vec_attribute_t&, const vec_attribute_t&);
	~VectorAttributeView();

private:
	std::vector<std::shared_ptr<QSpinBox>> spin_boxes_;
	vec_attribute_t data_;
	QLabel* attribute_name_label_;
	QLabel* current_value_label_;
	QLayout* layout_;
	QFrame* frame_;
};

#endif