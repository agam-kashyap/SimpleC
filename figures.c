#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct{
	float x;
	float y;
}point;
point read_point();

typedef struct{
	point A;
	point B;
}line;
line read_line();

typedef struct{
	point A;
	point B;
	point C;
}triangle;
triangle read_triangle();

typedef struct{
	point C;
	float R;
}circle;
circle read_circle();

int circle_point( circle c1, point a);
int line_point( line l, point a);
int point_point(point a, point b);
int line_line(line l1, line l2);
int check_same_sign(line l, point a, point b);
int point_triangle(triangle T, point a);
int circle_circle(circle c1, circle c2);
int line_triangle(line l, triangle T);
int circle_line(line l, circle c);
int triangle_circle(triangle T, circle c);
int triangle_triangle(triangle T, triangle T1);

int main()
{
    int flag;
    char input1, input2, dummy;

    point p1, p2;
    line l1, l2;
    triangle t1, t2;
    circle c1, c2;

    scanf("%c",&input1);
    if(input1 == 'P')
        p1 = read_point();
    else if(input1 == 'L')
        l1 = read_line();
    else if(input1 == 'T')
        t1 = read_triangle();
    else if(input1 == 'C')
        c1 = read_circle();

    scanf("%c", &dummy);
    scanf("%c",&input2);
    if(input2 == 'P')
        p2 = read_point();
    else if(input2 == 'L')
        l2 = read_line();
    else if(input2 == 'T')
        t2 = read_triangle();
    else if(input2 == 'C')
        c2 = read_circle();

    if(input1 == 'P')
    {
        if(input2 == 'P')
            flag = point_point(p1,p2);
        else if(input2 == 'L')
            flag = line_point(l2,p1);
        else if(input2 == 'T')
            flag = point_triangle(t2,p1);
        else if(input2 == 'C')
            flag = circle_point(c2,p1);
    }
    else if(input1 == 'L')
    {
        if(input2 == 'P')
            flag = line_point(l1,p2);
        else if(input2 == 'L')
            flag = line_line(l1,l2);
        else if(input2 == 'T')
            flag = line_triangle(l1,t2);
        else if(input2 == 'C')
            flag = circle_line(l1,c2);
    }
    else if(input1 == 'T')
    {
        if(input2 == 'P')
            flag = point_triangle(t1,p2);
        else if(input2 == 'L')
            flag = line_triangle(l2,t1);
        else if(input2 == 'T')
            flag = triangle_triangle(t1,t2);
        else if(input2 == 'C')
            flag = triangle_circle(t1,c2);
    }
    else if(input1 == 'C')
    {
        if(input2 == 'P')
            flag = circle_point(c1,p2);
        else if(input2 == 'L')
            flag = circle_line(l2,c1);
        else if(input2 == 'T')
            flag = triangle_circle(t2,c1);
        else if(input2 == 'C')
            flag = circle_circle(c1,c2);
    }

    if(flag == 0)
    {
        printf("The primitives do not intersect.\n");
    }
    else if(flag == 1)
    {
        printf("The primitives intersect.\n");
    }
}

point read_point()
{
	point p;
	scanf("%f %f",&p.x,&p.y);
	return p;
}

line read_line()
{
	line l;
	scanf("%f %f %f %f",&l.A.x,&l.A.y,&l.B.x,&l.B.y);
	return l;
}

triangle read_triangle()
{
	triangle t;
	scanf("%f %f %f %f %f %f",&t.A.x,&t.A.y,&t.B.x,&t.B.y,&t.C.x,&t.C.y);
	return t;
}

circle read_circle()
{
	circle c;
	scanf("%f %f %f",&c.C.x,&c.C.y,&c.R);
	return c;
}

int triangle_circle(triangle T, circle c)
{
	line l1;   //point A and point B
	line l2;  	//point B and point C
	line l3;	//point C and point A
	l1.A.x = T.A.x;
	l1.A.y = T.A.y;
	l1.B.x = T.B.x;
	l1.B.y = T.B.y;

	l2.A.x = T.B.x;
	l2.A.y = T.B.y;
	l2.B.x = T.C.x;
	l2.B.y = T.C.y;

	l3.A.x = T.C.x;
	l3.A.y = T.C.y;
	l3.B.x = T.A.x;
	l3.B.y = T.A.y;

	if(circle_line(l1,c) == 1)
		return 1;
	else if(circle_line(l2,c) == 1)
		return 1;
	else if(circle_line(l3,c) == 1)
		return 1;
	else
		return 0;
}

