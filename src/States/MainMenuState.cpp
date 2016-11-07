#include "MainMenuState.hpp"
#include "OptionsState.hpp"
#include "CreditsState.hpp"
#include "GameplayState.hpp"

MainMenuState::MainMenuState(GameEngine* game)
	: GameState(game)
{
	///GUI
	menu_theme = std::make_shared<tgui::Theme>("Data/gui/mainMenuButton.txt");

	main_layout = std::make_shared<tgui::VerticalLayout>();
	main_layout->setSize(0.4 * tgui::bindWidth(gui), 0.6 * tgui::bindHeight(gui));
	main_layout->setPosition(0.3 * tgui::bindWidth(gui),0.4 * tgui::bindHeight(gui));
	gui.add(main_layout);
	tgui::Button::Ptr temp_button = menu_theme->load("MainMenu");
	temp_button->setFont(resources->font);
	temp_button->setTextSize(35);

	temp_button->setText(resources->GetSfTextLine("main_single_player"));
	temp_button->connect("pressed", [&]() { main_theme.stop(); engine->PushState(new GameplayState(engine));  });
	main_layout->add(temp_button,"Play");
	main_layout->addSpace(0.15);


	tgui::Button::Ptr button_options = tgui::Button::copy(temp_button);
	button_options->setText(resources->GetSfTextLine("main_settings"));
	button_options->disconnectAll("pressed");
	button_options->connect("pressed", [&]() { engine->PushState(new OptionsState(engine)); });
	main_layout->add(button_options,"Options");
	main_layout->addSpace(0.15);

	tgui::Button::Ptr button_credits = tgui::Button::copy(temp_button);
	button_credits->setText(resources->GetSfTextLine("main_credits"));
	button_credits->disconnectAll("pressed");
	button_credits->connect("pressed", [&]() { engine->PushState(new CreditsState(engine));  });
	main_layout->add(button_credits,"Credits");
	main_layout->addSpace(0.15);

	tgui::Button::Ptr button_exit = tgui::Button::copy(temp_button);
	button_exit->setText(resources->GetSfTextLine("main_exit"));
	button_exit->disconnectAll("pressed");
	button_exit->connect("pressed", [&]() { engine->window.close();});
	main_layout->add(button_exit,"Exit");
	main_layout->addSpace(0.15);

	logo_sprite.setTexture(*resources->GetTexture("logo", TextureType::GUI));
	logo_sprite.setPosition(game->window.getSize().x/2-103, game->window.getSize().y/14 );

	background.setTexture(*resources->GetTexture("background", TextureType::GUI));
	backgroundpos = sf::Vector2f(0, 0);
	background.setPosition(backgroundpos);

	//To make the mouse a colliding object
	OrientedBoundingBox mouse_box(sf::Vector2f(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y));

	if (main_theme.openFromFile("Data/sound/mainmenu_theme_demo.ogg"))
	{
		main_theme.play();
		main_theme.setVolume(engine->options.volumeMusic);
		main_theme.setLoop(true);
	}
}

MainMenuState::~MainMenuState()
{

}

void MainMenuState::Update(float time_step)
{
	static int timer = fpscounter.GetTime() + 80;
	static int counter = 0;

	if(timer < fpscounter.GetTime())
	{
		if(counter < 7790)
			counter++;

		if(counter >= 7790)
		{
			counter = 0;
			backgroundpos = sf::Vector2f(0, 0);
		}

		backgroundpos.x -= 1;
		//backgroundpos.y -= 1;
		background.setPosition(backgroundpos);
	}
	for (int i = 0; i<4 ; i++)
	{
		mouse_box.Points[i].x = sf::Mouse::getPosition(engine->window).x;
		mouse_box.Points[i].y = sf::Mouse::getPosition(engine->window).y;
	}
	for(int j = 0; j < buttons.size(); j++)
	{
		if(Collision::BoundingBoxTest(buttons[j]->sprite,mouse_box))
		{
			if(Collision::PixelPerfectTest(buttons[j]->sprite, sf::Vector2f(sf::Mouse::getPosition(engine->window).x,sf::Mouse::getPosition(engine->window).y)))
			{
				buttons[j]->OnHover();
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if(!buttons[j]->clicked)
					{
						buttons[j]->OnClick();
						buttons[j]->clicked = true;
					}
				}
				else
					buttons[j]->clicked = false;
			}
			else
				buttons[j]->OnHoverExit();
		}
		else
			buttons[j]->OnHoverExit();
	}

}

void MainMenuState::HandleEvents(sf::Event& event)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		engine->PushState(new GameplayState(engine));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		engine->PushState(new OptionsState(engine));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		engine->PushState(new CreditsState(engine));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		engine->window.close();

	gui.handleEvent(event);
}

void MainMenuState::Render()
{
	sf::RenderTarget* target;

	target = &engine->window;
	target->draw(background);
	target->draw(logo_sprite);
	gui.draw();
	for(int j = 0; j < buttons.size(); j++)
	{
		buttons[j]->Render(*target);
	}
}

