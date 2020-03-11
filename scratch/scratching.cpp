#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>

typedef struct scratch_map {

  int n;
  int h;
  int w;
  int x0;
  int y0;

  int **data;

} scratch_map;

typedef struct scratch_tile {

  int n;
  int x1;
  int y1;
  int x2;
  int y2;

} scratch_tile;

void fill_up(std::vector<scratch_map> *maps, scratch_map *map1, int *qx, int *qy, int num)
{
	int cc=2;
	int h=map1->h;
	int w=map1->w;

	int x,y,xx,yy;
	int ga[30][30];
	memset(ga,0,sizeof(ga));
	int l=0;
	int r=0;

	//std::vector<scratch_map*> map2_tmp;
	scratch_tile tile1;
	scratch_map map2;
	tile1.n = num;
	map2.n = num;
	int i,j;
	printf("buOK1!\n");
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
			printf("%d ",map1->data[i][j]);
		printf("\n");
	}
	for(i=0;i<h;i++)
		for(j=0;j<w;j++)
		{
			if(map1->data[i][j] == 1 && ga[i][j] == 0)
			{
				//printf("buOK2!\n");
				r++; qx[r]=i; qy[r]=j; //first elem in this scratch
				ga[i][j]=cc;
				tile1.x1=i;
				tile1.y1=j;
				tile1.x2=i;
				tile1.y2=j;

				while(l<r)
				{
				//printf("buOK3!\n");
					l++; x=qx[l]; y=qy[l];
				//printf("l: %d, x: %d, y: %d\n",l,x,y);

					//up
					//printf("up!\n");
					xx=x-1; yy=y;
					if(xx >=0 && yy>=0 && xx<h && yy<w)
						if(map1->data[xx][yy] == 1 && ga[xx][yy] == 0)
						{
							r++; qx[r]=xx; qy[r]=yy;
							ga[xx][yy]=cc;
							if(xx<tile1.x1) tile1.x1=xx;
							if(xx>tile1.x2) tile1.x2=xx;
							if(yy<tile1.y1) tile1.y1=yy;
							if(yy>tile1.y2) tile1.y2=yy;
						}

					//down
					//printf("down!\n");
					xx=x+1; yy=y;
					if(xx >=0 && yy>=0 && xx<h && yy<w)
						if(map1->data[xx][yy] == 1 && ga[xx][yy] == 0)
						{
							r++; qx[r]=xx; qy[r]=yy;
							ga[xx][yy]=cc;
							if(xx<tile1.x1) tile1.x1=xx;
							if(xx>tile1.x2) tile1.x2=xx;
							if(yy<tile1.y1) tile1.y1=yy;
							if(yy>tile1.y2) tile1.y2=yy;
						}

					//left
					//printf("left!\n");
					xx=x; yy=y-1;
					if(xx >=0 && yy>=0 && xx<h && yy<w)
						if(map1->data[xx][yy] == 1 && ga[xx][yy] == 0)
						{
							r++; qx[r]=xx; qy[r]=yy;
							ga[xx][yy]=cc;
							if(xx<tile1.x1) tile1.x1=xx;
							if(xx>tile1.x2) tile1.x2=xx;
							if(yy<tile1.y1) tile1.y1=yy;
							if(yy>tile1.y2) tile1.y2=yy;
						}

					//right
					//printf("right!\n");
					xx=x; yy=y+1;
					if(xx >=0 && yy>=0 && xx<h && yy<w)
						if(map1->data[xx][yy] == 1 && ga[xx][yy] == 0)
						{
							r++; qx[r]=xx; qy[r]=yy;
							ga[xx][yy]=cc;
							if(xx<tile1.x1) tile1.x1=xx;
							if(xx>tile1.x2) tile1.x2=xx;
							if(yy<tile1.y1) tile1.y1=yy;
							if(yy>tile1.y2) tile1.y2=yy;
						}
					//printf("end!\n");
				} //end while

				map2.data = new int*[tile1.x2 - tile1.x1 + 1];
				map2.data[0] = new int[(tile1.x2 - tile1.x1 + 1)*(tile1.y2 - tile1.y1 + 1)];
				map2.h = tile1.x2 - tile1.x1 + 1;
				map2.w = tile1.y2 - tile1.y1 + 1;
				map2.x0 = tile1.x1;
				map2.y0 = tile1.y1;
				for(x=tile1.x1;x<=tile1.x2;x++)
				{
					map2.data[x-tile1.x1] = &map2.data[0][(x-tile1.x1)*map2.w];
					for(y=tile1.y1;y<=tile1.y2;y++)
					{
						//printf("x: %d, y: %d\n",x,y);
						map2.data[x-tile1.x1][y-tile1.y1] = map1->data[x][y];
						if(ga[x][y]!=ga[i][j]) map2.data[x-tile1.x1][y-tile1.y1]=0;
					}
				}
				cc++;

				//map2_tmp.push_back(map2);
				maps->push_back(map2);
				//if()
			}
		}

	//*maps = map2_tmp;
}

