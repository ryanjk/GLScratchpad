#include "IntegerAttributeView.h"



#include "programview.h"

IntegerAttributeView::IntegerAttributeView(
	QLayout* container, ProgramView* program_view, std::string name, int value, int min, int max)
	: AttributeView(container, program_view) {
	frame_ = new QFrame;
	layout_ = new QHBoxLayout;
	frame_->setLayout(layout_);

	attribute_name_label_ = new QLabel;
	attribute_name_label_->setText(name.c_str());
	layout_->addWidget(attribute_name_label_);

	current_value_label_ = new QLabel;
	current_value_label_->setText(QString::number(value, 'g', 2));
	//layout_->addWidget(current_value_label_);

	slider_ = new QSlider;
	slider_->setOrientation(Qt::Orientation::Horizontal);
	slider_->setRange(min, max);
	slider_->setSingleStep(1);
	slider_->setValue(value);
	layout_->addWidget(slider_);

	auto* value_display = current_value_label_;
	QObject::connect(slider_, &QSlider::valueChanged, program_view,
		[program_view, name, value_display](int value) {
		program_view->SetIntegerValue(name, value);
		//value_display->setText(QString::number(current_value));
	});

	container_->addWidget(frame_);
}


IntegerAttributeView::~IntegerAttributeView() {
	container_->removeWidget(frame_);
	delete slider_;
	delete attribute_name_label_;
	delete layout_;
	delete frame_;
	delete current_value_label_;
}
