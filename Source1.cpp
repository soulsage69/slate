#include <SFML\Graphics.hpp>
#include <iostream>
#include <SFML\System\Time.hpp>

using namespace sf;

const int WIN_HEIGHT = 800;
const int WIN_LENGTH = 1300;
sf::RenderWindow langas(sf::VideoMode(WIN_LENGTH, WIN_HEIGHT), "Slate", sf::Style::Close);
int kuris(1);
int nr1(1);
int mvnr(0);


struct stats {
    float hp;
    float hpr;
    float energy;
    float energyr;

}player, enemy1, enemy2, enemy3, boss;

struct position {
    float x;
    float y;
}tarahp, enemy1p, enemy2p, enemy3p, bossp;

bool ison(Vector2i pozicija, float x1, float x2, float y1, float y2) {
    
    if (pozicija.x>=x1 && pozicija.x<=x2) {
        if (pozicija.y >= y1 && pozicija.y <= y2) {
            return true;
        }
    }
    return false;
}

float countDamage(int end) {
    float ats;
    ats = rand()%end;
    return ats;
}


void stage1() {
    langas.setFramerateLimit(60);
    //langas.clear();
    bool isdone(false);
    int temp(0);
    int framecount(0), alpha(0), tarahs(0);
    int enemynr(0);
    int laikas(0);
    bool vyksta(0);

    Text ataka, pasigydyti, praleisti;
    Font font;
    font.loadFromFile("Resources/font.ttf");
    ataka.setString("attack");
    pasigydyti.setString("heal");
    praleisti.setString("parry");
    praleisti.setFont(font);
    ataka.setFont(font);
    pasigydyti.setFont(font);
    praleisti.setCharacterSize(30);
    ataka.setCharacterSize(30);
    pasigydyti.setCharacterSize(30);
    praleisti.setFillColor(Color::White);
    ataka.setFillColor(Color::White);
    pasigydyti.setFillColor(Color::White);
    praleisti.setPosition(300, 100);
    ataka.setPosition(300, 200);
    pasigydyti.setPosition(300, 300);

    Texture tarahBar;
    tarahBar.loadFromFile("Resources/healthbar.png");
    Sprite tb(tarahBar);
    Texture hlth, enrg;
    hlth.loadFromFile("Resources/health.png");
    enrg.loadFromFile("Resources/energy.png");
    Sprite health(hlth), energy(enrg);
    health.setPosition(30, 640);
    energy.setPosition(30, 730);
    tb.setColor(Color(255, 255, 255, 0));
    health.setColor(Color(255, 255, 255, 0));
    energy.setColor(Color(255, 255, 255, 0));

    Texture taraht, tarahta, tarahth;
    taraht.loadFromFile("Resources/stand.png");
    tarahta.loadFromFile("Resources/fight.png");
    tarahth.loadFromFile("Resources/hurt.png");
    Sprite tarah(taraht), tarahsa(tarahta), tarahsh(tarahth);
    tarah.setColor(Color(255, 255, 255, 0));
    tarah.setPosition(tarahp.x=100, tarahp.y=20);
    tarahsa.setPosition(tarahp.x, tarahp.y);
    tarahsh.setPosition(tarahp.x, tarahp.y);
    tarah.scale(0.2, 0.2);
    tarahsa.scale(0.2, 0.2);
    tarahsh.scale(0.2, 0.2);
    player.hp = 200;
    player.hpr = 200;
    player.energy = 200;
    player.energyr = 200;

    Texture enemyonet, enemyoneta, enemyoneth;
    enemyonet.loadFromFile("Resources/mob1,1.png");
    enemyoneta.loadFromFile("Resources/mob1,2.png");
    enemyoneth.loadFromFile("Resources/mob1,3.png");
    Sprite enemyones(enemyonet), enemyonea(enemyoneta), enemyoneh(enemyoneth);
    enemyones.setPosition(enemy1p.x = 800, enemy1p.y = 30);
    enemyonea.setPosition(enemy1p.x, enemy1p.y);
    enemyoneh.setPosition(enemy1p.x, enemy1p.y);
    enemyones.scale(0.25, 0.25);
    enemyonea.scale(0.25, 0.25);
    enemyoneh.scale(0.25, 0.25);
    enemy1.hp=100;
    enemy1.hpr=100;

    while (langas.isOpen()) {
        framecount++;
        Event e;
        while (langas.pollEvent(e))
        {
            if (e.type == Event::Closed)
                langas.close();
        }
        if (framecount==10 && alpha<240 && isdone==false) {
            framecount=0;
            alpha+=20;
            tarah.setColor(Color(255, 255, 255, alpha));
            tb.setColor(Color(255, 255, 255, alpha));
            health.setColor(Color(255, 255, 255, alpha));
            energy.setColor(Color(255, 255, 255, alpha));
            enemyones.setColor(Color(255, 255, 255, alpha));
            ataka.setFillColor(Color(255, 255, 255, alpha));
            pasigydyti.setFillColor(Color(255, 255, 255, alpha));
            praleisti.setFillColor(Color(255, 255, 255, alpha));
            langas.clear();
        }
        if (alpha == 240) {
            alpha = 255;
            enemynr++;
            langas.clear();
        }
        langas.clear();
        switch (enemynr) {
        case 0:
            break;
        case 1:
            enemyone(enemyones, enemyoneh, enemyonea, praleisti, pasigydyti, ataka, laikas, vyksta, tarah, tarahsa, tarahsh);
        }
        if (!vyksta)
        langas.draw(tarah);

        langas.draw(tb);
        langas.draw(health);
        langas.draw(energy);
        langas.display();
        
        std::cout << "tarah hp: " << player.hp<<std::endl;
        std::cout << "tarah enrg: " << player.energy<<std::endl;
        std::cout << "enemy hp: " << enemy1.hp<<std::endl;
        std::system("CLS");
    }
}

