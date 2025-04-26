/*

 _____                         ______                 ___   ____ 
|  __ \                        |  _  \               /   | / ___|
| |  \/  __ _  _ __ ___    ___ | | | |  ___ __   __ / /| |/ /___ 
| | __  / _` || '_ ` _ \  / _ \| | | | / _ \\ \ / // /_| || ___ \
| |_\ \| (_| || | | | | ||  __/| |/ / |  __/ \ V / \___  || \_/ |
 \____/ \__,_||_| |_| |_| \___||___/   \___|  \_/      |_/\_____/


*/

/* 
	AUTHOR: GameDev46

	Youtube: https://www.youtube.com/@gamedev46
	Github: https://github.com/GameDev46
*/

#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "include/raylib.h"

// Draw part of a texture (defined by a rectangle) with rotation and scale tiled into dest.
void DrawTextureTiled(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, float scale, Color tint);

/* ---------------------- */
/* MATHEMATICAL FUNCTIONS */
/* ---------------------- */

float distanceBetweenPoints(Vector2 point1, Vector2 point2) {

    // Calculate squared distance between points
    float gdistance = ( (point2.x - point1.x) * (point2.x - point1.x) ) + ( (point2.y - point1.y) * (point2.y - point1.y) );
    
    return sqrt(gdistance);
}

float distanceBetweenPointsSqrd(Vector2 point1, Vector2 point2) {

    // Calculate squared distance between points
    float gdistance = ( (point2.x - point1.x) * (point2.x - point1.x) ) + ( (point2.y - point1.y) * (point2.y - point1.y) );
    
    return gdistance;
}

float lengthOfVector(Vector2 length) {

    // Calculate squared distance between points
    float gdistance = ( length.x * length.x ) + ( length.y * length.y );
    
    return sqrt(gdistance);
}

float clamp(float d, float min, float max) {
  const float t = d < min ? min : d;
  return t > max ? max : t;
}

float minNum(float num1, float num2) {

    if (num1 < num2) {
        return num1;
    }

    return num2;
}

int generateRandomNumber(int lower, int upper) {
    return (rand() % (upper - lower + 1)) + lower;
}

/* ---------------------- */
/* BLOCK MANAGEMENT */
/* ---------------------- */

struct block {
    Vector2 position;
    Vector2 drawnPosition;
    Vector2 dimensions;
    Vector2 drawnDimensions;
    Color blockColour;
    int blockType;
    bool isHole;
};

const int maxBlocks = 50;

struct block sceneBlocks[50];
int nextBlockSpace = 0;

void createBlock(Vector2 position, Vector2 dimensions, int blockType, Color blockColour) {
    struct block newBlock;

    newBlock.position = (Vector2){ position.x - (dimensions.x * 0.5f), position.y - (dimensions.y * 0.5f) };
    newBlock.drawnPosition = newBlock.position;

    newBlock.dimensions = dimensions;
    newBlock.drawnDimensions = dimensions;

    newBlock.blockColour = blockColour;

    newBlock.blockType = blockType;
    newBlock.isHole = blockType == 1;

    sceneBlocks[nextBlockSpace] = newBlock;
    nextBlockSpace++;

    if (nextBlockSpace >= 50) {
        nextBlockSpace = 49;
    }

    return;
}

/* ---------------------- */
/* PARTICLE MANAGEMENT */
/* ---------------------- */

struct particle {
  Vector2 velocity;
  Vector2 position;
  Color particleColour;
  float lifeTime;
  float friction;
  float size;
  int fadeType;
};

const int maxParticles = 200;

struct particle sceneParticles[200];
int nextParticleSpace = 0;

void updateParticles() {

    for (int i = 0; i < maxParticles; i++) {

        if (sceneParticles[i].lifeTime > 0.0f) {
            // Update particle

            sceneParticles[i].position.x += sceneParticles[i].velocity.x * GetFrameTime() * 30.0f;
            sceneParticles[i].position.y += sceneParticles[i].velocity.y * GetFrameTime() * 30.0f;

            sceneParticles[i].velocity.x -= sceneParticles[i].velocity.x * GetFrameTime() * sceneParticles[i].friction;
            sceneParticles[i].velocity.y -= sceneParticles[i].velocity.y * GetFrameTime() * sceneParticles[i].friction;

            sceneParticles[i].lifeTime -= GetFrameTime();
            
        }

    }

    return;
}

void addParticles(Vector2 startPosition, Vector2 startVelocity, float size, float particleLifetime, float particleFriction, int fadeType, Color particleColour) {
    struct particle newParticle;

    newParticle.velocity = startVelocity;
    newParticle.position = startPosition;
    newParticle.particleColour = particleColour;
    newParticle.lifeTime = particleLifetime;
    newParticle.friction = particleFriction;
    newParticle.size = size;

    newParticle.fadeType = fadeType;

    sceneParticles[nextParticleSpace] = newParticle;
    nextParticleSpace++;

    if (nextParticleSpace >= maxParticles) {
        nextParticleSpace = 0;
    }

    return;
}

