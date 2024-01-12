#include "WinDialog.h"

WinDialog::WinDialog(QWidget *parent, QString playerNmae)
	: QDialog(parent), m_ui{ std::make_unique<Ui::WinDialogClass>() }
{
	m_ui->setupUi(this);
	m_ui->winLabel->setText(playerNmae + " won!");
	setFixedSize(width(), height()); 
	setWindowFlag(Qt::WindowStaysOnTopHint);
}

WinDialog::~WinDialog()
{}
