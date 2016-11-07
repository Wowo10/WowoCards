#include "GameEngine.hpp"

#include <memory>

#include "States/GameState.hpp"
#include "States/MainMenuState.hpp"


GameEngine::GameEngine()
	: gen(randomdevice())
{
	Init();
}

GameEngine::~GameEngine()
{
	delete resources;
}

void GameEngine::ChangeState(GameState* state)
{
	changestate = state;
	nextoperation = StateOperation::CHANGE;
}

void GameEngine::PushState(GameState* state)
{
	changestate = state;
	nextoperation = StateOperation::PUSH;
}

void GameEngine::PopState()
{
	nextoperation = StateOperation::POP;
}

void GameEngine::Update()
{
	if( !window.isOpen())
	{
		exit = true;
		return;
	}

	if(nextoperation != StateOperation::NONE)
	{
		window.setView(window.getDefaultView());
	}

	switch(nextoperation)
	{
		case StateOperation::CHANGE:
			if( !states.empty())
				states.pop_back();
			states.push_back(std::unique_ptr<GameState>(changestate));
			break;
		case StateOperation::PUSH:
			states.push_back(std::unique_ptr<GameState>(changestate));
			break;
		case StateOperation::POP:
			if( !states.empty())
				states.pop_back();
			break;
		case StateOperation::CLEAN:
			while( !states.empty())
				states.pop_back();
			break;
		case StateOperation::NONE:
		default:
			break;
	}

	nextoperation = StateOperation::NONE;

	HandleEvents();

	while(fpscounter.accumulator > fpscounter.TIME_STEP)
	{
		states.back()->Update(fpscounter.TIME_STEP);
		fpscounter.accumulator -= fpscounter.TIME_STEP;
	}

	fpscounter.CountFPS();

	Render();
}

void GameEngine::Exit()
{
	nextoperation = StateOperation::CLEAN;
	exit = true;
}

void GameEngine::Init()
{
	srand(time(NULL));

	InitLog();

	options.LoadFromFile();

	resources = new ResourceManager(options.language);

	if(options.first_run)
	{
		sf::VideoMode video = sf::VideoMode::getDesktopMode();

		window.create(sf::VideoMode(video.width, video.height), "Space Tails");//, sf::Style::Fullscreen);


		options.resolution_x = video.width;
		options.resolution_y = video.height;
		options.first_run = false;
		options.sets[8]  = std::to_string(options.first_run);
		options.sets[10] = std::to_string(static_cast<int>(options.resolution_x));
		options.sets[11] = std::to_string(static_cast<int>(options.resolution_y));

		options.SaveToFile();
	}
	else
	{
		if (options.fullscreen)
			window.create(sf::VideoMode(options.resolution_x, options.resolution_y), "Space Tails", sf::Style::Fullscreen);
		else
			window.create(sf::VideoMode(options.resolution_x, options.resolution_y), "Space Tails");
	}

	sf::Image icon;
	icon.loadFromFile("Data/img/icons/icon.png");

	window.setIcon(128, 128, icon.getPixelsPtr());


	PushState(new MainMenuState(this));
}

void GameEngine::HandleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();*/

		states.back()->HandleEvents(event);
	}
}

void GameEngine::Render()
{
	window.clear();

	states.back()->Render();

	window.display();
}