int check_bound(int x, int y, int **data, int h, int w)
{
	int xx,yy;
	int ans=0;
	int ans1=0;

	xx=x-1; yy=y;
	if(xx == -1)
	{
		ans++;
	}
	else
	{
		if(data[xx][yy] == 1)
		{
			ans++;
			ans1++;
		}
		else
		{
			if((yy == 0 || data[xx][yy-1] == 0) && (yy == w-1 || data[xx][yy+1] == 0)) ans++;
		}
	}

	xx=x+1; yy=y;
	if(xx == h)
	{
		ans++;
	}
	else
	{
		if(data[xx][yy] == 1)
		{
			ans1++;
			ans++;
		}
		else
		{
			if((yy == 0 || data[xx][yy-1] == 0) && (yy == w-1 || data[xx][yy+1] == 0)) ans++;
		}
	}

	xx=x; yy=y-1;
	if(yy == -1)
	{
		ans++;
	}
	else
	{
		if(data[xx][yy] == 1)
		{
			ans1++;
			ans++;
		}
		else
		{
			if((xx == 0 || data[xx-1][yy] == 0) && (xx == h-1 || data[xx+1][yy] == 0)) ans++;
		}
	}

	xx=x; yy=y+1;
	if(yy == w)
	{
		ans++;
	}
	else
	{
		if(data[xx][yy] == 1)
		{
			ans1++;
			ans++;
		}
		else
		{
			if((xx == 0 || data[xx-1][yy] == 0) && (xx == h-1 || data[xx+1][yy] == 0)) ans++;
		}
	}

	if((ans == 4 && ans1 >= 2) || ans1 == 3)
		return 1;
	else
		return 0;
}

