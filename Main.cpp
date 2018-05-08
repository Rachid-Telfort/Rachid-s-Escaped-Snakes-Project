#include<algorithm>
#include<cmath>
#include<cstddef>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<SFML/Config.hpp>
#include<SFML/Graphics/CircleShape.hpp>
#include<SFML/Graphics/Color.hpp>
#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/System/Clock.hpp>
#include<SFML/System/Time.hpp>
#include<SFML/System/Vector2.hpp>
#include<SFML/Window/Event.hpp>
#include<SFML/Window/VideoMode.hpp>
#include<SFML/Window/WindowStyle.hpp>

void setCircleShapes(sf::CircleShape (&circleShapes)[6u], float& floatingPoint)
{
    floatingPoint=180.0f;

    for(std::size_t index(0u); index<6u; ++index)
    {
        circleShapes[index].setFillColor(sf::Color::Blue);
        circleShapes[index].setRadius(128.0f/30.0f);
        circleShapes[index].setOrigin(circleShapes[index].getLocalBounds().left+circleShapes[index].getLocalBounds().width/2.0f, circleShapes[index].getLocalBounds().top+circleShapes[index].getLocalBounds().height/2.0f);

        if(!index)
        {
            circleShapes[index].setPointCount(6u);
            circleShapes[index].setRotation(180.0f);
            circleShapes[index].setPosition(64.0f, 10.0f);
        }

        else if(index==5u)
        {
            circleShapes[index].setPointCount(3u);
            circleShapes[index].setRotation(90.0f);
            circleShapes[index].setPosition(circleShapes[index-1u].getPosition().x+circleShapes[index-1u].getRadius(), circleShapes[index-1u].getPosition().y);
        }

        else
        {
            circleShapes[index].setPointCount(4u);
            circleShapes[index].setRotation(45.0f);
            circleShapes[index].setPosition(circleShapes[index-1u].getPosition().x+circleShapes[index-1u].getRadius(), circleShapes[index-1u].getPosition().y);
        }
    }
}

void setCircleShapesVector(std::vector<std::vector<sf::CircleShape> >& circleShapesVector, std::vector<bool>& booleanVector, std::vector<bool>& subBooleanVector, std::vector<float>& floatingPointVector, std::size_t sizeType=5u)
{
    circleShapesVector.resize(sizeType);
    booleanVector.resize(sizeType);
    subBooleanVector.resize(sizeType);
    floatingPointVector.resize(sizeType);

    std::fill(booleanVector.begin(), booleanVector.end(), true);

    std::fill(subBooleanVector.begin(), subBooleanVector.end(), false);

    std::fill(booleanVector.begin(), booleanVector.end(), 180.0f);

    for(std::vector<std::vector<sf::CircleShape> >::size_type index(0u); index<circleShapesVector.size(); ++index)
    {
        circleShapesVector[index].resize(4u);

        for(std::vector<sf::CircleShape>::size_type subIndex(0u); subIndex<circleShapesVector[index].size(); ++subIndex)
        {
            circleShapesVector[index][subIndex].setFillColor(sf::Color::Red);
            circleShapesVector[index][subIndex].setRadius(128.0f/30.0f);
            circleShapesVector[index][subIndex].setOrigin(circleShapesVector[index][subIndex].getLocalBounds().left+circleShapesVector[index][subIndex].getLocalBounds().width/2.0f, circleShapesVector[index][subIndex].getLocalBounds().top+circleShapesVector[index][subIndex].getLocalBounds().height/2.0f);

            if(!subIndex)
            {
                circleShapesVector[index][subIndex].setPointCount(6u);
                circleShapesVector[index][subIndex].setRotation(180.0f);
                circleShapesVector[index][subIndex].setPosition(64.0f, 118.0f);
            }

            else if(subIndex==3u)
            {
                circleShapesVector[index][subIndex].setPointCount(3u);
                circleShapesVector[index][subIndex].setRotation(90.0f);
                circleShapesVector[index][subIndex].setPosition(circleShapesVector[index][subIndex-1u].getPosition().x+circleShapesVector[index][subIndex-1u].getRadius(), circleShapesVector[index][subIndex-1u].getPosition().y);
            }

            else
            {
                circleShapesVector[index][subIndex].setPointCount(4u);
                circleShapesVector[index][subIndex].setRotation(45.0f);
                circleShapesVector[index][subIndex].setPosition(circleShapesVector[index][subIndex-1u].getPosition().x+circleShapesVector[index][subIndex-1u].getRadius(), circleShapesVector[index][subIndex-1u].getPosition().y);
            }
        }
    }
}

