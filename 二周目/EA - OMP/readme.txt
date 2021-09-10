流程 :
用兩個 unsigned long long int, n 及 n_2 儲存 100bit，初始值皆為0。
跑無限迴圈，迴圈內設計時區塊，如果超過時間就跳出迴圈(有試過沒加計時區塊的版本，但不知為何加了計時的版本反而速度更快)。每跑一次迴圈n的值遞增，如果n為0則代表overflow，n_2遞增。
迴圈結束後(時間到時)輸出目前最佳解。

pseudocode alike:

begin = time of program begins
max_of_sum = 0 # record best value
n = 0, n_2 = 0 # use unsigned long long int to store 100 bit (64bit of n and 36bit of n_2)
while (True):
    sum = get_value(n, n_2)
    if (sum > max_of_sum):
        max_of_sum = sum
        print_current_bits()
    
    if ((current_time - begin) > TIME_LIMIT):
        break
    
    n = n + 1
    if (n == 0):
        n_2 = n_2 + 1

print_best_value()
exit()


最佳結果 : 33