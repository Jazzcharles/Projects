#include <bits/stdc++.h>
using namespace std;
int nCount = 0;
int Matrix[100][100];

void chessBoard(int tr, int tc, int dr, int dc, int size);

int main()
{
    int size,r,c,row,col;
    memset(Matrix,0,sizeof(Matrix));
    scanf("%d",&size);
    scanf("%d%d",&row,&col);
    chessBoard(0,0,row,col,size);

    for (r = 0; r < size; r++)
    {
        for (c = 0; c < size; c++)
        {
            printf("%2d ",Matrix[r][c]);
        }
        printf("\n");
    }

    return 0;
}

void chessBoard(int tr, int tc, int dr, int dc, int size)
{
    //tr and tc represent the top left corner's coordinate of the matrix
    int s,t;
    if (1 == size) {
    	//cout<<dr<<' '<<dc<<endl;	
		return;
	}
    s = size/2; //The number of grid the matrix's edge
    t = ++ nCount;
	
	cout<<t<<' '<<s<<endl;
    //locate the special  grid on bottom right corner
    if (dr < tr + s && dc < tc +s)
    {
        chessBoard(tr,tc,dr,dc,s);
    }
    else
    {
        Matrix[tr+s-1][tc+s-1] = t;
        chessBoard(tr,tc,tr+s-1,tc+s-1,s);
    }

    //locate the special  grid on bottom left corner
    if (dr < tr + s && dc >= tc + s )
    {
        chessBoard(tr,tc+s,dr,dc,s);
    }
    else
    {
        Matrix[tr+s-1][tc+s] = t;
        chessBoard(tr,tc+s,tr+s-1,tc+s,s);
    }

    //locate the special  grid on top right corner
    if (dr >= tr + s && dc < tc + s)
    {
        chessBoard(tr+s,tc,dr,dc,s);
    } 
    else
    {
        Matrix[tr+s][tc+s-1] = t;
        chessBoard(tr+s,tc,tr+s,tc+s-1,s);
    }

    //locate the special  grid on top left corner
    if (dr >= tr + s && dc >= tc + s)
    {
        chessBoard(tr+s,tc+s,dr,dc,s);
    } 
    else
    {
        Matrix[tr+s][tc+s] = t;
        chessBoard(tr+s,tc+s,tr+s,tc+s,s);
    }

}
/*
4
0 1
*/