void setCircleShape(sf::CircleShape& circleShape)
{
    circleShape.setFillColor(sf::Color(165u, 42u, 42u));
    circleShape.setRadius(128.0f/5.0f);
    circleShape.setPosition(64.0f, 64.0f);
    circleShape.setOrigin(circleShape.getLocalBounds().left+circleShape.getLocalBounds().width/2.0f, circleShape.getLocalBounds().top+circleShape.getLocalBounds().height/2.0f);
}

void setRenderWindow(sf::RenderWindow& renderWindow)
{
    sf::Uint8 uInt8s[100u*100u*4];

    for(std::size_t index(0u); index<100u*100u*4; index+=4u)
    {
        if(index%3u)
        {
            uInt8s[index]=255u;
            uInt8s[index+1u]=0u;
            uInt8s[index+2u]=0u;
            uInt8s[index+3u]=255u;
        }

        else if(index%5u)
        {
            uInt8s[index]=0u;
            uInt8s[index+1u]=0u;
            uInt8s[index+2u]=255u;
            uInt8s[index+3]=255u;
        }

        else
        {
            uInt8s[index]=255u;
            uInt8s[index+1u]=255u;
            uInt8s[index+2u]=0u;
            uInt8s[index+3]=255u;
        }
    }

    renderWindow.create(sf::VideoMode(128u, 128u, sf::VideoMode::getDesktopMode().bitsPerPixel), "Escaped Snakes", sf::Style::Close);
    renderWindow.setIcon(100u, 100u, uInt8s);
    renderWindow.setVerticalSyncEnabled(true);
}

void drawCircleShapes(const sf::CircleShape (&circleShapes)[6u], sf::RenderWindow& renderWindow)
{
    for(std::size_t index(0u); index<6u; ++index)
    {
        renderWindow.draw(circleShapes[index]);
    }
}

void drawCircleShapesVector(const std::vector<std::vector<sf::CircleShape> >& circleShapesVector, const std::vector<bool>& booleanVector, sf::RenderWindow& renderWindow)
{
    for(std::vector<std::vector<sf::CircleShape> >::size_type index(0u); index<circleShapesVector.size(); ++index)
    {
        if(booleanVector[index])
        {
            for(std::vector<sf::CircleShape>::size_type subIndex(0u); subIndex<circleShapesVector[index].size(); ++subIndex)
            {
                renderWindow.draw(circleShapesVector[index][subIndex]);
            }
        }
    }
}

