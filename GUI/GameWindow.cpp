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

void GameWindow::drawBoard(QPainter* painter)
{
    std::reference_wrapper<twixt::Board> currentBoard{ m_game->getBoard() };

    m_game->addPylon({ 12, 3 }, twixt::Pylon::Type::Square, twixt::Pylon::Color::Red);
    m_game->addPylon({ 18, 3 }, twixt::Pylon::Type::Cross, twixt::Pylon::Color::Red);
    m_game->addPylon({ 3, 3 }, twixt::Pylon::Type::Single, twixt::Pylon::Color::Black);
    m_game->addPylon({ 0, 3 }, twixt::Pylon::Type::Square, twixt::Pylon::Color::Black);

    int boardSize{ currentBoard.get().getSize() };

    QSize circleSize;
    circleSize.setWidth(std::min((width() / (2.5 * boardSize)), (height() / (2.5 * boardSize))));
    circleSize.setHeight(circleSize.width());

    QRect boardBackground{ makeSquareBoardSize() };
    double padding{ 20.0 };
    boardBackground.adjust(-padding, -padding, padding, padding);
    painter->setBrush(QColor(200, 200, 200));
    painter->setPen(Qt::NoPen);
    painter->drawRect(boardBackground);

    for (size_t i = 0; i <  boardSize; ++i)
    {
        for (size_t j = 0; j < boardSize; ++j)
        {
            nonstd::observer_ptr<twixt::Pylon> currentPylon{ currentBoard.get().getFoundation({ i, j }).getPylon() };
            
            if ((i != 0 || (j != 0 && j != boardSize - 1)) && (i != boardSize - 1 || (j != 0 && j != boardSize - 1)))
            {
                painter->setPen(Qt::black);
                painter->setBrush(Qt::blue);
                if (currentPylon != nullptr)
                {
                    if (currentPylon->getColor() == twixt::Pylon::Color::Black)
                    {
                        painter->setBrush(Qt::black);
                    } 
                    else if (currentPylon->getColor() == twixt::Pylon::Color::Red)
                    {
                        painter->setBrush(Qt::red);
                    }
                }
                painter->drawEllipse(QRect(matCoordToQPoint({i, j}), circleSize));
            }
        }
    }
}

void GameWindow::drawBoardLines(QPainter* painter)
{
    std::reference_wrapper<twixt::Board> currentBoard{ m_game->getBoard() };

    int boardSize{ currentBoard.get().getSize() };

    QRect linesRect{ makeSquareBoardSize() };

    QSize circleSize;
    circleSize.setWidth(std::min((width() / (2.5 * boardSize)), (height() / (2.5 * boardSize))));
    circleSize.setHeight(circleSize.width());

    double padding{ -(1.5 * circleSize.width()) };
    linesRect.adjust(-padding, -padding, padding, padding);

    QPen penLine{ Qt::red, 3 };

    painter->setPen(penLine);

    painter->drawLine(linesRect.topLeft(), linesRect.topRight());
    painter->drawLine(linesRect.bottomLeft(), linesRect.bottomRight());
    
    penLine = { Qt::black, 3 };

    painter->setPen(penLine);

    painter->drawLine(linesRect.topLeft(), linesRect.bottomLeft());
    painter->drawLine(linesRect.topRight(), linesRect.bottomRight());
}

void GameWindow::paintEvent(QPaintEvent* event)
{
    QPainter* painter = new QPainter{ this };
    drawBoard(painter);
    drawBoardLines(painter);

    delete painter;
}

QPoint GameWindow::matCoordToQPoint(twixt::Position pos)
{
    int boardSize{ m_game->getBoard().getSize() };
    double radius = 2.5;
    double circleSize{ std::min(width() / (radius * boardSize), height() / (radius * boardSize)) };

    double offsetX{ (width() - boardSize * circleSize * 2) / 2 };
    double offsetY{ (height() - boardSize * circleSize * 2) / 2 };

    const auto& [row, col] = pos;

    int x = offsetX + col * 2 * circleSize;
    int y = offsetY + row * 2 * circleSize;

    return { x, y };
}

QRect GameWindow::makeSquareBoardSize()
{
    int boardSize{ m_game->getBoard().getSize() };

    QSize circleSize;
    circleSize.setWidth(std::min((width() / (2.5 * boardSize)), (height() / (2.5 * boardSize))));
    circleSize.setHeight(circleSize.width());

    QPoint topLeftCorner{ matCoordToQPoint({0, 0}) };
    QPoint bottomRightCorner{ matCoordToQPoint({boardSize - 1, boardSize - 1}) };

    bottomRightCorner.setX(bottomRightCorner.x() + circleSize.width());
    bottomRightCorner.setY(bottomRightCorner.y() + circleSize.height());

    return { topLeftCorner, bottomRightCorner };
}
