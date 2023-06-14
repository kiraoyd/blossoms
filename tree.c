/* To run: cc  tree.c   -lm  -lX11 */

#include  "FPToolkit.c"

#include <math.h>
#include <stdbool.h>

#include "animation_lib.h" //library of methods

#define PI 3.14159265

int main(){

    //Declare variables here
    //USE DOUBLES!!!!! NOT INTS, except for array accessors
    double x0, y0, x1, y1, x2, y2, length, adj, opp;

    G_init_graphics (SWIDTH, SHEIGHT) ;  // interactive graphics

    draw_background(SWIDTH, SHEIGHT);

    /* CODE HERE */

    //Create initial p0 and p1 points for the first triangle (also top of trunk square)
    struct Point p0 = {450.0, 200.0};
    struct Point p1 = {550.0, 200.0};
    double distance = sqrt((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
    //set how far from p0 we want the third point to lie
    double percent = 0.4;
    double depth = 6.0;


    /*TODO hold on second tree for now
    //initial points for a second tree
    struct Point p2 = {200.0, 500.0};
    struct Point p3 = {250.0, 500.0};
    double distance2 = sqrt((p3.x - p2.x) * (p3.x - p2.x) + (p3.y - p2.y) * (p3.y - p2.y));
    double percent2 = 0.7;
    double depth2 = 4.0;
    */


     //make array and index pointer to keep track of blossom positions (up to 1000)
     int size = 1000;

     //first array for big tree
     struct Point blossoms [size];
     init_blossoms(blossoms, size);

     int index_val = 0;
     int *index = &index_val;

    /* TODO hold on second tree
     //second array for small tree
     struct Point blossoms2 [size];
     init_blossoms(blossoms2, size);

     int index_val2 = 0;
     int *index2 = &index_val2;
     */

    //calculate and draw trees recursively
    tree(p0, p1, distance, percent, depth, blossoms, index); //front
    //TODO try drawing the blossoms here instead of in the tree function
    //tree(p2,p3, distance2, percent2, depth2, blossoms2, index2); //back

   int radius = 5;
   int target = 10;
   int increment = 1;
   int radius_size_front = 0;
   int radius_size_back = 0;

    //what is the size of the blossoms array?
    int blossom_num = *index;

    int current_frame = 0;
    current_frame = fall(blossoms, blossom_num, p0, p1, distance, percent, depth, radius_size_front);

    //reset blossoms back to ends of tree
    index_val = 0;
    index = &index_val;
    tree_save_blossoms(p0, p1, distance, percent, depth, blossoms, index); //front

    current_frame = draw_leaves(blossoms, *index, 5, current_frame);
    grow_blossoms(blossoms, 5.0, 75, 0.5, *index, current_frame);
    G_wait_key();


    /* BEGIN SETDOWN */
    //int key ;
    //key =  G_wait_key() ; // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("trees.bmp") ;
}


