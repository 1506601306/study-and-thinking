#include <iostream>  
using namespace std;

int weight[110], //  用来存损耗
Value[110],   //用来存价值
num[110];    //用来存数量
int f[1100];  //用来存结果数组
int limit;  //用来存背包容量

///  w=w[i], v=value[i] 
// w 表示第i个物品的损耗，v 表示第i个物品的价值，limit 背包的容量
inline void ZeroOnePack(int w, int v)
{                   
	int j;
	for (j = limit; j >= w; j--)
	{
		if (f[j - w] + v > f[j])
			f[j] = f[j - w] + v;
	}
}


// j只有从w[i]出发才有意义，因为这个方法是判断 第i个物品是否应该加入
// 背包容量小于w[i]的 根本都没有意义，如果 j要是从 0开始取的话
//那么 if判断的前面就要加上  j>w的判断，这样还是和此做法相同，

//w 表示第i个物品的损耗，v 表示第i个物品的价值，limit 背包的容量
inline void CompletePack(int w, int v)
{
	int j;
	for (j = w; j <= limit; j++)
	{
		if (f[j - w] + v > f[j])
			f[j] = f[j - w] + v;
	}
}

//w 表示第i件物品的重量，v表示第i件物品的价值，ammount表示第i件物品的数量
inline void MultiplePack(int w, int v, int amount)
{
	//如果 amount件物品的总重量大于背包的重量，那么就从中选取一部分
	//采用完全背包的方法，需要说明的是此时选取的数量一定小于等于amount
	//当使用 参数 i进行说明的话，那么就表示，从背包容量=w[i]，一直到
	//背包容量等于 limit的背包中，装入任意个 i物品，（i<=amount）
	//使得背包的容量最大，采用完全背包的好处是可以装入任意多个
	if (amount * w >= limit)
	{
		CompletePack(w, v);
		return;
	}

	//如果amount件物品的总重量小于背包的重量，那就采取01背包的方法装入

	// 需要说明一个 定理  1，2，4，8  .。。乘2 递增的数，可以表示任意
	//一个自然数

	//使用01 背包的好处是每一个数据只能访问一次，当 1，2，4，8 等依次
	//放入的时候，那么就会形成一个树，树的节点上从左到右是依次加1的自然数
	//当然树的叶子节点的最右端表示的就是这个自然数 amount，这个1，2，4，8
	//的数列的生成方法就是下面的式子

	//此外需要说明的是，这个数可以看作是二进制树，当依次放入完所有的
	//可能性了之后。存放结果的数组就已经更新了
	for (int k = 1; k<amount; k <<= 1)
	{
		ZeroOnePack(k*w, k*v);
		amount -= k;
	}

	//amount*w 表示的是这个树放入的最后一个正整数，因为不可能所有的数
	//都一定被2整除，最后一个不能被2整除的数保存在amount中，只有01背包
	//中放入这个数，所有的自然数才完整
	ZeroOnePack(amount*w, amount*v);
}
  //为什么第i件物品的总重量大于背包的时候要采取 完全背包，而小于背包的
  //时候要采取01背包呢？
   
  // 因为背包中要装入若干件i 物品，这个i物品的数量不好说，是由i物品的
  //重量决定的，但是不能全部装入，如果全部装入会爆掉，所以只能根据
  //背包的重量和i物品的重量动态的装入，因为可以重复装入，所以采取完全
  //背包的算法

  //同理为什么采取01背包呢，因为 i件物品的总重量小于背包的重量，所以
  //可以全部装入，也可以装入一部分，那么究竟该装入多少好呢，这是就利用
  //01背包，每个内存单元只能被访问一次的特性，同时利用 二进制定理
  //把所有的数列据一遍从1到amount，从中找到最合适的那个

  //当 i+1的时候，就会动态比较 装个x个i+1物品的时候的最大价值 1<=x<=amount
  //会综合 i 物品 和 i+1物品 的价值综合的判断最大价值，同时修改价值数组
  //使得 背包容量从 w[i+1] 到 W[V]的所有背包的价值都是综合i物品和i+1物品
  //的最大价值， 以后i+2同理，一直到最后一个物品，当最后一个物品装入完成
  //后这个价值数组就是综合 物品1到物品n，n表示最后一个物品 的背包中的
  //最大价值的体现 
     //此时f[v]就表示多背包问题，题目描述的问题的解了

  //需要说明的是 这个价值数组中的每一个元素一定有 值吗？
  //答案是不一定，这要根据各个物品的重量和背包的重量来决定，
   //这个价值数组有值的范围是 最小的物品重量 下标 到 limit 背包下标
   //在 最小重量之前的数组元素由于具有int类型数组的特性，所以就会默认的为0
    //此外使用内联函数可以加快程序的执行速度
int main()
{
	int T, n;
	cin >> T;
	while (T--)
	{
		cin >> limit >> n;

		for (int i = 0; i<n; i++)
			cin >> weight[i] >> Value[i] >> num[i];

		memset(f, 0, sizeof(f));

		for (int i = 0; i<n; i++)
			MultiplePack(weight[i], Value[i], num[i]);

		cout << f[limit] << endl;
	}
	return 0;
}