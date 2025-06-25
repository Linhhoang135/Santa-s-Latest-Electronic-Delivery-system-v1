#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
struct sled {
    int x,
        y,
        orientation,
        totalDistance;
};
void initialise_map(char map[30][30]){
    int i;
    int j;
    for (i=0;i<30;i++){
        for(j=0;j<30;j++){
            map[i][j]= '.';
        }
    }
}
void populate_map(FILE *mapfile,char map[30][30]){
    int x;
    int y;
    char o;
    if (mapfile!= NULL){
        char lineOfMap[9];
        while(fgets(lineOfMap,9, mapfile)!= NULL){
            sscanf(lineOfMap,"%d,%d,%c",&x,&y,&o);
            map[x][y]=o;
        } 
    }
}
void print_map(char map[30][30]){
    int a;
    int b;
    for (a=29;a>-1;a--){
        for(b=0;b<30;b++){
            printf("%c", map[b][a]);
        }
        printf("\n");
    } 
}
int process_command(FILE*comfile,char map[30][30], struct sled *p_sled){
    int turn;
    int move;
    if (comfile!= NULL){
        char lineOfCom[12];
        while(fgets(lineOfCom,12, comfile)!= NULL){
            if (strncmp(lineOfCom,"TURN",4)==0){
                sscanf(lineOfCom,"TURN %d",&turn);
                p_sled->orientation = p_sled->orientation + turn;
                while (p_sled->orientation>=360){
                    p_sled->orientation=p_sled->orientation-360;
                }
            }
            else if (strncmp(lineOfCom,"FORWARD",7)==0){
                sscanf(lineOfCom,"FORWARD %d",&move);
                p_sled->totalDistance=p_sled->totalDistance+move;
                if(p_sled->orientation==0){
                    p_sled->y=p_sled->y+move;

                }
                if(p_sled->orientation==90){
                    p_sled->x=p_sled->x+move;
                }
                if(p_sled->orientation==180){
                    p_sled->y=p_sled->y-move;

                }
                if(p_sled->orientation==270){
                    p_sled->x=p_sled->x-move;

                }
            }    
        }       
    }
    return 0;
}
void print_sled(struct sled my_sled){
    printf("sled status:\n");
    printf("location %d,%d\n", my_sled.x,my_sled.y);
    printf("orientation %d degrees\n", my_sled.orientation);
    printf("distance travelled %d squares\n", my_sled.totalDistance);
    printf("end of sled status.\n");
}
void print_symbol(char map[30][30], struct sled my_sled){
    char sym;
    sym = map[my_sled.x][my_sled.y];
    printf("sled is flying over symbol %c\n", sym);
}
int is_over_symbol (char map[30][30], struct sled my_sled, char overSym){
    overSym =map[my_sled.x][my_sled.y]; 
    if (strcmp(&overSym,".")==0){
        return 0;
    }
    else{
        return 1;
    }
}
int extended_process_command(FILE*comfile,char map[30][30], struct sled *p_sled){
    int turn;
    int move;
    int noCom=0;
    char lo;
    int cmp;
    char *tower = "T";
    if (comfile!= NULL){
        char lineOfCom[12];
        while(fgets(lineOfCom,12, comfile)!= NULL){
            if (strncmp(lineOfCom,"TURN",4)==0){
                noCom++;
                sscanf(lineOfCom,"TURN %d",&turn);
                p_sled->orientation = p_sled->orientation + turn;
                while (p_sled->orientation>=360){
                    p_sled->orientation=p_sled->orientation-360;
                }
            }
            else if (strncmp(lineOfCom,"FORWARD",7)==0){
                noCom++;
                sscanf(lineOfCom,"FORWARD %d",&move);
                p_sled->totalDistance=p_sled->totalDistance+move;
                if(p_sled->orientation==0){
                    p_sled->y=p_sled->y+move;
                }
                if(p_sled->orientation==90){
                    p_sled->x=p_sled->x+move;
                }
                if(p_sled->orientation==180){
                    p_sled->y=p_sled->y-move;
                }
                if(p_sled->orientation==270){
                    p_sled->x=p_sled->x-move;
                }
            }
            else if (strncmp(lineOfCom,"BACK",4)==0){
                noCom++;
                sscanf(lineOfCom,"BACK %d",&move);
                p_sled->totalDistance=p_sled->totalDistance+move;
                if(p_sled->orientation==0){
                    p_sled->y=p_sled->y-move;
                }
                if(p_sled->orientation==90){
                    p_sled->x=p_sled->x-move;
                }
                if(p_sled->orientation==180){
                    p_sled->y=p_sled->y+move;
                }
                if(p_sled->orientation==270){
                    p_sled->x=p_sled->x+move;
                }
            }
            lo = map[p_sled->x][p_sled->y];
            if(strcmp(&lo,tower)==90){
                p_sled->x=0;
                p_sled->y=0;
                p_sled->orientation=0;
                p_sled->totalDistance=0;
                printf("WARNING: This route will fly over a tower. Route aborted.\n");
                return noCom;
            }
        }
    }    
    return noCom; 
}
int main(){
    struct sled my_sled;
    my_sled.x = 0;
    my_sled.y = 0;
    my_sled.orientation = 0;
    my_sled.totalDistance = 0;
    struct sled *p_sled = &my_sled;
    char map[30][30];
    char overSym;
    initialise_map(map);
    FILE *mapfile;
    mapfile = fopen("map.txt","r+");
    populate_map(mapfile,map);
    fclose(mapfile);
    print_map(map);
    FILE *comfile;
    comfile = fopen("sledcommands.txt","r+");
    //process_command(comfile,map,p_sled);
    extended_process_command(comfile,map,p_sled);
    fclose(comfile);
    print_sled(my_sled);
    print_symbol(map,my_sled);
    is_over_symbol(map,my_sled,overSym);
}
