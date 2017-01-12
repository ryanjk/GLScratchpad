#include "programview.h"

#include <limits>

#include <qdebug.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qslider.h>

#include "Application.h"
#include "ShaderAttribute.h"
#include "FloatAttribute.h"
#include "FloatAttributeView.h"
#include "IntegerAttribute.h"
#include "IntegerAttributeView.h"
#include "VectorAttributeView.h"
#include "Util.h"

namespace {
	template<typename T>
	T SafeGet(const json& json_obj, std::string attribute_name, T default_return = T()) {
		auto itr = json_obj.find(attribute_name);
		if (itr != json_obj.end()) {
			return json_obj[attribute_name].get<T>();
		}
		else {
			qDebug() << "Couldn't find attribute " << attribute_name.c_str();
			return default_return;
		}
	}
} // namespace

ProgramView::ProgramView(QWidget *parent, glsp::ConcurrentCommandQueue* command_queue)
	: QDialog(parent), command_queue_(command_queue)
{
	ui.setupUi(this);
	attribute_view_container_ = ui.verticalLayout;
}

ProgramView::~ProgramView()
{

}

void ProgramView::InitializeProgram(const json& shader_data) {
	try {
		auto name = shader_data["name"].get<std::string>();
		glsp::Command load_program_command = [=](glsp::Application* application) {
			application->LoadProgram(name);
		};
		command_queue_->Enqueue(load_program_command);

		auto width = SafeGet<int>(shader_data, "window_width", 500);
		auto height = SafeGet<int>(shader_data, "window_height", 500);
		parentWidget()->resize(width, height);

		auto attributes = shader_data["attributes"];
		for (const auto& attribute : attributes) {
			auto attribute_name = SafeGet<std::string>(attribute, "name");
			auto attribute_type = SafeGet<std::string>(attribute, "type");
			if (attribute_type == "float") {
				auto attribute_value = SafeGet<float>(attribute, "value");
				auto min = SafeGet<float>(attribute, "min", attribute_value - 1);
				auto max = SafeGet<float>(attribute, "max", attribute_value + 1);
				CreateFloatAttribute(attribute_name, attribute_value, min, max);
			}
			else if (attribute_type == "int") {
				auto attribute_value = SafeGet<int>(attribute, "value");
				auto min = SafeGet<int>(attribute, "min", attribute_value - 1);
				auto max = SafeGet<int>(attribute, "max", attribute_value + 1);
				CreateIntegerAttribute(attribute_name, attribute_value, min, max);
			}
			else if (attribute_type == "transform") {
				auto attrib_value = attribute["value"];
				auto create_transform_attribute = 
					[attribute_name, &attrib_value, this]
					(const std::string& transform_data_name, 
						vec_attribute_t default_value = vec_attribute_t(), 
						vec_attribute_t default_min = vec_attribute_t(), vec_attribute_t default_max = vec_attribute_t()) {
					auto attrib_data = attrib_value[transform_data_name];
					auto value = SafeGet<vec_attribute_t>(attrib_data, "value", default_value);
					auto min_value = SafeGet<vec_attribute_t>(attrib_data, "min", default_min);
					auto max_value = SafeGet<vec_attribute_t>(attrib_data, "max", default_max);
					CreateVectorAttribute(attribute_name + "_" + transform_data_name, value, min_value, max_value);
				};
				create_transform_attribute("position", vec_attribute_t(3, 0.0f), vec_attribute_t(3, -10.0f), vec_attribute_t(3, 10.0f));
				create_transform_attribute("rotation", vec_attribute_t(3, 0.0f), vec_attribute_t(3, -180.0f), vec_attribute_t(3, 180.0f));
				create_transform_attribute("scale", vec_attribute_t(3, 1.0f), vec_attribute_t(3, 0.0f), vec_attribute_t(3, 5.0f));
				//CreateFloatAttribute(attribute_name + "_scale", 1.0f, 0.0f, std::numeric_limits<float>::max());
			}
			else if (attribute_type == "vec2") {
				auto v = SafeGet<vec_attribute_t>(attribute, "value");
				auto min = SafeGet<vec_attribute_t>(attribute, "min", { v[0] - 1, v[1] - 1 });
				auto max = SafeGet<vec_attribute_t>(attribute, "max", { v[0] + 1, v[1] + 1 });
				CreateVectorAttribute(attribute_name, v, min, max);
			}
			else if (attribute_type == "vec3") {
				auto v = SafeGet<vec_attribute_t>(attribute, "value");
				auto min = SafeGet<vec_attribute_t>(attribute, "min", { v[0] - 1, v[1] - 1, v[2] - 1 });
				auto max = SafeGet<vec_attribute_t>(attribute, "max", { v[0] + 1, v[1] + 1, v[2] + 1 });
				CreateVectorAttribute(attribute_name, v, min, max);
			}
			else if (attribute_type == "vec4") {
				auto v = SafeGet<vec_attribute_t>(attribute, "value");
				auto min = SafeGet<vec_attribute_t>(attribute, "min", { v[0] - 1, v[1] - 1, v[2] - 1, v[3] - 1 });
				auto max = SafeGet<vec_attribute_t>(attribute, "max", { v[0] + 1, v[1] + 1, v[2] + 1, v[3] + 1 });
				CreateVectorAttribute(attribute_name, v, min, max);
			}
			else {
				glsp::PrintLine("Can't parse JSON file, unsupported data type");
			}
		}
	}
	catch (std::domain_error e) {
		glsp::PrintLine(e.what());
	}
}

