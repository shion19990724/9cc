
#include <stdio.h>
#include <stdlib.h>


//　入力の終わりを表すトークンだったら１を返す
bool at_eof(){
	return token->kind == TK_EOF;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "引数の個数が正しくありません\n");
		return 1;
	}

	//　トークナイズする
	taken = tokenize(argv[1]);

	//　アセンブリの前半部分を出力する
	printf(".intel_syntax noprefix\n");
	printf(".global main\n");
	printf("main:\n");

	//　式の最初は数でなければならないので、それをチェックして、
	//　最初のmov命令を出力
	printf("	mov rax, %ld\n", expect_number());

	//　'+ <数>'あるいは'- <数>'というトークンの並びを消費しつつ
	//	アセンブリを出力
	while (!at_eof())
	{
		if (*p == '+')
		{
			p++;
			printf("	add rax, %ld\n", strtol(p, &p, 10));
			continue;
		}

		if (*p == '-')
		{
			p++;
			printf("	sub rax, %ld\n", strtol(p, &p, 10));
			continue;
		}

		fprintf(stderr, "予期しない文字です: '%c'\n", *p);
		return 1;
	}

	printf("	ret\n");
	return 0;
}
