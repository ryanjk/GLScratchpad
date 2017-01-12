#ifndef PROGRAMVIEW_H
#define PROGRAMVIEW_H

#include <QDialog>
#include "ui_programview.h"

#include <string>
#include <vector>

#include "json.h"

#include "glsp_types.h"
#include "ConcurrentCommandQueue.h"
#include "AttributeView.h"
#include "VectorAttribute.h"

using json = nlohmann::json;

class ProgramView : public QDialog {
	Q_OBJECT

public:
	ProgramView(QWidget *parent, glsp::ConcurrentCommandQueue*);
	~ProgramView();

	void InitializeProgram(const json&);
	void ClearProgramView();

	void SetFloatValue(std::string, float);
	void SetIntegerValue(std::string,int);
	void SetVectorValue(std::string, const vec_attribute_t&);

public slots:

private:
	Ui::ProgramView ui;
	QLayout* attribute_view_container_;
	std::vector <std::shared_ptr<AttributeView>> attribute_views_;
	glsp::ConcurrentCommandQueue* command_queue_;

	void CreateFloatAttribute(std::string, float, float, float);
	void CreateIntegerAttribute(std::string, int, int, int);
	void CreateVectorAttribute(std::string, const vec_attribute_t&, const vec_attribute_t&, const vec_attribute_t&);

	void InsertProgramAttribute(glsp::AttributeKey, glsp::ShaderAttribute*);
	void SetProgramAttribute(glsp::AttributeKey, glsp::ShaderAttribute*);
};

#endif // PROGRAMVIEW_H
