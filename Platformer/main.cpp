#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include<limits.h>

#include<algorithm>
#include<string.h>
#include<sstream>
#include<queue>
#include <fstream>
#include<bits/stdc++.h>
using namespace std;

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;

SDL_Event event;
bool quit = false;
int mouse_x;
int mouse_y;
const int tick_count=32;
const double grav=-0.1;
const double szegeny_konstans=200;
const double lov_konstans=-5000;

string ITS(int a){
stringstream ss;
ss<<a;
return ss.str();
}


class LTexture
{
public:
    LTexture();
    ~LTexture();

    bool loadFromFile( std::string path );
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    void free();

    void render( int x, int y, double angle = 0.0 , double width=1, double height=1, SDL_Rect* clip =NULL, SDL_Point* center=NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    void renderText(std::string text);
   // void renderTitle( std::string text );
    //void renderBackground();
    void setAlpha( Uint8 alpha );


    int getWidth();
    int getHeight();

    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};


bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TTF_Font *gFont = NULL;

LTexture gTextTexture;
//vector<LTexture>


LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}


void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

bool LTexture::loadFromFile( std::string path )
{
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }

    mTexture = newTexture;
    return mTexture != NULL;
}



bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface( textSurface );
    }
    return mTexture != NULL;
}

void LTexture::free()
{
    if( mTexture != NULL )
    {
        //SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render( int x, int y, double angle, double width, double height, SDL_Rect* clip, SDL_Point* center, SDL_RendererFlip flip )
{



    int newX,newY;
    SDL_Rect renderQuad;
    newX = x + SCREEN_WIDTH/2;//+960;
    newY = y + SCREEN_HEIGHT/2;//+540;
    renderQuad = { newX-(mWidth*width)/2, newY-(mHeight*height)/2, mWidth*width, mHeight*height};

    //Set clip rendering dimensions
    /*
    if( clip != NULL )
    {
    	renderQuad.w = clip->w;
    	renderQuad.h = clip->h;
    }
    */

    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

void LTexture::renderText( std::string text )
{
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    if( !gTextTexture.loadFromRenderedText( text, textColor ) )
    {
        printf( "Failed to render text texture!\n" );
    }
    SDL_Rect renderQuad = { 50, 500, mWidth, mHeight };
    SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
}



int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}



void SetMonitorspecs()
{
    SDL_DisplayMode current;


    int should_be_zero = SDL_GetCurrentDisplayMode(0, &current);

    if(should_be_zero != 0)
    {

        printf("Could not get display mode for video display ", SDL_GetError());

    }
    else
    {
        SCREEN_WIDTH = current.w;
        SCREEN_HEIGHT = current.h;
    }

}


bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        gWindow = SDL_CreateWindow( "SDL_Main", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }

                SetMonitorspecs();
            }
        }
    }
    //SDL_WM_SetCaption( "Button Test", NULL );
    loadMedia();
    return success;
}



vector<LTexture > textures;
vector<bool> isAnim;
vector<vector<SDL_Rect> > frames;

template <typename T>
class Actor{
    public:
T* father;
LTexture* texture;
double tick=0;
bool Anim;
vector<SDL_Rect> frame;
double width=1;
double height=1;
SDL_Point center;
SDL_RendererFlip flip = SDL_FLIP_NONE;
double Time=0;


void Transform(double width,double height){
center.x*=width/this->width;
center.y*=height/this->height;
this->width=width;
this->height=height;
}

Actor(T* father=NULL,int TextureId=0){
    this->father=father;
    texture=&(textures[TextureId]);
    Anim=isAnim[TextureId];
    if(Anim){
        frame=frames[TextureId];
        Time=(double)frames.size()/(double)tick_count;
    }
    center={texture->mWidth/2,texture->mHeight/2};
}

void renderActor(double x, double y, double deg){

    if(Anim){
         //   cout<<tick<<" "<<Time<<" "<<frame.size()<<" "<<(int)floor(tick/Time*frame.size())<<endl;
        texture->render(x,y,deg,width,height,&frame[(int)floor(tick/Time*frame.size())],&center);
        tick+=1.0/(double)tick_count;
        while(tick>=Time)tick-=Time;
    }else{
        texture->render(x,y,deg,width,height,NULL,&center);
    }

}


};