void game() {
    langas.setFramerateLimit(480);
    float judejimas(0);
    float temp(0);
    Clock laikas;
    Time trukme, periodas = seconds(2);
    Texture playerchart;
    playerchart.loadFromFile("Resources/stand.png");
    Sprite pc(playerchart);
    pc.setPosition(650, 1);
    pc.scale(0.25, 0.25);
    pc.setColor(sf::Color(255, 255, 255, 0));
    while (langas.isOpen()&&kuris==2) {
        
        Event e;
        judejimas++;
        
        while (langas.pollEvent(e))
        {
            if (e.type == Event::Closed)
                langas.close();
        }

        if (judejimas < 3000) {
            laikas.restart();
            pc.setPosition(650-(judejimas/10), 1);
            if (judejimas<1000) {
                pc.setColor(sf::Color(255, 255, 255, 0+((255*judejimas)/1000)));
            }
            while (trukme <= periodas) {
            trukme = laikas.getElapsedTime();

            }
            
        }
        bool anima1(true);
        if (judejimas > 2500&&anima1==true) {
            //laikas.restart();
            //periodas = seconds(4);
            //anima1 = false;
        }
        if (judejimas > 1500&&judejimas<4000) {
            //trukme = laikas.getElapsedTime();
            temp+=255.f/2500.f;
        }
        Vector2f temp2 = pc.getPosition();
        if (judejimas<4000&& judejimas>1500) {
            pc.setColor(sf::Color(255, 255, 255, 255 - temp));
            pc.setPosition(temp2.x - 0.2, 1);
        }
        if (judejimas > 6000) {
            break;
        }
        langas.draw(pc);
        langas.display();
        langas.clear();
    }
    stage1();
}

void meniu() {
    Texture Background, pavadinimas, playt, optionst, exitt, playtr, optionstr, exittr;
    Background.loadFromFile("Resources/bck3.png");
    pavadinimas.loadFromFile("Resources/slate_name.png");
    playt.loadFromFile("Resources/play.png");
    playtr.loadFromFile("Resources/playr.png");
    optionst.loadFromFile("Resources/options.png");
    optionstr.loadFromFile("Resources/optionsr.png");
    exitt.loadFromFile("Resources/exit.png");
    exittr.loadFromFile("Resources/exitr.png");
    Sprite Bckg(Background);
    Sprite pav(pavadinimas);
    Sprite play(playt);
    Sprite playr(playtr);
    Sprite options(optionst);
    Sprite optionsr(optionstr);
    Sprite exit(exitt);
    Sprite exitr(exittr);
    pav.setPosition(245, 100);
    play.setPosition(100, 550);
    play.scale(0.5, 0.5);
    options.setPosition(445, 550);
    options.scale(0.5, 0.5);
    exit.setPosition(950, 550);
    exit.scale(0.5, 0.5);

    playr.setPosition(100, 550);
    playr.scale(0.5, 0.5);
    optionsr.setPosition(445, 550);
    optionsr.scale(0.5, 0.5);
    exitr.setPosition(950, 550);
    exitr.scale(0.5, 0.5);
    //Bckg.setPosition(100, 0);

    while (langas.isOpen()&&kuris==1)
    {
        Event e;
        while (langas.pollEvent(e))
        {
            if (e.type == Event::Closed)
                langas.close();
        }
        langas.draw(Bckg);

        Vector2i pozicija = Mouse::getPosition(langas);
        if (ison(pozicija, 100, 100 + (200), 550, 550 + (275 / 2)) == true) {
            langas.draw(playr);
            if (Mouse::isButtonPressed(Mouse::Left) && ison(pozicija, 100, 100 + (200), 550, 550 + (275 / 2)) == true) {
                kuris = 2;
                langas.clear(Color(1, 0, 0));
                return;
            }
        }
        else langas.draw(play);
        if (ison(pozicija, 445, 445 + (748 / 2), 550, 550 + (275 / 2)) == true) {
            langas.draw(optionsr);
            
        }
        else langas.draw(options);
        if (ison(pozicija, 950, 950 + (415 / 2), 550, 550 + (275 / 2))) { 
            langas.draw(exitr); 
            if (Mouse::isButtonPressed(Mouse::Left) && ison(pozicija, 950, 950 + (415 / 2), 550, 550 + (275 / 2))) {
                kuris = 4;
                langas.clear(Color(1, 0, 0));
                return;
            }
        }
        else langas.draw(exit);
        langas.draw(pav);
        langas.display();
    }
}

int main() {
    switch (kuris)
    {
    case 1:
        meniu();
        break;
    case 2:
        game();
        break;
    case 4:
        return 0;
    default:
        return 0;
    }
    
    main();
}