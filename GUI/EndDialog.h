#pragma once

#include <QDialog>
#include <memory>
#include "ui_EndDialog.h"

class EndDialog : public QDialog
{
	Q_OBJECT

public:
	EndDialog(QWidget* parent = nullptr, QString message = "");
	~EndDialog();

private:
	std::unique_ptr<Ui::EndDialogClass> m_ui;
};
