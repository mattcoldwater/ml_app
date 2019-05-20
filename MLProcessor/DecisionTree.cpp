
#include <iostream>
#include <cctype>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include "utils_why.h"
#define inf 0x3f3f3f3f
#define LL long long
#define maxn 10005
using namespace std;

int hu = 0;

int NUM;                //数据数量
int ALL;                //属性数量
int state[maxn];
map<double, int> big_map;
map<int, double> sma_map;
vector<double> info[maxn];
vector<double> s;
int ttt = 0;

struct Tree_node{
	int feature;
    int edge[500]; //决定对应下标的child是父节点的哪个分支的
	Tree_node* child[500];
	int size;
	int positive;
	int negative;
    int state; //state = -1代表有儿子，state = 1或state = 0就是叶节点了
};

struct TwoDimension{
	vector<int> a[maxn];
};

void print_data()
{
	for(int i = 0; i < ALL; i++)
		cout << s[i] << "  ";
	printf("\n");
	for(int i = 1; i <= NUM; i++)
	{
		for(int j = 0; j < ALL; j++)
			cout << info[i][j] << "  ";
		printf("\n");
	}
	for(int i = 1; i <= NUM; i++)
		printf("%d  ", state[i]);
}

void read(vector<vector<double> > features,vector<double> label)
{
	double temp1;
	double temp2;
	int y = 0;
	NUM = 492;
	ALL = 442;
	//cout<<ALL;
	//scanf("%d%d", &NUM, &ALL);
	for(int i = 1; i <= ALL; i++)
	{
        temp1 = i;
		s.push_back(temp1);
		if(!big_map.count(temp1))
		{
			big_map[temp1] = ++y;
			sma_map[y] = temp1;
		}
		//cout<<s.at(i-1);
	}

	//cout<<endl;
	for(int i = 1; i <= NUM; i++)
	{
		//int h;
		//scanf("%d", &h);
		for(int j = 1; j <= ALL; j++)
		{
		    temp2 = features[i-1].at(j-1);

			info[i].push_back(temp2);
			if(!big_map.count(temp2))
			{
				big_map[temp2] = ++y;
				sma_map[y] = temp2;
			}
            //if(i==NUM&&j==ALL) cout<<"测试特征数据提取";
		}

		//cin>>temp2;
	}
	for(int i = 1; i <= NUM; i++){
        state[i] = label.at(i-1);
        //cout<<state[i];
	}
}

void print_decision_tree(Tree_node* root, int level)
{
	if(root == NULL)	printf("\n");
	if(root != NULL){
	if(root->state != -1)
	{
		printf("(State:%d, Yes:%d, No:%d)\n", root->state, root->positive, root->negative);
		return ;
	}
	else
		cout << "(" << sma_map[root->feature] << ")" << endl;
	for(int i = 0; i < root->size; i++)
	{
		for(int j = 0; j < (level+1)*8; j++)	printf(" ");
		cout << "[" <<sma_map[root->edge[i]] << "]";
		print_decision_tree(root->child[i], level + 1);
	}}
}

double entropy(double yes, double no, double sum)
{
	double yessum = yes/sum;
	double nosum = no/sum;
	if(!yes)	yessum = 1;
	if(!no)		nosum = 1;
	return -(yes/sum*log(yessum)/log(2) + no/sum*log(nosum)/log(2));
}

