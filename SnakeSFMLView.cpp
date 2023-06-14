//
// Created by c on 5/24/23.
//

#include "SnakeSFMLView.h"
#include <iostream>

SnakeSFMLView::SnakeSFMLView(Snake &s1, SnakeBoard &b1) : snake(s1), board(b1)
{
    cellWidth = WINDOW_WIDTH/MAP_SIZE;
    cellHeight = WINDOW_HEIGHT/MAP_SIZE;

    menuBackground = sf::RectangleShape(sf::Vector2f(800, 600));
    menuBackground.setFillColor(sf::Color(34,177,77));
    menuButtonPlay = sf::RectangleShape(sf::Vector2f(300, 100));
    menuButtonEasy = sf::RectangleShape(sf::Vector2f(100, 100));
    menuButtonNormal = sf::RectangleShape(sf::Vector2f(100, 100));
    menuButtonHard = sf::RectangleShape(sf::Vector2f(100, 100));

    load_all_txsp();
    if(font.loadFromFile("../OpenSans-Bold.ttf"))
    {} // https://fonts.google.com/specimen/Open+Sans/about?preview.text=1234567890&preview.text_type=custom
}

void SnakeSFMLView::draw(sf::RenderWindow &win)
{
    int x_pos = 0;
    int y_pos = 0;

    if(board.get_status() == MENU)
    {
        display_menu_screen(win);
        return;
    }

    for(int row=0; row<MAP_SIZE; ++row)
    {
        for(int col=0; col<MAP_SIZE; ++col)
        {
            draw_logic(row, col, x_pos, y_pos, win);
            x_pos += cellWidth;
        }
        x_pos=0;
        y_pos += cellHeight;
    }

    if(snake.get_status()==DEAD)
    {
        display_end_screen(win);
    }
}

