#include "tree_lib.h"
#include <math.h>


//Increase size of all blossoms and draw
int grow_blossoms(struct Point blossoms[], int radius, int target, int increment, int size ){
    while (radius < target){
        int count = 0;
        while(count < size){
            G_fill_circle(blossoms[count].x, blossoms[count].y, radius);
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

    //TODO can we make the blossoms fall at different rates?
void fall(struct Point blossoms[], int size, struct Point p0, struct Point p1, double distance, double percent, double depth, int radius){
    //animate blossoms falling from front tree
    bool hanging = true;
    //make array of indicies big enough to hold all the available ones
    int indicies[size];
    //fill it with values that match the actual indicies
    for(int i = 0; i<size; i++){
         indicies[i] = i;
    }
    //we don't want to actually alter the size arg, so make a temp instead
    int available = size;
    printf("Blossoms we have are: %d ", available);
    int to_fall[size]; //array that will hold which indicies to go to and animate in blossoms, each loop
    //initialize with -1 values to indicate empty spots
    for(int i=0; i<size; i++){
        to_fall[i] = -1;
    }
    int next_index = 0;

    int test = 0;
    //for each blossom, until we reach the ground redraw the blossoms at a lower point
    while(hanging){
        G_rgb(0.3, 0.3, 0.3);
        G_clear();
        redraw_tree_no_blossoms(p0, p1, distance, percent, depth);
        //time to make the blossoms fall
        hanging = false;
        /*
        int i = 0;
        while(i  < size){
            blossoms[i].y = blossoms[i].y - 3;
            i++;

        }
        //Draw all blossoms at once
       int blossom = 0;
       while(blossom  < size){
            G_rgb(0.98,0.85,0.86);
             G_fill_circle(blossoms[blossom].x, blossoms[blossom].y, radius);
             blossom++;
       }
       */
       //which blossoms should fall?
       int total_to_fall = 20;
       update_blossoms_to_move(blossoms, to_fall, &next_index, indicies, &available, total_to_fall);

       //now blossoms should be altered as we want it to be, draw all the blossoms
       int index = 0;
       while(index < size){
            printf("In loop");
          //first be sure we draw all the stationary blossoms
          int draw = is_falling(to_fall, index);
          if(draw == 0){ //index not in the to_fall list
          //printf("stationary, ");
            G_rgb(0.98,0.85,0.86);
            G_fill_circle(blossoms[index].x, blossoms[index].y, radius);
          }
          //then change and draw all the in motions falling ones
          else{
            printf("fall, ");
            blossoms[index].y -= 3.0;
            G_rgb(0.98,0.85,0.86);
            G_fill_circle(blossoms[index].x, blossoms[index].y, radius);
          }

          //update hanging to be true as long as at least one blossom hasn't reached the ground
          if(blossoms[index].y > 0){
             hanging = true;
          }
          index++;
       }

        G_wait_key();
        test++;
    }
    printf("Went through draw loop: %i times", test);
}