int triangle_triangle(triangle T1, triangle T2)
{
	line l1;   //point A and point B
	line l2;  	//point B and point C
	line l3;	//point C and point A
	l1.A.x = T1.A.x;
	l1.A.y = T1.A.y;
	l1.B.x = T1.B.x;
	l1.B.y = T1.B.y;

	l2.A.x = T1.B.x;
	l2.A.y = T1.B.y;
	l2.B.x = T1.C.x;
	l2.B.y = T1.C.y;

	l3.A.x = T1.C.x;
	l3.A.y = T1.C.y;
	l3.B.x = T1.A.x;
	l3.B.y = T1.A.y;



	if(line_triangle(l1,T2) == 1)
		return 1;
	if(line_triangle(l2,T2) == 1)
		return 1;
	if(line_triangle(l3,T2) == 1)
		return 1;
	else
		return 0;
}

int circle_line(line l, circle c)
{
	point lp, rp;

	int dx = l.B.x - l.A.x;
	int dy = l.B.y - l.A.y;
	int dr = pow((pow(dx,2) + pow(dy,2)),0.5);
	int D = l.A.x*l.B.y - l.B.x*l.A.y;

	int sqrt_term = pow(c.R,2)*pow(dr,2) - pow(D,2);

	if(sqrt_term >= 0)
	{
		if(dy < 0)
		{
			lp.x = (D*dy - dx*(pow(sqrt_term,0.5)))/(pow(dr,2));
			lp.y = (-D*dx + abs(dy)*(pow(sqrt_term,0.5)))/(pow(dr,2));
			rp.x = (D*dy + dx*(pow(sqrt_term,0.5)))/(pow(dr,2));
			rp.y = (-D*dx - abs(dy)*(pow(sqrt_term,0.5)))/(pow(dr,2));
		}
		else
		{
			lp.x = (D*dy + dx*(pow(sqrt_term,0.5)))/(pow(dr,2));
			lp.y = (-D*dx + abs(dy)*(pow(sqrt_term,0.5)))/(pow(dr,2));
			rp.x = (D*dy - dx*(pow(sqrt_term,0.5)))/(pow(dr,2));
			rp.y = (-D*dx - abs(dy)*(pow(sqrt_term,0.5)))/(pow(dr,2));
		}

		int flag;
		if((l.A.x <= lp.x && l.B.x >= lp.x) || (l.A.x >= lp.x && l.B.x <= lp.x))
		{
			if((l.A.y <= lp.y && l.B.y >= lp.y) || (l.A.y >= lp.y && l.B.y <= lp.y))
			{
				return 1;
			}
			else
			{
				flag = 0;
			}
		}
		else
		{
			flag = 0;
		}

		if((l.A.x <= rp.x && l.B.x >= rp.x) || (l.A.x >= rp.x && l.B.x <= rp.x))
		{
			if((l.A.y <= rp.y && l.B.y >= rp.y) || (l.A.y >= rp.y && l.B.y <= rp.y))
			{
				return 1;
			}
			else
			{
				flag = 0;
			}
		}
		else
		{
			flag = 0;
		}

		if(flag == 0)
			return 0;
	}
	else
	{
		return 0;
	}
}

int check_same_sign(line l, point a, point b)
{
	float m = (l.B.y - l.A.y)/(l.B.x - l.A.x);
	float c = (l.B.x*l.A.y - l.A.x*l.B.y)/(l.B.x - l.A.x);


	if((a.y - m*a.x - c <= 0 && b.y - m*b.x - c <= 0) || (a.y - m*a.x - c >= 0 && b.y - m*b.x - c >= 0))
	{
		return 1;
	}
	else
		return 0;
}

int point_triangle(triangle T, point a)
{
	line l1;   //point A and point B
	line l2;  	//point B and point C
	line l3;	//point C and point A
	l1.A.x = T.A.x;
	l1.A.y = T.A.y;
	l1.B.x = T.B.x;
	l1.B.y = T.B.y;

	l2.A.x = T.B.x;
	l2.A.y = T.B.y;
	l2.B.x = T.C.x;
	l2.B.y = T.C.y;

	l3.A.x = T.C.x;
	l3.A.y = T.C.y;
	l3.B.x = T.A.x;
	l3.B.y = T.A.y;

/*	if(check_same_sign(l1, a, T.C) == 1)
	{
		if(check_same_sign(l2, a, T.A) == 1)
		{
			if(check_same_sign(l3, a, T.B ) == 1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}*/
	if(line_point(l1,a)==1)
	return 1;
	if(line_point(l2,a)==1)
	return 1;
	if(line_point(l3,a)==1)
	return 1;
	else
	return 0;
}

