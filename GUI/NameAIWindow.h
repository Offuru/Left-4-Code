#pragma once

#include <QMainWindow>
#include "ui_NameAIWindow.h"

class NameAIWindow : public QMainWindow
{
	Q_OBJECT

public:
	NameAIWindow(QWidget *parent = nullptr);
	~NameAIWindow();

public slots:
	void on_buttonBack_clicked();

private:
	Ui::NameAIWindowClass ui;
};
