#include "OptionsState.hpp"

OptionsState::OptionsState(GameEngine* game)
	: GameState(game)
{
	mainTheme = std::make_shared<tgui::Theme>("Data/gui/mainMenuButton.txt");
	layout = std::make_shared<tgui::VerticalLayout>();
	settingLayout = std::make_shared<tgui::VerticalLayout>();
	layout->setSize(0.3 * tgui::bindWidth(gui),0.8 * tgui::bindHeight(gui));
	layout->setPosition(0.2 * tgui::bindWidth(gui),0.1 * tgui::bindHeight(gui));
	settingLayout->setSize(0.3 * tgui::bindWidth(gui),0.8 * tgui::bindHeight(gui));
	settingLayout->setPosition(0.51 * tgui::bindWidth(gui),0.1 * tgui::bindHeight(gui));


	buttonExit = mainTheme->load("MainMenu");
	buttonExit->setText("Exit");
	gui.add(buttonExit,"buttonExit");
	buttonExit->setPosition(0.1 * tgui::bindWidth(gui) -75,0.9 * tgui::bindHeight(gui));
	buttonExit->setSize(150,50);
	buttonExit->connect("pressed", [&] () {engine->PopState();});

	buttonSaveAndExit = tgui::Button::copy(buttonExit);
	buttonSaveAndExit->setText("Save and Exit");
	buttonSaveAndExit->setPosition(0.9 * tgui::bindWidth(gui) - 75,0.9 * tgui::bindHeight(gui));
	gui.add(buttonSaveAndExit,"buttonSaveAndExit");
	buttonSaveAndExit->connect("pressed", [&] () { SaveOptions(); });

	button1 = mainTheme->load("MainMenu");
	button1->setText("Fullscreen");
	layout->add(button1);
	layout->addSpace(0.25);

	button2 = tgui::Button::copy(button1);
	button2->setText("Resolution");
	layout->add(button2);
	layout->addSpace(0.25);

	button3 = tgui::Button::copy(button1);
	button3->setText("Multisampling");
	layout->add(button3);
	layout->addSpace(0.25);

	button4 = tgui::Button::copy(button1);
	button4->setText("Vsync");
	layout->add(button4);
	layout->addSpace(0.25);

	button5 = tgui::Button::copy(button1);
	button5->setText("Music");
	layout->add(button5);
	layout->addSpace(0.25);

	button6 = tgui::Button::copy(button1);
	button6->setText("Sounds");
	layout->add(button6);
	layout->addSpace(0.25);

	button7 = tgui::Button::copy(button1);
	button7->setText("Language");
	layout->add(button7);

	///Actual Buttons

	tgui::Button::Ptr buttonChangeFullscreen = tgui::Button::copy(button1);
	buttonChangeFullscreen->setText("Oh SHIT !");
	buttonChangeFullscreen->connect("pressed", [&]() { toggleFullscreen(); });
	settingLayout->add(buttonChangeFullscreen,"buttonChangeFullscreen");
	settingLayout->addSpace(0.25);


	tgui::Button::Ptr buttonChangeResolution = tgui::Button::copy(button1);
	buttonChangeResolution->setText("Oh SHIT !");
	buttonChangeResolution->connect("pressed", [&]() { changeResolution(); });
	settingLayout->add(buttonChangeResolution,"buttonChangeResolution");
	settingLayout->addSpace(0.25);

	tgui::Button::Ptr buttonChangeMultisampling = tgui::Button::copy(button1);
	buttonChangeMultisampling->setText("Oh SHIT !");
	buttonChangeMultisampling->connect("pressed", [&]() { changeMultisampling(); });
	settingLayout->add(buttonChangeMultisampling, "buttonChangeMultisampling" );
	settingLayout->addSpace(0.25);

	tgui::Button::Ptr buttonChangeVsync = tgui::Button::copy(button1);
	buttonChangeVsync->setText("Oh SHIT !");
	buttonChangeVsync->connect("pressed", [&]() { toggleVsync(); });
	settingLayout->add(buttonChangeVsync,"buttonChangeVsync" );
	settingLayout->addSpace(0.25);

	tgui::Slider::Ptr sliderMusic = mainTheme->load("Slider");
	sliderMusic->setMinimum(0);
	sliderMusic->setMaximum(100);
	sliderMusic->connect("ValueChanged", [&] () { changeMusic(); } );
	settingLayout->add(sliderMusic,"sliderMusic");
	settingLayout->addSpace(0.25);

	tgui::Slider::Ptr sliderSound = tgui::Slider::copy(sliderMusic);
	sliderSound->disconnectAll();
	sliderSound->connect("ValueChanged", [&] () { changeSound(); } );
	settingLayout->add(sliderSound,"sliderSound");
	settingLayout->addSpace(0.25);

	tgui::Button::Ptr buttonChangeLanguage = tgui::Button::copy(button1);
	buttonChangeLanguage->setText("Oh SHIT !");
	buttonChangeLanguage->connect("pressed", [&]() { changeLanguage(); });
	settingLayout->add(buttonChangeLanguage, "buttonChangeLanguage");


	background.setTexture( *resources->GetTexture("background", TextureType::GUI));
	backgroundpos = sf::Vector2f(0, 0);
	background.setPosition(backgroundpos);

	gui.add(layout);
	gui.add(settingLayout);

	initSettingsState();
}

