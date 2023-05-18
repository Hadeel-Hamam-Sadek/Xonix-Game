#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;

const int M = 25;
const int N = 40;

int grid[M][N] = {0};
int ts = 18;
struct Enemy
{
    int x,y,dx,dy;

    Enemy()
    {
        x=y=300;
        dx=4-rand()%8;
        dy=4-rand()%8;
    }

    void move()
    {
        x+=dx;
        if (grid[y/ts][x/ts]==1)
        {
            dx=-dx;
            x+=dx;
        }
        y+=dy;
        if (grid[y/ts][x/ts]==1)
        {
            dy=-dy;
            y+=dy;
        }
    }
};

void drop(int y,int x)
{
    if (grid[y][x]==0)
        grid[y][x]=-1;
    if (grid[y-1][x]==0)
        drop(y-1,x);
    if (grid[y+1][x]==0)
        drop(y+1,x);
    if (grid[y][x-1]==0)
        drop(y,x-1);
    if (grid[y][x+1]==0)
        drop(y,x+1);
}

int main()
{
    srand(time(0));

    RenderWindow window(VideoMode(N*ts, M*ts), "Xonix");

    window.setFramerateLimit(60);

    Texture t1,t2,t3,l1,l2,l3,bg;
    t1.loadFromFile("images/tiles.png");
    t2.loadFromFile("images/gameover.png");
    t3.loadFromFile("images/ghost3.png");
    l1.loadFromFile("images/level1.png");
    l2.loadFromFile("images/level2.png");
    l3.loadFromFile("images/level3.png");
    bg.loadFromFile("images/wall2.jpg");
    //SoundBuffer aud;
    //aud.loadFromFile("sound/sound.mp3");

    //SoundBuffer aud;
    //aud.loadFromFile("sound/sound.mp3");
    /*SoundBuffer buffer;
    buffer.loadFromFile("sound/sound.wav");
    if (!buffer.loadFromFile("sound/sound.wav"))
        return 0;*/



    /*Music music;

    if (!music.openFromFile("sound/sound.mp3"))
        //std::cout << "cannot find music.mp3" << std::endl;
        return 0;*/



    //Sound sound(buffer);
    //sound.play();



    Sprite sTile(t1), sGameover(t2), sEnemy(t3),sBg(bg);
    sGameover.setPosition(100,50);
    sEnemy.setOrigin(20,20);

    int enemyCount = 1;
    Enemy a[10];

    bool Game=true;
    int x=0, y=0, dx=0, dy=0;
    float timer=0, delay=0.07;
    Clock clock;

    for (int i=0; i<M; i++)
        for (int j=0; j<N; j++)
            if (i==0 || j==0 || i==M-1 || j==N-1)
                grid[i][j]=1;


    Sprite spr_Button1;
    spr_Button1.setTexture( l1 );
    spr_Button1.setPosition( 180, 150 );
    spr_Button1.setScale( .5, .3 );

    Sprite spr_Button2;
    spr_Button2.setTexture( l2 );
    spr_Button2.setPosition( 180, 200 );
    spr_Button2.setScale( .5, .3 );

    Sprite spr_Button3;
    spr_Button3.setTexture( l3 );
    spr_Button3.setPosition( 180, 250 );
    spr_Button3.setScale( .5, .3 );

    Sprite spr_Button4;
    spr_Button4.setTexture( l1 );
    spr_Button4.setPosition( 180, 300 );
    spr_Button4.setScale( .5, .3 );




    bool start=false,again=false;

    while (window.isOpen())
    {

        //music.play();
        //Sound sound(buffer);
        //sound.play();
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::KeyPressed)
                if (e.key.code==Keyboard::Escape)
                {
                    for (int i=1; i<M-1; i++)
                        for (int j=1; j<N-1; j++)
                            grid[i][j]=0;

                    x=10;
                    y=0;
                    Game=true;
                }

        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            dx=-1;
            dy=0;
        };
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            dx=1;
            dy=0;
        };
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            dx=0;
            dy=-1;
        };
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            dx=0;
            dy=1;
        };

        if (!Game)
            continue;

        if (timer>delay)
        {
            x+=dx;
            y+=dy;

            if (x<0)
                x=0;
            if (x>N-1)
                x=N-1;
            if (y<0)
                y=0;
            if (y>M-1)
                y=M-1;

            if (grid[y][x]==2)
                Game=false;
            if (grid[y][x]==0)
                grid[y][x]=2;
            timer=0;
        }

        for (int i=0; i<enemyCount; i++) a[i].move();

        if (grid[y][x]==1)
        {
            dx=dy=0;

            for (int i=0; i<enemyCount; i++)
                drop(a[i].y/ts, a[i].x/ts);

            for (int i=0; i<M; i++)
                for (int j=0; j<N; j++)
                    if (grid[i][j]==-1)
                        grid[i][j]=0;
                    else
                        grid[i][j]=1;
        }

        for (int i=0; i<enemyCount; i++)
            if  (grid[a[i].y/ts][a[i].x/ts]==2)
                Game=false;

        if(start == false)
        {
            window.clear();
            window.draw(sBg);
            window.draw( spr_Button1 );
            window.draw( spr_Button2 );
            window.draw( spr_Button3 );
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)
                    && sf::Mouse::getPosition(window).x >= 180
                    && sf::Mouse::getPosition(window).y >=150
                    && sf::Mouse::getPosition(window).x <= 540
                    && sf::Mouse::getPosition(window).y <= 190
              )
            {
                enemyCount=2;
                start=true;
            }
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)
                    && sf::Mouse::getPosition(window).x >= 180
                    && sf::Mouse::getPosition(window).y >=200
                    && sf::Mouse::getPosition(window).x <= 540
                    && sf::Mouse::getPosition(window).y <= 240
              )
            {
                enemyCount=4;
                start=true;
            }
            if( sf::Mouse::isButtonPressed(sf::Mouse::Left)
                    && sf::Mouse::getPosition(window).x >= 180
                    && sf::Mouse::getPosition(window).y >=250
                    && sf::Mouse::getPosition(window).x <= 540
                    && sf::Mouse::getPosition(window).y <= 290
              )
            {
                enemyCount=6;
                start=true;
            }
        }


        if(start==true)
        {


            window.clear();
            window.draw(sBg);
            for (int i=0; i<M; i++)
                for (int j=0; j<N; j++)
                {
                    if (grid[i][j]==0)
                        continue;
                    if (grid[i][j]==1)
                        sTile.setTextureRect(IntRect( 0,0,ts,ts));
                    if (grid[i][j]==2)
                        sTile.setTextureRect(IntRect(54,0,ts,ts));
                    sTile.setPosition(j*ts,i*ts);
                    window.draw(sTile);
                }

            sTile.setTextureRect(IntRect(36,0,ts,ts));
            sTile.setPosition(x*ts,y*ts);
            window.draw(sTile);

            //sEnemy.rotate(10);
            for (int i=0; i<enemyCount; i++)
            {
                sEnemy.setPosition(a[i].x,a[i].y);
                window.draw(sEnemy);
            }

            if (Game == false)
            {
                //window.clear();
                window.draw(sGameover);

                //window.draw(spr_Button4);
//                std::cout << "taha" << std::endl;
//                start=false;
//                Game = true;
            }
        }



        window.display();
    }

    return 0;
}

