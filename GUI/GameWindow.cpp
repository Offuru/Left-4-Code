#include "GameWindow.h"

GameWindow::GameWindow(QWidget* parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow(parent), m_ui{ std::make_unique<Ui::GameWindowClass>() }
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

	m_game = game;

	m_ui->setupUi(this);
}

GameWindow::~GameWindow()
{}

void GameWindow::closeEvent(QCloseEvent * event)
{
	QCoreApplication::quit();
}

void GameWindow::initializeBoard()
{
    int boardSize{ m_game->getBoard().getSize() };
    double circleSize{ std::min(width() / (2.5 * boardSize), height() / (2.5 * boardSize)) };

    double offsetX{ (width() - boardSize * circleSize * 2) / 2 + 0 };
    double offsetY{ std::max((height() - boardSize * circleSize * 2) / 2 + 10, 60.0) };

	for (int row = 0; row < boardSize; ++row)
	{
		for (int col = 0; col < boardSize; ++col)
		{
			int x = offsetX + col * 2 * circleSize;
			int y = offsetY + row * 2 * circleSize;
            m_pylons.push_back(QRect(x, y, circleSize, circleSize));
		}
	}
}

void GameWindow::drawBoard()
{
    if (m_pylons.size() == 0)
    {
        initializeBoard();
    }

    QPainter painter{ this };

    int boardSize{ m_game->getBoard().getSize() };

    double circleSize{ std::min(width() / (2.5 * boardSize), height() / (2.5 * boardSize)) };

    QRectF boardBackground{ m_pylons[0].topLeft(), m_pylons[m_pylons.size() - 1].bottomRight() };

    qreal padding{ 20.0 };
    boardBackground.adjust(-padding, -padding, padding, padding);

    painter.setBrush(QColor(200, 200, 200));
    painter.setPen(Qt::NoPen);
    painter.drawRect(boardBackground);

    for (int i = 1; i < m_pylons.size() - 1; ++i)
    {
        if (i != boardSize - 1 && i != boardSize * boardSize - boardSize)
        {
            painter.setPen(Qt::black);
            painter.setBrush(Qt::blue);
            painter.drawEllipse(m_pylons[i]);
        }
    }
}

void GameWindow::drawBoardLines()
{
    QPainter painter{ this };

    int boardSize{ m_game->getBoard().getSize() };
    int circleSize{ std::min(width() / (2 * boardSize), height() / (2 * boardSize)) };

    QPen penLine{ Qt::red, 3 };

    int firstRowY{ m_pylons[0].bottom() };
    int firstColX{ m_pylons[0].right() };
    int lastColX{ m_pylons[m_pylons.size() - 1].left() };
    int lastRowY{ m_pylons[m_pylons.size() - 1].top() };

    painter.setPen(penLine);

    painter.drawLine(firstColX + circleSize / 2, firstRowY + circleSize / 2, lastColX - circleSize / 2, firstRowY + circleSize / 2);
    painter.drawLine(firstColX + circleSize / 2, lastRowY - circleSize / 2, lastColX - circleSize / 2, lastRowY - circleSize / 2);

    penLine = { Qt::black, 3 };

    painter.setPen(penLine);

    painter.drawLine(firstColX + circleSize / 2, firstRowY + circleSize / 2, firstColX + circleSize / 2, lastRowY - circleSize / 2);
    painter.drawLine(lastColX - circleSize / 2, firstRowY + circleSize / 2, lastColX - circleSize / 2, lastRowY - circleSize / 2);
}

void GameWindow::paintEvent(QPaintEvent* event)
{
    drawBoard();
    drawBoardLines();
}