bool loadMedia()//!////////////////////////////////////////////////////////////////////
{
    bool success = true;
    //loadfromfile

    ifstream fin("TextureTable.txt");
    int Max;
    fin>>Max;
    textures.resize(Max,LTexture());
    isAnim.resize(Max);
    frames.resize(Max);
    int a;string b;int c,d,e,f;
    while(fin.good()){
        fin>>a>>b;
        if(!textures[a].loadFromFile(b)){
            cout<< "Failed to load texture "<<a<<" from "<<b<<endl;
        };
        while(fin>>c && c!=-1){
            isAnim[a]=true;
            fin>>d>>e>>f;
            SDL_Rect ne;
            ne.x=c;
            ne.y=d;
            ne.w=e;
            ne.h=f;
            frames[a].push_back(ne);
        }
    }


    gFont = TTF_OpenFont( "Fonts/airstrike.ttf", 16 );
    return success;
}





class Point{
double x,y;
};

class Line{
Point a,b;
};



class Poligon{
vector<Point> Points;
vector<Line> Lines;
};



/*friction collision gravity*/
template <typename T>
class Entity{
public:
T* father;
double x,y,xs,ys,xa=0,ya=0,deg=0,friction=1,gravity=0;
Poligon Hitbox;
Actor<Entity> Entity_actor;
Entity(T* father=NULL,int texture=0,double x=0, double y=0, double deg=0,double xs=0, double ys=0,double xa=0, double ya=0 ){
this->father=father;
this->x=x;
this->y=y;
this->xs=xs;
this->ys=ys;
this->xa=xa;
this->ya=ya;
Actor<Entity> Entity_actor(this,texture) ;
this->Entity_actor=Entity_actor;
};
void step(){
ya+=gravity;

xs+=xa/tick_count;
ys+=ya/tick_count;
x+=xs/tick_count;
y+=ys/tick_count;
if(friction!=1){
 xs/=pow(friction,1.0/(double)tick_count);
 ys/=pow(friction,1.0/(double)tick_count);
}
xa=0;
ya=0;
Entity_actor.renderActor(x,y,deg);
}

void impulse(double deg,double force){
xa+=tick_count*force*sin(deg/180*acos(-1));
ya+=tick_count*-force*sin((90-deg)/180*acos(-1));
}


};


void close()
{
    TTF_CloseFont( gFont );
    gFont = NULL;

    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

}









bool left_mouse_click=0;
bool right_mouse_click=0;




void Control(){
while( SDL_PollEvent( &event ))
                {//cout<<"a"<<endl;
                if( event.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                else
                if( event.type == SDL_MOUSEBUTTONDOWN )
                    {
                        if( event.button.button == SDL_BUTTON_LEFT )
                        {

                        }
                        if( event.button.button == SDL_BUTTON_RIGHT )
                        {

                        }
                    }

                    else
                     if( event.type == SDL_KEYDOWN )
                    {
                        switch( event.key.keysym.sym )
                        {
                        case SDLK_w:

                            break;
                        case SDLK_s:
                            break;
                        case SDLK_a:
                            break;
                        case SDLK_d:
                            break;
                        case SDLK_e:
                            break;
                        case SDLK_UP:
                            break;
                        case SDLK_DOWN:
                            break;
                        case SDLK_LEFT:
                            break;
                        case SDLK_RIGHT:
                            break;
                        case SDLK_l:
                            break;
                        default:
                            break;
                        }
                    }

                }//}

                // renderelés kezdete
                SDL_GetMouseState( &mouse_x, &mouse_y );

}



class Player{
public:
Entity<Player> Player_entity;
Player(){
 Entity<Player> Player_entity(this,0,0,0);
Player_entity.friction=3;
Player_entity.gravity=1000;
this->Player_entity=Player_entity;
}
void step(){
/**/
Player_entity.step();
}
};


int main(int argc, char *argv[])
{ ///std::iostream::sync_with_stdio(false);
 if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {


Player player;
int t0=0;
            //SDL_Event event;

            srand(time(NULL));
            /**/
            clock_t timer;











                timer=clock();

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );



                while(!quit){

                    timer=clock();

                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );
                    Control();
                    player.step();
                    if(t0==0){player.Player_entity.impulse(47,1000);cout<<"BUMM";}
                    SDL_RenderPresent( gRenderer );

                    timer=clock()-timer;

                    if((1.0/tick_count-timer/CLOCKS_PER_SEC)>0){
                        SDL_Delay((1.0/tick_count-timer/CLOCKS_PER_SEC)*1000);/*!...!*/
                    }
                t0++;
                };
                close();








    }
out:;
    cout << "Hello world!" << endl;
    return 0;
}








