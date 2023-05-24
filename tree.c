/* To run: cc  tree.c   -lm  -lX11 */

#include  "FPToolkit.c"

#include <math.h>
#include <stdbool.h>

#include "animation_lib.h" //library of methods


#define PI 3.14159265

int main(){


    //Declare variables here
    //USE DOUBLES!!!!! NOT INTS, except for array accessors
    int swidth, sheight ;
    double x0, y0, x1, y1, x2, y2, length, adj, opp;

    swidth = 1000 ;  sheight = 1000 ;
    G_init_graphics (swidth,sheight) ;  // interactive graphics

    // clear the screen in a given color
    G_rgb (0.3, 0.3, 0.3) ; // dark gray
    G_clear () ;

    /* CODE HERE */

    //Create initial p0 and p1 points for the first triangle (also top of trunk square)
    struct Point p0 = {450.0, 200.0};
    struct Point p1 = {550.0, 200.0};
    double distance = sqrt((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
    //set how far from p0 we want the third point to lie
    double percent = 0.4;
    double depth = 7.0;


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

    /* TODO
    int blossom_num2 = *index2;
    printf("size of blossoms: %d, size of blossoms2: %d", blossom_num, blossom_num2);
    */

    //animate blossoms growing on front tree
    //We will get the final radius value back
    radius_size_front = grow_blossoms(blossoms, radius, target, increment, blossom_num);

    /* TODO hold on back tree
    //animate blossoms growing on back tree
    //We will get the final radius value back
    radius_size_back = grow_blossoms(blossoms2, radius, target, increment, blossom_num2);

    struct RGB color = {0.4, 0.4, 0.4};
    int target2= 0;
    int inc = 1;
    //TODO
    //int shrunk = wilt(blossoms, radius_size_front, target2, inc, size, color, p0, p1, distance, percent, depth);
    */

    fall(blossoms, blossom_num, p0, p1, distance, percent, depth, radius_size_front);
    //TODO how to save the state of the front tree to redraw it as the second runs
    //grow leaves
    /*
    int c = 0;
    int frames = 10;
    while(c < frames){
        G_rgb(0.3, 0.3, 0.3);
        G_clear();
        redraw_tree_no_blossoms(p0, p1, distance, percent, depth);
        draw_blossoms(blossoms, size, radius_size_front);
        tree(p0, p1, distance, percent, depth, blossoms, index); //front
        draw_leaves(blossoms, size, c);
        G_wait_key();
        c++;
    }
    */
    //fall(blossoms2, blossom_num2, p2, p3, distance2, percent2, depth2, radius_size_back);




    /* BEGIN SETDOWN */
    //int key ;
    //key =  G_wait_key() ; // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("trees.bmp") ;
}