void updateCircleShapes(sf::CircleShape (&circleShapes)[6u], float& floatingPoint, const sf::Time& time, const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
                case sf::Keyboard::A:
                {
                    if(circleShapes[0u].getPosition().x>circleShapes[0u].getRadius()*2.0f)
                    {
                        if(floatingPoint>180.0f)
                        {
                            floatingPoint-=90.0f;
                        }

                        else if(floatingPoint<180.0f)
                        {
                            floatingPoint+=90.0f;
                        }

                        sf::Vector2f vector2f(circleShapes[0u].getPosition());
                        sf::Vector2f subVector2f;

                        circleShapes[0u].move(-circleShapes[0u].getRadius()*std::sin(floatingPoint*time.asSeconds()*3.14f/180.0f), 0.0f);

                        if(floatingPoint==180.0f)
                        {
                            circleShapes[0u].move(-time.asSeconds()*300.0f, 0.0f);
                        }

                        for(std::size_t index(1u); index<6u; ++index)
                        {
                            subVector2f=circleShapes[index].getPosition();
                            circleShapes[index].setPosition(vector2f);
                            vector2f=subVector2f;

                            if(index==5u&&circleShapes[index].getRotation()!=90.0f)
                            {
                                circleShapes[index].setRotation(90.0f);
                            }
                        }
                    }

                    break;
                }

                case sf::Keyboard::D:
                {
                    if(circleShapes[0u].getPosition().x<128.0f-circleShapes[0u].getRadius()*2.0f)
                    {
                        if(floatingPoint>360.0f)
                        {
                            floatingPoint-=90.0f;
                        }

                        else if(floatingPoint<360.0f)
                        {
                            floatingPoint+=90.0f;
                        }

                        sf::Vector2f vector2f(circleShapes[0u].getPosition());
                        sf::Vector2f subVector2f;

                        circleShapes[0u].move(circleShapes[0u].getRadius()*std::sin(floatingPoint*time.asSeconds()*3.14f/180.0f), 0.0f);

                        if(floatingPoint==360.0f)
                        {
                            circleShapes[0u].move(time.asSeconds()*300.0f, 0.0f);
                        }

                        for(std::size_t index(1u); index<6u; ++index)
                        {
                            subVector2f=circleShapes[index].getPosition();
                            circleShapes[index].setPosition(vector2f);
                            vector2f=subVector2f;

                            if(index==5u&&circleShapes[index].getRotation()!=270.0f)
                            {
                                circleShapes[index].setRotation(270.0f);
                            }
                        }
                    }

                    break;
                }

                case sf::Keyboard::Down:
                {
                    if(circleShapes[0u].getPosition().y<128.0f-circleShapes[0u].getRadius()*2.0f)
                    {
                        if(floatingPoint>270.0f)
                        {
                            floatingPoint-=90.0f;
                        }

                        else if(floatingPoint<270.0f)
                        {
                            floatingPoint+=90.0f;
                        }

                        sf::Vector2f vector2f(circleShapes[0u].getPosition());
                        sf::Vector2f subVector2f;

                        circleShapes[0u].move(0.0f, circleShapes[0u].getRadius()*std::cos(floatingPoint*time.asSeconds()*3.14f/180.0f));

                        for(std::size_t index(1u); index<6u; ++index)
                        {
                            subVector2f=circleShapes[index].getPosition();
                            circleShapes[index].setPosition(vector2f);
                            vector2f=subVector2f;

                            if(index==5u&&circleShapes[index].getRotation()!=0.0f)
                            {
                                circleShapes[index].setRotation(0.0f);
                            }
                        }
                    }

                    break;
                }

                case sf::Keyboard::Left:
                {
                    if(circleShapes[0u].getPosition().x>circleShapes[0u].getRadius()*2.0f)
                    {
                        if(floatingPoint>180.0f)
                        {
                            floatingPoint-=90.0f;
                        }

                        else if(floatingPoint<180.0f)
                        {
                            floatingPoint+=90.0f;
                        }

                        sf::Vector2f vector2f(circleShapes[0u].getPosition());
                        sf::Vector2f subVector2f;

                        circleShapes[0u].move(-circleShapes[0u].getRadius()*std::sin(floatingPoint*time.asSeconds()*3.14f/180.0f), 0.0f);

                        if(floatingPoint==180.0f)
                        {
                            circleShapes[0u].move(-time.asSeconds()*300.0f, 0.0f);
                        }

                        for(std::size_t index(1u); index<6u; ++index)
                        {
                            subVector2f=circleShapes[index].getPosition();
                            circleShapes[index].setPosition(vector2f);
                            vector2f=subVector2f;

                            if(index==5u&&circleShapes[index].getRotation()!=90.0f)
                            {
                                circleShapes[index].setRotation(90.0f);
                            }
                        }
                    }

                    break;
                }

                case sf::Keyboard::Right:
                {
                    if(circleShapes[0u].getPosition().x<128.0f-circleShapes[0u].getRadius()*2.0f)
                    {
                        if(floatingPoint>360.0f)
                        {
                            floatingPoint-=90.0f;
                        }

                        else if(floatingPoint<360.0f)
                        {
                            floatingPoint+=90.0f;
                        }

                        sf::Vector2f vector2f(circleShapes[0u].getPosition());
                        sf::Vector2f subVector2f;

                        circleShapes[0u].move(circleShapes[0u].getRadius()*std::sin(floatingPoint*time.asSeconds()*3.14f/180.0f), 0.0f);

                        if(floatingPoint==360.0f)
                        {
                            circleShapes[0u].move(time.asSeconds()*300.0f, 0.0f);
                        }

                        for(std::size_t index(1u); index<6u; ++index)
                        {
                            subVector2f=circleShapes[index].getPosition();
                            circleShapes[index].setPosition(vector2f);
                            vector2f=subVector2f;

                            if(index==5u&&circleShapes[index].getRotation()!=270.0f)
                            {
                                circleShapes[index].setRotation(270.0f);
                            }
                        }
                    }

                    break;
                }

                case sf::Keyboard::S:
                {
                    if(circleShapes[0u].getPosition().y<128.0f-circleShapes[0u].getRadius()*2.0f)
                    {
                        if(floatingPoint>270.0f)
                        {
                            floatingPoint-=90.0f;
                        }

                        else if(floatingPoint<270.0f)
                        {
                            floatingPoint+=90.0f;
                        }

                        sf::Vector2f vector2f(circleShapes[0u].getPosition());
                        sf::Vector2f subVector2f;

                        circleShapes[0u].move(0.0f, circleShapes[0u].getRadius()*std::cos(floatingPoint*time.asSeconds()*3.14f/180.0f));

                        for(std::size_t index(1u); index<6u; ++index)
                        {
                            subVector2f=circleShapes[index].getPosition();
                            circleShapes[index].setPosition(vector2f);
                            vector2f=subVector2f;

                            if(index==5u&&circleShapes[index].getRotation()!=0.0f)
                            {
                                circleShapes[index].setRotation(0.0f);
                            }
                        }
                    }

                    break;
                }

                case sf::Keyboard::Up:
                {
                    if(circleShapes[0u].getPosition().y>circleShapes[0u].getRadius()*2.0f)
                    {
                        if(floatingPoint>90.0f)
                        {
                            floatingPoint-=90.0f;
                        }

                        else if(floatingPoint<90.0f)
                        {
                            floatingPoint+=90.0f;
                        }

                        sf::Vector2f vector2f(circleShapes[0u].getPosition());
                        sf::Vector2f subVector2f;

                        circleShapes[0u].move(0.0f, -circleShapes[0u].getRadius()*std::cos(floatingPoint*time.asSeconds()*3.14f/180.0f));

                        for(std::size_t index(1u); index<6u; ++index)
                        {
                            subVector2f=circleShapes[index].getPosition();
                            circleShapes[index].setPosition(vector2f);
                            vector2f=subVector2f;

                            if(index==5u&&circleShapes[index].getRotation()!=180.0f)
                            {
                                circleShapes[index].setRotation(180.0f);
                            }
                        }
                    }

                    break;
                }

                case sf::Keyboard::W:
                {
                    if(circleShapes[0u].getPosition().y>circleShapes[0u].getRadius()*2.0f)
                    {
                        if(floatingPoint>90.0f)
                        {
                            floatingPoint-=90.0f;
                        }

                        else if(floatingPoint<90.0f)
                        {
                            floatingPoint+=90.0f;
                        }

                        sf::Vector2f vector2f(circleShapes[0u].getPosition());
                        sf::Vector2f subVector2f;

                        circleShapes[0u].move(0.0f, -circleShapes[0u].getRadius()*std::cos(floatingPoint*time.asSeconds()*3.14f/180.0f));

                        for(std::size_t index(1u); index<6u; ++index)
                        {
                            subVector2f=circleShapes[index].getPosition();
                            circleShapes[index].setPosition(vector2f);
                            vector2f=subVector2f;

                            if(index==5u&&circleShapes[index].getRotation()!=180.0f)
                            {
                                circleShapes[index].setRotation(180.0f);
                            }
                        }
                    }

                    break;
                }

                default:
                {
                    break;
                }
            }

            break;
        }

        default:
        {
            break;
        }
    }
}

