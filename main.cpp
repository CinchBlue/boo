#include "common.h"

//Dang MinGW is making me roll my own to_string()
template <class T>
std::string to_str(T t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

//Timer wrapper
class Timer
{
public:
	float get()
	{
		//Get difference
		sf::Time temp = c.getElapsedTime() - t;
		return temp.asSeconds();
	}
	void restart()
	{
		//Restart, set start time.
		c.restart();
		t = c.getElapsedTime();
	}
	
private:
	sf::Time t;
	sf::Clock c;
};

//Input wrapper
class Input
{
public:
	char c;
	
};

//Class to pulling out a random character
class NumberGen
{
public:
	NumberGen()
	{
		std::srand(std::time(0));
	}
	char get()
	{
		ss.str(std::string());
		//Generates a random printable character
		ss << static_cast<char>((rand() % 93) + 33);
		return ss.str()[0];
	}
	
private:
	std::stringstream ss;
	std::string str;
};

int main()
{
	//Init helper classes
	NumberGen ngen;
	Input input;
	Timer timer;
	
	//Setup window
	sf::RenderWindow window(sf::VideoMode(800, 600, 32),
							"SFML Test");
					
	
	//Load font
	sf::Font font;
	if(!font.loadFromFile("coolvetica.ttf"))
	{
		std::cout << "ERROR: Could not load coolvertica.ttf" << std::endl;
		return 1;
	}
	
	//Create string with random number, convert using string streams
	sf::String str(ngen.get());
	
	//Set text
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(40);
	text.setPosition(170.f, 150.f);
	text.setColor(sf::Color::Black);
	text.setString(str);
	
	//Set timer text
	sf::Text time_text = text;
	time_text.setPosition(0.f, 0.f);
	std::string time_str;
	
	//Load sounds
	sf::Music music;
	if(!music.openFromFile("frenzy.ogg"))
	{
		std::cout << "ERROR: Could not load frenzy.ogg" << std::endl;
		return 2;
	}
	
	//Play the music, start the timer
	music.play();
	timer.restart();

	//Begin loop
	while(window.isOpen())
	{
		//Event handling
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch (event.type)
			{
				//Close
				case (sf::Event::Closed):
					window.close();
				//Generate new letter if still not frozen.
				case (sf::Event::MouseButtonReleased):
						if (event.mouseButton.button == sf::Mouse::Left)
						{
							str = ngen.get();
							std::cout << ngen.get();
							text.setString(str);
						}
				//Get character input
				case (sf::Event::TextEntered):
					if (event.text.unicode > 32 && event.text.unicode < 127)
					{
						input.c = static_cast<char>(event.text.unicode);
						std::cout << input.c << "\n";
					}
						
				default:
					break;
			}
		}
			//Check time to see if lose
			if(timer.get() > 5.0f)
			{
				window.close();
				break;
			}
		
			//Check to see if right character; if so, reset timer, continue.
			if (input.c == str)
			{
				std::cout << "Yes!" << std::endl;
				str = ngen.get();
				text.setString(str);
				music.stop();
				music.play();
				timer.restart();
			}
			
			//Set time_text
			time_str = to_str(timer.get());
			time_text.setString(time_str);
			
			
			window.clear(sf::Color::White);
			window.draw(text);
			window.draw(time_text);
		
			window.display();
	}
	
	std::cout << "You lose!" << std::endl;
	
	return 0;
}