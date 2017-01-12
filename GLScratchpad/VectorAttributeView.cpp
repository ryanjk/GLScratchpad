#include "VectorAttributeView.h"

#include "ProgramView.h"

VectorAttributeView::VectorAttributeView(
	QLayout* container, ProgramView* program_view, std::string name, 
	const vec_attribute_t& value, const vec_attribute_t& min, const vec_attribute_t& max)
	: AttributeView(container, program_view) {
	data_ = value;
	frame_ = new QFrame;
	layout_ = new QHBoxLayout;
	frame_->setLayout(layout_);

	attribute_name_label_ = new QLabel;
	attribute_name_label_->setText(name.c_str());
	layout_->addWidget(attribute_name_label_);

	auto* data_ptr = &data_;
	auto CreateSpinBox = [program_view, name, data_ptr](float value, float min, float max, int vec_pos) {
		auto spin_box = new QDoubleSpinBox;
		spin_box->setRange(min, max);
		spin_box->setSingleStep((max - min)/100);
		spin_box->setAccelerated(true);
		spin_box->setValue(value);

		QObject::connect(spin_box, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
			program_view, [program_view, vec_pos, data_ptr, name](float value) {
			(*data_ptr)[vec_pos] = value;
			program_view->SetVectorValue(name, *data_ptr);
		});
		return spin_box;
	};

	for (int i = 0; i < value.size(); ++i) {
		auto spin_box = CreateSpinBox(value[i], min[i], max[i], i);
		layout_->addWidget(spin_box);
	}

	container_->addWidget(frame_);
}


VectorAttributeView::~VectorAttributeView() {
	container_->removeWidget(frame_);
}