int circle_circle(circle c1, circle c2)
{
	int x_term = pow((c1.C.x - c2.C.x),2);
	int y_term = pow((c1.C.y - c2.C.y),2);

	int distance = pow(x_term+y_term,0.5);

	if( abs(c1.R - c2.R) <= distance && c1.R + c2.R >= distance)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int line_triangle(line l, triangle T)
{
	line l1;   //point A and point B
	line l2;  	//point B and point C
	line l3;	//point C and point A
	l1.A.x = T.A.x;
	l1.A.y = T.A.y;
	l1.B.x = T.B.x;
	l1.B.y = T.B.y;

	l2.A.x = T.B.x;
	l2.A.y = T.B.y;
	l2.B.x = T.C.x;
	l2.B.y = T.C.y;

	l3.A.x = T.C.x;
	l3.A.y = T.C.y;
	l3.B.x = T.A.x;
	l3.B.y = T.A.y;

	if(line_line(l1,l) == 1)
		return 1;
	else if(line_line(l2,l) == 1)
		return 1;
	else if(line_line(l3,l) == 1)
		return 1;
	else
		return 0;
}


int circle_point( circle c1, point a)
{
	int x_term = pow((pow(a.x,2)-pow(c1.C.x,2)),2);
	int y_term = pow((pow(a.y,2)-pow(c1.C.y,2)),2);
	int R = pow(c1.R,2);

	if(x_term+y_term <= R)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int line_point( line l, point a)
{
	float m = (l.B.y - l.A.y)/(l.B.x - l.A.x);
	float c = (l.B.x*l.A.y - l.A.x*l.B.y)/(l.B.x - l.A.x);
	float X;
	float Y = m*X + c;

	if(a.y == m*a.x + c)
	{
		if((l.A.x <= a.x && l.B.x >= a.x) || (l.A.x >= a.x && l.B.x <= a.x))
		{
			if((l.A.y <= a.y && l.B.y >= a.y) || (l.A.y >= a.y && l.B.y <= a.y))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int point_point(point a, point b)
{
	if(a.x == b.x && a.y == b.y)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int line_line(line l1, line l2)
{
	float m1 = (l1.B.y - l1.A.y)/(l1.B.x - l1.A.x);
	float c1 = (l1.B.x*l1.A.y - l1.A.x*l1.B.y)/(l1.B.x - l1.A.x);
	float m2 = (l2.B.y - l2.A.y)/(l2.B.x - l2.A.x);
	float c2 = (l2.B.x*l2.A.y - l2.A.x*l2.B.y)/(l2.B.x - l2.A.x);
	float x_term,y_term;

	if(l1.B.x - l1.A.x == 0 || l2.B.x - l2.A.x == 0)
	{
		if(l1.B.x - l1.A.x == 0)
		{
			x_term = l1.A.x;
			y_term = m2*x_term + c2;
		}
		else if(l2.B.x - l2.A.x == 0)
		{
			x_term = l2.A.x;
			y_term = m1*x_term + c1;
		}
		else
		{
			return 0;
		}
	}
	if(m1 == m2)
	{
		int flag;
		flag = line_point(l1,l2.A) + line_point(l1,l2.B) + line_point(l2,l1.A) + line_point(l2,l1.B);
		if (flag>0)
			return 1;
		else
			return 0;
	}
	else
	{
		x_term = (c2 - c1)/(m1 - m2);
		y_term = m1*x_term + c1;
	}

	if((l1.A.x <= x_term && l1.B.x >= x_term) || (l1.A.x >= x_term && l1.B.x <= x_term))
	{
		if((l1.A.y <= y_term && l1.B.y >= y_term) || (l1.A.y >= y_term && l1.B.y <= y_term))
		{
			if((l2.A.x <= x_term && l2.B.x >= x_term) || (l2.A.x >= x_term && l2.B.x <= x_term))
			{
				if((l2.A.y <= y_term && l2.B.y >= y_term) || (l2.A.y >= y_term && l2.B.y <= y_term))
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}

    //Hello
}
