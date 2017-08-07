#include <iostream>
#include<bits/stdc++.h>
using namespace std;


class Poligon;





class Point{
    public:
    Poligon* father;
double x,y;
double start_x,start_y;
Point(double x,double y,Poligon* father){
start_x=x;
start_y=y;
this-> father=father;
}

void step(double Ent_x,double Ent_y,double Ent_deg){//cout<<"yap";
x=Ent_x+start_x*sin(Ent_deg/180*acos(-1))+start_y*cos(Ent_deg/180*acos(-1));
y=Ent_y+start_y*sin(Ent_deg/180*acos(-1))-start_x*cos(Ent_deg/180*acos(-1));
//SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
//SDL_RenderDrawLine(gRenderer, x + SCREEN_WIDTH/2,y + SCREEN_HEIGHT/2,0,0);
//cout<<x<<" "<<y<<endl;
};
};
class Line;

class Line{
    public:
       /* Line(const Line &a={},const Line &b={}){

        if( a!=b){this->father=a.father;
        this->a=a.a;
        this->b=a.b;
        this->Name=a.Name;}
        }*/
    Poligon* father;
Point* a; Point *b;
string Name="WUT";
/*bool operator!=(const Line &b) const{
return a==b.a&&b==b.b
}*/
bool operator=( Line a){
this->father=a.father;
this->a=a.a;
this->b=a.b;
this->Name=a.Name;
}

};



class Poligon{
public:
//Object* father;
vector<Point> Points;
vector<Line> Lines;
bool waiting_for_delete=false;
};



class Event{
    public:

    bool v;
    double x;
    Line l;
    bool e;
    Line a;
    Line b;
};

function<bool (Line,Line)>  Compare_LineHeight(double loc_x){

return [loc_x](Line a,Line b){cout<<a.Name<<","<<b.Name<<endl;
  return  (loc_x-a.a->x)/(a.b->x-a.a->x)*a.a->y+(1-(loc_x-a.a->x)/(a.b->x-a.a->x))*a.b->y<(loc_x-b.a->x)/(b.b->x-b.a->x)*b.a->y+(1-(loc_x-b.a->x)/(b.b->x-b.a->x))*b.b->y
 ;
};

}

bool Compare_Events(Event a,Event b){
return a.x<b.x;
}


int Line_intersection(Line a,Line b){
if(sqrt((a.a->x-a.b->x)*(a.a->x-a.b->x)+(a.a->y-a.b->y)*(a.a->y-a.b->y))+sqrt((b.a->x-b.b->x)*(b.a->x-b.b->x)+(b.a->y-b.b->y)*(b.a->y-b.b->y))>
   sqrt((a.a->x-b.b->x)*(a.a->x-b.b->x)+(a.a->y-b.b->y)*(a.a->y-b.b->y))+sqrt((b.a->x-a.b->x)*(b.a->x-a.b->x)+(b.a->y-a.b->y)*(b.a->y-a.b->y)) &&
   sqrt((a.a->x-a.b->x)*(a.a->x-a.b->x)+(a.a->y-a.b->y)*(a.a->y-a.b->y))+sqrt((b.a->x-b.b->x)*(b.a->x-b.b->x)+(b.a->y-b.b->y)*(b.a->y-b.b->y))>
   sqrt((a.a->x-b.a->x)*(a.a->x-b.a->x)+(a.a->y-b.a->y)*(a.a->y-b.a->y))+sqrt((b.b->x-a.b->x)*(b.b->x-a.b->x)+(b.b->y-a.b->y)*(b.b->y-a.b->y))){
       double x1=a.a->x,x2=a.b->x,x3=b.a->x,x4=b.a->x;
       double y1=a.a->y,y2=a.b->y,y3=b.a->y,y4=b.a->y;
       return ((x3-x4)/(y3-y4)*(y3+y1+(x1*(y1-y2))/(x1-x2))-x3)/((y1-y2)*(x3-x4)/((x1-x2)*(y3-y4))-1);
    } return -1;
}

