#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

int i = 1;
int k = 1;
char *p, *q;
char check[256];
char point[256];
ifstream fin;
ofstream fon;
struct Node {
	char a;
	Node *next, *prev;
};
class List {
public:
	Node *beg, *end;
	List(char *s) {
		beg = end = NULL;
		int i = 0;
		while (s[i] != NULL) {
			addend(s[i]);
			i++;
		}
		addbeg('@');
		addend('@');
	}
	~List() {
		while (beg != NULL)
			delbeg();
	}
	void addbeg(char c) {
		Node *node = new Node;
		node->a = c;
		node->prev = NULL;
		if (end == NULL) {
			end = node;
		}
		else
			beg->prev = node;
		node->next = beg;
		beg = node;
	}
	void addend(char c) {
		Node *node = new Node;
		node->a = c;
		node->next = NULL;
		if (beg == NULL) {
			beg = node;
		}
		else
			end->next = node;
		node->prev = end;
		end = node;
	}
	void delbeg() {
		if (beg != NULL) {
			Node *del = beg;
			beg = beg->next;
			if (beg != NULL)
				beg->prev = NULL;
			delete del;
		}
	}
	void delend() {
		if (end != NULL) {
			Node *del = end;
			end = end->prev;
			if (del != NULL)
				end->next = NULL;
			delete del;
		}
	}
	void show() {
		fon << endl;
		Node *s = beg->next;
		while (s != end) {
			fon << s->a;
			s = s->next;
		}
	}
};
class In {
public:
	char ch, dir;
	int mov;
	void set(char c, char d, int m) {
		ch = c;
		dir = d;
		mov = m;
	}
};
In in[1000][256];

