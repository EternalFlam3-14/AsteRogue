#include <background.h>


bool Background::init(sf::Texture &backgroundtexture, sf::RenderWindow &window)
{
    
    sf::Sprite bkg;
    bkg.setTexture(backgroundtexture);

    bkg.setTextureRect(sf::IntRect(0, 0,
                       window.getView().getSize().x * BACKGROUND_SCALE,
                       window.getView().getSize().y * BACKGROUND_SCALE
                      ));

    bkg.setOrigin(bkg.getLocalBounds().width / 2, bkg.getLocalBounds().height / 2);

    auto columns = 55, rows = 55;

    sf::FloatRect texturebounds(0, 0, 0, 0);
    auto offsetY = window.getSize().y * 0.5f;
    auto offsetX = window.getSize().x * 0.5f;
    auto texturewidth = bkg.getTextureRect().getSize().x;
    auto textureheight = bkg.getTextureRect().getSize().y;

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            bkg.setPosition(texturewidth * (j - (rows / 2)), textureheight * (i - (columns / 2)));
            if (bkg.getGlobalBounds().left < mapBounds.left)
            {
                texturebounds.left = bkg.getGlobalBounds().left;
                mapBounds.left = bkg.getGlobalBounds().left;
            }
            if (bkg.getGlobalBounds().top < mapBounds.top)
            {
                texturebounds.top = bkg.getGlobalBounds().top;
                mapBounds.top = bkg.getGlobalBounds().top;
            }
            if (bkg.getGlobalBounds().width > mapBounds.width)
            {
                texturebounds.width = bkg.getGlobalBounds().width;
                mapBounds.width = bkg.getGlobalBounds().width;
            }
            if (bkg.getGlobalBounds().height > mapBounds.height)
            {
                texturebounds.height = bkg.getGlobalBounds().height;
                mapBounds.height = bkg.getGlobalBounds().height;
            }
            
            backgrounds.push_back(bkg);
        }
    }
    mapBounds.left += offsetX;
    mapBounds.top += offsetY;
    mapBounds.width -= offsetX;
    mapBounds.height -= offsetY;

    return true;

}


void Background::draw(sf::RenderWindow &window)
{
    auto viewRect = window.getView().getViewport();
    for (auto sprite : backgrounds)
    {
        auto objectRect = sprite.getGlobalBounds();
        if (objectRect.left < viewRect.left + viewRect.width ||
            objectRect.left + objectRect.width > viewRect.left ||
            objectRect.top < viewRect.top + viewRect.height ||
            objectRect.top + objectRect.height > viewRect.top) 
            {
                // Render the object only if any part is within the visible area
                window.draw(sprite);
            }
    }
}

