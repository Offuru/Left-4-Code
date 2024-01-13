#include "GameWindow.h"

GameWindow::GameWindow(QWidget* parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow(parent), m_ui{ std::make_unique<Ui::GameWindowClass>() }
{
    setWindowState(Qt::WindowMaximized);

	m_game = game;

	m_ui->setupUi(this);

    m_currentPlayer = m_game->getCurrentPlayer();

    m_currentAction = Action::None;
    m_pylonRotation = 0;
    m_currentBridgeStartPos = { -1,-1 };
    m_pylonPlaced = false;
    m_gameEnded = false;
    m_currentStatus = twixt::Game::GameStatus::None;

    m_ui->player1NameLabel->setStyleSheet("QLabel { background-color : red; color : green; }");

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
    QObject::connect(m_ui->nextRoundButton, &QPushButton::clicked, this, &GameWindow::nextRoundAction);

    QObject::connect(m_ui->swapPlayersButton, &QPushButton::clicked, this, &GameWindow::swapButtonAction);

    QObject::connect(m_ui->saveGameButton, &QPushButton::clicked, this, &GameWindow::saveGameAction);

    QObject::connect(m_ui->loadGameButton, &QPushButton::clicked, this, &GameWindow::loadGameAction);
}

GameWindow::~GameWindow()
{}

void GameWindow::swapButtonAction()
{
    if (m_game->getRound() != 1) return;
    m_game->swapPlayers();
    m_currentPlayer = m_game->getCurrentPlayer();
    m_ui->swapPlayersButton->hide();
    m_pylonPlaced = true;
    updateNumberPylonsPlayersLabel();
}

void GameWindow::nextRoundAction()
{
    if (!m_pylonPlaced || m_gameEnded) return;

    m_game->setRound(m_game->getRound() + 1);

    if (m_game->getDebuilderBob()) { m_game->moveBob(); update(); };
    m_pylonPlaced = false;
    m_currentAction = Action::None;
    resetPushButtonIcon();
    m_currentStatus = m_game->getCurrentGameStatus(m_currentPlayer->getColor());

    if (m_currentStatus == twixt::Game::GameStatus::Draw)
    {
        m_endDialog = std::make_unique<EndDialog>(this, "It's a draw!");
        m_gameEnded = true;
        m_endDialog->show();
    }

    if (m_currentPlayer->getColor() == m_game->getPlayer2()->getColor())
    {
        m_game->setCurrentPlayer(nonstd::make_observer<twixt::IPlayer>(m_game->getPlayer1().get()));
        m_currentPlayer = m_game->getCurrentPlayer();
        m_ui->player1NameLabel->setStyleSheet("QLabel { background-color : red; color : green; }");
        m_ui->player2NameLabel->setStyleSheet("QLabel { background-color : transparent; color : black; }");
    }
    else
    {
        m_game->setCurrentPlayer(nonstd::make_observer<twixt::IPlayer>(m_game->getPlayer2().get()));
        m_currentPlayer = m_game->getCurrentPlayer();
        m_ui->player1NameLabel->setStyleSheet("QLabel { background-color : transparent; color : black; }");
        m_ui->player2NameLabel->setStyleSheet("QLabel { background-color : red; color : green; }");
    }
}

void GameWindow::saveGameAction()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text file (*.txt)");

    m_game->saveGame(fileName.toStdString());
}

void GameWindow::loadGameAction()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Text file (*.txt)");

    m_game->loadGame(fileName.toStdString());
    update();
}

void GameWindow::setFoundationsPoints(const std::vector<QPoint>& foundationsPoints)
{
    m_foundationsPoints = foundationsPoints;
}

void GameWindow::setPlayersNameLabel()
{
    m_ui->player1NameLabel->setText(m_game->getPlayer1()->getName().c_str());
    m_ui->player2NameLabel->setText(m_game->getPlayer2()->getName().c_str());
}

