#include "raylib.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

std::string chaineEtape(const std::string& nom, int etape);

int main(void)
{
// Initialiser la fenêtre avec une taille fixe
const int windowWidth = 800; // Vous pouvez ajuster la taille selon vos besoins
const int windowHeight = 800; // Vous pouvez ajuster la taille selon vos besoins

// Tailles pour les carreaux
const int tileWidth = 128;
const int tileHeight = 128;

// Calculer le nombre de carreaux dans chaque dimension
int numTilesX = 11;
int numTilesY = 11;

// Calculer la taille réelle de la carte
int mapWidth = numTilesX * tileWidth;
int mapHeight = numTilesY * tileHeight;




InitWindow(windowWidth, windowHeight, "Map and Viking");

    // Chargement des textures Viking
    std::vector<Texture2D> vikingTexturesFaceMarche;
    std::vector<Texture2D> vikingTexturesFaceAttend;
    std::vector<Texture2D> vikingTexturesDroitMarche;
    std::vector<Texture2D> vikingTexturesDroitAttend;
    std::vector<Texture2D> vikingTexturesDosMarche;
    std::vector<Texture2D> vikingTexturesDosAttend;
    std::vector<Texture2D> vikingTexturesGaucheMarche;
    std::vector<Texture2D> vikingTexturesGaucheAttend;

    // Chargement des textures Viking pour chaque étape de l'animation 
    for (int i = 1; i < 25; i++) {
        std::string chaine = chaineEtape("images-128/viking-animation/viking-face-marche", i);
        Image vikingImage = LoadImage(chaine.c_str());
        Texture2D vikingTexture = LoadTextureFromImage(vikingImage);
        UnloadImage(vikingImage);
        vikingTexturesFaceMarche.push_back(vikingTexture);
    }
    for (int i = 1; i < 25; i++) {
        std::string chaine = chaineEtape("images-128/viking-animation/viking-face-attend", i);
        Image vikingImage = LoadImage(chaine.c_str());
        Texture2D vikingTexture = LoadTextureFromImage(vikingImage);
        UnloadImage(vikingImage);
        vikingTexturesFaceAttend.push_back(vikingTexture);
    }
    for (int i = 1; i < 25; i++) {
        std::string chaine = chaineEtape("images-128/viking-animation/viking-droite-marche", i);
        Image vikingImage = LoadImage(chaine.c_str());
        Texture2D vikingTexture = LoadTextureFromImage(vikingImage);
        UnloadImage(vikingImage);
        vikingTexturesDroitMarche.push_back(vikingTexture);
    }
    for (int i = 1; i < 25; i++) {
        std::string chaine = chaineEtape("images-128/viking-animation/viking-droite-attend", i);
        Image vikingImage = LoadImage(chaine.c_str());
        Texture2D vikingTexture = LoadTextureFromImage(vikingImage);
        UnloadImage(vikingImage);
        vikingTexturesDroitAttend.push_back(vikingTexture);
    }
    for (int i = 1; i < 25; i++) {
        std::string chaine = chaineEtape("images-128/viking-animation/viking-dos-marche", i);
        Image vikingImage = LoadImage(chaine.c_str());
        Texture2D vikingTexture = LoadTextureFromImage(vikingImage);
        UnloadImage(vikingImage);
        vikingTexturesDosMarche.push_back(vikingTexture);
    }
    for (int i = 1; i < 25; i++) {
        std::string chaine = chaineEtape("images-128/viking-animation/viking-dos-attend", i);
        Image vikingImage = LoadImage(chaine.c_str());
        Texture2D vikingTexture = LoadTextureFromImage(vikingImage);
        UnloadImage(vikingImage);
        vikingTexturesDosAttend.push_back(vikingTexture);
    }
    for (int i = 1; i < 25; i++) {
        std::string chaine = chaineEtape("images-128/viking-animation/viking-gauche-marche", i);
        Image vikingImage = LoadImage(chaine.c_str());
        Texture2D vikingTexture = LoadTextureFromImage(vikingImage);
        UnloadImage(vikingImage);
        vikingTexturesGaucheMarche.push_back(vikingTexture);
    }
    for (int i = 1; i < 25; i++) {
        std::string chaine = chaineEtape("images-128/viking-animation/viking-gauche-attend", i);
        Image vikingImage = LoadImage(chaine.c_str());
        Texture2D vikingTexture = LoadTextureFromImage(vikingImage);
        UnloadImage(vikingImage);
        vikingTexturesGaucheAttend.push_back(vikingTexture);
    }

    // Chargement des textures des carreaux
    Image herbe = LoadImage("images-128/carre-herbe.png");
    Image arbre = LoadImage("images-128/carre-arbre.png");
    Image montagne = LoadImage("images-128/carre-montagne.png");

    Texture2D textureHerbe = LoadTextureFromImage(herbe);
    Texture2D textureArbre = LoadTextureFromImage(arbre);
    Texture2D textureMontagne = LoadTextureFromImage(montagne);

    UnloadImage(herbe);
    UnloadImage(arbre);
    UnloadImage(montagne);

    std::vector<Texture2D> carreaux = {textureHerbe, textureArbre, textureMontagne};

    std::vector<std::vector<int>> map = {
        {2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2},
        {2,2,1,1,0,0,0,2,2,2,2},
        {2,1,0,0,0,1,0,0,0,1,2},
        {2,0,0,0,1,1,1,0,0,2,2},
        {2,0,0,1,1,1,1,0,0,0,2},
        {2,0,1,1,1,0,0,0,0,0,2},
        {2,0,1,0,0,0,0,0,0,0,2},
        {2,1,0,0,0,0,0,0,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2},
        {2,2,2,2,2,2,2,2,2,2,2},
    };

    SetTargetFPS(60);

    //-------------------------------------------------------------------
    int currentFrame = 0;

    // Position initiale de la texture du Viking
    Vector2 positionViking = { float(mapWidth / 2 - vikingTexturesFaceAttend[currentFrame].width / 2), float(mapHeight / 2 - vikingTexturesFaceAttend[currentFrame].height / 2) };

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        //---------------------------------------------------------------
        currentFrame = (currentFrame + 1) % vikingTexturesFaceAttend.size();
        //---------------------------------------------------------------

        // Draw
        //---------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        
        // Calculer l'échelle en fonction de la taille de la fenêtre et de la taille de la carte
        float scale = std::min(float(windowWidth) / mapWidth, float(windowHeight) / mapHeight);

        // Dessiner la carte en parcourant le tableau map  
        for (int i = 0; i < numTilesY; i++) {
            for (int j = 0; j < numTilesX; j++) {
                // Calculer la position du carreau
                float x = float(j * tileWidth * scale);
                float y = float(i * tileHeight * scale);

                // Dessiner le carreau en fonction de la valeur dans le tableau map avec une échelle plus petite
                Rectangle sourceRect = { 0, 0, float(tileWidth), float(tileHeight) };
                Rectangle destRect = { x, y, float(tileWidth* scale), float(tileHeight * scale) };
                DrawTexturePro(carreaux[map[i][j]], sourceRect, destRect, { 0, 0 }, 0.0f, WHITE);
            }
        }
        
        // Dessinez le Viking avec l'échelle en fonction de la touche enfoncée
        // Vérifie si aucune touche n'est enfoncée
        if (!IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
        {
            currentFrame = (currentFrame + 1) % vikingTexturesFaceAttend.size();
            DrawTexturePro(vikingTexturesFaceAttend[currentFrame], { 0, 0, (float)vikingTexturesFaceAttend[currentFrame].width, (float)vikingTexturesFaceAttend[currentFrame].height },
            { positionViking.x * scale, positionViking.y * scale, vikingTexturesFaceAttend[currentFrame].width * scale, vikingTexturesFaceAttend[currentFrame].height * scale },
            { 0, 0 }, 0.0f, WHITE);
               }

        // Viking se déplace vers la droite
        if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_UP)) 
            {
                positionViking.x += 2.0f;
                currentFrame = (currentFrame + 1) % vikingTexturesDroitMarche.size();
                DrawTexturePro(vikingTexturesDroitMarche[currentFrame], { 0, 0, (float)vikingTexturesDroitMarche[currentFrame].width, (float)vikingTexturesDroitMarche[currentFrame].height },
                { positionViking.x * scale, positionViking.y * scale, vikingTexturesDroitMarche[currentFrame].width * scale, vikingTexturesDroitMarche[currentFrame].height * scale },
                { 0, 0 }, 0.0f, WHITE);
            }

            
        // Viking se déplace vers la gauche    
        if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_RIGHT)) 
        {

            positionViking.x -= 2.0f;
            currentFrame = (currentFrame + 1) % vikingTexturesGaucheMarche.size();
                DrawTexturePro(vikingTexturesGaucheMarche[currentFrame], { 0, 0, (float)vikingTexturesGaucheMarche[currentFrame].width, (float)vikingTexturesGaucheMarche[currentFrame].height },
                { positionViking.x * scale, positionViking.y * scale, vikingTexturesGaucheMarche[currentFrame].width * scale, vikingTexturesGaucheMarche[currentFrame].height * scale },
                { 0, 0 }, 0.0f, WHITE);
        }
        
        // Viking se déplace vers le haut
        if (IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) 
        {
            positionViking.y -= 2.0f;
            currentFrame = (currentFrame + 1) % vikingTexturesDosMarche.size();
            DrawTexturePro(vikingTexturesDosMarche[currentFrame], { 0, 0, (float)vikingTexturesDosMarche[currentFrame].width, (float)vikingTexturesDosMarche[currentFrame].height },
               { positionViking.x * scale, positionViking.y * scale, vikingTexturesDosMarche[currentFrame].width * scale, vikingTexturesDosMarche[currentFrame].height * scale },
               { 0, 0 }, 0.0f, WHITE);

        }

        // Viking se déplace vers le bas
        if (IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) 
        {
            positionViking.y += 2.0f;
            currentFrame = (currentFrame + 1) % vikingTexturesFaceMarche.size();
            DrawTexturePro(vikingTexturesFaceMarche[currentFrame], { 0, 0, (float)vikingTexturesFaceMarche[currentFrame].width, (float)vikingTexturesFaceMarche[currentFrame].height },
               { positionViking.x * scale, positionViking.y * scale, vikingTexturesFaceMarche[currentFrame].width * scale, vikingTexturesFaceMarche[currentFrame].height * scale },
               { 0, 0 }, 0.0f, WHITE);}


        // Dessiner le Viking
        //DrawTextureEx(vikingTextures[currentFrame], positionViking, 0.0f, 0.5f, WHITE);
        
      


        EndDrawing();

        //---------------------------------------------------------------
    }

    // De-Initialization
    //-------------------------------------------------------------------
    // Décharger toutes les textures à la fin du programme
    for (const auto& texture : vikingTexturesFaceAttend) {
        UnloadTexture(texture);
    }

    for (const auto& texture : carreaux) {
        UnloadTexture(texture);
    }

    CloseWindow();

    return 0;
}


std::string chaineEtape(const std::string& nom, int etape) {
    std::ostringstream oss;
    oss << nom << "-" << std::setfill('0') << std::setw(4) << etape << ".png";
    return oss.str();
}

