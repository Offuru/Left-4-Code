#include "SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget *parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow{ parent }, m_ui{ std::make_unique<Ui::SettingsWindowClass>() }
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	m_game = game;
	m_ui->setupUi(this);

	QObject::connect(m_ui->reusableCheckBox, &QCheckBox::stateChanged,
					[&]() { m_ui->reusableCheckBox->isChecked()? 
					m_game->setReusableMinedFoundation(true):m_game->setReusableMinedFoundation(false); });

	QObject::connect(m_ui->columnExplotionCheckBox, &QCheckBox::stateChanged,
					[&]() { m_ui->columnExplotionCheckBox->isChecked()? 
					m_game->setExplodeCol(true):m_game->setExplodeCol(false); });

	QObject::connect(m_ui->rowExplotionCheckBox, &QCheckBox::stateChanged,
					[&]() { m_ui->rowExplotionCheckBox->isChecked()?
					m_game->setExplodeRow(true):m_game->setExplodeRow(false); });

	QObject::connect(m_ui->areaExplotionCheckBox, &QCheckBox::stateChanged,
					[&]() { m_ui->areaExplotionCheckBox->isChecked()?
					m_game->setExplodeArea(true):m_game->setExplodeArea(false); });

	QObject::connect(m_ui->minesSpinBox, &QSpinBox::valueChanged,
					[&]() { m_game->getBoard().setTotalMines(m_ui->minesSpinBox->value()); });

	QObject::connect(m_ui->boardSizeSpinBox, &QSpinBox::valueChanged,
					[&]() { m_game->getBoard().setSize(m_ui->boardSizeSpinBox->value()); });

	QObject::connect(m_ui->pylonsSpinBox, &QSpinBox::valueChanged,
					[&]() { m_game->getPlayer1()->setNoPylons1x1(m_ui->pylonsSpinBox->value());
							m_game->getPlayer2()->setNoPylons1x1(m_ui->pylonsSpinBox->value()); });

	QObject::connect(m_ui->pylonsSqSpinBox, &QSpinBox::valueChanged, this, &SettingsWindow::setNoSquarePylons);

	QObject::connect(m_ui->pylonsCsSpinBox, &QSpinBox::valueChanged, this, &SettingsWindow::setNoCrossPylons);

	QObject::connect(m_ui->bridgeSpinBox, &QSpinBox::valueChanged,
					[&]() { m_game->getPlayer1()->setNoBridges(m_ui->bridgeSpinBox->value());
							m_game->getPlayer2()->setNoBridges(m_ui->bridgeSpinBox->value()); });
}

SettingsWindow::~SettingsWindow()
{}

void SettingsWindow::enableMineGameModeSettings()
{
	m_ui->minesSpinBox->setEnabled(true);
	m_ui->areaExplotionCheckBox->setEnabled(true);
	m_ui->rowExplotionCheckBox->setEnabled(true);
	m_ui->columnExplotionCheckBox->setEnabled(true);
	m_ui->reusableCheckBox->setEnabled(true);
}

void SettingsWindow::enableBigPylonsGameModeSettings()
{
	m_ui->pylonsSqSpinBox->setEnabled(true);
	m_ui->pylonsCsSpinBox->setEnabled(true);
}

void SettingsWindow::setNoSquarePylons()
{
	m_ui->pylonsSqSpinBox->setEnabled(true);
	m_game->getPlayer1()->setNoPylons2x2(m_ui->pylonsSqSpinBox->value());
	m_game->getPlayer2()->setNoPylons2x2(m_ui->pylonsSqSpinBox->value());
}

void SettingsWindow::setNoCrossPylons()
{
	m_ui->pylonsSqSpinBox->setEnabled(true);
	m_game->getPlayer1()->setNoPylonsCross(m_ui->pylonsCsSpinBox->value());
	m_game->getPlayer2()->setNoPylonsCross(m_ui->pylonsCsSpinBox->value());
}