void GameWindow::updateNumberPylonsPlayersLabel()
{
    m_ui->noPylonsPlayer1Label->setText(std::to_string(m_game->getPlayer1()->getNoPylons1x1()).c_str());
    m_ui->noPylonsPlayer2Label->setText(std::to_string(m_game->getPlayer2()->getNoPylons1x1()).c_str());
    m_ui->noBridgesPlayer1Label->setText(std::to_string(m_game->getPlayer1()->getNoBridges()).c_str());
    m_ui->noBridgesPlayer2Label->setText(std::to_string(m_game->getPlayer2()->getNoBridges()).c_str());
    if (m_game->getBigPylons())
    {
        m_ui->noSqPylonsPlayer1Label->setText(std::to_string(m_game->getPlayer1()->getNoPylons2x2()).c_str());
        m_ui->noSqPylonsPlayer2Label->setText(std::to_string(m_game->getPlayer2()->getNoPylons2x2()).c_str());
        m_ui->noCsPylonsPlayer1Label->setText(std::to_string(m_game->getPlayer1()->getNoPylonsCross()).c_str());
        m_ui->noCsPylonsPlayer2Label->setText(std::to_string(m_game->getPlayer2()->getNoPylonsCross()).c_str());
    }
    else
    {
        m_ui->noSqPylons1Label->hide();
        m_ui->noSqPylonsPlayer1Label->hide();

        m_ui->noSqPylons2Label->hide();
        m_ui->noSqPylonsPlayer2Label->hide();

        m_ui->noCsPylons1Label->hide();
        m_ui->noCsPylonsPlayer1Label->hide();
        m_ui->noCsPylons2Label->hide();
        m_ui->noCsPylonsPlayer2Label->hide();
    }
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
    m_currentPlayer = m_game->getCurrentPlayer();

    bool result = false;
    switch (m_currentAction)
    {
        case GameWindow::Action::Add_SinglePylon:
            if (m_game->getMinedFoundations() && m_game->placingPylonOnMine(matPosition, twixt::Pylon::Type::Single)) m_currentAction = Action::Add_Mine, m_pylonPlaced = true;
            result = m_game->addPylon(matPosition, twixt::Pylon::Type::Single, m_currentPlayer->getColor(), m_pylonRotation);
            break;
        case GameWindow::Action::Add_SquarePylonConfig1:
            if (m_game->getMinedFoundations() && m_game->placingPylonOnMine(matPosition, twixt::Pylon::Type::Square)) m_currentAction = Action::Add_Mine, m_pylonPlaced = true;
            result = m_game->addPylon(matPosition, twixt::Pylon::Type::Square, m_currentPlayer->getColor(), m_pylonRotation);
            break;
        case GameWindow::Action::Add_SquarePylonConfig2:
            if (m_game->getMinedFoundations() && m_game->placingPylonOnMine(matPosition, twixt::Pylon::Type::Square)) m_currentAction = Action::Add_Mine, m_pylonPlaced = true;
            result = m_game->addPylon(matPosition, twixt::Pylon::Type::Square, m_currentPlayer->getColor(), m_pylonRotation, false);
            break;
        case GameWindow::Action::Add_CrossPylonConfig1:
            if (m_game->getMinedFoundations() && m_game->placingPylonOnMine(matPosition, twixt::Pylon::Type::Cross)) m_currentAction = Action::Add_Mine, m_pylonPlaced = true;
            result = m_game->addPylon(matPosition, twixt::Pylon::Type::Cross, m_currentPlayer->getColor(), m_pylonRotation);
            break;
        case GameWindow::Action::Add_CrossPylonConfig2:
            if (m_game->getMinedFoundations() && m_game->placingPylonOnMine(matPosition, twixt::Pylon::Type::Cross)) m_currentAction = Action::Add_Mine, m_pylonPlaced = true;
            result = m_game->addPylon(matPosition, twixt::Pylon::Type::Cross, m_currentPlayer->getColor(), m_pylonRotation, false);
            break;
        default:
            break;
    }
    if (result)
    {
        if (m_game->getRound() == 1) m_ui->swapPlayersButton->hide();

        resetPushButtonIcon();
        m_currentAction = Action::None;
        m_pylonRotation = 0;
        m_pylonPlaced = true;
        updateNumberPylonsPlayersLabel();
    }
}

