#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include <QDialog>
#include "ui_cameraview.h"

class CameraView : public QDialog
{
	Q_OBJECT

public:
	CameraView(QWidget *parent = 0);
	~CameraView();

private:
	Ui::CameraView ui;
};

#endif // CAMERAVIEW_H
