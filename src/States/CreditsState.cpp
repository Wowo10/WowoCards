#include "CreditsState.hpp"

CreditsState::CreditsState(GameEngine* game)
	: GameState(game)
{
	mainTheme = std::make_shared<tgui::Theme>("Data/gui/mainMenuButton.txt");

	background.setTexture( *resources->GetTexture("img/background", TextureType::GUI));
	backgroundpos = sf::Vector2f(0, 0);
	background.setPosition(backgroundpos);

	creditsTextBox = mainTheme->load("TextBox");
	gui.add(creditsTextBox);


	creditsTextBox->setFont(resources->debugFont);
	creditsTextBox->setTextSize(28);
	creditsTextBox->setReadOnly();
	for (int i = 1 ; i<= CREDITSLINES ; i++)
	{
		creditsTextBox->addText(resources->GetSfTextLine("credits_" + to_string(i)) + "\n" );

	}
	creditsTextBox->setPosition(engine->window.getSize().x/2 -creditsTextBox->getFullSize().x/2, engine->window.getSize().y/2 - creditsTextBox->getFullSize().y/2);
	creditsTextBox->setSize(300,500);
}

CreditsState::~CreditsState()
{

}

void CreditsState::Update(float time_step)
{
	static int timer = fpscounter.GetTime() + 80;
	static int counter = 0;

	if(timer < fpscounter.GetTime())
	{
		if(counter < 660)
			counter++;

		if(counter >= 660)
		{
			counter = 0;
			backgroundpos = sf::Vector2f(0, 0);
		}

		backgroundpos.x -= 1;
		backgroundpos.y -= 1;
		background.setPosition(backgroundpos);
	}
}

void CreditsState::HandleEvents(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		engine->PopState();

	gui.handleEvent(event);
}

void CreditsState::Render()
{
	sf::RenderTarget* target;

	target = &engine->window;
	target->draw(background);
	gui.draw();

}

