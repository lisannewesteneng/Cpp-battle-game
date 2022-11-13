#include "bitmapText.hpp"
#include <cstdio>

//////// choose your default font here:
/**/
/// option 1:
// source: opengameart.org, made by domsson, license CC0
std::string defaultFilename = "Fonts\\charmap-oldschool_white.png";
// character width & height:
int defaultCw = 7;
int defaultCh = 9;
int defaultCols = 18;
/**
/// option 2:
// source: opengameart.org, made by gnsh, license CC0
std::string defaultFilename = "gnsh-bitmapfont-colour8.png";
// character width & height:
int defaultCw = 5;
int defaultCh = 12;
int defaultCols = 20;
/**
/// option 3:
// source: opengameart.org, made by drakzlin, license CC0
std::string defaultFilename = "font_16seg_led_white_384x256px.png";
// character width & height:
int defaultCw = 24;
int defaultCh = 32;
int defaultCols = 16;
/**/

sf::Texture defaultFontTexture;
sf::Sprite defaultFontSprite; 


bitmapText::bitmapText() 
{
	static bool textureLoaded = false;
	if (!textureLoaded) {
		defaultFontTexture.loadFromFile(defaultFilename);
		defaultFontSprite.setTexture(defaultFontTexture);
		textureLoaded = true;
	}
	// initialize with default values, including default font sprite:
	this->cw = defaultCw;
	this->ch = defaultCh;
	this->cols = defaultCols;
	fontSprite = &defaultFontSprite;
	x = 0;
	y = 0;
	scale = 1;
	ox = 0;
	oy = 0;
	text = "";
}

void bitmapText::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

void bitmapText::setOrigin(float originX, float originY) {
	ox = originX;
	oy = originY;
}


void bitmapText::setString(const std::string& text) {
	this->text = text;
}

void bitmapText::setScale(float scale) {
	this->scale = scale;
}

void bitmapText::setCharacterSize(int pixelHeight) {
	scale = 1.0 * pixelHeight / ch;
}

void bitmapText::setFillColor(const sf::Color& color) {
	this->color = color;
}

void bitmapText::setFont(sf::Sprite& fontSprite, int charWidth, int charHeight, int columns) {
	this->fontSprite = &fontSprite;
	cw = charWidth;
	ch = charHeight;
	cols = columns;
}

sf::FloatRect bitmapText::getLocalBounds() {
	return sf::FloatRect(0, 0, scale * text.length() * cw, scale * ch);
}

void bitmapText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	fontSprite->setScale(sf::Vector2f(scale, scale));
	fontSprite->setColor(color);
	for (int i = 0; i < text.length(); i++) {
		int ascii = (int)text[i];
		if (ascii < 32 && ascii >= 128) {
			ascii = 32; // insert space for unknown characters
		}
		int frame = ascii - 32;
		int col = frame % cols;
		int row = frame / cols;

		fontSprite->setTextureRect(sf::IntRect(col * cw, row * ch, cw, ch));
		fontSprite->setPosition(x + i * cw * scale - ox, y - oy);
		target.draw(*fontSprite, states);
	}
}

void bitmapText::render(sf::RenderWindow& window) {
	window.draw(*this);
}