void Collision_Detection(vector<Poligon> Poligons)
{
    vector<Event > events;
    for(int a=Poligons.size(); a>0; a--)
        for(int b=0; b<Poligons[a-1].Lines.size(); b++){
            Event newa;
            newa.x=Poligons[a-1].Lines[b].a->x;
            newa.e=true;
            newa.l=Poligons[a-1].Lines[b];
            newa.v=true;
            events.push_back(newa);
            Event newb;
            newb.x=Poligons[a-1].Lines[b].b->x;
            newb.e=false;
            newb.v=true;
            newb.l=Poligons[a-1].Lines[b];
            events.push_back(newb);
        }
    sort(events.begin(),events.end(),Compare_Events);
    vector<Line> ranges;
    double loc_x=0;
    while(!events.empty())
    {





        loc_x=events[0].x;

        if(events[0].v )
        {     //    cout<<"dolgok"<<endl;
              Event* now;
            now=&events[0];
            int left=0;
            int right=ranges.size()-1;
            if(left>right){ranges.insert(ranges.begin(),now->l);}else
            while (left <= right)
            {cout<<"a"<<endl;
                int middle = (left + right) / 2;
                if ((loc_x-ranges[middle].a->x)/(ranges[middle].b->x-ranges[middle].a->x)*ranges[middle].a->y+(1-(loc_x-ranges[middle].a->x)/(ranges[middle].b->x-ranges[middle].a->x))*ranges[middle].b->y
                     >= (now->e?now->l.a:now->l.b)->y
                     && (loc_x-ranges[middle-1].a->x)/(ranges[middle-1].b->x-ranges[middle-1].a->x)*ranges[middle-1].a->y+(1-(loc_x-ranges[middle-1].a->x)/(ranges[middle-1].b->x-ranges[middle-1].a->x))*ranges[middle-1].b->y<
                    (now->e?now->l.a:now->l.b)->y)
                    if((loc_x-ranges[middle].a->x)/(ranges[middle].b->x-loc_x)*ranges[middle].a->y+(1-(loc_x-ranges[middle].a->x)/(ranges[middle].b->x-loc_x))*ranges[middle].b->y==(now->e?now->l.a:now->l.b)->y){
                            ranges.erase(ranges.begin()+middle);
                            if(Line_intersection(ranges[middle],ranges[middle-1])==-1){
                                Event news;
                                news.x=Line_intersection(ranges[middle],ranges[middle-1]);
                                news.a=ranges[middle-1];
                                news.b=ranges[middle];
                                news.v=false;
                                events.insert(lower_bound(events.begin(),events.end(),news,Compare_Events),news);
                            }
                        }else{
                            ranges.insert(ranges.begin()+middle,now->l);
                            if(Line_intersection(ranges[middle],ranges[middle-1])==-1){
                                Event news;
                                news.x=Line_intersection(ranges[middle],ranges[middle-1]);
                                news.a=ranges[middle-1];
                                news.b=ranges[middle];
                                news.v=false;
                                events.insert(lower_bound(events.begin(),events.end(),news,Compare_Events),news);
                            }
                            if(Line_intersection(ranges[middle],ranges[middle+1])==-1){
                                Event news;
                                news.x=Line_intersection(ranges[middle],ranges[middle+1]);
                                news.a=ranges[middle];
                                news.b=ranges[middle+1];
                                news.v=false;
                                events.insert(lower_bound(events.begin(),events.end(),news,Compare_Events),news);
                            }
                        }
                else if ((loc_x-ranges[middle].a->x)/(ranges[middle].b->x-loc_x)*ranges[middle].a->y+(1-(loc_x-ranges[middle].a->x)/(ranges[middle].b->x-loc_x))*ranges[middle].b->y > (now->e?now->l.a:now->l.b)->y)
                    right = middle - 1;
                else
                    left = middle + 1;
            }
        }
        else
        {   Event* now=&events[0];
            Line swapee;


            /*FUCK LOWER BOUND (WELL IF WITH LINES)*/
            cout<<distance(ranges.begin(),lower_bound(ranges.begin(),ranges.end(),now->a,Compare_LineHeight(loc_x)))<<endl;
            swapee=(*lower_bound(ranges.begin(),ranges.end(),now->a,Compare_LineHeight(loc_x)));
            Line swapee2;
            swapee2=(*lower_bound(ranges.begin(),ranges.end(),now->b,Compare_LineHeight(loc_x)));
            *lower_bound(ranges.begin(),ranges.end(),now->a,Compare_LineHeight(loc_x))=swapee2;
            *lower_bound(ranges.begin(),ranges.end(),now->b,Compare_LineHeight(loc_x))=swapee;

            if(lower_bound(ranges.begin(),ranges.end(),now->a,Compare_LineHeight(loc_x))!=ranges.begin() && Line_intersection(*lower_bound(ranges.begin(),ranges.end(),now->a,Compare_LineHeight(loc_x)),*(--lower_bound(ranges.begin(),ranges.end(),now->a,Compare_LineHeight(loc_x))))==-1){
                Event news;
                news.x=Line_intersection(*lower_bound(ranges.begin(),ranges.end(),now->a,Compare_LineHeight(loc_x)),*(--lower_bound(ranges.begin(),ranges.end(),now->a,Compare_LineHeight(loc_x))));
                news.a=*lower_bound(ranges.begin(),ranges.end(),now->a,Compare_LineHeight(loc_x));
                news.b=*(--lower_bound(ranges.begin(),ranges.end(),now->a,Compare_LineHeight(loc_x)));
                news.v=false;
                events.insert(lower_bound(events.begin(),events.end(),news,Compare_Events),news);
            }
            if(lower_bound(ranges.begin(),ranges.end(),now->b,Compare_LineHeight(loc_x))!=ranges.end() && Line_intersection(*lower_bound(ranges.begin(),ranges.end(),now->b,Compare_LineHeight(loc_x)),*(++lower_bound(ranges.begin(),ranges.end(),now->b,Compare_LineHeight(loc_x))))==-1){
                Event news;
                news.x=Line_intersection(*lower_bound(ranges.begin(),ranges.end(),now->b,Compare_LineHeight(loc_x)),*(++lower_bound(ranges.begin(),ranges.end(),now->b,Compare_LineHeight(loc_x))));
                news.a=*lower_bound(ranges.begin(),ranges.end(),now->b,Compare_LineHeight(loc_x));
                news.b=*(++lower_bound(ranges.begin(),ranges.end(),now->b,Compare_LineHeight(loc_x)));
                news.v=false;
                events.insert(lower_bound(events.begin(),events.end(),news,Compare_Events),news);
            }

        }
        events.erase(events.begin());
        for(int x=0;x<ranges.size();x++){cout<<ranges[x].Name<<",";}cout<<endl;
    }

};







