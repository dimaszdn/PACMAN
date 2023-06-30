#include<GameBar.h>
#include<Global.h>

GameBar::GameBar(sf::RenderWindow &window) : m_window(window)
{

}

void GameBar::setFont()
{
    if (!m_font.loadFromFile(font_path))
        throw std::exception("Font file not found!");
}

void GameBar::setStr(const std::string &str)
{
    m_str = str;
}

void GameBar::setup()
{
    setFont();
    m_text = sf::Text{m_str, m_font, CELL_SIZE * 4};
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setScale(0.5f, 0.5f);
    m_text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
    m_text.setPosition(sf::Vector2f(m_window.getView().getCenter().x, m_window.getView().getCenter().y));
}

void GameBar::draw()
{
    m_window.draw(m_text);
}