//Player Bullets to enemy Ships

for (std::vector<Fund::Bullet>::iterator bulletIterator = bullets.begin(); bulletIterator != bullets.end();)
{
    //FOR EVERY ENEMY SPRITE...
    for (auto enemyIterator = enemies.begin(); enemyIterator != enemies.end();)
    {
        //TEST FOR COLLISION BETWEEN PLAYER BULLET AND ENEMY
        if (Fund::areSpritesOverLapping(bulletIterator->sprite, enemyIterator->sprite))
        {
            //DESTROY BULLET
            bulletIterator = bullets.erase(bulletIterator);
            //DESTROY ENEMY
            enemyIterator = enemies.erase(enemyIterator);

            //UPDATE ENEMYITERATOR TO THE NEXT VALID ITERATOR AFTER ERASING AN ENEMY
            if (enemyIterator != enemies.end())
                enemyIterator++;

            //IF WE DESTROY THE LAST OBJECT IN ONE OF THE CONTAINERS, THEN STOP COMPARING.
            if (bulletIterator == bullets.end())
                break; // LEAVE THE FOR LOOP.
        }
        else
        {
            //IF NO COLLISION, MOVE ON TO NEXT ENEMY.
            enemyIterator++;
        }
    }

    //UPDATE BULLETITERATOR TO THE NEXT VALID ITERATOR AFTER ERASING A BULLET
    if (bulletIterator != bullets.end())
        bulletIterator++;
}
