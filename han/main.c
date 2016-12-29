#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

FILE *file;

typedef struct tower_seg
{
    int size;
    struct tower_seg *seg_under;
}Tower;

Tower* create_tower(int seg_amount)
{
    Tower *hanoi_first,*hanoi_last;
    hanoi_first=(Tower*)malloc(sizeof(Tower));
    int i=1;                       //first seg

        hanoi_first->size=i;
        hanoi_last=hanoi_first;
    while(i++<seg_amount)
    {
                     //segments 2nd to pre last
        hanoi_last->seg_under=(Tower*)malloc(sizeof(Tower));
        hanoi_last=hanoi_last->seg_under;
        hanoi_last->size=i;
    }
         //last segment
        hanoi_last->seg_under=NULL;             //marking as last seg by setting vaulue of next to NULL
        return hanoi_first;
}

int USRinput_seg_amount()
{
    char c;
    int seg_amount=0;
    while(seg_amount<1)
    {
        printf("Podaj wielkosc wiezy!\n");
        if(scanf("%d",&seg_amount)==0)
        {
            do {
                c = getchar();
              }
            while (!isdigit(c));
            ungetc(c, stdin);
        }

    }
    return seg_amount;
}

int can_be_moved(Tower *top1,Tower *top2, Tower *top3, int *target)
{
    if(top1!=NULL)
    {
        if(top1->size!=1)
        {
            if(top2!=NULL)
            {
                if(top1->size < top2->size)
                {
                    *target=2; return 1;
                }
            }else {*target=2; return 1;}

            if(top3!=NULL)
            {
                if(top1->size < top3->size)
                {
                    *target=3; return 1;
                }
            }else {*target=3; return 1;}
        }
    }

    if(top2!=NULL)
    {
        if(top2->size!=1)
        {
            if(top1!=NULL)
            {
                if(top2->size < top1->size)
                {
                    *target=1; return 2;
                }
            }else {*target=1; return 2;}

            if(top3!=NULL)
            {
                if(top2->size < top3->size)
                {
                    *target=3; return 2;
                }
            }else {*target=3; return 2;}
        }
    }

    if(top3!=NULL)
    {
        if(top3->size!=1)
        {
            if(top1!=NULL)
            {
                if(top3->size < top1->size)
                {
                    *target=1; return 3;
                }
            }else {*target=1; return 3;}

            if(top2!=NULL)
            {
                if(top3->size < top2->size)
                {
                    *target=2; return 3;
                }
            }else {*target=2; return 3;}
        }
    }

    if(1)
        printf("very bad");
}

int count(Tower *tow)
{
    int amount=0;
    while(tow)
    {
        amount++;
        tow=tow->seg_under;
    }
    return amount;
}

void move(Tower **from, Tower **to)
{
    if(*from!=NULL)
    {

    Tower *tmp;
    tmp=(*from)->seg_under;
    (*from)->seg_under=*to;
    (*to)=(*from);
    (*from)=tmp;
    }
}

void print_towers(Tower *top1,Tower *top2,Tower *top3)
{
    system("cls");          //clears screen
    printf("I\tII\tIII\n\n");
    while(top1!=NULL || top2!=NULL || top3!=NULL)
    {
        if(top1!=NULL)
            {printf("%d\t",top1->size);top1=top1->seg_under;}else printf("\t");

        if(top2!=NULL)
            {printf("%d\t",top2->size);top2=top2->seg_under;}else printf("\t");
        if(top3!=NULL)

            {printf("%d\n",top3->size);top3=top3->seg_under;}else printf("\n");
    }
}

void print_toFile(Tower *top1,Tower *top2,Tower *top3, FILE *file)
{
    fprintf(file,"I\tII\tIII\n\n");
    while(top1!=NULL || top2!=NULL || top3!=NULL)
    {
        if(top1!=NULL)
            {fprintf(file,"%d\t",top1->size);
            top1=top1->seg_under;
            }else fprintf(file,"\t");

        if(top2!=NULL)
            {fprintf(file,"%d\t",top2->size);
            top2=top2->seg_under;
            }else fprintf(file,"\t");

        if(top3!=NULL)

            {fprintf(file,"%d\n",top3->size);
            top3=top3->seg_under;
            }else fprintf(file,"\n");
    } fprintf(file,"\n");
}

void user_move(Tower **top1, Tower **top2, Tower **top3,int selected, int target)
{
    if(selected==1)
    {
        if(target==2)      // top2 and top3 can be both null
        {
            move(top1,top2);
        }else move(top1,top3);
    }else if(selected==2)
            {
                if(target==1)
                   {
                move(top2,top1);
                   }else move(top2,top3);

            }else if(target==1)
                    {
                        move(top3,top1);
                    }else move(top3,top2);

}