void interact(sf::CircleShape (&circleShapes)[6u], const std::vector<std::vector<sf::CircleShape> >& circleShapesVector, std::vector<bool>& booleanVector, std::vector<bool>& subBooleanVector, const sf::CircleShape& circleShape, const sf::Event& event)
{
    switch(event.type)
    {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
                case sf::Keyboard::Space:
                {
                    if(circleShapes[0u].getFillColor()==sf::Color::Blue)
                    {
                        for(std::vector<std::vector<sf::CircleShape> >::size_type index(0u); index<circleShapesVector.size(); ++index)
                        {
                            for(std::vector<sf::CircleShape>::size_type subIndex(0u); subIndex<circleShapesVector[index].size(); ++subIndex)
                            {
                                if(circleShapes[0u].getGlobalBounds().intersects(circleShapesVector[index][subIndex].getGlobalBounds())&&booleanVector[index])
                                {
                                    booleanVector[index]=false;

                                    for(std::size_t subSubIndex(0u); subSubIndex<6u; ++subSubIndex)
                                    {
                                        circleShapes[subSubIndex].setFillColor(sf::Color::Red);
                                    }

                                    return;
                                }
                            }
                        }
                    }

                    else
                    {
                        if(circleShapes[0u].getGlobalBounds().intersects(circleShape.getGlobalBounds()))
                        {
                            for(std::vector<bool>::size_type index(0u); index<booleanVector.size(); ++index)
                            {
                                if(!booleanVector[index]&&!subBooleanVector[index])
                                {
                                    subBooleanVector[index]=true;

                                    break;
                                }
                            }

                            for(std::size_t subIndex(0u); subIndex<6u; ++subIndex)
                            {
                                circleShapes[subIndex].setFillColor(sf::Color::Blue);
                            }
                        }

                        else
                        {
                            for(std::vector<bool>::size_type index(0u); index<booleanVector.size(); ++index)
                            {
                                if(!booleanVector[index]&&!subBooleanVector[index])
                                {
                                    booleanVector[index]=true;

                                    for(std::size_t subIndex(0u); subIndex<6u; ++subIndex)
                                    {
                                        circleShapes[subIndex].setFillColor(sf::Color::Blue);
                                    }

                                    break;
                                }
                            }
                        }
                    }

                    break;
                }

                default:
                {
                    break;
                }
            }

            break;
        }

        default:
        {
            break;
        }
    }
}

