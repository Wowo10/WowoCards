#include "GameplayState.hpp"

#include "MainMenuState.hpp"

GameplayState::GameplayState(GameEngine* game)
	: GameState(game), end_gui(game->window)
{
	resources->InitVariables();

	plane = new Plane(sf::Color(0,50,0),engine->window); //#003200

	//testing Destructions - template of use
	sf::Sprite dest;
	dest.setTexture( *resources->GetTexture("shatteredearth"));
	dest.setPosition(engine->window.getSize().x/2,engine->window.getSize().y/2);
	dest.setOrigin(dest.getGlobalBounds().width/2,dest.getGlobalBounds().height/2);
	plane->AddDestruction(new Destruction(dest,2000));

	plane->AddDestruction("shatteredearth", sf::Vector2f(engine->window.getSize().x/4,engine->window.getSize().y/2),2000);

	units.push_back(new Unit("zombie",Course::LEFT,300)); //testings
	units.push_back(new Unit("zombie",Course::RIGHT,100));

	MAP_SIZE_X = resources->GetVariable("map_size_x");
	MAP_SIZE_Y = resources->GetVariable("map_size_y");

	srand(time(NULL));

	int seed = rand();
	gen.seed(seed);

	timer = resources->GetVariable("single_round_time");

	// explosion sound
	if (!sd_buffer.loadFromFile("Data/sound/explosion.wav"))
		Log("Sound not found: explosion.wav\n");

	///////////////////////////////////////////////////////////////////////////

	starttimer = fpscounter.GetTime() + 1000;

	camera.Init(sf::FloatRect(0, 0, engine->window.getSize().x, engine->window.getSize().y), CameraType::GAMEPLAY);

	sf::Text text;
	text.setFont(resources->font);
	text.setPosition(250, 60);
	text.setCharacterSize(70);
	text.setString(to_string(0));
	texts.push_back(text);

	text.setPosition(250, 200);
	text.setString(to_string(0));
	texts.push_back(text);
	//230, 220


	///***GUI***
	gui_theme = std::make_shared<tgui::Theme>("Data/gui/mainMenuButton.txt");

	tgui::ProgressBar::Ptr player_healthbar = std::make_shared<tgui::ProgressBar>();
	player_healthbar->setMinimum(0);
	player_healthbar->setMaximum(100);//players[0]->kMaxHP);
	player_healthbar->setValue(100);//players[0]->kMaxHP);
	player_healthbar->setOpacity(0.5);
	player_healthbar->setPosition(0.1 * tgui::bindWidth(gui),0.8 * tgui::bindHeight(gui));
	gui.add(player_healthbar,"main_player_healthbar");

	tgui::Label::Ptr time_diplay = std::make_shared<tgui::Label>();
	time_diplay->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	time_diplay->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	time_diplay->setText(to_string(timer.GetTimeLeft()));
	time_diplay->setFont(resources->font);
	time_diplay->setTextColor(tgui::Color("yellow"));
	time_diplay->setPosition(0.5 * tgui::bindWidth(gui), 0.05 * tgui::bindHeight(gui) );
	gui.add(time_diplay,"time_display");

	tgui::Label::Ptr kills_display = tgui::Label::copy(time_diplay);
	kills_display->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	kills_display->setPosition(0.05 * tgui::bindWidth(gui), 0.05 * tgui::bindHeight(gui) );
	kills_display->setText("Kills: 0");// + std::to_string(players[0]->kills));
	gui.add(kills_display,"kills_display");

	tgui::Label::Ptr deaths_display = tgui::Label::copy(time_diplay);
	deaths_display->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	deaths_display->setPosition(0.05 * tgui::bindWidth(gui), 0.07 * tgui::bindHeight(gui) );
	deaths_display->setText("Deaths: 0");// + std::to_string(players[0]->deaths));
	gui.add(deaths_display,"deaths_display");

	Player* ptr = AddPlayer(PlayerType::SHIP, ControlType::MANUAL);
	ptr->control.SetKeys(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::Space);
	ptr->control.SetActiveJoystick(0);

	/*AddPlayer(PlayerType::SHIP, ControlType::BOT);
	AddPlayer(PlayerType::SHIP, ControlType::BOT);
	AddPlayer(PlayerType::SHIP, ControlType::BOT);*/
}

GameplayState::~GameplayState()
{
	for(auto& it : players)
		delete it;

	for(auto& it : objects)
		delete it;

	for(auto& it : screams)
		delete it;

	delete plane;
}

float CountSqDistance(const sf::Vector2f& v1,const sf::Vector2f& v2)
{
	return (v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y);
}

