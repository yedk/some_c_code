#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
enum bool{false,true
};

struct location1
{
 char* pointx;
 char* pointy;
 char* time;
 char* date;
 char* place;
 double p_x;
 double p_y; 
} ;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//get to_radian;
double to_radian(double x)
{
	return x*(3.14159/180);
}
//get chord_length;
double chord_length(double lat1,double lat2,double long1,double long2)
{
	double chord_length;
	chord_length = sin(to_radian(lat1-lat2)/2)*sin(to_radian(lat1-lat2)/2)+cos(to_radian(lat1))*cos(to_radian(lat2))*sin(to_radian(long2-long1)/2)*sin(to_radian(long2-long1)/2);
	return chord_length;
}
//get angle_distance;
double angle_distance(double chord_length)
{
	double angle_distance;
	angle_distance = 2*atan2(sqrt(chord_length),sqrt(1-chord_length));
	return angle_distance;
}
//get distance;
double Dist(double lat1,double lat2,double long1,double long2)
{
	double dist;
	dist = 6371000*angle_distance(chord_length(lat1,lat2,long1,long2));
	return dist;
}
//get speed;
double Speed(double dist)
{
	return dist/30;
}

int main(int argc, char *argv[]) {
	
 	char filename[]="test0.txt";
 	FILE *fp;
 	char*StrLine[1024];
 	int a;
 	char stage1[]="Stage 1";
 	char header[] ="=========";
 	char point[] ="Trajectory starting point: ";
 	char time[] = "Trajectory starting time : ";
 	char date[] = "Trajectory starting date : ";
	struct location1 l;
	char delim[] =" ";
	double p_x;
	char i=0;
	char *Str1;
	char *Str;
	char stage2[]="Stage 2";
	char place_pre[10];
	char place_now[10];
	char place_max_pre[10];
	char place_max_now[10]; 
	enum bool flag=0;
	char *p_max_pre;
	char *p_max_now; 
	
	double lat1,lat2;
	double long1,long2;
	double dist,speed;
	double dist_max;

 	if((fp=fopen(filename,"r"))==NULL)
 	{
	 	printf("error!\n");
	 	return -1;
	 }
	while(!feof(fp))
	{
	 fgets(StrLine,55,fp);
	 //printf("%d:\n",i);
	// printf("%s",StrLine);
	 l.date=strtok(StrLine,delim);
	 l.time =strtok(NULL,delim);
	 l.pointx =strtok(NULL,delim);
	 l.pointy =strtok(NULL,delim);
	 l.place = strtok(NULL,delim);
	// l.p_x = atof(l.pointx);
	// l.p_y = atof(l.pointy);
	 lat1 = lat2;
	 long1 =long2;
	 lat2 = atof(l.pointx);
	 long2 = atof(l.pointy);
	 strcpy(place_pre,place_now);
	 strcpy(place_now,l.place);
	 //*place_pre = *(place_now);
	 //while(*l.place++)
	// *place_now = *(l.place);
	
	 if(flag)
	 {
	 	printf("%s\n",stage2);
	 	printf("%s\n",header);
	 };
	 if(i>0)
	 {
	 	flag=0;
	 	dist = Dist(lat1,lat2,long1,long2);
	 	if(dist>dist_max)
	 	{
	 		dist_max=dist;
	 		strcpy(place_max_pre,place_pre);
	 		strcpy(place_max_now,place_now);
		 }
	 	speed =Speed(dist);
	 	printf("Trajectory segment %02d : length: %06.2f,speed: %05.2f\n",i,dist,speed);
	 }
	 else
	 {
	 	printf("%s\n",stage1);
	 	printf("%s\n",header);
	 	printf("%s",point);
	 	printf("<%s,%s>\n",l.pointx,l.pointy);
	 	printf("%s",time);
	 	printf("%s\n",l.time);
	 	printf("%s",date);
	 	printf("%s\n",l.date);
	 	flag = true;
	 }
	 i++;
	}
	p_max_pre = strtok(place_max_pre,"\n");
	p_max_now = strtok(place_max_now,"\n"); 
	printf("Stage 3\n");
	printf("======\n");
	printf("Number of trajectory segments:%d\n",i-1);
	printf("Trajectory segment with longest length:[%s,%s]\n",p_max_pre,p_max_now); 
	
 	fclose(fp);
	return 0;
}