void subInteract(sf::CircleShape (&circleShapes)[6u], const std::vector<std::vector<sf::CircleShape> >& circleShapesVector, std::vector<bool>& booleanVector, const std::vector<bool>& subBooleanVector)
{
    for(std::vector<std::vector<sf::CircleShape> >::size_type index(0u); index<circleShapesVector.size(); ++index)
    {
        for(std::vector<sf::CircleShape>::size_type subIndex(0u); subIndex<circleShapesVector[index].size(); ++subIndex)
        {
            if(circleShapes[0u].getGlobalBounds().intersects(circleShapesVector[index][subIndex].getGlobalBounds())&&booleanVector[index])
            {
                for(std::vector<bool>::size_type subSubIndex(0u); subSubIndex<booleanVector.size(); ++subSubIndex)
                {
                    if(!booleanVector[subSubIndex]&&!subBooleanVector[subSubIndex])
                    {
                        booleanVector[subSubIndex]=true;

                        for(std::size_t subSubSubIndex(0u); subSubSubIndex<6u; ++subSubSubIndex)
                        {
                            circleShapes[subSubSubIndex].setFillColor(sf::Color::Blue);
                        }

                        return;
                    }
                }
            }
        }
    }
}

void updateCircleShapesSubVector(std::vector<sf::CircleShape>& circleShapesSubVector, float& floatingPoint, std::size_t sizeType, const sf::Time& time)
{
    switch(sizeType)
    {
        case 0u:
        {
            if(circleShapesSubVector[0u].getPosition().x>circleShapesSubVector[0u].getRadius()*2.0f)
            {
                if(floatingPoint>180.0f)
                {
                    floatingPoint-=90.0f;
                }

                else if(floatingPoint<180.0f)
                {
                    floatingPoint+=90.0f;
                }

                sf::Vector2f vector2f(circleShapesSubVector[0u].getPosition());
                sf::Vector2f subVector2f;

                circleShapesSubVector[0u].move(-circleShapesSubVector[0u].getRadius()*std::sin(floatingPoint*time.asSeconds()*3.14f/180.0f), 0.0f);

                if(floatingPoint==180.0f)
                {
                    circleShapesSubVector[0u].move(-time.asSeconds()*300.0f, 0.0f);
                }

                for(std::size_t index(1u); index<4u; ++index)
                {
                    subVector2f=circleShapesSubVector[index].getPosition();
                    circleShapesSubVector[index].setPosition(vector2f);
                    vector2f=subVector2f;

                    if(index==3u&&circleShapesSubVector[index].getRotation()!=90.0f)
                    {
                        circleShapesSubVector[index].setRotation(90.0f);
                    }
                }
            }

            break;
        }

        case 1u:
        {
            if(circleShapesSubVector[0u].getPosition().x<128.0f-circleShapesSubVector[0u].getRadius()*2.0f)
            {
                if(floatingPoint>360.0f)
                {
                    floatingPoint-=90.0f;
                }

                else if(floatingPoint<360.0f)
                {
                    floatingPoint+=90.0f;
                }

                sf::Vector2f vector2f(circleShapesSubVector[0u].getPosition());
                sf::Vector2f subVector2f;

                circleShapesSubVector[0u].move(circleShapesSubVector[0u].getRadius()*std::sin(floatingPoint*time.asSeconds()*3.14f/180.0f), 0.0f);

                if(floatingPoint==360.0f)
                {
                    circleShapesSubVector[0u].move(time.asSeconds()*300.0f, 0.0f);
                }

                for(std::size_t index(1u); index<4u; ++index)
                {
                    subVector2f=circleShapesSubVector[index].getPosition();
                    circleShapesSubVector[index].setPosition(vector2f);
                    vector2f=subVector2f;

                    if(index==3u&&circleShapesSubVector[index].getRotation()!=270.0f)
                    {
                        circleShapesSubVector[index].setRotation(270.0f);
                    }
                }
            }

            break;
        }

        case 2u:
        {
            if(circleShapesSubVector[0u].getPosition().y>circleShapesSubVector[0u].getRadius()*2.0f)
            {
                if(floatingPoint>90.0f)
                {
                    floatingPoint-=90.0f;
                }

                else if(floatingPoint<90.0f)
                {
                    floatingPoint+=90.0f;
                }

                sf::Vector2f vector2f(circleShapesSubVector[0u].getPosition());
                sf::Vector2f subVector2f;

                circleShapesSubVector[0u].move(0.0f, -circleShapesSubVector[0u].getRadius()*std::cos(floatingPoint*time.asSeconds()*3.14f/180.0f));

                for(std::size_t index(1u); index<4u; ++index)
                {
                    subVector2f=circleShapesSubVector[index].getPosition();
                    circleShapesSubVector[index].setPosition(vector2f);
                    vector2f=subVector2f;

                    if(index==3u&&circleShapesSubVector[index].getRotation()!=180.0f)
                    {
                        circleShapesSubVector[index].setRotation(180.0f);
                    }
                }
            }

            break;
        }

        case 3u:
        {
            if(circleShapesSubVector[0u].getPosition().y<128.0f-circleShapesSubVector[0u].getRadius()*2.0f)
            {
                if(floatingPoint>270.0f)
                {
                    floatingPoint-=90.0f;
                }

                else if(floatingPoint<270.0f)
                {
                    floatingPoint+=90.0f;
                }

                sf::Vector2f vector2f(circleShapesSubVector[0u].getPosition());
                sf::Vector2f subVector2f;

                circleShapesSubVector[0u].move(0.0f, circleShapesSubVector[0u].getRadius()*std::cos(floatingPoint*time.asSeconds()*3.14f/180.0f));

                for(std::size_t index(1u); index<4u; ++index)
                {
                    subVector2f=circleShapesSubVector[index].getPosition();
                    circleShapesSubVector[index].setPosition(vector2f);
                    vector2f=subVector2f;

                    if(index==3u&&circleShapesSubVector[index].getRotation()!=0.0f)
                    {
                        circleShapesSubVector[index].setRotation(0.0f);
                    }
                }
            }

            break;
        }

        default:
        {
            break;
        }
    }
}

