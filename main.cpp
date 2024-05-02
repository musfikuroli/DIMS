#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <bits/stdc++.h>
using namespace std;



#define MAX_SIZE 1000
SDL_Color textColor = {0xFF, 0xFF,0xFF};

string header;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
/* Structure to Hold the Informations of a Single Drug */
struct Drug
{
    char Name[MAX_SIZE];
    char Group[MAX_SIZE];
    char Indications[MAX_SIZE];
    char Dose[MAX_SIZE];
    char Price[MAX_SIZE];
};
string menu;


//void clear();
class LTexture
{
public:
    LTexture();

    ~LTexture();

    bool loadFromFile( std::string path );

        #if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
        #endif

    void free();

    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    void setBlendMode( SDL_BlendMode blending );

    void setAlpha( Uint8 alpha );

    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};


LTexture menuTexture;

SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile( std::string path )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }


    //Return success
    return mTexture != NULL;
}
#endif

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

LTexture header_text_input_texture;
LTexture header_text_input_texture0;
LTexture header_text_input_texture1;
LTexture header_text_input_texture2;
LTexture header_text_input_texture3;
LTexture header_text_input_texture4;

LTexture header_text_input_texture10;
LTexture header_text_input_texture11;
LTexture header_text_input_texture12;
LTexture header_text_input_texture13;
LTexture header_text_input_texture14;




SDL_Texture* loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}




