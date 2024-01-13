#include "EndDialog.h"

EndDialog::EndDialog(QWidget* parent, QString message)
	: QDialog(parent), m_ui{ std::make_unique<Ui::EndDialogClass>() }
{
	m_ui->setupUi(this);
	m_ui->label->setText(message);
	setFixedSize(width(), height());
	setWindowFlag(Qt::WindowStaysOnTopHint);
}

EndDialog::~EndDialog()
{}
