/*
	1.代码：迭代方程：f[i][v] = max(f[i - 1][v],f[i][v - weight[i]] + Value[i]);
	2.代码：迭代方程：f[v] = max(f[v],f[v - weight[i]] + Value[i]);

	为什么有迭代方程的转换， 
	因为方程底向上逐步累加的，所以当 运行到 i的时候
	f[i-1][v]  和  f[v] 是一样的，因为上一次运行 f[i-1][v]  的结果
	 存储了，f[v] 利用的是for循环的逻辑关系，把i-1 隐藏到for 循环
	 中去了

	 同理f[i][v-weight[i]]+Value[i] 和f[v-weight[i]]+Value[i]也是
	 利用for循环的逻辑关系， 

	 因为递归方程的每一个部分都可以利用这个for循环的逻辑关系，所以
	 就可以利用for循环的逻辑关系进行数组空间空间的简化
*/