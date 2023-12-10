#pragma once

#include <QMainWindow>
#include "ui_Name2PlayersWindow.h"

class Name2PlayersWindow : public QMainWindow
{
	Q_OBJECT

public:
	Name2PlayersWindow(QWidget *parent = nullptr);
	~Name2PlayersWindow();

public slots:
	void on_buttonBack_clicked();

private:
	Ui::Name2PlayersWindowClass ui;
};
