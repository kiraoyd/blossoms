#include "tree_lib.h"
#include <math.h>


//Increase size of all blossoms and draw
int grow_blossoms(struct Point blossoms[], int radius, int target, int increment, int size ){
    while (radius < target){
        int count = 0;
        while(count < size){
            /*TODO trying with flower
            G_fill_circle(blossoms[count].x, blossoms[count].y, radius);
            */
            draw_flower(blossoms[count].x, blossoms[count].y, 1);
            count++;
        }
        G_wait_key();
        radius = radius + increment;
    }
    return radius;
}

//TODO how to redraw the tree each time? Need to figure out which file this function should live in
//decrease size of all blossoms with color change
int wilt(struct Point blossoms[], int start_radius, int target, int increment, int size, struct RGB initial_color,struct Point p0, struct Point p1, double distance, double percent, double depth ){
    while(start_radius > target){
        int count = 0;
        while (count < size){
            G_rgb(0.3, 0.3, 0.3);
            G_clear();
            redraw_tree_no_blossoms(p0, p1, distance, percent, depth);
            //TODO change color as they wilt
            G_rgb(0.95,0.76,0.76);//pink
            G_fill_circle(blossoms[count].x, blossoms[count].y, start_radius);
            count++;
        }
        G_wait_key();
        start_radius = start_radius - increment;
    }
    return start_radius;
}


void fall(struct Point blossoms[], int size, struct Point p0, struct Point p1, double distance, double percent, double depth, int radius){
    //animate blossoms falling from front tree
    bool hanging = true;

    //make array of indicies big enough to hold all the available ones
    int indicies[size];
    //fill it with values that match the actual indicies
    for(int i = 0; i<size; i++){
         indicies[i] = i;
    }

    //we don't want to actually alter the size arg, as it holds onto the total number of blossoms that exist, so make a temp instead
    int available = size; //this will help track how many blossoms are still on the tree

    int to_fall[size]; //array that will hold which indicies to go to and animate in blossoms, will eventually hold ALL blossoms
    //initialize with -1 values to indicate empty spots
    for(int i=0; i<size; i++){
        to_fall[i] = -1;
    }

    //for each blossom, until we reach the ground, redraw the blossoms at a lower point
    int next_index = 0;
    while(hanging){
        G_rgb(0.3, 0.3, 0.3);
        G_clear();
        redraw_tree_no_blossoms(p0, p1, distance, percent, depth);

        //time to make the blossoms fall
       hanging = false; //assume all blossoms have fallen
       //which blossoms should fall? We will fill up to_fall each frame with a new blossom to join the fall
       int total_to_fall = 1;
       if(next_index < size){
            next_index = update_blossoms_to_move(blossoms, to_fall, next_index, indicies, &available, total_to_fall);
       }

       // draw all the blossoms: those in to_fall move down, the others draw in the tree at their initial spots
       int index = 0;
       while(index < size){
          //first be sure we draw all the stationary blossoms
          int draw = is_falling(to_fall, index, next_index);
          if(blossoms[index].y <= 0){
                //any blossom that has reached the ground should be drawn as stationary
                draw = 0;
          }
          if(draw == 0){ //index not in the to_fall list
              G_rgb(0.98,0.85,0.86);
              /* TODO trying with flower
              G_fill_circle(blossoms[index].x, blossoms[index].y, radius);
              */
              draw_flower(blossoms[index].x, blossoms[index].y, 1);
          }
          //then change and draw all the in motions falling ones
          else{
              blossoms[index].y -= 5.0;
              G_rgb(0.98,0.85,0.86);
              /* TODO trying with flower
              G_fill_circle(blossoms[index].x, blossoms[index].y, radius);
              */
              draw_flower(blossoms[index].x, blossoms[index].y, 1);
          }

          //update hanging to be true as long if at least one blossom hasn't reached the ground, keeps us in the loop
          if(blossoms[index].y > 0){
             hanging = true;
          }
          index++;
       }
        G_wait_key();

    }

}