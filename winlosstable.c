/*
 * プログラム名：課題1011(kadai1011.c）
 * 作成者：太田　夏織
 * 作成日：2023/11/06
 * 概 要 ：プロ野球勝敗表の表示
 */
#include <stdio.h>
#define  TEAMNUM  6

/* 構造体の定義 */
struct TEAM{
    char name[20];
    int win;
    int lose;
    int draw;
    double rate;
};
int main(void)
{
	struct TEAM team[TEAMNUM]; /* 構造体変数の宣言 */
	int    i, j, ret;
	
	/* データの入力 */
	for(i = 0; i < TEAMNUM; i++){
		/* チーム名の入力 */
		fflush(stdin);
		printf("チーム名(%d件目)>", i + 1);
		gets(team[i].name);

		/* 勝ち負け数の入力 */
		printf("勝数,負数,引分数>");
		fflush(stdin);
		ret = scanf("%d,%d,%d", &team[i].win, &team[i].lose, &team[i].draw);
		if(ret == 3){
			/* 勝率を計算する */
			if((team[i].win + team[i].lose) == 0){
				team[i].rate = 0.0;
			}else{
				team[i].rate = (double)team[i].win / (team[i].win + team[i].lose);
			}
		}else{
			puts("正しく入力して下さい");
			return -1;

		}
	}
	
	/* 勝率の降順にソートする */
	for(i = 0; i < TEAMNUM - 1; i++){
		for(j = i + 1; j < TEAMNUM; j++){
			if(team[i].rate < team[j].rate){
				struct TEAM w = team[i];
				team[i] = team[j];
				team[j] = w;
			}
		}
	}

	/* 勝敗表を表示する */
	puts("          ***  プロ野球勝敗表  ***");
	puts("+-----+--------------------+----+----+----+------+");
	puts("| 順位|    チーム名        |勝ち|負け|引分| 勝率 |");
	puts("+-----+--------------------+----+----+----+------+");
	for(i=0; i < TEAMNUM; i++){
		printf("|%4d |%-20s|%4d|%4d|%4d|%6.3f|\n"
		          ,i + 1, team[i].name, team[i].win, team[i].lose, team[i].draw, team[i].rate);
	}
	puts("+-----+--------------------+----+----+----+------+");

	int stop;
	scanf("%d",&stop);

	return 0;
}

/*
実行結果
kadai1011.exe
チーム名(1件目)>楽天 
勝数,負数,引分数>70,71,2
チーム名(2件目)>ロッテ
勝数,負数,引分数>70,68,5
チーム名(3件目)>日本ハム
勝数,負数,引分数>60,82,1
チーム名(4件目)>西武
勝数,負数,引分数>65,77,1
チーム名(5件目)>オリックス
勝数,負数,引分数>86,53,4
チーム名(6件目)>ソフトバンク
勝数,負数,引分数>71,69,3
          ***  プロ野球勝敗表  ***
+-----+--------------------+----+----+----+------+
| 順位|    チーム名        |勝ち|負け|引分| 勝率 |
+-----+--------------------+----+----+----+------+
|   1 |オリックス          |  86|  53|   4| 0.619|
|   2 |ロッテ              |  70|  68|   5| 0.507|
|   3 |ソフトバンク        |  71|  69|   3| 0.507|
|   4 |楽天                |  70|  71|   2| 0.496|
|   5 |西武                |  65|  77|   1| 0.458|
|   6 |日本ハム            |  60|  82|   1| 0.423|
+-----+--------------------+----+----+----+------+
*/
