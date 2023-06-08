#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <iterator>
#include <dirent.h>
using namespace sf;
using namespace std;
int main()
{
    // Create the main window
    RenderWindow window(VideoMode(960, 960), "Michelle.exe",Style::Titlebar|Style::Close);

    // Load a sprite to display
    Texture texture;
    if (!texture.loadFromFile("Picture/SM.jpg"))
        return EXIT_FAILURE;
    Sprite sprite(texture);
    // Create a graphical text to display
    Font font;
    if (!font.loadFromFile("ChunkFive-Regular.otf"))
        return EXIT_FAILURE;
    Text text("Never give up!!!Add oil", font, 30);
    text.setFillColor(Color::Black);
    // Load a music to play
    Music music;
    vector<string> Pnames;
        struct dirent **Pnamelist;
         int n;
         n = scandir("Picture/", &Pnamelist, NULL, alphasort);
         if (n < 0)
              perror("scandir");
         else {
                while (n > 2){
                	char X[60];
                	strcpy(X,"Picture/");
       	            strcat(X,Pnamelist[n-1]->d_name);
       	            Pnames.push_back(X);
       	            delete Pnamelist[n-1];
                    n--;
                  }
                for(int i=1;i>-1;i--)
                    delete Pnamelist[i];
                delete Pnamelist;
              }
    vector<string> names;
    struct dirent **namelist;
     int n2;

     n2 = scandir("music/", &namelist, NULL, alphasort);
     if (n2 < 0)
          perror("scandir");
     else {
            while (n2 > 2){
            	char X[60];
            	strcpy(X,"music/");
   	            strcat(X,namelist[n2-1]->d_name);
   	            names.push_back(X);
   	            delete namelist[n2-1];
                n2--;
              }
            for(int i=1;i>-1;i--)
              delete namelist[i];
            delete namelist;
          }
    if (!music.openFromFile(names[0]))
      return EXIT_FAILURE;
    Event event;
    // Play the music
    music.play();
    int count=0;
    int countP = 0;
    Clock c;
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed)
                window.close();

        }
        if(event.type == Event::EventType::KeyPressed){
           if(event.key.code == Keyboard::Key::Down)
        	  music.setVolume(music.getVolume()-10);
           if(event.key.code == Keyboard::Key::Up)
        	 music.setVolume(music.getVolume()+10);
           if(event.key.code == Keyboard::Key::Right){
        	  Time P = music.getPlayingOffset()+seconds(5);
        	  music.setPlayingOffset(Time(P));
            }
           if(event.key.code == Keyboard::Key::Left){
             Time P = music.getPlayingOffset()-seconds(5);
             if(P.asSeconds()<=0.0f)
            	P = seconds(0);
             music.setPlayingOffset(Time(P));
             }
          }
           int T = c.getElapsedTime().asMilliseconds();
            if(T%10000==0){
        	   countP++;
        	   texture.loadFromFile(Pnames[countP%Pnames.size()]);
        	   Sprite sprite(texture);
           }
        if(music.getStatus() == Music::Status::Stopped){
           count++;
           music.openFromFile(names[count%names.size()]);
           music.play();
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);
        // Draw the string
        window.draw(text);
        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
