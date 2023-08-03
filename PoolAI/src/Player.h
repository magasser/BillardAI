#pragma once

enum class PlayerIdentity
{
	PlayerOne,
	PlayerTwo
};

enum class PlayerType
{
	Player,
	AI,
};

class Player
{
public:
	Player(PlayerIdentity identity, PlayerType type) : m_Identity(identity), m_Type(type) {}

private:
	PlayerIdentity m_Identity;
	PlayerType m_Type;
};
