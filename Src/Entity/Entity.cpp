#include "Entity.h"
#include "../GameManager.h"
#include "../States/GameState/GameState.h"

// Function to get the opposite direction of the given direction
Directions GetOppositeDirection(Directions dir)
{
    switch (dir)
    {
    case Up:
        return Down;
        break;
    case Down:
        return Up;
        break;
    case Left:
        return Right;
        break;
    case Right:
        return Left;
        break;
    }
    return None;
}

// Entity constructor
Entity::Entity(GameState* gameState, Entities entityType)
{
    this->gameState = gameState;
    this->entityType = entityType;
}

// Function to get the final position of the entity's tile
sf::Vector2f Entity::GetFinalTilePosition()
{
    return sf::Vector2f((gridPos.x * gameState->tileWidth) - 5, (gridPos.y * gameState->tileHeight) - 5);
}

// Function to check if the neighboring tile in the given direction is available
bool Entity::IsNeighbourTileAvailable(Directions dir)
{
    switch (dir)
    {
    case Up:
        if (!gameState->tileArray[gridPos.x][gridPos.y - 1].DoesTileHaveType(sTile::Wall))
            return true;
        break;
    case Down:
        if (!gameState->tileArray[gridPos.x][gridPos.y + 1].DoesTileHaveType(sTile::Wall))
            return true;
        break;
    case Left:
        if (IsTeleportTile(sf::Vector2i(gridPos.x - 1, gridPos.y)))
            return false;
        if (!gameState->tileArray[gridPos.x - 1][gridPos.y].DoesTileHaveType(sTile::Wall))
            return true;
        break;
    case Right:
        if (IsTeleportTile(sf::Vector2i(gridPos.x + 1, gridPos.y)))
            return false;
        if (!gameState->tileArray[gridPos.x + 1][gridPos.y].DoesTileHaveType(sTile::Wall))
            return true;
        break;
    }

    return false;
}

// Function to check if the given position is a teleport tile
bool Entity::IsTeleportTile(sf::Vector2i pos)
{
    if (pos.x < 0 || pos.x > 27)
        return true;
    return false;
}

// Function to teleport the entity to the specified direction
void Entity::Teleport(Directions teleportTo)
{
    switch (teleportTo)
    {
    case Left:
        body.setPosition(sf::Vector2f((-1 * gameState->tileWidth) - 5, (gridPos.y * gameState->tileHeight) - 5));
        break;
    case Right:
        body.setPosition(sf::Vector2f((28 * gameState->tileWidth) - 5, (gridPos.y * gameState->tileHeight) - 5));
        break;
    }
}
