#include "all.h"
int main(){
    FILE *f_count = fopen("song.txt","r");
    int count = 1;
    char tmp;
    while(!feof(f_count)){
        fscanf(f_count, "%c",&tmp);
        if(tmp == '\n') count++;
    }
    fclose(f_count);


    FILE *f = fopen("song.txt","r");
    char *line = NULL;
    song *list = calloc(count, sizeof(song));
    int i = 0;
    while(cgetline(&line,0,f)){
        list[i] = malloc(sizeof(struct song_t));
        process(line,list[i]);
        i++;
    }
    int choice = 0, choice_1, remove;
    char strr[1024], new_song[1024], new_singer[1024], new_musician[1024], new_year[1024];
    while(choice != 6){
        Menu();
        printf("Nhap vao lua chon cua ban: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            Thuoctinh();
            printf("Nhap vao lua chon cua ban: ");
            scanf("%d",&choice_1);
            if(choice_1 == 1)qsort(list,count,sizeof(song),compare_name);
            else if(choice_1 == 2) qsort(list,count,sizeof(song),compare_singer);
            else if(choice_1 == 3) qsort(list,count,sizeof(song),compare_musician);
            else if(choice_1 == 4) qsort(list,count,sizeof(song),compare_year);
            Head();
            PrintSong(list,count);
            break;


            case 2:
            Thuoctinh();
            printf("Nhap vao lua chon cua ban: ");
            scanf("%d",&choice_1);
            if(choice_1 == 1){
                printf("Nhap ten bai hat can tim: ");
                scanf("%s",strr);
                Search_name(list,strr,count);
            }
            else if(choice_1 == 2){
                printf("Nhap ten ca si can tim: ");
                scanf("%s",strr);
                Search_singer(list,strr,count);
            }
            else if(choice_1 == 3){
                printf("Nhap ten nhac si can tim: ");
                scanf("%s",strr);
                Search_musician(list,strr,count);
            }
            else if(choice_1 == 4){
                printf("Nhap nam can tim: ");
                scanf("%s",strr);
                Search_year(list,strr,count);
            }
            break;


            case 3:
            clear();
            printf("Them bai hat\n");
            printf("%s","Ten bai hat: ");
            scanf("%[^\n]s",new_song);
            clear();
            printf("%s", "Ten ca sy: ");
            scanf("%[^\n]s",new_singer);
            clear();
            printf("%s", "Ten nhac sy: ");
            scanf("%[^\n]s",new_musician);
            clear();
            printf("%s", "Nam sang tac: ");
            scanf("%[^\n]s",new_year);
            clear();
            count++;
            list = (song*)realloc(list,count*sizeof(song));
            list[count-1] = malloc(sizeof(struct song_t));
            Add(list[count-1],new_song,new_singer,new_musician,new_year);
            break;


            case 4:
            clear();
            printf("Ban muon xoa bai hat nao? ");
            scanf("%d",&remove);
            list[remove-1]->ap = 0;
            Save(list,count);
            break;

            case 5:
            PrintBin(list,count);
            break;
        }
    }
    fclose(f);
    return 0;
}