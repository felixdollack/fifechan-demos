/**
 * \example sdlwidgets.cpp SDL widgets example for Guichan.
 */

// Include all necessary headers.
#include <iostream>
#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <SDL/SDL.h>

/*
 * Common stuff we need
 */
bool running = true;

/*
 * SDL Stuff we need
 */
SDL_Surface* screen;
SDL_Event event;

/*
 * Guichan SDL stuff we need
 */
gcn::SDLInput* input;             // Input driver
gcn::SDLGraphics* graphics;       // Graphics driver
gcn::SDLImageLoader* imageLoader; // For loading images

/*
 * Guichan stuff we need
 */
gcn::Gui* gui;            // A Gui object - binds it all together
gcn::ImageFont* font;     // A font

/*
 * All of the default widgets
 */
gcn::Container* top;                 // A top container
gcn::Label* label;                   // A label
gcn::Icon* icon;                     // An icon (image)
gcn::Button* button;                 // A button
gcn::TextField* textField;           // One-line text field
gcn::TextBox* textBox;               // Multi-line text box
gcn::ScrollArea* textBoxScrollArea;  // Scroll area for the text box
gcn::ListBox* listBox;               // A list box
gcn::DropDown* dropDown;             // Drop down
gcn::CheckBox* checkBox1;            // Two checkboxes
gcn::CheckBox* checkBox2;
gcn::RadioButton* radioButton1;      // Three radio buttons
gcn::RadioButton* radioButton2;
gcn::RadioButton* radioButton3;

gcn::Image *image;                   // An image for the icon

/*
 * List boxes and dropdowns needs an instance of a listmodel
 * to know what elements they have.
 */
class DemoListModel : public gcn::ListModel
{
public:
	int getNumberOfElements()
	{
		return 5;
	}

	std::string getElementAt(int i)
	{
		switch(i)
		{
		  case 0:
			  return std::string("zero");
		  case 1:
			  return std::string("one");
		  case 2:
			  return std::string("two");
		  case 3:
			  return std::string("three");
		  case 4:
			  return std::string("four");
		  default: // Just to keep warnings away
			  return std::string("");
		}
	}
};

DemoListModel demoListModel;

void initWidgets()
{
	/*
	 * Create all the widgets
	 */
	label = new gcn::Label("Label");
	
	image = new gcn::Image("gui-chan.bmp");
	icon = new gcn::Icon(image);
	
	button = new gcn::Button("Button");
	
	textField = new gcn::TextField("Text field");
	
	textBox = new gcn::TextBox("Multiline\nText box");
	textBoxScrollArea = new gcn::ScrollArea(textBox);
	textBoxScrollArea->setWidth(200);
	textBoxScrollArea->setHeight(100);
	textBoxScrollArea->setBorderSize(1);
	
	listBox = new gcn::ListBox(&demoListModel);
	listBox->setBorderSize(1);
	
	dropDown = new gcn::DropDown(&demoListModel);

	checkBox1 = new gcn::CheckBox("Checkbox 1");
	checkBox2 = new gcn::CheckBox("Checkbox 2");
	
	radioButton1 = new gcn::RadioButton("RadioButton 1", "radiogroup", true);
	radioButton2 = new gcn::RadioButton("RadioButton 2", "radiogroup");
	radioButton3 = new gcn::RadioButton("RadioButton 3", "radiogroup");

	/*
	 * Add them to the top container
	 */
	top->add(label, 10, 10);
	top->add(icon, 10, 30);
	top->add(button, 200, 10);
	top->add(textField, 250, 10);
	top->add(textBoxScrollArea, 200, 50);
	top->add(listBox, 200, 200);
	top->add(dropDown, 500, 10);
	top->add(checkBox1, 500, 130);
	top->add(checkBox2, 500, 150);
	top->add(radioButton1, 500, 200);
	top->add(radioButton2, 500, 220);
	top->add(radioButton3, 500, 240);	
}

/**
 * Initializes the application
 */
void init()
{
	/* 
	 * Here we initialize SDL as we would do with any SDL application.
	 */
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
	// We want unicode
	SDL_EnableUNICODE(1);
	// We want to enable key repeat
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	/*
	 * Now it's time for Guichan SDL stuff
	 */
	imageLoader = new gcn::SDLImageLoader();
	// The ImageLoader in use is static and must be set to be
	// able to load images	
	gcn::Image::setImageLoader(imageLoader); 
	graphics = new gcn::SDLGraphics();
	// Set the target for the graphics object to be the screen.
	// In other words, we will draw to the screen.
	// Note, any surface will do, it doesn't have to be the screen.
	graphics->setTarget(screen);
	input = new gcn::SDLInput();
	
	/*
	 * Last but not least it's time to initialize and create the gui
	 * with Guichan stuff.
	 */
	top = new gcn::Container();    
	// Set the dimension of the top container to match the screen.
	top->setDimension(gcn::Rectangle(0, 0, 640, 480));
	gui = new gcn::Gui();
	// Set gui to use the SDLGraphics object.
	gui->setGraphics(graphics);
	// Set gui to use the SDLInput object
	gui->setInput(input);	
	// Set the top container
	gui->setTop(top);
	// Load the image font.
	font = new gcn::ImageFont("fixedfont.bmp", " abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	// The global font is static and must be set.
	gcn::Widget::setGlobalFont(font);

	initWidgets();
}

/**
 * Halts the application
 */
void halt()
{
	/*
	 * Destroy Guichan stuff
	 */
	delete font;
	delete gui;

	/*
	 * Widgets
	 */
	delete top;
	delete label;
	delete icon;
	delete button;
	delete textField;
	delete textBox;
	delete textBoxScrollArea;
	delete listBox;
	delete dropDown;
	delete checkBox1;
	delete checkBox2;
	delete radioButton1;
	delete radioButton2;
	delete radioButton3;
	
	/*
	 * Destroy Guichan SDL stuff
	 */
	delete input;
	delete graphics;
	delete imageLoader;
	
	/*
	 * Destroy SDL stuff
	 */
	SDL_Quit();
}

/**
 * Checks input. On escape halt the application.
 */
void checkInput()
{
	/*
	 * Poll SDL events
	 */
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{  
				running = false;
			}
			if (event.key.keysym.sym == SDLK_f)
			{
				if (event.key.keysym.mod & KMOD_CTRL)
				{
					// Works with X11 only
					SDL_WM_ToggleFullScreen(screen);
				}
			}
		}
		else if(event.type == SDL_QUIT)
		{
			running = false;
		}

		/*
		 * Now that we are done polling and using SDL events we pass
		 * the leftovers to the SDLInput object to later be handled by
		 * the Gui.
		 */
		input->pushInput(event);        		
	}
}

/**
 * Runs the application
 */
void run()
{
	while(running)
	{
		// Poll input
		checkInput();
		// Let the gui perform it's logic (like handle input)
		gui->logic();
		// Draw the gui
		gui->draw();
		// Update the screen
		SDL_Flip(screen);
	}		
}

int main(int argc, char **argv)
{	
	try
	{
 		init();
		run();
		halt();			
	}
	/*
	 * Catch all Guichan exceptions
	 */
	catch (gcn::Exception e)
	{
		std::cout << e.getMessage() << std::endl;
	}
	/*
	 * Catch all Std exceptions
	 */
	catch (std::exception e)
	{
		std::cout << "Std exception: " << e.what() << std::endl;  
	}
	/*
	 * Catch all Unknown exceptions
	 */
	catch (...)
	{
		std::cout << "Unknown exception" << std::endl;
	}

	return 0;
}
