#include "tree_lib.h"



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
    //for each blossom, until we reach the ground redraw the blossoms at a lower point
    while(hanging){
        G_rgb(0.3, 0.3, 0.3);
        G_clear();
        redraw_tree_no_blossoms(p0, p1, distance, percent, depth);
        hanging = false;
        int i = 0;
        while(i  < size){
            blossoms[i].y = blossoms[i].y - 3;
            i++;
            if(blossoms[i].y > 0){
                hanging = true;
            }
        }
        //Draw all blossoms at once
       int blossom = 0;
       while(blossom  < size){
            G_rgb(0.98,0.85,0.86);
             G_fill_circle(blossoms[blossom].x, blossoms[blossom].y, radius);
             blossom++;
       }

        G_wait_key();
    }
}