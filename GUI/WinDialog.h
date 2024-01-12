#pragma once

#include <QDialog>
#include <memory>
#include "ui_WinDialog.h"

class WinDialog : public QDialog
{
	Q_OBJECT

public:
	WinDialog(QWidget *parent = nullptr, QString playerNmae = "");
	~WinDialog();

private:
	std::unique_ptr<Ui::WinDialogClass> m_ui;
};
