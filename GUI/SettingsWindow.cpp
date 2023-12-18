#include "SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget *parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow{ parent }, m_ui{ std::make_unique<Ui::SettingsWindowClass>() }
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	m_game = game;
	m_ui->setupUi(this);

	QObject::connect(m_ui->reusableCheckBox, &QCheckBox::stateChanged,
					this, [&]() { m_ui->reusableCheckBox->isChecked()?
					m_game->setReusableMinedFoundation(true):m_game->setReusableMinedFoundation(false); });

	QObject::connect(m_ui->columnExplotionCheckBox, &QCheckBox::stateChanged,
					this, [&]() { m_ui->columnExplotionCheckBox->isChecked()?
					m_game->setExplodeCol(true):m_game->setExplodeCol(false); });

	QObject::connect(m_ui->rowExplotionCheckBox, &QCheckBox::stateChanged,
					this, [&]() { m_ui->rowExplotionCheckBox->isChecked()?
					m_game->setExplodeRow(true):m_game->setExplodeRow(false); });

	QObject::connect(m_ui->areaExplotionCheckBox, &QCheckBox::stateChanged,
					this, [&]() { m_ui->areaExplotionCheckBox->isChecked()?
					m_game->setExplodeArea(true):m_game->setExplodeArea(false); });

	QObject::connect(m_ui->minesSpinBox, &QSpinBox::valueChanged,
					this, [&]() { m_game->getBoard().setTotalMines(m_ui->minesSpinBox->value()); });

	QObject::connect(m_ui->boardSizeSpinBox, &QSpinBox::valueChanged,
					this, [&]() { m_game->getBoard().setSize(m_ui->boardSizeSpinBox->value()); });

	QObject::connect(m_ui->pylonsSpinBox, &QSpinBox::valueChanged,
					this, 
					[&]() { m_game->getPlayer1()->setNoPylons1x1(m_ui->pylonsSpinBox->value());
							m_game->getPlayer2()->setNoPylons1x1(m_ui->pylonsSpinBox->value()); });
}

SettingsWindow::~SettingsWindow()
{}