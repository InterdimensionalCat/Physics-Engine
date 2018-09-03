#pragma once
#include "AABB.h"
#include<SFML\Graphics.hpp>
#include <iostream>
#include "RigidBody.h"
#include "RigidCircle.h"
#include "CollisionEngine.h"
#include "RigidSquare.h"
#include "RigidPolygon.h"

/////////////////////// FILE PATH STUFF ////////////////////////

#include <stdio.h>  /* defines FILENAME_MAX */
#define WINDOWS
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>




std::string GetCurrentWorkingDir(void) {
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}


/////////////////////////////////////////////////////////////////

//prototypes that need to be used within Game.cpp, but not outside of it

void onUpdate(float deltaTime);
void draw(sf::RenderWindow* window, double interpol);

bool debug = true;
sf::RenderWindow* window;
std::vector<RigidCircle*> circles;
std::vector<RigidSquare*> squares;
std::vector<RigidPolygon*> polygons;


int main()
{

	//Initialize some objects for the gameloop

	window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "LMAO EZ"); //NB: TEXTURES CANNOT BE CREATED BEFORE THIS WINDOW IS INITIALIZED
	window->setFramerateLimit(60);

	//causes keypresses to only send 1 event

	window->setKeyRepeatEnabled(false);

	//More initialization

	sf::Clock gameLoopTimer;
	sf::Clock fpsTimer;
	uint16_t tps = 0;
	uint16_t fps = 0;

	//RigidBody* test1 = new RigidBody(Vec2D(1,0), 0.9, 10, 5, Vec2D(640/2 , 480/2));
	//RigidBody* test2 = new RigidBody(Vec2D(2, 0), 0.3, 15, 5, Vec2D(640 / 2 -50, 480 / 2));
	//RigidBody* test3 = new RigidBody(Vec2D(-1, 0), 0.5, 11, 5, Vec2D(640 / 2 + 45, 480 / 2));
	//RigidBody* test4 = new RigidBody(Vec2D(-1.1, 0), 0.2, 20, 5, Vec2D(640 / 2 +50, 480 / 2 -50));
	//RigidBody* test5 = new RigidBody(Vec2D(1.1, 0), 0.7, 10, 5, Vec2D(640 / 2 - 50, 480 / 2 - 50));

	//bodies.push_back(test1);
	//bodies.push_back(test2);
	//bodies.push_back(test3);
	//bodies.push_back(test4);
	//bodies.push_back(test5);

	//RigidBody* test1 = new RigidBody(Vec2D(10, 10), 0.9, 5, 5, Vec2D(30 , 30));
	//RigidBody* test2 = new RigidBody(Vec2D(-2.815582, -11), 0.3, 15, 30, Vec2D(1000 - 60 , 1000 - 60));

	//RigidCircle* test1 = new RigidCircle(Vec2D(20, 5), 0.9, 5, 5, Vec2D(10, 290));
	//RigidCircle* test2 = new RigidCircle(Vec2D(0, 0), 0.3, 15, 30, Vec2D(500, 370));

	//RigidCircle* test3 = new RigidCircle(Vec2D(0, 0), 0.1, 0, 100, Vec2D(500, 500));
	//RigidCircle* test4 = new RigidCircle(Vec2D(-2.815582, -11), 0.3, 15, 30, Vec2D(1000 - 60, 1000 - 60));

	//RigidCircle* test1 = new RigidCircle(Vec2D(90, 0), 0.9, 5, 5, Vec2D(100, 500));
	//RigidCircle* test2 = new RigidCircle(Vec2D(-10, 0), 0.3, 25, 100, Vec2D(700, 500));

	//circles.push_back(test1);
	//circles.push_back(test2);
	//circles.push_back(test3);
	//circles.push_back(test4);
	//bodies.push_back(test3);
	//bodies.push_back(test4);


	//RigidSquare* sTest1 = new RigidSquare(Vec2D(0, -10), 0.3, 10, Vec2D(500, 700), Vec2D(64, 64));
	//RigidSquare* sTest2 = new RigidSquare(Vec2D(-10, 0), 0.3, 30, Vec2D(800, 200), Vec2D(128, 128));


	//RigidSquare* sTest3 = new RigidSquare(Vec2D(0, 0), 0.0, 0, Vec2D(50, 900), Vec2D(900 / 5, 20));
	//RigidSquare* sTest4 = new RigidSquare(Vec2D(0, 0), 0.0, 0, Vec2D(50 + 900 / 5, 900), Vec2D(900 / 5, 20));
	//RigidSquare* sTest5 = new RigidSquare(Vec2D(0, 0), 0.0, 0, Vec2D(50 + 900*2 / 5, 900), Vec2D(900 / 5, 20));
	//RigidSquare* sTest6 = new RigidSquare(Vec2D(0, 0), 0.0, 0, Vec2D(50 + 900 * 3 / 5, 900), Vec2D(900 / 5, 20));
	//RigidSquare* sTest7 = new RigidSquare(Vec2D(0, 0), 0.0, 0, Vec2D(50 + 900 * 4 / 5, 900), Vec2D(900 / 5, 20));

	//RigidSquare* sTest3 = new RigidSquare(Vec2D(0, 0), 0.0, 0, Vec2D(50, 900), Vec2D(900, 20));

	//squares.push_back(sTest1);
	//squares.push_back(sTest2);
	//squares.push_back(sTest3);
	//squares.push_back(sTest4);
	//squares.push_back(sTest5);
	//squares.push_back(sTest6);
	//squares.push_back(sTest7);

	//RigidCircle* ctest1 = new RigidCircle(Vec2D(2, 40), 0.3, 10, 20, Vec2D(500, 290));

	//circles.push_back(ctest1);


	//RigidSquare* sTest1 = new RigidSquare(Vec2D(0, 5), 0.1, 10, Vec2D(500, 400), Vec2D(20, 20));
	//RigidSquare* sTest2 = new RigidSquare(Vec2D(1, 3), 0.3, 15, Vec2D(450, 400), Vec2D(20, 20));
	//RigidSquare* sTest3 = new RigidSquare(Vec2D(0, 4), 0.7, 20, Vec2D(550, 400), Vec2D(20, 20));

	//RigidSquare* sTest4 = new RigidSquare(Vec2D(0, 0), 0.0, 0, Vec2D(50, 900), Vec2D(900, 20));

	//RigidCircle* ctest1 = new RigidCircle(Vec2D(1, -1), 0.1, 10, 20, Vec2D(500, 500));
	//RigidCircle* ctest2 = new RigidCircle(Vec2D(-1, 3), 0.3, 15, 20, Vec2D(450, 500));
	//RigidCircle* ctest3 = new RigidCircle(Vec2D(0, 0), 0.9, 20, 20, Vec2D(550, 500));


	//squares.push_back(sTest1);
	//squares.push_back(sTest2);
	//squares.push_back(sTest3);
	//squares.push_back(sTest4);

	//circles.push_back(ctest1);
	//circles.push_back(ctest2);
	//circles.push_back(ctest3);

	std::vector<Vec2D> vertices = { Vec2D(75,25), Vec2D(100, 50), Vec2D(100, 100), Vec2D(50, 100), Vec2D(50 , 50) };


	RigidPolygon* pTest1 = new RigidPolygon(Vec2D(3, 5), 0.0, 10, &vertices, 5, 0.4, 0.25);

	polygons.push_back(pTest1);

	//vertices = { Vec2D(100,900), Vec2D(450, 200), Vec2D(900,300), Vec2D(900, 1000), Vec2D(100, 1000) };

	//RigidPolygon* pTest2 = new RigidPolygon(Vec2D(0, 0), 0.0, 0, &vertices, 5, 0.3, 0.2);

	//polygons.push_back(pTest2);

	vertices = { Vec2D(100, 400), Vec2D(450, 900), Vec2D(450, 1000), Vec2D(100, 1000) };

	RigidPolygon* pTest2 = new RigidPolygon(Vec2D(0, 0), 0.0, 0, &vertices, 4, 0.4, 0.25);

	polygons.push_back(pTest2);

	vertices = { Vec2D(451, 900), Vec2D(900, 1000), Vec2D(900, 1100), Vec2D(451, 1000) };

	RigidPolygon* pTest3 = new RigidPolygon(Vec2D(0, 0), 0.0, 0, &vertices, 4, 0.4, 0.25);

	polygons.push_back(pTest3);

	//Main game loop

	//Draw the simulation once first

	draw(window, 0);
	
	bool started = false;

	while (window->isOpen()) {

		//handle window events

		sf::Event event;


		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window->close();
			}

			if (event.type == sf::Event::KeyPressed) {
				started = true;
			}
		}

		//update game logic

		float deltaTime = gameLoopTimer.getElapsedTime().asSeconds();
		gameLoopTimer.restart();
		if (started) {
			onUpdate(deltaTime);
			tps++;
		}


		//allows the debugger to show the current frames per second and ticks per second

		if (fpsTimer.getElapsedTime().asSeconds() >= 1) {
			fpsTimer.restart();
			if (debug) {
				std::cout << "tps: " << tps << " fps: " << fps << std::endl;
			}
			tps = 0;
			fps = 0;
		}

		window->clear(sf::Color(255, 255, 255, 255));

		//draw objects

		draw(window, gameLoopTimer.getElapsedTime().asSeconds() * 60);

		fps++;
		window->display();
	}


	return 0;
}

//deltatime is in seconds
void onUpdate(float deltaTime) {
	for (auto c : circles) {
		c->onUpdate(deltaTime);
	}

	for (auto s : squares) {
		s->onUpdate(deltaTime);
	}

	for (auto p : polygons) {
		p->onUpdate(deltaTime);
	}

	int size = circles.size();

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			CircleCollision(circles.at(i), circles.at(j));
		}
	}

	size = squares.size();

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			AABBCollision(squares.at(i), squares.at(j));
		}
	}

	for (auto c : circles) {
		for (auto s : squares) {
			CircleToAABB(c, s);
		}
	}

	size = polygons.size();

	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			PolygontoPolygon(polygons.at(i), polygons.at(j));
		}
	}

}

void draw(sf::RenderWindow* window, double interpol) {
	for (auto c : circles) {
		window->draw(*c);
	}

	for (auto s : squares) {
		window->draw(*s);
	}

	for (auto p : polygons) {
		window->draw(*p);
	}
}
