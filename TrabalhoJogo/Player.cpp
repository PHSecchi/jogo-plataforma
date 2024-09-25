#include "Player.h"

Player::Player(IdsColidiveis ID, sf::Vector2f sz, sf::Vector2f pos, sf::Vector2f vel, string texturePath, float* t, sf::RenderWindow* window):
	Character(ID, sz, pos, vel, texturePath, t, window),
	slowness(1.f),
	alive(false),
	canJump(true),
	jumpHeight(150.f),
	prevPunishment(1),
	currentPunishment(1),
	score(10000.f)
{
}

Player::~Player()
{
}

void Player::draw()
{
	windowPtr->draw(body);
}

void Player::collide(IdsColidiveis eId, sf::Vector2f ePosition, sf::Vector2f eSize, Entity* e)
{
	slowness = 1.f;

	if (e->getId() == IdsColidiveis::goblin)
		die();

	if (e->getId() == IdsColidiveis::bomberGoblin)
		die();

	if (e->getId() == IdsColidiveis::bomb)
		die();

	if (e->getId() == IdsColidiveis::trap)
		die(e);

	if (e->getId() == IdsColidiveis::slime)
		slowness = 4.f;

	if (e->getId() == IdsColidiveis::spike)
		die();

	if (e->getId() == IdsColidiveis::boss)
		die();
}

void Player::die()
{
	alive = false;
	punish();
}

void Player::die(Entity* e)
{
	if (e->getId() != IdsColidiveis::trap)
		punish();
}

bool Player::isAlive()
{
	return alive;
}

void Player::restart()
{
	velocity = sf::Vector2f(0.f, 0.f);
	alive = true;
}

void Player::setCanJump(bool canJump)
{
	this->canJump = canJump;
}

void Player::load(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f size, bool flip, bool canJump, int hp, int prevPunishment, int currentPunishment, float jumpHeight, float score)
{
	this->position = pos;
	this->velocity = vel;
	this->size = size;
	this->flip = flip;
	this->canJump = canJump;
	this->jumpHeight = jumpHeight;
	this->prevPunishment = prevPunishment;
	this->currentPunishment = currentPunishment;
	this->score = score;
}

void Player::save()
{
	/* all output operations happen at the end of the file, appending to its existing contents. */
	ofstream ofs("saves/Player.txt", ios::app);

	if (ofs.is_open())
	{
		ofs << body.getPosition().x << ' ' << body.getPosition().y << ' ' << velocity.x << ' ' << velocity.y << ' ' << body.getSize().x << ' ' <<
			body.getSize().y << ' ' << flip << ' ' << hp << ' ' << canJump << ' ' << jumpHeight << ' ' << currentPunishment << ' ' <<
			prevPunishment << ' ' << score << endl;

		ofs.close();
	}
	else
	{
		cout << "Unable to open \"saves/Player.txt\" in \"Player.cpp\"" << endl;
		exit(1);
	}
}


void Player::punish()
{
	int aux = currentPunishment;
	currentPunishment += prevPunishment;
	prevPunishment = aux;
	score = 10000.f - currentPunishment * 2;
}

float Player::getScore()
{
	return score;
}

int Player::getCurrentPunishment()
{
	return currentPunishment;
}

int Player::getPrevPunishment()
{
	return prevPunishment;
}

void Player::resetScore()
{
	score = 10000.f;
	prevPunishment = 1;
	currentPunishment = 1;
}