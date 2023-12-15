/*
 * プログラム名：課題741(kadai741.c）
 * 作成者：太田　夏織
 * 作成日：2023/10/23
 * 概  要：Ｃ言語タイピング練習プログラム
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* マクロ定義 */
#define LENGTH       12
#define MAX_KEYWORD  32
#define MAX_QUESTION 10
#define UNUSED  0
#define USED    1

/* 関数プロトタイプ */
void init_status(int *p);
int create_question(int *p);
int check(char *p, char *q);

/* main関数 */
int main(void)
{
	/* 出題候補をポインタ配列で定義する */
	char *keyword[] = { "auto",     "break",    "case"   ,  "char",
				        "const",    "continue", "default",  "do",
				        "double",   "else",     "enum",     "extern",
				        "float",    "for",      "goto",     "if",
				        "int",      "long",     "register", "return",
				        "short",    "signed",   "sizeof",   "static",
				        "struct",   "switch",   "typedef",  "union",
				        "unsigned", "void",     "volatile", "while"
					  };

	char input[LENGTH];       /* 解答入力用 */
	int  status[MAX_KEYWORD]; /* 出題管理テーブル(0:未使用 1:出題済) */
	int  no;                  /* 問題番号 */
	int  index;               /* 出題格納場所 */
	int  error_count = UNUSED;       /* 入力エラー回数 */

	/* 初期処理 */
	srand((unsigned)time(NULL));
	init_status(status); /* 出題管理テーブルを初期化する */

	/* タイトル表示 */
    printf( "***  Ｃ言語タイピング練習プログラム  ***\n" );
    printf( "画面に出力された文字列をキーボードから入力してください。\n\n" );

	/* 主処理（10問出題する） */
    for(no = USED; no <= MAX_QUESTION; no++) {

		index = create_question(status); //問題作成

		/* 正解を入力するまで処理を繰り返す(無限) */
		do{
	        printf( "[問%d]  %s\n  >>", no, keyword[index]);
	        gets(input);  //解答入力
			
			/* 文字数のチェック */
	        if(strlen(input) != strlen(keyword[index])) {
	            puts( "★入力文字数が違っています。★" );
				error_count++;
				continue;
	        }

			/* 文字が一致しているかチェックする */
			if(check(input, keyword[index])){
				puts("入力をやり直してください。");
				error_count++;
				continue;
	        }
			break; //次の問題へ移動するためループ脱出
		}while(1); //無限ループ
    }
	
    printf( "*** 再入力回数 = %d回\n", error_count);

	int stop;
	scanf("%d",&stop);	//画面ストップ用

	return 0;
}

/*****************************************************
 *  関数名：init_status()
 *  引　数：出題管理テーブルの先頭ポインタ
 *  戻り値：なし
 *  処　理：出題管理テーブルをすべて未使用に初期化する
 *****************************************************/
void init_status(int *p)
{
	int i;
	for(i = UNUSED; i < MAX_KEYWORD; i++, p++)
		*p = UNUSED;
}

/*****************************************************
 *  関数名：create_question()
 *  引　数：出題管理テーブルの先頭ポインタ
 *  戻り値：問題を出題する添え字
 *  処　理：問題を選ぶ
 *****************************************************/
int create_question(int *p)
{
	int index;
	do{
		index = rand() % MAX_KEYWORD;
    }while(p[index] == USED);
	p[index] = USED;
	return index;
}

/*****************************************************
 *  関数名：check()
 *  引　数：文字列１のポインタ、文字列２のポインタ
 *  戻り値：0:同じ文字列
 *          0以外:異なる位置
 *  処　理：２つの文字列の内容を比較し、同じならば0を
 *          異なる場合は、異なる位置を返す
 *****************************************************/
int check(char *p, char *q)
{
	int num = 1;
	
	/* 文字列１の終わりまで1文字ずつ比較する */
	while(*p != '\0'){
		if(*p != *q){
			printf( "★%d文字目の文字「%c」は文字「%c」です。★\n", num, *p, *q);
			return -1;
		}
		num++;
		p++;
		q++;
	}
	return 0;
}

/*
実行結果
kadai741.exe      
***  Ｃ言語タイピング練習プログラム  ***
画面に出力された文字列をキーボードから入力してください。

[問1]  if
  >>if
[問2]  enum
  >>rnum
★1文字目の文字「r」は文字「e」です。★
入力をやり直してください。
[問2]  enum
  >>enumA
★入力文字数が違っています。★
[問2]  enum
  >>enum
*** 再入力回数 = 2回
*/