void gen() {
	bool b;
	char *boolean = q;
	while (*boolean != 0 && *boolean != '.')
		boolean++;
	if (*boolean == 0)
		b = 0;
	else {
		b = 1;
		*boolean = 0;
	}

	int i_gen = i;

	char pchar = *p;
	char qchar = *q;

	int l;

	if (pchar != '>')
	{
		if (qchar != 0)
			q++;
		p++;
		i += 2;

	}
	else
	{
		for (l = 0; l < k; l++)
			in[i_gen][l].set(point[l], 'R', i + 1);
		i++;
	}

	while (*p != '>' || *q != 0)
	{
		if (*p == '>')
		{
			for (l = 1; l < k - 1; l++)
			{
				in[i][l].set('*', 'R', i + l);
				for (int m = 1; m < k - 1; m++)
					in[i + l][m].set(point[l], 'R', i + m);
				in[i + l][0].set(point[l], ' ', i + k - 1);
				in[i + l][k - 1].set(' ', ' ', 0);
			}
			for (int m = 0; m < k - 1; m++)
				in[i + k - 1][m].set(point[m], 'L', i + k - 1);
			in[i + k - 1][k - 1].set(*q, 'R', i + k);
			in[i][0].set(*q, 'R', i + k);
			in[i][k - 1].set(' ', ' ', 0);
			i += k;
			q++;
		}
		else if (*q == 0)
		{
			for (l = 0; l < k; l++)
				in[i][l].set(point[l], 'L', i + 1);
			in[i][check[*p]].set('*', 'R', i + 2);
			i++;
			for (l = 0; l < k; l++)
				in[i + 2][l].set(' ', ' ', 0);
			in[i + 2][k - 1].set(*p, 'L', i);
			i++; p++;
		}
		else
		{
			for (l = 0; l < k; l++)
				in[i][l].set(point[l], 'L', i + 1);
			in[i][check[*p]].set(*q, 'R', i + 2);
			i++;
			for (l = 0; l < k; l++)
				in[i + 2][l].set(' ', ' ', 0);
			in[i + 2][check[*q]].set(*p, 'L', i);
			i++; q++; p++;
		}
	}

	for (l = 0; l < k; l++)
		in[i][l].set(point[l], 'L', b + 1);
	i++;

	if (pchar != '>' && qchar != 0)
	{
		for (l = 0; l < k; l++)
		{
			in[i_gen][l].set(point[l], 'R', i_gen + 1);
			in[i_gen + 1][l].set(point[l], ' ', i_gen);
			in[i_gen + 3][l].set(' ', ' ', 0);
		}
		in[i_gen + 3][check[qchar]].set(pchar, 'R', i_gen + 1);
		in[i_gen][check[pchar]].set(qchar, 'R', i_gen + 2);
		in[i_gen + 1][0].set('@', 'L', i);
	}
	else if (qchar == 0)
	{
		for (l = 0; l < k; l++)
		{
			in[i_gen][l].set(point[l], 'R', i_gen + 1);
			in[i_gen + 1][l].set(point[l], ' ', i_gen);
			in[i_gen + 3][l].set(' ', ' ', 0);
		}
		in[i_gen + 3][k - 1].set(pchar, 'R', i_gen + 1);
		in[i_gen][check[pchar]].set('*', 'R', i_gen + 2);
		in[i_gen + 1][0].set('@', 'L', i);
	}

	for (l = 0; l < k; l++)
		in[i][l].set(point[l], 'L', i);
	in[i][0].set('@', ' ', i + 1);
	i++;
}
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	fin.open("Инструкции Маркова.txt");
	fon.open("Таблица Тьюринг.txt");
	char ins[256];
	fin >> ins;
	int l = 0;
	check['@'] = 0;
	point[0] = '@';
	while (ins[l] != 0) {
		check[ins[l]] = k;
		point[k] = ins[l];
		k++;
		l++;
	}
	check['*'] = k;
	point[k++] = '*';
	for (int l = 0; l < k; l++)
		in[0][l].set(' ', ' ', 0);
	for (int l = 1; l < k - 1; l++)
	{
		in[1][l].set(point[l], 'L', 1);
		in[2][l].set(point[l], 'L', 2);
	}
	in[1][k - 1].set('*', ' ', 3);
	for (int l = 1; l < k; l++)
		in[3][l].set(point[l], 'R', 3);
	in[3][0].set(' ', 'L', 4);
	for (int l = 0; l < k - 1; l++)
	{
		for (int m = 0; m < k - 1; m++)
			in[l + 4][m].set(point[l], 'L', m + 4);
		in[l + 4][k - 1].set(point[l], 'L', 1);
	}
	i += k + 2;

	in[2][0].set('@', ' ', 0);
	in[2][k - 1].set('*', ' ', i);
	for (int l = 1; l < k; l++)
		in[i][l].set(point[l], 'R', i);
	in[i][0].set(' ', 'L', i + 1);
	i++;
	for (int l = 0; l < k - 1; l++)
	{
		for (int m = 0; m < k - 1; m++)
			in[l + i][m].set(point[l], 'L', i + m);
		in[l + i][k - 1].set(point[l], 'L', 2);
	}
	i += k - 1;
	in[1][0].set('@', ' ', i);
	fin >> ins;
	List list(ins);
	while (!fin.eof()) {
		fin >> ins;
		p = q = ins;
		while (*q != '>')
			q++;
		q++;
		gen();
	}
	for (int l = 0; l < k; l++) {
		in[i][l].set(' ', ' ', 0);
	}
	int con, count = 0;
	int ii = i;
	fon << " ";
	while (ii) {
		fon << ' ';
		ii /= 10;
		count++;
	}
	fon << "  0";
	for (int l = 1; l <= i; l++) {
		con = 0;
		ii = l;
		while (ii) {
			ii /= 10;
			con++;
		}
		for (; con <= count + 2; con++)
			fon << ' ';
		fon << l;
	}
	fon << endl;
	for (int l = 0; l < k; l++) {
		fon << endl;
		fon << point[l];
		for (int j = 0; j <= i; j++) {
			con = 0;
			ii = in[j][l].mov;
			if (ii == 0)
				con = 1;
			else
				while (ii) {
					ii /= 10;
					con++;
				}
			for (; con <= count; con++)
				fon << ' ';
			fon << in[j][l].ch << in[j][l].dir << in[j][l].mov;
		}
		fon << endl;
	}
	int qi = 1;
	Node *pointer = list.beg;
	char prch;
	while (qi != 0) {
		prch = pointer->a;
		pointer->a = in[qi][check[prch]].ch;
		if (in[qi][check[prch]].dir == 'R')
			pointer = pointer->next;
		else if (in[qi][check[prch]].dir == 'L')
			pointer = pointer->prev;
		qi = in[qi][check[prch]].mov;
		if (list.end->a == ' ')
			list.delend();
		if (list.end->a != '@' && list.end->a != '*')
			list.addend('@');
	}
	list.show();
	fin.close();
	fon.close();
	return 0;
}