void scratching(std::vector<scratch_map> *maps, std::vector<scratch_tile> *tiles, int num, scratch_map *map1)
{
	int len=maps->size();

	int x,y,xx,yy;
	int i;
	int x1,y1,x2,y2;
	int min_x,min_y,max_x,max_y;

	scratch_map map2;
	scratch_tile tile1;
	tile1.n = num;
	//int **data_bk;
	int cc_0;
	int size1;
	size1=tiles->size();
	for(i=0;i<maps->size();i++)
	{
		for(int size=size1;size<tiles->size();size++)
		{
			tile1=(*tiles)[size];

			if((tile1.x2 - tile1.x1) * (tile1.y2 - tile1.y1) > 25)
			{
				if((tile1.x2 - tile1.x1) > (tile1.y2 - tile1.y1))
				{
					x=tile1.x2;
					tile1.x2 = (tile1.x1 + tile1.x2) / 2;
					(*tiles)[size] = tile1;
					tile1.x1 = tile1.x2 + 1;
					tile1.x2 = x;
					tiles -> push_back(tile1);
					tile1=(*tiles)[size];
				}
				else
				{
					y=tile1.y2;
					tile1.y2 = (tile1.y1 + tile1.y2) / 2;
					(*tiles)[size] = tile1;
					tile1.y1 = tile1.y2 + 1;
					tile1.y2 = y;
					tiles -> push_back(tile1);
					tile1=(*tiles)[size];
				}
			}
			printf("x1: %d, y1: %d, x2: %d, y2: %d\n",tile1.x1,tile1.y1,tile1.x2,tile1.y2);
			for(x=tile1.x1;x<tile1.x2;x++)
			{
				for(y=tile1.y1;y<tile1.y2;y++)
					printf("%d ", map1->data[x][y]);
				printf("\n");
			}
		}
		size1=tiles->size();

		//printf("1buOK%d!\n",i);
		map2 = (*maps)[i];
		printf("x0: %d, y0: %d, h: %d, w: %d\n",map2.x0,map2.y0,map2.h,map2.w);
		for(x=0;x<map2.h;x++)
		{
			for(y=0;y<map2.w;y++)
				printf("%d ",map2.data[x][y]);
			printf("\n");
		}
		printf("\n");

		if(map2.h*map2.w <=9)
		{
			tile1.x1=map2.x0;
			tile1.y1=map2.y0;
			tile1.x2=map2.x0+map2.h;
			tile1.y2=map2.y0+map2.w;
			tiles->push_back(tile1);
			continue;
		}

		cc_0=0;
		for(x=0;x<map2.h;x++)
			for(y=0;y<map2.w;y++)
			{
				if(map2.data[x][y] == 0)
					if(check_bound(x,y,map2.data,map2.h,map2.w) == 1)
					{
						map2.data[x][y] = 2;
					}
					else cc_0++;
			}

		if(cc_0 <= 2)
		{
			tile1.x1=map2.x0;
			tile1.y1=map2.y0;
			tile1.x2=map2.x0+map2.h;
			tile1.y2=map2.y0+map2.w;
			tiles->push_back(tile1);
			continue;
		}
		
		//printf("2buOK%d!\n",i);

		x1=0;
		y1=0;
		x2=map2.h;
		y2=map2.w;

		if(map2.data[x1][y1]!=0)
		{
			xx=x1;
			yy=y1;
			while(xx < x2 && map2.data[xx][y1] != 0) xx++;
			while(yy < y2 && map2.data[x1][yy] != 0) yy++;

			tile1.x1=x1+map2.x0;
			tile1.y1=y1+map2.y0;
			tile1.x2=xx+map2.x0;
			tile1.y2=yy+map2.y0;
			tiles->push_back(tile1);
			//printf("x1: %d, y1: %d, x2: %d, y2: %d\n",tile1.x1,tile1.y1,tile1.x2,tile1.y2);

			min_x=x2;
			min_y=y2;
			max_x=x1;
			max_y=y1;
			for(x=x1;x<x2;x++)
				for(y=y1;y<y2;y++)
				{
					if(x >= x1 && x < xx && y >= y1 && y < yy) map2.data[x][y]=0;
					if(map2.data[x][y] != 0)
					{
						if(x<min_x) min_x=x;
						if(x>max_x) max_x=x;
						if(y<min_y) min_y=y;
						if(y>max_y) max_y=y;
					}
				}

			x1=min_x;
			x2=max_x+1;
			y1=min_y;
			y2=max_y+1;
			if(x1>=x2 || y1>=y2) continue;
		}
		//printf("x1: %d, y1: %d, x2: %d, y2: %d\n",x1,y1,x2,y2);

		//printf("4buOK%d!\n",i);
		if(map2.data[x2-1][y2-1]!=0)
		{
			xx=x2-1;
			yy=y2-1;
			while(xx >= x1 && map2.data[xx][y2-1] != 0) xx--;
			while(yy >= y1 && map2.data[x2-1][yy] != 0) yy--;

			tile1.x1=map2.x0+xx+1;
			tile1.y1=map2.y0+yy+1;
			tile1.x2=map2.x0+x2;
			tile1.y2=map2.y0+y2;
			tiles->push_back(tile1);

			min_x=x2;
			min_y=y2;
			max_x=x1;
			max_y=y1;
			for(x=x1;x<x2;x++)
				for(y=y1;y<y2;y++)
				{
					if(x > xx && x < x2 && y > yy && y < y2) map2.data[x][y]=0;
					if(map2.data[x][y] != 0)
					{
						if(x<min_x) min_x=x;
						if(x>max_x) max_x=x;
						if(y<min_y) min_y=y;
						if(y>max_y) max_y=y;
					}
				}

			x1=min_x;
			x2=max_x+1;
			y1=min_y;
			y2=max_y+1;
			if(x1>=x2 || y1>=y2) continue;
		}

		if(map2.data[x1][y2-1]!=0)
		{
			xx=x1;
			yy=y2-1;
			while(xx < x2 && map2.data[xx][y2-1] != 0) xx++;
			while(yy >= y1 && map2.data[x1][yy] != 0) yy--;

			tile1.x1=map2.x0+x1;
			tile1.y1=map2.y0+yy+1;
			tile1.x2=map2.x0+xx;
			tile1.y2=map2.y0+y2;
			tiles->push_back(tile1);

			min_x=x2;
			min_y=y2;
			max_x=x1;
			max_y=y1;
			for(x=x1;x<x2;x++)
				for(y=y1;y<y2;y++)
				{
					if(x >= x1 && x < xx && y > yy && y < y2) map2.data[x][y]=0;
					if(map2.data[x][y] != 0)
					{
						if(x<min_x) min_x=x;
						if(x>max_x) max_x=x;
						if(y<min_y) min_y=y;
						if(y>max_y) max_y=y;
					}
				}

			x1=min_x;
			x2=max_x+1;
			y1=min_y;
			y2=max_y+1;
			if(x1>=x2 || y1>=y2) continue;
		}

		if(map2.data[x2-1][y1]!=0)
		{
			xx=x2-1;
			yy=y1;
			while(xx >= x1 && map2.data[xx][y1] != 0) xx--;
			while(yy < y2 && map2.data[x2-1][yy] != 0) yy++;

			tile1.x1=map2.x0+xx+1;
			tile1.y1=map2.y0+y1;
			tile1.x2=map2.x0+x2;
			tile1.y2=map2.y0+yy;
			tiles->push_back(tile1);

			min_x=x2;
			min_y=y2;
			max_x=x1;
			max_y=y1;
			for(x=x1;x<x2;x++)
				for(y=y1;y<y2;y++)
				{
					if(x > xx && x < x2 && y >= y1 && y < yy) map2.data[x][y]=0;
					if(map2.data[x][y] != 0)
					{
						if(x<min_x) min_x=x;
						if(x>max_x) max_x=x;
						if(y<min_y) min_y=y;
						if(y>max_y) max_y=y;
					}
				}

			x1=min_x;
			x2=max_x+1;
			y1=min_y;
			y2=max_y+1;
			if(x1>=x2 || y1>=y2) continue;
		}

		if(map2.data[x2-1][y1]!=0)
		{
			xx=x2-1;
			yy=y1;
			while(xx >= x1 && map2.data[xx][y1] != 0) xx--;
			while(yy < y2 && map2.data[x2-1][yy] != 0) yy++;

			tile1.x1=map2.x0+xx+1;
			tile1.y1=map2.y0+y1;
			tile1.x2=map2.x0+x2;
			tile1.y2=map2.y0+yy;
			tiles->push_back(tile1);

			min_x=x2;
			min_y=y2;
			max_x=x1;
			max_y=y1;
			for(x=x1;x<x2;x++)
				for(y=y1;y<y2;y++)
				{
					if(x > xx && x < x2 && y >= y1 && y < yy) map2.data[x][y]=0;
					if(map2.data[x][y] != 0)
					{
						if(x<min_x) min_x=x;
						if(x>max_x) max_x=x;
						if(y<min_y) min_y=y;
						if(y>max_y) max_y=y;
					}
				}

			x1=min_x;
			x2=max_x+1;
			y1=min_y;
			y2=max_y+1;
			if(x1>=x2 || y1>=y2) continue;
		}

		if(map2.data[x1][y2-1]!=0)
		{
			xx=x1;
			yy=y2-1;
			while(xx < x2 && map2.data[xx][y2-1] != 0) xx++;
			while(yy >= y1 && map2.data[x1][yy] != 0) yy--;

			tile1.x1=map2.x0+x1;
			tile1.y1=map2.y0+yy+1;
			tile1.x2=map2.x0+xx;
			tile1.y2=map2.y0+y2;
			tiles->push_back(tile1);

			min_x=x2;
			min_y=y2;
			max_x=x1;
			max_y=y1;
			for(x=x1;x<x2;x++)
				for(y=y1;y<y2;y++)
				{
					if(x >= x1 && x < xx && y > yy && y < y2) map2.data[x][y]=0;
					if(map2.data[x][y] != 0)
					{
						if(x<min_x) min_x=x;
						if(x>max_x) max_x=x;
						if(y<min_y) min_y=y;
						if(y>max_y) max_y=y;
					}
				}

			x1=min_x;
			x2=max_x+1;
			y1=min_y;
			y2=max_y+1;
			if(x1>=x2 || y1>=y2) continue;
		}

		if(map2.data[x2-1][y2-1]!=0)
		{
			xx=x2-1;
			yy=y2-1;
			while(xx >= x1 && map2.data[xx][y2-1] != 0) xx--;
			while(yy >= y1 && map2.data[x2-1][yy] != 0) yy--;

			tile1.x1=map2.x0+xx+1;
			tile1.y1=map2.y0+yy+1;
			tile1.x2=map2.x0+x2;
			tile1.y2=map2.y0+y2;
			tiles->push_back(tile1);

			min_x=x2;
			min_y=y2;
			max_x=x1;
			max_y=y1;
			for(x=x1;x<x2;x++)
				for(y=y1;y<y2;y++)
				{
					if(x > xx && x < x2 && y > yy && y < y2) map2.data[x][y]=0;
					if(map2.data[x][y] != 0)
					{
						if(x<min_x) min_x=x;
						if(x>max_x) max_x=x;
						if(y<min_y) min_y=y;
						if(y>max_y) max_y=y;
					}
				}

			x1=min_x;
			x2=max_x+1;
			y1=min_y;
			y2=max_y+1;
			if(x1>=x2 || y1>=y2) continue;
		}

		if(map2.data[x1][y1]!=0)
		{
			xx=x1;
			yy=y1;
			while(xx < x2 && map2.data[xx][y1] != 0) xx++;
			while(yy < y2 && map2.data[x1][yy] != 0) yy++;

			tile1.x1=map2.x0+x1;
			tile1.y1=map2.y0+y1;
			tile1.x2=map2.x0+xx;
			tile1.y2=map2.y0+yy;
			tiles->push_back(tile1);

			min_x=x2;
			min_y=y2;
			max_x=x1;
			max_y=y1;
			for(x=x1;x<x2;x++)
				for(y=y1;y<y2;y++)
				{
					if(x >= x1 && x < xx && y >= y1 && y < yy) map2.data[x][y]=0;
					if(map2.data[x][y] != 0)
					{
						if(x<min_x) min_x=x;
						if(x>max_x) max_x=x;
						if(y<min_y) min_y=y;
						if(y>max_y) max_y=y;
					}
				}

			x1=min_x;
			x2=max_x+1;
			y1=min_y;
			y2=max_y+1;
			if(x1>=x2 || y1>=y2) continue;
		}

		if((x2-x1)*(y2-y1) <=25)
		{
			tile1.x1=map2.x0+x1;
			tile1.y1=map2.y0+y1;
			tile1.x2=map2.x0+x2;
			tile1.y2=map2.y0+y2;
			tiles->push_back(tile1);
			continue;
		}
		else
		{
			xx=x2;
			int tt=1;
			while(tt)
			{
				xx--;
				for(yy=y1;yy<y2;yy++)
					if(map2.data[xx-1][yy] != map2.data[xx][yy])
					{
						tt=0;
						break;
					}
			}
			tile1.x1=map2.x0+xx;
			tile1.x2=map2.x0+x2;
			yy=y1;
			while(map2.data[xx][yy] == 0) yy++;
			tile1.y1=map2.y0+yy;
			yy=y2-1;
			while(map2.data[xx][yy] == 0) yy--;
			tile1.y2=map2.y0+yy+1;
			tiles->push_back(tile1);

			map2.h=xx-x1;
			map2.w=y2-y1;
			map2.x0=map2.x0+x1;
			map2.y0=map2.y0+y1;
			for(x=0;x<map2.h;x++)
				for(y=0;y<map2.w;y++)
					if(map2.data[x1+x][y1+y] != 0) map2.data[x][y]=1;
					else map2.data[x][y]=0;

			maps->push_back(map2);

		}

	}// end for i

	for(int size=size1;size<tiles->size();size++)
	{
		tile1=(*tiles)[size];

		if((tile1.x2 - tile1.x1) * (tile1.y2 - tile1.y1) > 25)
		{
			if((tile1.x2 - tile1.x1) > (tile1.y2 - tile1.y1))
			{
				x=tile1.x2;
				tile1.x2 = (tile1.x1 + tile1.x2) / 2;
				(*tiles)[size] = tile1;
				tile1.x1 = tile1.x2 + 1;
				tile1.x2 = x;
				tiles -> push_back(tile1);
				tile1=(*tiles)[size];
			}
			else
			{
				y=tile1.y2;
				tile1.y2 = (tile1.y1 + tile1.y2) / 2;
				(*tiles)[size] = tile1;
				tile1.y1 = tile1.y2 + 1;
				tile1.y2 = y;
				tiles -> push_back(tile1);
				tile1=(*tiles)[size];
			}
		}
		printf("x1: %d, y1: %d, x2: %d, y2: %d\n",tile1.x1,tile1.y1,tile1.x2,tile1.y2);
		for(x=tile1.x1;x<tile1.x2;x++)
		{
			for(y=tile1.y1;y<tile1.y2;y++)
				printf("%d ", map1->data[x][y]);
			printf("\n");
		}
	}

	return;
}