void updateCircleShapesVector(std::vector<std::vector<sf::CircleShape> >& circleShapesVector, std::vector<bool>& booleanVector, std::vector<float>& floatingPointVector, const sf::Time& time)
{
    for(std::vector<std::vector<sf::CircleShape> >::size_type index(0u); index<circleShapesVector.size(); ++index)
    {
        if(booleanVector[index])
        {
            updateCircleShapesSubVector(circleShapesVector[index], floatingPointVector[index], std::rand()%4u, time);
        }
    }
}

bool checkBooleanVectors(const std::vector<bool>& booleanVector, const std::vector<bool>& subBooleanVector)
{
    if(std::find(booleanVector.begin(), booleanVector.end(), true)==booleanVector.end()&&std::find(subBooleanVector.begin(), subBooleanVector.end(), false)==subBooleanVector.end())
    {
        return true;
    }

    return false;
}

void addCircleShapesSubVector(std::vector<std::vector<sf::CircleShape> >& circleShapesVector, std::vector<bool>& booleanVector, std::vector<bool>& subBooleanVector, std::vector<float>& floatingPointVector)
{
    if(circleShapesVector.size()<circleShapesVector.max_size()&&booleanVector.size()<booleanVector.max_size()&&subBooleanVector.size()<subBooleanVector.max_size()&&floatingPointVector.size()<floatingPointVector.max_size())
    {
        booleanVector.push_back(false);

        std::fill(booleanVector.begin(), booleanVector.end(), true);

        subBooleanVector.push_back(false);

        std::fill(subBooleanVector.begin(), subBooleanVector.end(), false);

        floatingPointVector.push_back(0.0f);

        std::fill(floatingPointVector.begin(), floatingPointVector.end(), 180.0f);

        circleShapesVector.push_back(std::vector<sf::CircleShape>(4u));

        for(std::vector<sf::CircleShape>::size_type index(0u); index<circleShapesVector.back().size(); ++index)
        {
            circleShapesVector.back()[index].setFillColor(sf::Color::Red);
            circleShapesVector.back()[index].setRadius(128.0f/30.0f);
            circleShapesVector.back()[index].setOrigin(circleShapesVector.back()[index].getLocalBounds().left+circleShapesVector.back()[index].getLocalBounds().width/2.0f, circleShapesVector.back()[index].getLocalBounds().top+circleShapesVector.back()[index].getLocalBounds().height/2.0f);

            if(!index)
            {
                circleShapesVector.back()[index].setPointCount(6u);
                circleShapesVector.back()[index].setRotation(180.0f);
                circleShapesVector.back()[index].setPosition(64.0f, 118.0f);
            }

            else if(index==3u)
            {
                circleShapesVector.back()[index].setPointCount(3u);
                circleShapesVector.back()[index].setRotation(90.0f);
                circleShapesVector.back()[index].setPosition(circleShapesVector.back()[index-1u].getPosition().x+circleShapesVector.back()[index-1u].getRadius(), circleShapesVector.back()[index-1u].getPosition().y);
            }

            else
            {
                circleShapesVector.back()[index].setPointCount(4u);
                circleShapesVector.back()[index].setRotation(45.0f);
                circleShapesVector.back()[index].setPosition(circleShapesVector.back()[index-1u].getPosition().x+circleShapesVector.back()[index-1u].getRadius(), circleShapesVector.back()[index-1u].getPosition().y);
            }
        }
    }

    else
    {
        std::fill(booleanVector.begin(), booleanVector.end(), true);

        std::fill(subBooleanVector.begin(), subBooleanVector.end(), false);

        std::fill(floatingPointVector.begin(), floatingPointVector.end(), 180.0f);
    }
}