/* ---------------------- */
/* MAP MANAGEMENT */
/* ---------------------- */

#define courseBlockWidth 10
#define courseBlockHeight 14

// Creates the course from a character array
void createCourseFromChars(int windowWidth, int windowHeight, int courseCode[courseBlockHeight][courseBlockWidth]) {

    float barrierWidth = 200.0f;

    float yScalar = windowHeight / (courseBlockHeight * 1.0f);
    float xScalar = (windowWidth - (2.0f * barrierWidth)) / (courseBlockWidth * 1.0f);

    // Create barriers
    createBlock( (Vector2){ barrierWidth - (windowHeight * 0.5f), windowHeight / 2.0f}, (Vector2){ windowHeight, windowHeight + 10.0f }, 2, GetColor(0x13131333) );
    createBlock( (Vector2){ windowWidth - (barrierWidth - (windowHeight * 0.5f)), windowHeight / 2.0f }, (Vector2){ windowHeight, windowHeight + 10.0f }, 2, GetColor(0x13131333) );

    for (int y = 0; y < courseBlockHeight; y++) {
        for (int x = 0; x < courseBlockWidth; x++) {

            // Block
            if (courseCode[y][x] == 1) {
                createBlock( (Vector2){ (x * xScalar) + (xScalar * 0.5f) + barrierWidth, (y * yScalar) + (yScalar * 0.5f) }, (Vector2){ xScalar, yScalar }, 0, GetColor(0x9ec468ff) );
            }

            // Music Block
            if (courseCode[y][x] == 2) {

                int randColourChoice = generateRandomNumber(0, 6);

                if (randColourChoice == 0) createBlock( (Vector2){ (x * xScalar) + (xScalar * 0.5f) + barrierWidth, (y * yScalar) + (yScalar * 0.5f) }, (Vector2){ xScalar, yScalar }, 3, GetColor(0xf56c42ff) );
                if (randColourChoice == 1) createBlock( (Vector2){ (x * xScalar) + (xScalar * 0.5f) + barrierWidth, (y * yScalar) + (yScalar * 0.5f) }, (Vector2){ xScalar, yScalar }, 3, GetColor(0xeb9e34ff) );
                if (randColourChoice == 2) createBlock( (Vector2){ (x * xScalar) + (xScalar * 0.5f) + barrierWidth, (y * yScalar) + (yScalar * 0.5f) }, (Vector2){ xScalar, yScalar }, 3, GetColor(0xebe834ff) );
                if (randColourChoice == 3) createBlock( (Vector2){ (x * xScalar) + (xScalar * 0.5f) + barrierWidth, (y * yScalar) + (yScalar * 0.5f) }, (Vector2){ xScalar, yScalar }, 3, GetColor(0x34eb86ff) );
                if (randColourChoice == 4) createBlock( (Vector2){ (x * xScalar) + (xScalar * 0.5f) + barrierWidth, (y * yScalar) + (yScalar * 0.5f) }, (Vector2){ xScalar, yScalar }, 3, GetColor(0x34abebff) );
                if (randColourChoice == 5) createBlock( (Vector2){ (x * xScalar) + (xScalar * 0.5f) + barrierWidth, (y * yScalar) + (yScalar * 0.5f) }, (Vector2){ xScalar, yScalar }, 3, GetColor(0x9334ebff) );
                if (randColourChoice == 6) createBlock( (Vector2){ (x * xScalar) + (xScalar * 0.5f) + barrierWidth, (y * yScalar) + (yScalar * 0.5f) }, (Vector2){ xScalar, yScalar }, 3, GetColor(0xeb3499ff) );

            }

            // Fan
            if (courseCode[y][x] == 3) {
                createBlock( (Vector2){ (x * xScalar) + (xScalar * 0.5f) + barrierWidth, (y * yScalar) + (yScalar * 0.5f) }, (Vector2){ xScalar, yScalar }, 5, GetColor(0xf0f0f0ff) );
            }

            if (courseCode[y][x] == 4) {
                createBlock( (Vector2){ (x * xScalar) + (xScalar * 0.5f) + barrierWidth, (y * yScalar) + (yScalar * 0.5f) }, (Vector2){ xScalar, yScalar }, 4, GetColor(0xf0f0f0ff) );
            }

            if (courseCode[y][x] == 5) {
                createBlock( (Vector2){ (x * xScalar) + (xScalar * 0.5f) + barrierWidth, (y * yScalar) + (yScalar * 0.5f) }, (Vector2){ xScalar, yScalar }, 6, GetColor(0xf0f0f0ff) );
            }

        }
    }

    // Create hole
    createBlock( (Vector2){ windowWidth / 2.0f, 50.0f }, (Vector2){ 8.0f, 8.0f }, 1, BLACK );

    return;
}

