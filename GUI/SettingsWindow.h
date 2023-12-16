#pragma once

#include <QMainWindow>
#include "ui_SettingsWindow.h"

class SettingsWindow : public QMainWindow
{
	Q_OBJECT

public:
	SettingsWindow(QWidget *parent = nullptr);
	~SettingsWindow();

private:
	Ui::SettingsWindowClass ui;
};
