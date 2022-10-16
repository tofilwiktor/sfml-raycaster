#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

#define mapWidth 24
#define mapHeight 24
#define sWidth 640
#define sHeight 460


int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main()
{

	double posX = 22, posY = 12; 
	double dirX = -1, dirY = 0; 
	double planeX = 0, planeY = 0.66;

	double time = 0;   
        sf::RenderWindow window(sf::VideoMode(sWidth, sHeight), "Raycaster");
        window.setFramerateLimit(60);

        while (window.isOpen()) 
	{
            std::vector<sf::VertexArray> lines;

        sf::Clock clock;
        sf::Event event;

        while(window.pollEvent(event))
            if (event.type == sf::Event::Closed) window.close();

        for(int x = 0; x < sWidth; x++)
	    {
			double cameraX = 2 * x / double(sWidth) - 1; 
			double rayPosX = posX;
			double rayPosY = posY;
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;

			int mapX = int(rayPosX);
			int mapY = int(rayPosY);

			double sideDistX;
			double sideDistY;

			double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
			double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
			double perpWallDist;

			int stepX;
			int stepY;

			int hit = 0;
			int side; 

			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (rayPosX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (rayPosY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
			}

			while (hit == 0)
			{
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				if (worldMap[mapX][mapY] > 0) hit = 1;
			}

			if (side == 0)
			perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
			else
			perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);

			int lineHeight = abs(int(sHeight / perpWallDist));

			int drawStart = -lineHeight / 2 + sHeight / 2;
			if (drawStart < 0) drawStart = 0;
			int drawEnd = lineHeight / 2 + sHeight / 2;
			if (drawEnd >= sHeight) drawEnd = sHeight - 1;

                        sf::Color color;
			switch(worldMap[mapX][mapY])
			{
                            case 1:  color = sf::Color::Red;  break;
                            case 2:  color = sf::Color::Green;  break;
                            case 3:  color = sf::Color::Blue;   break;
                            case 4:  color = sf::Color::White;  break;
                            default: color = sf::Color::Yellow; break;
			}

			if (side == 1) {
                            color.r /= 2;
                            color.b /= 2;
                            color.g /= 2;
                        }

                        sf::VertexArray line(sf::LineStrip, 2);

                        line[0].position = sf::Vector2f(x, drawStart);
                        line[1].position = sf::Vector2f(x, drawEnd);

                        line[0].color = color;
                        line[1].color = color;
                        lines.push_back(line);
            }

                time = clock.getElapsedTime().asMilliseconds();
		double frameTime = time / 1000.0;

		double moveSpeed = frameTime * 200.0;
		double rotSpeed = frameTime * 120.0;

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
		  if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
		  if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
		  if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
		  if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
		  double oldDirX = dirX;
		  dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		  dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		  double oldPlaneX = planeX;
		  planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		  planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
		  double oldDirX = dirX;
		  dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		  dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		  double oldPlaneX = planeX;
		  planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		  planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		}

        for (auto& line : lines)
            window.draw(line);
        window.display();
        window.clear();
        clock.restart();
        }

	return 0;
}