// Loads the next map
void loadMap(int mapID, int windowWidth, int windowHeight) {

    nextBlockSpace = 0;

    if (mapID == 1) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 2) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 3) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 },
            { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 4) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 },
            { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 0, 0, 0, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 0, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 5) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 1, 1, 1, 0, 0, 1, 1 },
            { 1, 1, 1, 1, 1, 1, 0, 0, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 0, 0, 1, 1, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 1, 1, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    // Introduction of music blocks
    if (mapID == 6) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 0, 0, 0, 0, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 2, 0, 2, 0, 0, 2, 0, 2, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 2, 0, 2, 0, 0, 2, 0, 2, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 0, 0, 0, 0, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 7) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, 
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 1, 2, 2, 1, 0, 0, 1 },
            { 1, 0, 0, 1, 0, 0, 0, 0, 0, 2 },
            { 1, 0, 0, 1, 0, 0, 0, 0, 0, 2 },
            { 1, 2, 2, 1, 0, 0, 1, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 8) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 },
            { 1, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 9) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    // Introduction of fans
    if (mapID == 10) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 11) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 12) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 13) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 },
            { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 14) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 1, 1, 1, 0, 0, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
            { 1, 1, 0, 0, 1, 1, 1, 1, 1, 1 },
            { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 15) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
            { 0, 1, 1, 1, 5, 5, 1, 1, 1, 0 },
            { 0, 1, 0, 0, 0, 0, 0, 0, 1, 0 },
            { 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 },
            { 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 },
            { 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 },
            { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
            { 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    if (mapID == 16) {
        int map[courseBlockHeight][courseBlockWidth] = { 
            { 1, 5, 5, 1, 0, 0, 0, 0, 0, 1 }, 
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
            { 4, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 4, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 1, 0, 0, 1, 1, 1, 1, 0, 0, 1 },
            { 1, 0, 0, 2, 0, 0, 0, 0, 0, 3 },
            { 1, 0, 0, 2, 0, 0, 0, 0, 0, 3 },
            { 1, 2, 2, 1, 0, 0, 1, 1, 1, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
        };

        createCourseFromChars(windowWidth, windowHeight, map);
    }

    return;

}

/* ---------------------- */
/* GAME LOOP */
/* ---------------------- */

int main() {

    // Initiate the window + starting variables
    const int windowWidth = 800, windowHeight = 600;

    InitWindow(windowWidth, windowHeight, "Pixel Putt");
    SetTargetFPS(60);

    Image windowIcon = LoadImage("images/icon.png");
    SetWindowIcon(windowIcon);

    InitAudioDevice();

    // Background settings
    const int backgroundDimensions = 638;
    const float backgroundScale = 0.5f;

    // Level transition settings
    bool isTransitioning = false;
    float transitionTimer = 0.0f;

    float transitionDuration = 5.0f;

    int transitionState = 0;

    // Setup course statistics
    int holeNumber = 1;
    int shots[100];

    for (int i = 0; i < 100; i++) {
        shots[i] = 0;
    }

    // Setup particles
    float ballMoveParticleTimer = 0.0f;
    float fanTimer = 0.0f;

    for (int i = 0; i < maxParticles; i++) {
        addParticles((Vector2){ -1000.0f, -1000.0f } , (Vector2){ 0.0f, 0.0f }, 0.0f, 0.0f, 10.0f, 0, BROWN);
    }

    // Setup ball
    Vector2 ballStartPosition = { windowWidth / 2.0, windowHeight - 100.0f };

    Vector2 ballPosition = ballStartPosition;
    Vector2 ballVelocity = { 0.0f, 0.0f };

    float ballRadius = 7.0f;

    float friction = 1.0f;

    // Setup player preferences
    bool pauseGameplay = false;
    bool showLevelStats = false;

    // Setup mouse listeners
    Vector2 localMousePosition = { 0.0f, 0.0f };

    bool isMouseDown = false;
    bool mouseWasDown = false;

    // Load background texture
    Texture2D background = LoadTexture("images/grass.png");

    // Load transition texture
    Texture2D transitionBacking = LoadTexture("images/transition.png");

    // Load note textures
    Texture2D noteImage = LoadTexture("images/note.png");
    Texture2D smallNoteImage = LoadTexture("images/singleNote.png");

    // Setup sounds
    Sound impactWav = LoadSound("sounds/impact.wav");
    Sound ballHitWav = LoadSound("sounds/clubHit.wav");
    Sound ballEnterHoleWav = LoadSound("sounds/enterHole.wav");
    Sound toneWav = LoadSound("sounds/tone.wav");
    Sound fanBlade = LoadSound("sounds/fan.wav");

    // Setup game theme
    Sound themeTune = LoadSound("sounds/Mini_Golf_Game_Theme.mp3");

    SetSoundVolume(themeTune, 0.2f);
    PlaySound(themeTune);

    // Load map
    loadMap(holeNumber, windowWidth, windowHeight);

    // Run the actual game
    while (!WindowShouldClose()) {

        // Check main menu music is playing
        if (!IsSoundPlaying(themeTune)) {
            PlaySound(themeTune);
        }

        // Record any keys being pressed
        int currentKeyPressed = GetKeyPressed();

        // Check to see if player wants to restart the level
        // R = 82
        if (currentKeyPressed == 82 && !pauseGameplay) {
            // Reset current level
            ballPosition = ballStartPosition;
            shots[holeNumber - 1] = 0;
            ballVelocity = (Vector2){ 0.0f, 0.0f };
        }

        // Check to see if player wants to toggle the level stats
        // T = 84
        if (currentKeyPressed == 84) {
            // Reset current level
            showLevelStats = !showLevelStats;
        }
        
        // Update mouse position and mouse state
        localMousePosition = GetMousePosition();
        isMouseDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);

        // Calculate a force to apply to the ball when hit
        float force = 0.0f;

        if (lengthOfVector(ballVelocity) < 0.3f) {

            ballVelocity.x = 0.0f;
            ballVelocity.y = 0.0f;

            if (isMouseDown == false && mouseWasDown == true && !pauseGameplay) {

                // Calculate the distance between the mouse and the ball
                float distFromBall = distanceBetweenPoints( ballPosition , localMousePosition );

                force = distFromBall * 0.1f;
                float radians = atan2(ballPosition.y - localMousePosition.y, ballPosition.x - localMousePosition.x);

                ballVelocity.x += cos(radians) * force;
                ballVelocity.y += sin(radians) * force;

                shots[holeNumber - 1]++;

                // Play hit sound
                PlaySound(ballHitWav);

            } else if (isMouseDown == true && !pauseGameplay) {

                float distFromBall = distanceBetweenPoints( ballPosition , localMousePosition );
                force = distFromBall * 0.1f;

            }
            
        } else {
            
            ballMoveParticleTimer += GetFrameTime();

            if (ballMoveParticleTimer > 0.05f) {
                ballMoveParticleTimer = 0.0f;

                float randomMultiplier = (generateRandomNumber(0, 1000) / 500.0f) - 1.0f;

                // Spawn particles
                addParticles(ballPosition, (Vector2){ lengthOfVector(ballVelocity) * randomMultiplier * 0.1f, lengthOfVector(ballVelocity) * randomMultiplier * 0.1f }, 5.0f, 1.0f, 2.0f, 1, GetColor(0x735f4bff));
                
            }

        }

        mouseWasDown = isMouseDown;

        // Move ball and check for any collisions (done twice per frame)
        if (!pauseGameplay) {

            bool hasHitHole = false;
            bool hasCollided = false;

            // Skip level if m key pressed
            // M = 77
            if (currentKeyPressed == 77) {
                // Reset current level
                hasHitHole = true;

                ballVelocity.x = 0.0f;
                ballVelocity.y = 0.0f;

                pauseGameplay = true;
            }

            for (int s = 0; s < 2; s++) {

                // Simulate the ball's velocity
                ballPosition.x += ballVelocity.x * GetFrameTime() * 30.0f * 0.5f;
                ballPosition.y += ballVelocity.y * GetFrameTime() * 30.0f * 0.5f;

                ballVelocity.x -= ballVelocity.x * GetFrameTime() * friction * 0.5f;
                ballVelocity.y -= ballVelocity.y * GetFrameTime() * friction * 0.5f;

                // Check for the edges of the window

                if (ballPosition.x - ballRadius < 0.0f) {
                    ballPosition.x = ballRadius;
                    ballVelocity.x *= -0.95f;

                    hasCollided = true;
                }

                if (ballPosition.x + ballRadius > windowWidth) {
                    ballPosition.x = windowWidth - ballRadius;
                    ballVelocity.x *= -0.95f;

                    hasCollided = true;
                }

                if (ballPosition.y - ballRadius < 0.0f) {
                    ballPosition.y = ballRadius;
                    ballVelocity.y *= -0.95f;

                    hasCollided = true;
                }

                if (ballPosition.y + ballRadius > windowHeight) {
                    ballPosition.y = windowHeight - ballRadius;
                    ballVelocity.y *= -0.95f;

                    hasCollided = true;
                }

                for (int i = 0; i < maxBlocks; i++) {
                    if (i < nextBlockSpace) {
                        // Check for x collision

                        float blockX = sceneBlocks[i].position.x;
                        float blockY = sceneBlocks[i].position.y;

                        float blockWidth = sceneBlocks[i].dimensions.x;
                        float blockHeight = sceneBlocks[i].dimensions.y;

                        bool yCollision = ballPosition.y + ballRadius > blockY && ballPosition.y - ballRadius < blockY + blockHeight;
                        bool xCollision = ballPosition.x + ballRadius > blockX && ballPosition.x - ballRadius < blockX + blockWidth;

                        if (sceneBlocks[i].blockType == 6 && ballPosition.y > blockY + blockHeight && xCollision) {
                            // Apply a force to the ball
                            ballVelocity.y += 20.0f * GetFrameTime();
                        }

                        // Check for y collision
                        if (yCollision) {

                            if (sceneBlocks[i].blockType == 4 && ballPosition.x > blockX + blockWidth) {
                                // Apply a force to the ball
                                ballVelocity.x += 20.0f * GetFrameTime();
                            }

                            if (sceneBlocks[i].blockType == 5 && ballPosition.x < blockX) {
                                // Apply a force to the ball
                                ballVelocity.x -= 20.0f * GetFrameTime();
                            }

                            // Check for x collision
                            if (xCollision) {

                                for (int t = 0; t < 20; t++) {

                                    // Y test
                                    float offset = 5.0f * t;

                                    if (ballPosition.y + ballRadius - offset < blockY) {
                                        // Top collision
                                        ballVelocity.y *= -0.95f;
                                        ballPosition.y = blockY - ballRadius;

                                        t += 100;
                                    }

                                    if (ballPosition.y - ballRadius + offset > blockY + blockHeight) {
                                        // Bottom collision
                                        ballVelocity.y *= -0.95f;
                                        ballPosition.y = blockY + blockHeight + ballRadius;

                                        t += 100;
                                    }

                                    // X test
                                    if (ballPosition.x + ballRadius - offset < blockX) {
                                        // Left side collision
                                        ballVelocity.x *= -0.95f;
                                        ballPosition.x = blockX - ballRadius;

                                        t += 100;
                                    }

                                    if (ballPosition.x - ballRadius + offset > blockX + blockWidth) {
                                        // Right side collision
                                        ballVelocity.x *= -0.95f;
                                        ballPosition.x = blockX + blockWidth + ballRadius;

                                        t += 100;
                                    }

                                }
                                
                                // Find closest side (ONLY WORKS WHEN BLOCK IS A SQUARE AND NOT A RECTANGLE!!!!) - OLD

                                /*float topSideDist = distanceBetweenPointsSqrd(ballPosition, (Vector2){ blockX + (0.5f * blockWidth), blockY });
                                float bottomSideDist = distanceBetweenPointsSqrd(ballPosition, (Vector2){ blockX + (0.5f * blockWidth), blockY + blockHeight });
                                float leftSideDist = distanceBetweenPointsSqrd(ballPosition, (Vector2){ blockX , blockY + (0.5f * blockHeight) });
                                float rightSideDist = distanceBetweenPointsSqrd(ballPosition, (Vector2){ blockX + blockWidth, blockY + (0.5f * blockHeight) });

                                float mimimunDist = minNum( topSideDist, minNum( bottomSideDist, minNum( leftSideDist, rightSideDist ) ) );

                                if (topSideDist == mimimunDist) {
                                    ballVelocity.y *= -1.0f;
                                    ballPosition.y = blockY - ballRadius;
                                }

                                if (bottomSideDist == mimimunDist) {
                                    ballVelocity.y *= -1.0f;
                                    ballPosition.y = blockY + blockHeight + ballRadius;
                                }

                                if (leftSideDist == mimimunDist) {
                                    ballVelocity.x *= -1.0f;
                                    ballPosition.x = blockX - ballRadius;
                                }

                                if (rightSideDist == mimimunDist) {
                                    ballVelocity.x *= -1.0f;
                                    ballPosition.x = blockX + blockWidth + ballRadius;
                                }*/

                                // Check if object is end hole
                                if (sceneBlocks[i].isHole) {
                                    hasHitHole = true;

                                    ballPosition.x = blockX + (blockWidth * 0.5f);
                                    ballPosition.y = blockY + (blockHeight * 0.5f);

                                    ballVelocity.x = 0.0f;
                                    ballVelocity.y = 0.0f;

                                    pauseGameplay = true;

                                    // Play ball enter hole sound
                                    PlaySound(ballEnterHoleWav);
                                }

                                // Check if object is a music block
                                // Check if object is end hole
                                if (sceneBlocks[i].blockType == 3) {
                                    // Play tone
                                    StopSound(toneWav);
                                    //SetSoundPitch(toneWav, generateRandomNumber(0, 2000) / 1000.0f);
                                    SetSoundPitch(toneWav, ( sceneBlocks[i].position.x + sceneBlocks[i].position.y ) / ( (windowWidth * 0.5f) + (windowHeight * 0.5f)) );
                                    PlaySound(toneWav);

                                    // Cause block to expand
                                    sceneBlocks[i].drawnDimensions.x = sceneBlocks[i].dimensions.x + 10.0f;
                                    sceneBlocks[i].drawnDimensions.y = sceneBlocks[i].dimensions.y + 10.0f;
                                }

                                hasCollided = true;

                            }
                        }
                    }
                }

            }

            if (hasCollided) {
                // Play collision sounds
                SetSoundVolume(impactWav, lengthOfVector(ballVelocity) * 0.1f);
                PlaySound(impactWav);
            }

            if (hasHitHole) {
                isTransitioning = true;
                transitionTimer = 0.0f;
            }

        }

        // Update particles
        updateParticles();

        // Render scene      
        BeginDrawing();

        ClearBackground( WHITE );

        // Draw background
        for (int i = 0; i < 3; i++) {

            DrawTextureEx(background, (Vector2){ i * backgroundDimensions * backgroundScale, 0 }, 0.0f, backgroundScale, WHITE);
            DrawTextureEx(background, (Vector2){ i * backgroundDimensions * backgroundScale, backgroundDimensions * backgroundScale }, 0.0f, backgroundScale, WHITE);

        }
        
        // Draw particles
        for (int i = 0; i < maxParticles; i++) {
            if (sceneParticles[i].lifeTime > 0.0f) {

                if (sceneParticles[i].fadeType == 1) {
                    DrawCircle(sceneParticles[i].position.x / 1, sceneParticles[i].position.y / 1, sceneParticles[i].lifeTime * sceneParticles[i].size, sceneParticles[i].particleColour);
                } else {
                    DrawCircle(sceneParticles[i].position.x / 1, sceneParticles[i].position.y / 1, sceneParticles[i].size, sceneParticles[i].particleColour);
                }

            }
        }

        // Render ball
        if (!pauseGameplay || transitionState != 0) {
            // Shadow
            DrawCircle(ballPosition.x / 1, (ballPosition.y / 1) + 5.0f, ballRadius - 1.0f, GetColor(0x00000044));

            // Ball
            DrawCircle(ballPosition.x / 1, ballPosition.y / 1, ballRadius, BLACK);
            DrawCircle(ballPosition.x / 1, ballPosition.y / 1, ballRadius - 4.0f, WHITE);
        }

        float closestFan = 999.0f;

        // Draw Blocks
        for (int i = 0; i < maxBlocks; i++) {
            if (i < nextBlockSpace) {

                if (sceneBlocks[i].isHole) {
                    DrawCircle(sceneBlocks[i].drawnPosition.x, sceneBlocks[i].drawnPosition.y, sceneBlocks[i].drawnDimensions.x, GetColor(0x353535ff));
                    DrawCircle(sceneBlocks[i].drawnPosition.x, sceneBlocks[i].drawnPosition.y + 1.5f, sceneBlocks[i].drawnDimensions.x * 0.9f, GetColor(0x131313ff));
                } else {
                    float shadowSize = 30.0f;
                    // Shadow
                    DrawRectangle(sceneBlocks[i].drawnPosition.x, sceneBlocks[i].drawnPosition.y, sceneBlocks[i].drawnDimensions.x, sceneBlocks[i].drawnDimensions.y + shadowSize, GetColor(0x13131377));

                    DrawRectangle(sceneBlocks[i].drawnPosition.x, sceneBlocks[i].drawnPosition.y, sceneBlocks[i].drawnDimensions.x, sceneBlocks[i].drawnDimensions.y, sceneBlocks[i].blockColour);
                    DrawRectangle(sceneBlocks[i].drawnPosition.x, sceneBlocks[i].drawnPosition.y + sceneBlocks[i].drawnDimensions.y - 5.0f, sceneBlocks[i].drawnDimensions.x, 5.0f, GetColor(0x13131333));

                    if (sceneBlocks[i].blockType == 2) {
                        // Border
                        DrawRectangle(sceneBlocks[i].drawnPosition.x, sceneBlocks[i].drawnPosition.y, 5.0f, sceneBlocks[i].drawnDimensions.y, GetColor(0x131313ff));
                        DrawRectangle(sceneBlocks[i].drawnPosition.x, sceneBlocks[i].drawnPosition.y, sceneBlocks[i].drawnDimensions.x, 5.0f, GetColor(0x131313ff));

                        DrawRectangle(sceneBlocks[i].drawnPosition.x, sceneBlocks[i].drawnPosition.y + sceneBlocks[i].drawnDimensions.y, sceneBlocks[i].drawnDimensions.x, 5.0f, GetColor(0x131313ff));
                        DrawRectangle(sceneBlocks[i].drawnPosition.x + sceneBlocks[i].drawnDimensions.x, sceneBlocks[i].drawnPosition.y, 5.0f, sceneBlocks[i].drawnDimensions.y, GetColor(0x131313ff));
                    }

                    if (sceneBlocks[i].blockType == 3) {

                        // Render note image on top of note block
                        if ((int)(sceneBlocks[i].position.x / 1) % 3 == 0) {
                            DrawTextureEx(noteImage, (Vector2){ sceneBlocks[i].drawnPosition.x + (sceneBlocks[i].drawnDimensions.x * 0.5f) - 14.0f, sceneBlocks[i].drawnPosition.y + (sceneBlocks[i].drawnDimensions.y * 0.5f) - 14.0f }, 0.0f, 0.04f, GetColor(0xffffff77));
                        } else {
                            DrawTextureEx(smallNoteImage, (Vector2){ sceneBlocks[i].drawnPosition.x + (sceneBlocks[i].drawnDimensions.x * 0.5f) - 14.0f, sceneBlocks[i].drawnPosition.y + (sceneBlocks[i].drawnDimensions.y * 0.5f) - 14.0f }, 0.0f, 0.04f, GetColor(0xffffff77));
                        }

                        sceneBlocks[i].drawnDimensions.x += (sceneBlocks[i].dimensions.x - sceneBlocks[i].drawnDimensions.x) * GetFrameTime() * 1.0f;
                        sceneBlocks[i].drawnDimensions.y += (sceneBlocks[i].dimensions.y - sceneBlocks[i].drawnDimensions.y) * GetFrameTime() * 1.0f;

                        sceneBlocks[i].drawnPosition.x = sceneBlocks[i].position.x + (sceneBlocks[i].dimensions.x - sceneBlocks[i].drawnDimensions.x) * 0.5f;
                        sceneBlocks[i].drawnPosition.y = sceneBlocks[i].position.y + (sceneBlocks[i].dimensions.y - sceneBlocks[i].drawnDimensions.y) * 0.5f;
                    }

                    // Check to see if any wind particles should be drawn
                    if (fanTimer > 0.1f) {

                        if (sceneBlocks[i].blockType == 4) {
                            addParticles( (Vector2){ sceneBlocks[i].position.x, sceneBlocks[i].position.y + 10.0f + ( (GetRandomValue(0, 100) / 100.0f) * (sceneBlocks[i].dimensions.y - 20.0f) ) }, (Vector2){ GetRandomValue(60, 130) / 10.0f, 0.0f }, GetRandomValue(5, 20) / 10.0f, 3.0f, 0.0f, 1, GetColor(0xffffff54) );

                            float dist = distanceBetweenPoints(ballPosition, sceneBlocks[i].position);
                            if (closestFan > dist) closestFan = dist;
                        }

                        if (sceneBlocks[i].blockType == 5) {
                            addParticles( (Vector2){ sceneBlocks[i].position.x, sceneBlocks[i].position.y + 10.0f + ( (GetRandomValue(0, 100) / 100.0f) * (sceneBlocks[i].dimensions.y - 20.0f) ) }, (Vector2){ GetRandomValue(60, 130) / -10.0f, 0.0f }, GetRandomValue(5, 20) / 10.0f, 3.0f, 0.0f, 1, GetColor(0xffffff54) );
                        
                            float dist = distanceBetweenPoints(ballPosition, sceneBlocks[i].position);
                            if (closestFan > dist) closestFan = dist;
                        }

                        if (sceneBlocks[i].blockType == 6) {
                            addParticles( (Vector2){ sceneBlocks[i].position.x + 10.0f + ( (GetRandomValue(0, 100) / 100.0f) * (sceneBlocks[i].dimensions.x - 20.0f) ), sceneBlocks[i].position.y }, (Vector2){ 0.0f, GetRandomValue(60, 130) / 10.0f }, GetRandomValue(5, 20) / 10.0f, 3.0f, 0.0f, 1, GetColor(0xffffff54) );
                        
                            float dist = distanceBetweenPoints(ballPosition, sceneBlocks[i].position);
                            if (closestFan > dist) closestFan = dist;
                        }

                    }

                    // DEBUG
                    //DrawCircle(sceneBlocks[i].drawnPosition.x, sceneBlocks[i].drawnPosition.y, 5.0f, RED);
                    //DrawCircle(sceneBlocks[i].drawnPosition.x, sceneBlocks[i].drawnPosition.y + sceneBlocks[i].drawnDimensions.y, 5.0f, BLUE);
                }

            }
        }

        if (closestFan != 999.0f) {
            SetSoundVolume( fanBlade, clamp( 0.5f - (closestFan * 0.0025f), 0.0f, 1.0f ) * 0.5f );

            if (!IsSoundPlaying(fanBlade)) PlaySound(fanBlade);
        }

        if (fanTimer > 0.1f) fanTimer = 0.0f;
        fanTimer += GetFrameTime();


        if (force > 0.1f) {
            Color lineColour = ColorFromHSV( clamp( 50.0f - force, 0.0f, 50.0f), 0.75f, 1.0f );
            DrawLineEx(ballPosition, localMousePosition, 5.0f, lineColour);
        }

        // Render UI

        // Draw power - developer mode
        /*char powerBuf[256];
        snprintf(powerBuf, sizeof(powerBuf), "%s %d", "Power:", (int) lround(force));

        DrawText(powerBuf, 10, 10, 25, WHITE);*/

        // Show hole number
        int textXPosition = 30;

        // Hole number
        char holeNumberBuf[256];
        snprintf(holeNumberBuf, sizeof(holeNumberBuf), "%s %d", "Hole", holeNumber);

        DrawText(holeNumberBuf, textXPosition, 20, 30, WHITE);
        
        // Shots
        char shotNumberBuff[256];
        snprintf(shotNumberBuff, sizeof(shotNumberBuff), "%s %d", "Strokes: ", shots[holeNumber - 1]);

        DrawText(shotNumberBuff, textXPosition, 55, 15, WHITE);

        // Information
        DrawText("Restart Level: R", textXPosition, 90, 10, WHITE);
        DrawText("Toggle Stats: T", textXPosition, 105, 10, WHITE);
        DrawText("Skip Level: M", textXPosition, 120, 10, WHITE);

        // Credits
        //DrawText("Credits:", 10, windowHeight - 175.0f, 15, WHITE);

        DrawText("Sound Effects:", 10, windowHeight - 145.0f, 10, WHITE);
        DrawText("https://freesound.org/", 10, windowHeight - 130.0f, 10, WHITE);
        DrawText("GameDev46", 10, windowHeight - 115.0f, 10, WHITE);

        DrawText("Programming:", 10, windowHeight - 85.0f, 10, WHITE);
        DrawText("GameDev46", 10, windowHeight - 70.0f, 10, WHITE);

        DrawText("Theme Song:", 10, windowHeight - 40.0f, 10, WHITE);
        DrawText("GameDev46", 10, windowHeight - 25.0f, 10, WHITE);

        // Check to show stats
        if (showLevelStats) {
            for (int s = 0; s < 100; s++) {

                if (s < holeNumber - 1) {

                    char statsHoleBuff[256];
                    snprintf(statsHoleBuff, sizeof(statsHoleBuff), "%s %d", "Hole", s + 1);
                    DrawText(statsHoleBuff, windowWidth - 100.0f, (s * 50) + 20, 20, WHITE);

                    char statsShotsBuff[256];
                    snprintf(statsShotsBuff, sizeof(statsShotsBuff), "%s %d", "Strokes: ", shots[s]);
                    DrawText(statsShotsBuff, windowWidth - 100.0f, (s * 50) + 45, 12, WHITE);

                } else {
                    s += 1000;
                }
            }
        }

        // Draw transition if showing
        if (isTransitioning) {

            if (isMouseDown && transitionState == 1) {
                transitionState = 2;
            }

            DrawTextureEx(transitionBacking, (Vector2){ -3000.0f + (transitionTimer * 6000.0f * (1.0f / transitionDuration)), -600.0f }, 0.0f, 3.0f, WHITE);

            if (transitionState == 1) {

                // Hole number
                char holeStats[256];
                snprintf(holeStats, sizeof(holeStats), "%s %d %s", "Hole", holeNumber, "Complete");
                DrawText(holeStats, (windowWidth / 2.0f) - 160.0f, (windowHeight / 2.0f) - 100.0f, 45, WHITE);
        
                // Shots
                char shotNumberStats[256];
                snprintf(shotNumberStats, sizeof(shotNumberStats), "%s %d", "Strokes: ", shots[holeNumber - 1]);
                DrawText(shotNumberStats, (windowWidth / 2.0f) - 80.0f, (windowHeight / 2.0f), 35, WHITE);

                DrawText("Left Click To Continue...", (windowWidth / 2.0f) - 90.0f, windowHeight - 50.0f, 15, WHITE);
            } else {

                transitionTimer += GetFrameTime();

            }

            if (transitionTimer >= transitionDuration * 0.45f && transitionState == 0) {
                // Pause transition at 50%
                transitionState = 1;
            }

            if (transitionTimer >= transitionDuration * 0.5f && transitionState == 2) {

                transitionState = 3;

                // Setup particles
                ballMoveParticleTimer = 0.0f;

                for (int i = 0; i < maxParticles; i++) {
                    addParticles((Vector2){ -1000.0f, -1000.0f } , (Vector2){ 0.0f, 0.0f }, 0.0f, 0.0f, 10.0f, 0, BROWN);
                }

                // Setup ball
                ballPosition = ballStartPosition;
                ballVelocity = (Vector2){ 0.0f, 0.0f };

                holeNumber++;
                loadMap(holeNumber, windowWidth, windowHeight);
            }

            if (transitionTimer >= transitionDuration * 0.75f) {
                // Stop transition
                isTransitioning = false;
                transitionTimer = 0.0f;

                pauseGameplay = false;

                transitionState = 0;
            }

        }

        EndDrawing();
    }

    // Unload game when window is closed and exit main

    UnloadSound(impactWav);
    UnloadSound(ballHitWav);
    UnloadSound(ballEnterHoleWav);
    UnloadSound(themeTune);
    UnloadSound(fanBlade);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
