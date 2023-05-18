#include <stdio.h>
#include <stdlib.h>


struct Point {
    double x, y;
};

struct RGB {
    double r, g, b;
};



void blossom_draw_save(struct Point blossoms[], int *index, struct Point p1, struct Point p2, struct Point p3, struct Point p4, int initial_radius ){
        //adjust colors to be one of three shades of pink
        int random = rand() % 3; //make 3 random numbers from 0 -2

        if(random == 0){
            G_rgb(0.87,0.647,0.643);//hot pink
        }
        else if (random == 1){
            G_rgb(0.95,0.76,0.76);//pink
        } else {
            G_rgb(0.98,0.85,0.86);//light pink
        }

        //TODO maybe we need to draw outside this function, all at once when we have the populated blossoms array
        //draw circles at the end points of each final square
        G_fill_circle(p1.x, p1.y, initial_radius);
        G_fill_circle(p2.x, p2.y, initial_radius);
        G_fill_circle(p3.x, p3.y, initial_radius);
        G_fill_circle(p4.x, p4.y, initial_radius);

        //populate array
        blossoms[(*index)] = p1;
        (*index)++;
        blossoms[(*index)] = p2;
        (*index)++;
        blossoms[(*index)] = p3;
        (*index)++;
        blossoms[(*index)] = p4;
        (*index)++;

}

//Initialize array of blossoms with empty points
void init_blossoms(struct Point array[], int size){
         struct Point init = {0,0};
         for(int i =0; i < size; i++){
            array[i] = init;
         }
}


//Draw all blossoms stored in an array of coordinates
void draw_blossoms(struct Point blossoms[], int size, int radius){
    int index = 0;
    while(index < size){
        G_rgb(0.98,0.85,0.86);
        G_fill_circle(blossoms[index].x, blossoms[index].y, radius);
        index++;
    }
}

//Draw all blossoms stored in an array of coordinates
void draw_leaves(struct Point blossoms[], int size, int radius){
    int index = 0;
    while(index < size){
        G_rgb(0,1,0);
        G_fill_circle(blossoms[index].x, blossoms[index].y, radius);
        index++;
    }
}


//get the size of indicies before calling this function
void select_random_indicies(int random[], int indicies[], int *available, int total){
    int count = 0;
    //for the requested number of random indicies to gather
    while (count < total){
            int last_index = *available -1;
            int random_i = (rand() % (*available-1)); //get a random number in the range of how big indicies is
            printf("RANDOM NUM: %d ", random_i);
            random[count] = indicies[random_i];
            if(random_i != last_index){
                //replace the value we just grabbed at the random index, with the value in the last index
                indicies[random_i] = indicies[last_index];
            }
            //always shrink the indicies available to grab, by 1, so that next time this gets called, last_index is one less
            *available -= 1;

        count++;
    }
/*
        printf("Testing to see what is in indicies[] at %d : ", count);
        for(int k = 0; k < *available; k++){
             printf("%d ", indicies[k]);
        }
        printf("\n");



    printf("Testing to see what we got in random IN FUNCTION: ");
    for(int k = 0; k < total; k++){
        printf("%d ", random[k]);
   }
   printf("\n");
*/
}

//I need to have a list of blossoms that have been selected to fall, so the ones that are not yet moving, stay still


int update_blossoms_to_move(struct Point blossoms[], int to_fall[], int next_index, int indicies[], int *available, int total_to_fall){
    int index = 0;
    int random[total_to_fall];
    for(int i = 0; i < total_to_fall; i++){
        random[i] = 0;
    }

    //randomly select num_select number of indicies
    if(total_to_fall <= *available-1){
         select_random_indicies(random, indicies, available, total_to_fall);
        //now we have access to both the filled random list, and the updated indicies list
        //available has shrunk as well
        //Now we want to update the to_fall list with what we got from random
        //go through random, and add what's there to the next available spot in to_fall
        printf("next_index: %d \n", next_index);

        while (index < total_to_fall){
                //update just the blossom at each index of the random array of index values
                to_fall[next_index] = random[index];
                printf("Random number added: %d \n", random[index]);
                next_index++;
                index++;
        }
    }
    else{
        //there are less blossoms left to add to to_fall than the requested amount
        //So just add the rest of what's in indicies to to_fall
        while(index < *available){
            to_fall[next_index] = indicies[index];
            next_index++;
            index++;
        }
    }
/*
    printf("Testing to see what we got in to_fall: ");
    for(int j = 0; j < next_index; j++){
        printf("%d ", to_fall[j]);
    }
    printf("\n");
*/
    return next_index;
}

int is_falling(int to_fall[], int blossom, int next_index){
    int count = 0;
    int found = 0;
    while(count < next_index){
        if (to_fall[count] == blossom){
            found = 1;
        }
        count++;
    }
    return found;
}

