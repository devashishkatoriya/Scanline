#include <iostream>
#include <graphics.h>

using namespace std;

#define LIMIT 20

/*
class Edge
{
public:
    int x1,x2,y1,y2;
    int flag;
};
*/

void polyRead(int x[],int y[],int *n)
{
m1: cout<<"\nEnter how many vertices : ";
    cin>>*n;
    if(*n>LIMIT || *n<2)
    {
        cout<<"\nToo many or Too few vertices entered.";
        goto m1;
    }
    cout<<"Enter the co-ordinates :- \n";
    for(int i=0;i<*n;i++)
    {
        cout<<"\n";
        cin>>x[i]>>y[i];
    }
}

void polyDraw(int x[],int y[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        line(x[i],y[i],x[i+1],y[i+1]);
    }
    line(x[n-1],y[n-1],x[0],y[0]);
}

//My Custom Scanline - Works only on Convex Polygons
void scanLine(int x[],int y[],int n)
{
    int i,j,len1,len2;
    float dx1,dx2,dy1,dy2,x1,y1,x2,y2;

    i = 1;
    while(i+1<=n-1)
    {
        dx1 = abs(x[i]-x[0]);
        dy1 = abs(y[i]-y[0]);
        if(dx1>=dy1)
            len1 = dx1;
        else
            len1 = dy1;
        dx1 = (x[i]-x[0])/len1;
        dy1 = (y[i]-y[0])/len1;
        x1 = x[0];
        y1 = y[0];


        dx2 = abs(x[i]-x[i+1]);
        dy2 = abs(y[i]-y[i+1]);
        if(dx2>=dy2)
            len2 = dx2;
        else
            len2 = dy2;
        dx2 = (x[i]-x[i+1])/len2;
        dy2 = (y[i]-y[i+1])/len2;
        x2 = x[i+1];
        y2 = y[i+1];

        j = 1;
        while(j<=len1 && j<=len2)
        {
            x1 = x1 + dx1;
            y1 = y1 + dy1;
            x2 = x2 + dx2;
            y2 = y2 + dy2;

            delay(10);
            line(x1,y1,x2,y2);
            j++;
        }
        i++;
    }

}


int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    char ch;
    int x[LIMIT],y[LIMIT],n;
    do
    {
        ch = 'y';
        cleardevice();
        polyRead(x,y,&n);
        polyDraw(x,y,n);
        scanLine(x,y,n);
        cout<<"\nDo you want to continue (y/n) ? ";
        cin>>ch;
    }while(ch=='y'||ch=='Y');

    closegraph();
    return 0;
}

//Sample Points
// 4 - 100 100 100 200 200 200 200 100
// 3 - 100 100 200 200 50 200
// 3 - 100 100 200 200 200 100
// 4 - 0 0 50 0 50 50 0 50

// 3 - 308 170 100 320 308 180
// 4 - 100 100 200 150 400 150 300 100
// 5 - 100 100 150 150 200 100 200 200 100 200 - Concave Polygon(not working)