OptionsState::~OptionsState()
{

}

void OptionsState::initSettingsState()
{
	tgui::Button::Ptr tempButton = gui.get<tgui::Button>("buttonChangeFullscreen",true);
	if(engine->options.fullscreen == 0)
		tempButton->setText("Off");
	else
		tempButton->setText("On");

	tempButton = gui.get<tgui::Button>("buttonChangeResolution",true);
	tempButton->setText(to_string(engine->options.resolution_x) + "x" + to_string(engine->options.resolution_y));

	tempButton = gui.get<tgui::Button>("buttonChangeMultisampling",true);
	tempButton->setText(to_string(engine->options.multisampling));

	tempButton = gui.get<tgui::Button>("buttonChangeVsync",true);
	if(engine->options.vsync == 0)
		tempButton->setText("Off");
	else
		tempButton->setText("On");

	tempButton = gui.get<tgui::Button>("buttonChangeLanguage",true);
	tempButton->setText(engine->options.language);

	gui.get<tgui::Slider>("sliderMusic",true)->setValue(engine->options.volumeMusic);
	gui.get<tgui::Slider>("sliderSound",true)->setValue(engine->options.volumeSound);
}

void OptionsState::Update(float time_step)
{
	///BACKGROUND
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

void OptionsState::toggleFullscreen()
{
	tgui::Button::Ptr tempButton = gui.get<tgui::Button>("buttonChangeFullscreen", true);
	if(engine->options.fullscreen == 0)
	{
		engine->options.fullscreen = 1;
		tempButton->setText("On");
	}
	else
	{
		engine->options.fullscreen = 0;
		tempButton->setText("Off");
	}

	engine->options.sets[13] = to_string(engine->options.fullscreen);
}

void OptionsState::changeMultisampling()
{
	tgui::Button::Ptr tempButton = gui.get<tgui::Button>("buttonChangeMultisampling", true);
	engine->options.multisampling*=2;
	if (engine->options.multisampling>8)
		engine->options.multisampling=2;
	engine->options.sets[15]=to_string(engine->options.multisampling);
	tempButton->setText(to_string(engine->options.multisampling));
}

void OptionsState::toggleVsync()
{
	tgui::Button::Ptr tempButton = gui.get<tgui::Button>("buttonChangeVsync", true);
	if(engine->options.vsync == 0)
	{
		engine->options.vsync = 1;
		tempButton->setText("On");
	}
	else
	{
		engine->options.vsync = 0;
		tempButton->setText("Off");
	}

	engine->options.sets[17] = to_string(engine->options.vsync);
}

void OptionsState::changeResolution()
{
	///Possible resolutions:
	/*
	1920x1080
	1600x900
	1366x768
	1280x1024
	1024x768
	800x600
	*/
	///******************///
	tgui::Button::Ptr tempButton = gui.get<tgui::Button>("buttonChangeResolution", true);
	if(engine->options.resolution_x==800)
	{
		engine->options.resolution_x=1024;
		engine->options.resolution_y=768;
	}
	else if(engine->options.resolution_x==1024)
	{
		engine->options.resolution_x=1280;
		engine->options.resolution_y=1024;
	}
	else if(engine->options.resolution_x==1280)
	{
		engine->options.resolution_x=1366;
		engine->options.resolution_y=768;
	}
	else if(engine->options.resolution_x==1366)
	{
		engine->options.resolution_x=1600;
		engine->options.resolution_y=900;
	}
	else if(engine->options.resolution_x==1600)
	{
		engine->options.resolution_x=1920;
		engine->options.resolution_y=1080;
	}
	else if(engine->options.resolution_x==1920)
	{
		engine->options.resolution_x=800;
		engine->options.resolution_y=600;
	}
	else
	{
		engine->options.resolution_x=800;
		engine->options.resolution_y=600;
	}

	engine->options.sets[10]=to_string(engine->options.resolution_x);
	engine->options.sets[11]=to_string(engine->options.resolution_y);
	tempButton->setText(to_string(engine->options.resolution_x) + "x" + to_string(engine->options.resolution_y));
}

void OptionsState::changeMusic()
{
	engine->options.volumeMusic=gui.get<tgui::Slider>("sliderMusic",true)->getValue();
	engine->options.sets[19]=to_string(engine->options.volumeMusic);
}

void OptionsState::changeSound()
{
	engine->options.volumeSound=gui.get<tgui::Slider>("sliderSound",true)->getValue();
	engine->options.sets[21]=to_string(engine->options.volumeSound);
}

void OptionsState::changeLanguage()
{
	tgui::Button::Ptr tempButton = gui.get<tgui::Button>("buttonChangeLanguage", true);
	if(engine->options.language=="PL")
		engine->options.language="EN";
	else if(engine->options.language=="EN")
		engine->options.language="RU";
	else if(engine->options.language=="RU")
		engine->options.language="PL";
	else
		engine->options.language="EN";

	tempButton->setText(engine->options.language);
	engine->options.sets[23]=engine->options.language;
}

void OptionsState::HandleEvents(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		engine->PopState();

	gui.handleEvent(event);
}

void OptionsState::Render()
{
	sf::RenderTarget* target;

	target = &engine->window;
	target->draw(background);
	gui.draw();
}

void OptionsState::SaveOptions()
{
	engine->options.SaveToFile();
	engine->restart = true;
	engine->Exit();
}
