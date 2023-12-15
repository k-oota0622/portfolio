/*
 *  プログラム名：kadai1041.c
 * 作成者：太田　夏織
 * 作成日：2023/11/06
 *  概　要：売上管理におけるABC分析レポートを作成する
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* マクロ定義 */
#define  MAX_RECORD 10                  /* 最大レコード件数 */
enum rank { RANK_A = 80, RANK_B = 95};  /* ランク列挙体 */

/* 構造体定義 */
typedef struct _Sales{
	char name[20];        /* 品名 */
	int suryo;        /* 数量 */
	int tanka;        /* 単価 */
	int uriage;        /* 年間売上高 */
	int total;        /* 売上高累計 */
	double ratio;        /* 累計構成比 */ 
	char rank;        /* ランク     */
}Sales;

int uriage_total;           /* 年間売上高合計 */

/* 関数のプロトタイプ宣言 */
int input_Sales(Sales *p);
void sort_Sales (Sales *p, int c);
void disp_report(Sales *p, int c);
char get_rank(double ratio);

/*****************************
 * メイン関数
 *****************************/
int main(void){
	
	Sales uriage[MAX_RECORD] = {0};           //売上構造体配列
	int count;      //入力件数
	
	count = input_Sales(uriage);
	if(count > 0){
		/* 入力データが存在すれば、売上高の降順に整列しレポートを表示する */
		sort_Sales(uriage, count);   
		disp_report(uriage, count);  
	}

	int stop;
	scanf("%d",&stop);	//画面ストップ用

	return 0;
}

/*
 * 関数名：input_Sales()
 * 引　数：売上構造体配列のアドレス（ポインタ）
 * 戻り値：入力件数
 * 機　能：データを入力する
 */
int input_Sales(Sales *p)
{
	int count = 0;
	int ret;
	
	/* 最大件数までデータを入力する */
	while(count < MAX_RECORD){
		
		printf("商品(終了:Ctrl+Z)>");
		fflush(stdin);
		ret = scanf("%s", p->name);
		
		/* EOFなら入力終了 */
		if(ret == EOF){
			break;
		}
		
		printf("数量>");
		fflush(stdin);
		ret = scanf("%d", &p->suryo);
		/* エラーチェック(０以上であること) */
		if(p->suryo < 0 || ret != 1){
			puts("年間販売数は0以上を入力して下さい");
			continue;
		}
			
		printf("単価>");
		fflush(stdin);
		ret = scanf("%d", &p->tanka);
		/* エラーチェック（０以上であること） */
		if(p->tanka < 0 || ret != 1){
			puts("単価は0以上を入力して下さい");
			continue;
		}
              
			
		/* 売上高を計算し、売り上げ合計を求める */
		p->uriage = p->suryo * p->tanka;
		uriage_total += p->uriage;
		count++;
	    p++;
	}

	return count;
}
 

/*
 * 関数名：sort_Sales()
 * 引　数：売上構造体配列のアドレス（ポインタ）、入力件数
 * 戻り値：なし（関数内で書き換えする）
 * 機　能：売上データを売上高の降順に整列する
 */
void sort_Sales(Sales *p, int c) 
{
	int i, j;
	
	for(i = 0; i < c-1; i++){
		for(j = i + 1; j < c; j++){
			/* 構造体単位に入れ替える */
			if((p + i)->uriage < (p + j)->uriage){
				Sales w = *(p + i); 
			    *(p + i) = *(p + j);
				*(p + j) = w;
			}
		}
	}
	
}

/*
 * 関数名：disp_report()
 * 引　数：売上構造体配列のアドレス（ポインタ）、入力件数
 * 戻り値：なし
 * 機　能：売上分析表を表示する
 */
void disp_report(Sales *p, int c)
{
	int i; 
	static int sum=0;  /* 構成比累計を求める */
	
	puts("      ***  売 上 分 析 表  ***");
	puts("+------------------------------+----+----+--------+----------+------+------+");
	puts("|       商  品  名             |数量|単価| 売上高 |売上高累計|構成比|ランク|");
	puts("+------------------------------+----+----+--------+----------+------+------+");
	for(i = 0; i < c; i++){
		sum += p->uriage;
		p->total = sum;
		p->ratio = (double)p->total / uriage_total * 100; 
		p->rank = get_rank(p->ratio);                      

		printf("|%-30s|%4d|%4d|%8d|%10d|%6.1f|  %c   |\n",
		        p->name, p->suryo, p->tanka, p->uriage, p->total, p->ratio, p->rank);
		p++;
	}
	puts("+------------------------------+----+----+--------+----------+------+------+");
	printf("|                              |  合 計  |%8d|\n", uriage_total);
	puts("+------------------------------+----+----+--------+");

}

/*
 * 関数名：get_rank
 * 引　数：構成比（実数）
 * 戻り値：ランク（文字）
 * 機　能：ランクを判別する
 */
char get_rank(double ratio)
{
	char  rank;
	if(0 <= ratio && ratio <= RANK_A){
		rank='A';
	}else if(RANK_A < ratio && ratio <= RANK_B){
		rank='B';
	}else if(RANK_B < ratio && ratio <= 100){
		rank='C';
	}
	return rank;
}

/*
実行結果
kadai1041.exe
商品(終了:Ctrl+Z)>商品1
数量>110
単価>2
商品(終了:Ctrl+Z)>商品2
数量>60
単価>40
商品(終了:Ctrl+Z)>商品3
数量>10
単価>4
商品(終了:Ctrl+Z)>商品4
数量>130
単価>1
商品(終了:Ctrl+Z)>商品5
数量>50
単価>12
商品(終了:Ctrl+Z)>商品6
数量>1
単価>25
商品(終了:Ctrl+Z)>商品7 
数量>10
単価>2
商品(終了:Ctrl+Z)>商品8 
数量>150
単価>2
商品(終了:Ctrl+Z)>商品9
数量>20
単価>2
商品(終了:Ctrl+Z)>商品10
数量>50
単価>1
      ***  売 上 分 析 表  ***
+------------------------------+----+----+--------+----------+------+------+
|       商  品  名             |数量|単価| 売上高 |売上高累計|構成比|ランク|
+------------------------------+----+----+--------+----------+------+------+
|商品2                         |  60|  40|    2400|      2400|  62.7|  A   |
|商品5                         |  50|  12|     600|      3000|  78.4|  A   |
|商品8                         | 150|   2|     300|      3300|  86.3|  B   |
|商品1                         | 110|   2|     220|      3520|  92.0|  B   |
|商品4                         | 130|   1|     130|      3650|  95.4|  C   |
|商品10                        |  50|   1|      50|      3700|  96.7|  C   |
|商品9                         |  20|   2|      40|      3740|  97.8|  C   |
|商品3                         |  10|   4|      40|      3780|  98.8|  C   |
|商品6                         |   1|  25|      25|      3805|  99.5|  C   |
|商品7                         |  10|   2|      20|      3825| 100.0|  C   |
+------------------------------+----+----+--------+----------+------+------+
|                              |  合 計  |    3825|
+------------------------------+----+----+--------+
*/