void GameWindow::addBridge(const twixt::Position& endPosition)
{
    if (m_currentAction == Action::Add_Bridge)
    {
        bool result = m_game->addBridge(m_currentBridgeStartPos, endPosition, m_currentPlayer->getColor());
        updateNumberPylonsPlayersLabel();
        if (result)
            m_currentAction = Action::None;
    }
    else
    {
        m_currentAction = Action::Add_Bridge;
        m_currentBridgeStartPos = endPosition;
    }
    m_currentStatus = m_game->getCurrentGameStatus(m_currentPlayer->getColor());
    if (m_currentStatus == twixt::Game::GameStatus::Won)
    {
        m_gameEnded = true;
        std::string message = m_currentPlayer->getName() + " won!";
        m_endDialog = std::make_unique<EndDialog>(this, message.c_str());
        m_endDialog->show();
    }
}

void GameWindow::removeBridge(const twixt::Position& endPosition)
{
    if (m_currentAction == Action::Remove_Bridge)
    {
        m_currentAction = Action::None;
        m_game->removeBridge(m_currentBridgeStartPos, endPosition, m_currentPlayer->getColor());
    } 
    else
    {
        m_currentAction = Action::Remove_Bridge;
        m_currentBridgeStartPos = endPosition;
    }
}

void GameWindow::drawBoard(QPainter* painter)
{
    std::reference_wrapper<twixt::Board> currentBoard{ m_game->getBoard() };

    int boardSize{ currentBoard.get().getSize() };

    int circleSize{ int(std::min((width() / (2.5 * boardSize)), (height() / (2.5 * boardSize)))) };
    QSize circleQSize = { circleSize,circleSize };

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

                    QPen penLine{ brush, 3 };
                    painter->setPen(penLine);
                    for (const auto& bridge : currentPylon->getConnections())
                    {
                        const auto& [startPosRow, startPosCol] = bridge->getPosStart();
                        const auto& [endPosRow, endPosCol] = bridge->getPosEnd();
                        size_t startPoint = boardSize * startPosRow + startPosCol;
                        size_t endPoint = boardSize * endPosRow + endPosCol;
                        QPoint startPos{ m_foundationsPoints[startPoint].x() + circleSize/ 2, m_foundationsPoints[startPoint].y() + circleSize / 2 };
                        QPoint endPos{ m_foundationsPoints[endPoint].x() + circleSize / 2, m_foundationsPoints[endPoint].y() + circleSize / 2 };
                        painter->drawLine(startPos, endPos);
                    }
                    painter->setPen(Qt::NoPen);
                    if (currentPylon->getType() != twixt::Pylon::Type::Single)
                    {
                        painter->setBrush(Qt::cyan);
                        QRect bgSquare = QRect(matCoordToQPoint(foundationPos), circleQSize);
                        double padding{ 1.f * circleSize / 2 };
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

                painter->setBrush(brush);
                painter->drawEllipse(QRect(matCoordToQPoint(foundationPos), circleQSize));
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
    if (m_gameEnded) return;
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
            if (event->button() == Qt::LeftButton)
            {
                if (m_currentAction == Action::Add_Mine) m_game->placeMine(matPosition) ? (m_currentAction = Action::None) : (m_currentAction = Action::Add_Mine);
                else if (!m_pylonPlaced)
                {
                    if (m_currentAction == Action::None) m_currentAction = Action::Add_SinglePylon;
                    addPylon(matPosition);
                }
                else if (m_game->getBoard().getFoundation(matPosition).getPylon() != nullptr)
                    addBridge(matPosition);
            }
            else
                removeBridge(matPosition);
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
    if (m_currentAction == Action::None || m_currentAction != Action::Add_SinglePylon)
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
    double radius = 2.5;
    int circleSize{ int(std::min(width() / (radius * boardSize), height() / (radius * boardSize))) };

    QPoint topLeftCorner{ matCoordToQPoint({0, 0}) };
    QPoint bottomRightCorner{ matCoordToQPoint({boardSize - 1, boardSize - 1}) };

    bottomRightCorner.setX(bottomRightCorner.x() + circleSize);
    bottomRightCorner.setY(bottomRightCorner.y() + circleSize);

    return { topLeftCorner, bottomRightCorner };
}