void run(sf::CircleShape (&circleShapes)[6u], float& floatingPoint, std::vector<std::vector<sf::CircleShape> >& circleShapesVector, std::vector<bool>& booleanVector, std::vector<bool>& subBooleanVector, std::vector<float>& floatingPointVector, sf::CircleShape& circleShape, sf::RenderWindow& renderWindow, sf::Clock& clock, sf::Time& time, sf::Event& event)
{
    while(renderWindow.isOpen())
    {
        while(renderWindow.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                {
                    renderWindow.close();

                    return;
                }

                case sf::Event::KeyPressed:
                {
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Escape:
                        {
                            renderWindow.close();

                            return;
                        }

                        default:
                        {
                            updateCircleShapes(circleShapes, floatingPoint, time, event);

                            interact(circleShapes, circleShapesVector, booleanVector, subBooleanVector, circleShape, event);

                            break;
                        }
                    }

                    break;
                }

                default:
                {
                    break;
                }
            }
        }

        updateCircleShapesVector(circleShapesVector, booleanVector, floatingPointVector, time);

        subInteract(circleShapes, circleShapesVector, booleanVector, subBooleanVector);

        if(checkBooleanVectors(booleanVector, subBooleanVector))
        {
            addCircleShapesSubVector(circleShapesVector, booleanVector, subBooleanVector, floatingPointVector);
        }

        time=clock.restart();

        renderWindow.clear(sf::Color::Yellow);

        renderWindow.draw(circleShape);
        drawCircleShapes(circleShapes, renderWindow);
        drawCircleShapesVector(circleShapesVector, booleanVector, renderWindow);

        renderWindow.display();
    }
}

int main()
{
    std::srand(std::time(NULL));

    sf::CircleShape circleShapes[6];
    float floatingPoint;

    std::vector<std::vector<sf::CircleShape> > circleShapesVector;
    std::vector<bool> booleanVector;
    std::vector<bool> subBooleanVector;
    std::vector<float> floatingPointVector;

    sf::CircleShape circleShape;

    sf::RenderWindow renderWindow;

    sf::Clock clock;

    sf::Time time;

    sf::Event event;

    setCircleShapes(circleShapes, floatingPoint);
    setCircleShapesVector(circleShapesVector, booleanVector, subBooleanVector, floatingPointVector);
    setCircleShape(circleShape);
    setRenderWindow(renderWindow);

    run(circleShapes, floatingPoint, circleShapesVector, booleanVector, subBooleanVector, floatingPointVector, circleShape, renderWindow, clock, time, event);

    return 0;
}