int main()
{
Poligon a;
if(true){
Line A,B,C;
A.father=&a;
A.Name="Aranka0,0";
B.Name="Branka1,1";
C.Name="Cranka3,2";
B.father=&a;
C.father=&a;
Point p(0,0,&a),P(1,1,&a),q(3,2,&a);
a.Lines.push_back(A);a.Lines.push_back(B);a.Lines.push_back(C);
a.Points.push_back(p);a.Points.push_back(P);a.Points.push_back(q);
a.Lines[0].a=&a.Points[0];
a.Lines[0].b=&a.Points[1];
a.Lines[1].a=&a.Points[1];
a.Lines[1].b=&a.Points[2];
a.Lines[2].a=&a.Points[2];
a.Lines[2].b=&a.Points[0];
}
Poligon b;
if(true){
Line A,B,C;
A.father=&b;
B.father=&b;
C.father=&b;
A.Name="Artoise0,1";
B.Name="Brtoise1,0";
C.Name="Crtoise3,2";
Point p(0,1,&b),P(1,0,&b),q(3,2,&b);
b.Lines.push_back(A);b.Lines.push_back(B);b.Lines.push_back(C);
b.Points.push_back(p);b.Points.push_back(P);b.Points.push_back(q);
b.Lines[0].a=&b.Points[0];
b.Lines[0].b=&b.Points[1];
b.Lines[1].a=&b.Points[1];
b.Lines[1].b=&b.Points[2];
b.Lines[2].a=&b.Points[2];
b.Lines[2].b=&b.Points[0];
}
vector<Poligon> Poligons;
Poligons.push_back(a);
Poligons.push_back(b);
Collision_Detection(Poligons);
    return 0;
}
