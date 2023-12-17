#pragma once

#include <QMainWindow>
#include <memory>
#include "ui_SettingsWindow.h"

class SettingsWindow : public QMainWindow
{
	Q_OBJECT

public:
	SettingsWindow(QWidget *parent = nullptr);
	~SettingsWindow();

private:
	std::unique_ptr<Ui::SettingsWindowClass> m_ui;
};