int get_information_gain(int& positive, int& negative, vector<double>& str, vector<int>& use_these_data, TwoDimension& next_use_data , int* lock_feature)
{
	int t = 0;
	int rest_feature = 0;
	int rest_id;
	int num[maxn];
	int yes[maxn];
	int no[maxn];
	double Gain[maxn];

	map<double, int> mp;

	memset(Gain, -1, sizeof(Gain));

	//验证是否所有数据都正或都负
	int a = 0;
	int b = 0;
	for(int i = 0; i < use_these_data.size(); i++)
	{
		int j = use_these_data[i];
		if(state[j])	a++;
		else	b++;
	}
	if(a == use_these_data.size())
	{
		positive = use_these_data.size();
		negative = 0;
		return -2;
	}
	if(b == use_these_data.size())
	{
		positive = 0;
		negative = use_these_data.size();
		return -2;
	}

	for(int i = 0; i < ALL; i++)
	{
		//数据初始化
		memset(num, 0, sizeof(num));
		memset(yes, 0, sizeof(yes));
		memset(no, 0, sizeof(no));
		mp.clear();
		t = 0;
		//特征锁为0，此特征可用
		if(!lock_feature[i])
		{
			rest_feature ++;
			rest_id = i;
			Gain[i] = 0;
			double sum = use_these_data.size();
			for(int k = 0; k < use_these_data.size(); k++)
			{
				int j = use_these_data[k];
				//在数据集中找到此特征值
				if(!mp.count(info[j][i]))
					mp[info[j][i]] = ++t;
				int e = mp[info[j][i]];
				//num[e]代表一个特征下各特征值的数量
				num[e]++;
				//注意，e最小是1，所以用yes[e]和no[e]表示具体特征值的正负例个数，用yes[0]和no[0]表示此特征的正负例个数
				if(state[j])
				{
					yes[e]++;
					yes[0]++;
				}
				else
				{
					no[e]++;
					no[0]++;
				}
			}
			//计算此特征的information gain
			for(int j = 0; j <= t; j++)
			{
				if(!j)
					Gain[i] += entropy(yes[0], no[0], yes[0]+no[0]);
				else
					Gain[i] -= num[j]/sum*entropy(yes[j], no[j], yes[j]+no[j]);
			}
		}
	}

	//剩余特征只有一个，不会再往下分了
	if(rest_feature == 1)
	{
		for(int i = 0; i < use_these_data.size(); i++)
		{
			int j = use_these_data[i];
			if(state[j])	positive++;
			else			negative++;
		}
		str.push_back(s[rest_id]);
		return -3;
	}

	double target = -1;
	int id = -1;
	for(int i = 0; i < ALL; i++)
	{
		if(Gain[i] > target && !lock_feature[i])
		{
			target = Gain[i];
			id = i;
		}
	}
	if(id == -1)
		return -1;
	else
	{
		t = 0;
		positive = negative = 0;
		mp.clear();
		for(int i = 0; i < use_these_data.size(); i++)
		{
			int j = use_these_data[i];
			if(!mp.count(info[j][id]))
			{
				str.push_back(info[j][id]);
				mp[info[j][id]] = t++;
			}
			int e = mp[info[j][id]];
			next_use_data.a[e].push_back(j);
			if(state[j])	positive ++;
			else	negative ++;
		}
	}
	return id;
}

Tree_node* build_decision_tree(vector<int> use_these_data, int* lock_feature)   //属性锁不是全局变量
{
	//函数变量声明
	Tree_node* neww = (Tree_node*) malloc (sizeof(Tree_node));
	neww->state = -1;
	int positive = 0;
	int negative = 0;
	int target = -1;
	neww->size = 0;
	vector<double> information_gain;
	TwoDimension next_use_data;
	vector<double> str;
	//计算此节点并递归建树

	target = get_information_gain(positive, negative , str, use_these_data, next_use_data, lock_feature);
	//特殊的返回值
	if(target == -1)
		return NULL;
	if(target == -2)
	{
		neww->positive = positive;
		neww->negative = negative;
		if(positive > negative)	neww->state = 1;
		else					neww->state = 0;
		return neww;
	}
	if(target == -3)
	{
		neww->positive = positive;
		neww->negative = negative;
		neww->feature = big_map[str[0]];
		Tree_node* newc = (Tree_node*) malloc (sizeof(Tree_node));
		if(positive > negative)	newc->state = 1;
		else					newc->state = 0;
		newc->negative = negative;
		newc->positive = positive;
		neww->child[neww->size++] = newc;
		return neww;
	}
	neww->feature = big_map[s[target]];
	neww->positive = positive;
	neww->negative = negative;

	//剩下的数据全正或全负，直接建立叶结点
	if(positive == 0)
	{
		neww->positive = 0;
		neww->negative = negative;
		Tree_node* newc = (Tree_node*) malloc (sizeof(Tree_node));
		newc->state = 0;
		newc->negative = negative;
		newc->positive = 0;
		neww->child[neww->size++] = newc;
		return neww;
	}
	if(negative == 0)
	{
		neww->positive = positive;
		neww->negative = negative;
		Tree_node* newc = (Tree_node*) malloc (sizeof(Tree_node));
		newc->state = 1;
		newc->negative = negative;
		newc->positive = positive;
		neww->child[neww->size++] = newc;
		return neww;
	}

	//递归建树
	neww->size = 0;
	for(int i = 0; i < str.size(); i++)
	{
		neww->edge[neww->size] = big_map[str[i]];
		int new_lock[maxn];

		for(int j = 0; j < ALL; j++)
			new_lock[j] = lock_feature[j];
		new_lock[target] = 1;

		neww->child[neww->size++] = (build_decision_tree(next_use_data.a[i], new_lock));
	}
	return neww;
}

/*int main2()
{

    vector<vector<double> > features;
    vector<int> labels;
    read_csv(features, labels, "D:\\project\\MLProcessor\\texts\\data_aac.csv");

	//freopen("C:\\Users\\123\\Desktop\\output.txt","r",stdin);
	Tree_node* decision_tree;
	decision_tree = (Tree_node*) malloc (sizeof(Tree_node));
	//清空子树
	vector<int> use_these_data;
    for(int i = 1; i <= NUM; i++)
		use_these_data.push_back(i);
	//所有数据都可以用
	int lock_feature[maxn];
	memset(lock_feature, 0, sizeof(lock_feature));
	//所有特性都可选择
	decision_tree = build_decision_tree(use_these_data, lock_feature);
	//建树
	printf("\n\n");
	print_decision_tree(decision_tree, 0);
}*/