void HeaderInputFromUser(int a){


  SDL_Rect  headerRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  bool quit_this = false;
  SDL_Event e1;
  SDL_Color textColor ={0xFF,0xFF,0xFF};
  SDL_Texture* tempTexture = loadTexture("background.png");
  header_text_input_texture.loadFromRenderedText( " ", textColor );

  std::string inputText = " ";
  inputText.pop_back();
         if(a==1) header_text_input_texture1.loadFromRenderedText( "Enter Medicine Name", textColor );
    else if(a==2) header_text_input_texture1.loadFromRenderedText( "ENter Medicine Group", textColor );
    else if(a==3) header_text_input_texture1.loadFromRenderedText( "ENter The Indications", textColor );
    else if(a==4) header_text_input_texture1.loadFromRenderedText( "Enter The Dose", textColor );
    else if(a==5) header_text_input_texture1.loadFromRenderedText( "Enter The Price", textColor );
    else if(a==6) header_text_input_texture1.loadFromRenderedText( "Enter Medicine Name to Search: ", textColor );
    else if(a==7) header_text_input_texture1.loadFromRenderedText( "Enter Medicine Group to Search: ", textColor );
    else if(a==8) header_text_input_texture1.loadFromRenderedText( "Enter Medicine Name to Delete: ", textColor );



  SDL_StartTextInput();

  while( !quit_this )
  {

    bool renderText = false;


    while( SDL_PollEvent( &e1 ) != 0 )
    {
        if(a==17)
            {




                    header_text_input_texture1.loadFromRenderedText( "Medicine Information saved to file successfully!", textColor );
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    SDL_RenderSetViewport(gRenderer, &headerRect);

                    SDL_RenderCopy(gRenderer, tempTexture, NULL, NULL);



                    header_text_input_texture1.render( 200,100 );

                     SDL_RenderPresent( gRenderer);
                    for(long long i=0;i<900000000;i++);
                        quit_this = true;

            }
        if(a==0)
            {




                    header_text_input_texture1.loadFromRenderedText( "No entry deleted", textColor );
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    SDL_RenderSetViewport(gRenderer, &headerRect);

                    SDL_RenderCopy(gRenderer, tempTexture, NULL, NULL);



                    header_text_input_texture1.render( 400,100 );

                     SDL_RenderPresent( gRenderer);
                    for(long long i=0;i<900000000;i++);
                        quit_this = true;

            }
            if(a>40)
            {




                    header_text_input_texture1.loadFromRenderedText( "Some entry deleted!", textColor );
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    SDL_RenderSetViewport(gRenderer, &headerRect);

                    SDL_RenderCopy(gRenderer, tempTexture, NULL, NULL);



                    header_text_input_texture1.render( 400,100 );

                     SDL_RenderPresent( gRenderer);
                    for(long long i=0;i<900000000;i++);
                        quit_this = true;

            }

        if(a==20)
            {




                    header_text_input_texture1.loadFromRenderedText( "Medicine Database is empty! Nothing to delete!", textColor );
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    SDL_RenderSetViewport(gRenderer, &headerRect);

                    SDL_RenderCopy(gRenderer, tempTexture, NULL, NULL);



                    header_text_input_texture1.render( 400,100 );

                     SDL_RenderPresent( gRenderer);
                    for(long long i=0;i<900000000;i++);
                        quit_this = true;

            }

        if(a==9)
            {




                    header_text_input_texture1.loadFromRenderedText( "No Such Medicine Found!", textColor );
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    SDL_RenderSetViewport(gRenderer, &headerRect);

                    SDL_RenderCopy(gRenderer, tempTexture, NULL, NULL);



                    header_text_input_texture1.render( 400,100 );

                     SDL_RenderPresent( gRenderer);
                    for(long long i=0;i<900000000;i++);
                        quit_this = true;

            }
      if(e1.type == SDL_QUIT)
      {
        quit_this = true;

      }

       if( e1.type == SDL_KEYDOWN )
      {
        if( e1.key.keysym.sym == SDLK_RETURN )
        {
            menu=inputText;

            //printf("%s\n",menu);
          quit_this = true;
        }

        if( e1.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
        {
                inputText.pop_back();
          renderText = true;
        }

        if(e1.type == SDL_QUIT)
        {

          quit_this = true;

        }

      }
      else if( e1.type == SDL_TEXTINPUT )
      {
        if( !( SDL_GetModState() & KMOD_CTRL && ( e1.text.text[ 0 ] == 'c' || e1.text.text[ 0 ] == 'C' || e1.text.text[ 0 ] == 'v' || e1.text.text[ 0 ] == 'V' ) ) )
        {
          inputText += e1.text.text;
          renderText = true;
        }
      }
    }


    if( renderText )
    {

      if( inputText != " " )
      {

        header_text_input_texture.loadFromRenderedText( inputText.c_str(), textColor );
      }

      else
      {

        header_text_input_texture.loadFromRenderedText( " ", textColor );
      }

    }



    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    SDL_RenderSetViewport(gRenderer, &headerRect);

    SDL_RenderCopy(gRenderer, tempTexture, NULL, NULL);

    header_text_input_texture.render( 300,300 );
    header_text_input_texture1.render( 200,200 );


    SDL_RenderPresent( gRenderer);
  }


  SDL_StopTextInput();
  SDL_RenderClear( gRenderer );
  header = "";
  header += inputText;
}




bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                if(TTF_Init()==-1){
                    printf("TTF Initialization erron\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load dot texture
    if( !menuTexture.loadFromFile( "dot.bmp" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }
    gFont = TTF_OpenFont("boy.ttf", 40);

    return success;
}

void close()
{
    //Free loaded images
    menuTexture.free();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}



/* current size of the medicine array */
int currentSize = 0;



/* Array to Hold All the Drugs Information */
Drug medicine[MAX_SIZE];

/* enumerator for different search types */
typedef enum { Name, Group } search_t;

/* Function Prototypes */
void addEntry();
void display(int index);
void displayAll();
void search(char key[], search_t type);
void removeEntry(char Name[]);
void strtolower(char str[]);
void readFromFile();
void saveToFile();


int main()
{
    readFromFile();
    char selection[100];
    int choice=0;
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;


            //Event handler
            SDL_Event e;
            
            
            SDL_Rect opt1 = {245, 404, 599, 97};
            SDL_Rect opt2 = {209, 295, 667, 97};
            SDL_Rect opt3 = {287, 77, 529, 97};
            SDL_Rect opt4 = {287, 186, 529, 97};
            SDL_Rect opt5 = {224, 507, 651, 97};
            //SDL_Rect opt6 = {50, 485, 490, 60};
            SDL_Rect opt7 = {441, 611, 194, 97};
            

            while( !quit )
            {
                SDL_RenderClear(gRenderer);

                menuTexture.render(0, 0);
                SDL_RenderPresent( gRenderer );
                /*puts("Drug Information Management System");
                puts("    1. Insert A New Entry");
                puts("    2. Display All Entry");
                puts("    3. Search by Name");
                puts("    4. Search by Group");
                puts("    5. Delete a Medicine Information (By Name)");
                puts("    6. Save Database");
                puts("    7. Exit");*/

                while( SDL_PollEvent( &e ) != 0){
                    if(e.type == SDL_QUIT){
                        exit(0);
                        quit = true;
					}
					
                    if( e.button.x > opt1.x && e.button.x < opt1.x + opt1.w && e.button.y > opt1.y && e.button.y < opt1.y + opt1.h ){
                        if(e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
                            choice = 1;
                    }
                    else if( e.button.x > opt2.x && e.button.x < opt2.x + opt2.w && e.button.y > opt2.y && e.button.y < opt2.y + opt2.h ){
                        if(e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
                            choice = 2;
                    }
                    else if( e.button.x > opt3.x && e.button.x < opt3.x + opt3.w && e.button.y > opt3.y && e.button.y < opt3.y + opt3.h ){
                        if(e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
                            choice = 3;
                    }
                    else if( e.button.x > opt4.x && e.button.x < opt4.x + opt4.w && e.button.y > opt4.y && e.button.y < opt4.y + opt4.h ){
                        if(e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
                            choice = 4;
                    }
                    else if( e.button.x > opt5.x && e.button.x < opt5.x + opt5.w && e.button.y > opt5.y && e.button.y < opt5.y + opt5.h ){
                        if(e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
                            choice = 5;
                    }
                    // else if( e.button.x > opt6.x && e.button.x < opt6.x + opt6.w && e.button.y > opt6.y && e.button.y < opt6.y + opt6.h ){
                    //     if(e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
                    //         choice = 6;
                    // }
                    else if( e.button.x > opt7.x && e.button.x < opt7.x + opt7.w && e.button.y > opt7.y && e.button.y < opt7.y + opt7.h ){
                        if(e.type == SDL_MOUSEBUTTONDOWN && e.key.repeat == 0)
                            choice = 7;
                    }
                    else choice = 0;
                }

                switch(choice)
                {
                    case 1:
                    addEntry();
                    saveToFile();
                    //clear();
                    break;
                    case 2:
                    displayAll();
                    //clear();
                    break;
                    case 3:
                    HeaderInputFromUser(6);
                    for(int i=0;i<strlen(menu.c_str());i++)selection[i]=menu.c_str()[i];
                        selection[strlen(menu.c_str())]=0;

                    search(selection, Name);
                    //clear();
                    break;
                    case 4:
                    HeaderInputFromUser(7);
                    for(int i=0;i<strlen(menu.c_str());i++)selection[i]=menu.c_str()[i];
                    selection[strlen(menu.c_str())]=0;
                    search(selection, Group);
                    //clear();
                    break;
                    case 5:
                    HeaderInputFromUser(8);
                    for(int i=0;i<strlen(menu.c_str());i++)selection[i]=menu.c_str()[i];
                    selection[strlen(menu.c_str())]=0;
                    removeEntry(selection);
                    //clear();
                    break;
                    case 6:
                    saveToFile();
                    //clear();
                    break;
                    case 7:
                    quit = true;
                    exit(0);
                    break;
                    default:
                    break;
                }
                choice = 0;
            }
        }
    }
    close();
    return 0;
}
// void clear()
// {
//     //system("PAUSE"); // press any key to continue..
//     //system("CLEAR"); // clear the screen ( Linux: clear )
// }


void addEntry()
{
    if(currentSize == MAX_SIZE)
    {
        puts("Error: memory is fuLL!");
        return;
    }

    Drug c;

     HeaderInputFromUser(1);

     for(int i=0;i<strlen(menu.c_str());i++)c.Name[i]=menu.c_str()[i];
        c.Name[strlen(menu.c_str())]=0;

    HeaderInputFromUser(2);

     for(int i=0;i<strlen(menu.c_str());i++)c.Group[i]=menu.c_str()[i];
        c.Group[strlen(menu.c_str())]=0;

     HeaderInputFromUser(3);

     for(int i=0;i<strlen(menu.c_str());i++)c.Indications[i]=menu.c_str()[i];
        c.Indications[strlen(menu.c_str())]=0;

    HeaderInputFromUser(4);

     for(int i=0;i<strlen(menu.c_str());i++)c.Dose[i]=menu.c_str()[i];
        c.Dose[strlen(menu.c_str())]=0;

    HeaderInputFromUser(5);

     for(int i=0;i<strlen(menu.c_str());i++)c.Price[i]=menu.c_str()[i];
        c.Price[strlen(menu.c_str())]=0;



    medicine[currentSize] = c;
    ++currentSize;

    printf("\nDrug Information Added\n");
}

void display(int index)
{
    if(index < 0 || index >= currentSize)
    {
        puts("Error: invalid index!");
        return;
    }


    Drug c = medicine[index];
    
    {


  SDL_Rect  headerRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  bool quit_this = false;
  SDL_Event e1;
  SDL_Color textColor ={0xFF,0xFF,0xFF};
  SDL_Texture* tempTexture = loadTexture("background.png");
  header_text_input_texture0.loadFromRenderedText( c.Name, textColor );
  header_text_input_texture1.loadFromRenderedText( c.Group, textColor );
  header_text_input_texture2.loadFromRenderedText( c.Indications, textColor );
  header_text_input_texture3.loadFromRenderedText( c.Dose, textColor );
  header_text_input_texture4.loadFromRenderedText( c.Price, textColor );
  header_text_input_texture10.loadFromRenderedText( "Name        :", textColor );
  header_text_input_texture11.loadFromRenderedText( "Group       :", textColor );
  header_text_input_texture12.loadFromRenderedText( "Indications :", textColor );
  header_text_input_texture13.loadFromRenderedText( "Dose        :", textColor );
  header_text_input_texture14.loadFromRenderedText( "Price       :", textColor );



  while( !quit_this )
  {




    while( SDL_PollEvent( &e1 ) != 0 )
    {
      if(e1.type == SDL_QUIT)
      {
        quit_this = true;

      }

       if( e1.type == SDL_KEYDOWN )
      {
        if( e1.key.keysym.sym == SDLK_RETURN )
        {

          quit_this = true;
        }
      }
      }
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( gRenderer );

    SDL_RenderSetViewport(gRenderer, &headerRect);

    SDL_RenderCopy(gRenderer, tempTexture, NULL, NULL);

    header_text_input_texture0.render( 250,200 );
    header_text_input_texture1.render( 250,250 );
    header_text_input_texture2.render( 250,300 );
    header_text_input_texture3.render( 250,350 );
    header_text_input_texture4.render( 250,400 );
    header_text_input_texture10.render( 20,200 );
    header_text_input_texture11.render( 20,250 );
    header_text_input_texture12.render( 20,300 );
    header_text_input_texture13.render( 20,350 );
    header_text_input_texture14.render( 20,400 );


    SDL_RenderPresent( gRenderer);
  }
  SDL_RenderClear( gRenderer );
}


    printf("Medicine Name : %s\n", c.Name);
    printf("Group         : %s\n", c.Group);
    printf("Indications   : %s\n", c.Indications);
    printf("Dose          : %s\n", c.Dose);
    printf("Unit Price    : %s\n", c.Price);
}

// Function for printing all the medicines information
void displayAll()
{
    if(currentSize == 0) {
        puts("Medicine Database is empty!");
        return;
    }
    int i;
    for(i=0; i<currentSize; i++) {
        display(i);
        puts(""); // extra new line
    }
}

// This function modifies the given string
void strtolower(char str[])
{
    int len = strlen(str);
    int i;
    for(i=0; i<len; i++)
    {
        str[i] = tolower(str[i]);
    }
}

void search(char key[], search_t type)
{
    int found = 0;
    int i;
    char content[100];

    strtolower(key);

    if(type == Name)
    {
        for(i=0; i<currentSize; i++)
        {

            strcpy(content, medicine[i].Name);
            strtolower(content);

            if(strcmp(content, key) == 0)
            {
                display(i);
                found = 1;
            }
        }
    }
    if(type == Group)
    {
        for(i=0; i<currentSize; i++)
        {

            strcpy(content, medicine[i].Group);
            strtolower(content);

            if(strcmp(content, key) == 0)
            {
                display(i);
                found = 1;
            }
        }
    }
    if(!found)
    {
        HeaderInputFromUser(9);
        puts("Not Such Medicine Found!");
    }
}

// Function to Delete an entry by Name
void removeEntry(char Name[])
{
    if(currentSize == 0) {
        HeaderInputFromUser(20);
        return;
    }


    int i, j;
    int count = 0;
    for(i=0; i<currentSize; i++) {
        if(strcmp(medicine[i].Name, Name) == 0) {
            for(j=i; j<currentSize-1; j++) {
                medicine[j] = medicine[j+1];
            }

            strcpy(medicine[j].Name, "");
            strcpy(medicine[j].Group, "");
            strcpy(medicine[j].Indications, "");
            strcpy(medicine[j].Dose, "");
            strcpy(medicine[j].Price, "");

            currentSize -= 1;
            ++count;
        }
    }
    if(count == 0) {
        HeaderInputFromUser(0);
        puts("No entry deleted");
    }
    else {

        printf("%d entries deleted\n", count);
        count+=40;
        HeaderInputFromUser(count);
    }
}


void readFromFile()
{
    FILE *fp;
    if((fp = fopen("medicine.db", "rb")) == NULL) {
        puts("Error: can't load the database file");
        return;
    }


    /* read the size of the medicine database */
    if(fread(&currentSize, sizeof(currentSize), 1, fp) != 1) {
         puts("Error: can't read data!");
         return;
    }

    /* read the actual medicine content */
    if(fread(medicine, sizeof(medicine), 1, fp) != 1) {
        puts("Error: can't read data!");
        return;
    }

}


void saveToFile()
{
    FILE *fp;
    if( (fp = fopen("medicine.db", "wb")) == NULL ) {
        puts("Error: can't create a database file!");
        return;
    }

    /* Save the current size of the medicine database */
    if (fwrite(&currentSize, sizeof(currentSize), 1, fp) != 1 ) {
        puts("Error: can't save data!");
        return;
    }

    /* save the medicine contents */
    if(fwrite(medicine, sizeof(medicine), 1, fp) != 1) {
        puts("Error: can't save data!");
        return;
    }
    HeaderInputFromUser(17);
    puts("Medicine Information saved to file successfully!");
}