void SnakeSFMLView::load_all_txsp()
{
    if(!end_screen_loss.tx.loadFromFile("../textures/lost.png", sf::IntRect(0, 0, 100, 100)))
        exit(1);
    end_screen_loss.sp.setTexture(end_screen_loss.tx);

    if(!end_screen_win.tx.loadFromFile("../textures/won.png", sf::IntRect(0, 0, 100, 100)))
        exit(1);
    end_screen_win.sp.setTexture(end_screen_win.tx);

    if(!snakeHead.tx.loadFromFile("../textures/karpHead.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    snakeHead.sp.setTexture(snakeHead.tx);

    if(!snakeTail.tx.loadFromFile("../textures/karpTail.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    snakeTail.sp.setTexture(snakeTail.tx);

    if(!grass.tx.loadFromFile("../textures/grass.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    grass.sp.setTexture(grass.tx);

    if(!wall_1.tx.loadFromFile("../textures/wall_1.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    wall_1.sp.setTexture(wall_1.tx);

    if(!wall_2.tx.loadFromFile("../textures/wall_2.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    wall_2.sp.setTexture(wall_2.tx);

    if(!apple.tx.loadFromFile("../textures/apple.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    apple.sp.setTexture(apple.tx);

    if(!snakeBody.tx.loadFromFile("../textures/karpBody.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    snakeBody.sp.setTexture(snakeBody.tx);

    if(!buttonPlay.tx.loadFromFile("../textures/buttonPlay.png", sf::IntRect(0, 0, 300, 100)))
        exit(1);
    buttonPlay.sp.setTexture(buttonPlay.tx);

    if(!buttonEasy.tx.loadFromFile("../textures/buttonEasy.png", sf::IntRect(0, 0, 100, 100)))
        exit(1);
    buttonEasy.sp.setTexture(buttonEasy.tx);

    if(!buttonNormal.tx.loadFromFile("../textures/buttonNormal.png", sf::IntRect(0, 0, 100, 100)))
        exit(1);
    buttonNormal.sp.setTexture(buttonNormal.tx);

    if(!buttonHard.tx.loadFromFile("../textures/buttonHard.png", sf::IntRect(0, 0, 100, 100)))
        exit(1);
    buttonHard.sp.setTexture(buttonHard.tx);

}

void SnakeSFMLView::display_end_screen(sf::RenderWindow &win)
{
    sf::Text scoreTable;
    scoreTable.setString("BEST SCORES:");
    scoreTable.setFont(font);
    scoreTable.setFillColor(sf::Color::Red);
    scoreTable.setCharacterSize(60);
    scoreTable.setOrigin(scoreTable.getGlobalBounds().width/2, scoreTable.getGlobalBounds().height/2);
    scoreTable.setPosition(WINDOW_WIDTH/2, scoreTable.getGlobalBounds().height/2);
    win.draw(scoreTable);

    sf::Text displayed_score;
    displayed_score.setFont(font);
    displayed_score.setCharacterSize(60);
    displayed_score.setFillColor(sf::Color::Black);
    displayed_score.setOrigin(displayed_score.getGlobalBounds().width/2, displayed_score.getGlobalBounds().height/2);

    if(board.get_scoreBoardUpdated == false)
        board.update_bestScores();
    const int* bestScores = board.get_bestScores();
    int x_pos=WINDOW_WIDTH/2;
    int y_pos=displayed_score.getGlobalBounds().height/2+scoreTable.getGlobalBounds().height;
    displayed_score.setPosition(x_pos, y_pos);

    for(int place = 1; place<=10; place++)
    {
        std::string score;
        score.append(std::to_string(place));
        score.append(". ");
        score.append(std::to_string(bestScores[place-1]));
        displayed_score.setString(score);
        displayed_score.setPosition(x_pos-displayed_score.getGlobalBounds().width/2, y_pos);
        win.draw(displayed_score);
        displayed_score.setPosition(x_pos-displayed_score.getGlobalBounds().width/2, y_pos+=displayed_score.getGlobalBounds().height);
    }

}

void SnakeSFMLView::draw_logic(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
{
    draw_grass(x_pos, y_pos, win);
    draw_apple(row, col, x_pos, y_pos, win);
    draw_wall(row, col, x_pos, y_pos, win);
    draw_snake(row, col, x_pos, y_pos, win);
}

void SnakeSFMLView::draw_object(int x_pos, int y_pos, sf::RenderWindow &win, sf::Sprite objectSprite, float rotationInDegrees, float factorX, float factorY)
{
    objectSprite.setRotation(rotationInDegrees);
    objectSprite.setScale(factorX, factorY);
    objectSprite.setPosition(x_pos, y_pos);
    win.draw(objectSprite);
}

void SnakeSFMLView::draw_apple(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
{
    if(board.check_for_apple(row, col))
    {
        draw_object(x_pos, y_pos, win,apple.sp, 0, 1, 1);
    }
}

void SnakeSFMLView::draw_wall(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
{
    if(board.check_for_wall(row, col))
    {
        if((row*MAP_SIZE+col) % 2 == 0)
            draw_object(x_pos, y_pos, win,wall_1.sp, 0, 1, 1);
        else
            draw_object(x_pos, y_pos, win,wall_2.sp, 0, 1 ,1);
    }
}

void SnakeSFMLView::draw_grass(int x_pos, int y_pos, sf::RenderWindow &win)
{
    draw_object(x_pos, y_pos, win,grass.sp, 0, 1, 1);
}

void SnakeSFMLView::draw_snake(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
{
    set_snake_origin();
    x_pos+=80/2;
    y_pos+=60/2;

    for(int cell : snake.get_snakeBody())
    {
        if(cell == snake.get_snake_head() && cell == row*MAP_SIZE+col)
            draw_snakeHead(x_pos, y_pos, win);
        else if(cell == snake.get_snake_tail() && cell == row*MAP_SIZE+col)
            draw_snakeTail(x_pos, y_pos, win);
        else if (cell == row*MAP_SIZE+col)
            draw_snakeBody(x_pos, y_pos, win);
    }
}

void SnakeSFMLView::snakeHead_facing(float &rotationInDegrees, float &factorX, float &factorY)
{
    switch (snake.get_snake_facing())
    {
        case UP: {
            rotationInDegrees = 90;
            factorX=-1.0f;
            factorY=80.0f/60.0f*1.0f;
            break;
        }
        case DOWN: {
            rotationInDegrees = 90;
            factorX=1.0f;
            factorY=80.0f/60.0f*-1.0f;
            break;
        }
        case RIGHT: {
            rotationInDegrees = 0;
            factorX=1.0f;
            factorY=1.0f;
            break;
        }
        case LEFT: {
            rotationInDegrees = 0;
            factorX=-1.0f;
            factorY=1.0f;
            break;
        }
    }
}


void SnakeSFMLView::draw_snakeHead(int x_pos, int y_pos, sf::RenderWindow &win)
{
    float headRotation;
    float headFactorX, headFactorY;
    snakeHead_facing(headRotation, headFactorX, headFactorY);
    draw_object(x_pos, y_pos, win,snakeHead.sp, headRotation, headFactorX, headFactorY);
}


void SnakeSFMLView::draw_snakeBody(int x_pos, int y_pos, sf::RenderWindow &win)
{
    draw_object(x_pos, y_pos, win, snakeBody.sp, 0,1, 1);
}

void SnakeSFMLView::draw_snakeTail(int x_pos, int y_pos, sf::RenderWindow &win)
{
    float rotationInDegrees, factorX, factorY;
    snakeTail_facing(rotationInDegrees, factorX, factorY);
    draw_object(x_pos,y_pos,win, snakeTail.sp, rotationInDegrees, factorX, factorY);
}

void SnakeSFMLView::snakeTail_facing(float &rotationInDegrees, float &factorX, float &factorY)
{
    int index = static_cast<int>(snake.get_snakeBody().size())-2;
    bool bodyOnRight = snake.get_snakeBody()[index] == snake.get_snake_tail() + 1;
    bool bodyOnLeft = snake.get_snakeBody()[index] == snake.get_snake_tail() - 1;
    bool bodyAbove = snake.get_snakeBody()[index] / MAP_SIZE - 1 == snake.get_snake_tail() / MAP_SIZE;
    bool bodyBelow = snake.get_snakeBody()[index] / MAP_SIZE + 1 == snake.get_snake_tail() / MAP_SIZE;
    bool bodyInSameColumn = snake.get_snakeBody()[index] % MAP_SIZE == snake.get_snake_tail() % MAP_SIZE;

    if(bodyOnRight)
    {
        rotationInDegrees = 0;
        factorX = 1;
        factorY = 1;
    }
    else if(bodyOnLeft)
    {
        rotationInDegrees = 180;
        factorX = 1;
        factorY = 1;
    }
    else if(bodyAbove and bodyInSameColumn)
    {
        rotationInDegrees = 90;
        factorX = 1;
        factorY = 80.0f/60.0f*-1.0f;
    }
    else if(bodyBelow and bodyInSameColumn)
    {
        rotationInDegrees = 270;
        factorX = 1;
        factorY = 80.0f/60.0f*-1.0f;
    }
}


sf::FloatRect SnakeSFMLView::get_menuButtonPlay()
{
    return menuButtonPlay.getGlobalBounds();
}

sf::FloatRect SnakeSFMLView::get_menuButtonEasy()
{
    return menuButtonEasy.getGlobalBounds();
}

sf::FloatRect SnakeSFMLView::get_menuButtonNormal()
{
    return menuButtonNormal.getGlobalBounds();
}

sf::FloatRect SnakeSFMLView::get_menuButtonHard()
{
    return menuButtonHard.getGlobalBounds();
}

void SnakeSFMLView::display_menu_screen(sf::RenderWindow &win)
{
    set_menuButtons_origin();
    set_menuButtons_position();
    set_menuButtons_color();
    draw_menuButtons(win);
}

void SnakeSFMLView::set_menuButtons_origin()
{
    menuButtonPlay.setOrigin(menuButtonPlay.getSize().x/2 , menuButtonPlay.getSize().y/2);
    menuButtonEasy.setOrigin(menuButtonEasy.getSize().x/2 , menuButtonEasy.getSize().y/2);
    menuButtonNormal.setOrigin(menuButtonNormal.getSize().x/2 , menuButtonNormal.getSize().y/2);
    menuButtonHard.setOrigin(menuButtonHard.getSize().x/2 , menuButtonHard.getSize().y/2);

    buttonPlay.sp.setOrigin(buttonPlay.sp.getGlobalBounds().width/2 , buttonPlay.sp.getGlobalBounds().height/2);
    buttonEasy.sp.setOrigin(buttonEasy.sp.getGlobalBounds().width/2 , buttonEasy.sp.getGlobalBounds().height/2);
    buttonNormal.sp.setOrigin(buttonNormal.sp.getGlobalBounds().width/2 , buttonNormal.sp.getGlobalBounds().height/2);
    buttonHard.sp.setOrigin(buttonHard.sp.getGlobalBounds().width/2 , buttonHard.sp.getGlobalBounds().height/2);
}

void SnakeSFMLView::set_menuButtons_position()
{
    float centreScreenX = 800.0f/2;
    float centreScreenY = 600.0f/2;
    float difficultyOffsetY = 150;
    float difficultyOffsetX= 150;
    menuButtonPlay.setPosition(centreScreenX, centreScreenY);
    menuButtonEasy.setPosition(centreScreenX-difficultyOffsetX, centreScreenY + difficultyOffsetY);
    menuButtonNormal.setPosition(centreScreenX, centreScreenY + difficultyOffsetY);
    menuButtonHard.setPosition(centreScreenX+difficultyOffsetX, centreScreenY + difficultyOffsetY);

    buttonPlay.sp.setPosition(centreScreenX, centreScreenY);
    buttonEasy.sp.setPosition(centreScreenX-difficultyOffsetX, centreScreenY + difficultyOffsetY);
    buttonNormal.sp.setPosition(centreScreenX, centreScreenY + difficultyOffsetY);
    buttonHard.sp.setPosition(centreScreenX+difficultyOffsetX, centreScreenY + difficultyOffsetY);
}

void SnakeSFMLView::set_menuButtons_color()
{
    menuButtonPlay.setFillColor(sf::Color(166, 230, 29));
    switch(board.get_GameDifficulty())
    {
        case EASY:
        {
            menuButtonEasy.setFillColor(sf::Color(11, 115, 40));
            menuButtonNormal.setFillColor(sf::Color(166, 230, 29));
            menuButtonHard.setFillColor(sf::Color(166, 230, 29));
            break;
        }
        case NORMAL:
        {
            menuButtonEasy.setFillColor(sf::Color(166, 230, 29));
            menuButtonNormal.setFillColor(sf::Color(11, 115, 40));
            menuButtonHard.setFillColor(sf::Color(166, 230, 29));
            break;
        }
        case HARD:
        {
            menuButtonEasy.setFillColor(sf::Color(166, 230, 29));
            menuButtonNormal.setFillColor(sf::Color(166, 230, 29));
            menuButtonHard.setFillColor(sf::Color(11, 115, 40));
            break;
        }
    }
}

void SnakeSFMLView::draw_menuButtons(sf::RenderWindow &win)
{
    win.draw(menuBackground);
    win.draw(menuButtonPlay);
    win.draw(menuButtonEasy);
    win.draw(menuButtonNormal);
    win.draw(menuButtonHard);

    win.draw(buttonPlay.sp);
    win.draw(buttonEasy.sp);
    win.draw(buttonNormal.sp);
    win.draw(buttonHard.sp);
}

void SnakeSFMLView::set_snake_origin()
{
    snakeHead.sp.setOrigin(snakeHead.sp.getGlobalBounds().width/2, snakeHead.sp.getGlobalBounds().height/2);
    snakeTail.sp.setOrigin(snakeTail.sp.getGlobalBounds().width/2, snakeTail.sp.getGlobalBounds().height/2);
    snakeBody.sp.setOrigin(snakeBody.sp.getGlobalBounds().width/2, snakeBody.sp.getGlobalBounds().height/2);
}