void GameplayState::Update(float time_step)
{
	camera.Update();

	plane->UpdateDestructions();

	if(starttimer < fpscounter.GetTime())
	{
		float deltatime = time_step * timemultiplier;
		fpscounter.UpdateTime(deltatime * 1000);

		UpdateObjects(deltatime);

		CheckCollisions(deltatime);

		for(auto it = units.begin(); it != units.end();)
		{
			(*it)->Update(deltatime);


			if(!(*it)->attacking)
				for(auto jt = units.begin(); jt != units.end(); ++jt)
				{
					if(jt == it)
						continue;

					if(!(*jt)->attacking &&
							CountSqDistance((*it)->GetPosition(),(*jt)->GetPosition()) >
							resources->GetVariable("aggressiondistance"))
					{
						//aggressive moves
					}
				}

			if( (*it)->todelete)
			{
				delete (*it);
				it = units.erase(it);
			}
			else
				++it;
		}
	}

	if( !players.empty())
	{
		///Healthbar
		gui.get<tgui::ProgressBar>("main_player_healthbar")->setValue(players[0]->GetHP());

		///Kills and Deaths
		gui.get<tgui::Label>("kills_display")->setText("Kills: " + std::to_string(players[0]->kills));
		gui.get<tgui::Label>("deaths_display")->setText("Deaths: " + std::to_string(players[0]->deaths));
	}

	///Time Display
	gui.get<tgui::Label>("time_display")->setText(to_string(timer.GetTimeLeft()/60)+":"+to_string((timer.GetTimeLeft()%60)/10)+to_string((timer.GetTimeLeft()%60)%10));

	//Checking if the time has come ! ///END LEVEL SCREEEN
	if(timer.Passed() && !showendgui)
	{
		showendgui = true;

		///timer.RestartTimer(10);
	}

	if(timer.Passed() && showendgui)
	{
		engine->PopState();
	}

}

void GameplayState::HandleEvents(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		engine->PopState();

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		showgui = true;
	else
		showgui = false;


	for(auto& it : players)
	{
		it->CheckInput();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
		timemultiplier = timemultiplier/2.0f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
		timemultiplier = 1.0f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4))
		timemultiplier = timemultiplier*2.0f;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		camera.AddShakingEffect(2000);

	//gridview
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		plane->SwitchGridView();

	//dmg to all
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
		for(auto& it : units)
			it->ApplyDamage(1);

	//camera
	if(event.type == sf::Event::MouseWheelMoved)
	{
		camera.Zoom(event.mouseWheel.delta);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		camera.Zoom(1.0f);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		camera.Zoom(-1.0f);

	static int pausetimer = 0;
	if(pausetimer < fpscounter.GetTime() && sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		if(timemultiplier == 0.0f)
			timemultiplier = 1.0f;
		else
			timemultiplier = 0.0f;

		pausetimer = fpscounter.GetTime() + 300;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		rounds = 0;

		engine->ChangeState(new GameplayState(engine));
	}

	gui.handleEvent(event);
}

void GameplayState::Render()
{
	engine->window.clear(sf::Color(18, 17, 24));
	plane->Draw(engine->window);
	engine->window.setView(camera.view);

	RenderMapToActiveView();

	engine->window.setView(engine->window.getDefaultView());
	if(showgui)
	{
		for(auto& it : guielements)
			engine->window.draw(it);
		for(auto& it : texts)
			engine->window.draw(it);

	}
	gui.draw();
	if (showendgui)
	{
		end_gui.draw();
	}

	for(auto& it : units)
		it->Render(engine->window);
}

void GameplayState::RenderMapToActiveView()
{
	RenderObjectsToActiveView();
}

void GameplayState::RenderObjectsToActiveView()
{
	for(auto& it : objects)
		it->Render(engine->window);

	for(auto& it : players)
		it->Render(engine->window);
}

void GameplayState::UpdateObjects(float gametime)
{
	for(auto it = objects.begin(); it != objects.end();)
	{
		(*it)->Update(1.0);

		if( (*it)->todelete)
		{
			delete (*it);
			it = objects.erase(it);
		}
		else
			++it;
	}


	///players
	for(auto& it : players)
	{
		it->control.Update(&players);
		it->Update(1.0);

		if(it->GetHP()<=0 && it->alive)
		{
			KillPlayer(it);
			continue;
		}
	}
}

void GameplayState::CheckCollisions(float gametime)
{
	for(auto& it : players)
	{
		if( !it->alive)
			continue;

		//check collisions with all objects
		for(int j = 0; j < objects.size(); j++)
		{
			if(it->CheckBoundingBoxTest(objects[j]->sprite))
			{
				/*if(objects[j]->type == ObjectType::OBSTACLE)
				{
					if(it->CheckPixelPerfectTest(objects[j]->sprite))
					{
						//do something
					}
				}*/
			}
		}
	}
}


Player* GameplayState::AddPlayer(PlayerType type, ControlType controltype)
{
	players.push_back(new Player(type, playerid, controltype));
	players.back()->SetPosition(0.0f, 0.0f);

	playerid++;

	return players.back();
}

void GameplayState::KillPlayer(Player* player)
{
	if (player->alive)
	{
		sf::Sound* tmp_sound = new sf::Sound(sd_buffer);
		tmp_sound->setPitch(1 - (rand()%10)*0.01);
		tmp_sound->setVolume(engine->options.volumeSound);

		screams.push_back(tmp_sound);
		screams.back()->play();

		camera.AddShakingEffect(1000);

		player->Kill();
		player->deathtimer.AddDelta(5000);

	}
}