int main(int argc, char **argv)
{
	char *filename, *outputname;
	if(argc > 1) filename=argv[1];
	if(argc > 2) outputname=argv[2];

	std::vector<scratch_map> maps;

	int n,height,width;

	FILE* fp=fopen(filename,"r");

	fscanf(fp,"%d",&n);

	fscanf(fp,"%d%d",&height,&width);
	scratch_map* map1;

	int i,j,x,y;
	int *qx = new int[1000];
	int *qy = new int[1000];

	std::vector<scratch_tile> tiles;

	printf("OK!\n");
	for(i=0;i<n;i++)
	{
		maps.resize(0);
		map1 = new scratch_map();
		map1->h = height;
		map1->w = width;
		map1->n = i;
		map1->data = new int*[height];
		map1->data[0] = new int[height*width];

		printf("OK%d!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n",i);
		for(x=0;x<height;x++)
		{
			map1->data[x] = &map1->data[0][x*width];
			for(y=0;y<width;y++)
				fscanf(fp,"%d",&map1->data[x][y]);
		}

		fill_up(&maps,map1,qx,qy,i);

		//for(j=0;j<maps.size();j++)
		//{
		//	printf("x0: %d, y0: %d, h: %d, w: %d\n",maps[j].x0,maps[j].y0,maps[j].h,maps[j].w);
		//	for(x=0;x<maps[j].h;x++)
		//	{
		//		for(y=0;y<maps[j].w;y++)
		//			printf("%d ",maps[j].data[x][y]);
		//		printf("\n");
		//	}
		//	printf("\n");
		//}
		scratching(&maps,&tiles,i,map1);
		//maps.push_back(map1);
	}

	FILE *fp2=fopen(outputname,"w");

	for(i=0;i<tiles.size();i++)
	{
		fprintf(fp2, "%d %d %d %d %d\n", tiles[i].n+1, tiles[i].x1, tiles[i].y1, tiles[i].x2, tiles[i].y2);
		if((tiles[i].x2-tiles[i].x1)*(tiles[i].y2-tiles[i].y1) > 25)
			printf("%d %d %d %d %d\n", tiles[i].n+1, tiles[i].x1, tiles[i].y1, tiles[i].x2, tiles[i].y2);
	}


	return 0;
}