#pragma once

#include <QMainWindow>
#include "ui_NameAIWindow.h"

class NameAIWindow : public QMainWindow
{
	Q_OBJECT

public:
	NameAIWindow(QWidget *parent = nullptr);
	~NameAIWindow();

private:
	Ui::NameAIWindowClass ui;
};