void ProgramView::ClearProgramView() {
	attribute_views_.clear();
}

void ProgramView::CreateFloatAttribute(std::string name, float value, float min, float max) {
	attribute_views_.emplace_back(std::make_shared<FloatAttributeView>(attribute_view_container_, this, name, value, min, max));

	auto* float_attribute = new glsp::FloatAttribute(value);
	InsertProgramAttribute(name, float_attribute);
}

void ProgramView::CreateIntegerAttribute(std::string name, int value, int min, int max) {
	attribute_views_.emplace_back(std::make_shared<IntegerAttributeView>(attribute_view_container_, this, name, value, min, max));

	auto* int_attribute = new glsp::IntegerAttribute(value);
	InsertProgramAttribute(name, int_attribute);
}

void ProgramView::CreateVectorAttribute(
	std::string name, const vec_attribute_t& value, const vec_attribute_t& min, const vec_attribute_t& max) {
	attribute_views_.emplace_back(std::make_shared<VectorAttributeView>(attribute_view_container_, this, name, value, min, max));

	auto* vec_attribute = new glsp::VectorAttribute(value);
	InsertProgramAttribute(name, vec_attribute);
}

void ProgramView::SetFloatValue(std::string id, float data) {
	auto float_attribute = new glsp::FloatAttribute(data);
	SetProgramAttribute(id, float_attribute);
}

void ProgramView::SetIntegerValue(std::string id, int data) {
	auto integer_attribute = new glsp::IntegerAttribute(data);
	SetProgramAttribute(id, integer_attribute);
}

void ProgramView::SetVectorValue(std::string id, const vec_attribute_t& data) {
	auto vector_attribute = new glsp::VectorAttribute(data);
	SetProgramAttribute(id, vector_attribute);
}

void ProgramView::InsertProgramAttribute(glsp::AttributeKey id, glsp::ShaderAttribute* attribute) {
	glsp::Command insert_attribute_command = [=](glsp::Application* application) {
		application->InsertProgramAttribute(id, attribute);
	};
	command_queue_->Enqueue(insert_attribute_command);
}

void ProgramView::SetProgramAttribute(glsp::AttributeKey id, glsp::ShaderAttribute* attribute) {
	glsp::Command set_attribute_command = [=](glsp::Application* application) {
		application->SetProgramAttribute(id, attribute);
	};
	command_queue_->Enqueue(set_attribute_command);
}
