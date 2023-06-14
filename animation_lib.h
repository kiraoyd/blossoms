#include "tree_lib.h"
#include <math.h>

int SWIDTH = 1000;
int SHEIGHT = 1000;
int ground = 75;
#define FRAME_SAVE 100

void draw_background(int width, int height){
    //Draw lines from the bottom of the screen to the top, in a gradient of color
    double r,g,b, rw,gw,bw,rb,gb,bb;
    rw = 1.0;
    gw = 1.0;
    bw = 1.0;

//    rb = 52.0/255.0;
//    gb = 79.0/255.0;
//    bb = 235.0/255.0;

    rb = 13.0/255.0;
    gb = 20.0/255.0;
    bb = 94.0/255.0;

    //start with while
    r = rw;
    g = gw;
    b = bw;

    double blend_factor = 0; //0 is closer to white, 1 to blue
    int y = 0;
    int x_start = 0;
    int x_end = width - 1;

    G_clear();
    //fill screen from bottom up
    while (y < height){
        //blend colors
        r = (1-blend_factor) * rb + blend_factor* rw;
        g = (1-blend_factor) * gb + blend_factor* gw;
        b = (1-blend_factor) * bb + blend_factor* bw;
        //draw line
        G_rgb(r,g,b);
        G_line(x_start, y, x_end, y);
        blend_factor += 0.0003;
        y += 1;
    }

    //draw ground
    double rg,gg,bg; //for brown ground

    rg = 56.0/255.0;
    gg = 37.0/255.0;
    bg = 38.0/255.0;

    //start with white
    r = rw;
    g = gw;
    b = bw;
    blend_factor = 0; //0 is closer to white, 1 to blue
    y = 0;
    x_start = 0;
    x_end = width - 1;
    while (y < 150){
        //blend colors
        r = (1-blend_factor) * rg + blend_factor* rw;
        g = (1-blend_factor) * gg + blend_factor* gw;
        b = (1-blend_factor) * bg + blend_factor* bw;
        //draw line
        G_rgb(r,g,b);
        G_line(x_start, y, x_end, y);
        blend_factor += 0.003;
        y += 1;
    }

     //draw sun
        double rs,gs,bs; //for yellow sun

        rs = 247.0/255.0;
        gs = 215.0/255.0;
        bs = 5.0/255.0;

        //start with white
        r = rw;
        g = gw;
        b = bw;
        blend_factor = 0; //0 is closer to white, 1 to yellow
        y = 0;
        double x_center = 800;
        double y_center = 800;
        int radius = 50;
        while (radius > 0){
            //blend colors
            r = (1-blend_factor) * rw + blend_factor* rs;
            g = (1-blend_factor) * gw + blend_factor* gs;
            b = (1-blend_factor) * bw + blend_factor* bs;
            //draw line
            G_rgb(r,g,b);
            G_circle(x_center, y_center, radius);
            blend_factor += 0.05;
            radius -= 1;
        }



}

//Increase size of all blossoms and draw
int grow_blossoms(struct Point blossoms[], double radius, int target, double increment, int size, int current_frame ){
    char frame_name[FRAME_SAVE]; //holds the frame_name
    int frames = FRAME_SAVE;
    while (radius < target){
        int count = 0;
        sprintf(frame_name, "img%04d.bmp", current_frame); //create a sequential framing scheme for the mpeg
        //draw all the blossoms/leaves
        while(count < size){
            if (count % 2 == 0){
                G_rgb(74.0/255.0, 103.0/255.0, 65.0/255.0);
            } else if (count % 3 == 0){
                G_rgb(9.0/255.0, 121.0/255.0, 105/255.0);
            } else if (count % 5 == 0) {
                G_rgb(79.0/255.0, 121.0/255.0, 66/255.0);
            } else{
                //G_rgb(170.0/255.0, 255.0/255.0, 0/255.0);
                G_rgb(34.0/255.0, 139.0/255.0, 34.0/255.0);
            }

            G_fill_circle(blossoms[count].x, blossoms[count].y, radius);
            //draw_flower(blossoms[count].x, blossoms[count].y, 1);
            count++;
        }
        //G_wait_key();
        G_save_to_bmp_file(frame_name);
        current_frame++;
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


int fall(struct Point blossoms[], int size, struct Point p0, struct Point p1, double distance, double percent, double depth, int radius){
    //animate blossoms falling from front tree
    bool hanging = true;
    double rate = 20.0;
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
    int count = 0;
    char frame_name[FRAME_SAVE]; //holds the frame_name
    int frames = FRAME_SAVE;
    while(hanging){
       sprintf(frame_name, "img%04d.bmp", count); //create a sequential framing scheme for the mpeg

//        G_rgb(0.3, 0.3, 0.3);
        //G_clear();
        draw_background(SWIDTH, SHEIGHT);

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
          if(blossoms[index].y <= ground){
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
              blossoms[index].y -= rate;
              G_rgb(0.98,0.85,0.86);
              /* TODO trying with flower
              G_fill_circle(blossoms[index].x, blossoms[index].y, radius);
              */
              draw_flower(blossoms[index].x, blossoms[index].y, 1);
          }

          //update hanging to be true as long if at least one blossom hasn't reached the ground, keeps us in the loop
          if(blossoms[index].y > ground){
             hanging = true;
          }
          index++;
       }
        //G_wait_key();
        G_save_to_bmp_file(frame_name);
        count++;
    }
    return count;

}