/*
//ScanLine using Active Edges
 Edge ed[LIMIT],temped;
    int i, j, k, Ymin, Ymax, temp, inter_x[LIMIT], dx, dy, xx, yy;
    double m[LIMIT], x_int[LIMIT];
    Ymin = 480;
    Ymax = 0;

    //Find Ymax and Ymin
    for(i=0;i<n;i++)
    {
        if (Ymin > y[i])
        {
            Ymin = y[i];
        }
        if (Ymax < y[i])
        {
            Ymax = y[i];
        }
        ed[i].x1 = x[i];
        ed[i].y1 = y[i];
    }

    //store the edge info
    for(i=0;i<n-1;i++)
    {
        ed[i].x2 = ed[i + 1].x1;
        ed[i].y2 = ed[i + 1].y1;
        ed[i].flag = 0;
    }
    ed[n-1].x2 = ed[0].x1;
    ed[n-1].y2 = ed[0].y1;
    ed[n-1].flag = 0;


    //Check for y1>y2, if not interchange y1 and y2
    for(i=0;i<n;i++)
    {
        if(ed[i].y1 < ed[i].y2)
        {
            temp=ed[i].x1;
            ed[i].x1=ed[i].x2;
            ed[i].x2=temp;

            temp=ed[i].y1;
            ed[i].y1=ed[i].y2;
            ed[i].y2=temp;
        }
    }

    //Sorting the edges in the order of y1,y2,x1
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1;j++)
        {
            if(ed[j].y1<ed[j+1].y1)
            {
                temped = ed[j];
                ed[j] = ed[j+1];
                ed[j+1] = temped;
            }
            if(ed[j].y1==ed[j+1].y1)
            {
                if(ed[j].y2<ed[j+1].y2)
                {
                    temped = ed[j];
                    ed[j] = ed[j+1];
                    ed[j+1] = temped;
                }
                if (ed[j].y2==ed[j+1].y2)
                {
                    if(ed[j].x1<ed[j+1].x1)
                    {
                        temped = ed[j];
                        ed[j] = ed[j+1];
                        ed[j+1] = temped;
                    }
                }
            }
        }
    }

    //Calculating Inverse Slope of each edge and storing top
    for(i=0;i<n;i++)
    {
        dx = ed[i].x2 - ed[i].x1;
        dy = ed[i].y2 - ed[i].y1;

        if(dy==0)
        {
            m[i] = 0;
        }
        else
        {
            m[i] = dx/dy;
        }
        inter_x[i] = ed[i].x1;
    }

    //Making the Actual Edges
    yy = Ymax;
    while(yy>Ymin)
    {
        for (i = 0; i < n; i++)
        {
            if (yy > ed[i].y2 && yy <= ed[i].y1)
                ed[i].flag = 1;
            else
                ed[i].flag = 0;
            j = 0;
            for (i = 0; i < n; i++)
            {
                if (ed[i].flag == 1)
                {
                    if (yy == ed[i].y1)
                    {
                        x_int[j] = ed[i].x1;
                        j++;
                        if (ed[i - 1].y1 == yy && ed[i - 1].y1 < yy)
                        {
                            x_int[j] = ed[i].x1;
                            j++;
                        }
                        if (ed[i + 1].y1 == yy && ed[i + 1].y1 < yy)
                        {
                            x_int[j] = ed[i].x1;
                            j++;
                        }
                    }
                    else
                    {
                        x_int[j] = inter_x[i] + (-m[i]);
                        inter_x[i] = x_int[j];
                        j++;
                    }
                }
            }
        }
        //Sorting the X-intersections
        for(i=0;i<j;i++)
        {
            for(k=0;k<j-1;k++)
            {
                if(x_int[k]>x_int[k+1])
                {
                    temp = x_int[k];
                    x_int[k] = x_int[k+1];
                    x_int[k+1] = temp;
                }
            }
        }

        //Drawing the Actual Scan-Lines
        for(i=0;i<j;i=i+2)
        {
            line((int)x_int[i],yy,(int)x_int[i+1],yy);
        }
        yy--;
        delay(50);
    }
*/







/*
//Actual scanline fill algorithm
void polygon::fill()
{
	bresenhem b;
	int i,k,inter_x[LIMIT],temp,y,Ymax = 0,Ymin = 480;
	float m[LIMIT],dx,dy;

	for(i=0;i<n;i++)
	{
		if(Py[i]>=Ymax)
			Ymax = Py[i];
		if(Py[i]<=Ymin)
			Ymin = Py[i];
	}
	for(i=0;i<n-1;i++)
	{
		dx = Px[i+1] - Px[i];
		dy = Py[i+1] - Py[i];

		if(dx==0)
			m[i] = 0;
		if(dy==0)
			m[i] = 1;
		if((dx!=0) && (dy!=0))
			m[i] = dx/dy;
	}
	dx = Px[n-1] - Px[0];
	dy = Py[n-1] - Py[0];

	if(dx==0)
		m[n-1] = 0;
	if(dy==0)
		m[n-1] = 1;
	if((dx!=0) && (dy!=0))
		m[n-1] = dx/dy;

	for(y = Ymax;y>=Ymin;y--)
	{
		int cnt = 0;
		for(i=0;i<n;i++)
		{
			if(((Py[i]>y) && (Py[i+1]<=y))||((Py[i]<=y) && (Py[i+1]>y)))
			{
				inter_x[cnt] = Px[i] + (m[i]*(y-Py[i]));
				cnt++;
			}
		}
		for(k=0;k<cnt-1;k++)
		{
			for(i=0;i<cnt-1;i++)
			{
				if(inter_x[i]>inter_x[i+1])
				{
					temp = inter_x[i];
					inter_x[i] = inter_x[i+1];
					inter_x[i+1] = temp;
				}
			}
		}
		for(i=0;i<cnt-1;i++)
		{
			line(inter_x[i],y,inter_x[i+1],y);
			delay(10);
		}
	}
}
*/