void user_solve(Tower *hanoi_first, int seg_amount)
{
    Tower *top1,*top2=NULL,*top3=NULL, *being_moved, *to;
    top1=hanoi_first;

    int segs_top3,selected,target,valid_move;
    char c;


    while(segs_top3!=seg_amount)
    {
        print_towers(top1,top2,top3);
        print_toFile(top1,top2,top3,file);
        while(selected<1 || selected>3 || target<1 || target>3 || selected==target || valid_move!=1)
              {
                    valid_move=1;

                    printf("\nPodaj nr stosu z ktorego przesunac: ");
                    if(scanf("%d",&selected)==0)
                    {
                        do{
                            c=getchar();
                        }while(!isdigit(c));
                        ungetc(c,stdin);
                    }

                    printf("\nPodaj nr stosu bedacy celem: "); scanf("%d",&target);

                        if(selected==1)
                        {
                            being_moved=top1;
                        }else if(selected==2)
                                {
                                    being_moved=top2;
                                }else if(selected==3)
                                {
                                    being_moved=top3;
                                }

                        if(target==1)
                        {
                            to=top1;
                        }else if(target==2)
                                {
                                    to=top2;
                                }else if(target==3)
                                {
                                    to=top3;
                                }



                        if(being_moved==NULL)
                        {
                            valid_move=0;
                        }
                        if(selected<1 ||selected>3 || target<1 || target>3)
                           {
                               valid_move=0;
                           }else
                                    if(to!=NULL && being_moved!=NULL)
                                    {
                                        if(being_moved->size > to->size)
                                            valid_move=0;
                                    }

                        if(valid_move==0)
                        {
                            printf("\nNiedozwolony ruch!");
                        }
              }valid_move=0;

        user_move(&top1,&top2,&top3,selected,target);
        segs_top3=count(top3);
    }
    print_towers(top1,top2,top3);
    print_toFile(top1,top2,top3,file);
}

int solve_hanoi(Tower *hanoi_first,int seg_amount)
{
    int wait;
    printf("Podaj opoznienie (w milisekundach) miedzy kolejnymi ruchami: ");scanf("%d",&wait);system("cls");
    if(seg_amount<1)
        return -1;

    Tower *top1, *top2=NULL, *top3=NULL;
    int segs_top3=0, from,to;
    top1=hanoi_first;

       while(segs_top3!=seg_amount)
       {
            print_towers(top1,top2,top3);
            Sleep(wait);
            segs_top3=0;
             if(top1!=NULL)
                 {if(top1->size==1 && segs_top3!=seg_amount)                  //moving smallest seg to the next tower
                 {
                     if(seg_amount%2==0)
                        move(&top1,&top2);else move(&top1,&top3);

                        printf("W TOP1"); Sleep(750);
                     segs_top3=count(top3);
                     print_towers(top1,top2,top3);
                     Sleep(wait);

                     if(segs_top3!= seg_amount)
                     {
//                         printf("Waht"); Sleep(750);
                     from=can_be_moved(top1,top2,top3,&to);
                     user_move(&top1,&top2,&top3,from,to);
                            print_towers(top1,top2,top3);
                            Sleep(wait);
                     }
                 }
             }
         if(top2!=NULL)
             {if(top2->size==1 && segs_top3!=seg_amount)                  //moving smallest seg to the next tower
             {
                 if(seg_amount%2==0)
                 move(&top2,&top3);else move(&top2,&top1);

                 segs_top3=count(top3);
                 print_towers(top1,top2,top3);
                 Sleep(wait);

                     printf("W TOP2"); Sleep(750);
                if(segs_top3!= seg_amount)
                {
                    from=can_be_moved(top1,top2,top3,&to);
                    user_move(&top1,&top2,&top3,from,to);
                    segs_top3=count(top3);

                    print_towers(top1,top2,top3);
                    Sleep(wait);
                }
             }
         }

        if(top3!=NULL)
             {if(top3->size==1 && segs_top3!=seg_amount)                  //moving smallest seg to the next tower
             {
                printf("W TOP3"); Sleep(750);

                 if(seg_amount%2==0)
                 move(&top3,&top1);else move(&top3,&top2);

                segs_top3=count(top3);
                 print_towers(top1,top2,top3);
                 Sleep(wait);

                segs_top3=count(top3);
                if(segs_top3!= seg_amount)
                {
                    from=can_be_moved(top1,top2,top3,&to);
                    user_move(&top1,&top2,&top3,from,to);
                    print_towers(top1,top2,top3);
                    Sleep(wait);
                }

             }
         }


       }
    return 0;
}

int main()
{
    file=fopen("hanoi.txt","w");
    int amount, select=1;
    char c;

    while(select!=0)
    {
        amount=USRinput_seg_amount();
        Tower *top1=create_tower(amount );
        system("cls");
        printf("0 Koniec programu\n1 Zobacz rozwiazanie\n2 Sprobuj rozwiazac\nPodaj numer: ");
        if(scanf("%d",&select)==0)
        {
            do{
                c=getchar();
            }while(!isdigit(c));
            ungetc(c,stdin);
        }
        if(select==1)
                {system("cls");solve_hanoi(top1,amount);system("cls");}
        if(select==2)
                {system("cls");user_solve(top1,amount);system("cls");}
    }
    close(file);
    return 0;
}
