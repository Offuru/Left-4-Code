#include "GameWindow.h"

GameWindow::GameWindow(QWidget* parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow(parent), m_ui{ std::make_unique<Ui::GameWindowClass>() }
{
    setWindowState(Qt::WindowMaximized);

	m_game = game;

	m_ui->setupUi(this);

    m_currentAction = Action::Add_SinglePylon;
    m_pylonRotation = 0;

    QObject::connect(m_ui->squareConfig1Button, &QPushButton::clicked,
                    [&]() { 
                        if (m_currentAction != Action::Add_SquarePylonConfig1) { resetPushButtonIcon(); m_currentAction = Action::Add_SquarePylonConfig1; }
                        else m_currentAction = Action::Add_SinglePylon;
                    });
    QObject::connect(m_ui->squareConfig2Button, &QPushButton::clicked,
                    [&]() {
                        if (m_currentAction != Action::Add_SquarePylonConfig2) { resetPushButtonIcon(); m_currentAction = Action::Add_SquarePylonConfig2; }
                        else m_currentAction = Action::Add_SinglePylon;
                    });
    QObject::connect(m_ui->crossConfig1Button, &QPushButton::clicked,
                    [&]() {
                        if (m_currentAction != Action::Add_CrossPylonConfig1) { resetPushButtonIcon(); m_currentAction = Action::Add_CrossPylonConfig1; }
                        else m_currentAction = Action::Add_SinglePylon;
                    });
    QObject::connect(m_ui->crossConfig2Button, &QPushButton::clicked,
                    [&]() {
                        if (m_currentAction != Action::Add_CrossPylonConfig2) { resetPushButtonIcon(); m_currentAction = Action::Add_CrossPylonConfig2; }
                        else m_currentAction = Action::Add_SinglePylon;
                    });
}

GameWindow::~GameWindow()
{}

void GameWindow::setFoundationsPoints(const std::vector<QPoint>& foundationsPoints)
{
    m_foundationsPoints = foundationsPoints;
}

void GameWindow::closeEvent(QCloseEvent* event)
{
	QCoreApplication::quit();
}

void GameWindow::changeVisibilityBigPylonsButtons(bool state)
{
    m_ui->crossConfig1Button->setVisible(state);
    m_ui->crossConfig2Button->setVisible(state);
    m_ui->squareConfig1Button->setVisible(state);
    m_ui->squareConfig2Button->setVisible(state);
}

void GameWindow::addPylon(const twixt::Position& matPosition)
{
    switch (m_currentAction)
    {
        case GameWindow::Action::Add_SinglePylon:
            m_game->addPylon(matPosition, twixt::Pylon::Type::Single, twixt::Pylon::Color::Red, m_pylonRotation);
            break;
        case GameWindow::Action::Add_SquarePylonConfig1:
            m_game->addPylon(matPosition, twixt::Pylon::Type::Square, twixt::Pylon::Color::Red, m_pylonRotation);
            break;
        case GameWindow::Action::Add_SquarePylonConfig2:
            m_game->addPylon(matPosition, twixt::Pylon::Type::Square, twixt::Pylon::Color::Red, m_pylonRotation, false);
            break;
        case GameWindow::Action::Add_CrossPylonConfig1:
            m_game->addPylon(matPosition, twixt::Pylon::Type::Cross, twixt::Pylon::Color::Red, m_pylonRotation);
            break;
        case GameWindow::Action::Add_CrossPylonConfig2:
            m_game->addPylon(matPosition, twixt::Pylon::Type::Cross, twixt::Pylon::Color::Red, m_pylonRotation, false);
            break;
        default:
            break;
    }
    resetPushButtonIcon();
    m_currentAction = Action::Add_SinglePylon;
    m_pylonRotation = 0;
}

void GameWindow::drawBoard(QPainter* painter)
{
    std::reference_wrapper<twixt::Board> currentBoard{ m_game->getBoard() };

    int boardSize{ currentBoard.get().getSize() };

    QSize circleSize;
    circleSize.setWidth(std::min((width() / (2.5 * boardSize)), (height() / (2.5 * boardSize))));
    circleSize.setHeight(circleSize.width());

    QRect boardBackground{ makeSquareBoardSize() };
    double padding{ 20.0 };
    boardBackground.adjust(-padding, -padding, padding, padding);
    painter->setBrush(QColor(200, 200, 200));
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(boardBackground, 10, 10);

    for (size_t i = 0; i < boardSize; ++i)
    {
        for (size_t j = 0; j < boardSize; ++j)
        {
            twixt::Position foundationPos = { i, j };
            nonstd::observer_ptr<twixt::Pylon> currentPylon{ currentBoard.get().getFoundation(foundationPos).getPylon() };

            if ((i != 0 || (j != 0 && j != boardSize - 1)) && (i != boardSize - 1 || (j != 0 && j != boardSize - 1)))
            {
                QBrush brush{ Qt::blue };
                painter->setBrush(brush);
                if (currentPylon != nullptr)
                {
                    if (currentPylon->getColor() == twixt::Pylon::Color::Black)
                        brush = Qt::black;
                    else if (currentPylon->getColor() == twixt::Pylon::Color::Red)
                        brush = Qt::red;
                    if (currentPylon->getType() != twixt::Pylon::Type::Single)
                    {
                        painter->setPen(Qt::NoPen);
                        painter->setBrush(Qt::cyan);
                        QRect bgSquare = QRect(matCoordToQPoint(foundationPos), circleSize);
                        double padding{ 1.f * circleSize.height() / 2 };
                        bgSquare.adjust(-padding, -padding, padding, padding);
                        painter->drawRect(bgSquare);

                    }
                    if (currentPylon->getType() != twixt::Pylon::Type::Single && (currentPylon->getConnectionPoints()[0] == foundationPos || currentPylon->getConnectionPoints()[1] == foundationPos))
                        brush = QColor(255, 105, 180);

                }
                if (currentBoard.get().getFoundation(foundationPos).getBob() == true)
                    brush = Qt::yellow;
                if (currentBoard.get().getFoundation(foundationPos).getMined() == true)
                    brush = QColor(75, 0, 130); //purple
                if (currentBoard.get().getFoundation(foundationPos).getExploded() == true && currentPylon == nullptr)
                    brush = QColor(173, 255, 47); //green

                painter->setPen(Qt::black);
                painter->setBrush(brush);
                painter->drawEllipse(QRect(matCoordToQPoint(foundationPos), circleSize));
                m_foundationsPoints[boardSize * i + j] = matCoordToQPoint(foundationPos);
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

void GameWindow::mousePressEvent(QMouseEvent* event)
{
    int boardSize{ m_game->getBoard().getSize() };
    double radius = 2.5;
    double circleSize{ std::min(width() / (radius * boardSize), height() / (radius * boardSize)) };

    QPoint mousePosition = event->pos();
    twixt::Position matPosition = qPointToMatCoord(mousePosition);
    if (boardSize * matPosition.first + matPosition.second >= 0 && boardSize * matPosition.first + matPosition.second < m_foundationsPoints.size())
    {
        QPoint foundationPos = m_foundationsPoints[boardSize * matPosition.first + matPosition.second];

        int distance = std::sqrt(std::pow(mousePosition.x() - foundationPos.x(), 2) + std::pow(mousePosition.y() - foundationPos.y(), 2));

        if (distance <= circleSize)
        {
            if (m_game->getBoard().getFoundation(matPosition).getPylon() == nullptr)
                addPylon(matPosition);
        }
    }
    
    update();
}

void GameWindow::wheelEvent(QWheelEvent* event)
{
    if (m_currentAction != Action::Add_SinglePylon)
    {
        int rotationFactor = (event->angleDelta().y() > 0) ? 1 : -1;
        m_pylonRotation += rotationFactor;
        if (m_pylonRotation < 0) m_pylonRotation = 3;
        m_pylonRotation %= 4;

        switch (m_currentAction)
        {
            case GameWindow::Action::Add_SquarePylonConfig1:
                rotatePushButtonIcon(*m_ui->squareConfig1Button, rotationFactor);
                break;
            case GameWindow::Action::Add_SquarePylonConfig2:
                rotatePushButtonIcon(*m_ui->squareConfig2Button, rotationFactor);
                break;
            case GameWindow::Action::Add_CrossPylonConfig1:
                rotatePushButtonIcon(*m_ui->crossConfig1Button, rotationFactor);
                break;
            case GameWindow::Action::Add_CrossPylonConfig2:
                rotatePushButtonIcon(*m_ui->crossConfig2Button, rotationFactor);
                break;
            default:
                break;
        }
    }
}

void GameWindow::rotatePushButtonIcon(QPushButton& button, int rotationFactor)
{
    QIcon buttonIcon{ button.icon() };
    QPixmap buttonPixmap{ buttonIcon.pixmap(buttonIcon.actualSize(QSize(60, 60))) };
    button.setIcon(buttonPixmap.transformed(QTransform().rotate(rotationFactor * 90)));
}

void GameWindow::resetPushButtonIcon()
{
    if (m_currentAction != Action::Add_SinglePylon)
    {
        m_pylonRotation = 0;
        m_ui->squareConfig1Button->setIcon(QPixmap("Static files/Images/SquarePylonConfig1.png"));
        m_ui->squareConfig2Button->setIcon(QPixmap("Static files/Images/SquarePylonConfig2.png"));
        m_ui->crossConfig1Button->setIcon(QPixmap("Static files/Images/CrossPylonConfig1.png"));
        m_ui->crossConfig2Button->setIcon(QPixmap("Static files/Images/CrossPylonConfig2.png"));
    }
}

QPoint GameWindow::matCoordToQPoint(const twixt::Position& pos)
{
    int boardSize{ m_game->getBoard().getSize() };
    double radius = 2.5;
    double circleSize{ std::min(width() / (radius * boardSize), height() / (radius * boardSize)) };

    double offsetX{ (width() - boardSize * circleSize * 2) / 2 };
    double offsetY{ (height() - boardSize * circleSize * 2) / 2 };

    const auto& [row, col] = pos;

    int x = (offsetX) + col * 2 * circleSize;
    int y = (offsetY) + row * 2 * circleSize;

    return { x, y };
}

twixt::Position GameWindow::qPointToMatCoord(const QPoint& pos)
{
    int boardSize{ m_game->getBoard().getSize() };
    double radius = 2.5;
    double circleSize{ std::min(width() / (radius * boardSize), height() / (radius * boardSize)) };

    double offsetX{ (width() - boardSize * circleSize * 2) / 2 };
    double offsetY{ (height() - boardSize * circleSize * 2) / 2 };

    const auto& [x, y] = pos;

    int row = (y - offsetY) / (2 * circleSize);
    int col = (x - offsetX) / (2 * circleSize);

    return { row, col };
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
