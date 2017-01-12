#include "FloatAttributeView.h"

#include "programview.h"

FloatAttributeView::FloatAttributeView(
	QLayout* container, ProgramView* program_view, std::string name, float value, float min, float max) 
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

	const float STEP = 0.01;
	slider_ = new QSlider;
	slider_->setOrientation(Qt::Orientation::Horizontal);
	slider_->setRange(0, (1 / STEP));
	slider_->setSingleStep(1);
	slider_->setValue(((value - min) / (max - min)) / STEP);
	layout_->addWidget(slider_);

	auto* value_display = current_value_label_;
	QObject::connect(slider_, &QSlider::valueChanged, program_view, 
		[program_view, name, STEP, max, min, value_display](float value) {
		float alpha = value * STEP;
		float current_value = (value * STEP) * (max - min) + min;
		program_view->SetFloatValue(name, current_value);
		//value_display->setText(QString::number(current_value));
	});

	container_->addWidget(frame_);
}


FloatAttributeView::~FloatAttributeView() {
	container_->removeWidget(frame_);
	delete slider_;
	delete attribute_name_label_;
	delete layout_;
	delete frame_;
	delete current_value_label_;
}
