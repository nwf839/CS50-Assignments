//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// height and width of paddle
#define PADDLEHEIGHT 20
#define PADDLEWIDTH 60

// height and width of bricks
#define BRICKHEIGHT 15
#define BRICKWIDTH 34

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    GObject brick;
    double xVelocity = 0;
    double yVelocity = 0;
    
    xVelocity = 2.0;
    yVelocity = 2.0;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        
        // move circle along x-axis
        move(ball, xVelocity, yVelocity);

        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            xVelocity = -2 - drand48();
        }

        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            xVelocity = 2 + drand48();
        }
        
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives -= 1;
            removeGWindow(window, ball);
            ball = initBall(window);
        }
        
        else if (getY(ball) <= 0)
        {
            yVelocity = -yVelocity;
        }
        
        if (detectCollision(window, ball) != NULL &&
            strcmp(getType(detectCollision(window, ball)), "GRect") == 0 &&
            strcmp(getType(detectCollision(window, ball)), "GLabel") != 0)
        {
            yVelocity = -yVelocity;
            if (detectCollision(window, ball) != paddle)
            {
                removeGWindow(window, detectCollision(window, ball));
                points++;
                updateScoreboard(window, label, points);
            }
        }
        

        // linger before moving again
        pause(10);
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);

        // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure circle follows top cursor
                double x = getX(event) - PADDLEWIDTH / 2;
                setLocation(paddle, x, 520);
            }
        }

    }
    
    setLabel(label, "GAME OVER, CLICK SCREEN TO EXIT");
    setLocation(label, 0, (getHeight(window) - getHeight(label)) / 2);
    setFont(label, "SansSerif-22");

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int i = 0;
    int j = 0;
    GRect brick;
    
    for (i = 6; i < 395; i += 39)
    {
        for (j = 60; j < 160; j += 20)
        {
            brick = newGRect(i, j, BRICKWIDTH, BRICKHEIGHT);
            setFilled(brick, true);
            add(window, brick);
            if (j < 80)
            {
                setColor(brick, "RED");
            }
            else if (j < 100)
            {
                setColor(brick, "ORANGE");
            }
            else if (j < 120)
            {
                setColor(brick, "YELLOW");
            }
            else if (j < 140)
            {
                setColor(brick, "GREEN");
            }
            else
            {
                setColor(brick, "BLUE");
            }
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int xPosition = 0;
    int yPosition = 0;
    GOval ball;
    xPosition = (WIDTH - RADIUS) / 2;
    yPosition = (HEIGHT - RADIUS) / 2;
    ball = newGOval(xPosition, yPosition, RADIUS, RADIUS);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    int xPosition = 0;
    int yPosition = 0;
    GRect paddle;
    xPosition = (WIDTH - PADDLEWIDTH) / 2;
    yPosition = (HEIGHT - PADDLEHEIGHT) - 100;
    paddle = newGRect(xPosition, yPosition, PADDLEWIDTH, PADDLEHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label;
    double x = 0;
    double y = 0;
    
    label = newGLabel("0");
    x = (getWidth(window) - getWidth(label)) / 2;
    y = (getHeight(window) - getHeight(label)) / 2;
    setFont(label, "SansSerif-24");
    setLocation(label, x, y);
    add (window, label);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
