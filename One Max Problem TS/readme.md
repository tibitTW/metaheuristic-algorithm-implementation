# 結果收斂圖

<img src="D:\GitHub\ML-Algos\One Max Problem TS\result.jpg" alt="result" style="zoom:20%;" />

#  程式流程(main algorithm)

```pseudocode
# initialzation
init solQueue[7] <- []
init sol
sBest <- sol
fBest <- fitness(sol)
solQueue.push(sol)

under iteration:
	nbsol <- neighborhood(sol)
	if (fitness(nbsol) > fBest) and not solQueue.contains(nbsol):
		sBest <- nbsol
		fBest <- fitness(nbsol)
		if (solQueue.size == 7):
			solQueue.pop()
		solQueue.push(sol)
	
return sBest
```



# 結果分析

最佳解 : 100 bit

平均最佳解 : 100 bit

一開始 neighborhood 的選擇方式為B2D後加減一的值再轉回二進位，但這樣做會造成兩個鄰居必有一個在tabu list內，永遠只有一個方向可以前進，等同於變相的ES。因此後來neighborhood的選法改為隨機選一個bit翻轉。但程式內更新solution的方法為比原先的fitness高者才更新solution(不確定這樣算不算作弊)