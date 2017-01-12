#include "AbstractShader.h"

#include <iostream>

#include <qdebug.h>

namespace {

template<typename Key, typename Data>
bool DoesMapContain(const std::unordered_map<Key, Data>& map, const Key id) {
	auto itr = map.find(id);
	return itr != map.end();
}

} // namespace

namespace glsp {

AbstractShader::AbstractShader(glsp::Camera* camera) : time_{0.0f}, camera_{camera}, attributes_{} {}

AbstractShader::~AbstractShader() {}

void AbstractShader::SetAttribute(glsp::AttributeKey id, glsp::ShaderAttribute* attribute) {
	if (DoesMapContain(attributes_, id)) {
		attributes_[id]->Copy(attribute);
	}
	else {
		qDebug() << "AbstractShader::SetAttribute: Can't find attribute '" << id.c_str() << "'";
	}
	delete attribute;
}

void AbstractShader::Draw(glsp::RenderData render_data) {
	time_ += render_data.dt;
	Render(render_data);
}

float AbstractShader::Time() {
	return time_;
}

const glsp::Camera* AbstractShader::Camera() {
	return camera_;
}

void AbstractShader::InsertAttribute(glsp::AttributeKey id, glsp::ShaderAttribute* attribute) {
	if (!DoesMapContain(attributes_, id)) {
		attributes_.insert(std::make_pair(id, attribute));
	}
	else {
		qDebug() << "AbstractShader::InsertAttribute: Attribute '" << id.c_str() << "' already exists\n";
	}
}

void AbstractShader::Get(glsp::AttributeKey id, void* out) {
	if (DoesMapContain(attributes_, id)) {
		attributes_[id]->Get(out);
	}
	else {
		qDebug() << "AbstractShader::Get: Can't find attribute '" << id.c_str() << "'\n";
	}
}

} //namespace glsp



